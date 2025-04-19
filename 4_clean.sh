#!/bin/bash

# ================================================
# Script de nettoyage complet du projet JUCE
# Supprime le dossier build/ et les artefacts intermédiaires
# Compatible Linux / macOS / Windows via Git Bash / WSL
# ================================================

set -e

# Déduit automatiquement le chemin du répertoire JUCE_PROJ
JUCE_PROJ=$(cd "$(dirname "$0")/.." && pwd)
PROJECT="$(basename "$PWD")"
BUILD_DIR="build"

echo "🧹 Nettoyage du projet : $PROJECT"

if [ -d "$BUILD_DIR" ]; then
  rm -rf "$BUILD_DIR"
  echo "✅ Dossier $BUILD_DIR supprimé."
else
  echo "ℹ️ Aucun dossier $BUILD_DIR à supprimer."
fi

# Nettoyage complémentaire si nécessaire
rm -f install_manifest.txt
rm -f *.tar.gz *.pkg *.deb *.exe *.zip

echo "✅ Nettoyage terminé."
echo "💡 Vous pouvez relancer ./2_build.sh pour recompiler."
