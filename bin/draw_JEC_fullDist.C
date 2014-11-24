//Author : Yeonju Go

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TLine.h"
#include "stdio.h"
#include <iostream>

//! pt binning
double ptbins[] ={10,15,20,27,35,45,57,72,90,120,150,200,300,400,550,750,1000};
const int npt = sizeof(ptbins)/sizeof(double) - 1;

const double etabins[]={-3.0,-2.4,-1.8,-1.4,-1.0,-0.8,-0.6,-0.4,-0.2,
	0.0,0.2,0.4,0.6,0.8,1.0,1.4,1.8,2.4,3.0};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.700,-2.100,-1.500,-0.900,-0.300,
	0.300,0.900,1.500,2.100,2.700,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

//for 2013 HiWinter pPb
const int kAlgos = 12; 
const char *calgo[kAlgos] = {"ak3PF","ak4PF","ak5PF","ak3Calo","ak4Calo","ak5Calo",
                     "akPu3PF","akPu4PF","akPu5PF","akPu3Calo","akPu4Calo","akPu5Calo"
};

//for 2014 private PbPb
/*
const int kAlgos = 24; 
const char *calgo[kAlgos] = {"ak2PF","ak3PF","ak4PF","ak5PF","ak2Calo","ak3Calo","ak4Calo","ak5Calo",
	"akPu2PF","akPu3PF","akPu4PF","akPu5PF","akPu2Calo","akPu3Calo","akPu4Calo","akPu5Calo",
	"akVs2PF","akVs3PF","akVs4PF","akVs5PF","akVs2Calo","akVs3Calo","akVs4Calo","akVs5Calo"};
*/

//string corrFileName[kAlgos]= {"AK1PF","AK2PF","AK3PF","AK4PF","AK5PF","AK6PF","AK7PF","AK1Calo","AK2Calo","AK3Calo","AK4Calo","AK5Calo","AK6Calo","AK7Calo",
//"AKPu1PF","AKPu2PF","AKPu3PF","AKPu4PF","AKPu5PF","AKPu6PF","AKPu7PF","AKPu1Calo","AKPu2Calo","AKPu3Calo","AKPu4Calo","AKPu5Calo","AKPu6Calo","AKPu7Calo",
//                  "AK1PF","AK2PF","AK3PF","AK4PF","AK5PF","AK6PF","AK7PF","AK1Calo","AK2Calo","AK3Calo","AK4Calo","AK5Calo","AK6Calo","AK7Calo",
//                                    "AKVs1PF","AKVs2PF","AKVs3PF","AKVs4PF","AKVs5PF","AKVs6PF","AKVs7PF","AKVs1Calo","AKVs2Calo","AKVs3Calo","AKVs4Calo","AKVs5Calo","AKVs6Calo","AKVs7Calo"
//                                    };
//



void draw_JEC_fullDist(){
	TH1::SetDefaultSumw2();
	const int np = 11;
	//TFile* fin = new TFile("afterJEC_output_v1.root");
	//TFile* fin = new TFile("afterJEC_output_v3_nonPuJEC.root");
	TFile* fin = new TFile("afterJEC_output_v3.root");
	gStyle -> SetOptStat(0);
	
	// raw/gen pt dep.
	TH1D* hresrrpt_genm[kAlgos][npt];
	// reco/gen pt dep.
	TH1D* hrescrpt_genm[kAlgos][npt];
	// reco/gen eta dep.
	TH1D* hrescrpt_genm_eta[kAlgos][npt][neta];
	// reco/gen phi dep.
	TH1D* hrescrpt_genm_phi[kAlgos][npt][nphi];

	TCanvas* c_fullDist[kAlgos];
	
	// get reco/gen value for each pt bin.
	for(int nj=0; nj<kAlgos; nj++){ //for each algorithm,
		c_fullDist[nj] = new TCanvas(Form("c_fullDist%d",nj),"",1000,1000);
		c_fullDist[nj] -> Divide(4,4);
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			c_fullDist[nj] -> cd(ip+1);
			//hresrrpt_genm[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hresrrpt_genm%d_%d", calgo[nj], nj, ip)); 
			hrescrpt_genm[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm%d_%d", calgo[nj], nj, ip)); 
			hrescrpt_genm[nj][ip] -> Draw();
	/*		for(int ieta=0; ieta<neta; ieta++){	
				hrescrpt_genm_eta[nj][ip][ieta] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm_eta%d_%d_%d", calgo[nj], nj, ip, ieta)); 
			}
			for(int iphi=0; iphi<nphi; iphi++){	
				hrescrpt_genm_phi[nj][ip][iphi] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm_phi%d_%d_%d", calgo[nj], nj, ip, iphi)); 
			}*/
		}
	}
}
