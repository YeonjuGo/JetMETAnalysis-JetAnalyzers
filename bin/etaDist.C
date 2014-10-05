//Author : Yeonju Go

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TLine.h"
#include "TH1D.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>

//! pt binning
double ptbins[] ={10,15,20,27,35,45,57,72,90,120,150,200,300,400,550,750,1000};
const int npt = sizeof(ptbins)/sizeof(double) - 1;

double Avgptbins[] ={12.5,17.5,23.5,31,40,51,64.5,81,105,135,175,250,350,475,650,875}; 

const double etabins[]={-3.0,-2.4,-1.8,-1.4,-1.0,-0.8,-0.6,-0.4,-0.2,
	0.0,0.2,0.4,0.6,0.8,1.0,1.4,1.8,2.4,3.0};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.700,-2.100,-1.500,-0.900,-0.300,
	0.300,0.900,1.500,2.100,2.700,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

//for 2013 HiWinter pPb
const int kAlgos = 1; 
const char *calgo[kAlgos] = {"ak3Calo"};
string corrFileName[kAlgos]= {"AK3Calo"};
/*
   const int kAlgos = 12; 
   const char *calgo[kAlgos] = {"ak3PF","ak4PF","ak5PF","ak3Calo","ak4Calo","ak5Calo",
   "akPu3PF","akPu4PF","akPu5PF","akPu3Calo","akPu4Calo","akPu5Calo"
   };
   string corrFileName[kAlgos]= {"AK3PF","AK4PF","AK5PF","AK3Calo","AK4Calo","AK5Calo",
   "AKPu3PF","AKPu4PF","AKPu5PF","AKPu3Calo","AKPu4Calo","AKPu5Calo"
   };
   */
const int nRadius = 3;
const int nAlgoGroup = 4;// akPF, akCalo, akPuPF, akPuCalo

//for 2014 private PbPb
/*
   const int kAlgos = 24; 
   const char *calgo[kAlgos] = {"ak2PF","ak3PF","ak4PF","ak5PF","ak2Calo","ak3Calo","ak4Calo","ak5Calo",
   "akPu2PF","akPu3PF","akPu4PF","akPu5PF","akPu2Calo","akPu3Calo","akPu4Calo","akPu5Calo",
   "akVs2PF","akVs3PF","akVs4PF","akVs5PF","akVs2Calo","akVs3Calo","akVs4Calo","akVs5Calo"};
   const int nRadius = 4;
   const int nAlgoGroup = 6; // akPF, akCalo, akPuPF, akPuCalo, akVsPF, akVsCalo
   */

//string corrFileName[kAlgos]= {"AK1PF","AK2PF","AK3PF","AK4PF","AK5PF","AK6PF","AK7PF","AK1Calo","AK2Calo","AK3Calo","AK4Calo","AK5Calo","AK6Calo","AK7Calo",
//"AKPu1PF","AKPu2PF","AKPu3PF","AKPu4PF","AKPu5PF","AKPu6PF","AKPu7PF","AKPu1Calo","AKPu2Calo","AKPu3Calo","AKPu4Calo","AKPu5Calo","AKPu6Calo","AKPu7Calo",
//                  "AK1PF","AK2PF","AK3PF","AK4PF","AK5PF","AK6PF","AK7PF","AK1Calo","AK2Calo","AK3Calo","AK4Calo","AK5Calo","AK6Calo","AK7Calo",
//                                    "AKVs1PF","AKVs2PF","AKVs3PF","AKVs4PF","AKVs5PF","AKVs6PF","AKVs7PF","AKVs1Calo","AKVs2Calo","AKVs3Calo","AKVs4Calo","AKVs5Calo","AKVs6Calo","AKVs7Calo"
//                                    };
//



void etaDist(const int nj=0){
	TH1::SetDefaultSumw2();
	std::string inname="jra_hiF_ak_dijet_test_lowpt.root";
	TFile* fin = new TFile(inname.c_str(),"r");
	
	// raw/gen eta dep
	cout << "ss" << endl;
	TH1D* RelRsp_JetEta[nj][neta];
	double RelRsp_JetEta_mean[nj][neta];
	double RelRsp_JetEta_meanErr[nj][neta];
	double RelRsp_JetEta_sigma[nj][neta];
	double RelRsp_JetEta_sigmaErr[nj][neta];

	TCanvas* c_detail_reco = new TCanvas("c_detail_reco", "c_detail_reco", 1200,900);
	c_detail_reco -> Divide(4,3);
	cout << "alshg" << endl;
	for(int ie=0;ie<neta;ie++){
		cout << "aa" << endl;
		RelRsp_JetEta[nj][ie] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/RelRsp_JetEta%dto%d", calgo[nj], ie, ie+1)); 
		cout << "aaaaaaaaaaaaaaa" << endl;
		RelRsp_JetEta_mean[nj][ie] = RelRsp_JetEta[nj][ie] -> GetMean(); 
	//	RelRsp_JetEta_meanErr[nj][ie] = RelRsp_JetEta[nj][ie] -> GetMeanError();
	//	RelRsp_JetEta_sigma[nj][ie] = RelRsp_JetEta[nj][ie] -> GetRMS();
//		RelRsp_JetEta_sigmaErr[nj][ie] = RelRsp_JetEta[nj][ie] -> GetRMSError();
		cout << "s" << endl;
		c_detail_reco -> cd(ie+1);
		RelRsp_JetEta[nj][ie]-> Draw(); 	
	}

	TH1D* all_RelRsp_JetEta[nj]; // raw/gen
	all_RelRsp_JetEta[nj] = new TH1D(Form("all_RelRsp_JetEta%d", nj), Form("(Raw/Gen) jet pt vs. eta for %s", calgo[nj]), neta, etabins);
	all_RelRsp_JetEta[nj] -> SetAxisRange(-3.0,3.0,"X"); 
	all_RelRsp_JetEta[nj] -> SetAxisRange(0.4,1.5,"Y"); 
	all_RelRsp_JetEta[nj] -> SetMarkerStyle(20); 
	cout << "sldgj" << endl;
	for(int ie=0;ie<neta;ie++){
		all_RelRsp_JetEta[kAlgos] ->  SetBinContent(ie+1, RelRsp_JetEta_mean[nj][ie]);  
	}

}

