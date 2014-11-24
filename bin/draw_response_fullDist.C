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
#include "TPad.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>

//! pt binning
int ptbins[] ={10,15,20,27,35,45,57,72,90,120,150,200,300,400,550,750,1000};
const int npt = sizeof(ptbins)/sizeof(int) - 1;

double Avgptbins[] ={12.5,17.5,23.5,31,40,51,64.5,81,105,135,175,250,350,475,650,875}; 

const double etabins[]={-3.0,-2.4,-1.8,-1.4,-1.0,-0.8,-0.6,-0.4,-0.2,
	0.0,0.2,0.4,0.6,0.8,1.0,1.4,1.8,2.4,3.0};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.700,-2.100,-1.500,-0.900,-0.300,
	0.300,0.900,1.500,2.100,2.700,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

const int kAlgos = 12; 
const char *calgo[kAlgos] = {"ak3PF","ak4PF","ak5PF","ak3Calo","ak4Calo","ak5Calo",
	"akPu3PF","akPu4PF","akPu5PF","akPu3Calo","akPu4Calo","akPu5Calo"
};


void draw_response_fullDist(){
	const int np = 10;
	TH1::SetDefaultSumw2();
	gStyle->SetOptStat(0000);
	gStyle->SetPadTopMargin(0.01); 
	gStyle->SetPadBottomMargin(0.15); 
	gStyle->SetPadLeftMargin(0.1); 
	gStyle->SetPadRightMargin(0.05); 
	std::string inname="response_v1.root";
	TFile* fin = new TFile(inname.c_str(),"r");


	TH1D* RefPt[kAlgos][npt];	
	TH1D* RefPt_Barrel[kAlgos][npt];	
	TH1D* JetPt[kAlgos][npt];	
	TH1D* JetPt_Barrel[kAlgos][npt];	
	TH1D* RelRsp[kAlgos][npt];
	TH1D* RelRsp_Barrel[kAlgos][npt];
	TH1D* EtaRsp[kAlgos][npt];
	TH1D* PhiRsp[kAlgos][npt];
	const int cw = 1400;
	const int ch = 500;
//===============================================
// RefPt
//===============================================
	TCanvas* c_RefPt[kAlgos];
	for(int nj=0; nj<kAlgos; nj++){
		c_RefPt[nj] = new TCanvas(Form("c_RefPt%d",nj),Form("%sJetAnalyzer",calgo[nj]),cw,ch);
		c_RefPt[nj] -> Divide(5,2); 
	//	c_RefPt[nj] = new TCanvas(Form("c_RefPt%d",nj),Form("%sJetAnalyzer",calgo[nj]),980,570);
	//	c_RefPt[nj] -> Divide(4,3); 
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			c_RefPt[nj] -> cd(ip+1);
			cout << Form("%sJetAnalyzer/RefPt_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]) << endl;
			RefPt[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/RefPt_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]));
			cout << RefPt[nj][ip]<<" , " <<  ip << endl;
			RefPt[nj][ip] -> Draw();
			RefPt[nj][ip] -> SetLabelSize(0.06,"X");
			RefPt[nj][ip] -> SetLabelSize(0.05,"Y");
			RefPt[nj][ip] -> SetTitleOffset(1.1,"X");
			RefPt[nj][ip] -> SetTitleSize(0.06,"X");
		}
		c_RefPt[nj]->SaveAs(Form("pdf/%sJetAnalyzer_RefPt.pdf", calgo[nj]));
	}

