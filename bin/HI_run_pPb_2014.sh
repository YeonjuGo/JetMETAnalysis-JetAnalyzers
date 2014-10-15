#HI_weight_pPb.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat15_5020GeV.root" "test/pho_pPb15.root" 30 199048.0 
#HI_weight_pPb.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat30_5020GeV.root" "test/pho_pPb30.root" 50 12900.0
#HI_weight_pPb.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat50_5020GeV.root" "test/pho_pPb50.root" 80 1467.0
#HI_weight_pPb.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat80_5020GeV.root" "test/pho_pPb80.root" 120 145.0
#HI_weight_pPb.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat120_5020GeV.root" "test/pho_pPb120.root" 170 13.0
#HI_weight_pPb.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat170_5020GeV.root" "test/pho_pPb170.root" 9999 2.0

#HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat15_5020GeV.root" "test/leadingpho_pPb15.root" 30 199048.0
#HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat30_5020GeV.root" "test/leadingpho_pPb30.root" 50 12900.0
#HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat50_5020GeV.root" "test/leadingpho_pPb50.root" 80 1467.0
#HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat80_5020GeV.root" "test/leadingpho_pPb80.root" 120 145.0
#HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat120_5020GeV.root" "test/leadingpho_pPb120.root" 170 13.0
#HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_MC_5020GeV/pp_pPbstyle_MC_AllQCDPhotons_PtHat170_5020GeV.root" "test/leadingpho_pPb170.root" 9999 2.0

HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_JEC_5020GeV/pp_pPbstyle_JEC_AllQCDPhotons_PtHat15_5020GeV.root" "test/leadingpho_pPb15_v7.root" 30 199048.0
HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_JEC_5020GeV/pp_pPbstyle_JEC_AllQCDPhotons_PtHat30_5020GeV.root" "test/leadingpho_pPb30_v7.root" 50 12900.0
HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_JEC_5020GeV/pp_pPbstyle_JEC_AllQCDPhotons_PtHat50_5020GeV.root" "test/leadingpho_pPb50_v7.root" 80 1467.0
HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_JEC_5020GeV/pp_pPbstyle_JEC_AllQCDPhotons_PtHat80_5020GeV.root" "test/leadingpho_pPb80_v7.root" 120 145.0
HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_JEC_5020GeV/pp_pPbstyle_JEC_AllQCDPhotons_PtHat120_5020GeV.root" "test/leadingpho_pPb120_v7.root" 170 13.0
HI_weight_pPb_leadingPho.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_pPbstyle_JEC_5020GeV/pp_pPbstyle_JEC_AllQCDPhotons_PtHat170_5020GeV.root" "test/leadingpho_pPb170_v7.root" 9999 2.0

list=`echo ./test/leadingpho_pPb*_v7.root`
hadd leading_gammajet_pPb_bacJEC_mergedpthatbins_test_MC_v7.root $list
