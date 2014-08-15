HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat15_2760GeV.root" "test/pho_pp15.root" 30 187760.0 
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat30_2760GeV.root" "test/pho_pp30.root" 50 10193.0
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat50_2760GeV.root" "test/pho_pp50.root" 80 977.0
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat80_2760GeV.root" "test/pho_pp80.root" 120 96.0
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat120_2760GeV.root" "test/pho_pp120.root" 170 10.0
HI_weight.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MC_2760GeV/pp_MC_AllQCDPhotons_PtHat170_2760GeV.root" "test/pho_pp170.root" 9999 1

list=`echo ./test/pho_pp*.root`
hadd gammajet_pp_bacJEC_mergedpthatbins_test_MC.root $list
