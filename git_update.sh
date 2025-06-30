#!/bin/bash

# Répertoires
PROJ_DIR="$HOME/Stage_ffaure/Reverb"

# Aller dans le projet
cd "$PROJ_DIR" || { echo "❌ Dossier introuvable : $PROJ_DIR" >&2; exit 1; }

# Nettoyage
echo "🧹 Nettoyage des dossiers générés par Projucer..."
rm -rf Builds JuceLibraryCode

echo "🧹 Suppression des fichiers temporaires *~"
find . -type f -name '*~' -delete

# Vérification de l’état Git
if ! git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
    echo "❌ Ce dossier n'est pas un dépôt Git." >&2
    exit 1
fi

# Demande de message de commit
read -p "Entrez le message de commit : " MESSAGE

# Ajouter les changements
echo "🔍 Préparation des changements pour commit..."
git add -A

# Commit avec message automatique ou personnalisé
MESSAGE="${MESSAGE:-mise à jour}"
git commit -m "$MESSAGE"

# Pousser sur le dépôt distant
echo "📤 Envoi sur Git..."
git push

echo "✅ Fini."