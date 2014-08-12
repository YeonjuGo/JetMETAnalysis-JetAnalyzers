HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat15_2760GeV.root" "test/pho_pp15.root" 30 2.034e-01
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat30_2760GeV.root" "test/pho_pp30.root" 50 2.034e-01
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat50_2760GeV.root" "test/pho_pp50.root" 80 2.034e-01
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat80_2760GeV.root" "test/pho_pp80.root" 120 2.034e-01
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat120_2760GeV.root" "test/pho_pp120.root" 170 2.034e-01
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat170_2760GeV.root" "test/pho_pp170.root" 9999 2.034e-01

list=`echo ./test/pho_pp*.root`
hadd gammajet_pp_bacJEC_mergedpthatbins_test_MC.root $list
