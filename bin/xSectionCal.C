#include "TROOT.h"
#include "TString.h"
#include <iostream>
#include "TFile.h"
#include "TSystem.h"
#include "TPad.h"
#include "TH1D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include <stdlib.h>
using namespace std;

void xSectionCal(const char *ksp="pp"){
    const int nFile = 5;

    /* 
    //pp    
    const char *fileName[nFile] = {
        "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat15_2760GeV.root",
        "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat30_2760GeV.root",
        "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat50_2760GeV.root",
        "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat80_2760GeV.root",
        "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat120_2760GeV.root",
        "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat170_2760GeV.root"};
  */  
    // pPb
    const char *fileName[nFile] = {
	    "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pPb_JEC/merging-forest/pPbAllQCD15/JEC_pPbAllQCD15.root",        
	    "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pPb_JEC/merging-forest/pPbAllQCD30/JEC_pPbAllQCD30.root",        
	    "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pPb_JEC/merging-forest/pPbAllQCD50/JEC_pPbAllQCD50.root",        
	    "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pPb_JEC/merging-forest/pPbAllQCD80/JEC_pPbAllQCD80.root",        
	    "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pPb_JEC/merging-forest/pPbAllQCD120/JEC_pPbAllQCD120.root"        
    };


    TFile *fin[nFile];
    TTree *jetTree[nFile];
    float pEnt[nFile][nFile];
    float totalEnt[nFile];
    for(int i=0; i<nFile ; i++){
        totalEnt[i]=0.0;
        for(int j=0; j<nFile ; j++){
            pEnt[i][j]=0.0;
        }
    }

    for(int ifile=0; ifile<nFile; ifile++){
        fin[ifile] = new TFile(fileName[ifile]);
        jetTree[ifile] = (TTree*) fin[ifile] -> Get("akPu3PFJetAnalyzer/t");
        Float_t pthat;
        TBranch *b_pthat; 
        jetTree[ifile]->SetBranchAddress("pthat",&pthat, &b_pthat);
        totalEnt[ifile] = jetTree[ifile] -> GetEntries();
        pEnt[ifile][0] = jetTree[ifile] -> GetEntries("pthat>=15 && pthat<30");
        pEnt[ifile][1] = jetTree[ifile] -> GetEntries("pthat>=30 && pthat<50");
        pEnt[ifile][2] = jetTree[ifile] -> GetEntries("pthat>=50 && pthat<80");
        pEnt[ifile][3] = jetTree[ifile] -> GetEntries("pthat>=80 && pthat<120");
        pEnt[ifile][4] = jetTree[ifile] -> GetEntries("pthat>=120 && pthat<9999");
       // pEnt[ifile][5] = jetTree[ifile] -> GetEntries("pthat>=170 && pthat<9999");
        cout << jetTree[ifile] << ", : " << pEnt[ifile][0] << ", " << pEnt[ifile][1] <<  ", " << pEnt[ifile][2] <<  ", " << pEnt[ifile][3] <<  ", " << pEnt[ifile][4] <<  ", " << ", total Entries = " << totalEnt[ifile] << endl;
    }

    //
    // Calculate weighting factor
    //
    double weight[nFile];
    for(int ipart=0; ipart<nFile; ipart++){
        weight[ipart] = (pEnt[0][ipart])/(pEnt[0][ipart]+pEnt[1][ipart]+pEnt[2][ipart]+pEnt[3][ipart]+pEnt[4][ipart]+pEnt[5][ipart]);
        cout << ipart << "th partition weight : " << weight[ipart] << endl;
    }

	cout << "devide the range of pthat15 and each entries : " << endl;
	cout << "pthat 15 - 30 : " << pEnt[0][0]+pEnt[0][1]+pEnt[0][2]+pEnt[0][3]+pEnt[0][4] << endl;
	cout << "pthat 30 - 50 : " << pEnt[0][1]+pEnt[0][2]+pEnt[0][3]+pEnt[0][4]  << endl;
	cout << "pthat 50 - 80 : " << pEnt[0][2]+pEnt[0][3]+pEnt[0][4]  << endl;
	cout << "pthat 80 - 120 : " << pEnt[0][3]+pEnt[0][4] << endl;
	cout << "pthat 120 - 9999 : " << pEnt[0][4] << endl;

    TH1D *hpthat[nFile];
    for(int ifile=0; ifile<nFile; ifile++){
        hpthat[ifile] = new TH1D(Form("hpthat%d",ifile),"", 210, 10, 1000);
        jetTree[ifile]-> SetWeight(weight[ifile]);
        jetTree[ifile]-> Draw("pthat>>+hpthat[ifile]");
        hpthat[ifile] = (TH1D*)gDirectory->Get("hpthat[ifile]");
        // hpthat = (TH1F*)gPad->GetPrimitive("hpthat[ifile]");
    }
    /*
    TCanvas *can = new TCanvas("can", "can", 300,300);

    for(int ifile=0; ifile<nFile; ifile++){
        if(ifile==0) hpthat[0] -> Draw();
        else  hpthat[ifile] -> Draw("same");
        cout << hpthat[ifile] -> GetBinContent(20) << endl; 
    }
*/
}
