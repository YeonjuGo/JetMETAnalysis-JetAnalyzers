#! /bin/sh -f
echo "Running for gammajet only for one Algorithm........... "

jet_response_analyzer_x jra_lowpt.config -input merged_pPb_leadingpho_v1.root -useweight true -output response_oneAlgo.root -algs ak3CaloJetAnalyzer:0.3

jet_l3_correction_x -input response_oneAlgo.root -era JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20 -batch true -formats pdf -output l3_oneAlgo.root -algs ak3CaloJetAnalyzer
	
jet_l2_correction_x -input response_oneAlgo.root -l3input l3_oneAlgo.root -era JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20 -batch true -formats pdf -output l2_oneAlgo.root -algs ak3CaloJetAnalyzer

#    ak2PFJetAnalyzer ak3PFJetAnalyzer ak4PFJetAnalyzer ak5PFJetAnalyzer \
#    akVs2PFJetAnalyzer akVs3PFJetAnalyzer akVs4PFJetAnalyzer akVs5PFJetAnalyzer \
#    ak2CaloJetAnalyzer ak3CaloJetAnalyzer ak4CaloJetAnalyzer ak5CaloJetAnalyzer \
#    akVs2CaloJetAnalyzer akVs3CaloJetAnalyzer akVs4CaloJetAnalyzer akVs5CaloJetAnalyzer \
#    akPu2PFJetAnalyzer akPu3PFJetAnalyzer akPu4PFJetAnalyzer akPu5PFJetAnalyzer \
#    akPu2CaloJetAnalyzer akPu3CaloJetAnalyzer akPu4CaloJetAnalyzer akPu5CaloJetAnalyzer 

