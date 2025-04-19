#!/bin/bash

# ================================================
# Script de compilation JUCE/CMake multi-mode
# - Debug par défaut, Release avec --release
# - Recompilation rapide avec --fast
# Compatible Linux / macOS / Windows via WSL ou Git Bash
# ================================================

set -e

# Chargement config utilisateur
CONFIG_FILE="$HOME/.juce_config"
if [ -f "$CONFIG_FILE" ]; then
  source "$CONFIG_FILE"
else
  echo "❌ Fichier de configuration introuvable : $CONFIG_FILE"
  echo "Lancez d'abord ./1_setup.sh MonProjet"
  exit 1
fi

# Nom du projet courant (déduit du dossier courant)
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

# Vérification
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

# Proposition d'exécution
OS_NAME=$(uname)
echo -e "\n▶️ Étape suivante : lancer ./3_exec.sh"
echo "💡 Chemin binaire probable :"
if [[ "$OS_NAME" == "Linux" ]]; then
  echo "$JUCE_PROJ/$PROJECT/build/${PROJECT}_artefacts/$BUILD_TYPE/Standalone/Fred_$PROJECT"
elif [[ "$OS_NAME" == "Darwin" ]]; then
  echo "open $JUCE_PROJ/$PROJECT/build/${PROJECT}_artefacts/$BUILD_TYPE/Standalone/Fred_$PROJECT.app"
elif [[ "$OS_NAME" == MINGW* || "$OS_NAME" == MSYS* || "$OS_NAME" == CYGWIN* ]]; then
  echo "& \"C:\\Users\\<NomUtilisateur>\\...\\$PROJECT\\build\\${PROJECT}_artefacts\\$BUILD_TYPE\\Standalone\\Fred_${PROJECT}.exe\""
else
  echo "🔹 Système non reconnu : $OS_NAME"
fi
