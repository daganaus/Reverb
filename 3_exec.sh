#!/bin/bash

# ================================================
# Script d'exécution du binaire JUCE standalone
# Détecte automatiquement le système et le chemin
# Compatible Linux / macOS / Windows via WSL / Git Bash
# ================================================

set -e

# Déduit automatiquement le chemin du répertoire JUCE_PROJ
JUCE_PROJ=$(cd "$(dirname "$0")/.." && pwd)
PROJECT="$(basename "$PWD")"
BUILD_TYPE="Debug"

LINUX_BIN="$JUCE_PROJ/$PROJECT/build/${PROJECT}_artefacts/$BUILD_TYPE/Standalone/Fred_$PROJECT"
MACOS_APP="$JUCE_PROJ/$PROJECT/build/${PROJECT}_artefacts/$BUILD_TYPE/Standalone/Fred_$PROJECT.app"
WIN_EXE="C:\\Users\\<NomUtilisateur>\\...\\$PROJECT\\build\\${PROJECT}_artefacts\\$BUILD_TYPE\\Standalone\\Fred_${PROJECT}.exe"

OS_NAME=$(uname)

echo "▶️ Lancement de l'application JUCE Standalone..."

if [[ "$OS_NAME" == "Linux" ]]; then
  if [ -f "$LINUX_BIN" ]; then
    "$LINUX_BIN"
  else
    echo "❌ Binaire non trouvé : $LINUX_BIN"
    echo "💡 Compilez d'abord avec ./2_build.sh"
  fi

elif [[ "$OS_NAME" == "Darwin" ]]; then
  if [ -d "$MACOS_APP" ]; then
    open "$MACOS_APP"
  else
    echo "❌ Application .app non trouvée : $MACOS_APP"
    echo "💡 Compilez d'abord avec ./2_build.sh"
  fi

elif [[ "$OS_NAME" == MINGW* || "$OS_NAME" == MSYS* || "$OS_NAME" == CYGWIN* ]]; then
  echo "💡 Sous Windows, ouvrez :"
  echo "$WIN_EXE"
else
  echo "❌ Système non reconnu : $OS_NAME"
fi
