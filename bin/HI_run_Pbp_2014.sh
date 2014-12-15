#HI_weight_Pbp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat15_5020GeV.root" "test/pho_Pbp15.root" 30 199048.0 
#HI_weight_Pbp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat30_5020GeV.root" "test/pho_Pbp30.root" 50 12900.0
#HI_weight_Pbp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat50_5020GeV.root" "test/pho_Pbp50.root" 80 1467.0
#HI_weight_Pbp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat80_5020GeV.root" "test/pho_Pbp80.root" 120 145.0
#HI_weight_Pbp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat120_5020GeV.root" "test/pho_Pbp120.root" 170 13.0
#HI_weight_Pbp.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat170_5020GeV.root" "test/pho_Pbp170.root" 9999 2.0

#HI_weight_Pbp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat15_5020GeV.root" "test/leadingpho_Pbp15.root" 30 199048.0
#HI_weight_Pbp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat30_5020GeV.root" "test/leadingpho_Pbp30.root" 50 12900.0
#HI_weight_Pbp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat50_5020GeV.root" "test/leadingpho_Pbp50.root" 80 1467.0
#HI_weight_Pbp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat80_5020GeV.root" "test/leadingpho_Pbp80.root" 120 145.0
#HI_weight_Pbp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat120_5020GeV.root" "test/leadingpho_Pbp120.root" 170 13.0
#HI_weight_Pbp_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Pbpstyle_MC_5020GeV/pp_Pbpstyle_MC_AllQCDPhotons_PtHat170_5020GeV.root" "test/leadingpho_Pbp170.root" 9999 2.0

HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/Pbp_JEC/merging-forest/PbpAllQCD15/JEC_PbpAllQCD15.root" "test/leadingpho_Pbp15_v1.root" 30 10200.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/Pbp_JEC/merging-forest/PbpAllQCD30/JEC_PbpAllQCD30.root" "test/leadingpho_Pbp30_v1.root" 50 5635.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/Pbp_JEC/merging-forest/PbpAllQCD50/JEC_PbpAllQCD50.root" "test/leadingpho_Pbp50_v1.root" 80 1658.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/Pbp_JEC/merging-forest/PbpAllQCD80/JEC_PbpAllQCD80.root" "test/leadingpho_Pbp80_v1.root" 120 385.0
HI_weight_pPb_leadingPho.exe "/u/user/goyeonju/PRODUCTION/CMSSW_5_3_20/src/Pbp_JEC/merging-forest/PbpAllQCD120/JEC_PbpAllQCD120.root" "test/leadingpho_Pbp120_v1.root" 9999 88.0

list=`echo ./test/leadingpho_Pbp*_v1.root`
hadd merged_Pbp_leadingpho_v1.root $list