//===============================================
// RefPt_Barrel
//===============================================
	TCanvas* c_RefPt_Barrel[kAlgos];
	for(int nj=0; nj<kAlgos; nj++){
		c_RefPt_Barrel[nj] = new TCanvas(Form("c_RefPt_Barrel%d",nj),Form("%sJetAnalyzer",calgo[nj]),cw,ch);
		c_RefPt_Barrel[nj] -> Divide(5,2); 
	//	c_RefPt_Barrel[nj] = new TCanvas(Form("c_RefPt_Barrel%d",nj),Form("%sJetAnalyzer",calgo[nj]),980,580);
	//	c_RefPt_Barrel[nj] -> Divide(4,3); 
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			c_RefPt_Barrel[nj] -> cd(ip+1);
			cout << Form("%sJetAnalyzer/RefPt_Barrel_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]) << endl;
			RefPt_Barrel[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/RefPt_Barrel_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]));
			cout << RefPt_Barrel[nj][ip]<<" , " <<  ip << endl;
			RefPt_Barrel[nj][ip] -> Draw();
			RefPt_Barrel[nj][ip] -> SetLabelSize(0.06,"X");
			RefPt_Barrel[nj][ip] -> SetLabelSize(0.05,"Y");
			RefPt_Barrel[nj][ip] -> SetTitleOffset(1.1,"X");
			RefPt_Barrel[nj][ip] -> SetTitleSize(0.06,"X");
		}
		c_RefPt_Barrel[nj]->SaveAs(Form("pdf/%sJetAnalyzer_RefPt_Barrel.pdf", calgo[nj]));
	}


//===============================================
// JetPt
//===============================================
	TCanvas* c_JetPt[kAlgos];
	for(int nj=0; nj<kAlgos; nj++){
		c_JetPt[nj] = new TCanvas(Form("c_JetPt%d",nj),Form("%sJetAnalyzer",calgo[nj]),cw,ch);
		c_JetPt[nj] -> Divide(5,2); 
	//	c_JetPt[nj] = new TCanvas(Form("c_JetPt%d",nj),Form("%sJetAnalyzer",calgo[nj]),980,580);
	//	c_JetPt[nj] -> Divide(4,3); 
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			c_JetPt[nj] -> cd(ip+1);
			cout << Form("%sJetAnalyzer/JetPt_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]) << endl;
			JetPt[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/JetPt_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]));
			cout << JetPt[nj][ip]<<" , " <<  ip << endl;
			JetPt[nj][ip] -> Draw();
			JetPt[nj][ip] -> SetLabelSize(0.06,"X");
			JetPt[nj][ip] -> SetLabelSize(0.05,"Y");
			JetPt[nj][ip] -> SetTitleOffset(1.1,"X");
			JetPt[nj][ip] -> SetTitleSize(0.06,"X");
		}
		c_JetPt[nj]->SaveAs(Form("pdf/%sJetAnalyzer_JetPt.pdf", calgo[nj]));
	}

//===============================================
// JetPt_Barrel
//===============================================
	TCanvas* c_JetPt_Barrel[kAlgos];
	for(int nj=0; nj<kAlgos; nj++){
		c_JetPt_Barrel[nj] = new TCanvas(Form("c_JetPt_Barrel%d",nj),Form("%sJetAnalyzer",calgo[nj]),cw,ch);
		c_JetPt_Barrel[nj] -> Divide(5,2); 
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			c_JetPt_Barrel[nj] -> cd(ip+1);
			cout << Form("%sJetAnalyzer/JetPt_Barrel_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]) << endl;
			JetPt_Barrel[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/JetPt_Barrel_RefPt%dto%d", calgo[nj], ptbins[ip], ptbins[ip+1]));
			cout << JetPt_Barrel[nj][ip]<<" , " <<  ip << endl;
			JetPt_Barrel[nj][ip] -> Draw();
			JetPt_Barrel[nj][ip] -> SetLabelSize(0.06,"X");
			JetPt_Barrel[nj][ip] -> SetLabelSize(0.05,"Y");
			JetPt_Barrel[nj][ip] -> SetTitleOffset(1.1,"X");
			JetPt_Barrel[nj][ip] -> SetTitleSize(0.06,"X");
		}
		c_JetPt_Barrel[nj]->SaveAs(Form("pdf/%sJetAnalyzer_JetPt_Barrel.pdf", calgo[nj]));
	}

}

