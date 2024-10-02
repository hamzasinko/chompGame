#!/bin/bash

# Function to verify that APT is the package manager
function check_apt {
    if ! [ -x "$(command -v apt)" ]; then
        echo "This script is designed for APT package manager. Please adapt it to your package manager."
        exit 1
    fi
}

# Function to install lcov if not installed
function install_lcov {
    if ! [ -x "$(command -v lcov)" ]; then
        check_apt
        sudo apt install lcov
    fi
}

# Compilation avec les options de couverture,
gcc -fprofile-arcs -ftest-coverage -o test_executable main.test.c ./headers/interaction.c ./headers/traitement.c ./headers/ai.c ./headers/aiV1.c ./headers/matrice.c ./headers/network.c ./tests/traitement.test.c ./tests/matrice.test.c ./tests/interaction.test.c tests/network.test.c 2> gcc_errors.log

# Exécution des tests
./test_executable

# Check if lcov is installed
install_lcov

# Capture des données de couverture avec LCOV
lcov --capture --directory . --output-file lcov.info

# Générer le rapport HTML
genhtml lcov.info --output-directory out

# Ouvrir le rapport HTML dans un navigateur
# www-browser out/index.html
firefox out/index.html
