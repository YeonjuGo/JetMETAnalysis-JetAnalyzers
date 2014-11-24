//Author : Yeonju Go
//not completed
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



void compare_jetE_PU_nonPU(const int nj=0){
	TH1::SetDefaultSumw2();
	std::string inname="merged_pPb_leadingpho_v7.root";
	TFile* fin = new TFile(inname.c_str(),"r");
	
	TTree* tree = (TTree*) fin -> Get("ak3PFJetAnalyzer/t");
	TTree* Putree = (TTree*) fin -> Get("akPu3PFJetAnalyzer/t");
	//Putree -> SetAlias(
	tree -> AddFriend(Putree);

	tree -> Draw("Putree.t.rawpt:rawpt","rawpt<1000");
}

