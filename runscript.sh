#!/bin/bash

# List of available Makefiles
MAKEFILES=(
    "Makefile.withGEMM_withAVX"
    "Makefile.withGEMM_withAVX_SSE4.2"
    "Makefile.withGEMM_withoutSIMD"
    "Makefile.withGEMM_withSSE4.2"
    "Makefile.withoutGEMM_withAVX"
    "Makefile.withoutGEMM_withAVX_SSE4.2"
    "Makefile.withoutGEMM_withoutSIMD"
    "Makefile.withoutGEMM_withSSE4.2"
)

# Function to display an alert message
display_alert() {
    echo "=================================================="
    echo "⚠️  ALERT: Ensure you have installed Likwid benchmarking tool before proceeding!"
    echo "   If not installed, run: sudo apt-get install likwid (Debian/Ubuntu)"
    echo "   For other distros, visit: https://github.com/RRZE-HPC/likwid"
    echo "=================================================="
}

# Function to display the menu
display_menu() {
    echo "====================================="
    echo "      NeuroProbe Build Menu          "
    echo "====================================="
    for i in "${!MAKEFILES[@]}"; do
        echo "$((i+1)). ${MAKEFILES[$i]}"
    done
    echo "0. Exit"
    echo "====================================="
}

# Function to build and execute the selected Makefile
build_and_execute() {
    local makefile=$1
    echo "====================================="
    echo "Compiling using $makefile..."
    echo "====================================="
    
    make clean -f "$makefile"
    make -f "$makefile"

    if [ ! -f "bin/neuroprobe" ]; then
        echo "❌ Error: Compilation failed! Exiting..."
        exit 1
    fi

    echo "====================================="
    echo "🚀 Running likwid-perfctr..."
    echo "====================================="
    sudo likwid-perfctr -C S0:0 -g MEM_DP bin/neuroprobe

    echo "====================================="
    echo "🧹 Running likwid-memsweeper..."
    echo "====================================="
    sudo likwid-memsweeper
}

# Main menu loop
while true; do
    display_alert  # Show the alert message
    display_menu  # Show the menu

    echo -n "Enter your choice (0-8): "
    read choice

    if [[ $choice -eq 0 ]]; then
        echo "Exiting..."
        exit 0
    elif [[ $choice -ge 1 && $choice -le 8 ]]; then
        build_and_execute "${MAKEFILES[$((choice-1))]}"
    else
        echo "❌ Invalid choice! Please enter a number between 0 and 8."
        sleep 2
    fi
done
