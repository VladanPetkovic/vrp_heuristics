#!/bin/bash

dir="test_data/uchoa_et_al_2014"

for file in "$dir"/*.xml; do
    echo "Running for file: $file"
    python3 main.py "$file"
done
