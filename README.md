# Template JUCE multi-plateforme (Linux, macOS, Windows)

Ce dépôt est un **modèle minimal et fonctionnel** pour créer un plugin audio ou une application standalone avec **JUCE** et **CMake**, compatible avec **Linux, macOS et Windows**.
Il est destiné en particulier à des [TP](https://www-fourier.ujf-grenoble.fr/~faure/enseignement/musique/TP_MAO/) pour étudiants en Physique-Musicologie à l'UGA.

---


<!-- TOC -->- [Template JUCE multi-plateforme (Linux, macOS, Windows)](#template-juce-multi-plateforme-linux-macos-windows)
- [Template JUCE multi-plateforme (Linux, macOS, Windows)](#template-juce-multi-plateforme-linux-macos-windows)
- [Étapes d'utilisation](#étapes-dutilisation)
  - [1. A faire une seule fois avant le premier projet](#1-a-faire-une-seule-fois-avant-le-premier-projet)
    - [1.1. Choisir un répertoire et télécharger JUCE](#11-choisir-un-répertoire-et-télécharger-juce)
    - [1.2. Télécharger  ce Template](#12-télécharger--ce-template)
  - [2. Créer un nouveau projet](#2-créer-un-nouveau-projet)
  - [3. Compiler le projet](#3-compiler-le-projet)
  - [4. Lancer l'exécutable standalone](#4-lancer-lexécutable-standalone)
- [5. (Optionnel) Ecriture automatique  du code GUI (des widgets) pour JUCE: com.h, com.cc](#5-optionnel-ecriture-automatique--du-code-gui-des-widgets-pour-juce-comh-comcc)
  - [5.1 Exemple d'utilisation  avec le projet Template](#51-exemple-dutilisation--avec-le-projet-template)
- [6. (Optionnel) Nettoyer le projet](#6-optionnel-nettoyer-le-projet)
- [7. Déposer le projet  sur GitLab](#7-déposer-le-projet--sur-gitlab)
  - [🔗 Dépendances nécessaires](#-dépendances-nécessaires)
- [8. Astuces](#8-astuces)
  - [8.1 Options de compilations disponibles](#81-options-de-compilations-disponibles)
- [9. A faire (TO DO)](#9-a-faire-to-do)
- [📬 Contact](#-contact)

<!-- TOC END -->




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

# 5. (Optionnel) Ecriture automatique  du code GUI (des widgets) pour JUCE: com.h, com.cc

On peut utiliser un script appelé `makef`pour écrire automatique le code c++ concernant les widgets de l'interface GUI de JUCE. 

Voici le logiciel `makef`à installer et configurer:

https://gricad-gitlab.univ-grenoble-alpes.fr/faurefre/makef


## 5.1 Exemple d'utilisation  avec le projet Template


On supposer que vous avez installé le logiciel `makef` et que vous avez créé un projet `Projet` (ou autre nom) à partir de `Template`.

- Ouvrir le fichier Source/editor/manager.h et dans la classe Manager, vers la ligne 50 ajoutez  la ligne suivante:

      int essai = 3; //  make_gui =  N(ZT("mon onglet"),"essai") help ="un essai de widget"

- Modifier les répertoires dans le fichcier `makef.config`

- Dans un terminal, se placer dans le répertoire du projet, et écrire:


      makef Source editor/PluginEditor.cc  makef.config  main   JUCE



  résultat: cela écrit les fichiers com.h, com.cc dans le répertoire $REP/Source, prêts à la compilation.      

- Vous recompilez (en mode fast) et exécutez le projet comme expliqué ci-dessus.

  résultat: Il apparaitra un onglet appelé "mon onglet" qui contient un widget avec la valeur numérique de la variable essai que l'on peut modifier. Il y a aussi le message d'aide si la souris passe dessus.

<!-- OK  sous Linux -->

---

#  6. (Optionnel) Nettoyer le projet


- Sous linux ou Mac:
  ```bash
  ./4_clean.sh
  ```

- Sous Windows:

  ```bash
  ./4_clean.ps1
  ```


Cela supprime le dossier `build/` et tous les fichiers intermédiaires (artefacts de packaging, caches, etc).

---

#  7. Déposer le projet  sur GitLab

depuis le répertoire du projet:

  ```bash
  ./git_update.sh
  ```

c'est un script simple pour synchroniser votre projet avec un dépôt distant GitLab ou GitHub.

---

## 🔗 Dépendances nécessaires

- [JUCE](https://github.com/juce-framework/JUCE) (à cloner une fois dans `$JUCE_PROJ/JUCE`)
- `cmake` (≥ 3.22)
- `g++` / `clang++`
- `git`
- (Windows) Visual Studio ou MSYS2 recommandé

---


# 8. Astuces


## 8.1 Options de compilations disponibles

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

# 9. A faire (TO DO)

 - Incorporer le script make_f et ajouter la doc
 - Mettre les jauges de latence dans un onglet "moniteur"
 - Rendre compatible avec ROOT du cern et Armadillo?
 

---

# 📬 Contact

Auteur : Frédéric Faure  
📧 [frederic.faure@univ-grenoble-alpes.fr](mailto:frederic.faure@univ-grenoble-alpes.fr)  
🌐 [https://www-fourier.ujf-grenoble.fr/~faure/](https://www-fourier.ujf-grenoble.fr/~faure/)

---

Bon code ! 🎧
