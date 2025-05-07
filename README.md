# Template JUCE multi-plateforme (Linux, macOS, Windows)

Ce dépôt est un **modèle minimal et fonctionnel** pour créer un plugin audio ou une application standalone avec **JUCE** et **CMake**, compatible avec **Linux, macOS et Windows**.
Il est destiné en particulier à des [TP](https://www-fourier.ujf-grenoble.fr/~faure/enseignement/musique/TP_MAO/) pour étudiants en Physique-Musicologie à l'UGA.

---

## Table des matières

- [🎹 Template JUCE multi-plateforme (Linux, macOS, Windows)](#-template-juce-multi-plateforme-linux-macos-windows)
  - [📋 Menu rapide](#-menu-rapide)
  - [🚀 Étapes d'utilisation](#-étapes-dutilisation)
    - [✅ 0. A faire une seule fois avant le premier projet](#-0-a-faire-une-seule-fois-avant-le-premier-projet)
      - [✅ 0.1. Choisir un répertoire et télécharger JUCE](#-01-choisir-un-répertoire-et-télécharger-juce)
      - [✅ 0.2. Télécharger  ce Template](#-02-télécharger--ce-template)
    - [🛠️ 2. Créer un nouveau projet](#️-2-créer-un-nouveau-projet)
    - [⚙️ 3. Ecriture automatique  du code GUI pour JUCE: com.h, com.cc](#️-3-ecriture-automatique--du-code-gui-pour-juce-comh-comcc)
    - [⚙️ 4. Compiler le projet](#️-4-compiler-le-projet)
    - [▶️ 5. Lancer l'exécutable standalone](#️-5-lancer-lexécutable-standalone)
    - [🧹 6. Nettoyer le projet](#-6-nettoyer-le-projet)
    - [⬆️ 7. Déposer le projet  sur GitLab](#️-7-déposer-le-projet--sur-gitlab)
  - [🔗 Dépendances nécessaires](#-dépendances-nécessaires)
  - [✨ Astuces](#-astuces)
      - [3.2 Options de compilations disponibles](#32-options-de-compilations-disponibles)
  - [A faire (TO DO)](#a-faire-to-do)
  - [📬 Contact](#-contact)


---

#  Étapes d'utilisation



## 1. A faire une seule fois avant le premier projet



###  1.1. Choisir un répertoire et télécharger JUCE


Avant de commencer, on choisit un répertoire existant,  par exemple le répertoire `TP` où seront stockés tous nos projets utilisant JUCE.

- Télécharger JUCE:

  sur le site, [JUCE](https://juce.com/download/), cliquer sur « Download from GitHub », puis bouton « Code » et « Download ZIP » et extraire le fichier téléchargé dans ce répertoire (ex: `TP`). Cela crée le répertoire « JUCE-master ».


- Alternative pour télécharger JUCE:

  dans un terminal depuis ce répertoire (ex: `TP`) écrire

    
      git clone --recurse-submodules https://github.com/juce-framework/JUCE.git
      mv JUCE JUCE-master 



###  1.2. Télécharger  ce Template


Dans un terminal, dans ce répertoire (ex: `TP`) écrire:

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

## 2. Créer un nouveau projet

On choisit un nom de projet, par exemple `Projet1` et on écrit dans le terminal depuis le répertoire `Template`:

- Sous linux et Mac écrire:

  ```bash
  ./1_setup.sh Projet1
  ```

- Sous Windows écrire:
  ```bash
  ./1_setup.ps1 Projet1
  ```

Ce script :
- télécharge le template s'il est absent
- Copie ce template dans un nouveau répertoire
- Se déplace dans ce nouveau répertoire du nouveau projet. Ou le faire soi-même.

<!-- OK  -->

---

## 3. Compiler le projet

Dans le répertoire du projet écrire **au choix** une des lignes suivante:

- Sous linux ou Mac:

  ```bash
  # Compilation Debug (par défaut, à faire la 1ere fois)
  ./2_build.sh          
  # ou Recompilation rapide (pas la 1ere fois)
  ./2_build.sh --fast   
  # ou Compilation Release (pour avoir une version finale optimisée)
  ./2_build.sh --release 
  ```

<!-- OK  -->

- Sous Windows:

  ```bash
  # Compilation Debug (par défaut, à faire la 1ere fois)
  ./2_build.ps1          
  # ou Recompilation rapide (pas la 1ere fois)
  ./2_build.ps1 --fast   
  # ou Compilation Release (pour avoir une version finale optimisée)
  ./2_build.ps1 --release 
  ```
<!-- OK  -->

---

## 4. Lancer l'exécutable standalone

Dans le répertoire du projet écrire:

- Sous linux ou Mac:

  ```bash
  ./3_exec.sh
  ```

- Sous Windows:

  ```bash
  ./3_exec.ps1
  ```
<!-- OK  -->


---

## 5. Ecriture automatique  du code GUI (des widgets) pour JUCE: com.h, com.cc

On peut utiliser un script appelé `makef`pour ecrire automatique le code c++ concernant les widgets de l'interface GUI de JUCE. Au départ vous donnez l'information sur les widgets dans les commentaires de votre code (voir documentation sur `makef`).


- Au préalable il faut renseigner  les informations voulues dans le fichier de configuration `makef.config`
  Les explications sont donnés ci-dessous.

Dans les lignes suivantes (modifier si besoin),
 - $REP est le répertoire du projet
 - $REP/Source est le répertoire qui contient les fichiers sources .h et .cc de votre projet.
 - $FILE est le fichier de départ indiqué depuis le répertoire $REP
 - $CONFIG est le fichier de configuration  `makef.config` contenant les paramètres pour makef.


Dans un terminal, se placer dans le répertoire du projet, et écrire:


    REP=.
    FILE=editor/PluginEditor.cc
    CONFIG="$REP"/makef.config

    makef "$REP"/Source "$FILE" "$CONFIG" main JUCE
    rm -rf "$REP"/Source/editor/Makefile*
    rm -rf "$REP"/Source/editor/README_tmp
    


résultat: cela écrit les fichiers com.h, com.cc dans le répertoire $REP/Source, prêts à la compilation.


---

### 🧹 6. Nettoyer le projet


Sous linux ou Mac:
```bash
./4_clean.sh
```

Sous Windows:
```bash
./4_clean.ps1
```


Cela supprime le dossier `build/` et tous les fichiers intermédiaires (artefacts de packaging, caches, etc).

---

### ⬆️ 7. Déposer le projet  sur GitLab

depuis le répertoire du projet:

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

## A faire (TO DO)

 - Incorporer le script make_f et ajouter la doc
 - Mettre les jauges de latence dans un onglet "moniteur"
 - Rendre compatible avec ROOT du cern et Armadillo?
 

---

## 📬 Contact

Auteur : Frédéric Faure  
📧 [frederic.faure@univ-grenoble-alpes.fr](mailto:frederic.faure@univ-grenoble-alpes.fr)  
🌐 [https://www-fourier.ujf-grenoble.fr/~faure/](https://www-fourier.ujf-grenoble.fr/~faure/)

---

Bon code ! 🎧
