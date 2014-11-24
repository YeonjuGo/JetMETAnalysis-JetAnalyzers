#! /bin/sh -f
echo "Running for gammajet........... "

# Generate the response
#jet_response_analyzer_x  jra_lowpt.config -input merged_pPb_leadingpho_v1.root -useweight true \
#   -output response.root \
#   -algs \
#    ak3CaloJetAnalyzer:0.3 ak3PFJetAnalyzer:0.3 \
#    ak4CaloJetAnalyzer:0.3 ak4PFJetAnalyzer:0.3 \
#    ak5CaloJetAnalyzer:0.3 ak5PFJetAnalyzer:0.3 \
#    akVs3CaloJetAnalyzer:0.3 akVs3PFJetAnalyzer:0.3 \
#    akVs4CaloJetAnalyzer:0.3 akVs4PFJetAnalyzer:0.3 \
#    akVs5CaloJetAnalyzer:0.3 akVs5PFJetAnalyzer:0.3 \
#    akPu3CaloJetAnalyzer:0.3 akPu3PFJetAnalyzer:0.3 \
#    akPu4CaloJetAnalyzer:0.3 akPu4PFJetAnalyzer:0.3 \
#    akPu5CaloJetAnalyzer:0.3 akPu5PFJetAnalyzer:0.3 \
#exit




# Get the l3 corrections
jet_l3_correction_x -input response.root -era JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20 -batch true -formats pdf \
    -output l3.root \
    -algs \
    ak3PFJetAnalyzer ak4PFJetAnalyzer ak5PFJetAnalyzer \
    akVs3PFJetAnalyzer akVs4PFJetAnalyzer akVs5PFJetAnalyzer \
    ak3CaloJetAnalyzer ak4CaloJetAnalyzer ak5CaloJetAnalyzer \
    akVs3CaloJetAnalyzer akVs4CaloJetAnalyzer akVs5CaloJetAnalyzer \
    akPu3PFJetAnalyzer akPu4PFJetAnalyzer akPu5PFJetAnalyzer \
    akPu3CaloJetAnalyzer akPu4CaloJetAnalyzer akPu5CaloJetAnalyzer 
#exit
#

# use the l3 output and response output to get l2 corrections
jet_l2_correction_x -input response.root -l3input l3.root -era JEC_gammajet_HiWinter13_STARTHI53_LV1_5_3_20 -batch true -formats pdf \
    -output l2.root \
    -algs \
    ak3PFJetAnalyzer ak4PFJetAnalyzer ak5PFJetAnalyzer \
    ak3CaloJetAnalyzer ak4CaloJetAnalyzer ak5CaloJetAnalyzer  \
    akVs3PFJetAnalyzer akVs4PFJetAnalyzer akVs5PFJetAnalyzer \
    akVs3CaloJetAnalyzer akVs4CaloJetAnalyzer akVs5CaloJetAnalyzer \
    akPu3PFJetAnalyzer akPu4PFJetAnalyzer akPu5PFJetAnalyzer \
    akPu3CaloJetAnalyzer akPu4CaloJetAnalyzer akPu5CaloJetAnalyzer 
