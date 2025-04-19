# 🎹 Template JUCE multi-plateforme (Linux, macOS, Windows)

Ce dépôt est un **modèle minimal et fonctionnel** pour créer un plugin audio ou une application standalone avec **JUCE** et **CMake**, compatible avec **Linux, macOS et Windows**.
Il est destiné en particulier à des [TP](https://www-fourier.ujf-grenoble.fr/~faure/enseignement/musique/TP_MAO/) pour étudiants en Physique-Musicologie à l'UGA.

---

## 📋 Menu rapide

- [🎹 Template JUCE multi-plateforme (Linux, macOS, Windows)](#-template-juce-multi-plateforme-linux-macos-windows)
  - [📋 Menu rapide](#-menu-rapide)
  - [🚀 Étapes d'utilisation](#-étapes-dutilisation)
    - [✅ 0. A faire une seule fois avant le premier projet](#-0-a-faire-une-seule-fois-avant-le-premier-projet)
      - [✅ 0.1. Choisir un répertoire et télécharger JUCE](#-01-choisir-un-répertoire-et-télécharger-juce)
      - [✅ 0.2. Télécharger  ce Template](#-02-télécharger--ce-template)
    - [🛠️ 2. Créer un nouveau projet](#️-2-créer-un-nouveau-projet)
    - [⚙️ 3. Compiler le projet](#️-3-compiler-le-projet)
    - [▶️ 4. Lancer l'exécutable standalone](#️-4-lancer-lexécutable-standalone)
    - [🧹 5. Nettoyer le projet](#-5-nettoyer-le-projet)
    - [⬆️ 6. Pousser sur GitLab](#️-6-pousser-sur-gitlab)
  - [🔗 Dépendances nécessaires](#-dépendances-nécessaires)
  - [✨ Astuces](#-astuces)
      - [3.2 Options de compilations disponibles](#32-options-de-compilations-disponibles)
  - [📬 Contact](#-contact)


---

## 🚀 Étapes d'utilisation



### ✅ 0. A faire une seule fois avant le premier projet



#### ✅ 0.1. Choisir un répertoire et télécharger JUCE


Avant de commencer, on choisit un répertoire existant  (par exemple le répertoire TP ou $HOME/c++/musique/JUCE_fred/ ) où seront stockés tous nos projets et où on va télécharger (cloner)  ce dépôt Template. Pour écrire dans un terminal

    export JUCE_PROJ=$HOME/TP

  ou
   
    export JUCE_PROJ=$HOME/c++/musique/JUCE_fred

  et

    cd $JUCE_PROJ

Dans ce répertoire, il faut au préalable avoir  installé JUCE  dans le répertoire JUCE-master.    Si ce n'est pas déjà fait, sur le site, [JUCE](https://juce.com/download/), cliquer sur « Download from GitHub », puis bouton « Code » et « Download ZIP » et extraire le fichier téléchargé dans ce répertoire (ex: TP). Cela crée le répertoire « JUCE-master ».


Alternative pour télécharger JUCE sous linux ou Mac: dans un terminal depuis ce répertoire écrire

    cd "$JUCE_PROJ"
    git clone --recurse-submodules https://github.com/juce-framework/JUCE.git
    mv JUCE JUCE-master 



#### ✅ 0.2. Télécharger  ce Template

Dans ce répertoire $JUCE_PROJ, on télécharge ce projet Template il faut au préalable avoir  installé JUCE  dans le répertoire JUCE-master.    Si ce n'est pas déjà fait, sur le site, [JUCE](https://juce.com/download/), cliquer sur « Download from GitHub », puis bouton « Code » et « Download ZIP » et extraire le fichier téléchargé dans ce répertoire (ex: TP). Cela crée le répertoire « JUCE-master ».

Par exemple sous linux ou Mac:

```bash
git clone https://gricad-gitlab.univ-grenoble-alpes.fr/faurefre/juce_template.git Template
cd Template
```

Ainsi, plus tard, on aura par exemple  l'arborescence

```
$HOME/TP/
├── JUCE-master/             ← téléchargé depuis JUCE
├── Template/                ← ce dépôt téléchargé
├── Projet1/                 ← futurs  projets que l'on créer
├── Projet2/
```


---

### 🛠️ 2. Créer un nouveau projet

On choisit un nom de projet, par exemple Projet1 et on écrit dans le terminal:

```bash
./1_setup.sh Projet1
```

Ce script :
- télécharge le template s'il est absent
- crée un nouveau dossier
- initialise Git et ajoute un `.gitignore`

Aller dans le répertoire du nouveau projet en écrivant 

    cd ../Projet1




---

### ⚙️ 3. Compiler le projet

Dans le répertoire du projet écrire au choix:

```bash
 # Compilation Debug (par défaut, à faire la 1ere fois)
./2_build.sh          
```
ou 

```bash
# Recompilation rapide (pas la 1ere fois)
./2_build.sh --fast    
```

ou

```bash
# Compilation Release (pour avoir une version finale optimisée)
./2_build.sh --release 
```


---

### ▶️ 4. Lancer l'exécutable standalone

Dans le répertoire du projet écrire:

```bash
./3_exec.sh
```



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

## ✨ Astuces

Vous pouvez créer plusieurs projets très rapidement à partir du template :

```bash
./1_setup.sh NomDuProjet       # crée un nouveau projet depuis le template
cd ../NomDuProjet              # se déplace dans le nouveau répertoire
./2_build.sh                   # compile le projet
./3_exec.sh                    # exécute l'application
```



#### 3.2 Options de compilations disponibles

Au début du fichier `CMakeLists.txt`, ou en option de la commande  ./2_build.sh     tu peux activer/désactiver certains formats ou le packaging via les options suivantes :

| Option              | Par défaut | Description                                        |
|---------------------|------------|----------------------------------------------------|
| `BUILD_STANDALONE`  | `ON`       | Génère l'application autonome (Standalone)         |
| `BUILD_VST3`        | `ON`       | Génère un plugin VST3                              |
| `BUILD_AU`          | `ON`       | Génère un plugin AU (macOS uniquement)             |
| `ENABLE_PACKAGING`  | `ON`       | Active la génération de paquets (`.pkg`, `.deb`…)  |

Par exemple, pour  ne compiler que le standalone sans packaging:

```bash
./2_build.sh  -DBUILD_VST3=OFF -DENABLE_PACKAGING=OFF
```


---

## 📬 Contact

Auteur : Frédéric Faure  
📧 [frederic.faure@univ-grenoble-alpes.fr](mailto:frederic.faure@univ-grenoble-alpes.fr)  
🌐 [https://www-fourier.ujf-grenoble.fr/~faure/](https://www-fourier.ujf-grenoble.fr/~faure/)

---

Bon code ! 🎧
