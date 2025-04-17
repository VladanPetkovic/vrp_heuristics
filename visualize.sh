#!/bin/bash

dir_augerat="augerat_1995_set_a"
dir_christofides="christofides_et_al_1979_cmt"
dir_uchoa="uchoa_et_al_2014"
dir_visualization="visualization"
dir_solution="solution"

##########################
# algorithms
#algorithms=('nearest_neighbor' 'savings_clark_wright' 'lambda_opt_nn' 'lambda_opt_savings')
algorithms=('lambda_interchange_savings' 'lambda_opt_nn' 'lambda_opt_savings')

##########################

cd "test_data"
# run visualization for all data (ignoring large data)
for dir in "$dir_augerat" "$dir_christofides"; do
    for algorithm in "${algorithms[@]}"; do
        # create subdirectory for algorithm and data set
        mkdir -p "../$dir_visualization/$algorithm/$dir"
        dir_temp_solution="../$dir_solution/$algorithm/$dir"

        for file in "$dir"/*.xml; do
            echo "Running for file: $file with algorithm: $algorithm"

            filename=$(basename -- "$file")
            filename_no_ext="${filename%.xml}"

            output_file="../$dir_visualization/$algorithm/$dir/$filename_no_ext.png"
            solution_file="$dir_temp_solution/$filename"
            echo "Saving to: $output_file"

            /usr/bin/python3.10 ../data_analysis/main_visualize.py "$file" "$output_file" --solution_file "$solution_file"
            echo /usr/bin/python3.10 ../data_analysis/main_visualize.py "$file" "$output_file" --solution_file "$solution_file"
        done
    done
done
