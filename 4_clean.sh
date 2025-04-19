#!/bin/bash

# ================================================
# Script de nettoyage complet du projet JUCE
# Supprime le dossier build/ et les artefacts intermédiaires
# Compatible Linux / macOS / Windows via Git Bash / WSL
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

# Nom du projet (dossier courant)
PROJECT="$(basename "$PWD")"
BUILD_DIR="build"

echo "🧹 Nettoyage du projet : $PROJECT"

if [ -d "$BUILD_DIR" ]; then
  rm -rf "$BUILD_DIR"
  echo "✅ Dossier $BUILD_DIR supprimé."
else
  echo "ℹ️ Aucun dossier $BUILD_DIR à supprimer."
fi

# Nettoyage complémentaire si nécessaire (ex: cpack, install manifest)
rm -f install_manifest.txt
rm -f *.tar.gz *.pkg *.deb *.exe *.zip

echo "✅ Nettoyage terminé."
echo "💡 Vous pouvez relancer ./2_build.sh pour recompiler."
