#!/bin/bash

# ================================================
# Script d'exécution du binaire JUCE Standalone
# Compatible Linux / macOS / Windows via WSL / Git Bash
# ================================================

set -e

JUCE_PROJ=$(cd "$(dirname "$0")/.." && pwd)
PROJECT="$(basename "$PWD")"
BUILD_TYPE="Debug"

# Trouve dynamiquement le nom d'artefact
ARTEFACT_DIR=$(find "$JUCE_PROJ/$PROJECT/build" -maxdepth 1 -type d -name "*_artefacts" | head -n 1)
APP_NAME=$(basename "$ARTEFACT_DIR" _artefacts) # Ex: Template → Fred_Template

if [ -z "$ARTEFACT_DIR" ]; then
  echo "❌ Aucun dossier *_artefacts trouvé dans build/. Avez-vous bien compilé ?"
  exit 1
fi

OS_NAME=$(uname)

echo "▶️ Lancement de l'application JUCE Standalone..."

if [[ "$OS_NAME" == "Linux" ]]; then
  EXEC="$ARTEFACT_DIR/$BUILD_TYPE/Standalone/Fred_${APP_NAME}"
  if [ -f "$EXEC" ]; then
    "$EXEC"
  else
    echo "❌ Binaire non trouvé : $EXEC"
    echo "💡 Compilez d'abord avec ./2_build.sh"
  fi

elif [[ "$OS_NAME" == "Darwin" ]]; then
  APP="$ARTEFACT_DIR/$BUILD_TYPE/Standalone/Fred_${APP_NAME}.app"
  if [ -d "$APP" ]; then
    open "$APP"
  else
    echo "❌ Application .app non trouvée : $APP"
    echo "💡 Compilez d'abord avec ./2_build.sh"
  fi

elif [[ "$OS_NAME" == MINGW* || "$OS_NAME" == MSYS* || "$OS_NAME" == CYGWIN* ]]; then
  echo "💡 Sous Windows, ouvrez :"
  echo "C:\\Users\\<NomUtilisateur>\\...\\$PROJECT\\build\\${APP_NAME}_artefacts\\$BUILD_TYPE\\Standalone\\Fred_${APP_NAME}.exe"
else
  echo "❌ Système non reconnu : $OS_NAME"
fi
