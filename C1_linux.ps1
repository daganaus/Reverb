#!/bin/bash

# --- SCRIPT DE COMPILATION AVEC CMAKE POUR LINUX ---

# Définir le chemin du répertoire de build
BUILD_PATH="$HOME/TP/juce_template-main/build"

# Créer le dossier de build s'il n'existe pas
if [ ! -d "$BUILD_PATH" ]; then
    mkdir -p "$BUILD_PATH"
fi

# Se déplacer dans ce nouveau répertoire
cd "$BUILD_PATH" || exit

# Définir la variable d'environnement pour JUCE_DIR
export JUCE_DIR="$HOME/TP/JUCE-master/build/JUCE"

# Générer les fichiers Makefile avec CMake
cmake ..

# Compiler avec CMake
cmake --build . --config Release

# Retourner au répertoire de travail initial
cd "$HOME/TP" || exit
