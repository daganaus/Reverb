#!/bin/bash

# ================================================
# Script Bash pour créer un nouveau projet JUCE
# à partir d'un template local ou en le clonant
# Usage : ./setup_juce.sh MonNouveauProjet
# Compatible macOS / Linux
# ================================================

set -e

# Vérifie que l'utilisateur fournit un nom de projet
if [ -z "$1" ]; then
  echo "❌ Veuillez fournir un nom de projet."
  echo "Usage : ./setup_juce.sh NomDuProjet"
  exit 1
fi

# ========== Paramètres ==========
NEW_PROJECT_NAME="$1"
JUCE_PROJ="$HOME/c++/musique/JUCE_fred"
TEMPLATE_NAME="Template"
TEMPLATE_REPO="https://gricad-gitlab.univ-grenoble-alpes.fr/faurefre/juce_template.git"
SOURCE_DIR="$JUCE_PROJ/$TEMPLATE_NAME"
DEST_DIR="$JUCE_PROJ/$NEW_PROJECT_NAME"

# ========== Vérifications ==========

# Vérifie que le projet n'existe pas déjà
if [ -d "$DEST_DIR" ]; then
  echo "❌ Le dossier cible existe déjà : $DEST_DIR"
  exit 1
fi

# Vérifie si le template est disponible localement, sinon le cloner
if [ ! -d "$SOURCE_DIR" ]; then
  echo "📥 Template introuvable localement. Clonage depuis GitLab..."
  cd "$JUCE_PROJ"
  git clone "$TEMPLATE_REPO" "$TEMPLATE_NAME"
fi

# ========== Copie du template ==========
echo "📁 Copie du template vers $NEW_PROJECT_NAME..."
cp -r "$SOURCE_DIR" "$DEST_DIR"

# ========== Mise à jour du nom dans CMakeLists.txt ==========
CMAKE_PATH="$DEST_DIR/CMakeLists.txt"
sed -i.bak "s/set(\s*TARGET_NAME\s\+.*)/set(TARGET_NAME $NEW_PROJECT_NAME)/" "$CMAKE_PATH"
rm "$CMAKE_PATH.bak"

# ========== Initialisation Git et .gitignore ==========
cd "$DEST_DIR"
git init > /dev/null

# Crée un fichier .gitignore adapté à JUCE/CMake
cat > .gitignore <<EOF
build/
cmake-build-*/
CMakeFiles/
Makefile
CMakeCache.txt
install_manifest.txt
Builds/
JuceLibraryCode/
*.o
*.so
*.dylib
*.exe
*.app
*.a
.vscode/
.idea/
.DS_Store
*.tar.gz
*.deb
*.pkg
EOF

git add .gitignore

echo "✅ Nouveau projet prêt : $DEST_DIR"
echo "📖 Un fichier README.md est inclus avec des instructions pour Linux, macOS et Windows."
echo "💡 Dans le répertoire $DEST_DIR, lancez ./build_juce.sh ou ./build_juce.ps1 pour compiler."

