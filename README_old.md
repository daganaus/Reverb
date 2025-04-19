🎹 Projet JUCE – Modèle multi-plateforme
=======================

Ce dépôt est un template minimal pour créer des projets audio (VST3 / Standalone) en C++ avec JUCE, compatible Linux, macOS et Windows via CMake.

Ce projet est utilisé dans les  TP suivants:
[TP_JUCE](https://www-fourier.ujf-grenoble.fr/~faure/enseignement/musique/TP_MAO/)



On suppose que vous avez un répertoire contenant tous vos projets de JUCE, appelé

    $HOME/c++/musique/JUCE_fred/   

On suppose que dans ce répertoire vous avez déjà installé  [JUCE-master](https://github.com/juce-framework/JUCE) 


Dans la suite, on explique comment ajouter un projet selon un modèle proposé. On aura donc  une arborescence similaire à: 


    $HOME/c++/musique/JUCE_fred/           ← répertoire selon votre cas
    ├── JUCE-master/                       ← clone unique du dépôt JUCE
    ├── Projet1/
    │   ├── CMakeLists.txt
    │   ├── src/
    │   └── build/
    ├── Projet2/
    │   ├── CMakeLists.txt
    │   ├── src/
    │   └── build/


Selon votre ordinateur, aller à la section [Linux](#1-linux) ou [Windows](#2-windows)




1 Linux
==========


Téléchargement sous Linux
---------------------------
Dans un terminal, écrire (remplacer Projet par le nom du nouveau projet):

    ./setup_juce.sh Projet


1.1 Compiler sous Linux 
-----------
Dans un terminal, écrire au choix:


    ./build_juce.sh               # debug complet (nettoyage + cpack)
    ./build_juce.sh --release     # release complet (nettoyage + cpack)
    ./build_juce.sh --fast        # recompilation rapide





    

1.2 Execution sous Linux
-----------
Dans un terminal, écrire:

    JUCE_PROJ="$HOME/c++/musique/JUCE_fred" # select your directory here
    PROJECT="Template";

    $JUCE_PROJ/$PROJECT/build/"$PROJECT"_artefacts/Standalone/Fred_$PROJECT






1.3 Poser le projet sur gitlab depuis Linux
------------------------

    ./git_update.sh





2 Windows
==========

2.1 Compiler sous windows
-----------
Dans un terminal, écrire au choix:

    .\build_juce.ps1               # debug complet
    .\build_juce.ps1 --release     # release complet
    .\build_juce.ps1 --fast        # recompilation rapide




