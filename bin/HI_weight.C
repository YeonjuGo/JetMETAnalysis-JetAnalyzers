#include "TROOT.h"
#include "TString.h"
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include <stdlib.h>
using namespace std;

//! pp 2.76 TeV PYTHIA cross sections
const double xsec[12][3] ={{2.034e-01,15,30}, //! 15
			   {1.075e-02,30,50}, //! 30
			   {1.025e-03,50,80}, //! 50
			   {9.865e-05,80,120}, //! 80
			   {1.129e-05,120,170}, //! 120
			   {1.465e-06,170,220}, //! 170
			   {2.837e-07,220,280}, //! 220
			   {5.323e-08,280,370}, //! 280
			   {5.934e-09,370,460}, //! 370
			   {8.125e-10,460,540}, //! 460
			   {1.467e-10,540,9999}, //! 540
			   {0,9999,9999}
};

float GetXsec(float/*maxpthat*/);

int weight(const char *infile="/mnt/hadoop/cms/store/user/belt/Validations53X/Track8_Jet29_cut1/QCDpT15_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_1GeVcut_badJEC_forest.root",
	   const char *outfile="test_corr_MC.root",
	   float maxpthat=30.,
	   float xSection=1.075e-02
  )
{
  TFile *fin = TFile::Open(infile, "readonly");
  cout<<infile<<endl;

  cout<<endl;
  cout<<endl;
  fin->ls();
  cout<<endl;
  cout<<endl;

  const int ndir=42;

  string DirName[ndir]= {
//    "ak1CaloJetAnalyzer",
//    "ak1PFJetAnalyzer",
    "ak2CaloJetAnalyzer",
    "ak2PFJetAnalyzer",
    "ak3CaloJetAnalyzer",
    "ak3PFJetAnalyzer",
    "ak4CaloJetAnalyzer",
    "ak4PFJetAnalyzer",
    "ak5CaloJetAnalyzer",
    "ak5PFJetAnalyzer",
//    "ak6CaloJetAnalyzer",
//    "ak6PFJetAnalyzer",
//    "ak7CaloJetAnalyzer",
//    "ak7PFJetAnalyzer",
//
//    "akPu1CaloJetAnalyzer",
//    "akPu1PFJetAnalyzer",
    "akPu2CaloJetAnalyzer",
    "akPu2PFJetAnalyzer",
    "akPu3CaloJetAnalyzer",
    "akPu3PFJetAnalyzer",
    "akPu4CaloJetAnalyzer",
    "akPu4PFJetAnalyzer",
    "akPu5CaloJetAnalyzer",
    "akPu5PFJetAnalyzer",
//    "akPu6CaloJetAnalyzer",
//    "akPu6PFJetAnalyzer",
//    "akPu7CaloJetAnalyzer",
//    "akPu7PFJetAnalyzer",
//
//
//    "akVs1CaloJetAnalyzer",
//    "akVs1PFJetAnalyzer",
    "akVs2CaloJetAnalyzer",
    "akVs2PFJetAnalyzer",
    "akVs3CaloJetAnalyzer",
    "akVs3PFJetAnalyzer",
    "akVs4CaloJetAnalyzer",
    "akVs4PFJetAnalyzer",
    "akVs5CaloJetAnalyzer",
    "akVs5PFJetAnalyzer",
//    "akVs6CaloJetAnalyzer",
//    "akVs6PFJetAnalyzer",
//    "akVs7CaloJetAnalyzer",
//    "akVs7PFJetAnalyzer"
  };

  TFile *fout=new TFile(outfile,"RECREATE");

  TTree *tr_in=0, *tr_out=0;
  Int_t           hiBin;

  TTree *tr_ev = 0;
  tr_ev = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
  tr_ev->SetBranchAddress("hiBin",&hiBin);
  tr_ev->SetBranchStatus("*",0,0);
  tr_ev->SetBranchStatus("hiBin",1,0);

  for(Int_t idir=0;idir<ndir;idir++){

    cout <<"idir =" << idir <<" JetName ="<< DirName[idir].c_str() <<endl ;
    tr_in = (TTree*)fin->Get(Form("%s/t",DirName[idir].c_str()));

    float fentries = (float)tr_in->GetEntries();
    float weight = xSection/(fentries/1000.);
    //float weight = effec_xsec/(fentries/1000.);
    //weight=1;
    cout<<" weight "<<weight<<" \t " << tr_in->GetName() << " entries : " << fentries << endl;

    //Declaration of leaves types
    int   nref;
    float pthat;
    float corrpt[1000];
    float jtpt[1000];
    float rawpt[1000];
    float jteta[1000];
    float jtphi[1000];
    float jty[1000];
    float jtpu[1000];
    float neutralSum[1000];
    float chargedSum[1000];
    float photonSum[1000];
    float refpt[1000];
    float refeta[1000];
    float refphi[1000];
    float refdphijt[1000];
    float refdrjt[1000];
    float refparton_pt[1000];
    int refparton_flavor[1000];
    int subid[1000];

    tr_in->SetBranchAddress("nref",&nref);
    tr_in->SetBranchAddress("pthat",&pthat);
    tr_in->SetBranchAddress("rawpt",rawpt);
    tr_in->SetBranchAddress("jtpt",jtpt);
    tr_in->SetBranchAddress("jteta",jteta);
    tr_in->SetBranchAddress("jty",jty);
    tr_in->SetBranchAddress("jtphi",jtphi);
    tr_in->SetBranchAddress("jtpu",jtpu);
    tr_in->SetBranchAddress("neutralSum",neutralSum);
    tr_in->SetBranchAddress("chargedSum",chargedSum);
    tr_in->SetBranchAddress("photonSum",photonSum);
    tr_in->SetBranchAddress("refpt",refpt);
    tr_in->SetBranchAddress("refphi",refphi);
    tr_in->SetBranchAddress("refeta",refeta);
    tr_in->SetBranchAddress("refdphijt",refdphijt);
    tr_in->SetBranchAddress("refdrjt",refdrjt);
    tr_in->SetBranchAddress("refparton_pt",refparton_pt);
    tr_in->SetBranchAddress("refparton_flavor",refparton_flavor);
    tr_in->SetBranchAddress("subid",subid);
    cout<<"get jet trees!!! "<<endl;

    //! Add Friends to the TTree
    tr_in->AddFriend(tr_ev);

    fout->mkdir(DirName[idir].c_str());
    fout->cd(DirName[idir].c_str());

    tr_out = new TTree("t","Jet  Response Analyzer");
    tr_out->SetMaxTreeSize(4200000000);

    // Set output branch addresses.
    tr_out->Branch("hiBin",&hiBin,"hiBin/I");
    tr_out->Branch("nref",&nref,"nref/I");
    tr_out->Branch("pthat",&pthat,"pthat/F");
    tr_out->Branch("weight",&weight,"weight/F");
    tr_out->Branch("jtpt",jtpt,"jtpt[nref]/F");
    tr_out->Branch("rawpt",rawpt,"rawpt[nref]/F");
    tr_out->Branch("corrpt",corrpt,"corrpt[nref]/F");
    tr_out->Branch("jtpu",jtpu,"jtpu[nref]/F");
    tr_out->Branch("jteta",jteta,"jteta[nref]/F");
    tr_out->Branch("jty",jty,"jty[nref]/F");
    tr_out->Branch("jtphi",jtphi,"jtphi[nref]/F");
    tr_out->Branch("neutralSum",neutralSum,"neutralSum[nref]/F");
    tr_out->Branch("chargedSum",chargedSum,"chargedSum[nref]/F");
    tr_out->Branch("photonSum",photonSum,"photonSum[nref]/F");
    tr_out->Branch("refpt",refpt,"refpt[nref]/F");
    tr_out->Branch("refeta",refeta,"refeta[nref]/F");
    tr_out->Branch("refphi",refphi,"refphi[nref]/F");
    tr_out->Branch("refdphijt",refdphijt,"refdphijt[nref]/F");
    tr_out->Branch("refdrjt",refdrjt,"refdrjt[nref]/F");
    tr_out->Branch("refparton_pt",refparton_pt,"refparton_pt[nref]/F");
    tr_out->Branch("refparton_flavor",refparton_flavor,"refparton_flavor[nref]/I");
    tr_out->Branch("subid",subid,"subid[nref]/I");



    Long64_t nbytes = 0;
    for (Long64_t i=0; i<fentries;i++) {
      nbytes += tr_in->GetEntry(i);

      if(pthat > maxpthat)continue;

      //! jet loop
      for(int iref=0;iref<nref;iref++){


	corrpt[iref] = jtpt[iref];
	jtpt  [iref] = rawpt[iref];

      }

      tr_out->Fill();
    }

    tr_out->Write();

  }

  cout <<"finish the code!!"<<endl ;
  fout->Close();
  cout<<"XXXX"<<endl;

  return 0;
}
float GetXsec(float maxpt)
{
  float effxsec=0;
  for(int i=0; i<11; i++){
    //for(int i=0; i<10; i++){
    if(TMath::Abs(maxpt - xsec[i][2]) < 1e-08){
      //effxsec = xsec[i][0] - xsec[i+1][0];
      effxsec = xsec[i][0];
      return effxsec;
    }
  }
  return  1;
}

int main(int argc, char **argv)
{
  if(argc != 5)
  {
    std::cout << "Wrong number of arguments" << std::endl;
    return 1;
  } else {
    weight(argv[1],
	   argv[2],
	   atof(argv[3]),
	   atof(argv[4]));
  }
  return 0;
}
