
#include <TF1.h>
#include <TProfile.h>
#include <TChain.h>
#include <TTree.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TFile.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TRandom3.h>

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>


#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

using namespace std;


#ifdef _MAKECINT_
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#endif

int GetPhiBin(float /*phi*/);
int GetEtaBin(float /*eta*/);
int GetPtBin(float /*pt*/);
double delphi(double /*phi1*/, double /*phi2*/);


//! pt binning
double ptbins[] ={10,15,20,27,35,45,57,72,90,120,150,200,300,400,550,750,1000};
//double ptbins[]={10, 10.5, 11 ,11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 16, 17, 18, 19, 20, 27, 35, 45, 57, 72, 90, 120, 150, 200, 300, 400, 550,  750, 1000};
const int nbins = sizeof(ptbins)/sizeof(double) - 1;

//! data pt binning
//double ptbins_data[] ={100, 110, 120, 130, 140, 150, 160, 170, 180, 200, 240, 300};
//const int dbins = sizeof(ptbins_data)/sizeof(double) - 1;

//! constants
int iYear=2014;
const double pi=acos(-1.);
//const double pi2=2*pi -1;

const float ketacut=3.0;
const double kptrecocut=10.0;
const double kptgencut =0.0;
const double kdRCut=0.30;
double rbinl=0.0;
double rbinh=2.0;

//const double etabins[]={-3.000,
//			      -2.500, -2.043, -1.930, -1.740, -1.653, -1.566, -1.392,
//			      -1.218, -1.131, -0.957, -0.879, -0.783, -0.609, -0.522,
//			      -0.435, -0.348, -0.261, -0.087,
//			      +0.000,
//			      +0.087, +0.261, +0.348, +0.435, +0.522, +0.609, +0.783,
//			      +0.879, +0.957, +1.131, +1.218, +1.392, +1.566,
//			      +1.653, +1.740, +1.930, +2.043, +2.500,
//			      +3.000
//};

const double etabins[]={-3.0,-2.4,-1.8,-1.4,-1.0,-0.8,-0.6,-0.4,-0.2,
			0.0,0.2,0.4,0.6,0.8,1.0,1.4,1.8,2.4,3.0};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.700,-2.100,-1.500,-0.900,-0.300,
			  0.300,0.900,1.500,2.100,2.700,3.141
};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

/*
const int kAlgos = 1;
const char *calgo[kAlgos] = {"ak3Calo"};
string corrFileName[kAlgos]= {"AK3Calo"};
*/

const int kAlgos = 12;
const char *calgo[kAlgos] = {"ak3PF","ak4PF","ak5PF","ak3Calo","ak4Calo","ak5Calo",
			     "akPu3PF","akPu4PF","akPu5PF","akPu3Calo","akPu4Calo","akPu5Calo"
};
string corrFileName[kAlgos]= {"AK3PF","AK4PF","AK5PF","AK3Calo","AK4Calo","AK5Calo",
			      "AKPu3PF","AKPu4PF","AKPu5PF","AKPu3Calo","AKPu4Calo","AKPu5Calo"
};

//float kDelRCut=0.3;

bool is_file(const char *fileName);
bool is_file(const char *fileName)
{
  std::ifstream infile(fileName,ios::in);
  return infile.good();
}



