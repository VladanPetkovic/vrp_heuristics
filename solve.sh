#!/bin/bash

dir_augerat="augerat_1995_set_a"
dir_christofides="christofides_et_al_1979_cmt"
dir_uchoa="uchoa_et_al_2014"
dir_solution="solution"

performance_file_path="test_data/performance.csv"
dir_output="$dir_solution/stats"

##########################
# algorithms
#algorithms=('nearest_neighbor' 'savings_clark_wright' 'nn_lambda_opt' 'savings_lambda_opt' 'nn_improvement' 'savings_improvement' 'iterated_local_search')
algorithms=('savings_improvement' 'iterated_local_search')

##########################

cd "test_data"
# run solver for different test-data
#for dir in "$dir_augerat" "$dir_christofides" "$dir_uchoa"; do
for dir in "$dir_augerat" "$dir_christofides"; do
    for algorithm in "${algorithms[@]}"; do
        # create subdirectory for algorithm and data set
        mkdir -p "../$dir_solution/$algorithm/$dir"

        for file in "$dir"/*.xml; do
            echo "Running for file: $file with algorithm: $algorithm"

            output_file="../$dir_solution/$algorithm/$file"
            echo "Saving to: $output_file"

            ../vrp_solver/out/vrp_solver -i "$file" -o "$output_file" -a "$algorithm"
        done
    done
done

cd ".."
# run statistics afterwards
# REMEMBER TO COPY A NEW VERSION OF data_stats.csv IF NEEDED
echo /usr/bin/python3.10 data_analysis/main_analyze.py "$performance_file_path" "$dir_output"
/usr/bin/python3.10 data_analysis/main_analyze.py "$performance_file_path" "$dir_output"
