#!/bin/bash

# Define the program executable

OUTPUT_FILE="results_SSE.txt"

#!/bin/bash

# List of file patterns to loop through
file_patterns1=("10n_with_gemm.c" "20n_with_gemm.c" "40n_with_gemm.c" "80n_with_gemm.c" "160n_with_gemm.c" "320n_with_gemm.c")

# Loop over the file patterns
for file in "${file_patterns1[@]}"; do
    # Compile each file with gcc and use the corresponding output name
    gcc "$file" -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -pg -ggdb -march='skylake' -O3  -fopt-info-vec-optimized -msse -mno-avx -lm
    
    # Check if the compilation succeeded
    if [ $? -eq 0 ]; then
        echo "Compilation successful for $file"
    else
        echo "Compilation failed for $file"
    fi
    echo "Program execution Started."
    for ((input=1; input<=5; input++))
    do
        echo "Iteration with GEMM: $input" >> $OUTPUT_FILE 2>&1
        sudo likwid-memsweeper
        sudo likwid-perfctr -C S0:0 -g MEM_DP ./a.out >> $OUTPUT_FILE 2>&1
    done
    rm a.out
done


file_patterns2=("10n_without_gemm.c" "20n_without_gemm.c" "40n_without_gemm.c" "80n_without_gemm.c" "160n_without_gemm.c" "320n_without_gemm.c")

# Loop over the file patterns
for file in "${file_patterns2[@]}"; do
    # Compile each file with gcc and use the corresponding output name
    gcc "$file" -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -pg -ggdb -march='skylake' -O3  -fopt-info-vec-optimized -msse -mno-avx -lm
    
    # Check if the compilation succeeded
    if [ $? -eq 0 ]; then
        echo "Compilation successful for $file"
    else
        echo "Compilation failed for $file"
    fi
    echo "Program execution Started."
    for ((input=1; input<=5; input++))
    do
        echo "Iteration without GEMM: $input" >> $OUTPUT_FILE 2>&1
        sudo likwid-memsweeper
        sudo likwid-perfctr -C S0:0 -g MEM_DP ./a.out >> $OUTPUT_FILE 2>&1
    done
    rm a.out
done