TStopwatch timer;
int CalJec(const char *ksp="Pbp")
{

  timer.Start();

  std::string inname="";
  int knj = kAlgos;

  //inname="leading_gammajet_Pbp_bacJEC_mergedpthatbins_test_MC.root";
  inname="merged_Pbp_leadingpho_v1.root";
  //inname="/net/hidsk0001/d00/scratch/pawan/combinedPtHat/dijet_pbpb_bacJEC_mergedpthatbins_Track8_Jet29_MC.root";
  //inname="/net/hidsk0001/d00/scratch/pawan/combinedPtHat/dijet_pbpb_official_mergedpthatbins_Track8_Jet28_MC.root";

  TFile *fin = new TFile(inname.c_str(),"r");

  std::string outname="";
  //outname="JetResponse_histos_lowpt_ppSignal_pbpbReco_official_Track8_Jet28_MC.root";
  //outname="JetResponse_histos_lowpt_ppSignal_pbpbReco_final_Track8_Jet28_MC.root";
  outname="afterJEC_output_Pbp.root";

  TFile *fout = new TFile(outname.c_str(),"RECREATE");

  std::cout<<"\t"<<std::endl;
  std::cout<<"\t"<<std::endl;
  std::cout<<"**************************************************** "<<std::endl;
  std::cout<<Form("Analyzeforest_jec : %s",ksp)<<std::endl;
  std::cout<<Form("eta cut for %0.3f ",ketacut)<<std::endl;
  std::cout<<"**************************************************** "<<std::endl;
  std::cout<<"\t"<<std::endl;
  std::cout<<"\t"<<std::endl;


  //! Before running check all the txt files are available
  for(int nj=0; nj<knj; nj++){
    //std::string L2Name = "/net/hisrv0001/home/pawan/Validation/Track8_Jet19/CMSSW_5_3_16/src/JEC_base/pbpb2014/txtfiles/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L2Relative_"+corrFileName[nj]+".txt";
    std::string L2Name = "JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20_L2Relative_"+corrFileName[nj]+".txt";
    if(!is_file(L2Name.c_str())){
      cout<<"**** ++++++  L2Name does not exists  "<<L2Name<<endl;
      return  2;
    }
    //std::string L3Name = "/net/hisrv0001/home/pawan/Validation/Track8_Jet19/CMSSW_5_3_16/src/JEC_base/pbpb2014/txtfiles/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L3Absolute_"+corrFileName[nj]+".txt";
    std::string L3Name = "JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20_L3Absolute_"+corrFileName[nj]+".txt";
    if(!is_file(L3Name.c_str())){
      cout<<"**** ++++++  L3Name does not exists  "<<L3Name<<endl;
      return 3;
    }
  }

  //!
  //! Define histograms here
  //   TH1::SetDefaultSumw2();
  //   TH2::SetDefaultSumw2();
  //   TH3::SetDefaultSumw2();
  //  TProfile::SetDefaultSumw2();

  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  TH1F *hBin    = new TH1F("hBin","Centrality bin",200,-0.5,200-0.5);
  hBin->Sumw2();
  TH1F *hpthat  = new TH1F("hpthat","pt-hat distribution",500,0,1000);
  hpthat->Sumw2();

  //! Gen matched jets
  TH1F *hgenpt_genm [knj], *hrecopt_genm[knj], *hrawpt_genm[knj];
  TH1F *hgeneta     [knj], *hgenphi     [knj];
  TH1F *hjeteta     [knj], *hjetphi     [knj];

  //! Resposnse
  TH1F *hrescrpt_genm [knj][nbins], *hresrrpt_genm [knj][nbins], *hratio [knj][nbins];
  TH1F *hrescrpt_genm_eta [knj][nbins][neta], *hresrrpt_genm_eta [knj][nbins][neta], *hratio_eta [knj][nbins][neta];
  TH1F *hrescrpt_genm_phi [knj][nbins][nphi], *hresrrpt_genm_phi [knj][nbins][nphi], *hratio_phi [knj][nbins][nphi];

  TH1F *havjetpt_genm[knj][nbins], *havrawpt_genm[knj][nbins];

  //! Response vs deltar
  TH1F *hRspVsDeltaR[knj][25];

  TProfile *hcorr_rawpt[knj], *hcorr_genpt[knj], *hcorr_recopt[knj];
  TProfile *hl3corr_rawpt[knj], *hl3corr_genpt[knj], *hl3corr_recopt[knj];
  TProfile *hl2corr_rawpt[knj], *hl2corr_genpt[knj], *hl2corr_recopt[knj];
  TProfile *hrawpt_genpt[knj], *hrecopt_genpt[knj];

  TH1F *hDeltaR[knj];

  //! Efficency histos
  TH1F *hdRAll [knj], *hdRSel [knj];
  TH1F *hPtAll [knj], *hPtSel [knj];
  TH1F *hEtaAll[knj], *hEtaSel[knj];
  TH1F *hPhiAll[knj], *hPhiSel[knj];

  //! Fake histograms
  TH1F *hFakePtAll [knj], *hFakePtSel [knj];
  TH1F *hFakeEtaAll[knj], *hFakeEtaSel[knj];
  TH1F *hFakePhiAll[knj], *hFakePhiSel[knj];



  for(int nj=0;nj<knj;nj++){

    fout->mkdir(Form("%sJetAnalyzer",calgo[nj]));
    fout->cd(Form("%sJetAnalyzer",calgo[nj]));

    hgenpt_genm [nj] = new TH1F(Form("hgenpt_genm%d",nj),Form("Gen matched gen p_{T} distribution jet centb %s",calgo[nj]),500,0,1000);
    hgenpt_genm [nj]->Sumw2();
    hrecopt_genm[nj] = new TH1F(Form("hrecopt_genm%d",nj),Form("Gen matched reco p_{T} distribution jet %s",calgo[nj]),500,0,1000);
    hrecopt_genm[nj]->Sumw2();
    hrawpt_genm [nj] = new TH1F(Form("hrawpt_genm%d",nj),Form("Gen matched raw p_{T} distribution jet  %s",calgo[nj]),500,0,1000);
    hrawpt_genm [nj]->Sumw2();

    hjeteta[nj] = new TH1F(Form("hjeteta%d",nj),Form("jet eta distribution jet %s",calgo[nj]),72,-ketacut,ketacut);
    hjeteta[nj]->Sumw2();
    hjetphi[nj] = new TH1F(Form("hjetphi%d",nj),Form("jet phi distribution jet %s",calgo[nj]),72,-pi,pi);
    hjetphi[nj]->Sumw2();

    hgeneta[nj] = new TH1F(Form("hgeneta%d",nj),Form("gen jet eta distribution jet %s",calgo[nj]),72,-ketacut,ketacut);
    hgeneta[nj]->Sumw2();
    hgenphi[nj] = new TH1F(Form("hgenphi%d",nj),Form("gen jet phi distribution jet %s",calgo[nj]),72,-pi,pi);
    hgenphi[nj]->Sumw2();


    hcorr_genpt [nj] = new TProfile(Form("hcorr_genpt%d",nj),Form("Corr Fac gen p_{T} %s",calgo[nj]),nbins,ptbins);
    hcorr_genpt [nj]->Sumw2();
    hcorr_rawpt [nj] = new TProfile(Form("hcorr_rawpt%d",nj),Form("Corr Fac raw p_{T} %s",calgo[nj]),nbins,ptbins);
    hcorr_rawpt [nj]->Sumw2();
    hcorr_recopt [nj] = new TProfile(Form("hcorr_recopt%d",nj),Form("Corr Fac reco p_{T} %s",calgo[nj]),nbins,ptbins);
    hcorr_recopt [nj]->Sumw2();

    hl2corr_genpt [nj] = new TProfile(Form("hl2corr_genpt%d",nj),Form("l2Corr Fac gen p_{T} %s",calgo[nj]),nbins,ptbins);
    hl2corr_genpt [nj]->Sumw2();
    hl2corr_rawpt [nj] = new TProfile(Form("hl2corr_rawpt%d",nj),Form("l2Corr Fac raw p_{T} %s",calgo[nj]),nbins,ptbins);
    hl2corr_rawpt [nj]->Sumw2();
    hl2corr_recopt [nj] = new TProfile(Form("hl2corr_recopt%d",nj),Form("l2Corr Fac reco p_{T} %s",calgo[nj]),nbins,ptbins);
    hl2corr_recopt [nj]->Sumw2();

    hl3corr_genpt [nj] = new TProfile(Form("hl3corr_genpt%d",nj),Form("l3Corr Fac gen p_{T} %s",calgo[nj]),nbins,ptbins);
    hl3corr_genpt [nj]->Sumw2();
    hl3corr_rawpt [nj] = new TProfile(Form("hl3corr_rawpt%d",nj),Form("l3Corr Fac raw p_{T} %s",calgo[nj]),nbins,ptbins);
    hl3corr_rawpt [nj]->Sumw2();
    hl3corr_recopt [nj] = new TProfile(Form("hl3corr_recopt%d",nj),Form("l3Corr Fac reco p_{T} %s",calgo[nj]),nbins,ptbins);
    hl3corr_recopt [nj]->Sumw2();

    hrawpt_genpt [nj] = new TProfile(Form("hrawpt_genpt%d",nj),Form("reco p_{T} gen p_{T} %s",calgo[nj]),nbins,ptbins);
    hrawpt_genpt [nj]->Sumw2();
    hrecopt_genpt [nj] = new TProfile(Form("hrecopt_genpt%d",nj),Form("reco p_{T} gen p_{T} %s",calgo[nj]),nbins,ptbins);
    hrecopt_genpt [nj]->Sumw2();

    hDeltaR[nj]  = new TH1F(Form("hDeltaR%d",nj),Form("#DeltaR for algorithm %s",calgo[nj]),100,0,1);
    hDeltaR[nj]->Sumw2();


    //! efficcy histograms
    hdRAll [nj] = new TH1F(Form("hdRAll%d",nj),Form("dR Denominator pT for algorithm %s ",calgo[nj]),100,0,1);
    hdRAll [nj]->Sumw2();
    hPtAll [nj] = new TH1F(Form("hPtAll%d",nj),Form("Denominator pT for algorithm %s ",calgo[nj]),nbins,ptbins);
    hPtAll [nj]->Sumw2();
    hEtaAll[nj] = new TH1F(Form("hEtaAll%d",nj),Form("Denominator eta  for algorithm %s ",calgo[nj]),neta,etabins);
    hEtaAll[nj]->Sumw2();
    hPhiAll[nj] = new TH1F(Form("hPhiAll%d",nj),Form("Denominator  phi  for algorithm %s",calgo[nj]),nphi,phibins);
    hPhiAll[nj]->Sumw2();

    hdRSel [nj] = new TH1F(Form("hdRSel%d",nj),Form("dR Numerator pT for algorithm %s ",calgo[nj]),100,0,1);
    hdRSel [nj]->Sumw2();
    hPtSel [nj] = new TH1F(Form("hPtSel%d",nj),Form("Numerator pT for algorithm %s ",calgo[nj]),nbins,ptbins);
    hPtSel [nj]->Sumw2();
    hEtaSel[nj] = new TH1F(Form("hEtaSel%d",nj),Form("Numerator eta  for algorithm %s ",calgo[nj]),neta,etabins);
    hEtaSel[nj]->Sumw2();
    hPhiSel[nj] = new TH1F(Form("hPhiSel%d",nj),Form("Numerator  phi  for algorithm %s",calgo[nj]),nphi,phibins);
    hPhiSel[nj]->Sumw2();

    hFakePtAll [nj] = new TH1F(Form("hFakePtAll%d",nj),Form("Fake Denominator pT for algorithm %s ",calgo[nj]),nbins,ptbins);
    hFakePtAll [nj]->Sumw2();
    hFakeEtaAll[nj] = new TH1F(Form("hFakeEtaAll%d",nj),Form("Fake Denominator eta  for algorithm %s ",calgo[nj]),neta,etabins);
    hFakeEtaAll[nj]->Sumw2();
    hFakePhiAll[nj] = new TH1F(Form("hFakePhiAll%d",nj),Form("Fake Denominator  phi  for algorithm %s",calgo[nj]),nphi,phibins);
    hFakePhiAll[nj]->Sumw2();

    hFakePtSel [nj] = new TH1F(Form("hFakePtSel%d",nj),Form("Fake Numerator pT for algorithm %s ",calgo[nj]),nbins,ptbins);
    hFakePtSel [nj]->Sumw2();
    hFakeEtaSel[nj] = new TH1F(Form("hFakeEtaSel%d",nj),Form("Fake Numerator eta  for algorithm %s ",calgo[nj]),neta,etabins);
    hFakeEtaSel[nj]->Sumw2();
    hFakePhiSel[nj] = new TH1F(Form("hFakePhiSel%d",nj),Form("Fake Numerator  phi  for algorithm %s",calgo[nj]),nphi,phibins);
    hFakePhiSel[nj]->Sumw2();


    for(int ir=0;ir<25;ir++){
      //! Response vs DeltaR
      hRspVsDeltaR[nj][ir] = new TH1F(Form("hRspVsDeltaR%d_%d",nj,ir),Form(" <recopt/refpt> vs. #DeltaR (%d) algorithm %s",ir,calgo[nj]),75,rbinl,rbinh);
      hRspVsDeltaR[nj][ir]->Sumw2();
    }

    for(int ip=0;ip<nbins;ip++){
      havjetpt_genm [nj][ip]= new TH1F(Form("havjetpt_genm%d_%d",nj,ip),Form("(<Reco>) jet p_{T} %s %0.0f < p_{T}^{REF} < %0.0f",calgo[nj],ptbins[ip],ptbins[ip+1]),500,0,1000);
      havjetpt_genm [nj][ip]->Sumw2();
      havrawpt_genm [nj][ip]= new TH1F(Form("havrawpt_genm%d_%d",nj,ip),Form("(<Raw>) jet p_{T} %s %0.0f < p_{T}^{REF} < %0.0f",calgo[nj],ptbins[ip],ptbins[ip+1]),500,0,1000);
      havrawpt_genm [nj][ip]->Sumw2();

      //! Gen matched Response and resolution
      hrescrpt_genm [nj][ip]= new TH1F(Form("hrescrpt_genm%d_%d",nj,ip),Form("(Reco/Gen) jet p_{T} %s %0.0f < p_{T}^{REF} < %0.0f",calgo[nj],ptbins[ip],ptbins[ip+1]),150,rbinl,rbinh);
      hrescrpt_genm [nj][ip]->Sumw2();
      hresrrpt_genm [nj][ip]= new TH1F(Form("hresrrpt_genm%d_%d",nj,ip),Form("(Raw/Gen) jet p_{T} %s %0.0f < p_{T}^{REF} < %0.0f",calgo[nj],ptbins[ip],ptbins[ip+1]),150,rbinl,rbinh);
      hresrrpt_genm [nj][ip]->Sumw2();
      hratio[nj][ip]= new TH1F(Form("hratio%d_%d",nj,ip),Form("(Reco/Raw) jet p_{T} %s %0.0f < p_{T}^{REF} < %0.0f",calgo[nj],ptbins[ip],ptbins[ip+1]),150,rbinl,rbinh);
      hratio[nj][ip]->Sumw2();

      for(int ie=0;ie<neta;ie++){
	hrescrpt_genm_eta [nj][ip][ie]= new TH1F(Form("hrescrpt_genm_eta%d_%d_%d",nj,ip,ie),Form("(Reco/Gen) jet p_{T} %s %d %d",calgo[nj],ip,ie),150,rbinl,rbinh);
	hrescrpt_genm_eta [nj][ip][ie]->Sumw2();
	hresrrpt_genm_eta [nj][ip][ie]= new TH1F(Form("hresrrpt_genm_eta%d_%d_%d",nj,ip,ie),Form("(Raw/Gen) jet p_{T} %s %d %d",calgo[nj],ip,ie),150,rbinl,rbinh);
	hresrrpt_genm_eta [nj][ip][ie]->Sumw2();
	hratio_eta[nj][ip][ie]= new TH1F(Form("hratio_eta%d_%d_%d",nj,ip,ie),Form("(Reco/Raw) jet p_{T} %s %d %d",calgo[nj],ip,ie),150,rbinl,rbinh);
	hratio_eta[nj][ip][ie]->Sumw2();
      }

      for(int ij=0;ij<nphi;ij++){
	hrescrpt_genm_phi [nj][ip][ij]= new TH1F(Form("hrescrpt_genm_phi%d_%d_%d",nj,ip,ij),Form("(Reco/Gen) jet p_{T} %s %d %d",calgo[nj],ip,ij),150,rbinl,rbinh);
	hrescrpt_genm_phi [nj][ip][ij]->Sumw2();
	hresrrpt_genm_phi [nj][ip][ij]= new TH1F(Form("hresrrpt_genm_phi%d_%d_%d",nj,ip,ij),Form("(Raw/Gen) jet p_{T} %s %d %d",calgo[nj],ip,ij),150,rbinl,rbinh);
	hresrrpt_genm_phi [nj][ip][ij]->Sumw2();
	hratio_phi[nj][ip][ij]= new TH1F(Form("hratio_phi%d_%d_%d",nj,ip,ij),Form("(Reco/Raw) jet p_{T} %s %d %d",calgo[nj],ip,ij),150,rbinl,rbinh);
	hratio_phi[nj][ip][ij]->Sumw2();
      }
    }
    fout->cd("../");
  }//! nj
  std::cout<<"Initialized the histograms " <<std::endl;
  /////////////////////////////////////////////////////////////////////////////////////////


  TTree *tr_in=0;
  //std::vector<double> vJets;
  Long64_t nbytes=0;

  double nevt [kAlgos]={0};
  double njets[kAlgos]={0};

  for(int nj=0; nj<knj; nj++){

    tr_in = (TTree*)fin->Get(Form("%sJetAnalyzer/t",calgo[nj]));
    Long64_t nentries = tr_in->GetEntries();
    std::cout<<Form("# of entries in TTree for %s %s : ",calgo[nj],ksp)<<nentries<<std::endl;


    //Declaration of leaves types
    int hiBin;
    int   nref;
    float pthat;
    float weight;
    float corrpt[1000];
    float jtpt[1000];
    float rawpt[1000];
    float jteta[1000];
    float jtphi[1000];
    float refpt[1000];
    float refeta[1000];
    float refphi[1000];
    float refdrjt[1000];
    float refparton_pt[1000];
    int subid[1000];

    tr_in->SetBranchAddress("hiBin",&hiBin);
    tr_in->SetBranchAddress("nref",&nref);
    tr_in->SetBranchAddress("pthat",&pthat);
    tr_in->SetBranchAddress("weight",&weight);
    tr_in->SetBranchAddress("rawpt",rawpt);
    tr_in->SetBranchAddress("corrpt",corrpt);
    tr_in->SetBranchAddress("jtpt",jtpt);  //! this is also raw pt
    tr_in->SetBranchAddress("jteta",jteta);
    tr_in->SetBranchAddress("jtphi",jtphi);
    tr_in->SetBranchAddress("refpt",refpt);
    tr_in->SetBranchAddress("refphi",refphi);
    tr_in->SetBranchAddress("refeta",refeta);
    tr_in->SetBranchAddress("refdrjt",refdrjt);
    tr_in->SetBranchAddress("refparton_pt",refparton_pt);
    tr_in->SetBranchAddress("subid",subid);

    //! Load the jet energy correction factors on fly
    string L2Name, L3Name;
    JetCorrectorParameters *parHI_l2=0, *parHI_l3=0;
    vector<JetCorrectorParameters> vpar_HI;
    FactorizedJetCorrector *_JEC_HI;
  //  FactorizedJetCorrector *_JEC_HI = new FactorizedJetCorrector(vpar_HI);//JR

    //! Sample from which JEC was derived
    //L2Name = "/net/hisrv0001/home/pawan/Validation/Track8_Jet19/CMSSW_5_3_16/src/JEC_base/pbpb2014/txtfiles/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L2Relative_"+corrFileName[nj]+".txt";
    L2Name = "JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20_L2Relative_"+corrFileName[nj]+".txt";
    cout<<"**** ++++++  L2Name "<<L2Name<<endl;
    //L3Name = "/net/hisrv0001/home/pawan/Validation/Track8_Jet19/CMSSW_5_3_16/src/JEC_base/pbpb2014/txtfiles/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L3Absolute_"+corrFileName[nj]+".txt";
    L3Name = "JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20_L3Absolute_"+corrFileName[nj]+".txt";
    cout<<"**** ++++++  L3Name "<<L3Name<<endl;

    //! Official pp sample JEC
    //L2Name = "/net/hisrv0001/home/pawan/Validation/Track8_Jet19/CMSSW_5_3_16/src/JEC_base/pbpb2014/official/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet28_L2Relative_"+corrFileName[nj]+".txt";
    //cout<<"**** ++++++  L2Name "<<L2Name<<endl;
    ///L3Name = "/net/hisrv0001/home/pawan/Validation/Track8_Jet19/CMSSW_5_3_16/src/JEC_base/pbpb2014/official/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet28_L3Absolute_"+corrFileName[nj]+".txt";
    //cout<<"**** ++++++  L3Name "<<L3Name<<endl;
    std::cout<<std::endl;


    parHI_l2 = new JetCorrectorParameters(L2Name.c_str());
    parHI_l3 = new JetCorrectorParameters(L3Name.c_str());

    vpar_HI.push_back(*parHI_l2);
    vpar_HI.push_back(*parHI_l3);
    _JEC_HI = new FactorizedJetCorrector(vpar_HI);


    Int_t iEvent=0;
    for (Long64_t i=0; i<nentries;i++) {
      nbytes += tr_in->GetEntry(i);
      //return 0;

      double wcen=1;
      double wvz=1;
      //! weight  for the merging of the samples for different pT hat bins
      double wxs = weight;

      //if(i%50000==0)std::cout<<" ********** Event # " <<i<<"\t weight  : "<<weight<<"\t pthat : "<<pthat<<std::endl;
      if(nj==3)hBin->Fill(hiBin,wxs*wcen*wvz);

      //! xsec-weight
      if(nj==3)hpthat->Fill(pthat,wxs*wcen*wvz);
      nevt[nj]++;

      //! Gen matched jets loop
      for(int igen=0; igen<nref; igen++){
	//if(igen>2)continue;

	int gj = igen;
	if(fabs(refeta[gj]) > ketacut || rawpt[gj] <= 10)continue;

	_JEC_HI->setJetEta(jteta[gj]);
	_JEC_HI->setJetPt (rawpt[gj]);
//	float corrfac = _JEC_HI->getCorrection();
	//float corrfac =1.0; 
	std::vector<float> subcorr = _JEC_HI->getSubCorrections();
    float corrfac = subcorr[subcorr.size()-1]; 
    float l2corr = subcorr[0];
	float l3corr = subcorr[1];
	float recopt  = rawpt[gj]*corrfac;  //! correction with JECv14
	//float recopt_l2corr = rawpt[gj]*l2corr;
	//float recopt_l3corr = rawpt[gj]*l3corr;


// 	if(rawpt[gj] > 10 && rawpt[gj] < 15){
// 	  cout <<" WARNING " << calgo[nj] << " refpt : " << refpt[gj] <<  " rawpt :  " << rawpt[gj] << "\t recopt "<< recopt << " corr : "
// 	       << corrfac << "  l3corr : " << l3corr << "  l2corr : " << l2corr << endl;
// 	}

	if( (abs(corrfac - recopt/rawpt[gj]) > 0.2) || corrfac > 5 ){
	  std::cout <<" WARNING " << calgo[nj] << " refpt : " << refpt[gj] <<  " rawpt :  " << rawpt[gj] << "\t recopt "<< recopt << " corr : " << std::endl;
	  continue;
	}

	hcorr_genpt[nj]->Fill(refpt[gj],corrfac,wxs*wcen*wvz);
	hl2corr_genpt[nj]->Fill(refpt[gj],l2corr,wxs*wcen*wvz);
	hl3corr_genpt[nj]->Fill(refpt[gj],l3corr,wxs*wcen*wvz);

	hcorr_rawpt[nj]->Fill(rawpt[gj],corrfac,wxs*wcen*wvz);
	hl2corr_rawpt[nj]->Fill(rawpt[gj],l2corr,wxs*wcen*wvz);
	hl3corr_rawpt[nj]->Fill(rawpt[gj],l3corr,wxs*wcen*wvz);

	hcorr_recopt[nj]->Fill(recopt,corrfac,wxs*wcen*wvz);
	hl2corr_recopt[nj]->Fill(recopt,l2corr,wxs*wcen*wvz);
	hl3corr_recopt[nj]->Fill(recopt,l3corr,wxs*wcen*wvz);


	hrawpt_genpt[nj]->Fill(refpt[gj],rawpt[gj],wxs*wcen*wvz);
	hrecopt_genpt[nj]->Fill(refpt[gj],recopt,wxs*wcen*wvz);
	float recoeta = jteta[gj];
	float recophi = jtphi[gj];
	float delr    = refdrjt[gj];


	if(refpt[gj] > 35.0){

	  //! DeltaR efficiency
	  hDeltaR[nj]->Fill(delr,wxs*wcen*wvz);
	  for (int idrmax=0;idrmax<100;idrmax++) {
	    float drmax = idrmax*0.01+0.005;
	    hdRAll[nj]->Fill(drmax,wxs*wcen*wvz);
	    if (delr<drmax){
	      hdRSel[nj]->Fill(drmax,wxs*wcen*wvz);
	    }
	  }

	  //! Reconstruction
	  //! Denominator for reconstruction efficiency
	  hPtAll [nj]->Fill(refpt[gj],wxs*wcen*wvz);
	  hEtaAll[nj]->Fill(refeta[gj],wxs*wcen*wvz);
	  hPhiAll[nj]->Fill(refphi[gj],wxs*wcen*wvz);
	  if(delr < kdRCut){
	    //! Numerator for reconstrunction efficiency
	    hPtSel [nj]->Fill(refpt[gj],wxs*wcen*wvz);
	    hEtaSel[nj]->Fill(refeta[gj],wxs*wcen*wvz);
	    hPhiSel[nj]->Fill(refphi[gj],wxs*wcen*wvz);

	    if( recopt > kptrecocut && refpt[gj] > 30){
	      //! Fake
	      hFakePtAll [nj]->Fill(recopt,wxs*wcen*wvz);
	      hFakeEtaAll[nj]->Fill(recoeta,wxs*wcen*wvz);
	      hFakePhiAll[nj]->Fill(recophi,wxs*wcen*wvz);

	      if( subid[gj] != 0 ){
		hFakePtSel [nj]->Fill(recopt,wxs*wcen*wvz);
		hFakeEtaSel[nj]->Fill(recoeta,wxs*wcen*wvz);
		hFakePhiSel[nj]->Fill(recophi,wxs*wcen*wvz);
	      }
	    }
	  }
	}

	if(subid[gj] != 0 || recopt < kptrecocut || recopt > 1000 || refpt[gj] < kptgencut)continue;


	njets[nj]++;


// 	if( (abs(corrfac - recopt/rawpt[gj]) > 0.2) || corrfac > 5 ){
// 	  cout << "refeta : " << refeta[gj] << " refpt : "  << refpt[gj] <<" rawpt : " << rawpt[gj] << " corrpt : " << recopt << " l2corrpt : "<< recopt_l2corr << " l3corrpt : " <<recopt_l3corr<<" l2corr : " << subcorr[0]  << " l3corr : " << subcorr[1] <<  " corr : " << corrfac << endl;
// 	  continue;
//	}

	double resp_corr =  recopt / refpt[gj];
	double resp_raw  =  rawpt[gj] / refpt[gj];
	double ratio     =  recopt / rawpt[gj];

	if( refpt[gj] > 35.0 ){
	  for (int idr=0;idr<25;idr++) {
	    double drcut = 0.0+idr*(0.25-0.00)/(25-1);
	    if (delr>drcut) continue;
	    hRspVsDeltaR[nj][idr]->Fill(resp_corr,wxs*wcen*wvz);
	  }
	}

	if(delr > kdRCut)continue;


	int iphi = GetPhiBin(refphi[gj]);
	int ieta = GetEtaBin(refeta[gj]);
	int ipt  = GetPtBin (refpt[gj]);


	//cout << "  eta : "  << refeta[gj] << "  " << ieta << " \t pt " <<  refpt[gj] << "  "<< ipt << endl;

	hgenpt_genm[nj]->Fill(refpt[gj],wxs*wcen*wvz);
	hrecopt_genm[nj]->Fill(recopt,wxs*wcen*wvz);
	hrawpt_genm[nj]->Fill(rawpt[gj],wxs*wcen*wvz);

	hjeteta[nj]->Fill(recoeta,wxs*wcen*wvz);
	hjetphi[nj]->Fill(recophi,wxs*wcen*wvz);

	hgeneta[nj]->Fill(refeta[gj],wxs*wcen*wvz);
	hgenphi[nj]->Fill(refphi[gj],wxs*wcen*wvz);

	//! Response in pt and eta
	if( ipt>=0 && ipt<nbins ){
	  havjetpt_genm [nj][ipt]->Fill(recopt,wxs*wcen*wvz);
	  havrawpt_genm [nj][ipt]->Fill(rawpt[gj],wxs*wcen*wvz);

	  hrescrpt_genm [nj][ipt]->Fill(resp_corr,wxs*wcen*wvz);
	  hresrrpt_genm [nj][ipt]->Fill(resp_raw ,wxs*wcen*wvz);
	  hratio        [nj][ipt]->Fill(ratio    ,wxs*wcen*wvz);

	  if( ieta>=0 && ieta<neta){
	    hrescrpt_genm_eta [nj][ipt][ieta]->Fill(resp_corr,wxs*wcen*wvz);
	    hresrrpt_genm_eta [nj][ipt][ieta]->Fill(resp_raw ,wxs*wcen*wvz);
	    hratio_eta        [nj][ipt][ieta]->Fill(ratio    ,wxs*wcen*wvz);
	  }

	  if( iphi>=0 && iphi<nphi){
	    hrescrpt_genm_phi [nj][ipt][iphi]->Fill(resp_corr,wxs*wcen*wvz);
	    hresrrpt_genm_phi [nj][ipt][iphi]->Fill(resp_raw ,wxs*wcen*wvz);
	    hratio_phi        [nj][ipt][iphi]->Fill(ratio    ,wxs*wcen*wvz);
	  }

	}
      }//! igen loop
      iEvent++;
      //std::cout<<"Completed event #  "<<ievt<<std::endl;
    }//! event loop ends
    delete parHI_l2;
    delete parHI_l3;
    delete _JEC_HI;

  }//! jet loop

  std::cout<<std::endl;
  for(int nj=0;nj<knj;nj++){
    std::cout<<calgo[nj] << std::endl;
    std::cout<<"\t # of events : "<< " Pbp " << "  " << nevt[nj] << "  " << njets[nj] << std::endl;
  }
  std::cout<<std::endl;

  //! Write to output file
  fout->cd();
  fout->Write();
  fout->Close();


  //! Check
  timer.Stop();
  double rtime  = timer.RealTime();
  double ctime  = timer.CpuTime();

  std::cout<<std::endl;
  std::cout<<Form("RealTime=%f seconds, CpuTime=%f seconds",rtime,ctime)<<std::endl;
  std::cout<<std::endl;
  std::cout<<"Good bye : " <<"\t"<<std::endl;
  return 1;
}

int GetEtaBin(float eta)
{
  for(int ix=0;ix<neta;ix++){
    if(eta>=etabins[ix] && eta<etabins[ix+1]){
      return ix;
    }
  }
  return -1;
}
int GetPhiBin(float phi)
{
  for(int ix=0;ix<nphi;ix++){
    if(phi>=phibins[ix] && phi<phibins[ix+1]){
      return ix;
    }
  }
  return -1;
}

int GetPtBin(float pt)
{
  for(int ix=0;ix<nbins;ix++){
    if(pt>=ptbins[ix] && pt<ptbins[ix+1]){
      return ix;
    }
  }
  return -1;
}
double delphi(double phi1, double phi2)
{
  double dphi = phi2 - phi1;
  dphi = fabs(atan2(sin(dphi),cos(dphi)));
  return dphi;
}

int main(int argc, char **argv)
{
  CalJec("Pbp");
  return 0;
}
