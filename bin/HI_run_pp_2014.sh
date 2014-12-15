#HI_weight_pp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat15_5020GeV.root" "test/pho_pp15.root" 30 199048.0 
#HI_weight_pp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat30_5020GeV.root" "test/pho_pp30.root" 50 12900.0
#HI_weight_pp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat50_5020GeV.root" "test/pho_pp50.root" 80 1467.0
#HI_weight_pp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat80_5020GeV.root" "test/pho_pp80.root" 120 145.0
#HI_weight_pp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat120_5020GeV.root" "test/pho_pp120.root" 170 13.0
#HI_weight_pp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat170_5020GeV.root" "test/pho_pp170.root" 9999 2.0

#HI_weight_pp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat15_5020GeV.root" "test/leadingpho_pp15.root" 30 199048.0
#HI_weight_pp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat30_5020GeV.root" "test/leadingpho_pp30.root" 50 12900.0
#HI_weight_pp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat50_5020GeV.root" "test/leadingpho_pp50.root" 80 1467.0
#HI_weight_pp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat80_5020GeV.root" "test/leadingpho_pp80.root" 120 145.0
#HI_weight_pp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat120_5020GeV.root" "test/leadingpho_pp120.root" 170 13.0
#HI_weight_pp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_ppstyle_MC_5020GeV/pp_ppstyle_MC_AllQCDPhotons_PtHat170_5020GeV.root" "test/leadingpho_pp170.root" 9999 2.0

HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pp_JEC/merging-forest/ppAllQCD15/JEC_ppAllQCD15.root" "test/leadingpho_pp15_v1.root" 30 5900.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pp_JEC/merging-forest/ppAllQCD30/JEC_ppAllQCD30.root" "test/leadingpho_pp30_v1.root" 50 3073.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pp_JEC/merging-forest/ppAllQCD50/JEC_ppAllQCD50.root" "test/leadingpho_pp50_v1.root" 80 710.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pp_JEC/merging-forest/ppAllQCD80/JEC_ppAllQCD80.root" "test/leadingpho_pp80_v1.root" 120 126.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/pp_JEC/merging-forest/ppAllQCD120/JEC_ppAllQCD120.root" "test/leadingpho_pp120_v1.root" 9999 22.0

list=`echo ./test/leadingpho_pp*_v1.root`
hadd merged_pp_leadingpho_v1.root $list
