# 🎹 Template JUCE multi-plateforme (Linux, macOS, Windows)

Ce dépôt est un **modèle minimal et fonctionnel** pour créer un plugin audio ou une application standalone avec **JUCE** et **CMake**, compatible avec **Linux, macOS et Windows**.

---

## 📋 Menu rapide

- [🎹 Template JUCE multi-plateforme (Linux, macOS, Windows)](#-template-juce-multi-plateforme-linux-macos-windows)
  - [📋 Menu rapide](#-menu-rapide)
  - [📁 Arborescence recommandée](#-arborescence-recommandée)
  - [🚀 Étapes d'utilisation](#-étapes-dutilisation)
    - [✅ 1. Cloner ce template](#-1-cloner-ce-template)
    - [✅ 2. Configuration initiale (automatique)](#-2-configuration-initiale-automatique)
    - [🛠️ 2. Créer un nouveau projet](#️-2-créer-un-nouveau-projet)
    - [⚙️ 3. Compiler le projet](#️-3-compiler-le-projet)
    - [▶️ 4. Lancer l'exécutable standalone](#️-4-lancer-lexécutable-standalone)
    - [🧹 5. Nettoyer le projet](#-5-nettoyer-le-projet)
    - [⬆️ 6. Pousser sur GitLab](#️-6-pousser-sur-gitlab)
  - [🔗 Dépendances nécessaires](#-dépendances-nécessaires)
  - [✨ Astuce](#-astuce)
  - [📬 Contact](#-contact)

---

## 📁 Arborescence recommandée

```
$HOME/c++/musique/JUCE_fred/
├── JUCE/                    ← clone du framework JUCE (officiel ou fork)
├── Template/                ← ce dépôt cloné ici (modèle de base)
├── MonProjet1/              ← projets créés depuis le modèle
├── MonProjet2/
```

---

## 🚀 Étapes d'utilisation



### ✅ 1. Cloner ce template

Avant de commencer, vous devez choisir un répertoire personnel où seront stockés tous vos projets JUCE et où vous pouvez   cloner (copier) ce dépôt template.
Dans ce répertoire, on suppose que vous avez déjà installé  [JUCE](https://github.com/juce-framework/JUCE) 

Par exemple sous linux:

```bash
mkdir -p $HOME/c++/musique/JUCE_fred
cd $HOME/c++/musique/JUCE_fred

git clone https://gricad-gitlab.univ-grenoble-alpes.fr/faurefre/juce_template.git Template
cd Template
```

### ✅ 2. Configuration initiale (automatique)

La première fois, le script vous demandera :

```bash
❓ Où souhaitez-vous stocker vos projets JUCE ?
Répertoire racine (ex: $HOME/juce_projects) :
```

Ce chemin sera sauvegardé dans `~/.juce_config` pour toutes les futures utilisations.

---

### 🛠️ 2. Créer un nouveau projet

```bash
./1_setup.sh MonNouveauProjet
```

Ce script :
- clone le template s'il est absent
- crée un nouveau dossier
- renomme automatiquement le projet dans le `CMakeLists.txt`
- initialise Git et ajoute un `.gitignore`
- vous place dans le dossier du projet

---

### ⚙️ 3. Compiler le projet

Dans le dossier du projet :

```bash
./2_build.sh           # Compilation Debug (par défaut)
./2_build.sh --fast    # Recompilation rapide
./2_build.sh --release # Compilation Release
```

---

### ▶️ 4. Lancer l'exécutable standalone

```bash
./3_exec.sh
```

Ce script détecte automatiquement :
- Linux → exécute le binaire
- macOS → ouvre l'application .app
- Windows → affiche le chemin du `.exe`

---

### 🧹 5. Nettoyer le projet

```bash
./4_clean.sh
```

Supprime le dossier `build/` et tous les fichiers intermédiaires (artefacts de packaging, caches, etc).

---

### ⬆️ 6. Pousser sur GitLab

```bash
./git_update.sh
```

Script simple pour synchroniser votre projet avec un dépôt distant GitLab ou GitHub.

---

## 🔗 Dépendances nécessaires

- [JUCE](https://github.com/juce-framework/JUCE) (à cloner une fois dans `$JUCE_PROJ/JUCE`)
- `cmake` (≥ 3.22)
- `g++` / `clang++`
- `git`
- (Windows) Visual Studio ou MSYS2 recommandé

---

## ✨ Astuce

Vous pouvez créer plusieurs projets très rapidement à partir du template :

```bash
./1_setup.sh NomDuProjet       # crée un nouveau projet depuis le template
./2_build.sh                   # compile le projet
./3_exec.sh                    # exécute l'application
```

---

## 📬 Contact

Auteur : Frédéric Faure  
📧 [frederic.faure@univ-grenoble-alpes.fr](mailto:frederic.faure@univ-grenoble-alpes.fr)  
🌐 [https://www-fourier.ujf-grenoble.fr/~faure/](https://www-fourier.ujf-grenoble.fr/~faure/)

---

Bon code ! 🎧
