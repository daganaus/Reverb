#!/bin/bash

# ================================================
# Script de compilation JUCE/CMake multi-mode
# - Debug par défaut, Release avec --release
# - Recompilation rapide avec --fast
# ================================================

JUCE_PROJ="$HOME/c++/musique/JUCE_fred"
PROJECT="Template"
JUCE_DIR="$JUCE_PROJ/JUCE-master"
BUILD_DIR="build"

# Couleurs terminal
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Options par défaut
BUILD_TYPE="Debug"
FULL_REBUILD=true

# Analyse des options
for arg in "$@"; do
  case $arg in
    --release)
      BUILD_TYPE="Release"
      shift
      ;;
    --fast)
      FULL_REBUILD=false
      shift
      ;;
  esac
done

# Affichage
echo -e "${GREEN}🚀 Compilation de $PROJECT [$BUILD_TYPE]${NC}"

# Vérification des chemins
cd "$JUCE_PROJ/$PROJECT" || { echo -e "${RED}❌ Projet introuvable${NC}"; exit 1; }
if [ ! -f "$JUCE_DIR/CMakeLists.txt" ]; then
    echo -e "${RED}❌ Erreur : JUCE_DIR invalide ($JUCE_DIR)${NC}"
    exit 1
fi

# Nettoyage build si nécessaire
if [ "$FULL_REBUILD" = true ]; then
  echo -e "${GREEN}🧹 Suppression de l'ancien build...${NC}"
  rm -rf "$BUILD_DIR"
  mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR" || exit 1

# Configuration (si nécessaire)
if [ "$FULL_REBUILD" = true ] || [ ! -f "CMakeCache.txt" ]; then
  echo -e "${GREEN}⚙️ Configuration CMake [$BUILD_TYPE]...${NC}"
  cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DJUCE_DIR="$JUCE_DIR" .. || { echo -e "${RED}❌ Échec configuration${NC}"; exit 1; }
fi

# Compilation
echo -e "${GREEN}🛠️ Compilation...${NC}"
cmake --build . -- -j$(nproc) || { echo -e "${RED}❌ Échec compilation${NC}"; exit 1; }

# Packaging (optionnel)
if [ "$FULL_REBUILD" = true ]; then
  echo -e "${GREEN}📦 Création du package (cpack)...${NC}"
  cpack . || echo -e "${RED}⚠️ Aucun package généré (optionnel)${NC}"
fi

echo -e "${GREEN}✅ Compilation terminée avec succès.${NC}"


# Détection du système pour afficher la commande d'exécution appropriée
OS_NAME=$(uname)

echo "▶️ Pour exécuter :"
if [[ "$OS_NAME" == "Linux" ]]; then
  echo "🔹 Sous Linux :"
  echo "\"$JUCE_PROJ/$PROJECT/build/${PROJECT}_artefacts/$BUILD_TYPE/Standalone/Fred_$PROJECT\""
elif [[ "$OS_NAME" == "Darwin" ]]; then
  echo "🔹 Sous macOS :"
  echo "open \$JUCE_PROJ/\$PROJECT/build/\${PROJECT}_artefacts/Standalone/Fred_\$PROJECT.app"
elif [[ "$OS_NAME" == MINGW* || "$OS_NAME" == MSYS* || "$OS_NAME" == CYGWIN* ]]; then
  echo "🔹 Sous Windows :"
  echo "& \"C:\\Users\\<NomUtilisateur>\\c++\\musique\\JUCE_fred\\$NEW_PROJECT_NAME\\build\\${NEW_PROJECT_NAME}_artefacts\\Standalone\\Fred_${NEW_PROJECT_NAME}.exe\""
else
  echo "🔹 Système non reconnu : $OS_NAME"
fi
