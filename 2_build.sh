#!/bin/bash

# ================================================
# Script de compilation JUCE/CMake multi-mode
# - Debug par défaut, Release avec --release
# - Recompilation rapide avec --fast
# Compatible Linux / macOS / Windows via WSL ou Git Bash
# ================================================

set -e

# Déduit automatiquement le chemin du répertoire JUCE_PROJ
JUCE_PROJ=$(cd "$(dirname "$0")/.." && pwd)
PROJECT="$(basename "$PWD")"
JUCE_DIR="$JUCE_PROJ/JUCE-master"
BUILD_DIR="build"

# Options par défaut
BUILD_TYPE="Debug"
FULL_REBUILD=true

# Lecture des options
for arg in "$@"; do
  case $arg in
    --release)
      BUILD_TYPE="Release"
      shift;;
    --fast)
      FULL_REBUILD=false
      shift;;
  esac
done

# Affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
echo -e "${GREEN}🚀 Compilation de $PROJECT [$BUILD_TYPE]${NC}"

# Vérification JUCE_DIR
if [ ! -f "$JUCE_DIR/CMakeLists.txt" ]; then
  echo -e "${RED}❌ Erreur : JUCE_DIR invalide ($JUCE_DIR)${NC}"
  exit 1
fi

# Nettoyage build si nécessaire
if [ "$FULL_REBUILD" = true ]; then
  echo -e "${GREEN}🧹 Nettoyage du dossier build...${NC}"
  rm -rf "$BUILD_DIR"
  mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Configuration CMake
if [ "$FULL_REBUILD" = true ] || [ ! -f "CMakeCache.txt" ]; then
  echo -e "${GREEN}⚙️ Configuration CMake...${NC}"
  cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DJUCE_DIR="$JUCE_DIR" ..
fi

# Compilation
echo -e "${GREEN}🛠️ Compilation en cours...${NC}"
cmake --build . -- -j$(nproc)

# Packaging (optionnel)
if [ "$FULL_REBUILD" = true ]; then
  echo -e "${GREEN}📦 Packaging avec cpack...${NC}"
  cpack . || echo -e "${RED}⚠️ Aucun package généré (facultatif)${NC}"
fi

# Message final
echo -e "${GREEN}✅ Compilation réussie.${NC}"
echo -e "\n▶️ Étape suivante : ./3_exec.sh"
