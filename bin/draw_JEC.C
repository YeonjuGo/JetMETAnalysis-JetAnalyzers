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



void draw_JEC(){
	TH1::SetDefaultSumw2();
	const int np = 11;
	//TFile* fin = new TFile("afterJEC_output_v1.root");
	//TFile* fin = new TFile("afterJEC_output_v3_nonPuJEC.root");
	//TFile* fin = new TFile("afterJEC_output_Pbp.root");
	TFile* fin = new TFile("afterJEC_output_pp.root");
	gStyle -> SetOptStat(0);
	
	// raw/gen pt dep.
	TH1D* hresrrpt_genm[kAlgos][npt];
	// reco/gen pt dep.
	TH1D* hrescrpt_genm[kAlgos][npt];
	// reco/gen eta dep.
	TH1D* hrescrpt_genm_eta[kAlgos][npt][neta];
	// reco/gen phi dep.
	TH1D* hrescrpt_genm_phi[kAlgos][npt][nphi];

	// get reco/gen value for each pt bin.
	for(int nj=0; nj<kAlgos; nj++){ //for each algorithm,
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			hresrrpt_genm[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hresrrpt_genm%d_%d", calgo[nj], nj, ip)); 
			hrescrpt_genm[nj][ip] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm%d_%d", calgo[nj], nj, ip)); 
			for(int ieta=0; ieta<neta; ieta++){	
				hrescrpt_genm_eta[nj][ip][ieta] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm_eta%d_%d_%d", calgo[nj], nj, ip, ieta)); 
			}
			for(int iphi=0; iphi<nphi; iphi++){	
				hrescrpt_genm_phi[nj][ip][iphi] = (TH1D*) fin -> Get(Form("%sJetAnalyzer/hrescrpt_genm_phi%d_%d_%d", calgo[nj], nj, ip, iphi)); 
			}
		}
	}

	//assemble values into one histogram	
	TH1D* all_hresrrpt_genm[kAlgos]; // reaw/gen
	TH1D* all_hrescrpt_genm[kAlgos]; // reco/gen vs. gen pt
	TH1D* all_hrescrpt_genm_eta[kAlgos][npt]; // reco/gen vs. eta
	TH1D* all_hrescrpt_genm_phi[kAlgos][npt]; // reco/gen vs. phi

	TH1D* all_hresrrpt_genm_sigma[kAlgos]; // reaw/gen
	TH1D* all_hrescrpt_genm_sigma[kAlgos]; // reco/gen vs. gen pt
	TH1D* all_hrescrpt_genm_eta_sigma[kAlgos][npt]; // reco/gen vs. eta
	TH1D* all_hrescrpt_genm_phi_sigma[kAlgos][npt]; // reco/gen vs. phi
	for(int nj=0; nj<kAlgos; nj++){
		all_hresrrpt_genm[nj] = new TH1D(Form("all_hresrrpt_genm%d", nj), Form("(Raw/Gen) jet pt vs. gen pt for %s ; p_{T} (GeV); Raw p_{T}/Gen p_{T}", calgo[nj]), npt, ptbins);
		all_hresrrpt_genm[nj] -> SetAxisRange(10,ptbins[np-1],"X"); 
		all_hresrrpt_genm[nj] -> SetAxisRange(0.95,1.05,"Y"); 
		all_hresrrpt_genm[nj] -> SetMarkerStyle(20); 
		all_hresrrpt_genm_sigma[nj] = new TH1D(Form("all_hresrrpt_genm_sigma%d", nj), Form("Sigma of (Raw/Gen) jet pt vs. gen pt for %s ; p_{T} (GeV); sigma", calgo[nj]), npt, ptbins);
		all_hresrrpt_genm_sigma[nj] -> SetAxisRange(10,ptbins[np-1],"X"); 
		all_hresrrpt_genm_sigma[nj] -> SetAxisRange(0,0.5,"Y"); 
		all_hresrrpt_genm_sigma[nj] -> SetMarkerStyle(20); 

		all_hrescrpt_genm[nj] = new TH1D(Form("all_hrescrpt_genm%d", nj), Form("(Reco/Gen) jet pt vs. gen pt for %s ; p_{T} (GeV); Reco p_{T}/Gen p_{T}", calgo[nj]), npt, ptbins);
		all_hrescrpt_genm[nj] -> SetAxisRange(10,ptbins[np-1],"X"); 
		all_hrescrpt_genm[nj] -> SetAxisRange(0.95,1.05,"Y"); 
		all_hrescrpt_genm[nj] -> SetMarkerStyle(20); 
		all_hrescrpt_genm_sigma[nj] = new TH1D(Form("all_hrescrpt_genm_sigma%d", nj), Form("Sigma of (Reco/Gen) jet pt vs. gen pt for %s ; p_{T} (GeV); sigma", calgo[nj]), npt, ptbins);
		all_hrescrpt_genm_sigma[nj] -> SetAxisRange(10,ptbins[np-1],"X"); 
		all_hrescrpt_genm_sigma[nj] -> SetAxisRange(0,0.5,"Y"); 
		all_hrescrpt_genm_sigma[nj] -> SetMarkerStyle(20); 
		
		for(int ip=0; ip<np;ip++){ //for each pt bin.
			all_hrescrpt_genm_eta[nj][ip] = new TH1D(Form("all_hrescrpt_genm_eta%d_%d", nj, ip), Form("(Reco/Gen) jet pt vs. eta for %s;#eta;Reco p_{T}/Gen p_{T}", calgo[nj]), neta, etabins);
			//all_hrescrpt_genm_eta[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_eta[nj][ip] -> SetAxisRange(0.95,1.05,"Y"); 
			all_hrescrpt_genm_eta[nj][ip] -> SetMarkerStyle(20); 
			all_hrescrpt_genm_eta_sigma[nj][ip] = new TH1D(Form("all_hrescrpt_genm_eta_sigma%d_%d", nj, ip), Form("Sigma of (Reco/Gen) jet pt vs. eta for %s;#eta;sigma", calgo[nj]), neta, etabins);
			//all_hrescrpt_genm_eta_sigma[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_eta_sigma[nj][ip] -> SetAxisRange(0,0.5,"Y"); 
			all_hrescrpt_genm_eta_sigma[nj][ip] -> SetMarkerStyle(20); 

			all_hrescrpt_genm_phi[nj][ip] = new TH1D(Form("all_hrescrpt_genm_phi%d_%d", nj, ip), Form("(Reco/Gen) jet pt vs. phi for %s;#phi;Reco p_{T}/Gen p_{T}", calgo[nj]), nphi, phibins);
			//all_hrescrpt_genm[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_phi[nj][ip] -> SetAxisRange(0.95,1.05,"Y"); 
			all_hrescrpt_genm_phi[nj][ip] -> SetMarkerStyle(20); 
			all_hrescrpt_genm_phi_sigma[nj][ip] = new TH1D(Form("all_hrescrpt_genm_phi_sigma%d_%d", nj, ip), Form("Sigma of (Reco/Gen) jet pt vs. phi for %s;#phi;sigma", calgo[nj]), nphi, phibins);
			//all_hrescrpt_genm_phi_sigma[nj][ip] -> SetAxisRange(10,120,"X"); 
			all_hrescrpt_genm_phi_sigma[nj][ip] -> SetAxisRange(0,0.5,"Y"); 
			all_hrescrpt_genm_phi_sigma[nj][ip] -> SetMarkerStyle(20); 
		}
		
		for(int ip=0; ip<np;ip++){
			all_hresrrpt_genm[nj] -> SetBinContent(ip+1, hresrrpt_genm[nj][ip]->GetMean());	
			all_hresrrpt_genm[nj] -> SetBinError(ip+1,hresrrpt_genm[nj][ip] -> GetMeanError());
			all_hresrrpt_genm_sigma[nj] -> SetBinContent(ip+1, hresrrpt_genm[nj][ip]->GetRMS());	
			all_hresrrpt_genm_sigma[nj] -> SetBinError(ip+1, hresrrpt_genm[nj][ip]->GetRMSError());	
			
			all_hrescrpt_genm[nj] -> SetBinContent(ip+1, hrescrpt_genm[nj][ip]->GetMean());	
			all_hrescrpt_genm[nj] -> SetBinError(ip+1, hrescrpt_genm[nj][ip]-> GetMeanError());	
			all_hrescrpt_genm_sigma[nj] -> SetBinContent(ip+1, hrescrpt_genm[nj][ip]->GetRMS());	
			all_hrescrpt_genm_sigma[nj] -> SetBinError(ip+1, hrescrpt_genm[nj][ip]->GetRMSError());	

			for(int ieta=0; ieta<neta; ieta++){	
				all_hrescrpt_genm_eta[nj][ip] -> SetBinContent(ieta+1, hrescrpt_genm_eta[nj][ip][ieta]->GetMean());	
				all_hrescrpt_genm_eta[nj][ip] -> SetBinError(ieta+1, hrescrpt_genm_eta[nj][ip][ieta]->GetMeanError());	
				all_hrescrpt_genm_eta_sigma[nj][ip] -> SetBinContent(ieta+1, hrescrpt_genm_eta[nj][ip][ieta]->GetRMS());	
				all_hrescrpt_genm_eta_sigma[nj][ip] -> SetBinError(ieta+1, hrescrpt_genm_eta[nj][ip][ieta]->GetRMSError());	
			}	

			for(int iphi=0; iphi<nphi; iphi++){
				all_hrescrpt_genm_phi[nj][ip] -> SetBinContent(iphi+1, hrescrpt_genm_phi[nj][ip][iphi]->GetMean());	
				all_hrescrpt_genm_phi[nj][ip] -> SetBinError(iphi+1, hrescrpt_genm_phi[nj][ip][iphi]->GetMeanError());	
				all_hrescrpt_genm_phi_sigma[nj][ip] -> SetBinContent(iphi+1, hrescrpt_genm_phi[nj][ip][iphi]->GetRMS());	
				all_hrescrpt_genm_phi_sigma[nj][ip] -> SetBinError(iphi+1, hrescrpt_genm_phi[nj][ip][iphi]->GetRMSError());
			}
		}
	}

	TLine* t1 = new TLine(ptbins[0],1.01,ptbins[np],1.01);
	t1->SetLineWidth(1);
	t1->SetLineStyle(7); // 7 is jumSun , 1 is onSun
	t1->SetLineColor(1); // 2 is red

	TLine* t2 = new TLine(ptbins[0],0.99,ptbins[np],0.99);
	t2->SetLineWidth(1);
	t2->SetLineStyle(7); // 7 is jumSun , 1 is onSun
	t2->SetLineColor(1); // 2 is red

	TLine* t3 = new TLine(30,0.95,30,1.05);
	t3->SetLineWidth(1.5);
	t3->SetLineStyle(7); // 7 is jumSun , 1 is onSun
	t3->SetLineColor(2); // 2 is red


	TCanvas* cPF = new TCanvas("cPF", "cPF",900,600);
	cPF -> Divide(3,2);

	for(int nj=0; nj<3; nj++){//ak3PF, ak4PF, ak5PF
		cPF -> cd(nj+1);
		all_hrescrpt_genm[nj] -> Draw("pl");
		all_hrescrpt_genm[nj] -> SetMarkerSize(0.5);
		t1 -> Draw();
		t2 -> Draw();
		t3 -> Draw();
		
		cPF -> cd(nj+4);
		all_hrescrpt_genm_sigma[nj] -> Draw("pl");
		all_hrescrpt_genm_sigma[nj] -> SetMarkerSize(0.5);
	
	}
	cPF -> SaveAs("pdf/closureJEC_PF.pdf");

	TCanvas* cCalo = new TCanvas("cCalo", "cCalo",900,600);
	cCalo -> Divide(3,2);

	for(int nj=3; nj<6; nj++){//ak3Calo, ak4Calo, ak5Calo
		cCalo -> cd(nj+1-3);
		all_hrescrpt_genm[nj] -> Draw("pl");
		all_hrescrpt_genm[nj] -> SetMarkerSize(0.5);
		t1 -> Draw();
		t2 -> Draw();
		t3 -> Draw();
		
		cCalo -> cd(nj+4-3);
		all_hrescrpt_genm_sigma[nj] -> Draw("pl");
		all_hrescrpt_genm_sigma[nj] -> SetMarkerSize(0.5);
	
	}
	cCalo -> SaveAs("pdf/closureJEC_Calo.pdf");

	TCanvas* cPuPF = new TCanvas("cPuPF", "cPuPF",900,600);
	cPuPF -> Divide(3,2);

	for(int nj=6; nj<9; nj++){//akPu3PF, akPu4PF, akPu5PF
		cPuPF -> cd(nj+1-6);
		all_hrescrpt_genm[nj] -> Draw("pl");
		all_hrescrpt_genm[nj] -> SetMarkerSize(0.5);
		t1 -> Draw();
		t2 -> Draw();
		t3 -> Draw();
		
		cPuPF -> cd(nj+4-6);
		all_hrescrpt_genm_sigma[nj] -> Draw("pl");
		all_hrescrpt_genm_sigma[nj] -> SetMarkerSize(0.5);
	
	}
	cPuPF -> SaveAs("pdf/closureJEC_PuPF.pdf");
	
	TCanvas* cPuCalo = new TCanvas("cPuCalo", "cPuCalo",900,600);
	cPuCalo -> Divide(3,2);

	for(int nj=9; nj<12; nj++){//akPu3Calo, akPu4Calo, akPu5Calo
		cPuCalo -> cd(nj+1-9);
		all_hrescrpt_genm[nj] -> Draw("pl");
		all_hrescrpt_genm[nj] -> SetMarkerSize(0.5);
		t1 -> Draw();
		t2 -> Draw();
		t3 -> Draw();
		
		cPuCalo -> cd(nj+4-9);
		all_hrescrpt_genm_sigma[nj] -> Draw("pl");
		all_hrescrpt_genm_sigma[nj] -> SetMarkerSize(0.5);
	
	}
	cPuCalo -> SaveAs("pdf/closureJEC_PuCalo.pdf");
}
