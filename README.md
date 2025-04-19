Projet: Template pour C++ et JUCE
=======================

C'est un modèle de base pour démarrer un projet quelconque utilisant C++ et  JUCE, sous Linux, Mac ou Windows.

Ce projet est utilisé dans les  TP suivants:
[TP_JUCE](https://www-fourier.ujf-grenoble.fr/~faure/enseignement/musique/TP_MAO/)

[Aller à la section Linux](#1-linux)


Dans la suite on suppose une arborescence similaire à: 


$HOME/c++/musique/JUCE_fred/
├── JUCE/                       ← clone unique du dépôt JUCE (officiel ou fork)
├── Projet1/
│   ├── CMakeLists.txt
│   ├── src/
│   └── build/
├── Projet2/
│   ├── CMakeLists.txt
│   ├── src/
│   └── build/


On suppose que JUCE est installé. On va ajouter le projet "Template"


1 Linux
==========


Téléchargement sous Linux
---------------------------
Dans un terminal, écrire:

    JUCE_PROJ="$HOME/c++/musique/JUCE_fred" # select your directory here
    PROJECT="Template";

	cd $JUCE_PROJ/$PROJECT;

    git clone https://gricad-gitlab.univ-grenoble-alpes.fr/faurefre/juce_template.git # telecharge projet et cree repertoire juce_template

1.1 Compiler sous Linux 
-----------
Dans un terminal, écrire:


    JUCE_PROJ="$HOME/c++/musique/JUCE_fred" # select your directory here
    PROJECT="Template";
    REP="juce_template";

	cd $JUCE_PROJ/$PROJECT;

	rm -rf build; # optionnel, detruit anciens
	mkdir build;

	cd build;
	

    JUCE_DIR=$JUCE_PROJ/JUCE
    #cmake  -DCMAKE_BUILD_TYPE=Release ../$REP; # version Release mais compilation plus lente
    cmake  ../$REP;  # version debug mais compilation + rapide
    
    cmake --build . --  -j$(nproc); # cat /proc/cpuinfo 



    

1.2 Execution sous Linux
-----------
Dans un terminal, écrire:

    JUCE_PROJ="$HOME/c++/musique/JUCE_fred" # select your directory here
    PROJECT="Template";
    REP="juce_template";

    $JUCE_PROJ/$PROJECT/build/"$PROJECT"_artefacts/Standalone/Fred_$PROJECT






1.3 Poser le projet sur gitlab depuis Linux
------------------------



à partir de la deuxieme fois, dans un terminal, écrire:



    JUCE_PROJ="$HOME/c++/musique/JUCE_fred" # select your directory here
    PROJECT="Template";
    REP="juce_template";

    cd  $JUCE_PROJ/$PROJECT/$REP;
    rm -rf Builds JuceLibraryCode # created by projucer
    find . -type f \( -name '*~' \) -delete # supprime les fichiers temporaires inutiles dans les sous repertoires
    git add -A # ajoute toutes les modifs
    git commit -a  -m "mise a jour"
    git push






1.4 fabriquer com.h et com.cc avec makef sous Linux
---------------- 


    PROJECT="Template"; 	REP="juce_template";
    ~/c++/makef/makef ~/c++/musique/JUCE_fred/$PROJECT/$REP/Source  editor/PluginEditor.cc  ~/c++/musique/JUCE_fred/$PROJECT/makef.config    main   JUCE;
    rm -rf ~/c++/musique/JUCE_fred/$PROJECT/$REP/Source/editor/Makefile*;
    rm -rf ~/c++/musique/JUCE_fred/$PROJECT/$REP/Source/editor/README_tmp;


1.5 preparation de makef sous Linux
-----------------

    cd ~/c++/makef;
    cmake .
    cmake --build .



