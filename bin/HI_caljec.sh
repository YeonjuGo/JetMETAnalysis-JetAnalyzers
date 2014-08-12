#! /bin/sh -f
echo "Running for gammajet........... "

# Generate the response
#jet_response_analyzer_x  jra_fine_binning_lowpt.config -input dijet_pbpb_bacJEC_mergedpthatbins_Track8_Jet29_MC.root -useweight true \
jet_response_analyzer_x  jra_lowpt.config -input gammajet_pp_bacJEC_mergedpthatbins_test_MC.root -useweight true \
   -output jra_hiF_ak_dijet_test_lowpt.root \
   -algs \
#    ak1CaloJetAnalyzer:0.3 ak1PFJetAnalyzer:0.3 \
    ak2CaloJetAnalyzer:0.3 ak2PFJetAnalyzer:0.3 \
    ak3CaloJetAnalyzer:0.3 ak3PFJetAnalyzer:0.3 \
    ak4CaloJetAnalyzer:0.3 ak4PFJetAnalyzer:0.3 \
    ak5CaloJetAnalyzer:0.3 ak5PFJetAnalyzer:0.3 \
#    ak6CaloJetAnalyzer:0.3 ak6PFJetAnalyzer:0.3 \
#    ak7CaloJetAnalyzer:0.3 ak7PFJetAnalyzer:0.3 \
#    akVs1CaloJetAnalyzer:0.3 akVs1PFJetAnalyzer:0.3 \
    akVs2CaloJetAnalyzer:0.3 akVs2PFJetAnalyzer:0.3 \
    akVs3CaloJetAnalyzer:0.3 akVs3PFJetAnalyzer:0.3 \
    akVs4CaloJetAnalyzer:0.3 akVs4PFJetAnalyzer:0.3 \
    akVs5CaloJetAnalyzer:0.3 akVs5PFJetAnalyzer:0.3 \
#    akVs6CaloJetAnalyzer:0.3 akVs6PFJetAnalyzer:0.3 \
#    akVs7CaloJetAnalyzer:0.3 akVs7PFJetAnalyzer:0.3 \
#    akPu1CaloJetAnalyzer:0.3 akPu1PFJetAnalyzer:0.3 \
    akPu2CaloJetAnalyzer:0.3 akPu2PFJetAnalyzer:0.3 \
    akPu3CaloJetAnalyzer:0.3 akPu3PFJetAnalyzer:0.3 \
    akPu4CaloJetAnalyzer:0.3 akPu4PFJetAnalyzer:0.3 \
    akPu5CaloJetAnalyzer:0.3 akPu5PFJetAnalyzer:0.3 \
#    akPu6CaloJetAnalyzer:0.3 akPu6PFJetAnalyzer:0.3 \
#    akPu7CaloJetAnalyzer:0.3 akPu7PFJetAnalyzer:0.3 
#exit




# Get the l3 corrections
#jet_l3_correction_x -input jra_hiF_ak_dijet_test_lowpt.root -era JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29 -batch true -formats pdf \
jet_l3_correction_x -input jra_hiF_ak_dijet_test_lowpt.root -era JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20 -batch true -formats pdf \
    -output jra_hiF_ak_l3_dijet_test_lowpt.root \
    -algs \
    ak2PFJetAnalyzer ak3PFJetAnalyzer ak4PFJetAnalyzer ak5PFJetAnalyzer \
    akVs2PFJetAnalyzer akVs3PFJetAnalyzer akVs4PFJetAnalyzer akVs5PFJetAnalyzer \
    ak2CaloJetAnalyzer ak3CaloJetAnalyzer ak4CaloJetAnalyzer ak5CaloJetAnalyzer \
    akVs2CaloJetAnalyzer akVs3CaloJetAnalyzer akVs4CaloJetAnalyzer akVs5CaloJetAnalyzer \
    akPu2PFJetAnalyzer akPu3PFJetAnalyzer akPu4PFJetAnalyzer akPu5PFJetAnalyzer \
    akPu2CaloJetAnalyzer akPu3CaloJetAnalyzer akPu4CaloJetAnalyzer akPu5CaloJetAnalyzer 
#exit
#

# use the l3 output and response output to get l2 corrections
#jet_l2_correction_x -input jra_hiF_ak_dijet_test_lowpt.root -l3input jra_hiF_ak_l3_dijet_test_lowpt.root -era JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29 -batch true -formats pdf \
jet_l2_correction_x -input jra_hiF_ak_dijet_test_lowpt.root -l3input jra_hiF_ak_l3_dijet_test_lowpt.root -era JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20 -batch true -formats pdf \
    -output jra_hiF_ak_l2_dijet_test_lowpt.root \
    -algs \
    ak2PFJetAnalyzer ak3PFJetAnalyzer ak4PFJetAnalyzer ak5PFJetAnalyzer \
    ak2CaloJetAnalyzer ak3CaloJetAnalyzer ak4CaloJetAnalyzer ak5CaloJetAnalyzer  \
    akVs2PFJetAnalyzer akVs3PFJetAnalyzer akVs4PFJetAnalyzer akVs5PFJetAnalyzer \
    akVs2CaloJetAnalyzer akVs3CaloJetAnalyzer akVs4CaloJetAnalyzer akVs5CaloJetAnalyzer \
    akPu2PFJetAnalyzer akPu3PFJetAnalyzer akPu4PFJetAnalyzer akPu5PFJetAnalyzer \
    akPu2CaloJetAnalyzer akPu3CaloJetAnalyzer akPu4CaloJetAnalyzer akPu5CaloJetAnalyzer 
