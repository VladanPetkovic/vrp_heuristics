#!/bin/bash

dir_augerat="augerat_1995_set_a"
dir_christofides="christofides_et_al_1979_cmt"
dir_uchoa="uchoa_et_al_2014"
dir_solution="solution"

##########################
# algorithms
algorithms=('nearest_neighbor' 'savings_clark_wright') # add additional separating with space


##########################

cd "test_data"
# run solver for different test-data
for dir in "$dir_augerat" "$dir_christofides" "$dir_uchoa"; do
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