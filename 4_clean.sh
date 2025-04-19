#!/bin/bash

# ================================================
# Script de nettoyage complet du projet JUCE
# Supprime le dossier build/ et les artefacts intermédiaires
# Compatible Linux / macOS / Windows via Git Bash / WSL
# ================================================

set -e

JUCE_PROJ=$(cd "$(dirname "$0")/.." && pwd)
PROJECT="$(basename "$PWD")"
BUILD_DIR="build"

echo "🧹 Nettoyage du projet : $PROJECT"

# Suppression du dossier de build
if [ -d "$BUILD_DIR" ]; then
  rm -rf "$BUILD_DIR"
  echo "✅ Dossier $BUILD_DIR supprimé."
else
  echo "ℹ️ Aucun dossier $BUILD_DIR à supprimer."
fi

# Suppression des fichiers de packaging
rm -f install_manifest.txt
rm -f *.tar.gz *.pkg *.deb *.exe *.zip

# Suppression des fichiers de sauvegarde éventuels
rm -f CMakeLists.txt.bak
rm -f *.old *.tmp

echo "✅ Nettoyage terminé."
echo "💡 Vous pouvez relancer ./2_build.sh pour recompiler."
