// -*- mode:C++ ; compile-command: "make all" -*- 

/* 1997. version 2017, 2023.  Programme pour creer automatiquement le fichier makefile pour compiler du c++
   ensuite
   ce programme sert a creer un fichier makefile automatiquement.
   en partant d'un fichier "nomfichier.cc" qui contient le main().


Exemple avec JUCE:
==================


Commande 1: compile makef et cree programme (rm: main is not important here)
----------------
cd ~/c++/makef; make all; 	~/c++/makef/makef ~/c++/makef/example/JUCE/Essai/Source  PluginEditor.cc  /home/faure/c++/makef/example/JUCE/Essai/Source/makef.config    main   JUCE  # step 1 for JUCE

commande 2: compile programme test et execute
---------------
cd ~/c++/makef/example/JUCE/Essai/Builds/LinuxMakefile/; make; cd ~/c++/makef/example/JUCE/Essai/Builds/LinuxMakefile/build;   ./Essai # step 2 for JUCE


Rem: rajouter "make clean" si on change des propriétés du plugin (le nom etc):
    VST3, AU, StandAlone

ou executer avec juce_host ou Ardour





Exemple avec ROOT:
==================

step 1: compile makef et cree programme
-----------------------------------------
cd ~/c++/makef; make all; 	~/c++/makef/makef ~/c++/makef/example  main.cc  /home/faure/c++/makef/makef.config main  g++   # step 1 for ROOT




step 2: compile programme test et execute
-----------------------------------------------
cd ~/c++/makef/example;  make clean;  make all; ./main;  # step 2 for ROOT


autre exemple avec ROOT:
==============

cd ~/c++/makef; make all; 	~/c++/makef/makef  ~/c++/syst_dynamiques/kuramoto_on_S1   main.cc  /home/faure/c++/makef/makef.config main  g++   # step 1 for EX

cd  ~/c++/syst_dynamiques/kuramoto_on_S1; make clean; make all; ./main;  # step 2 for EX







Exemple avec EMCC:
==================

step 1: compile makef et cree programme
-----------------------------------------
@@ to write 

step 2: compile programme test et execute
-----------------------------------------------
@@ to write 




========

Compilation
------------
cd ~/c++/makef; make all;



Example d'utilisation:
-------------------------
~/c++/makef/example/main.cc


Utilisation
-------------

   Pour l'utiliser, il faut
   ---------------
   1) ecrire le fichier 
         makef.config
		 (voir des exemples)

   2) lancer : 
       makef repertoire nomfichier.cc  makef.config    <nom_executable>  g++
       ou
	   makef repertoire nomfichier.cc  makef.config    <nom_executable>  emcc
       ou
	   makef repertoire nomfichier.cc  makef.config    <nom_executable>  JUCE



   3) ensuite pour compiler (lancer le Makefile), il
   il faut faire :
   make clean   (pour detruire les fichiers .o precedants)
   make all


   voir par exemple le script "compp"







Il y a 3 possibilité pour lancer le code: 1) g++ Root, 2) c++ JUCE 3) emcc  


1) Compilation et execution  en C++ avec Root
------------------------------------------------

. ~/bin/.mon_bashrc; compp ~/c++/makef/example main.cc main g++


Pour executer, dans un terminal,
./main



2) Compilation et execution  en C++ avec JUCE
------------------------------------------------
Attention:
     on utilise l'extension .cc et non pas .cpp
	 pour fabriquer le Makefile on utilise JUCE et non pas makef

la premiere fois, pour creer le projet,
.....................    
    - Lancer juce (dans un terminal)
       - creer new project, Basic Plugin, choisir Project Name, Exporter: linux et MacOs
       - View/Show Project settings  , plugin charactersitics: Midi in,out,Effect, VST3, AU, StandAlone
	        en bas dans la rubrique Header Search Paths ,
			ajouter:
			/home/faure/c++/Utils
			/home/faure/c++/makef/example/JUCE/Essai/Source
	   
			Sauver,
			- changer l'extension .cpp en .cc par Rename

	   - dans les fichiers .h et .cc changer le nom des classes par Editor et Processor et l'objet processor
	 
         modifier les fichiers d'après les exemples:
		 ~/c++/makef/example/JUCE/Essai/Source/PluginEditor.h, .cc PluginProcessor.h, .cc 


		-dans le logiciel juce (Projucer) faire dans le repertoire Source:
		    Add new Cpp and Header files: com.h
		  -> cela cree des fichiers com.h et com.cpp que l'on va modifier ensuite.
               renomer com.cpp en com.cc

		  Sauver le projet (-> cela ecrit le Makefile)

		  rajouter de meme les fichiers .h et .cc du projet
		  
    - copier un fichier makef.config dans le repertoire 
	       ~/c++/makef/example/JUCE/Essai/Source

Pour fabriquer automatiquement les fichiers com.h et com.cc: 
.....................	
	~/c++/makef/makef ~/c++/makef/example/JUCE/Essai/Source  PluginEditor.cc  /home/faure/c++/makef/makef.config main   JUCE

Pour compiler, dans le repertoire ~/c++/makef/example/JUCE/Essai/Builds/LinuxMakefile ecrire:
...................
  cd ~/c++/makef/example/JUCE/Essai/Builds/LinuxMakefile/; make;

Pour executer, dans le repertoire 
....................
cd ~/c++/makef/example/JUCE/Essai/Builds/LinuxMakefile/build;   ./Essai







Compilation et execution  en JS:
------------------

. ~/bin/.mon_bashrc; compp ~/c++/makef/example main.cc main emcc


lancer un serveur web dans une console, meme repertoire que ce projet:


xterm -e python3 -m http.server --bind 127.0.0.1 8000 &

firefox http://localhost:8000/index.html &

ou

google-chrome http://localhost:8000/index.html &





ou (si python 2)

xterm -e python -m SimpleHTTPServer 8000 &


dans une autre console, et meme repertoire, lancer:

firefox http://localhost:8000/index.html

ou

google-chrome http://localhost:8000/index.html


Rem: you can change 8000 by 8080 or another port number.


Rem:
to decode  emcc compilation  messages use c++filt, ex: 
 c++filt  '_ZplRKNSt3__26vectorIiNS_9allocatorIiEEEES5_'
 gives
 operator+(std::__2::vector<int, std::__2::allocator<int> > const&, std::__2::vector<int, std::__2::allocator<int> > const&)





Abstract: 
==========

Ecrire a la main:
--------------------
dans ce projet on a ecrit à la main, seulement:
 les fichiers:   


 fichier.h   : fichier principal qui contient la plupart des instructions pour makef
 fichier.cc  : ce fichier avec les fonctions

et si on choisit le  mode emcc, alors dans ce repertoire, il faut creer un lien symbolique javascript  vers le repertoire Utils/javascript

il faut aussi le fichier de configuration:  makef.config

Configurer a la main:
----------------------
fichier de config: makef.config

dans le fichier  makef.config (en derniere ligne) on choisit le mode de compilation :
 gcc ou  emcc, cad sortie JavaScript (JS) ou JUCE
rem: il suffit de remplacer dans la ligne non souhaitee
 "compilation" par "ompilation" 
"librairies et include  =" par "ibrairies et include  ="
et les librairies souhaitees


Sortie
========

Le script de compilation,  ecrit automatique com.cc et com.h et index.html (si emcc) qui sont une fenetre de commandes.


----------------------------

Doc: 
======
cf makef.cc
et eventuellement cours_c++.lyx sur ma page web.



Rem
-----
dans le code c++, utiliser si besoin:

#if !defined(__EMSCRIPTEN__)
...
#endif

#if !defined (JUCE_APP_VERSION)
...
#endif

#if defined (_ROOT_)
...
#endif

pour les parties destinees  a g++.à ROOT, EMCC ou JUCE, selon.





//----------------------


Resultat
--------
 -En G++:  Une fenetre de commande GUI est lancee dans un autre thread (process) "com" et utilise root.

 - En EMCC:  Une fenetre HTML  avec widgets de la librairie interfaces.js

 - Cette fenetre  contient tous les widgets des variables (selectionnees) des classes que utilise le projet main().

    avec 
	- un menu, 
	- une zone commune: ZC
	- des zones de tabs: ZT1, ZT2, ...

	Les widgets sont placés à la suite horizontalement dans la zone demandee.

- En JUCE: une appli/Plugin


Exemple complet:
-------------------

 ~/c++/makef/example/main.cc


ou pour JUCE:

 ~/c++/makef/example/JUCE/Essai/Source/  

Technical details,
-------------------

les valeurs de ces widgets sont en permanence couplées à la variable c++.
      Pour cela il y a un pointeur pour chaque classe, ex: pointeur  p_C1 pour la classe C1


      - Dans le code,  ecrire:

   		   #include  <REPERTOIRE/com.h> 
		   
          pour pouvoir ensuite utiliser le pointeur p_com->

      - Si un widget est activé (ou changé), le process "com" change les variables  du main avec une protection prealable de type mutex.
	  
	  - depuis le process "main", on appelle  explicitement p_com->Met_a_jour() pour que l'affichage de "com" corresponde aux variables de  "main".

	  - optionnellement, le process "com" appelle Met_a_jour() de facon periodique (tous les 0.1 sec), pour eviter cet appel explicite.

	  - dans le programme "main", avant/apres d'acceder aux variables partagees, il faut mettre/ enlever le mutex mtx_com: 	  mtx_com->lock(); 	  mtx_com->unlock(); 

	  - si besoin, on a acces aux fenetres de commandes par le pointeur Com *p_com;




Fichiers crees automatiquement
------------------------------------

  fichiers c++: com.cc, com.h dans le meme repertoire que fichier.h  qui sont des classes c++ d'un  panneau de commandes,


Documentation 
-------------

Zones pour placer le widget
--------------------

ZC: zone commune
ZT: zone tabulation
nl: newline

	ex:
	double x1=4; // make_gui = nl  N(ZC, "x1=")  
	double x1=4; // make_gui = nl  N(ZT("tab1"), "x1=")







-  Sous Sections et Sous-Sous-Sections:
 
   optionnellement, dans le constructeur d'un objet declare, mettre la declaration des titres:

	p_com->titles_tabs = { "1. Section",
						   "1.1 sous section",
						   "1.1.1 sous-sous section",
						   "1.1.2 sous-sous section",
						   ...


  et de facon equivalente, dans la declaration de la classe,  utiliser _ et __ (deux),  par exemple:

	double X1 = 4.1 ; // make_gui = nl  N(ZT("1"), "X1")  texxt = "text on the left, number double:"  
	double X1b = 4.1 ; // make_gui = nl  N(ZT("1"), "X1b")  texxt = "text on the left, number double:" 
	double X2 = 1 ; // make_gui = nl  N(ZT("1__1"), "X2")  

	//--- sub-sub-sections
	int b111 = 2; // make_gui = nl  N(ZT("1__1__1"), "b111")
	int b112 = 2; // make_gui = nl  N(ZT("1__1__2"), "b111")
	
   l'ordre n'est pas important. Les tabs sont classés par ordre alphabetique.









commandes speciales
--------------------

- ST : demarrage d'une fonction f()  dans le constructeur de l'interface, i.e. dans com::com()
ex: 
	    void f() ; // make_gui = ST

special G++:
...............

- TT : "TTimer" ou "callback".  appel regulier d'une fonction f()  toutes les 100ms. Utilise <TTimer.h> de  root
     rem: il peut y avoir plusieurs call back dans le programme.
         Ils sont dans le meme thread.  
ex: 
	    void f() ; // make_gui = TT(100)



options generales (dans l'ordre)
--------------------------------

- nl: "Newline",	On peut revenir à la ligne si on commence par l'instruction "nl":
	ex:  double x1=4; // make_gui = nl  N(ZT("tab1"), "x1=")

//.............
event  = "mouseDown, mouseMove, mouseWheelMove, keyPressed" : une de ces options dans ordre quelconque. Pour JUCE, et le widget "Window", cela va créer la detection de la souris ou du keyboard. Pour l'utiliser il suffit de ecrire dans son code,  la fonction: (remplacer NomClasse et NomFonction par les noms adequates)
     void TCanvas_NomClasse_NomFonction::mouseMove(const MouseEvent &event)
    {
   	   cout<<"mouseMove, x="<<event.getMouseDownX () <<", y="<<event.getMouseDownY () <<endl;
	}
(cf par exemple, tunplot.cc)


//.............
texxt = "text:"   : text qui est ecrit avant le widget
   	ex:  double x1=4; // make_gui = nl  N(ZT("tab1"), "x1=") texxt = "x1 = "


//.............
attach_function = "f" : la  fonction membre void f() sera executee chaque fois que le widget est activé. Cela permet d'effectuer certaines taches comme synchronisation .. 
        	ex:  double x1=4; // make_gui = nl  N(ZT("tab1"), "x1=") attach_function = "f"

//.............
midicontrol="TINYCONTROL, M=0xB0, C=0x3, R=[0,3.]"  :  La variable double ou int est controllee par un controller midi, de nom = TINYCONTROL, Message midi M=0xB0 (i.e. control change on channel 0), Controller=0x3, the value 0->127 is mapped to the range=[0,3.] for the variable

   ex: 	double x  ; // make_gui =   N(ZC) midicontrol="TINYCONTROL, M=0xB0, C=0x3, R=[0,3.]"  help="from control change C. V=0->127 is mapped to range R"
   ex:  double x  ; // make_gui =   N(ZC) midicontrol="TINYCONTROL, M=0x90, C=0x3, R=[0,3.]" help="from note on message, key=C. V=0->127 is mapped to range R"
   ex:  double x  ; // make_gui =   HS(ZC) midicontrol="TINYCONTROL, M=0xB0, C=0x3, R=[0,3.]"  help="from control change C. V=0->127 is mapped to range R"
   ex:  int a;     // make_gui =   C(ZC) midicontrol="TINYCONTROL, M=0x80, C=0x3, "  help="from note off message -> switch from 0 to 1"
   ex:  int a;     // make_gui =   C(ZC) midicontrol="TINYCONTROL, M=0x90, C=0x3, "  help="from note on message -> switch from 0 to 1"
   ex:  void f();     // make_gui =   B(ZC, "button") midicontrol="TINYCONTROL, M=0x90, C=0x3, R = [20,50]"  help="from note on message -> function called if vel is in range R"
   ex:  void f();     // make_gui =   B(ZC, "button") midicontrol="TINYCONTROL, M=0xB0, C=0x3, R = [20,50]"  help="from  control change message -> function called if vel  is in range R"

      

//.............
help ="comment text"   : texte d'aide associe au widget.
           	ex:  double x1=4; // make_gui = nl  N(ZT("tab1"), "x1=") help = "this is a number"



//...........
JUCE: les parametres servent a l'automation seulement ou le changement de variables via des controlleurs.
     Pour save/load, on utilise directement les variables c++.
      pour une variable c++, on fait save/load par default, sauf si il y a l'option finale _no_save_


_param_  : (for JUCE) this widget will  be exposed as  a parameter for the DAW.
         only the following widget can be  exposed as a parameter  for the DAW:
		"L", "LB", "HS",   "INC", "C" , "Color"

		Rem : this is widget for which the range is well defined)
              the range can not be changed dynamically. For ex for "L" and "LB".


_no_save_ : (JUCE)  pour une variable c++, on fait save/load par default, sauf si il y a l'option finale _no_save_



commandes sans objet C++
-------------------------

MS : "Menu System", permet de lancer une commande par system("command"), à partir du Menu
    Cela peut etre utile pour ouvrir une documentation pdf par la commande: evince ~/doc.pdf ou lyx ~/doc.lyx

	ex: 
     // make_gui = MS("nom_colonne_du_menu","texte_dans_le_menu", "command") 
     // make_gui = MS("doc","doc.lyx", "lyx doc/doc.lyx &") 
     // make_gui = MS("doc","doc.pdf", "evince doc/doc.pdf &") 



rem: cf aussi appel menu  M() ci-dessous

LINK : permet de lier des fichiers et arborescences lors de la fabrication de fichier d'exportation  zip 
 
    ex: pour un fichier depuis le repertoire courant, on met un point ./. Pour un dossier, on rajoute / a la fin
     // make_gui = LINK("./doc/tuto.pdf")    
	 // make_gui = LINK("./doc/")    
    ex: pour un fichier ou dossier depuis le repertoire Utils/, on ne met pas de point ./
     // make_gui = LINK("musique/README.md")
     // make_gui = LINK("musique/doc/")

TITRE : titre de la fenetre de commandes
     ex: make_gui = TITRE("Titre Version 10.10")


HLINK : ajoute un texte avec hyperlien, cela fonctionne avec JUCE. 
     ex: // make_gui =  HLINK(ZC, "Help",  "https://www-fourier.ujf-grenoble.fr/~faure/Modelisation_musicale/tonnetz_doc/index.html")  help = "Help for tonnetz online. This is version 12/4/2023 20:22"



Attention: comme le reste il faut le mettre dans une declaration de class, meme si cela n'a pas de sens.


Commandes avec objets c++
---------------------------
chaque zone peut contenir des widgets avec le format suivant:


     - N: Numerique entre/sortie  pour int, double
	    ex: 
		   int a; //  make_gui = N(ZC,"a=")
		   double x1=4; // make_gui = N(ZT("tab1"), "x1=")

	 - T : Texte entre/sortie      pour string
	    ex:
         string text = "hello" ; // make_gui = T(ZT("tab1"))

	 - HS: Horizontal Slider entre/sortie pour int/double. On donne min,max
	    ex: 
		double x = 1 ; // make_gui = HS(ZT("tab1"), 0, 5, 0.1) // with step 0.1
		double x = 1 ; // make_gui = HS(ZT("tab1"), 0, 5) // with step 1

	    ex: 
		double x1 = 1, x2= 3 ; // make_gui = HS(ZT("tab1"), 0, 5, 0.1)  help="with step 0.1"
		double x1 = 1, x2= 3 ; // make_gui = HS(ZT("tab1"), 0, 5)  help="with step 1"

	    ex: 
		double x1 = 1, x2= 3, x3= 4 ; // make_gui = HS(ZT("tab1"), 0, 5, 0.1)  help="with step 0.1"
		double x1 = 1, x2= 3, x3= 4 ; // make_gui = HS(ZT("tab1"), 0, 5)  help="with step 1"




	 - (only in JUCE) 
      INC: Increment buttons for int/double. On donne min,max and increment value
  	    ex: 
		double x = 1 ; // make_gui = INC(ZT("tab1"), 0, 5, 0.1)  // with step 0.1
		int    x = 1 ; // make_gui = INC(ZT("tab1"), 0, 5)  // with step 1


	 -(not yet)  VS: Vertical Slider:   entre/sortie pour int/double

	 - PB: Progress Bar: sortie pour int,double
	   ex:
	    double y = 5 ; // make_gui = PB(ZT("tab2"), 0,5)


	 - C : Check entree/sortie pour int x=0,1
	   ex: int opt = 1 ;  //make_gui = C(ZT("tab2"), ":opt")

	 - L : Liste entre/sortie pour int x \in [0,N-1] 
	  ex:
	  int choix = 2 ; //make_gui = L(ZT("tab2"), {"a","b","c","d"}) 


	  ex: plus dynamique
	  int choix = 2 ; //make_gui = L(ZT("tab2"), liste) 
	  vector<string> liste = {"a", "b", "c"};

       si on change la liste, on remet à jour le widget par:

	   p_com->Met_a_jour_NomClass_NomObject();


	 - LB : Liste Box entre/sortie pour int x \in [0,N-1] 
	  ex:
	  int choix = 2 ; //make_gui = LB(ZT("tab2"), {"a","b","c","d"}) 
	  ex:
	  int choix = 2 ; //make_gui = LB(ZT("tab2"), liste) 
	  vector<string> liste = {"a", "b", "c"};

	 - B : Bouton d'appel pour fonction void f()
	    void f() ; // make_gui = B(ZC,"C1_f")

	 - M : Menu d'appel pour fonction void f()
	    void g() ; // make_gui = M("menu2","C1_g")



widgets only available with G++ Root or JUCE
---------------------------

  	 - File : Nom de fichier. Ouvre dialogue pour choisir un nom de  fichier.
	   ex: 
        string text = "toto.txt" ; //make_gui = File(ZT("tab1"), "")
        string text = "toto.txt" ; //make_gui = File(ZT("tab1"), "'texte','*.txt', 'code','*.cc', 'All','*' ")
		 i.e. en option le nom et le type des fichiers, par paires

  	 - Dir : Nom de  repertoire. Ouvre dialogue pour choisir un nom de repertoire.
	   ex: 
        string text = "toto.txt" ; //make_gui = Dir(ZT("tab1"))


		 

    - Color : choix d'une couleur
         ex:
        
		int choix_color = 0;  //make_gui =    Color(ZT("Midi_ports")) texxt = " color:"  attach_function = "af_choix_color" help = " color of the connection" 
	     void af_choix_color(); // fonction appelee si changement des valeurs


widgets only available with JUCE
---------------------------

    - Editor: put a button to open a window this is an editor for a string
	ex:
	string text = "abc"; // make_gui =  Editor(ZC, "TEXT")
   	           where "Show TEXT" will be the text on the button.


    - Window:  put a button to open an external window to draw in it.
	ex: 
	void Dessin(juce::Graphics& g); // make_gui =  nl Window2(ZC, "Tunplot", 400, 300) event="mouseDown, mouseMove, mouseWheelMove" help="a window"
	TCanvas c; // window associated to Dessin()


    - Window2:  There is an internal window. Also a button to shift to an external window to draw in it.
	ex: 
	void Dessin(juce::Graphics& g); // make_gui =  nl Window2(ZC, "Tunplot", 400, 300) event="mouseDown, mouseMove, mouseWheelMove" help="a window"
	TCanvas c; // window associated to Dessin()



widgets only available with EMCC
--------------------------------
	
- Texte html :  afin de rajouter du code html dans une zone. Rem: il est utile d'y mettre un identifiant pour pouvoir y rajouter du texte après.
   ex: 
   	// make_gui = HTML(ZC, texte_html) 
	string texte_html = "<span id='zone_texte'> Some <b>html</b> code <br><br> </span>"; 






Remarques special G++
----------------------


   voir guitest.cc et guitest pour les possibilites et l'utilisation.  

 acces direct aux widgets depuis le code c++:
  ..........................................
   par exemple, si dans la classe C on a

    int choix = 2 ; //make_gui = L(ZT("tab2"), {"a","b","c","d"}) 

alors  dans le fichier com.h, il y a l'objet
TGComboBox *C_choix;

ainsi on peut ecrire par exemple:

C_choix->Select(2);
int s = C_choix->GetSelected();

B->SetState(kButtonDown);
B->SetState(kButtonUp);

T->SetText(string.c_str());


N->SetNumber(x);

//... attention: les commandes suivantes doient etre fait dans le meme thread que celui de l'interface!

L->AddEntry(string.c_str(),i); 
L->Select(i);
L->RemoveEntry(i);  // i>=1
L->RemoveAll(); 
L->Resize(150, 20);
L->GetTextEntry()->GetText()

mais si on change les tailles, il faut recalculer l'ensemble: ex:

	p_com->Midi_choix_port_in->Resize(len, 20);  // ajuste longueur du TGComboBox
	p_com->MapSubwindows(); // il faut tout recalculer la fenetre
	p_com->Resize();
	p_com->MapWindow();


//.... activer/desactiver des widgets:
  pour un widget associe a un objet:
   Class::object, on peut ecrire:

   p_com->Class_object->setEnabled(true);
   p_com->Class object->setEnabled(false);


//.. activer/desactiver des tabs:
   si un tab porte le nom complet: "1 External Synthe" (avec des espaces) alors on peut l'activier/desactiver par: 
       p_com->p_Tab_1_External_Synthe->setEnabled(true);
       p_com->p_Tab_1_External_Synthe->setEnabled(false);


//.; changer la couleur ou autre d'un widget: ici check C()
		p_com->Pitch_opt_detect_pitch->setColour( ToggleButton::tickColourId ,   Colours::pink);


//... activer une commande de l'interface, par exemple pour un button (ne marche pas?)
L->Clicked();

//---- pour rafraichir la fenetre de commandes:
	p_com->Met_a_jour();

	gSystem->ProcessEvents();  // ne doit etre appeler que par le thread du GUI.

//---------------


- PB: rajouter couleur et style (bloc) et precision apres virgule
       fH_N_notes->SetBarColor("blue");

       fH_N_notes->SetFillType(TGProgressBar::kBlockFill);
    	fH_Diss->ShowPosition(kTRUE,kFALSE,"Dissonance: %.2f");



*/










/*
Faire:
==========
juin 2019;



En c++,   
---------
  
   Ajouter widget html

       avec la classe TGHtml qui permet d'afficher du texte html. Cf calendar.C


En emcc,
---------
   ajouter choix couleur
   ajouter File
  ajoute TT: utiliser emscripten_set_interval avec #include <emscripten/html5.h>


	 continuer a mettre au point les widgets avec javascript.



janvier 2019:


 general
---------------


- Trouver une solution pour eviter d'ecrire dans le code
   		   #include  <REPERTOIRE/com.h> 

   qui depend du repertoire et qui depend que l'on a l'option make_gui



- rajouter destructeur de la forme:

Com_Tuning::~Com_Tuning()
{
	Cleanup();
}


- OPtionnellement, lancer  les fonctions dans un autre thread, afin de ne pas bloquer l'interface. voir par exemple tuning.cc Tuning::Start()
  Pour cela il faut declarer (et memoriser) la variable de thread dans com.h.
   Attention: il  faut une protection, pour ne pas relancer un thread si le precedent n'est pas termine.


Nouveaux widgets:
----------------

- H1 : Histogramme 1D pour  vector<int>, vector<double>, vec
- H2 : Histogramme 2D pour  vector<vector<int>>, vector<vector<double>>, mat
- Liste de CheckBox  pour vector<int> a; avec a[j]=0,1

- KC: clavier circulaire: vector<int> kv; kv[j]=0,1, j=0->11   (il faut creer ce widget en c++)
- KV : clavier droit : vector<int> kv; kv[j]=0,1, j=0->127



- possibilite de plusieurs widget pour une variable, avec le symbole & 




 */


int verbose = 0;

int opt_makeh = 0; //0 ,1  : si ecriture automatique des fichiers .h qui manquent
int opt_makegui = 0; //0 ,1  : si ecriture automatique d'une fenetre de commmandes gui en c++
int opt_make_zip = 0; //0 ,1  : si ecriture automatique d'une archive exportable du code .zip

//*****************************************************************
#include <iostream>
using namespace std;

#include <fstream>
#include <string>
#include <stdlib.h> // pour system
 

#include <vector>
#include <algorithm>
//#include "fichiers/fichiers.h"

#include <vector>
#include <sstream>

// declaration
string traite_cc(string nom_rep_cc, string  nom_fichier_cc,  int opt_rep);

// variables globales
string chaine_objets;

string src2; // ex: essai.cc
string rep_src, rep_src2;
string fliste; // liste des fichiers traites
vector<string> liste_files_h_cc; // liste des fichiers .h .cc .c du projets
vector<string> liste_files_main; // liste des fichiers du repertoire du main()
vector<string> liste_files_linked; // liste des fichiers ajoutes a zip  dans Utils/
vector<string> liste_files_linked_main; // liste des fichiers ajoutes a zip, dans le rep du main()

string makefile;

string comp_name; // compilateur "g++" ou "emcc"
string ext_o; // extension, sera ".o" ou ".bc" selon le compilateur

string ext_cc = ".cc"; // extension, sera ".cc" ou ".cpp" ou ".c" selon le compilateur


int compteur;

//=========================
/*
Input: string in hexadecimal
output: int
 */
int stringhexa_to_int(string s)
{
	stringstream ss;
	ss<<hex<<s;
	int x;
	ss>>x;
	return x;
}


//================
// return 1 if s1  contains s2
bool contains(const string s1, const string s2)
{
	return (s1.find(s2) != string::npos);  //  if s1 contains s2
}


//===================================
// remplace 'search' par 'replace' partout dans la chaine 'subject'. Output:  'subject'
void ReplaceStringInPlace(string& subject, const string& search, const string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos)
	{
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

/*#################################################
  petite routine qui va pointer apres le prochain caractere '=' */
int prochain(ifstream & fich, int verbose=0)
{
	char caract;

	do {
		fich.get(caract);
	}
	while ((caract!='=')&&(!fich.eof()));

	if (fich.eof())
	{
		if(verbose)
			cerr<<" makef.cc :: prochain(). erreur : fin de fichier et = non trouvee..\n";
		return 0;
	}
	else
		return 1;
}

/*#################################################
  petite routine qui va pointer apres la prochaine chaine donnee
  renvoit 0 si pas trouve 1 si trouve  */
int  prochain(ifstream & fich, string chaine, int verbose=0)
{// unsigned char caract;
	char caract;
	int n,i;

	n=chaine.length();

//cout<<"recherche dans fichier, la chaine:"<<chaine<<endl;
	do
	{
		// cherche le premier caractere de la chaine
		do {
			fich.get(caract);

			//	   cout<<"."<<caract<<flush;
		}
		while ((caract!=chaine[0])&&(!fich.eof()));


// verifie si il y a le reste de la chaine
		i=0;

		if(!fich.eof())
		{
			do
			{ i++;
				fich.get(caract);
				//cout<<"-"<<caract<<flush;
			}
			while((chaine[i]==caract) && (i<(n-1)));
		}
	}

	while(!(
			  fich.eof()  || (
				  (i==(n-1))  &&   (chaine[n-1]==caract)
				  )
			  ));

	if (fich.eof())
	{
		if(verbose)
			cerr<<"makef.cc :: prochain(.,.). Resultat : fin de fichier trouvee..et chaine="<<chaine<<" non trouvee ..\n";
		return 0;
	}
	else return 1;
}


//==========================
// Affiche vector
ostream & operator <<(ostream & sortie,  const vector<string> & V)
{

 sortie<<"["<<flush;

  for(int i=0;i<V.size();i++)
    {
      if(i>0)
	sortie<<","<<flush;
      sortie<<V[i]<<flush;
    }
  cout<<"]"<<endl;

    return sortie;
}

//==========================
// Affiche vector
ostream & operator <<(ostream & sortie,  const vector<vector<string> > & L)
{
  for(int l=0;l<L.size();l++)
    {
      sortie<<L[l];
    }

    return sortie;
}



//==========================
// Affiche vector
ostream & operator <<(ostream & sortie,  const vector<int> & V)
{

 sortie<<"["<<flush;

  for(int i=0;i<V.size();i++)
    {
      if(i>0)
	sortie<<","<<flush;
      sortie<<V[i]<<flush;
    }
  cout<<"]"<<endl;

    return sortie;
}

//===============================
// fonctions pour make_gui

//===============
// enleve les espaces ou tabulation  du debut et fin de chaine
void Enleve_espaces(string &s)
{
	while((s[0] == ' ') || (s[0] == '\t'))
		s.erase(0,1);
	while((s[s.size()-1]==' ') || (s[s.size()-1]=='\t'))
		s.erase(s.size()-1,1);
}
//===================
// renvoit true si l est absent de la liste L
template<typename A>
bool is_not_in(A l, vector<A> L)
{
	return( find(L.begin(), L.end(), l) ==  L.end() );
}




/*=======================================
 Decompose la chaine " .. | .." en sous chaines des caractères entre les '|' =signe
ex:
s = "aa|bb|cc|"
signe = "|"
sortie = "aa" , "bb", "cc"
*/
vector<string> Decompose(string s, string signe)
{
    vector<string> Ls;
    
//    size_t pos=ligne.find(signe); // cherche le premier |
	//  ligne=ligne.substr(pos+1); // garde la suite seulement
	//  ligne=ligne.substr(0,pos); // garde avant
	
    while(s.find(signe) != string::npos) // il reste au moins une occurence du  signe
    {
		size_t pos = s.find(signe);
		string s1 =  s.substr(0,pos); // avant le signe
		s=  s.substr(pos + signe.size()); // apres le signe

		if(s1.size()>0)
		{
			Enleve_espaces(s1);
			Ls.push_back(s1);
		}
		
    }

	if(s.size()>0)
		Ls.push_back(s); // rajoute la fin
	
    return Ls;
}



//======================
/* entree
ex:
   s = "A","B"
   delim = "__"
sortie: 
  "A__B"
 */
string Label(vector<string> s, string delim="__")
{
		int k = s.size()-1;
		
		//... cree label
		string label = s[0];
		for(int k2=1; k2<=k; k2++)
			label = label + delim + s[k2];
//		cout<<"  label = "<<label<<endl;
		return label; 
}


//================
class Infos
{
public:
	string nom_fichier="", nom_class="", ligne="";
	string type ="", nom ="", val ="", nom2 ="", val2 ="", nom3 ="", val3 ="";
	int opt_nl=0; // option newline
	int opt_param = 0; //  a parameter
	int opt_no_save = 0; //  no save/load in JUCE
	string widget="", zone="", texte="", nom_tab="", xmin="", xmax="", step="",  help="", attach_function="", text="", object="";
	string Id="", nom_obj="";

	int ID=-1;
	
	// Idj is  index of the tab that contains the widget:
	// ex: p_Tab_"<< Get_Tab_name(Idj) gives   p_Tab_3_Audio1_Audio_in
	int Idj=-1;

	
	vector<string> L_l; // pour Liste


	int W,H; // size of window
	
	string URL;
	
	//... for midicontrol
	string midicontrol=""; // total string
	string midi_name="";
	int midi_M=-1, midi_C=-1;
	double midi_R1=-1, midi_R2=-1; // range

	int mouseDown =0, mouseMove =0, mouseWheelMove=0, keyPressed=0; // for mouse keyboard events on windows
	
	//.. position on the screen
	int x=0, y=0, w=0, h=0;

	
};

ostream & operator <<(ostream & s,  const Infos & inf)
{
	s<<"---------------"<<endl;
	s<<"   nom_fichier  = \""<<inf.nom_fichier<<"\""<<endl;
	s<<"   nom_class  = \""<<inf.nom_class<<"\""<<endl;
	s<<"   ligne  = \""<<inf.ligne<<"\""<<endl;
	s<<"   ..............."<<endl;
	s<<"   type  = \""<<inf.type<<"\""<<endl;
	s<<"   nom  = \""<<inf.nom<<"\""<<endl;
	s<<"   val  = \""<<inf.val<<"\""<<endl;
	s<<"   nom2  = \""<<inf.nom2<<"\""<<endl;
	s<<"   val2  = \""<<inf.val2<<"\""<<endl;
	s<<"   nom3  = \""<<inf.nom3<<"\""<<endl;
	s<<"   val3  = \""<<inf.val3<<"\""<<endl;
	s<<"   opt_nl  = \""<<inf.opt_nl<<"\""<<endl;
	s<<"   opt_param  = \""<<inf.opt_param<<"\""<<endl;
	s<<"   opt_no_save  = \""<<inf.opt_no_save<<"\""<<endl;
	s<<"   ..............."<<endl;
	s<<"   widget  = \""<<inf.widget<<"\""<<endl;
	s<<"   zone  = \""<<inf.zone<<"\""<<endl;
	s<<"   texte  = \""<<inf.texte<<"\""<<endl;
	s<<"   nom_tab  = \""<<inf.nom_tab<<"\""<<endl;
	s<<"   xmin  = \""<<inf.xmin<<"\""<<endl;
	s<<"   xmax  = \""<<inf.xmax<<"\""<<endl;
	s<<"   step  = \""<<inf.step<<"\""<<endl;


		
		
	s<<"   help  = \""<<inf.help<<"\""<<endl;
	s<<"   attach_function  = \""<<inf.attach_function<<"\""<<endl;
	s<<"   text  = \""<<inf.text<<"\""<<endl;
	s<<"   object  = \""<<inf.object<<"\""<<endl;

	s<<"   Id  = \""<<inf.Id<<"\""<<endl;
	s<<"   Idj  = \""<<inf.Idj<<"\""<<endl;
	s<<"   ID  = \""<<inf.ID<<"\""<<endl;
	s<<"   nom_obj  = \""<<inf.nom_obj<<"\""<<endl;
	s<<"   URL  = \""<<inf.URL<<"\""<<endl;

	for(int i=0; i<inf.L_l.size(); i++)
		s<<"   L_l["<<i<<"]  = \""<<inf.L_l[i]<<"\""<<endl;

		
	s<<"   midicontrol  = \""<<inf.midicontrol<<"\""<<endl;
	s<<"   midiname  = \""<<inf.midi_name<<"\""<<endl;
	s<<"   midi_M  = \""<<inf.midi_M<<"\""<<endl;
	s<<"   midi_C  = \""<<inf.midi_C<<"\""<<endl;
	s<<"   midi_R1  = \""<<inf.midi_R1<<"\""<<endl;
	s<<"   midi_R2  = \""<<inf.midi_R2<<"\""<<endl;
	s<<"   mouseDown = \""<<inf.mouseDown <<"\""<<endl;
	s<<"   mouseMove = \""<<inf.mouseMove <<"\""<<endl;
    s<<"   mouseWheelMove = \""<<inf.mouseWheelMove <<"\""<<endl;
	s<<"   keyPressed = \""<<inf.keyPressed <<"\""<<endl;
	
	s<<"   x  = \""<<inf.x<<"\""<<endl;
	s<<"   y  = \""<<inf.y<<"\""<<endl;
	s<<"   w  = \""<<inf.w<<"\""<<endl;
	s<<"   h  = \""<<inf.h<<"\""<<endl;
	s<<"   ..............."<<endl;
	s<<endl;
	return s;
}

//===================

vector<Infos> L_infos;
vector<string> L_noms_classes; // liste des noms de classes
vector<string> L_noms_fichiers; // liste des noms de fichiers contenant des infos
vector<string> L_noms_menus; // liste des noms de menus
vector<string> L_noms_tabs; // liste des noms des zones tab
vector<vector<string>> L_sous_tabs; // liste des noms des zones tab en arborescence
vector<string> L_midicontrol_name; // list of midicontrol requests
vector<int> L_noms_TT; // duree des TTimer demandees
int  HLINK_cpt = 0; // counter  for HLINK

string Titre=""; // titre de la fenetre de commandes

int n_passage =1; // numero de passage.  il faudra 2 passages si opt_makegui=1.

//==============================
// fonction pour make_gui
/*
Entree:
 p_fich: pointeur dans fichier,

Sortie: 
   0: si rien fait
   1: si ok

Action
-----


Algo:
-----
dans le fichier on cherche le code c++ de la prochaine class

On extrait les infos pour chaque ligne contenant le texte  "make_gui"

 */
int  Extrait_infos_from_next_class(ifstream  & p_fich,  string nom_fichier)
{


	//---- on recherche le mot clef: 'class' dans une ligne qui ne contient pas ';' (ce serait seulement une annonce comme: class toto;)

	int test =0;
	while(test==0)
	{
		int res = prochain(p_fich, "class "); // res =0 si pas trouve
		if(res==0)
			return 0;

		int  pos = p_fich.tellg(); // -> memorise position  dans le fichier

		string l;
		getline(p_fich, l);// -> l. copie la ligne dans l (sans le code retour a la ligne)
	
		if(verbose>=3)
			cout<<"Ligne l="<<l<<endl;

		if(l.find(";") == string::npos) // si ';' ne se trouve pas dans la ligne
		{
			test = 1;
			if(verbose>=3)
				cout<<" OK."<<endl;
			p_fich.seekg(pos, p_fich.beg); // se replace a la position pos du fichier (begining + pos)
		}
	}
	
	

	//---------------------------------

	if(verbose)
	{
		cout<<"Debut de Fonction Extract_next_class()"<<endl;
		cout<<"----------------------------"<<endl;
	}

	//---------------------------------------------------------------
	//-----Etape  1) extrait chaque ligne du code c++ de la classe -> L_class ---------------
	if(verbose >=2)
	{
		cout<<"------------"<<endl;
		cout<<"## Etape (1)"<<endl;
		cout<<"------------"<<endl;
	}
	
	
	vector<string> L_class;


	//... on extrait la ligne contenant le mot clef 'class'
	
	string t_class; // temporaire pour une ligne
	
	if(verbose)
		cout<<"------"<<endl;

	int cpt=0, cpt_v=0; // compteur des accolades, pour trouver la fin de la classe
	while(p_fich.good())
	{
		char c;
		p_fich.get(c); // -> c
	   
	
		if(c!= '\n' && !iscntrl(c))
		{
			//	cout<<"c='"<<c<<"'"<<endl;
			t_class.push_back(c);
		}
		else if (c == '\n')  // nouvelle ligne
		{
			
			L_class.push_back(t_class);

			if(verbose>=3)
				//	cout<<"ligne "<<L_class.size()<<" t_class="<<t_class<<endl;
				cout<<"ligne "<<L_class.size()<<" L_class[L_class.size()-1]="<<L_class[L_class.size()-1]<<endl;
			
			t_class.clear();
		}

		//.. bilan des acccolades {, } pour detecter la fin de classe
		if(c=='{')
			cpt++;
		else if(c=='}')
			cpt--;
		if(cpt==0 && cpt_v==1)
			break;
		cpt_v=cpt;

	}

    //------- affiche les lignes de code----------
	if(verbose >=2)
	{
		cout<<"Lignes de code:"<<endl;
		for(auto s : L_class)
			cout<<s<<endl;
	}
	//--------------------------------------------------------------
	//--- 2) on extrait les infos pertinentes de chaque ligne, a partir de L_class
	if(verbose >=2)
	{
		cout<<"------------"<<endl;
		cout<<"## Etape (2)"<<endl;
		cout<<"------------"<<endl;
	}
	
	string nom_class = L_class[0];
	
	if(verbose >= 2)
	{
		cout<<"nom_class (1)  = '"<<nom_class<<"'"<<endl;
		
	}
	
	//... si il y a heritage:
	nom_class = nom_class.substr(0, nom_class.find(":")); // extrait sous chaine entre le debut (indice 0) la premiere occurence de ":"

	if(verbose >= 2)
	{
		cout<<"nom_class (2)  = '"<<nom_class<<"'"<<endl;
	}
		
	Enleve_espaces(nom_class);

		
	if(verbose >= 2)
	{
		cout<<"nom_class (final)  = '"<<nom_class<<"'"<<endl;
	}
	int cpt_mk = 0; // nbre de "make_gui" trouves
		
	for(int k= 1; k < L_class.size(); k++) // boucle sur les lignes de code
	{
		string ligne = L_class[k];
		Enleve_espaces(ligne);

		if(verbose >=2)	cout<<"........"<<endl;

		//--- etude de la ligne 
		if(ligne.find("make_gui") != string::npos) // si ligne contient "make_gui"
		{

			if(verbose >=2)
			{
				cout<<"------------"<<endl;
				cout<<"## Etape (2.O): Analysis of the line:"<<endl;
				cout<<"------------"<<endl;
				cout<<ligne<<endl;
			}


			
			cpt_mk++;
			
			string widget, zone, texte, nom_tab, xmin, xmax, step,  help, attach_function, text, object, URL, midicontrol, midi_name;
			int W=0, H=0;
			int midi_M, midi_C;
			int mouseDown =0, mouseMove =0, mouseWheelMove=0, keyPressed=0;
			double midi_R1, midi_R2;
			vector<string> L_l; // pour Liste
			
			//ligne0: code c++ avant le signe //  ------------------
			if(verbose >=2)
			{
				cout<<"------------"<<endl;
				cout<<"## Etape (2.1): code c++ before the sign //"<<endl;
				cout<<"------------"<<endl;
			}


			string ligne0 =  ligne.substr(0, ligne.find("//"));  // extrait  avant //

			ligne0 =  ligne0.substr(0, ligne0.find(";"));  // extrait  avant ;

			Enleve_espaces(ligne0);// enleve espaces de debut et fin

			string type =  ligne0.substr(0, ligne0.find(" "));  // extrait  avant " "
			Enleve_espaces(type);

			
			ligne0 =  ligne0.substr(ligne0.find(" ")+1); // extrait apres " "
			
			string nom="", val="", nom2="", val2="", nom3="", val3="";

			if(type == "void") // c'est une fonction
				nom =  ligne0.substr(0, ligne0.find("("));  // extrait  avant ()
			else
			{
					if(ligne0.find("=") != string::npos) // si contient =
					{
						nom =  ligne0.substr(0, ligne0.find("="));  // extrait  avant =
						val =  ligne0.substr(ligne0.find("=")+1); // extrait apres =

						//... we look if there are still other variables after
						if(val.find(",") != string::npos) // si contient ,
						{
							string temp = val;
//							cout<<"val="<<val<<endl;
							val =  temp.substr(0, temp.find(","));  // extrait  avant ,
							temp = temp.substr(temp.find(",")+1); // extrait apres ,

//							cout<<"temp="<<temp<<endl;
							if(temp.find("=") != string::npos) // si contient =
							{
								nom2 =  temp.substr(0, temp.find("="));  // extrait  avant =
								val2 =  temp.substr(temp.find("=")+1); // extrait apres =
								Enleve_espaces(nom2);
								Enleve_espaces(val2);

								//... we look if there are still other variables after
								if(val2.find(",") != string::npos) // si contient ,
								{
									string temp = val2;
//									cout<<"val2="<<val2<<endl;
									val2 =  temp.substr(0, temp.find(","));  // extrait  avant ,
									temp = temp.substr(temp.find(",")+1); // extrait apres ,

//									cout<<"temp="<<temp<<endl;
									if(temp.find("=") != string::npos) // si contient =
									{
										nom3 =  temp.substr(0, temp.find("="));  // extrait  avant =
										val3 =  temp.substr(temp.find("=")+1); // extrait apres =
										Enleve_espaces(nom3);
										Enleve_espaces(val3);
									}
									else
										cout<<"Erreur, je ne comprends:  nom_fichier="<<nom_fichier<<" ligne = "<<ligne <<endl;
								}
							
							}
							else
								cout<<"Erreur, je ne comprends:  nom_fichier="<<nom_fichier<<" ligne = "<<ligne <<endl;
						}
					}
					else
					{
						nom =  ligne0;
					}
			} //if



			Enleve_espaces(nom);
			Enleve_espaces(val);
			

			
			if(verbose >=2)
			{
				cout<<"ligne0 = "<<ligne0<<endl;
				cout<<"   type  = "<<type<<endl;
				cout<<"   nom  = "<<nom<<endl;
				cout<<"   val  = "<<val<<endl<<endl;
				cout<<"   nom2  = "<<nom2<<endl;
				cout<<"   val2  = "<<val2<<endl<<endl;
				cout<<"   nom3  = "<<nom3<<endl;
				cout<<"   val3  = "<<val3<<endl<<endl;
			}

			//ligne1 -----------------------
			if(verbose >=2)
			{
				cout<<"------------"<<endl;
				cout<<"## Etape (2.2): code c++ after the sign //"<<endl;
				cout<<"------------"<<endl;
			}
		
			
			string ligne1 =  ligne.substr(ligne.find("//"));  // extrait apres //
			ligne1 =  ligne1.substr(ligne1.find("=")+1); // extrait apres '='
			Enleve_espaces(ligne1);// enleve espaces de debut et fin
			
			if(verbose >=2)
				cout<<"ligne1,0 = "<<ligne1<<endl;

			//..... Test si option 'nl' ...........
			int opt_nl = 0;
			if(ligne1[0] == 'n' && ligne1[1] == 'l') // si "nl"
			{
				opt_nl = 1; // demande de newline
				ligne1.erase(0,2); // enleve "nl" de debut
			}

			//..... Test si option '_param_' ...........
			int opt_param  = 0;
			if(ligne1.find("_param_") != string::npos) // si ligne contient "_param_"
				opt_param  = 1;

			//..... Test si option '_no_save_' ...........
			int opt_no_save  = 0;
			if(ligne1.find("_no_save_") != string::npos) // si ligne contient "_no_save_"
				opt_no_save  = 1;

			//..... Extrait widget's  name ....
			widget = ligne1.substr(0, ligne1.find("(")); // extrait avant le premier (
			Enleve_espaces(widget);// enleve espaces de debut et fin
			if(verbose >=2)
				cout<<"widget="<<widget<<endl;
			
			//.... Test si option 'help' ............;
			if(ligne1.find("help") != string::npos) // si ligne contient "help"
			{
				help = ligne1.substr(ligne1.find("help"));  // extrait apres "help"
				help = help.substr(help.find("\"")+1);  // extrait apres le premier "
				help = help.substr(0,help.rfind("\""));  // et avant " de la fin
				
				ligne1 = ligne1.substr(0, ligne1.find("help")); // extrait avant "help"
				if(verbose >=2)
					cout<<"ligne1,h = "<<ligne1<<endl;
			}

			
			//.... Test si option 'midicontrol' ............;
			if(ligne1.find("midicontrol") != string::npos) // si ligne contient "midicontrol"
			{
				string mc = ligne1.substr(ligne1.find("midicontrol"));  // extrait apres "midicontrol"
				mc = mc.substr(mc.find("\"")+1);  // extrait apres "
				mc = mc.substr(0,mc.rfind("\""));  // et avant le dernier "
				
				//	cout<<"midicontrol="<<mc<<endl;

				//... parsing of mc. Ex: mc = "TINYCONTROL, M=0xB0, C=0x3, R=[0,3.]"
				midi_name = mc.substr(0, mc.find(",")); // extrait avant le premier,
				Enleve_espaces(midi_name);// enleve espaces de debut et fin
				midicontrol = mc;
				
				mc = mc.substr(mc.find("M=")+2);  // extrait apres le premier 'M='
				string midi_MM =  mc.substr(0, mc.find(",")); // extrait avant le premier,
				midi_M = stringhexa_to_int(midi_MM);
			

				
				mc = mc.substr(mc.find("C=")+2);  // extrait apres le premier 'C='
				string midi_CC =  mc.substr(0, mc.find(",")); // extrait avant le premier,
				midi_C =  stringhexa_to_int(midi_CC);;
				
				string midi_R = mc.substr(mc.find("[")+1);  // extrait apres le premier '['
				midi_R =   midi_R.substr(0, midi_R.find("]")); // extrait avant le premier ']'
				string midi_RR1 = midi_R.substr(0,midi_R.find(","));  // extrait avant le premier ','
				string midi_RR2 = midi_R.substr(midi_R.find(",")+1);  // extrait apres le premier ','

//				cout<<"midi_name = '"<<midi_name<<"' midi_MM='"<<midi_MM<<"' midi_CC='"<<midi_CC<<"' midi_R='"<<midi_R<<"'"<<"' midi_RR1='"<<midi_RR1<<"' midi_RR2='"<<midi_RR2<<"'"<<endl;

				midi_R1 = stof(midi_RR1);
				midi_R2 = stof(midi_RR2);
				
					
				//.......
				if(is_not_in(midi_name,  L_midicontrol_name)) // si  pas deja present dans liste 
					L_midicontrol_name.push_back(midi_name); // on rajoute a la liste

				
				ligne1 = ligne1.substr(0, ligne1.find("midicontrol")); // extrait avant "text"
				if(verbose >=2)
					cout<<"ligne1,mc = "<<ligne1<<endl;
					
			}

		

			//.... Test si option 'attach_function' ............;
			if(ligne1.find("attach_function") != string::npos) // si ligne contient "attach_function"
			{
				attach_function = ligne1.substr(ligne1.find("attach_function"));  // extrait apres "attach_function"
				attach_function = attach_function.substr(attach_function.find("\"")+1);  // extrait apres "
				attach_function = attach_function.substr(0,attach_function.rfind("\""));  // et avant " de la fin
				
				ligne1 = ligne1.substr(0, ligne1.find("attach_function")); // extrait avant "attach_function"
			if(verbose >=2)
				cout<<"ligne1,af = "<<ligne1<<endl;

			}


			
			//.... Test si option 'text' ............;
			if(ligne1.find("texxt") != string::npos) // si ligne contient "texxt"
			{
				text = ligne1.substr(ligne1.find("texxt"));  // extrait apres "text"
				text = text.substr(text.find("\"")+1);  // extrait apres "
				text = text.substr(0,text.rfind("\""));  // et avant " de la fin
				
				ligne1 = ligne1.substr(0, ligne1.find("texxt")); // extrait avant "text"
				if(verbose >=2)
					cout<<"ligne1,tt = "<<ligne1<<endl;

			}

	
			//.... Test si option 'event' ............;
			if(ligne1.find("event") != string::npos) // si ligne contient "event"
			{

				string event = ligne1.substr(ligne1.find("event"));  // extrait apres "event"
				//	cout<<"event = "<<event<<endl;
				event = event.substr(text.find("\"")+1);  // extrait apres "
				event = event.substr(0,text.rfind("\""));  // et avant " de la fin

//				cout<<"event = "<<event<<endl;

				//... parsing of event. Ex: event = "mouseDown, mouseMove, mouseWheelMove, keyPressed" // see JUCE doc

				auto pos = event.find("mouseDown");
				if(pos != string::npos) // found
					mouseDown = 1;

				auto pos2 = event.find("mouseMove");
				if(pos2 != string::npos) // found
					mouseMove = 1;

				auto pos3 = event.find("mouseWheelMove");
				if(pos3 != string::npos) // found
					mouseWheelMove = 1;

				auto pos4 = event.find("keyPressed");
				if(pos4 != string::npos) // found
					keyPressed = 1;


				
				
				//..................
				ligne1 = ligne1.substr(0, ligne1.find("event")); // extrait avant "event"
				if(verbose >=2)
					cout<<"ligne1,ev = "<<ligne1<<endl;

			}



			//............
			ligne1 = ligne1.substr(ligne1.find("(")+1);  // extrait apres (
			ligne1 = ligne1.substr(0,ligne1.rfind(")"));  // et avant ) de la fin
			if(verbose >=2)
				cout<<"ligne1,3 = "<<ligne1<<endl;

			//.. lecture de zone 
			if(widget == "M" || widget == "MS") // si menu
			{
				nom_tab = ligne1.substr(0, ligne1.find(","));  // extrait avant ,
				nom_tab = nom_tab.substr(nom_tab.find("\"")+1);  // extrait apres "
				nom_tab = nom_tab.substr(0, nom_tab.find("\"")); // extrait avant "
				if(is_not_in(nom_tab,  L_noms_menus)) // si nom_tab  pas deja present dans liste L_noms_menus
					L_noms_menus.push_back(nom_tab); // on rajoute a la liste pour L_noms_menus
				
			}
			
			else if(widget == "LINK") 
			{

				nom_tab = ligne1.substr(ligne1.find("\"")+1);  // extrait apres "
				nom_tab = nom_tab.substr(0, nom_tab.find("\"")); // extrait avant "

				if(nom_tab[0] == '.' && nom_tab[1] == '/') // commence par "./"
				{
					nom_tab = nom_tab.substr(nom_tab.find("./")+2);  // extrait apres './'
					liste_files_linked_main.push_back(nom_tab);

				}
					
			}
			
			else if(widget == "TITRE") // titre de la fenetre de commandes 
			{

				nom_tab = ligne1.substr(ligne1.find("\"")+1);  // extrait apres "
				nom_tab = nom_tab.substr(0, nom_tab.find("\"")); // extrait avant "
				Titre = nom_tab;
					
			}
			

			else if(widget != "ST" && widget != "TT") // sinon et si != "ST", "TT"
			{
				zone = ligne1.substr(0, ligne1.find(","));  // extrait avant ,
				Enleve_espaces(zone);
				if(zone[1] == 'T') // si ZT
				{
					nom_tab = zone.substr(zone.find("\"")+1);  // extrait apres "
					nom_tab = nom_tab.substr(0, nom_tab.find("\"")); // extrait avant "
					if(is_not_in(nom_tab,  L_noms_tabs))// si pas deja present
						L_noms_tabs.push_back(nom_tab);

					zone = "ZT";
				}
				else if(zone == "ZC") // si ZC
				{
					nom_tab = "ZC";
				}
			}

			if(widget=="TT")
			{
				int duree = stoi(ligne1);
				L_noms_TT.push_back(duree);
				val  = ligne1;
			}

			
			//........ suite
			
			if(widget=="N" || widget=="C" || widget=="B"  || widget=="M" || widget == "Color"   || widget=="Window"  || widget=="Editor"  ) // Numerical or Check or Button or Menu
			{
                //-- on cherche info: zone, titre
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				if(verbose >=2)
						cout<<"ligne1,4 = "<<ligne1<<endl;
				Enleve_espaces(ligne1);
				ligne1.erase(0,1); // enleve " de debut
				ligne1.erase(ligne1.size()-1,1); // enleve " de fin
				texte = ligne1;
				
			}

			else if( widget=="Window2"  )
			{
                //-- on cherche info: zone, titre
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				
				//	cout<<"ligne1,4 = "<<ligne1<<endl;
				
				Enleve_espaces(ligne1);
				ligne1.erase(0,1); // enleve " de debut
				//cout<<"ligne1 = "<<ligne1<<endl;
				texte = ligne1.substr(0, ligne1.find("\""));  // extrait avant "
				//cout<<"texte = "<<texte<<endl;
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				//cout<<"ligne1 = "<<ligne1<<endl;
				W = stoi( ligne1.substr(0, ligne1.find(",")));  // extrait avant ,
//				cout<<"W = "<<W<<endl;
				
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				//cout<<"ligne1 = "<<ligne1<<endl;
				H = stoi( ligne1.substr(0, ligne1.find(",")));  // extrait avant ,
//				cout<<"H = "<<H<<endl;
				
			}

						
			else if(widget=="HLINK") // Hyperlien
			{
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,

				texte = ligne1.substr(0, ligne1.find(","));  // extrait avant ,
				Enleve_espaces(texte);
				texte.erase(0,1); // enleve " de debut
				texte.erase(texte.size()-1,1); // enleve " de fin

				
				URL = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				Enleve_espaces(URL);
				URL.erase(0,1); // enleve " de debut
				URL.erase(URL.size()-1,1); // enleve " de fin

				HLINK_cpt ++;

				nom = to_string(HLINK_cpt); // car il n y a pas de nom sinon.
			}




			
			
			else if(widget=="T") //Text
			{
				
			}

			
			else if(widget=="HTML") 
			{
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				Enleve_espaces(ligne1);
				texte = ligne1;
				nom = texte; // car il n y a pas de nom sinon.
			}

			else if(widget=="File" || widget=="Dir") 
			{
				 //-- on cherche info: zone, titre
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				Enleve_espaces(ligne1);
				ligne1.erase(0,1); // enleve " de debut
				ligne1.erase(ligne1.size()-1,1); // enleve " de fin
				texte = ligne1;
				
			}

			else if(widget=="MS") //Menu System
			{

				
				
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				Enleve_espaces(ligne1);
				if(verbose >=2)
					cout<<"ligne1,'MS2' = "<<ligne1<<endl;
				texte = ligne1.substr(0, ligne1.find(","));  // extrait avant ,
				Enleve_espaces(texte);
				texte.erase(0,1); // enleve " de debut
				texte.erase(texte.size()-1,1); // enleve " de fin

				nom = texte; // car sinon nom est vide
				//.. enleve des caracteres interdits
				nom = nom.substr(0, nom.find(" "));  // extrait avant ' '
				nom = nom.substr(0, nom.find("."));  // extrait avant '.'
				
				
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				Enleve_espaces(ligne1);
				ligne1.erase(0,1); // enleve " de debut
				ligne1.erase(ligne1.size()-1,1); // enleve " de fin

				attach_function = ligne1;
			}

			else if(widget=="HS"  || widget=="VS" || widget=="PB" || widget=="INC" ) // Slider or ProgressBar
			{
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				xmin = ligne1.substr(0, ligne1.find(","));  // extrait avant ,
				Enleve_espaces(xmin);
				xmax = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				Enleve_espaces(xmax);

				if(xmax.find(",") != string::npos) // si contient encore  ,
				{
					string l = xmax;
					xmax = xmax.substr(0, xmax.find(","));  // extrait avant ,
					Enleve_espaces(xmax);

					step = l.substr(l.find(",")+1);  // extrait apres ,
					Enleve_espaces(step);
				}
				else
					step = "1";
				
			}
			
			else if(widget=="L") // List
			{
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				if(verbose >=2)
					cout<<"ligne1,'L' = "<<ligne1<<endl;

				while(ligne1.find("\"") != string::npos) // si contient "
				{
					ligne1 = ligne1.substr(ligne1.find("\"")+1);  // extrait apres "
					string l = ligne1.substr(0, ligne1.find("\""));  // extrait avant "
					L_l.push_back(l);
					ligne1 = ligne1.substr(ligne1.find("\"")+1);  // extrait apres "
				
				}

				if(L_l.size()==0) // la liste n'est pas explicite mais donnee par vector<string> nom
				{
					Enleve_espaces(ligne1);// enleve espaces de debut et fin
					object = ligne1; 
				}
			}

			else if(widget=="LB") // List Box
			{
				ligne1 = ligne1.substr(ligne1.find(",")+1);  // extrait apres ,
				while(ligne1.find("\"") != string::npos) // si contient "
				{
					ligne1 = ligne1.substr(ligne1.find("\"")+1);  // extrait apres "
					string l = ligne1.substr(0, ligne1.find("\""));  // extrait avant "
					L_l.push_back(l);
					ligne1 = ligne1.substr(ligne1.find("\"")+1);  // extrait apres "				
				}

				
				if(L_l.size()==0) // la liste n'est pas explicite mais donnee par vector<string> nom
				{
					Enleve_espaces(ligne1);// enleve espaces de debut et fin
					object = ligne1; 
				}
			}

			if(verbose >=2)
			{
				cout<<"   widget  = \""<<widget<<"\""<<endl;
				cout<<"   zone  = \""<<zone<<"\""<<endl;
				cout<<"   nom_tab  = \""<<nom_tab<<"\""<<endl;
				cout<<"   texte  = \""<<texte<<"\""<<endl;
				cout<<"   xmin  = \""<<xmin<<"\""<<endl;
				cout<<"   xmax  = \""<<xmax<<"\""<<endl;
				cout<<"   step  = \""<<step<<"\""<<endl;

				cout<<"   text  = \""<<text<<"\""<<endl;
				cout<<"   attach_function  = \""<<attach_function<<"\""<<endl;
				cout<<"   help  = \""<<help<<"\""<<endl;
				cout<<"   object  = \""<<object<<"\""<<endl;
				cout<<"   URL  = \""<<URL<<"\""<<endl;
				cout<<"   midicontrol  = \""<<midicontrol<<"\""<<endl;


				for(int i=0; i<L_l.size(); i++)
					cout<<"   L_l["<<i<<"]  = \""<<L_l[i]<<"\""<<endl;
				
				cout<<endl;
			}

			if(midicontrol.size() >0)
				help +=  " MIDICONTROL:" +  midicontrol;
			
			Infos infos;
			infos.nom_fichier = nom_fichier;
			infos.nom_class = nom_class;
			infos.ligne = ligne;
			infos.type = type;
			infos.nom =nom;
			infos.val = val;
			infos.nom2 = nom2;
			infos.val2 = val2;
			infos.nom3 = nom3;
			infos.val3 = val3;
			infos.opt_nl = opt_nl;
			infos.opt_param = opt_param;
			infos.opt_no_save = opt_no_save;
			infos.widget = widget;
			infos.zone=zone;
			infos.nom_tab=nom_tab;
			infos.texte=texte;
			infos.xmin=xmin;
			infos.xmax=xmax;
			infos.step=step;
			infos.W = W;
			infos.H = H;
			

			
			infos.L_l=L_l;
			infos.help = help;
			infos.attach_function = attach_function;
			infos.text = text;
			infos.object = object;
			infos.URL = URL;
			infos.midicontrol = midicontrol;
			infos.midi_name = midi_name;
			infos.midi_M = midi_M;
			infos.midi_C = midi_C;
			infos.midi_R1 = midi_R1;
			infos.midi_R2 = midi_R2;
			infos.mouseDown = mouseDown;
			infos.mouseMove = mouseMove;
			infos.mouseWheelMove = mouseWheelMove;
			infos.keyPressed = keyPressed;
			
			infos.Id = "Id_" + nom_class + "_" + widget + "_" + nom; //  -> nom Identificateur
			infos.nom_obj = nom_class + "_" +  nom; // -> nom de l'objet c++
			
			L_infos.push_back(infos);

			if(verbose>=2)
			{
				cout<<"We have put a new info object in the list L_infos:"<<endl;
				cout<<infos<<endl;
			}
				
		} //   si ligne contient "make_gui"
	} // for k, ligne de code

    //--------------------------------
	if(cpt_mk>=1)
	{
		L_noms_classes.push_back(nom_class); 
		if(is_not_in(nom_fichier, L_noms_fichiers))
		{
//			cout<<"nom_fichier="<<nom_fichier<<endl;
			L_noms_fichiers.push_back(nom_fichier);
		}
	}

	
	//---------------------
	if(verbose)
	{
		cout<<" Fin de Fonction Extract_next_class()"<<endl;
		cout<<"----------------------------"<<endl<<endl;;
	}
	return 1;
	
}
/*======================================================================
-- Arborescence des sections a partir de la liste L_noms_tabs -------------------
ex:
entree:  Ls  =  { "A__A1" , "A__A2", "B", "A__A1__C1", "A__A1__C2", "C", "B__B1"} 
         delim ="__"

sortie:

    "A",    "A1",
    "A",    "A1",    "C1",
    "A",    "A1",    "C2",
    "A",    "A2",
    "B",
    "B",    "B1",
    "C",
*/
vector<vector<string>> Cree_arborescence_tabs(vector<string> Ls, string delim)
{

	//---- etape 1:  cree une premiere liste 
	vector<vector<string>> L1;
	for(int i=0;i< Ls.size(); i++)
		L1.push_back( Decompose(Ls[i], delim)); // decompose en noms des sous tabs 

	//---- etape 2 : rajoute des intermediares
	vector<vector<string>> L2;
	for(vector<string> l : L1)
		for(int k=0; k<l.size(); k++)
		{
			vector<string> l2;
			for(int j=0;j<= k; j++)
				l2.push_back(l[j]);
			L2.push_back(l2);
		}


	//--- etape 3 : elimine les doublons
	vector<vector<string>> L3;
	for(vector<string> l : L2)
		if(is_not_in(l, L3))
					L3.push_back(l);


	//-- etape 4 : ordonne
	sort(L3.begin(), L3.end()); // ordonne par ordre lexyco


	//... affiche la liste
	if(verbose >= 1)
	{
		cout<<"Sous_tabs = "<<endl;
		for(int i=0; i<L3.size(); i++)
		{
			for(int j=0; j<L3[i].size(); j++)
			{
				cout<<"    \""<<L3[i][j]<<"\","<<flush;
			}
			cout<<endl;
		}
	}

	return L3;
}
	
//=================================
void Bilan_collecte_infos()
{


	
	
	//-------------------------------
	
	cout<<"Bilan de la collecte des infos:"<<endl;
	cout<<endl;

	cout<<"double list of tabs, L_sous_tabs[j][k], j: tab, k: depth"<<endl;

	for(int j=0; j< L_sous_tabs.size(); j++)
	{
		cout<<"j="<<j<<", \tL_sous_tabs[j].size="<<L_sous_tabs[j].size()<<" "<<flush;
		for(int k=0; k< L_sous_tabs[j].size(); k++)
		{
			cout<<"|\t"<<L_sous_tabs[j][k]<<flush;
		}
		cout<<endl;
	}




	cout<<"------------------"<<endl;
	for(int i=0; i< L_noms_classes.size(); i++)
		cout<<" i="<<i<<" L_noms_classes[i]="<<L_noms_classes[i]<<endl;

	cout<<"------------------"<<endl;
	for(int i=0; i< L_noms_menus.size(); i++)
		cout<<" i="<<i<<" L_noms_menus[i]="<<L_noms_menus[i]<<endl;
	cout<<"------------------"<<endl;
	for(int i=0; i< L_noms_tabs.size(); i++)
		cout<<" i="<<i<<" L_noms_tabs[i]="<<L_noms_tabs[i]<<endl;
	cout<<"------------------"<<endl;
	for(int i=0; i< L_midicontrol_name.size(); i++)
		cout<<" i="<<i<<" L_midicontrol_name[i]="<<L_midicontrol_name[i]<<endl;


	cout<<"------------------"<<endl;
	
	cout<<endl;
	cout<<" L_infos.size() = "<<L_infos.size()<<endl;

	for(auto inf : L_infos)
	{
		cout<<inf<<endl;
	}



	
}



//============================
// fonction pour make_gui
/*
 entree:  a partir des informations contenues dans
  L_infos

sortie: ecrit com.cc et com.h et index.html  pour une interface
*/
void 	Ecriture_fichiers_cpp_JS()
{
	if(verbose>=1)
	{
		cout<<"=========================================================="<<endl;
		cout<<"## == Part 2: Ecriture des fichiers com.cc et com.h et index.html for EMCC  =========="<<endl;
		cout<<"=========================================================="<<endl<<endl;
		cout<<"Debut de Fonction Ecriture_fichiers_cpp_JS()"<<endl;
		cout<<"----------------------------"<<endl;
	}

	//======= Ecriture du fichier index.html ===================================
	string nom_com = rep_src2 + "/index.html";
	
//	cout<<"Ecriture du fichier :"<<nom_com<<endl;
	
	ofstream f(nom_com);

	f<<"<!-- THIS  HTML CODE IS WRITTEN AUTOMATICALLY BY: makef.cc"<<endl;
	f<<"======================================================== \n\
    The first call is done by main() defined in main.js  -->"<<endl;

	// We force the brwoser to reload each time
	f<<"<!DOCTYPE html>\n\
 <html>\n\
  <head>\n\
	<title>Title</title>\n\
	<meta charset=\"UTF-8\">\n\
   <meta http-equiv='cache-control' content='no-cache, must-revalidate, post-check=0, pre-check=0' />\n\
  <meta http-equiv='cache-control' content='max-age=0' />\n\
  <meta http-equiv='expires' content='0' />\n\
  <meta http-equiv='expires' content='Tue, 01 Jan 1980 1:00:00 GMT' />\n\
  <meta http-equiv='pragma' content='no-cache' />\n\
    <link rel='icon' href='data:,'>\n\
 <!-- Si fichier style.css a part:   <link rel=\"stylesheet\" href=\"style.css\" />-->\n\
<style>\n\
@import url('https://fonts.googleapis.com/css2?family=Bebas+Neue&family=Hind+Vadodara:wght@300&display=swap');\n\
</style>\n\
<style>\n\
  body {\n\
	margin : 20px;\n\
	font-family: 'Hind Vadodara', sans-serif;\n\
}\n\
button {\n\
	background-color : lightgreen;\n\
	padding : 10px;\n\
}\n\
/* propriete des boutons si la souris passe dessus*/\n\
button:hover {\n\
	background-color : green;\n\
	color: white;\n\
}\n\
/* propriete des liens */\n\
a {\n\
	text-decoration: none;\n\
	color : red;\n\
}\n\
/* propriete des liens si la souris passe dessus*/\n\
a:hover {	\n\
	font-weight: bold;\n\
	text-decoration: underline;\n\
}\n\
h1 {\n\
    font-family: 'Bebas Neue', cursive;\n\
}\n\
</style>\n\
  </head>\n\
  \n\
  <script src=\"main.js\"></script>\n\
  <script src=\"javascript/interface2.js\"></script>\n\
<link rel=\"stylesheet\" href=\"javascript/web-music-tools/css/music.min.css\" />\n\
<script src=\"javascript/web-music-tools/libs/harmony-1.0.0.min.js\"></script>\n\
<script src=\"javascript/web-music-tools/libs/abc-ui-1.0.0.min.js\"></script>\n\
<script src=\"javascript/web-music-tools/libs/music-ui-1.0.0.min.js\"></script>\n\
<script src=\"javascript/web-music-tools/soundfonts/acoustic_grand_piano-mp3.js\"></script>\n\
<script src=\"javascript/web-music-tools/soundfonts/violin-mp3.js\"></script>\n\
<script src=\"javascript/WebMIDIAPI/WebMIDIAPI.min.js\"></script>\n\
<script src=\"javascript/initialise_midi.js\"></script>\n\
\n\
  \n";
/*
  <script>\n\
	window.onload =	   function F_start()\n\
	{\n\
	main = Module.cwrap('main')\n\
    document.getElementById(\"zone_start\").innerHTML = \"Please wait 1 sec ...\";\n \
    setTimeout(function(){ main(); }, 1000); // wait 1 sec to load\n\
	}\n\
  </script>\n\
*/
	
	f<<"\n\
  <p id=\"debug\"></p>\n\
  <p id=\"zone_start\"></p>\n\
  <p id=\"zone_canvas\"></p>\n\
  <p id=\"verbose\"></p>\n\
</body>\n\
</html> \n\
";

	f.close(); // ferme le fichier 

	

	//======= Ecriture du fichier com.h ===================================
	nom_com = rep_src2 + "/com.h";
	
//	cout<<"Ecriture du fichier :"<<nom_com<<endl;
	
	f.open(nom_com);

	f<<"#if !defined(__COM_MODEL_H)\n\
#define __COM_MODEL_H\n\
//THIS  C++  CODE com.h IS WRITTEN AUTOMATICALLY BY: makef.cc\n\
// AND IS FOR COMPILATION BY: EMCC\n\
#include <chrono>\n\
using namespace std::chrono;\n\
#include <iostream>\n\
#include <fstream>\n\
#include <sstream>\n\
using namespace std;\n\
#include <emscripten.h>\n\
\n\
#include \"javascript/interfaces.h\"\n\
\n\
";

	for(auto nf : L_noms_fichiers)
		f<<"# include \""<<nf<<"\"\n";		

	
	f<<"\n\
//==================\n\
void Lance_com(";
	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p_"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<");"<<endl;
	}
	f<<"\n\
//===================\n\
class Com\n\
{\n\
public :\n\
\n\
	Com(";
	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p_"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<");"<<endl;
	}


//	f<<"    vector<string> subtitles_tabs; // for menus"<<endl;
	f<<"    vector<string> titles_tabs;  // for menus"<<endl<<endl;
	
	
	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.nom.size() == 0)
			continue;

		f<<"//=== fonctions attachees a l' objet: "<<inf.nom_class<<"_"<<inf.nom<<" ==============\n";
		f<<"\n\
//..... function to be called to refresh html form..................\n\
void Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"();\n\
\n\
\n";
	}

    f<<"};"<<endl;

	f<<"//============"<<endl;
	f<<"extern Com *p_com;// = nullptr;  // pointeur sur l'objet (declare dans com.cc)"<<endl;
	f<<"extern mutex *mtx_com;  // pointeur sur l'objet (declare dans com.cc)\n\n";
//..........
	f<<"#endif\n";
//---------------------------------
	f.close(); // ferme le fichier


    //======= Ecriture du fichier com.cc ===================================
	nom_com = rep_src2 + "/com.cc";
	
//	cout<<"Ecriture du fichier :"<<nom_com<<endl;
	
	f.open(nom_com);

	f<<"//CE CODE C++ com.cc EST ECRIT AUTOMATIQUEMENT PAR: makef.cc\n\
#include \"./com.h\"\n\
#include <emscripten/html5.h>\n\
\n\
";
	


	f<<"//=== pointeurs sur les objets ==============\n";
	for(int i=0; i <L_noms_classes.size(); i++)
	{
		f<<L_noms_classes[i]<<"  *p_"<<L_noms_classes[i]<<" = nullptr;"<<endl;
	}

	f<<"mutex *mtx_com = nullptr; // pointeur pour partager un mutex \n\
Com *p_com = nullptr; \n\
\n";
	
	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.nom.size() == 0)
			continue;

				
		f<<"//=== fonctions attachees a l' objet: "<<inf.nom_class<<"_"<<inf.nom<<", appelee si modification de l'objet ==============\n";
		f<<"\n\
string id_"<<inf.nom_obj<<"; // identifiant objet html\n\n\
//..... c++ -> html:  function to be called to refresh html form ..................\n\
void Com::Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"()\n\
{\n";

		f<<" if(id_"<<inf.nom_obj<<" ==\"\")  // if the widget is not yet defined"<<endl;
		f<<"    return; "<<endl;
		
		if(inf.widget == "N") //entree numerique
		{
			f<<"   T_NE[indice_NE(id_"<<inf.nom_obj<<")].x = p_"<<inf.nom_class<<"->"<<inf.nom<<";\n";
			f<<"   T_NE[indice_NE(id_"<<inf.nom_obj<<")].met_a_jour_html();\n";
		} // if objet
		
		else if(inf.widget == "T") //entree texte
		{
			f<<"   T_NE[indice_NE(id_"<<inf.nom_obj<<")].text = p_"<<inf.nom_class<<"->"<<inf.nom<<";\n";
			f<<"  T_NE[indice_NE(id_"<<inf.nom_obj<<")].type= \"string\";\n";
			f<<"  T_NE[indice_NE(id_"<<inf.nom_obj<<")].met_a_jour_html();\n";
		} // if objet

		else if(inf.widget == "PB") // progress Bar
		{
			f<<"   T_PB[indice_PB(id_"<<inf.nom_obj<<")].x = p_"<<inf.nom_class<<"->"<<inf.nom<<";\n";
			f<<"  T_PB[indice_PB(id_"<<inf.nom_obj<<")].met_a_jour_html();\n";
		} // if objet
		
		else if(inf.widget == "C") // Check button
		{
			f<<"   T_C[indice_C(id_"<<inf.nom_obj<<")].x = p_"<<inf.nom_class<<"->"<<inf.nom<<";\n";
			f<<"  T_C[indice_C(id_"<<inf.nom_obj<<")].met_a_jour_html();\n";
		} // if objet

		else if(inf.widget == "L") // List
		{
			f<<"   T_LS[indice_LS(id_"<<inf.nom_obj<<")].is = p_"<<inf.nom_class<<"->"<<inf.nom<<";\n";
			f<<"  T_LS[indice_LS(id_"<<inf.nom_obj<<")].met_a_jour_html();\n";
		} // if objet
		
	

		
		
		f<<"\
}\n									\
\n\
//.....  html -> c++ : function called when the html object has been modified .................\n\
void attach_function_"<<inf.nom_obj<<"()\n\
{\n\
  //.... value in html -> value in c++\n\
";
		if(inf.widget == "N" || inf.widget == "HS" || inf.widget == "INC")
		{
			f<<"  p_"<<inf.nom_class<<"->"<<inf.nom<<" = T_NE[indice_NE(id_"<<inf.nom_obj<<")].x;";
		} // if objet
		else if(inf.widget == "T")
		{
			f<<"  p_"<<inf.nom_class<<"->"<<inf.nom<<" = T_NE[indice_NE(id_"<<inf.nom_obj<<")].text;";
		} // if objet
	
		else if(inf.widget == "C")
		{
			f<<"  p_"<<inf.nom_class<<"->"<<inf.nom<<" = T_C[indice_C(id_"<<inf.nom_obj<<")].x;";
		} // if objet
		else if(inf.widget == "L")
		{
			f<<"  p_"<<inf.nom_class<<"->"<<inf.nom<<" = T_LS[indice_LS(id_"<<inf.nom_obj<<")].is;";
		} // if objet
		else if(inf.widget == "B")
		{
			f<<"  p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
		}
		
		f<<"\n\
";
		if(inf.attach_function.size()>0) // si il faut appeler fonction
		{
			f<<"  //.... call attached function"<<endl;
			if(inf.widget != "MS")
				f<<"  p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
		}

		f<<"}\n\n";
		//.... if help button
		if(inf.help.size()>0)
		{	f<<"//.... for help button ....\n";	
			f<<"string id_"<<inf.nom_obj<<"_help; // identifiant for help button\n\
int open_"<<inf.nom_obj<<"_help = 0; // flag if open/closed\n\n\
void f_"<<inf.nom_obj<<"_help() // function called by button for help\n\
{\n\
  if(open_"<<inf.nom_obj<<"_help == 0) // this is closed\n\
  {\n\
   open_"<<inf.nom_obj<<"_help = 1;\n\
   Change_button_text(id_"<<inf.nom_obj<<"_help, \"X\");\n\
   ostringstream os3;\n\
   os3<<\"document.getElementById('zone__"<<inf.nom_obj<<"_help').style.display= '';\"; // show\n\
   emscripten_run_script(os3.str().c_str());\n\
  }\n\
  else if(open_"<<inf.nom_obj<<"_help == 1) // this is open\n\
  {\n\
   open_"<<inf.nom_obj<<"_help = 0;\n\
   Change_button_text(id_"<<inf.nom_obj<<"_help, \"?\");\n\
   ostringstream os3;\n\
   os3<<\"document.getElementById('zone__"<<inf.nom_obj<<"_help').style.display= 'none';\"; // hide\n\
   emscripten_run_script(os3.str().c_str());\n\
  }\n\
}\n";
		}
    f<<"\n";
			
	} // for inf, boucle sur objets



	
	
	f<<"//=== identifiants pour chaque zone de tabulation ==============\n";

	f<<"string id_ZC; // zone commune"<<endl;
		
	for(int i=0;i<L_sous_tabs.size(); i++)
	{
		string label = Label(L_sous_tabs[i]);

		//......
		
		f<<"string id_"<<label<<";"<<endl;
		f<<"int open_"<<label<<" = -1; // -1 au depart, car les objets ne sont  pas crees\n"<<endl;
	}

    //------------------
	int size = L_sous_tabs.size();
	
	//------ Ecriture des fonctions Section() pour chaque zone tabulation ------------
	for(int i=-1; i<size; i++) // -1: est pour Zone commune ZC
	{
		string nom_tab;
		if(i == -1) // zone commune
			nom_tab = "ZC";
		else
			nom_tab = Label(L_sous_tabs[i]);
        //.........;
		
		f<<"//============================\n\
void Section_"<<nom_tab<<"()\n\
{\n\
	//-- creation of objects --------------------------------\n";

		if(nom_tab != "ZC") // zone tab
		{
			f<<"if(open_"<<nom_tab<<" == -1) \n	\
	{\n\
		open_"<<nom_tab<<" =1;\n\
		Change_button_text(id_"<<nom_tab<<", \"Close\");\n\
";
		}

		//......... creation des objets pour la tabulation actuelle
		for(auto inf : L_infos) // boucle sur les objets
		{
//			cout<<"Debug: inf.nom_tab="<<inf.nom_tab<<", nom_tab="<<nom_tab<<endl;
			
			//... si l'objet n'est pas dans le tab en cours, on continue
			if(inf.nom_tab != nom_tab)
				continue;
//			cout<<" -> idem."<<endl;

			//.......
			f<<"\n";
			f<<"        //=== Creation de l'objet: "<<inf.nom_class<<"_"<<inf.nom<<"  ==============\n";
			f<<"	    //-- d'apres la ligne de la classe "<<inf.nom_class<<": "<<endl;
			f<<"        // "<<inf.ligne<<endl;

			//------ option nl : newline
			if(inf.opt_nl == 1)
			{
				f<<"        message(\"<br>\", \"zone__"<<inf.nom_tab<<"\", \"add\"); // newline\n";
			}

			//.... si  text avant
			if(inf.text.size()>0)
			{
				f<<"        message(\""<<inf.text<<"\",\"zone__"<<inf.nom_tab<<"\",\"add\");"<<endl;
			}
			
			//-------- pour creation des objets --------------------
			
			if(inf.widget == "N" || inf.widget == "T" || inf.widget == "HS" || inf.widget == "INC")
			{
				//..........


				string options ="";
				if (inf.widget == "HS" || inf.widget == "INC")
					options = "type ='range' min='" + inf.xmin + "' max='"+ inf.xmax +"'";
				
				f<<"\n\
        id_"<<inf.nom_obj<<" = new_NE(\"zone__"<<inf.nom_tab<<"\", \""<<inf.texte<<"\", \""<<inf.type<<"\", \"add\",\""<<options<<"\") ; \n";
				if(inf.widget == "N")
					f<<"		T_NE[indice_NE(id_"<<inf.nom_obj<<")].x = "<<inf.val<<"; // valeur initiale\n";
				else if(inf.widget == "T")
					f<<"		T_NE[indice_NE(id_"<<inf.nom_obj<<")].text = "<<inf.val<<"; // valeur initiale\n";
				else if(inf.widget == "HS" || inf.widget == "INC")
					f<<"		T_NE[indice_NE(id_"<<inf.nom_obj<<")].x = "<<inf.val<<"; // valeur initiale\n";
				f<<"		T_NE[indice_NE(id_"<<inf.nom_obj<<")].f = attach_function_"<<inf.nom_obj<<"; // fonction appele si modif de l'objet\n\
";
				f<<"		T_NE[indice_NE(id_"<<inf.nom_obj<<")].met_a_jour_html();\n";
			
			} // if widget

			else if(inf.widget == "PB")
			{
				f<<"\n\
        id_"<<inf.nom_obj<<" = new_PB(\"zone__"<<inf.nom_tab<<"\", "<<inf.val<<", "<<inf.xmin<<", "<<inf.xmax<<", \""<<inf.texte<<"\", \"add\") ; \n";
				
				f<<"		T_PB[indice_PB(id_"<<inf.nom_obj<<")].f = attach_function_"<<inf.nom_obj<<"; // fonction appele si modif de l'objet\n\
";				 
			} // if widget

			else if(inf.widget == "C")
			{
				f<<"\n\
        id_"<<inf.nom_obj<<" = new_C("<<inf.val<<", \"zone__"<<inf.nom_tab<<"\", \""<<inf.texte<<"\", \"add\") ; \n";
				
				f<<"		T_C[indice_C(id_"<<inf.nom_obj<<")].f = attach_function_"<<inf.nom_obj<<"; // fonction appele si modif de l'objet\n\
";				 
			} // if widget
			
			else if(inf.widget == "L")
			{
				f<<"       {\n";
				if(inf.object !="") // si il y a une liste explicite
				{
					f<<"\n\
        id_"<<inf.nom_obj<<" = new_LS( &p_"<<inf.nom_class<<"->"<<inf.object<<" , "<<inf.val<<", \"zone__"<<inf.nom_tab<<"\", \""<<inf.texte<<"\", \"add\") ; \n";
					
				}
				else
				{
					f<<"        vector<string> ls = {";
					for(int i=0; i<inf.L_l.size(); i++)
					{
						f<<"\""<<inf.L_l[i]<<"\"";
						if(i<(inf.L_l.size()-1))
							f<<",";
					}
					f<<"};\n";
								
					f<<"\n\
        id_"<<inf.nom_obj<<" = new_LS(&ls, "<<inf.val<<", \"zone__"<<inf.nom_tab<<"\", \""<<inf.texte<<"\", \"add\") ; \n";

				} //else
				
				f<<"		T_LS[indice_LS(id_"<<inf.nom_obj<<")].f = attach_function_"<<inf.nom_obj<<"; // fonction appele si modif de l'objet\n\
";
				f<<"       }\n";

			} // if widget



			else if(inf.widget == "B")
			{
				f<<"\n\
        id_"<<inf.nom_obj<<" = new_B(  attach_function_"<<inf.nom_obj<<", \"zone__"<<inf.nom_tab<<"\", \""<<inf.texte<<"\", \"add\") ; \n";
				
				f<<"		T_B[indice_B(id_"<<inf.nom_obj<<")].f = attach_function_"<<inf.nom_obj<<"; // fonction appele si modif de l'objet\n\
";				 
			} // if widget

			else if(inf.widget == "HTML")
			{
				f<<"        message(p_"<<inf.nom_class<<"->"<<inf.texte<<", \"zone__"<<inf.nom_tab<<"\",\"add\"); // write a html text"<<endl;
				if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"        p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
				
					
			} // if widget
			
			
			//.... si help
			if(inf.help.size()>0)
			{
				f<<"         id_"<<inf.nom_obj<<"_help = new_B(f_"<<inf.nom_obj<<"_help, \"zone__"<<inf.nom_tab<<"\", \"?\", \"add\");"<<endl;
				f<<"        message(\"<span id='zone__"<<inf.nom_obj<<"_help'> "<<inf.help<<"  </span>\",\"zone__"<<inf.nom_tab<<"\",\"add\"); // create zone for tooltiptext"<<endl;
				f<<"\n\
        {\n\
         ostringstream os3;\n\
         os3<<\"document.getElementById('zone__"<<inf.nom_obj<<"_help').style.display= 'none';\"; // hide\n\
         emscripten_run_script(os3.str().c_str());\n\
        }\n";
			} // if help

				
			
		} // for auto inf, boucle sur les objets

		if(nom_tab != "ZC")
		{


	f<<"\n\
   	    ostringstream os3;\n\
        os3<<\"document.getElementById('zone__"<<nom_tab<<"').style.display= '';\"; // show\n	\
        os3<<\"document.getElementById('zone__"<<nom_tab<<"_tabs').style.display= '';\"; // show\n	\
        emscripten_run_script(os3.str().c_str());\n";
			
	f<<"    }\n\
//--  objets deja crees, mais  il faut ouvrir --------------------------------\n\
else if(open_"<<nom_tab<<" == 0)\n\
	{\n\
		open_"<<nom_tab<<" = 1; \n\
		Change_button_text(id_"<<nom_tab<<", \"Close\");\n\
\n\
\n\
		ostringstream os3;\n\
		os3<<\"document.getElementById('zone__"<<nom_tab<<"').style.display= '';\"; // show\n\
		os3<<\"document.getElementById('zone__"<<nom_tab<<"_tabs').style.display= '';\"; // show\n\
		emscripten_run_script(os3.str().c_str());	\n\
\n\
	}\n\
//-- il faut fermer --------------------------------\n\
else if(open_"<<nom_tab<<" == 1) \n\
	{\n\
		open_"<<nom_tab<<" = 0; \n\
		Change_button_text(id_"<<nom_tab<<", \"Open\");\n\
\n\
\n\
		ostringstream os3;\n\
		os3<<\"document.getElementById('zone__"<<nom_tab<<"').style.display= 'none';\"; // hide\n\
		os3<<\"document.getElementById('zone__"<<nom_tab<<"_tabs').style.display= 'none';\"; // hide\n\
		emscripten_run_script(os3.str().c_str());	\n\
\n\
	}\n";
		} // if zone_tab != "ZC"
		//----------------------------------
		f<<"\n\
}\n\
\n\
";
	} //for i: tab


//---- fonctions _TT for periodic callback
f<<"//========================================"<<endl;
for(auto inf : L_infos) // boucle sur les objets
{
	if(inf.widget == "TT") 
	{

		f<<"	//-- d'apres la ligne de la classe "<<inf.nom_class<<": "<<endl;
		f<<"    // "<<inf.ligne<<endl;
		f<<"	void "<<inf.nom<<"_TT(void * data)"<<endl;
		f<<"      {"<<endl;
		f<<"        p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
		f<<"      }"<<endl;
	}
		
}



	
//---- ecriture de la fonction principale
f<<"//============================\n\
void Lance_com(";
for(int j=0; j<L_noms_classes.size(); j++)
{
	auto nc=L_noms_classes[j];
	f<<nc<<" *p_"<<nc<<"_";
	if(j<(L_noms_classes.size()-1))
		f<<", ";
	else
		f<<")"<<endl;
}

f<<"	{\n"<<endl;
for(int i=0; i <L_noms_classes.size(); i++)
{
	f<<"  p_"<<L_noms_classes[i]<<" =  p_"<<L_noms_classes[i]<<"_ ;"<<endl;
}



	 //--- Create objects"<<endl;
//	for(int i=0; i <L_noms_classes.size(); i++)
	 //	{
	 //	f<<"        p_"<<L_noms_classes[i]<<" = new "<<L_noms_classes[i]<<"();"<<endl;
	 //	}



f<<"\n	 //---- cree des zones d ecriture dans zone_start qui est dans index.html \n"<<endl;



f<<"\n\
		{\n\
           ostringstream os;\n\
\n\
		   //............\n\
           for(int i=1;i <= 50;i++)\n\
		      os<<\"<span id='zone_canvas_\"<<i<<\"'>  </span>\";\n\
           //............\n\
		   message(os.str(),\"zone_start\");\n\
        }\n\
\n";

f<<"\n\
		{\n\
           ostringstream os;\n\
\n\
		   //............\n\
		   os<<\"<span id='zone__ZC'>  </span>\";\n\
		\n\
	       //............\n\
		   message(os.str(),\"zone_start\",\"add\");\n\
        }\n\
\n";

			//---- fabrique les menus et sous menus
		   for(int k=0; k<= 10; k++) // profondeur
		   {
			   if(verbose)
				   cout<<"profondeur k = "<<k<<endl;
		
			   for(int i=0;i<L_sous_tabs.size(); i++)
			   {
				   if(L_sous_tabs[i].size() != (k+1)) // selectionne les menus de profondeur k
					   continue;

				   string label = Label(L_sous_tabs[i]);

				   //... cree zone
				   string zone;
				   if(k==0) // si profondeur 0
					   zone = "zone_start";
				   else
					   zone = "zone";
			
				   for(int k2=0; k2<=k-1; k2++)
					   zone = zone + "__" + L_sous_tabs[i][k2];

				   if(k!=0)
					   zone = zone + "_tabs";
						   
				   if(verbose)
					   cout<<"  zone = "<<zone<<endl;


				   //.... header 
				   string header = "h" + to_string(k+1); // h1, h2, ...
				   if((k+1) >= 4)
					   header = "h4";

				   //...................
				   
				   f<<"		//............\n\
		{\n\
           ostringstream os;\n\
\n\
           string header_name = \""<<L_sous_tabs[i][k]<<"\";\n\
		   if(p_com->titles_tabs.size() > "<<i<<" )\n\
			   header_name = p_com->titles_tabs["<<i<<"];\n	\
\n\
		   os<<\"<hr><"<<header<<">\"<<header_name<<\"</"<<header<<">\";\n\
	       os<<\"<span id='zoneButton_"<<label<<"'>  </span>\";\n\
		   os<<\"<span id='zone__"<<label<<"'>  </span>\";\n\
		   os<<\"<span id='zone__"<<label<<"_tabs'>  </span>\";\n\
\n";

			f<<"	   	   //............\n\
		   message(os.str(),\""<<zone<<"\",\"add\");\n\n\
        }\n\
\n";
		} // for i





		
	}//for k


/*
	for(int i=0;i<L_noms_tabs.size(); i++)
	{



		
		f<<"		//............\n\
		os<<\"<h1>"<<L_noms_tabs[i]<<"</h1>\";\n\
		os<<\"<span id='zone_B_"<<L_noms_tabs[i]<<"'>  </span>\";\n\
		os<<\"<span id='zone_"<<L_noms_tabs[i]<<"'>  </span>\";\n\
\n";
	}





	f<<"		//............\n\
		message(os.str(),\"zone_start\");\n\
\n\
";
		
*/
	
        f<<"		//............."<<endl;
		f<<"        Section_ZC(); //create objects of zone__ZC"<<endl;
		f<<endl;

	
		f<<"		//---  affiche boutons open/close des zones  --------------"<<endl;
		for(int i=0;i<L_sous_tabs.size(); i++)
		{
			string label = Label(L_sous_tabs[i]);
			//....
/*
			f<<"\n\
           {\n\
           string header_name = \""<<L_sous_tabs[i][L_sous_tabs[i].size()-1]<<"\";\n\
		   if((p_com->subtitles_tabs.size()-1) >= "<<i<<" )\n\
			   header_name = p_com->subtitles_tabs["<<i<<"];\n\
\n\
";
*/	
			f<<"		id_"<<label<<" = new_B(Section_"<<label<<", \"zoneButton_"<<label<<"\", \"Open\");"<<endl;
			//	f<<"             }"<<endl;
						
		}



        f<<endl;
		f<<"		//---  a priori, ferme chaque zone  --------------"<<endl;
		f<<"		ostringstream os3;"<<endl;

		for(int i=0;i<L_sous_tabs.size(); i++)
		{
			
//			if(L_sous_tabs[i].size()>1)
//				continue;
				
			string label = Label(L_sous_tabs[i]);
			//....
			f<<"        os3<<\"document.getElementById('zone__"<<label<<"').style.display= 'none';\"; // hide\n";
			f<<"        os3<<\"document.getElementById('zone__"<<label<<"_tabs').style.display= 'none';\"; // hide\n";
			
		}

	

        f<<"		emscripten_run_script(os3.str().c_str());	"<<endl;


        //---- Timer: Set periodic callback -------------------------------

for(auto inf : L_infos) // boucle sur les objets
{
	if(inf.widget == "TT") 
	{
		f<<"	//-- d'apres la ligne de la classe "<<inf.nom_class<<": "<<endl;
		f<<"    // "<<inf.ligne<<endl;
		f<<"	void *userData; \n\
 	long id = emscripten_set_interval(  "<<inf.nom<<"_TT , "<<inf.val<<", userData); // function .._TT is defined above."<<endl;

	}
		
}

        //-----------------------------------
	
		f<<"	}\n\
";




//---------------------------------
f.close(); // ferme le fichier
		
//==================================
if(verbose>=1)
{
	cout<<" Fin de Fonction Ecriture_fichiers_cpp_JS()"<<endl;
	cout<<"----------------------------"<<endl<<endl;
}
}




//=============================
// ex: gives 1_Temperaments2_Chords;
string Get_Tab_name(int j)
{
	string name;
	for(int k=0; k< L_sous_tabs[j].size(); k++)
		name += L_sous_tabs[j][k]; // concatene
	ReplaceStringInPlace(name, " ","_");
	ReplaceStringInPlace(name, "/","_");
	return name;
}
//============================
// fonction pour make_gui
/*
 entree:  a partir des informations contenues dans
  L_infos

sortie: ecrit com.cc et com.h
*/
void 	Ecriture_fichiers_cpp()
{

	if(verbose>=1)
	{
		cout<<"=========================================================="<<endl;
		cout<<"## == Part 2: Ecriture des fichiers com.cc com.h for Root c++ =========="<<endl;
		cout<<"=========================================================="<<endl<<endl;
		cout<<"Debut de Fonction Ecriture_fichiers_cpp()"<<endl;
		cout<<"----------------------------"<<endl;
	}
	
	string nom_com = rep_src2 + "/com.cc";
	
	//---fichier com.cc ---------------------------------
	if(verbose>=1)
		cout<<"Ecriture du fichier :"<<nom_com<<endl;
	
	ofstream f(nom_com);

	f<<"//CE CODE C++ com.cc EST ECRIT AUTOMATIQUEMENT PAR: makef.cc"<<endl;
	f<<"//========================================================"<<endl;

	//---- ecriture des entetes
	f<<" \n\
# include \"./com.h\" \n\
";



	f<<endl<<endl<<"//=================="<<endl;

	for(auto nc : L_noms_classes)
		f<<nc<<" *p_"<<nc<<"; // pointeur sur objet de la classe "<<nc<<endl;

	f<<"mutex *mtx_com = nullptr; // pointeur pour partager un mutex \n\
Com *p_com; \n\
\n\
//=================== \n\
// Lance la fenetre de commandes \n\
// \n\
void Lance_com(";

	for(int i=0; i<L_noms_classes.size(); i++)
	{
		auto nc = L_noms_classes[i];
		f<<nc<<" *p"<<nc;
		if(i<L_noms_classes.size()-1)
			f<<", ";
	}
	f<<")"<<endl;

		
	f<<"{"<<endl<<"\n\
// 	sleep_for(milliseconds{100}); // attente pour etre sur que un autre root a le temps de se lancer si besoin. \n \
	TApplication * p_App = new TApplication(\"App\", nullptr, nullptr); \n\
	p_com=  new Com(";

	for(int i=0; i<L_noms_classes.size(); i++)
	{
		auto nc = L_noms_classes[i];
		f<<"p"<<nc;
		if(i<L_noms_classes.size()-1)
			f<<", ";
	}
	f<<");  // cree fenetre de control et l'associe a  l'objet present"<<endl;
	f<<" 	p_com->p_App = p_App;"<<endl;
	f<<" 	p_App->Run(); //----donne la main a l'utilisateur --- \n\
}"<<endl;
	
	f<<endl;
	f<<"//====== identifieurs (int) pour les messages de commandes\n\
enum Command_id \n\
{"<<endl;


	for(int j=0;j<L_infos.size(); j++)
	{
		if(L_infos[j].nom.size() == 0)
			continue;

		f<<L_infos[j].Id;
		if(j<(L_infos.size()-1))
			f<<", "<<endl;
	}
	f<<endl<<"}; \n\
\n\
int X=300, Y=150; // taille en pixels\n\
\n\
//===================\n\
Com::Com(";

	for(int i=0; i<L_noms_classes.size(); i++)
	{
		auto nc = L_noms_classes[i];
		f<<nc<<" *p"<<nc;
		if(i<L_noms_classes.size()-1)
			f<<", ";
	}
	f<<")"<<endl;	

	f<<" : TGMainFrame(gClient->GetRoot(), X,Y) \n\
{\n\
\n\
\n\
    if(verbose)\n\
       cout<<\"com.cc Com();\"<<endl;\n\
\n\
	//-- bloque le mutex\n\
    if(mtx_com == nullptr) \n\
        mtx_com = new mutex(); // if not yet defined \n\
	mtx_com->lock(); // si mtx est libre on le bloque, sinon on attend\n\
\n\
\n\
	//---- pointeurs sur objets\n\
";
	for(auto nc : L_noms_classes)
		f<<"     p_"<<nc<<" = p"<<nc<<";"<<endl;


	f<<"\n\
\n\
	//-- regles de positionnement\n\
	TGLayoutHints *fLH_TX =  new TGLayoutHints(kLHintsTop | kLHintsExpandX , 2, 2, 2, 5);\n\
	TGLayoutHints *fLH_C = new TGLayoutHints(kLHintsCenterX | kLHintsExpandX | kLHintsExpandY,5,5,5,5);\n\
	TGLayoutHints *fLH_L = new TGLayoutHints(kLHintsLeft,5,5,5,5);\n\
	TGLayoutHints *fLH_R = new TGLayoutHints(kLHintsRight,5,5,5,5);\n\
\n\
\n\
\n";


	if(L_noms_menus.size()>0)
	{
		f<<"//--------- Menu ----------\n\
	TGMenuBar *fMB = new TGMenuBar(this, X,Y);\n\
	AddFrame(fMB, fLH_TX);\n\
\n\
";

		for(auto menu : L_noms_menus)
		{
			f<<"    TGPopupMenu *f_"<<menu<<" = fMB->AddPopup(\""<<menu<<"\");"<<endl;
			//... boucle sur les objets a mettre au menu
			for(auto inf : L_infos) // boucle sur les objets
				if((inf.widget == "M" || inf.widget == "MS") && inf.nom_tab == menu)
					f<<"    f_"<<menu<<" ->AddEntry(\""<<inf.texte<<"\","<<inf.Id<<");"<<endl;
		
			f<<"    f_"<<menu<<" -> Associate(this);"<<endl;
			f<<endl;
		}
	}


	int cpt_n_ZC = 0; // numero de la frame en cours de zone commune.
	
	
	f<<"\n\
\n\
\n\
	// zone commune superieure (ZC) ===================\n\
		\n\
		\n\
	auto  * f_ZC = new TGVerticalFrame(this);\n\
	AddFrame(f_ZC,  fLH_L);\n\
\n\
    auto  * f_ZC_"<<cpt_n_ZC<<" = new TGHorizontalFrame(f_ZC);\n\
	f_ZC->AddFrame(f_ZC_"<<cpt_n_ZC<<",  fLH_L);\n\
	"<<endl;


//----------- Sub Tabs
// given in vector<vector<string>> L_sous_tabs;

int k=0; // depth
int j = 0; // counter
int i_last = 0; //for memorize
cout<<"============="<<endl;
f<<"	// zone sous tabs ZT  ================"<<endl;
while(j < L_sous_tabs.size()) // there still remains some tabs
{
	for(int i=0; i<L_sous_tabs.size(); i++)
		if(L_sous_tabs[i].size() == (k+1) ) // depth k
		{
			
//			cout<<"k="<<k<<"\t"<<L_sous_tabs[i]<<endl;

			//... we create a new GTab
			if(i==0 || (i>0 && L_sous_tabs[i].size() > L_sous_tabs[i-1].size())) //  Create a new GTab.
			{
//				cout<<" Create a new GTab"<<endl;
				f<<endl;
				f<<"     //-------------------------------------"<<endl;
				ostringstream s; // code of previous Tab
				if(i==0)
					s<<"this";
				if(i>0)
					s<<"f_ZT_"<<i-1; // previous new Tab
				f<<"     auto *fZTGT_"<<i<<" = new TGTab("<<s.str()<<", 1, 1);"<<endl; // i is code of the new GTab
				f<<"     "<<s.str()<<"->AddFrame(fZTGT_"<<i<<", fLH_L);"<<endl;
				i_last = i; //memorize
			}

			//... we add a new Tab
//			cout<<" Add a new Tab"<<endl;
	
			f<<"    //........................."<<endl;
			ostringstream s; // code of the new Tab
			s<<"f_ZT_"<<i;
			f<<"     auto  *"<<s.str()<<" = fZTGT_"<<i_last<<"->AddTab(\""<<L_sous_tabs[i][k]<<"\");"<<endl; // Label is the last word: L_sous_tabs[i][k]
			f<<"     auto  *f_ZT_"<<i<<"_V = new TGVerticalFrame("<<s.str()<<", X, Y);"<<endl; //the parent Vertical  Frame (V) for this tab.
			f<<"     "<<s.str()<<"->AddFrame(f_ZT_"<<i<<"_V, fLH_L);"<<endl;
			f<<"     auto  *f_ZT_"<<i<<"_0 = new TGHorizontalFrame("<<s.str()<<"_V, X, Y);"<<endl; //the first Horizontal Frame (0) for this tab.
			f<<"     "<<s.str()<<"_V->AddFrame(f_ZT_"<<i<<"_0, fLH_L);"<<endl;


			//........
			j++;
		} // for i
	k++;
} // while j
//-----------------------------------
/*
	if(L_noms_tabs.size()>0)
	{
		f<<"	// zone tab ZT  ================\n\
\n\
	auto *fZT = new TGTab(this);\n\
	AddFrame(fZT);\n\
"<<endl;
	}

//..... each tab zone (index pos) is structured in TGHorizontalFrames.  cpt_n_ZT[pos]  is the number of HorizontalFrames in tab with index pos.
	vector<int> cpt_n_ZT;
	
	for(auto nom_tab : L_noms_tabs)
	{
		string var_tab0 = "f_ZT_" + nom_tab; // Composite Frame (parent)
		string var_tab = var_tab0 + "_0"; 
		cpt_n_ZT.push_back(0);

		f<<"    //-------------------------------------"<<endl;
		f<<"	auto  *"<<var_tab0<<" = fZT->AddTab(\""<<nom_tab<<"\");"<<endl;
		f<<"    auto  *"<<var_tab<<" = new TGHorizontalFrame("<<var_tab0<<", X, Y); //the parent Frame (0) for this tab."<<endl;
		f<<"    "<<var_tab0<<"->AddFrame("<<var_tab<<", fLH_L);"<<endl<<endl;
	}

	
	f<<endl;
	*/


//--- for below, create the list of Full tag names
vector<string> L_full_tag_name;
for(int i=0; i<L_sous_tabs.size(); i++)
	L_full_tag_name.push_back(Label(L_sous_tabs[i]));


vector<int> cpt_n_ZT; //cpt_n_ZT[i]  is the number of HorizontalFrames in tab with index pos.
cpt_n_ZT.assign(L_sous_tabs.size(), 0); 

	//----boucle sur les objets a mettre dans les zones  ZC ou ZT

f<<endl<<"	//== Objects to put in zones ZC or ZT  ================\n"<<endl;
f<<"   //   we denote f_ZT_i_j where i is the horizontal tag index and j the vertical Frame index."<<endl;

	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.widget == "M" || inf.widget == "MS" || inf.widget == "ST" || inf.widget == "TT" ) // menu ou ST
			continue;
		
		string var_tab, var_tab0;
		//-------------------------
		if(inf.zone == "ZT")
		{
			//... search the index i   so that L_full_tag_name[i] = inf.nom_tab
			int i=0;
			while(i<L_full_tag_name.size())
			{
				if(L_full_tag_name[i] == inf.nom_tab)
					break;
				i++;
			}
			if(i == L_full_tag_name.size()) //not found
			{
				cout<<"makef.cc. Error: tag not found in the list:  inf.nom_tab="<<inf.nom_tab<<endl;
				while(1);
			}

			
			if(inf.opt_nl == 1) // newline
				cpt_n_ZT[i] = cpt_n_ZT[i]+1;

			var_tab0 = "f_ZT_" +  to_string(i) + "_V"; // Vertical container
			var_tab  = "f_ZT_" +  to_string(i) +  "_" + to_string(cpt_n_ZT[i]); // current TGH frame
			
		}
		//-------------------------
		else if(inf.zone == "ZC")
		{
			var_tab0 = "f_ZC"; // parent
			if(inf.opt_nl == 1) // newline
				cpt_n_ZC++;
			
			var_tab = "f_ZC_" + to_string(cpt_n_ZC);
		}
	
			
	
		f<<"	//-- d'apres la ligne de la classe "<<inf.nom_class<<": "<<endl;
		f<<"    // "<<inf.ligne<<endl;

		if(inf.opt_nl == 1) // newline
		{
			f<<"    auto  *"<<var_tab<<" = new TGHorizontalFrame("<<var_tab0<<", X, Y);"<<endl;
			f<<"    "<<var_tab0<<"->AddFrame("<<var_tab<<", fLH_L);"<<endl;
		}
		
		//----------------------------
		if(inf.widget == "N")
		{

			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........

			
			string style = "(TGNumberFormat::EStyle) 0"; // pour type = int
			if(inf.type=="double")
				style = "(TGNumberFormat::EStyle) 5"; // cf ligne 33 de https://root.cern.ch/doc/master/TGNumberEntry_8h_source.html

			int size = 2 + (inf.val).size();
			
			f<<"	"<<inf.nom_obj<<" = new TGNumberEntry("<<var_tab<<", p_"<<inf.nom_class<<"->"<<inf.nom<<", "<<size<<", "<<inf.Id<<", "<<style<<"); "<<endl;
			if((inf.help).size()>0)
				f<<"    "<<inf.nom_obj<<"->GetNumberEntry()->SetToolTipText(\""<< inf.help <<"\");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<",  fLH_L);"<<endl;
			f<<endl;

			//.... texte apres
			string var2 = "N_lab_" + inf.nom_class + "_" + inf.nom;
			f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.texte<<"\");"<<endl;
			f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
			f<<endl;

				
		}
		//----------------------------
		else 	if(inf.widget == "B")
		{

			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........

			
			f<<"	" << inf.nom_obj << " = new TGTextButton("<<var_tab<<", \""<<inf.texte<<"\", "<<inf.Id<<");"<<endl;
			if((inf.help).size()>0)
				f<<"    "<<inf.nom_obj<<"->SetToolTipText(\""<< inf.help <<"\");"<<endl;

			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<",  fLH_L);"<<endl;
			f<<endl;
				
		}
		//----------------------------
		else 	if(inf.widget == "T")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........
		
			f<<"	" << inf.nom_obj << " = new TGTextEntry("<<var_tab<<",  p_"<<inf.nom_class<<"->"<<inf.nom<<".c_str(), "<<inf.Id<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<endl;
				
		}
			//----------------------------
		else 	if(inf.widget=="File" || inf.widget=="Dir")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........
		
			f<<"	" << inf.nom_obj << " = new TGTextEntry("<<var_tab<<",  p_"<<inf.nom_class<<"->"<<inf.nom<<".c_str(), "<<inf.Id<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<endl;

			//..........
			if(inf.widget=="File")
				inf.texte = "Select file";
			else if(inf.widget=="Dir")
				inf.texte = "Select directory";
				
			f<<"	" << inf.nom_obj << "_B = new TGTextButton("<<var_tab<<", \""<<inf.texte<<"\", "<<inf.Id<<");"<<endl;
			if((inf.help).size()>0)
				f<<"    "<<inf.nom_obj<<"_B -> SetToolTipText(\""<< inf.help <<"\");"<<endl;

			f<<"    "<<inf.nom_obj<<"_B ->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<"_B,  fLH_L);"<<endl;
			f<<endl;
		}
		//----------------------------
		else 	if(inf.widget == "HS" || inf.widget == "INC")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........

			
			f<<"	" << inf.nom_obj << " = new TGHSlider("<<var_tab<<", 150, kSlider1|kScaleDownRight, "<<inf.Id<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->SetRange("<<inf.xmin<<", "<<inf.xmax<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->SetPosition(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<endl;
				
		}
		//----------------------------
		else 	if(inf.widget == "PB")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........
	
			f<<"	" << inf.nom_obj << " = new TGHProgressBar("<<var_tab<<", TGProgressBar::kFancy, 200);"<<endl;
			f<<"    "<<inf.nom_obj<<"->ShowPosition(kTRUE,kFALSE,\""<<inf.nom_obj<<": %.0f\");"<<endl;
			f<<"    "<<inf.nom_obj<<"->SetBarColor(\"green\");"<<endl;
			f<<"    "<<inf.nom_obj<<"->SetRange("<<inf.xmin<<", "<<inf.xmax<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->SetPosition(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
			//		f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<endl;
				
		}
		
		//----------------------------
		else 	if(inf.widget == "C")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........
		
			f<<"	" << inf.nom_obj << " = new TGCheckButton("<<var_tab<<",  \""<<inf.texte<<"\",  "<<inf.Id<<");"<<endl;
			if((inf.help).size()>0)
				f<<"    "<<inf.nom_obj<<"->SetToolTipText(\""<< inf.help <<"\");"<<endl;
			
			f<<"    "<<inf.nom_obj<<"->Resize(120, "<<inf.nom_obj<<"->GetDefaultHeight());"<<endl;
			f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<")"<<endl;
			f<<"       "<<inf.nom_obj<<"->SetState(kButtonDown);"<<endl;
			f<<"    else"<<endl;
			f<<"       "<<inf.nom_obj<<"->SetState(kButtonUp);"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<endl;
				
		}
		//----------------------------
		else 	if(inf.widget == "Color")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........
			f<<"    {\n";
			f<<"    Pixel_t col;" <<endl;
			f<<"    fClient->GetColorByName(\"red\", col); // -> col"<<endl;
			f<<"	" << inf.nom_obj << " = new TGColorSelect("<<var_tab<<",  col, "<<inf.Id<<");"<<endl;
			
			if((inf.help).size()>0)
				f<<"    "<<inf.nom_obj<<"->SetToolTipText(\""<< inf.help <<"\");"<<endl;
			
			f<<"    " << inf.nom_obj << "->Resize(40, 20);"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<"    }\n";
			f<<endl;

			

		}			
		//----------------------------
		else 	if(inf.widget == "L")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........
	
			f<<"	" << inf.nom_obj << " = new TGComboBox("<<var_tab<<", "<<inf.Id<<");"<<endl;
			for(int j=0; j<inf.L_l.size(); j++)
				f<<"    "<<inf.nom_obj<<"->AddEntry(\""<<inf.L_l[j]<<"\","<<j<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Resize(150, 20);"<<endl;
			f<<"    "<<inf.nom_obj<<"->Select( p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<endl;
		}
		//----------------------------
		else 	if(inf.widget == "LB")
		{
			//.... si  text avant
			if(inf.text.size()>0)
			{
				string var2 =  inf.nom_obj + "_text";
				f<<"	auto *" << var2 << " = new  TGLabel("<<var_tab<<" , \""<<inf.text<<"\");"<<endl;
				f<<"	"<<var_tab<<"->AddFrame("<<var2<<", fLH_L);"<<endl;
				f<<endl;
			}

			//..........
	
			f<<"	" << inf.nom_obj << " = new TGListBox("<<var_tab<<", "<<inf.Id<<");"<<endl;
			for(int j=0; j<inf.L_l.size(); j++)
				f<<"    "<<inf.nom_obj<<"->AddEntry(\""<<inf.L_l[j]<<"\","<<j<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Resize(150, 80);"<<endl;
			f<<"    "<<inf.nom_obj<<"->Select( p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
			f<<"    "<<inf.nom_obj<<"->Associate(this);"<<endl;
			f<<"    "<<var_tab<<"->AddFrame("<<inf.nom_obj<<");"<<endl;
			f<<endl;
		}

	} // for inf


	f<<"	// fenetre  generale  ===============\n\
	\n\
	MapSubwindows();\n\
	Resize();\n\
	MapWindow();\n";

	if(Titre.size()>0)
		f<<"SetWindowName(\""<<Titre<<"\"); // nom de la fenetre\n";
	else
		f<<"SetWindowName(\"Commandes de "<< src2 <<"\"); // nom de la fenetre\n";
	f<<endl;

	if(L_noms_TT.size()>0)
	{

		f<<"\n\
    timer = new TTimer(this, "<< L_noms_TT[0] <<");//create a TTimer to call the frame's HandleTimer(TTimer*) every X ms \n \
    timer->TurnOn();\n\
\n\
";
	}

	f<<"\n\
    //-- debloque le mutex\n\
	mtx_com->unlock(); \n\
\n\
    //-- Lance fonctions initialisation (ST)\n\
"<<endl;
	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.widget == "ST") 
		{
			f<<"	//-- d'apres la ligne de la classe "<<inf.nom_class<<": "<<endl;
			f<<"    // "<<inf.ligne<<endl;
			f<<"    p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
		}
		
	}
	
	
	f<<"\
\n\
\n\
    if(verbose)\n\
       cout<<\"com.cc fin de Com();\"<<endl;\n\
\n\
\n\
}"<<endl;

f<<"\n\
//========================\n\
Com::~Com()\n\
  {\n\
   Cleanup();\n\
";
if(L_noms_TT.size()>0)
{
	f<<"   timer->TurnOff();\n"<<endl;
}
f<<"\n\
   p_App->Terminate();\n\
  }\n\
";

f<<"\n\
//========================\n\
Bool_t Com::HandleTimer(TTimer*)\n\
{\n\
\n\
    if(verbose >= 2)\n\
       cout<<\"Com::HandleTimer() called\"<<endl;\n\
\n\
";
for(auto inf : L_infos) // boucle sur les objets
{
	if(inf.widget == "TT") 
	{
		f<<"	//-- d'apres la ligne de la classe "<<inf.nom_class<<": "<<endl;
		f<<"    // "<<inf.ligne<<endl;
		f<<"    p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
	}
		
}
	

f<<"\n\
 //    gSystem->ProcessEvents();\n\
	return kTRUE; \n\
}\n\
";


	
	f<<"\n\
//=====================================\n\
// This function is called after every event on the command window \n\
//     input : msg, p1, p2 : informations on the event \n\
//=====================================\n\
Bool_t Com::ProcessMessage(Long_t msg, Long_t p1, Long_t p2)\n\
{\n\
\n\
	int M = GET_MSG(msg), S=GET_SUBMSG(msg);\n\
\n\
    if(verbose)\n\
        cout<<\"Process_Message:  M = \"<<M<<\"  S = \"<<S<<\"  p1=\"<<p1<<\"  p2=\"<<p2<<endl;\n\
	mtx_com->lock();\n\
";

	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.widget == "N")
		{
			f<<"//-- N: Numerical entry"<<endl
			 <<"    if(M==4 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<" = "<<inf.nom_obj<<"->GetNumber();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;
		}
		else	if(inf.widget == "T")
		{
			f<<"//-- T:  Text entry"<<endl;
			f<<"    if(M==4 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<" = "<<inf.nom_obj<<"->GetText();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;
		}
		else	if(inf.widget=="File" || inf.widget=="Dir")
		{
			f<<"//-- File:  File Text "<<endl;
			f<<"    if(M==4 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<" = "<<inf.nom_obj<<"->GetText();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;

			
			f<<"//-- File:  File Name Selection "<<endl;
			f<<"    if(M==1 && S==3 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;

			f<<"\n\
             static TString dir(\".\"); \n\
			 TGFileInfo fi;"<<endl;
			if(inf.widget=="File")
			{
				if(inf.texte.size()==0) // alors format standard
					f<<"              const char *filetypes[] = {\"All files\", \"*\", 0, 0};"<<endl;
				else // inf.texte doit etre au format: \"texte\",\"*.txt\", etc par paires
				{
					ReplaceStringInPlace(inf.texte,"'","\"");  //--- on remplace les ' par des "
					f<<"\
             const char *filetypes[] = {"<<inf.texte<<", 0, 0};"<<endl;
				}
				f<<"\n\
             fi.fFileTypes = filetypes;"<<endl;
			}



			
			f<<"\n\
			 fi.fIniDir    = StrDup(dir); \n\
			 TGFileDialog *fFD = new TGFileDialog(fClient->GetRoot(), this, kFDOpen, &fi); \n\
			 //if(verbose) \n\
			 //	 printf(\"Open file: %s (dir: %s) \", fi.fFilename, fi.fIniDir); \n\
			 dir = fi.fIniDir; \n\
            "<<endl;


			if(inf.widget=="File")
			{
				f<<"\n\
            if(fi.fFilename != nullptr) // not empty file name\n\
		    {\n\
			 p_"<<inf.nom_class<<"->"<<inf.nom<<" = fi.fFilename; //file name\n\
			 p_com->Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"();\n\
  		    }\n\
"<<endl;
			}
			else 	if(inf.widget=="Dir")
			{
				f<<"\n\
               p_"<<inf.nom_class<<"->"<<inf.nom<<" = fi.fIniDir; // directory name\n\
			   p_com->Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"();\n\
"<<endl;		
			}

			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;

			f<<"        }";
			f<<endl;
		}
		else if(inf.widget == "B")
		{
			f<<"//-- B: Bouton"<<endl;
			f<<"    if(M==1 && S==3 && p1== "<<inf.Id<<" )"<<endl;
			f<<"    {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"       //  p_com->Met_a_jour();"<<endl;
			f<<"    }"<<endl;
			f<<endl;
		}
		else if(inf.widget == "M")
		{
			f<<"//-- M: Menu"<<endl;
			f<<"    if(M==1 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"    {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        // p_com->Met_a_jour();"<<endl;
			f<<"    }"<<endl;
			f<<endl;
		}
		else if(inf.widget == "MS")
		{
			f<<"//-- MS: Menu System"<<endl;
			f<<"    if(M==1 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"    {"<<endl;
					f<<"         int res = system(\""<<inf.attach_function<<"\");"<<endl;
			f<<"    }"<<endl;
			f<<endl;
		}

		else if(inf.widget == "HS" || inf.widget == "INC")
		{
			f<<"//-- HS: Slider"<<endl;
			f<<"    if(M==6 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<" = "<<inf.nom_obj<<"->GetPosition();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;
		}
		else if(inf.widget == "C")
		{
			f<<"//-- C: Check Button"<<endl;
			f<<"    if(M==1 && S==4 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         if("<<inf.nom_obj<<"->IsDown())"<<endl;
			f<<"            p_"<<inf.nom_class<<"->"<<inf.nom<<" = 1;"<<endl;
			f<<"         else"<<endl;
			f<<"            p_"<<inf.nom_class<<"->"<<inf.nom<<" = 0;"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;
		}
		else if(inf.widget == "Color")
		{
			f<<"//-- Color: "<<endl;
			f<<"    if(M==10 && S==2 && p1=="<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         Pixel_t col =  "<<inf.nom_obj<<"->GetColor();"<<endl;
			f<<"         Int_t r,g,b;"<<endl;
			f<<"         {\n";
			f<<"           TColor tc;		"<<endl;
			f<<"           tc.Pixel2RGB(col,r,g,b);"<<endl;
			f<<"           Int_t col2 = tc.GetColor(r,g,b);  // conversion"<<endl;
			f<<"           p_"<<inf.nom_class<<"->"<<inf.nom<<" = col2;"<<endl;
			f<<"         }\n";
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;
		}
		else if(inf.widget == "L")
		{
			f<<"//-- L: List Combo"<<endl;
			f<<"    if(M==1 && S==7 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<" = "<<inf.nom_obj<<"->GetSelected();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;
		}
		else if(inf.widget == "LB")
		{
			f<<"//-- LB: List Box"<<endl;
			f<<"    if(M==1 && S==7 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<" = "<<inf.nom_obj<<"->GetSelected();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        }";
			f<<endl;
		}
	}
	f<<"	mtx_com->unlock();"<<endl;
f<<"\n\
    if(verbose)\n\
       cout<<\"com.cc fin de Process_Messages();\"<<endl;\n\
\n\
";
	f<<"return kTRUE;"<<endl;
	f<<"}"<<endl<<endl;

	

	
	f<<endl<<endl;
	
	//------- Mises a jour -------------------------
	
	ostringstream code2;


	
    f<<"#include <TSystem.h>"<<endl;
	f<<"// =========================================\n			\
//  Met a jour toutes les valeurs de la fenetre de Commandes,\n\
//   a partir des donnees des classes\n\
void  Com::Met_a_jour()\n\
{\n\
\n\
    if(verbose)\n\
       cout<<\"com.cc Met_a_jour();\"<<endl;\n\
\n\
	//mtx_com->lock();\n\
";
	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.nom.size() == 0)
			continue;

				
		//... fonction individuelle
		code2 << "//=================="<<endl;
		code2 << "void  Com::Met_a_jour_"<<inf.nom_obj<<"()"<<endl;
		code2 << "{"<<endl;
		
		//..................
		ostringstream code;

		if(inf.widget == "N")
			code <<"	"<<inf.nom_obj<<"->SetNumber(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
		else if(inf.widget == "T")
			code <<"	"<<inf.nom_obj<<"->SetText(p_"<<inf.nom_class<<"->"<<inf.nom<<".c_str());"<<endl;
		else if(inf.widget=="File" || inf.widget=="Dir")
			code <<"	"<<inf.nom_obj<<"->SetText(p_"<<inf.nom_class<<"->"<<inf.nom<<".c_str());"<<endl;
		else if(inf.widget == "HS" || inf.widget == "INC")
			code <<"    "<<inf.nom_obj<<"->SetPosition(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
		else if(inf.widget == "PB")
			code <<"    "<<inf.nom_obj<<"->SetPosition(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
		else if(inf.widget == "C")
		{
			code <<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<")"<<endl;
			code <<"       "<<inf.nom_obj<<"->SetState(kButtonDown);"<<endl;
			code <<"    else"<<endl;
			code <<"       "<<inf.nom_obj<<"->SetState(kButtonUp);"<<endl;
		}
		else if(inf.widget == "Color")
		{
			code  <<"       {\n";
			code << "    	 TColor tc;"<<endl;
			code << "        Int_t  col = tc.Number2Pixel(p_"<<inf.nom_class<<"->"<<inf.nom<<");// convertit"<<endl;
			code <<"         "<<inf.nom_obj<<"->SetColor(col);"<<endl;
			code  <<"       }\n";
		}
		else if(inf.widget == "L" || inf.widget == "LB")
		{
			//... 
			if(inf.object !="") // si il y a une liste explicite
			{
				code <<"    "<<inf.nom_obj<<"->RemoveAll();"<<endl;
				code <<"    {"<<endl;
				code <<"     int len = 0; //  compute max length of words"<<endl;
				code <<"     for(int i=0; i < p_"<<inf.nom_class<<"->"<<inf.object<<".size(); i++)"<<endl;
				code <<"     {"<<endl;
				code <<"       "<<inf.nom_obj<<"->AddEntry( p_"<<inf.nom_class<<"->"<<inf.object<<"[i].c_str(), i);"<<endl;
				code <<"        if(p_"<<inf.nom_class<<"->"<<inf.object<<"[i].size() > len)"<<endl;
				code <<"             len = p_"<<inf.nom_class<<"->"<<inf.object<<"[i].size();"<<endl;
				code <<"     }"<<endl;
				code <<"     len = 6*len + 40; // scaling"<<endl;
				code <<"     if(len < 12)"<<endl;
				code <<"       len = 12;"<<endl;
				code <<"     else if(len > 500)"<<endl;
				code <<"       len = 500;"<<endl;
				code <<"      "<<inf.nom_obj<<"->Resize(len, 20);  // ajuste longueur du TGComboBox"<<endl;
				code <<"    }"<<endl;
								
				code <<"	MapSubwindows(); // il faut tout recalculer les tailles de la  fenetre"<<endl;
				code <<"	Resize();"<<endl;
				code <<"    MapWindow();"<<endl;
			}

			//.....
			code <<"    "<<inf.nom_obj<<"->Select( p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
		}
	
		code2 << code.str();
		code2 << "}"<<endl<<endl;
		f << code.str() <<endl;
		
	} // for

	f<<"\n\
    //-- debloque le mutex\n\
	//mtx_com->unlock(); \n\
\n\
";
	f<<"}"<<endl;

	f << code2.str() << endl;


	//--------- Evenement MIDI venant des controlleurs 
	if(L_midicontrol_name.size()>0) // there are some request for MIDI controls
	{
		f<<"//========================================\n";
		f<<"// MIDI event function. But it has to be executed in the thread of GUI root, not the midi event thread.\n";
		f<<"void Com::Midi_events(double deltatime, vector< unsigned char > * message, string midi_port_in_name)\n";
		f<<"{\n";
		f<<"  if((int)(*message)[0] != 0xfe )//special recurent midi messages\n";
		f<<"  {\n"; 
		f<<"  cout<<\"Com::Midi_events, port_in=\"<<midi_port_in_name;\n";
		f<<"  cout<<hex<<\"   message in hexa=\"<<(int)(*message)[0]<<\",\"<<(int)(*message)[1]<<\",\"<<(int)(*message)[2]<<endl;\n";
		f<<" }\n";
			
		for(auto inf : L_infos) // boucle sur les objets
		{
			if(inf.midicontrol.size()>0) // if there is midicontrol
			{
				f<<endl;
				f<<"  //-------------------\n";
				f<<"  // from line:"<<inf.ligne<<endl;
				f<<"  if(midi_port_in_name == \""<<inf.midi_name<<"\")\n";
				f<<"    {\n";
				f<<"      if(message->size() >= 3 && ((int)(*message)[0]) == "<<inf.midi_M<<" && ((int)(*message)[1]) == "<<inf.midi_C<<" ) \n";
				f<<"       {\n";

				f<<"        double val = (int)(*message)[2]; // value\n";
				f<<"        val = val/127.*("<<inf.midi_R2<<" - "<<inf.midi_R1<<") + "<<inf.midi_R1<<"; // conversion \n";
				f<<"         cout<<\"widget='"<<inf.widget<<"' val=\"<<val<<endl;\n";

				if(inf.widget == "N" || inf.widget == "HS" || inf.widget == "VS" || inf.widget == "INC" ) //entree numerique
					f<<"        p_"<<inf.nom_class<<"->"<<inf.nom<<" = val; // val -> c++ value\n";
				else if(inf.widget == "B")
				{
					f<<"         if( val != 0) // condition for action\n"<<endl; 
					f<<"            p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl; // call function
				}
				else if(inf.widget == "C")
				{
					f<<"         if( val != 0) // condition for action\n"<<endl;
					f<<"          { //... switch c++ value\n";
					f<<"           if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 0)\n"<<endl;
					f<<"              p_"<<inf.nom_class<<"->"<<inf.nom<<" = 0;\n"<<endl;
					f<<"           else\n"<<endl;
					f<<"              p_"<<inf.nom_class<<"->"<<inf.nom<<" = 1;\n"<<endl;
					f<<"          }\n";
				}

				
				f<<"        Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"(); // c++ value -> widget\n";
				if(inf.attach_function.size()>0) // si il faut appeler fonction
				{
					f<<"       //.... call attached function"<<endl;
					if(inf.widget != "MS")
						f<<"       p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
				}
					
			
				f<<"       }\n";
				f<<"    }\n";
				
	
				
			}
		}

		
		f<<"}\n";

		
	} // if (L_midicontrol_name.size()>0

	
	//---------------------------------
	f.close(); // ferme le fichier com.cc

	
	
	//=======================================
	nom_com = rep_src2 + "/com.h";
	
	//---fichier com.h ---------------------------------
//	cout<<"Ecriture du fichier :"<<nom_com<<endl;
	f.open(nom_com);
	
	//-----------------------------------------------------------------
	f<<"\n\
#if !defined(__COM_MODEL_H)\n\
#define __COM_MODEL_H\n\
//THIS  C++  CODE com.h IS WRITTEN AUTOMATICALLY BY: makef.cc\n\
// AND IS FOR COMPILATION BY: G++\n\
//============================================================\n\
\n\
# include <TCanvas.h> \n\
# include <TGFrame.h> \n\
# include <TGButton.h> \n\
# include <TGNumberEntry.h> \n\
# include <TGMenu.h> \n\
# include <TGLabel.h> \n\
# include <TApplication.h> \n\
# include <TGTab.h> \n\
# include <TGSlider.h> \n\
# include <TGProgressBar.h> \n\
#include<TGFileDialog.h> \n\
# include <TGComboBox.h>  \n\
# include <TTimer.h>  \n\
# include <TSystem.h>  \n\
# include <thread> \n\
# include <chrono> \n\
using namespace std::chrono; \n\
using namespace std::this_thread; \n\
# include <iostream> \n\
using namespace std; \n\
#include <string> \n\
# include <mutex> \n";

	for(auto nf : L_noms_fichiers)
		f<<"#include \""<<nf<<"\"\n";		
		


	f<<"\n\
//==================\n\
void Lance_com(";

	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<");"<<endl;
	}
	f<<"\n\
//===================\n\
class Com: public  TGMainFrame\n\
{\n\
public :\n\
\n\
	Com(";
	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<");"<<endl;
	}

	f<<"TApplication* p_App;"<<endl;
	f<<"TTimer* timer;"<<endl;
	f<<"virtual ~Com();"<<endl;
	f<<"Bool_t HandleTimer(TTimer*);"<<endl;
	
	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.nom.size() == 0)
			continue;

				
		if(inf.widget == "N")
			f<<"	TGNumberEntry *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget == "T")
			f<<"	TGTextEntry *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget=="File" || inf.widget=="Dir")
		{
			f<<"	TGTextEntry *"<<inf.nom_obj<<";"<<endl;
			f<<"	TGTextButton *"<<inf.nom_obj<<"_B;"<<endl;
		}
		else if(inf.widget == "HS")
			f<<"	TGHSlider *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget == "PB")
			f<<"	TGHProgressBar *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget == "C")
			f<<"	TGCheckButton *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget == "Color")
			f<<"	TGColorSelect *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget == "L")
			f<<"	TGComboBox *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget == "LB")
			f<<"	TGListBox *"<<inf.nom_obj<<";"<<endl;
		else if(inf.widget == "B")
			f<<"	TGTextButton *"<<inf.nom_obj<<";"<<endl;
	}
	
	f<<"\n\
	Bool_t ProcessMessage(Long_t msg, Long_t p1, Long_t p2);\n\
	void  Met_a_jour();"<<endl;
	
	for(auto inf : L_infos) // boucle sur les objets
	{
		if(inf.nom.size() == 0)
			continue;

		f << "     void  Met_a_jour_"<<inf.nom_obj<<"();"<<endl;
	}

	//--------------
	f<<"\n    string window_title = \""<<Titre<<"\"; // name of the main window \n\n";
	
	//-------Midicontrol--------------------
	if(L_midicontrol_name.size()>0) // there are some request for MIDI controls
	{
		f<<"\n    //......midicontrols.............\n";
		f<<"     int opt_midicontrol = 1; // means there are midicontrols\n";
		f<<"     const vector<string> L_midicontrol_name = {";
		for(int i=0; i<L_midicontrol_name.size(); i++)
		{
			f<<"\""<<L_midicontrol_name[i]<<"\"";
			if(i<L_midicontrol_name.size()-1)
				f<<",";
			else
				f<<"};\n";
		}
		f<< "     void Midi_events(double deltatime, vector< unsigned char > * message, string midi_port_in_name);\n\n";
		
		
	}
else
{
	f<<"       int opt_midicontrol = 0; // means there are no midicontrols\n";
}
//--------------------


	f<<"       int verbose = 0; \n";
	
	f<<"}; // end of class declaration\n\
\n\
//============\n\
\n\
extern Com *p_com;  // pointeur sur l'objet (declare dans com.cc)\n\
extern mutex *mtx_com;  // pointeur sur l'objet (declare dans com.cc)\n\
\n\
#endif\n\
";





	//---------------------------------
	f.close(); // ferme le fichier




	
//------------------------------	
	if(verbose>=1)
	{
		cout<<" Fin de Fonction Ecriture_fichiers_cpp()"<<endl;
		cout<<"----------------------------"<<endl<<endl;
	}
}



//============================
// fonction pour make_gui
/*
 entree:  a partir des informations contenues dans
  L_infos

sortie: ecrit com.cc et com.h
*/
void 	Ecriture_fichiers_cpp_JUCE()
{

	if(verbose>=1)
	{
		cout<<"=========================================================="<<endl;
		cout<<"## == Part 2: Ecriture des fichiers com.cc com.h for JUCE  =========="<<endl;
		cout<<"=========================================================="<<endl<<endl;
	
	}



	//==== correction of a bug in juce for object juce::Label()?
/*
	for(auto &inf : L_infos) // boucle sur les objets
		if(inf.text.size() == 0)
			inf.text=" "; // non empty
*/

	//===== test if there are periodic "callback" and put ID to them
	int test_TT = 0; // number of callback needed (MultiTimer)
	for(auto &inf : L_infos) // boucle sur les objets
		if(inf.widget == "TT")
		{
			inf.ID = test_TT;
			test_TT++;
		}

	//===== test if we need open files window
	int test_File = 0; // number
	for(auto &inf : L_infos) // boucle sur les objets
		if(inf.widget == "File" || inf.widget == "Dir")
			test_File++;

	
	//===== test if we need open color window
	int test_Color = 0; // number
	for(auto &inf : L_infos) // boucle sur les objets
		if(inf.widget == "Color")
			test_Color++;

	
	//===== test if we need open  window
	int test_Window = 0; // number
	for(auto &inf : L_infos) // boucle sur les objets
		if(inf.widget == "Window" ||  inf.widget=="Window2" ||  inf.widget=="Editor")
			test_Window++;


//==== changement de convention : index 0 est pour ZC qui deviendra ZT_0
	vector<string> L = {"ZC"};
	L_sous_tabs.insert(L_sous_tabs.begin(), L); // on insert au debut 
	L_noms_tabs.insert(L_noms_tabs.begin(), "ZC");


	
	//=== assign Id of tabs for objects
	for(int j= 0; j< (int)L_sous_tabs.size(); j++) // loop over the tab.
	{
		// construct full tab name
		string name;
		for(int k=0; k<L_sous_tabs[j].size(); k++)
		{
			name += L_sous_tabs[j][k];
			if( k < L_sous_tabs[j].size()-1)
				name += "__";
		}
		//.......
		for(auto &inf : L_infos)
		{
			if (inf.nom_tab == name)
			{
				inf.Id = "ZT_" + to_string(j);
				inf.Idj = j;
//				cout<<"j="<<j<<" name = "<<name<<" inf.nom_obj="<<inf.nom_obj<<endl;
			}
		}	
	}
     //======== prepare list of sub-tabs
	//--- subtabs j2 of j in this zone.	Conditions are: (1) longueur de j2 = (longueur de j) +1 et (2)  parmi les elements j2 > j  de longueur > j qui suivent
	vector<vector<int>> L_sous_tabs_index;
	
	for(int j=0; j< (int)L_sous_tabs.size(); j++) // loop over the tab.
	{
		int	Lj = L_sous_tabs[j].size();
		if(j==0) // special ZC
			Lj=0;
		
		vector<int> Ls;
		
		for(int j2= j+1; j2< (int)L_sous_tabs.size(); j2++)
		{
			if(L_sous_tabs[j2].size() <= Lj) // condition (2)
				break;
			if(L_sous_tabs[j2].size() == (Lj+1)) // condition (1)
				Ls.push_back(j2);

		} // for j2
		L_sous_tabs_index.push_back(Ls);
	}//for j

	//--- affiche
	
//	for(int j=0; j< L_sous_tabs_index.size(); j++)
//		cout<<"j="<<j<<",  L_sous_tabs_index["<<j<<"]="<<L_sous_tabs_index[j]<<endl;

	 //======== prepare another list of sub-tabs
	// ex: j=10, L_sous_tabs_inclusions[10]=[8,6,1,0]
	vector<vector<int>> L_sous_tabs_inclusions; 
	
	
	for(int j=0; j< (int)L_sous_tabs.size(); j++) // loop over the tab.
	{
		vector<int> L;

		int size = L_sous_tabs[j].size();
		
		for(int k = j-1; k>=1; k--)
		{
			if(L_sous_tabs[k].size() == (size-1))
			{
				L.push_back(k);
				size--;
			}
		}
		L.push_back(0); // main window
		
		L_sous_tabs_inclusions.push_back(L);	
	}//for j

	//--- affiche
/*
	cout<<"-----------"<<endl;
	for(int j=0; j<  L_sous_tabs_inclusions.size(); j++)
		cout<<"j="<<j<<", L_noms_tabs["<<j<<"]="<<L_noms_tabs[j]<<",\t\t L_sous_tabs_inclusions["<<j<<"]="<< L_sous_tabs_inclusions[j]<<endl;
*/
	

	//====== Compute position of each object and position of horizontal frames that contains objects

	int x_window=0, y_window=0; // position of windows (will be incremented)

	vector<int> L_sous_tabs_h1T; //  h1T :height above subtabs
	int w_tot = 100; // total width ajusted below
	int h_tot = 100; // total height  ajusted below

	//....
	int size_c = 8; // size of a character in pixels
	int size_N = 50;// size of "N" in pixels
	int size_T = 80;// size of "T" in pixels
	int size_HS = 120;// size of "HS" in pixels
	int size_B = 20;// size of "B" vide in pixels
	int size_C = 30;// size of "C" in pixels
	int size_L = 120;// size of "L" in pixels
	int size_File = 130;// size of "File" in pixels
	int size_Color = 30;// size of "Color" in pixels
	int size_tab = 35;// vertical  size of tab in pixels
		
	int xD = 12, yD=10; // additionnal space

	for(int j= 0; j< (int)L_sous_tabs.size(); j++) // loop over the tab.
	{
		
		
		int xF=0, yF=0, wF=0, hF=0; // x,y,width,heigth of the next horizontal frame that contains objects
		int x = 0, y= yD, w=0,h=0; // x,y,width,heigth of the next object

		int wT=0, h1T=0, h2T=0; // size of the tab


		if(j ==0 && L_noms_menus.size() > 0)
		{
			//---- new position
			x = xF + wF + xD;
			y = yF + yD;
				
			//---- we will put a button first
			w = 10 + 80;
			h = 20;
				
			//----- adapt the frame
			wF += (xD + w);
			if((yD+h)>hF)
				hF = yD + h;
			
			if(wF>wT)
				wT=wF;
		}

		
		for(auto &inf : L_infos) // objects
			if (inf.Idj == j) 	//--- Define selection of objects for this tab
			{
				//------- if new line
				if(inf.opt_nl == 1) // new horizontal frame
				{
					//... compute next HFrame
					yF = yF + hF;
					wF = 0;
					hF = 0;
					//...  object
					x = 0;
					y = yF;
				}
				
				//---- new position
				x = xF + wF + xD;
				y = yF + yD;
				
				//---- compute size of the object
				w = 80;
				h = 20;
				
				if(inf.widget == "N")
				{
					w =  inf.text.size()*size_c + xD + size_N + inf.texte.size()*size_c + xD;
					h = 20;
				}
				
				else if(inf.widget == "T")
				{
					w =  inf.text.size()*size_c + xD + size_T + inf.texte.size()*size_c + xD;
					h = 20;
				}
			
				else if(inf.widget == "HS"  || inf.widget == "PB" || inf.widget == "INC") // horizontal slider
				{
					w =  inf.text.size()*size_c + xD + size_HS + inf.texte.size()*size_c + xD;
					h = 20;
				}
				else if(inf.widget == "C") // check button
				{
					w =  inf.text.size()*size_c + xD + size_N + inf.texte.size()*size_c + xD;
					h = 20;
				}
				else if(inf.widget == "Color") // select color
				{
					w =  inf.text.size()*size_c + xD + size_Color  + xD;
					h = 20;
				}
				else if(inf.widget == "L" || inf.widget == "LB") // Combo box: choose in a list
				{
					w =  inf.text.size()*size_c + xD + size_L + inf.texte.size()*size_c + xD;
					h = 20;
				}
				else if(inf.widget == "B" || inf.widget == "Window" || inf.widget=="Editor" || inf.widget == "HLINK") // Text Button
				{
					w =  inf.text.size()*size_c + xD + size_B + inf.texte.size()*size_c + xD;
					h = 20;
				}
				else if(inf.widget == "Window2") 
				{
					w =  inf.text.size()*size_c + xD + size_B + inf.texte.size()*size_c + xD;
					if(inf.W > w)
						w = inf.W;
					h = 20 + inf.H;
				}
				else if(inf.widget=="File" || inf.widget=="Dir") // Text Button
				{
					w =  inf.text.size()*size_c + xD + size_File + size_B + inf.texte.size()*size_c + xD;
					h = 20;
				}


				
				//--- memorize position of the object for later use
				inf.x = x;
				inf.y = y;
				inf.w = w;
				inf.h = h;
				

				//----- adapt the frame
				wF += (xD + w);
				if((yD+h)>hF)
					hF = yD + h;

				if(wF>wT)
					wT=wF;
				
				//	cout<<"tab j="<<j<<" object inf.nom="<<inf.nom<<" x="<<x<<" y="<<y<<" w="<<w<<" h="<<h<<endl;

			} // for inf


		//--- vertical size of the tab
		h1T = yF + hF + yD;

		if(w_tot < wT) // from size of objects
			w_tot = wT;

		int wsT=0; // from size of tabs
		for(int j2 = 0; j2 < L_sous_tabs_index[j].size(); j2++)
		{
			int k =  L_sous_tabs_index[j][j2];
			int k2 =  L_sous_tabs[k].size()-1;
			int wsT2 = xD + L_sous_tabs[k][k2].size()*size_c; 
			if(wsT2<60) // mini
				wsT2 = 60;
			wsT += wsT2;  
		}
		//	cout<<"j="<<j<<" wsT="<<wsT<<endl;
		
		if(w_tot < wsT) // from size of objects
			w_tot = wsT;

		
		
		L_sous_tabs_h1T.push_back(h1T);
		
		
	}// for j, sous_tabs


//---- compute total height h_tot afterwards
/*	
	for(int j=0; j<L_sous_tabs_inclusions.size(); j++)
	{
//		int h =   L_sous_tabs_h1T[j]; // height above subtab
		int h = 0;
		cout<<"j="<<j<<", L_noms_tabs["<<j<<"]="<<L_noms_tabs[j]<<",  L_sous_tabs_inclusions["<<j<<"]="<< L_sous_tabs_inclusions[j]<<endl;
			
		for(int j2=0; j2<L_sous_tabs_inclusions[j].size(); j2++)
		{
			
			int k= L_sous_tabs_inclusions[j][j2];
			if(k == 0) // this is ZC (Zone commune)
				h +=  L_sous_tabs_h1T[k]; // we count the heigh
			else
				h += 30; // add the height of a tab menu

			cout<<"        k="<<k<<" L_sous_tabs_h1T["<<k<<"]="<< L_sous_tabs_h1T[k]<<endl;
		}
		h +=  L_sous_tabs_inclusions[j][0]; // last window
//		cout<<"j="<<j<<" h="<<h<<endl;
		if(h_tot < h)
			h_tot = h;
	}
	
	cout<<"w_tot="<<w_tot<<" h_tot="<<h_tot<<endl;
*/

	h_tot = 0;
	w_tot = 0;
	
	for(auto &inf : L_infos) // objects
	{
	
		
		if(w_tot < (inf.x + inf.w))
			w_tot = inf.x + inf.w;


		int H = inf.y + inf.h;

		if(inf.Idj >= 0)
			H += size_tab * L_sous_tabs_inclusions[inf.Idj].size();  // we add size of the tab widgets

		if(inf.Idj != 0 && h_tot < H)
		{
			h_tot = H;
			//	cout<<"inf.nom="<<inf.nom<<" inf.x="<<inf.x<<" inf.y="<<inf.y<<" H="<<H<<"\n   inf.ligne="<<inf.ligne<<endl;
			//cout<<"   inf.nom_fichier="<<inf.nom_fichier<<endl;
		}
	}

	h_tot +=  L_sous_tabs_h1T[0]; // add ZC common zone


	if(h_tot<100)
		h_tot = 100;
	if(w_tot<100)
		w_tot = 100;
	
//	cout<<"w_tot="<<w_tot<<" h_tot="<<h_tot<<endl;
	


	
    //======== write file com.h for JUCE ===============================
	string nom_com = rep_src2 + "/com.h";
	
//---fichier com.h ---------------------------------
//	cout<<"Ecriture du fichier :"<<nom_com<<endl;

	ofstream f(nom_com);
	

	f<<"//This code  C++ com.h is written automatically by: makef.cc, so do write in it. It concerns a Plugin in JUCE. "<<endl;
	f<<"//========================================================================================="<<endl;

	//---  entetes-----------------------------
	f<<"#pragma once\n";
	f<<"#include \"Source/JuceHeader.h\"\n";
	f<<"using namespace std;"<<endl;
	f<<"using namespace juce;"<<endl;


//	for(auto nf : L_noms_fichiers) 
//		f<<"#include \"./"<<nf<<"\"\n";	

	
	f<<"//============\n";
	f<<"// declared below\n";
	f<<"class Editor;"<<endl;
	f<<"class Com;"<<endl;
	f<<"class ColourChangeButton;"<<endl;
	f<<"\n";
	f<<"//============\n";
	f<<"// object declared in com.cc\n";
	f<<"//extern Com *p_com;\n";
	f<<"//extern mutex *mtx_com;\n";



	f<<"\n";
	for(auto nc : L_noms_classes)
	{
		f<<"class "<<nc<<";\n";
//		f<<"//extern "<<nc<<" *p_"<<nc<<"; // in com.cc"<<nc<<endl;
	}
	f<<"\n";
	



	//----------------------------

	f<<"//===============================\n";
	f<<"// override  design\n";
	f<<"\n";
	f<<"class CustomTabLookAndFeel : public LookAndFeel_V4\n";
	f<<"{\n";
	f<<"public:\n";
	f<<"    CustomTabLookAndFeel()\n";
	f<<"		{\n";
	f<<"			//setColour(TabbedButtonBar::ColourIds::frontTextColourId, Colours::yellow); // Couleur du texte du tab sélectionné\n";
	f<<"			setColour(TabbedButtonBar::ColourIds::frontTextColourId, Colour(0xb5, 0x89, 0x00) ); // kyellow: Color of selected tab\n";
	f<<"			setColour(Slider::ColourIds::thumbColourId, Colour(0xcb, 0x4b, 0x16) ); // korange: color of sliders\n";
	
	f<<"		}\n";
	f<<"\n";
	f<<"    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override\n";
	f<<"		{\n";
	f<<"			LookAndFeel_V4::drawTabButton(button, g, isMouseOver, isMouseDown);\n";
	f<<"			// Ajoutez ici un code personnalisé pour dessiner les onglets si nécessaire\n";
	f<<"		}\n";
	f<<"};\n";
	f<<"\n";

	//---------------------------
	for(auto inf : L_infos)
		if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget=="Editor")
		{
			
			f<<"//==============================================================================\n";
			f<<"// A Window\n";
			f<<"class TCanvas_"<<inf.nom_obj<<" : public juce::DocumentWindow\n";
			f<<"{\n";
			f<<"public:	\n";
			f<<"    Com * p_com = nullptr;\n";

			if( inf.widget=="Editor" )
			{
				f<<"    CodeEditorComponent *p_editor = nullptr;\n";
			}
			
			f<<"	TCanvas_"<<inf.nom_obj<<"(Com *p_i, const juce::String &name, juce::Colour backgroundColour, int requiredButtons, bool addToDesktop=true);\n";
			f<<"	~TCanvas_"<<inf.nom_obj<<"() override;\n";
			f<<"\n";
			f<<"    int status = 0; //0 : internal, 1: external\n";
			f<<"	void resized() override;\n";
			f<<"	void moved() override;\n";
			f<<"	void paint(juce::Graphics& g) override;\n";
			if(inf.mouseDown)
				f<<"	void mouseDown (const juce::MouseEvent &event) override;\n";
			if(inf.mouseMove)
			{
				f<<"	void mouseMove (const juce::MouseEvent &event) override;\n";
				f<<"	void mouseExit (const juce::MouseEvent &event) override;\n";
			}
			if(inf.mouseWheelMove)
				f<<"	void mouseWheelMove (const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) override;\n";
			if(inf.keyPressed)
				f<<"	virtual bool  keyPressed (const juce::KeyPress &key) override;\n";


			f<<"	void closeButtonPressed();\n";
			
			f<<"\n";
			f<<"//----To detect leak memory : Put class name---------------\n";
			f<<"	JUCE_LEAK_DETECTOR (TCanvas_"<<inf.nom_obj<<")\n";
			f<<"};\n";

		} // for inf
	
	f<<"\n";
	f<<"//-- Below is the list of "<< L_sous_tabs.size() + 1<< " windows for each tab window + ZC.\n";
	f<<"\n";
	

	
//---- loop over the tab windows
	// remark: cast (int) is important
	for(int j= 0; j< (int)L_sous_tabs.size(); j++) // loop over the tab.
	{

		ostringstream s; // code of the new Tab
		s<<"Page_ZT_"<<j;
	
		//--------------

		
		f<<"\n";
		f<<"//=============================================\n";
		f<<"class "<<s.str()<<" : public juce::Component \n";
		f<<"{\n";
		f<<" public:\n";
		f<<"   "<<s.str()<<"(Com *p_i);\n";
		f<<"   ~"<<s.str()<<"();\n";
		f<<"\n";
		f<<"    // resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled).\n";
		f<<"    void resized() override;\n";
		f<<"    void paint(juce::Graphics& g) override;\n";
		
		f<<"    Com *p_com = nullptr;\n";

		f<<"    int ZC_size = 20; // vertical size of zone above tabs\n";
		f<<"\n";



		
		//--- subtabs j2
		f<<"\n";
		f<<"    //------------\n";
		f<<"    juce::TabbedComponent *tab;\n";


		f<<"    CustomTabLookAndFeel customLookAndFeel;\n";
		
		if(j ==0 && L_noms_menus.size() > 0)
		{
			f<<"\n";
			f<<"    //------------\n";
			f<<"    juce::TextButton *b_menu; // button for general menu on ZC\n";
		}

		
		f<<"\n";
		f<<"//----To detect leak memory---------------\n";
		f<<"JUCE_LEAK_DETECTOR ("<<s.str()<<")\n";
	
		f<<"};\n";
		
	} // for j, loop over tabs


	

	

//---- write the main class Com()	

	f<<"\n";
	f<<"//=====================\n";
	f<<"// Main class for widgets\n";
	f<<"\n";

	if(test_TT == 0)
		f<<"class Com\n";
	else
		f<<"class Com   : public juce::MultiTimer\n";
	
	f<<"{\n";
	f<<"public:\n";

	f<<"    int verbose = 0; // 1: used for debug\n";
	f<<"    string window_title = \""<<Titre<<"\"; // name of the main window \n\n";

	f<<"    Com(Editor *p_i, ";
	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<");"<<endl;
	}
	
	f<<"	~Com();\n";




	f<<"\n";
	for(auto nc : L_noms_classes)
	{
		f<<"    "<<nc<<" *p_"<<nc<<";"<<endl;
	}
	f<<"\n";
	



	f<<"	void resized();\n";





	
	if(test_TT >=  1)
		f<<"    void timerCallback(int ID); // derived from class MultiTimer\n";

	if(test_File >=  1)
	{
		f<<"	juce::FileChooser chooser; //used to open files or dir.\n";
		f<<"//	std::unique_ptr<FileChooser> chooser;\n";
	}

	f<<"\n";
	f<<"	//-----------\n";
	f<<"	Editor *p_e = nullptr;\n";

	f<<"\n";
	f<<"   //some pointers for easer access to tabs by their full name\n"; 

	
	for(int j= 0; j< (int)L_sous_tabs.size(); j++)
	{
		f<<"	Page_ZT_"<<j<<"  * p_Tab_"<< Get_Tab_name(j) <<";\n";
		
	}//for j



	f<<"\n";
	f<<"  //--- list of objects in this zone\n";

	for(auto inf : L_infos) // objects
	{
		//--- Define selection of objects for this tab
		//	if (inf.Idj == j)
		{

			f<<"\n";
			f<<"	//-- from the instruction of class: "<<inf.nom_class<<": "<<endl;
			f<<"    // "<<inf.ligne<<endl;
				
			
				
			if(inf.widget == "N" || inf.widget == "T")
			{
				f<<"    juce::TextEditor *"<<inf.nom_obj<<";\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_texte;\n";
			}
					
				
			
			else if(inf.widget == "HS"  || inf.widget == "INC") // horizontal slider
			{
				f<<"    juce::Slider *"<<inf.nom_obj<<";\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_texte;\n";

			}
			else if(inf.widget == "PB") // progress bar
			{
				f<<"    juce::ProgressBar *"<<inf.nom_obj<<";\n";
				f<<"    double "<<inf.nom_obj<<"_x = 0; // value of the ProgressBar\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_texte;\n";
			}
			else if(inf.widget == "C") // check button
			{
				f<<"    juce::ToggleButton *"<<inf.nom_obj<<";\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_texte;\n";
			}
			else if(inf.widget == "Color") // select color
			{
				f<<"    ColourChangeButton *"<<inf.nom_obj<<"; // class defined above\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
//					f<<"    juce::Label *"<<inf.nom_obj<<"_texte;\n";
			}
			else if(inf.widget == "L" || inf.widget == "LB") // Combo box: choose in a list
			{
				f<<"    juce::ComboBox *"<<inf.nom_obj<<" = nullptr;\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_texte;\n";
			}
			else if(inf.widget == "B")
			{
				f<<"    juce::TextButton *"<<inf.nom_obj<<";\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
			}
			else if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor")
			{
				f<<"    juce::TextButton *"<<inf.nom_obj<<"_button;\n";
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
				f<<"    TCanvas_"<<inf.nom_obj<<" *"<<inf.nom_obj<<" = nullptr;\n";
				f<<"    void Show_Hide_Window_"<<inf.nom_obj<<"();\n";
				if(inf.widget == "Editor")
					f<<"    CodeDocument "<<inf.nom_obj<<"_code;\n";
					
			}
			else if(inf.widget=="File" || inf.widget=="Dir") // Text Button
			{
				f<<"    juce::Label *"<<inf.nom_obj<<"_text;\n";
				f<<"    juce::TextEditor *"<<inf.nom_obj<<"_ed;\n";
				f<<"    juce::TextButton *"<<inf.nom_obj<<";\n";
			}
			else if(inf.widget == "HLINK")
			{
				f<<"    juce::HyperlinkButton *"<<inf.nom_obj<<";\n";
			}


		} // if

			
	} // for inf: objects


		

	//-----------------------
	f<<"\n";
	f<<"	//-- transfert of values --------\n";


	for(auto inf : L_infos)
		if(inf.widget != "TITRE" && inf.widget != "LINK" && inf.widget != "TT")
		{
			f<<"    void Met_a_jour_"<<inf.nom_obj<<"();  //  c++ value --> widget value\n";
			f<<"    void Process_message_"<<inf.nom_obj<<"();  //  widget value --> c++ value\n";
			
		}
	
	f<<"\n";
	f<<"//----To detect leak memory---------------\n";
	f<<"JUCE_LEAK_DETECTOR (Com)\n";
	
	
	f<<"\n";
	f<<"};\n";

	if(test_Color >= 1)
	{
		f<<"//==========================================================\n";
		f<<"// A TextButton that pops up a colour chooser to change its colours.\n";
		f<<"class ColourChangeButton  : public juce::TextButton, public juce::ChangeListener\n";
		f<<"{\n";
		f<<"public:\n";
		f<<"	void (Com::*f)() = nullptr; // pointor to function to call\n";
		f<<"	Com *p_com = nullptr;\n";
		f<<"\n";
		f<<"	//............\n";
		f<<"    ColourChangeButton(Com *p_i): TextButton (\"Click to change colour\")\n";
		f<<"		{\n";
		f<<"			p_com = p_i;\n";
		f<<"			setSize (10, 24);\n";
		f<<"			changeWidthToFitText();\n";
		f<<"		}\n";
		f<<"	//............\n";
		f<<"    void clicked() override\n";
		f<<"		{\n";
		f<<"			auto colourSelector = std::make_unique<juce::ColourSelector> (juce::ColourSelector::showAlphaChannel\n";
		f<<"																		  | juce::ColourSelector::showColourAtTop\n";
		f<<"																		  | juce::ColourSelector::editableColour\n";
		f<<"																		  | juce::ColourSelector::showSliders\n";
		f<<"																		  | juce::ColourSelector::showColourspace);\n";
		f<<"\n";
		f<<"			colourSelector->setName (\"background\");\n";
		f<<"			colourSelector->setCurrentColour (findColour (TextButton::buttonColourId));\n";
		f<<"			colourSelector->addChangeListener (this);\n";
		f<<"			colourSelector->setColour (juce::ColourSelector::backgroundColourId, juce::Colours::transparentBlack);\n";
		f<<"			colourSelector->setSize (300, 400);\n";
		f<<"			juce::CallOutBox::launchAsynchronously (std::move (colourSelector), getScreenBounds(), nullptr);\n";
		f<<"		}\n";
		f<<"\n";
		f<<"    using TextButton::clicked;\n";
		f<<"\n";
		f<<"    void changeListenerCallback (juce::ChangeBroadcaster* source) override\n";
		f<<"		{\n";
		f<<"			if (auto* cs = dynamic_cast<juce::ColourSelector*> (source))\n";
		f<<"				setColour (TextButton::buttonColourId, cs->getCurrentColour());\n";
		f<<"            //p_com->Process_message_C1_choix_color();\n";
		f<<"	        if(f != nullptr)";
		f<<"			   (p_com->*f)();";
		f<<"            //cout<<\"Correct code in com.h, makef.cc, find solution \";\n";
		f<<"		}\n";

		f<<"//----To detect leak memory---------------\n";
		f<<"JUCE_LEAK_DETECTOR (ColourChangeButton)\n";
		f<<"\n";
		
		f<<"};\n";
	}


//---------------------------- 
	
	f<<"//==========================================================\n";
	f<<"/*\n";
	f<<"Parameters of the plugin\n";
	f<<"*/\n";
	f<<"\n";
	f<<"class Processor; \n";
	f<<"\n";
	f<<"class Parameters\n";

	
	f<<"{\n";
	f<<"public:\n";



	f<<"   Parameters(";
	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<");"<<endl;
	}
	
	f<<"	~Parameters();\n";

	f<<"	mutex mtx_params;  // used to access Parameters\n";
	f<<"	Com *p_com = nullptr;\n";

	f<<"\n";
	f<<"	//.... parameters of objects in com.h\n";
	for(auto inf : L_infos)
		if(inf.widget == "Window" || inf.widget == "Window2"|| inf.widget == "Editor")
		{
			f<<"	int "<<inf.nom_obj<<"_cx = 20, "<<inf.nom_obj<<"_cy = 20, "<<inf.nom_obj<<"_wx = 600,  "<<inf.nom_obj<<"_wy = 600;\n";
		} // for inf
	f<<"\n";
	
	f<<"//........\n";
	for(auto nc : L_noms_classes)
	{
		f<<"    "<<nc<<" *p_"<<nc<<";"<<endl;
	}
	f<<"\n";
	
	f<<"//........\n";
	for(auto inf : L_infos)
	{
		if(inf.nom.size() == 0 || inf.opt_param == 0)
			continue;

		if(inf.widget == "L" || inf.widget == "LB")
			f<<"	AudioParameterChoice* P_"<<inf.nom_obj<<";\n";


		else if(inf.widget == "HS" || inf.widget == "INC")
		{
			if(inf.type == "int")
			{
				f<<"	AudioParameterInt* P_"<<inf.nom_obj<<";\n";
				if(inf.nom2.size()>0)
					f<<"	AudioParameterInt* P_"<<inf.nom_class<<"_"<<inf.nom2<<";\n";
				if(inf.nom3.size()>0)
					f<<"	AudioParameterInt* P_"<<inf.nom_class<<"_"<<inf.nom3<<";\n";
			}
			else if(inf.type == "double")
			{
				f<<"	AudioParameterFloat* P_"<<inf.nom_obj<<";\n";
				if(inf.nom2.size()>0)
					f<<"	AudioParameterFloat* P_"<<inf.nom_class<<"_"<<inf.nom2<<";\n";
				if(inf.nom3.size()>0)
					f<<"	AudioParameterFloat* P_"<<inf.nom_class<<"_"<<inf.nom3<<";\n";
			}
		}
		else if(inf.widget == "C")
		{
			f<<"	AudioParameterBool* P_"<<inf.nom_obj<<";\n";
		}
		else if(inf.widget == "Color")
		{
			f<<"	AudioParameterInt* P1_"<<inf.nom_obj<<";\n";
			f<<"	AudioParameterInt* P2_"<<inf.nom_obj<<";\n";
		}
		
	}// for inf

	
	f<<"\n";

	f<<"	void Save_parameters(Processor * processor, MemoryBlock& destData);\n";
	f<<"	void Load_parameters(Processor * processor, const void* data, int sizeInBytes);\n";
	f<<"\n";
	f<<"	void Add_Automation_Parameters(Processor * processor);\n";
	f<<"	void Transmit_Automation_Parameters(Processor * processor, int parameterIndex);\n";


	
	//.. midicontrols............
	if(L_midicontrol_name.size()>0)
	{
		f<<"    //.......................\n";
		f<<"    // for midicontrols\n";
		f<<"    int Scan_Midi_Control_Process(MidiMessage & message);\n";
		f<<"    void Scan_Midi_Control_GUI();\n";

		for(auto inf : L_infos) // boucle sur les objets
		{
			if(inf.midicontrol.size()>0) // if there is midicontrol
			{
				f<<"\n";;
				f<<"     //-------------------\n";
				f<<"     // from line:"<<inf.ligne<<endl;


				
				f<<"     atomic<bool> A_"<<inf.nom_class<<"_"<<inf.nom<<"_asked = 0;\n";
				if(inf.type == "int")
					f<<"     atomic<int>  A_"<<inf.nom_class<<"_"<<inf.nom<<"  = "<<inf.val<<";\n";
				else if(inf.type == "double")
					f<<"     atomic<double>  A_"<<inf.nom_class<<"_"<<inf.nom<<"  = "<<inf.val<<";\n";
					
		
			} // if
		} // for inf
		

	}// if midicontrols

	
	f<<"//----To detect leak memory---------------\n";
	f<<"JUCE_LEAK_DETECTOR (Parameters)\n";
	f<<"\n";

	f<<"};\n";

//---------------------------------
	f.close(); // ferme le fichier com.h


//=========  write file com.cc for JUCE ========================================
//---fichier com.cc ---------------------------------
nom_com = rep_src2 + "/com.cc";
if(verbose>=1)
	cout<<"Ecriture du fichier :"<<nom_com<<endl;
	
	f.open(nom_com);
	
	f<<"//This code  C++ com.cc is written automatically by: makef.cc, so do write in it. It concerns a Plugin in JUCE. "<<endl;

	f<<"//========================================================================================="<<endl;

	//---- ecriture des entetes
	f<<"\n";

	f<<"#include \"Source/JuceHeader.h\"\n";
	f<<"using namespace juce;"<<endl;

	f<<"#include \"Source/processor/PluginProcessor.h\"\n";

	f<<"#include \"Source/editor/PluginEditor.h\"\n";
	f<<"#include \"Source/com.h\"\n\n";

	for(auto nf : L_noms_fichiers) 
		f<<"#include \""<<nf<<"\"\n";		

	
	f<<"\n";
	f<<"//-- Below is the list of "<< L_sous_tabs.size() + 1<< " windows for each tab window + ZC, named: Page_ZT_j, with j=0->"<<(int) L_sous_tabs.size()-1<<"\n";
	f<<"\n";
	

//---- loop over the tab windows
for(int j= 0; j< (int) L_sous_tabs.size(); j++) // loop over the tab.
	{
		ostringstream s, s2; // code of the new Tab
		s<<"Page_ZT_"<<j;
		s2<<"ZT_"<<j;
		
		
		f<<"\n";
		f<<"//====Constructor =========================================\n";
		f<<s.str()<<"::"<<s.str()<<"(Com *p_i)\n";
		f<<"{\n";
		
		
		f<<"   p_com = p_i;\n";
		//	f<<"   p_com->p_"<<s2.str()<<" = this;\n";

		string name;
		for(int k=0; k< L_sous_tabs[j].size(); k++)
			name += L_sous_tabs[j][k]; // concatene
		ReplaceStringInPlace(name, " ","_");
		ReplaceStringInPlace(name, "/","_");
		f<<"   p_com->p_Tab_"<<name<<" = this;\n";
		
		f<<"   if(p_com->verbose >= 1 )\n";
		f<<"     cout<<\""<<s.str()<<"()\"<<endl;\n";
		f<<"\n";

		//----  objects for this tab
		for(auto & inf : L_infos)
		{
			//--- Define selection of objects for this tab
			if (inf.Idj == j) 
			{

				f<<"\n";
				f<<"   //-- from the instruction of class: "<<inf.nom_class<<": "<<endl;
				f<<"   // "<<inf.ligne<<endl;

				//----------------------------
		    	if(inf.widget == "N" || inf.widget == "T")
				{
					//.... text avant
					f<<"\n";
//					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";

					
					//...... TextEditor ....
					f<<"\n";
					f<<"	p_com->" << inf.nom_obj << " = new juce::TextEditor(\"p_com->"<<inf.nom_obj<<"\");\n";
					if(inf.widget == "N")
						f<<"   p_com->"<<inf.nom_obj<<"->setText(\""<< inf.val <<"\");\n";
					else if(inf.widget == "T")
						f<<"   p_com->"<<inf.nom_obj<<"->setText("<< inf.val <<");\n";

					f<<"   p_com->"<<inf.nom_obj<<"->onTextChange = [this] { p_com->Process_message_"<<inf.nom_obj<<"(); }; // callback\n";
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";
					
					//.... texte apres
					f<<"\n";
//					f<<"   p_com->"<<inf.nom_obj<<"_texte = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte->setText(\""<< inf.texte <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_texte);\n";

				}

				//----------------------------
				else 	if(inf.widget == "B" || inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor")
				{

					//.... text avant
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";

					
					f<<"\n";

					if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor")
					{
						f<<"   p_com->" << inf.nom_obj << "_button = new juce::TextButton();\n";
						if(inf.widget != "Window2")
							f<<"   p_com->"<<inf.nom_obj<<"_button->setButtonText(\""<< "Show "+ inf.texte <<"\");\n";
						else
							f<<"   p_com->"<<inf.nom_obj<<"_button->setButtonText(\""<< "External "+ inf.texte <<"\");\n";
							
						f<<"   p_com->"<<inf.nom_obj<<"_button->onClick = [this] { p_com->Process_message_"<<inf.nom_obj<<"(); }; // callback\n";
						if(inf.help.size()>0)
							f<<"   p_com->"<<inf.nom_obj<<"_button->setTooltip(\""<<inf.help<< "\");\n";
						f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_button);\n";


						if(inf.widget == "Window2")
						{
							f<<"   p_com->"<<inf.nom_obj<<" = new TCanvas_"<<inf.nom_obj<<"(p_i, \""<< inf.texte <<"\", juce::Colour(), 7); // 7:all buttons\n";
							f<<"   p_com->"<<inf.nom_obj<<"->status = 0; //embeded\n";
							f<<"   addAndMakeVisible(p_com->"<<inf.nom_obj<<");\n";
							
						}
						

					}
					else if(inf.widget == "B" )
					{
						f<<"   p_com->" << inf.nom_obj << " = new juce::TextButton();\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setButtonText(\""<< inf.texte <<"\");\n";
						f<<"   p_com->"<<inf.nom_obj<<"->onClick = [this] { p_com->Process_message_"<<inf.nom_obj<<"(); }; // callback\n";
						if(inf.help.size()>0)
							f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";
						f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";

					}
					
					
					
				}
					//----------------------------
				else 	if(inf.widget == "HLINK")
				{
					f<<"\n";
					f<<"   p_com->" << inf.nom_obj << " = new juce::HyperlinkButton();\n";
					f<<"   p_com->"<<inf.nom_obj<<"->setButtonText(\""<< inf.texte <<"\");\n";
					f<<"   p_com->"<<inf.nom_obj<<"->setURL(URL(\""<< inf.URL <<"\"));\n";
					
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";
					
					
				}
					//----------------------------
				else 	if(inf.widget=="File" || inf.widget=="Dir")
				{

					//.... text avant
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";

						
					//...... TextEditor ....
					f<<"\n";
					f<<"	p_com->" << inf.nom_obj << "_ed = new juce::TextEditor(\""<<inf.nom_obj<<"\");\n";
					if(inf.widget == "N")
						f<<"   p_com->"<<inf.nom_obj<<"_ed->setText(\""<< inf.val <<"\");\n";
					else if(inf.widget == "T")
						f<<"   p_com->"<<inf.nom_obj<<"_ed->setText("<< inf.val <<");\n";

					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"_ed->setTooltip(\""<<inf.help<< "\");\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_ed);\n";
					
					//...... TextButton ....

					if(inf.widget=="File")
						inf.texte = "Select file";
					else if(inf.widget=="Dir")
						inf.texte = "Select dir.";
			


					
					f<<"\n";
					f<<"   p_com->" << inf.nom_obj << " = new juce::TextButton();\n";
					f<<"   p_com->"<<inf.nom_obj<<"->setButtonText(\""<< inf.texte <<"\");\n";
					

					f<<"   p_com->"<<inf.nom_obj<<"->onClick = [this] { p_com->Process_message_"<<inf.nom_obj<<"(); }; // callback\n";
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";
					
					
				}
							//----------------------------
				else 	if(inf.widget == "HS" || inf.widget == "INC")
				{
				

					//.... text avant
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";

					
					//... slider	

					if(inf.nom2.size()==0) // one variable
					{
						f<<"   p_com->"<<inf.nom_obj<<" = new juce::Slider(juce::Slider::LinearHorizontal,  Slider::TextBoxRight);\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setValue("<<inf.val<< ");\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setTextBoxStyle(Slider::TextBoxRight, true, 50, 20); // false: no editable\n";
					}
					else if(inf.nom3.size()==0) // two variable
					{
						f<<"   p_com->"<<inf.nom_obj<<" = new juce::Slider(juce::Slider::TwoValueHorizontal,  Slider::TextBoxRight);\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setMinValue("<<inf.val<< ");\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setMaxValue("<<inf.val2<< ");\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setTextBoxStyle(Slider::TextBoxRight, true, 50, 20); // false: no editable\n";	
					}
					else// three variable
					{
						f<<"   p_com->"<<inf.nom_obj<<" = new juce::Slider(juce::Slider::ThreeValueHorizontal,  Slider::TextBoxRight);\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setMinValue("<<inf.val<< ");\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setValue("<<inf.val2<< ");\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setMaxValue("<<inf.val3<< ");\n";
						f<<"   p_com->"<<inf.nom_obj<<"->setTextBoxStyle(Slider::TextBoxRight, true, 50, 20); // false: no editable\n";	
					}
					
				
					if( inf.widget == "INC")
						f<<"   p_com->"<<inf.nom_obj<<"->setSliderStyle(Slider::IncDecButtons);\n";

					f<<"   p_com->"<<inf.nom_obj<<"->setRange ("<<inf.xmin<<", "<<inf.xmax<<", "<<inf.step<<");\n";
				


					f<<"   p_com->"<<inf.nom_obj<<"->onValueChange = [this] { p_com->Process_message_"<<inf.nom_obj<<"(); }; // callback\n";
						
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";


					
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";

					//.... texte apres
					f<<"   p_com->"<<inf.nom_obj<<"_texte = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte->setText(\""<< inf.texte <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_texte);\n";

				}


				
				//----------------------------
				else 	if(inf.widget == "PB")
				{
					//.... text avant
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";
				
					//... PB
					double x = 0; //in [0,1]
					if(stof(inf.xmax)> stof(inf.xmin))
						x = stof(inf.val) / (stof(inf.xmax) - stof(inf.xmin));
					if(x>1)
						x=1;
					if(x<0)
						x=0;
					
					f<<"   p_com->"<<inf.nom_obj<<"_x = "<<x<< ";\n";

					f<<"   p_com->"<<inf.nom_obj<<" = new juce::ProgressBar(p_com->"<<inf.nom_obj<<"_x);\n";
				

					
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";

					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";

					//.... texte apres
					f<<"   p_com->"<<inf.nom_obj<<"_texte = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte->setText(\""<< inf.texte <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_texte);\n";


					/*

					//..........
	
					f<<"	p_com->" << inf.nom_obj << " = new TGHProgressBar("<<var_tab<<", TGProgressBar::kFancy, 200);"<<endl;
					f<<"    p_com->"<<inf.nom_obj<<"->ShowPosition(kTRUE,kFALSE,\"p_com->"<<inf.nom_obj<<": %.0f\");"<<endl;
					f<<"    p_com->"<<inf.nom_obj<<"->SetBarColor(\"green\");"<<endl;
					f<<"    p_com->"<<inf.nom_obj<<"->SetRange("<<inf.xmin<<", "<<inf.xmax<<");"<<endl;
					f<<"    p_com->"<<inf.nom_obj<<"->SetPosition(p_com->p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
					//		f<<"    p_com->"<<inf.nom_obj<<"->Associate(this);"<<endl;
					f<<"    "<<var_tab<<"->AddFrame(p_com->"<<inf.nom_obj<<");"<<endl;
					f<<endl;
					*/
				}
		
				//----------------------------
				else 	if(inf.widget == "C")
				{
				
					//.... text avant
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";

					
					//...... ....
					f<<"\n";
					f<<"	p_com->" << inf.nom_obj << " = new juce::ToggleButton();\n";

					f<<"   p_com->"<<inf.nom_obj<<"->onClick = [this] { p_com->Process_message_"<<inf.nom_obj<<"(); }; // callback\n";
					if(inf.val == "0")
						f<<"   p_com->"<<inf.nom_obj<<"->setToggleState(false, juce::dontSendNotification);\n";
					else
						f<<"   p_com->"<<inf.nom_obj<<"->setToggleState(true, juce::dontSendNotification);\n";
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";
					
					//.... texte apres
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte->setText(\""<< inf.texte <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_texte);\n";
				}
				//----------------------------
				else 	if(inf.widget == "Color")
				{
					//.... text avant
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";

				
					//...... ....
					f<<"\n";
					f<<"	p_com->" << inf.nom_obj << " = new ColourChangeButton(p_com);\n";
					f<<"    p_com->"<<  inf.nom_obj<<"->setColour(TextButton::buttonColourId, juce::Colour((uint32) p_com->p_"<< inf.nom_class <<"->"<< inf.nom <<"));\n";
					f<<"    p_com->"<<  inf.nom_obj<<"->setButtonText(\" \");\n";

					
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";
					
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";


					f<<"   p_com->"<<inf.nom_obj<<"->f =  &Com::Process_message_"<<inf.nom_obj<<"; // assign function \n";
					
					//.... texte apres
/*
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_texte);\n";
*/
				}			
				//----------------------------
				else 	if(inf.widget == "L" || inf.widget == "LB")
				{
				
					//.... text avant
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_text->setText(\""<< inf.text <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_text);\n";

					
					//...... ....
					f<<"\n";
					f<<"	p_com->" << inf.nom_obj << " = new juce::ComboBox();\n";

					f<<"   p_com->"<<inf.nom_obj<<"->onChange = [this] { p_com->Process_message_"<<inf.nom_obj<<"(); }; // callback\n";
					for(int j=0; j<inf.L_l.size(); j++)
					{
						f<<"    p_com->"<<inf.nom_obj<<"->addItem(\""<<inf.L_l[j]<<"\","<<j+1<<");"<<endl;

					}

					f<<"    p_com->"<<inf.nom_obj<<"->setSelectedId( p_com->p_"<<inf.nom_class<<"->"<<inf.nom<<"+1);"<<endl;
					
					if(inf.help.size()>0)
						f<<"   p_com->"<<inf.nom_obj<<"->setTooltip(\""<<inf.help<< "\");\n";
					
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<");\n";
					
					//.... texte apres
					f<<"\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte = new juce::Label();\n";
					f<<"   p_com->"<<inf.nom_obj<<"_texte->setText(\""<< inf.texte <<"\", juce::dontSendNotification);\n";
					f<<"   addAndMakeVisible (p_com->"<<inf.nom_obj<<"_texte);\n";
				}

				
			} // if L_nom_tabs

			
		} // for inf: objects


		//--- subtabs
		if(L_sous_tabs_index[j].size()>=1)
		{
			f<<"\n";	
			f<<"   tab = 	new juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop);\n";
			//	f<<"   tab->setTabBarDepth(20);\n";

			f<<"   auto colour = findColour (ResizableWindow::backgroundColourId);\n";
			for(int k=0; k< L_sous_tabs_index[j].size(); k++)
			{
				int j2 = L_sous_tabs_index[j][k];
				f<<"   tab->addTab(\""<< L_sous_tabs[j2][L_sous_tabs[j2].size()-1] <<"\", colour, new Page_ZT_"<<j2<<"(p_com), true);\n";
			}
//			f<<"   tab->setColour(TabbedButtonBar::tabOutlineColourId, Colours::green);\n";
			f<<"   tab->setLookAndFeel(&customLookAndFeel);\n";
			
			f<<"   addAndMakeVisible (tab);\n";


			f<<"\n";
		}




		//---- menu
		int ID = 1; 
		if(j ==0 && L_noms_menus.size() > 0)
		{
			
			
			f<<"	   b_menu = new juce::TextButton();\n";
			f<<"       b_menu->setButtonText(\"Menu\");\n";
			f<<"	   b_menu->onClick = [this]\n";
			f<<"	     {\n";
			f<<"		  PopupMenu menu;\n";

			for(int i=0; i<L_noms_menus.size(); i++)
			{
				f<<"          {\n";
				f<<"		   PopupMenu subMenu;\n";

				for(auto & inf : L_infos) 
					if ((inf.widget == "M" || inf.widget == "MS" ) && inf.nom_tab == L_noms_menus[i] )
					{
						f<<"		   subMenu.addItem ( "<<ID<<", \""<<  inf.texte  <<"\", true);\n";
						inf.ID = ID; // memorize
						ID++;
					}

				f<<"		   menu.addSubMenu (\""<< L_noms_menus[i] <<"\", subMenu, true);\n";
				f<<"          }//submenu\n";
			}// for i
		   
			f<<"		 menu.showMenuAsync(PopupMenu::Options{}.withTargetComponent (b_menu)  , [](int ID)\n";
			f<<"		   {\n";
			f<<"						   //-- this inline function is called from the main Thread, when the user has selectedan item in the menu\n";

			for(auto & inf : L_infos)
				if (inf.widget == "M" || inf.widget == "MS" )
				{
					f<<"	      if(ID == "<< inf.ID  <<")\n";
					f<<"             {\n";
					f<<"               //cout<<ID<<endl;\n";
					if (inf.widget == "M")
						f<<"               p_com->p_"<<inf.nom_class<<"->"<<inf.nom<<"(); \n";
					f<<"			 }\n";
				}
			f<<"		   }\n";
	
			f<<"	     ); // showMenu: show the menu near the button\n";
			f<<"	   }; // onClick: callback of menu button\n";
			f<<"	   b_menu->setTooltip(\"In this menu you can select some actions\");\n";
			f<<"	   addAndMakeVisible (b_menu);\n";
		} // if menu

		f<<"   if(p_com->verbose >= 1 )\n";
		f<<"     cout<<\"end of "<<s.str()<<"()\"<<endl;\n";
		f<<"\n";


//----------------------
f<<"}\n"; // end of constructor 


				
		f<<"\n";
		f<<"//====  Destructor =========================================\n";
		f<<s.str()<<"::~"<<s.str()<<"()\n";
		f<<"{\n";


		//----  objects for this tab
		f<<"\n";
		for(auto inf : L_infos)
		{
			//--- Define selection of objects for this tab
			if(inf.Idj == j)
			{


				if(inf.widget == "N" || inf.widget == "T" || inf.widget == "HS" || inf.widget == "C" || inf.widget == "L" || inf.widget == "LB" || inf.widget == "PB" || inf.widget == "INC")
				{
					f<<"   delete p_com->"<<inf.nom_obj<<"_text;\n";
					f<<"   delete p_com->"<<inf.nom_obj<<";\n";
					f<<"   delete p_com->"<<inf.nom_obj<<"_texte;\n";
				}
			
			
			
				else if(inf.widget == "Color") // select color
				{
					f<<"   delete p_com->"<<inf.nom_obj<<"_text;\n";
					f<<"   delete p_com->"<<inf.nom_obj<<";\n";
//					f<<"   delete p_com->"<<inf.nom_obj<<"_texte;\n";
				}
			
				else if(inf.widget == "B") // Text Button
				{
					f<<"   delete p_com->"<<inf.nom_obj<<"_text;\n";
					f<<"   delete p_com->"<<inf.nom_obj<<";\n";
				}
				else if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor") 
				{
					f<<"   delete p_com->"<<inf.nom_obj<<"_text;\n";
					f<<"   delete p_com->"<<inf.nom_obj<<"_button;\n";
					if( inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor")
					{
						f<<"   if(p_com->"<<inf.nom_obj<<" != nullptr)\n";
						f<<"     delete p_com->"<<inf.nom_obj<<";\n";
					}
				}
				else if(inf.widget == "HLINK")
				{
					f<<"   delete p_com->"<<inf.nom_obj<<";\n";
				}
				else if( inf.widget=="File" || inf.widget=="Dir")
				{
					f<<"   delete p_com->"<<inf.nom_obj<<"_text;\n";
					f<<"   delete p_com->"<<inf.nom_obj<<"_ed;\n";
					f<<"   delete p_com->"<<inf.nom_obj<<";\n";
				}


			} // if

			
		} // for inf: objects

		//--- subtabs
		if(L_sous_tabs_index[j].size()>=1)
		{
			f<<"\n";	
			f<<"   delete tab;\n";
			f<<"\n";
		}
		
		//---- menu
		if(j ==0 && L_noms_menus.size() > 0)
		{
			f<<"\n";	
			f<<"   delete b_menu;\n";
			f<<"\n";
		}


		
		f<<"}\n"; // end of destructor 


		f<<"\n";
		f<<"//=============================================\n";
		f<<"// resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled). This is a good place to set the size and position of widgets so they can be positioned relative to the window bounds.\n";

		f<<"void "<<s.str()<<"::resized()\n";
		f<<"{\n";


		
		//---- menu
		if(j ==0 && L_noms_menus.size() > 0)
			f<<"   b_menu->setBounds(10, 10, 80, 20 ); //   (x, y, width, height)\n";


		//----  objects for this tab



		
		for(auto inf : L_infos)
		{
			//--- Define selection of objects for this tab
			if (inf.Idj == j)
			{

				f<<"\n";
				if(inf.widget == "N" || inf.widget == "T" ||  inf.widget == "HS" ||  inf.widget == "C" ||  inf.widget == "L" ||  inf.widget == "LB" || inf.widget == "Color" || inf.widget == "PB" || inf.widget == "INC")
				{
					int x = inf.x;
					int w =  inf.text.size()*size_c ; 
					f<<"   p_com->"<<inf.nom_obj<<"_text->setBounds("<<x<<", "<<inf.y<<", "<< w <<", "<<inf.h<<" ); //  (x, y, width, height)\n"; // text
					x += w;
					if(inf.widget == "N")
					   w =  size_N;
					else if(inf.widget == "T")
						w =  size_T;
					else if(inf.widget == "HS" || inf.widget == "INC")
						w =  size_HS;
					else if(inf.widget == "C")
							w =  size_C;
					else if(inf.widget == "L")
						w =  size_L;
					else if(inf.widget == "Color")
						w =  size_Color;
					else if(inf.widget == "PB")
						w =  size_HS;
					f<<"   p_com->"<<inf.nom_obj<<"->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<<inf.h<<" ); //  (x, y, width, height)\n"; 
					x += w;

					 if(inf.widget != "Color")
					 {
						 w =  inf.texte.size()*size_c + xD;
						 f<<"   p_com->"<<inf.nom_obj<<"_texte->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<<inf.h<<" ); //  (x, y, width, height)\n"; // texte
					 }
					
				}
				
			
				else if(inf.widget == "B") // Text Button
				{
					int x = inf.x;
					int w =  inf.text.size()*size_c ; 
					f<<"   p_com->"<<inf.nom_obj<<"_text->setBounds("<<x<<", "<<inf.y<<", "<< w <<", "<<inf.h<<" ); //  (x, y, width, height)\n"; // text
					x += w;
				
					
					w =  size_B + inf.texte.size()*size_c + xD;
					f<<"   p_com->"<<inf.nom_obj<<"->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<<inf.h<<" ); //  (x, y, width, height)\n"; 
				
				}
				else if(inf.widget == "Window"  || inf.widget == "Editor") 
				{
					int x = inf.x;
					int w =  inf.text.size()*size_c ; 
					f<<"   p_com->"<<inf.nom_obj<<"_text->setBounds("<<x<<", "<<inf.y<<", "<< w <<", "<<inf.h<<" ); //  (x, y, width, height)\n"; // text
					x += w;
				
					
					w =  size_B + inf.texte.size()*size_c + xD;
					f<<"   p_com->"<<inf.nom_obj<<"_button->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<<inf.h<<" ); //  (x, y, width, height)\n";
				
				}
				else if(inf.widget == "Window2") 
				{
					int x = inf.x;
					int w =  inf.text.size()*size_c ; 
					f<<"   p_com->"<<inf.nom_obj<<"_text->setBounds("<<x<<", "<<inf.y<<", "<< w <<", "<< size_B  <<" ); //  (x, y, width, height)\n"; // text
					x += w;
				
					
					w =  size_B + inf.texte.size()*size_c + xD;
					f<<"   p_com->"<<inf.nom_obj<<"_button->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<< size_B <<" ); //  (x, y, width, height)\n";
					f<<"   p_com->"<<inf.nom_obj<<"->setBounds("<< x<<", "<<inf.y +  size_B <<", "<< inf.W <<", "<< inf.H <<" ); //  (x, y, width, height)\n";
				
				}
				else if(inf.widget == "HLINK")
				{
					int x = inf.x;
					
					int w =  size_B + inf.texte.size()*size_c + xD;
					f<<"   p_com->"<<inf.nom_obj<<"->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<<inf.h<<" ); //  (x, y, width, height)\n"; 
				
				}
				else if( inf.widget=="File" || inf.widget=="Dir") // Text Button
				{
					int x = inf.x;
					int w =  inf.text.size()*size_c + 10; 
					f<<"   p_com->"<<inf.nom_obj<<"_text->setBounds("<<x<<", "<<inf.y<<", "<< w <<", "<<inf.h<<" ); //  (x, y, width, height)\n"; // text
					x += w;
					w =  size_File;
					f<<"   p_com->"<<inf.nom_obj<<"_ed->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<<inf.h<<" ); //  (x, y, width, height)\n";
					x += w;
					
					w =   inf.texte.size()*size_c + xD;
					f<<"   p_com->"<<inf.nom_obj<<"->setBounds("<< x<<", "<<inf.y<<", "<<w<<", "<<inf.h<<" ); //  (x, y, width, height)\n"; 
				
				}


			} // if

			
		} // for inf: objects

		//--- subtabs
		if(L_sous_tabs_index[j].size()>=1)
		{
			f<<"\n";

			 // w: width, h1 :height 1 (above subtabs) , h2 : heigth 2 (below subtabs)

			int h1T = L_sous_tabs_h1T[j];

			
			f<<"   tab->setBounds(0, "<<h1T <<", "<< w_tot <<", "<< h_tot-h1T<<");// x,y,w,h\n";
			f<<"\n";
		}
		

		
		f<<"}\n"; // end of resized()


		


		f<<"\n";
		f<<"//=============================================\n";
		f<<"// paint() function is where all custom shapes and GUI elements are drawn to the window.\n";

		f<<"void "<<s.str()<<"::paint(juce::Graphics& g)\n";
		f<<"{\n";


		f<<"}\n"; // end of paint()


		
		//----- functions callback() for each object. So Event on widget, variable of widget  -> variable of the class.
		

		

		
	} // for j: tab window


//--- main class Com()



	f<<"//======================\n";	
	f<<"Com::Com(Editor *p_i, ";
	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<")"<<flush;
	}

		
	if(test_File >= 1)
		f<<" : chooser(\"Select a file or directory\", File::getCurrentWorkingDirectory(), \"*\")\n"; //name of dialog window
	else
		f<<"\n";
		
	f<<"{\n";

	f<<"   //cout<<\"Com::Com()\"<<endl;\n"; 

	f<<"\n";
	for(auto nc : L_noms_classes)
	{
		f<<"   p_"<<nc<<" = p"<<nc<<";\n";
		f<<"   p_"<<nc<<"->p_com = this;\n\n";
	}
	f<<"\n";
	
	
	f<<"   p_e = p_i;\n";
	if(Titre.size()<0)
		f<<"   p_e->setTitle("<<Titre<<");\n";
	f<<"   p_Tab_ZC = new Page_ZT_0(this);//main page\n";
	f<<"   p_e->addAndMakeVisible(p_Tab_ZC);\n\n";



	if(test_TT >=  1) // Timers
	{
		f<<"// ---- periodic call of function	Com::timerCallback(int ID) below\n";
		for(auto inf : L_infos) // boucle sur les objets
			if(inf.widget == "TT")
				f<<"   startTimer("<<inf.ID<<", "<< inf.val<<"); // ID, period in ms\n";
	}


	f<<"   //.....  c++ variables -> widget\n";
	for(auto inf : L_infos)
		if(inf.nom != "" && inf.widget != "TT")
			f<<"   Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"();\n";


	
	f<<"}\n";

	
	f<<"//===========\n";
	f<<"Com::~Com()\n";
	f<<"{\n";

	for(auto nc : L_noms_classes)
	{
		f<<"   p_"<<nc<<"->p_com = nullptr;\n";
	}
	
	f<<"   delete p_Tab_ZC;\n";

	f<<"}\n";

	
	f<<"//=============\n";
	f<<"void Com::resized()\n";
	f<<"{\n";
	f<<"   p_Tab_ZC->setBounds(0, 0, p_e->getWidth(), p_e->getHeight());\n";

	
	f<<"   p_e->setSize ("<<w_tot<<", "<<h_tot<<"); // resize the main window\n";
	
	f<<"}\n";


	//----- function timerCallback() if needed
	if(test_TT >=  1) // Timers
	{
	f<<"//=============\n";
	f<<"void Com::timerCallback(int ID)\n";
	f<<"{\n";
		
	for(auto inf : L_infos) // boucle sur les objets
		if(inf.widget == "TT")
		{
			f<<"   if(ID == "<<inf.ID<<")\n";
			f<<"        p_"<<inf.nom_class<<"->"<<inf.nom<<"(); // call the function"<<endl;
		}
	f<<"}\n";
			
	}

	
	//------ loop on objects: add a function Met_a_jour(), so variable c++ ->  variable of the widget

	
	for(auto inf : L_infos)
	{
		if(inf.nom.size() == 0 || inf.widget == "TT")
			continue;

		f<<"//===================\n";
		f<<"// function to transfert c++ variable -> widget variable\n";
		f<<"// will call Process_"<<inf.nom_obj<<"()\n";
		f<<"void Com::Met_a_jour_"<<inf.nom_obj<<"()\n";
		f<<"{\n";


		f <<"	if( "<<inf.nom_obj<<" == nullptr)\n";
		f <<"		return;\n";
			
		if(inf.widget == "N")
			f <<"	"<<inf.nom_obj<<"->setText(to_string(p_"<<inf.nom_class<<"->"<<inf.nom<<"));"<<endl;
		else if(inf.widget == "T")
			f <<"	"<<inf.nom_obj<<"->setText(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;

		else if(inf.widget=="File" || inf.widget=="Dir")
			f <<"	"<<inf.nom_obj<<"_ed->setText(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;

		else if(inf.widget == "HS" || inf.widget == "INC")
		{
			if(inf.nom2.size()==0) // one variable
			{
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 	"<<inf.nom_obj<<"->getValue())"<<endl;
				f<<"	    "<<inf.nom_obj<<"->setValue(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
			}
			else if(inf.nom3.size()==0) // two variable
			{
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 	"<<inf.nom_obj<<"->getMinValue())"<<endl;
				f<<"	    "<<inf.nom_obj<<"->setMinValue(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom2<<" != 	"<<inf.nom_obj<<"->getMaxValue())"<<endl;
				f<<"	    "<<inf.nom_obj<<"->setMaxValue(p_"<<inf.nom_class<<"->"<<inf.nom2<<");"<<endl;
			}
			else// three variable
			{
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 	"<<inf.nom_obj<<"->getMinValue())"<<endl;
				f<<"	    "<<inf.nom_obj<<"->setMinValue(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom2<<" != 	"<<inf.nom_obj<<"->getValue())"<<endl;
				f<<"	    "<<inf.nom_obj<<"->setValue(p_"<<inf.nom_class<<"->"<<inf.nom2<<");"<<endl;
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom3<<" != 	"<<inf.nom_obj<<"->getMaxValue())"<<endl;
				f<<"	    "<<inf.nom_obj<<"->setMaxValue(p_"<<inf.nom_class<<"->"<<inf.nom3<<");"<<endl;
			}
		}
		
		else if(inf.widget == "PB")
		{
			f<<"	double x = 0; //in [0,1];\n";
			if(stof(inf.xmax) > stof(inf.xmin))
				f<<"	x = (p_"<<inf.nom_class<<"->"<<inf.nom<<" - "<< stof(inf.xmin)<<") / double("<< stof(inf.xmax) - stof(inf.xmin)<<");\n";
			f<<"	if(x>1)\n";
			f<<"	   x=1;\n";
			f<<"	if(x<0)\n";
			f<<"	   x=0;\n";
			f <<"	"<<inf.nom_obj<<"_x = x;"<<endl;
		}
		else if(inf.widget == "C")
		{
			
			f <<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<")"<<endl;
			f <<"       	"<<inf.nom_obj<<"->setToggleState(true, juce::dontSendNotification);"<<endl;
			f <<"    else"<<endl;
			f <<"       	"<<inf.nom_obj<<"->setToggleState(false, juce::dontSendNotification);"<<endl;
			
			
		}
		else if(inf.widget == "Color")
		{
			f << "    	// We transform the int c++ variable to RGB and assign to the Button"<<endl;
			f << "    		Colour col = juce::Colour((uint32) p_"<< inf.nom_class <<"->"<< inf.nom <<"); // in ARBG on first 4*8=32 bits\n;";
			f << "      "<<inf.nom_obj<<"->setColour (TextButton::buttonColourId, col);\n";

		}
		else if(inf.widget == "L" || inf.widget == "LB")
		{
			
			if(inf.object !="") // si il y a une liste explicite
			{
				f <<"    "<<inf.nom_obj<<"->clear();"<<endl;

				f <<"     int len = 0; //  compute max length of words"<<endl;
				f <<"     for(int i=0; i < p_"<<inf.nom_class<<"->"<<inf.object<<".size(); i++)"<<endl;
				f <<"     {"<<endl;
				f <<"       "<<inf.nom_obj<<"->addItem( p_"<<inf.nom_class<<"->"<<inf.object<<"[i].c_str(), i+1);"<<endl;
				f <<"        if(p_"<<inf.nom_class<<"->"<<inf.object<<"[i].size() > len)"<<endl;
				f <<"             len = p_"<<inf.nom_class<<"->"<<inf.object<<"[i].size();"<<endl;
				f <<"     }"<<endl;
				f <<"     len = 6*len + 40; // scaling"<<endl;
				f <<"     if(len < 12)"<<endl;
				f <<"       len = 12;"<<endl;
				f <<"     else if(len > 500)"<<endl;
				f <<"       len = 500;"<<endl;
				f <<"      //"<<inf.nom_obj<<"->resize(len, 20);  // ajuste longueur du ComboBox. Not yet written"<<endl;

								
			}
			
			
			//.....
			f <<"    "<<inf.nom_obj<<"->setSelectedId( p_"<<inf.nom_class<<"->"<<inf.nom<<"+1);"<<endl;
		}
		else if(inf.widget == "Editor")
		{
			f<<"     "<<inf.nom_obj<<"_code.replaceAllContent(p_"<<inf.nom_class<<"->"<<inf.nom<<");\n"; 
		}
		
		
		f<<"}\n";
	} // for inf
 	


	
	//------ loop on objects: add a function Process_message_object(), to transfert widget variable -> c++ variable

	
	for(auto inf : L_infos)
	{
		
		if(inf.nom.size() == 0 || inf.widget == "TT")
			continue;
		
		f<<"//===================\n";
		f<<"// function to transfert widget variable -> c++ variable -> parameter\n";
		f<<"void Com::Process_message_"<<inf.nom_obj<<"()\n";
		f<<"{\n";


		if(inf.widget == "N")
		{
			if(inf.type == "int")
				f<<"    p_"<<inf.nom_class<<"->"<<inf.nom<<" = 	"<<inf.nom_obj<<"->getText().getIntValue();"<<endl;
			else if(inf.type == "double")
				f<<"    p_"<<inf.nom_class<<"->"<<inf.nom<<" = 	"<<inf.nom_obj<<"->getText().getDoubleValue();"<<endl;
			if(inf.attach_function.size()>0)  // si il faut appeler fonction
				f<<"   p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
		}
		else if(inf.widget == "T")
		{
				f<<"    p_"<<inf.nom_class<<"->"<<inf.nom<<" = 	(string) "<<inf.nom_obj<<"->getText().toStdString();"<<endl;
			if(inf.attach_function.size()>0)  // si il faut appeler fonction
				f<<"   p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";

		}
			
		else if(inf.widget=="File" || inf.widget=="Dir")
		{
			
			if(inf.attach_function.size()>0)  // si il faut appeler fonction
				f<<"   p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
			if(inf.widget=="File")
			{
				// Afficher la fenêtre de selection de fichier
				f<<"     chooser.launchAsync(FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles, [this](const FileChooser& chooser)\n";
				f<<"      { // this function is called from the  main thread, when user has selected a file or closed the file window\n";
				f<<"        File selectedFile = chooser.getResult(); // get selected file\n";
				f<<"        if (selectedFile.existsAsFile()) // check if the file exists\n";
				f<<"         {\n";
				f<<"          cout << \"selected File : \" << selectedFile.getFullPathName() << std::endl; // show full path\n";
				f<<"          if (selectedFile.hasReadAccess())\n";
				f<<"          	 cout << \"selected File is readable\" << endl;\n";
				f<<"          else\n";
				f<<"          	 cout << \"selected File is not readable\" << endl;\n";
				f<<"          if (selectedFile.hasWriteAccess())\n";
				f<<"          	 cout << \"selected File is writeable\" << endl;\n";
				f<<"          else\n";
				f<<"          	 cout << \"selected File is not writeable\" << endl;\n";


				f<<"          	 p_"<<inf.nom_class<<"->"<<inf.nom<<" = selectedFile.getFullPathName().toStdString();;\n";
				f<<"          	 cout<< p_"<<inf.nom_class<<"->"<<inf.nom<<"<<endl;\n";

				f <<"	"<<inf.nom_obj<<"_ed->setText(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
							
				f<<"          }\n";
				f<<"        else\n";
				f<<"         {\n";
				f<<"              cout << \"No File selected.\" << std::endl;\n";
				f<<"         }\n";
				f<<"       });\n";
			
			}
			else if(inf.widget=="Dir")
			{
				// Afficher la fenêtre de selection de fichier
	// Afficher la fenêtre de selection de fichier
				f<<"     chooser.launchAsync(FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories, [this](const FileChooser& chooser)\n";
				f<<"      { // this function is called from the  main thread, when user has selected a file or closed the file window\n";
				f<<"        File selectedFile = chooser.getResult(); // get selected file\n";
			
			
				f<<"          cout << \"selected File : \" << selectedFile.getFullPathName() << std::endl; // show full path\n";
			

				f<<"          	 p_"<<inf.nom_class<<"->"<<inf.nom<<" = selectedFile.getFullPathName().toStdString();;\n";
				f<<"          	 cout<< p_"<<inf.nom_class<<"->"<<inf.nom<<"<<endl;\n";

				f <<"	"<<inf.nom_obj<<"_ed->setText(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
							
			
				f<<"       });\n";


				/*
				f<<"     chooser = std::make_unique<FileChooser> (\"Please select a directory\", File::getSpecialLocation (File::userHomeDirectory), \"\");\n";
				f<<"      auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories;\n";

				f<<"       chooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)\n";
				f<<"       {\n";
				f<<"         File selectedFile (chooser.getResult());\n";

				f<<"          	 p_"<<inf.nom_class<<"->"<<inf.nom<<" = selectedFile.getFullPathName().toStdString();;\n";
				f<<"          	 cout<<\""<<inf.nom_class<<"->"<<inf.nom<<"\" p_"<<inf.nom_class<<"->"<<inf.nom<<"<<endl;\n";
				
				f <<"	         "<<inf.nom_obj<<"_ed->setText(p_"<<inf.nom_class<<"->"<<inf.nom<<");"<<endl;
							
				f<<"         }\n";

				f<<"       });\n";
				*/

			}
			
			/*
			
			f<<"//-- File:  File Name Selection "<<endl;
			f<<"    if(M==1 && S==3 && p1== "<<inf.Id<<" )"<<endl;
			f<<"        {"<<endl;

			f<<"\n\
             static TString dir(\".\"); \n\
			 TGFileInfo fi;"<<endl;
			if(inf.widget=="File")
			{
				if(inf.texte.size()==0) // alors format standard
					f<<"              const char *filetypes[] = {\"All files\", \"*\", 0, 0};"<<endl;
				else // inf.texte doit etre au format: \"texte\",\"*.txt\", etc par paires
				{
					ReplaceStringInPlace(inf.texte,"'","\"");  //--- on remplace les ' par des "
					f<<"\
             const char *filetypes[] = {"<<inf.texte<<", 0, 0};"<<endl;
				}
				f<<"\n\
             fi.fFileTypes = filetypes;"<<endl;
			}



			
			f<<"\n\
			 fi.fIniDir    = StrDup(dir); \n\
			 TGFileDialog *fFD = new TGFileDialog(fClient->GetRoot(), this, kFDOpen, &fi); \n\
			 //if(verbose) \n\
			 //	 printf(\"Open file: %s (dir: %s) \", fi.fFilename, fi.fIniDir); \n\
			 dir = fi.fIniDir; \n\
            "<<endl;


			if(inf.widget=="File")
			{
				f<<"\n\
            if(fi.fFilename != nullptr) // not empty file name\n\
		    {\n\
			 p_"<<inf.nom_class<<"->"<<inf.nom<<" = fi.fFilename; //file name\n\
			 Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"();\n\
  		    }\n\
"<<endl;
			}
			else 	if(inf.widget=="Dir")
			{
				f<<"\n\
               p_"<<inf.nom_class<<"->"<<inf.nom<<" = fi.fIniDir; // directory name\n\
			   Met_a_jour_"<<inf.nom_class<<"_"<<inf.nom<<"();\n\
"<<endl;		
			}

			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;

			f<<"        }";
			f<<endl;
	 */
		}
		else if(inf.widget == "B")
		{
			f<<"     p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
			if(inf.attach_function.size()>0)  // si il faut appeler fonction
				f<<"   p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
		}

		else if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor")
		{
			f<<"     Show_Hide_Window_"<<inf.nom_obj<<"();"<<endl;
		}

		
		else if(inf.widget == "M")
		{
			/*
			f<<"//-- M: Menu"<<endl;
			f<<"    if(M==1 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"    {"<<endl;
			f<<"         p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"         p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			f<<"        // Met_a_jour();"<<endl;
			f<<"    }"<<endl;
			f<<endl;
			 */
		}
		else if(inf.widget == "MS")
		{
			/*
			f<<"//-- MS: Menu System"<<endl;
			f<<"    if(M==1 && S==1 && p1== "<<inf.Id<<" )"<<endl;
			f<<"    {"<<endl;
					f<<"         int res = system(\""<<inf.attach_function<<"\");"<<endl;
			f<<"    }"<<endl;
			f<<endl;
			 */
		}

		else if(inf.widget == "HS" || inf.widget == "INC")
		{
			//......................................
			if(inf.nom2.size()==0) // one variable
			{
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 	"<<inf.nom_obj<<"->getValue())"<<endl;
				f<<"    {\n";
				
				f<<"       p_"<<inf.nom_class<<"->"<<inf.nom<<" = 	"<<inf.nom_obj<<"->getValue();"<<endl;
				if(inf.attach_function.size()>0)  // si il faut appeler fonction
					f<<"      p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
				f<<"    }\n";

				
				if(inf.opt_param == 1)
				{
					f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != *(p_e->processor.params->P_"<<inf.nom_obj<<"))\n";
					f<<"    {\n";
					f<<"      *(p_e->processor.params->P_"<<inf.nom_obj<<") = p_"<<inf.nom_class<<"->"<<inf.nom<<";  // transmit to Parameter\n";
					f<<"    }\n";
				}

			}

			
			//......................................
			else if(inf.nom3.size()==0) // two variable
			{
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 	"<<inf.nom_obj<<"->getMinValue())"<<endl;
				f<<"    {\n";
				
				f<<"       p_"<<inf.nom_class<<"->"<<inf.nom<<" = 	"<<inf.nom_obj<<"->getMinValue();"<<endl;
				if(inf.attach_function.size()>0)  // si il faut appeler fonction
					f<<"      p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
				f<<"    }\n";


				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom2<<" != 	"<<inf.nom_obj<<"->getMaxValue())"<<endl;
				f<<"    {\n";
				
				f<<"       p_"<<inf.nom_class<<"->"<<inf.nom2<<" = 	"<<inf.nom_obj<<"->getMaxValue();"<<endl;
				if(inf.attach_function.size()>0)  // si il faut appeler fonction
					f<<"      p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
				f<<"    }\n";

				

				f<<"       //.... refresh the Textbox with two values\n";
				f<<"       "<<inf.nom_obj<<"->textFromValueFunction = [&](double v) {return juce::String("<<inf.nom_obj<<"->getMinValue()) + \" | \" + juce::String("<<inf.nom_obj<<"->getMaxValue());};\n";
				f<<"       "<<inf.nom_obj<<"->updateText();\n";

				
				if(inf.opt_param == 1)
				{
					f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom<<"))\n";
					f<<"      *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom<<") = p_"<<inf.nom_class<<"->"<<inf.nom<<";  // transmit to Parameter\n";
					f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom2<<" != *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom2<<"))\n";
					f<<"      *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom2<<") = p_"<<inf.nom_class<<"->"<<inf.nom2<<";  // transmit to Parameter\n";

				}

			}

			//......................................
			else// three variable
			{
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 	"<<inf.nom_obj<<"->getMinValue())"<<endl;
				f<<"    {\n";
				
				f<<"       p_"<<inf.nom_class<<"->"<<inf.nom<<" = 	"<<inf.nom_obj<<"->getMinValue();"<<endl;
				if(inf.attach_function.size()>0)  // si il faut appeler fonction
					f<<"      p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
				f<<"    }\n";

				
				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom2<<" != 	"<<inf.nom_obj<<"->getValue())"<<endl;
				f<<"    {\n";
				
				f<<"       p_"<<inf.nom_class<<"->"<<inf.nom2<<" = 	"<<inf.nom_obj<<"->getValue();"<<endl;
				if(inf.attach_function.size()>0)  // si il faut appeler fonction
					f<<"      p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
				f<<"    }\n";


				f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom3<<" != 	"<<inf.nom_obj<<"->getMaxValue())"<<endl;
				f<<"    {\n";
				
				f<<"       p_"<<inf.nom_class<<"->"<<inf.nom3<<" = 	"<<inf.nom_obj<<"->getMaxValue();"<<endl;
				if(inf.attach_function.size()>0)  // si il faut appeler fonction
					f<<"      p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
				f<<"    }\n";

				f<<"       //.... refresh the Textbox with three values\n";
				f<<"       "<<inf.nom_obj<<"->textFromValueFunction = [&](double v) {return juce::String("<<inf.nom_obj<<"->getMinValue()) + \"|\" + juce::String("<<inf.nom_obj<<"->getValue() + \"|\" + juce::String("<<inf.nom_obj<<"->getMaxValue() );};\n";
				f<<"       "<<inf.nom_obj<<"->updateText();\n";				
				
				if(inf.opt_param == 1)
				{
					f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom<<"))\n";
					f<<"      *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom<<") = p_"<<inf.nom_class<<"->"<<inf.nom<<";  // transmit to Parameter\n";
					f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom2<<" != *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom2<<"))\n";
					f<<"      *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom2<<") = p_"<<inf.nom_class<<"->"<<inf.nom2<<";  // transmit to Parameter\n";
					f<<"    if(p_"<<inf.nom_class<<"->"<<inf.nom3<<" != *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom3<<"))\n";
					f<<"      *(p_e->processor.params->P_"<<inf.nom_class<<"_"<<inf.nom3<<") = p_"<<inf.nom_class<<"->"<<inf.nom3<<";  // transmit to Parameter\n";

				}

			}

		}

		else if(inf.widget == "PB")
		{

			f<<"	double x = 	"<<inf.nom_obj<<"_x; //in [0,1];\n";
			if(stof(inf.xmax) > stof(inf.xmin))
				f<<"	x = x* "<<stof(inf.xmax) - stof(inf.xmin) <<" + "<< stof(inf.xmin) <<";\n";
			f <<"	"<<inf.nom_obj<<"_x = x;\n\n";


			if(inf.attach_function.size()>0)  // si il faut appeler fonction
				f<<"   p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";
		
		}


		
		else if(inf.widget == "C")
		{
			f<<"         if("<<inf.nom_obj<<"->getToggleState())"<<endl;
			f<<"            	p_"<<inf.nom_class<<"->"<<inf.nom<<" = 1;"<<endl;
			f<<"         else"<<endl;
			f<<"            	p_"<<inf.nom_class<<"->"<<inf.nom<<" = 0;"<<endl;
			
		
			if(inf.attach_function.size()>0)  // si il faut appeler fonction
				f<<"   p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";

			if(inf.opt_param == 1)
			{
				f<<"   if(*(p_e->processor.params->P_"<<inf.nom_obj<<") != p_"<<inf.nom_class<<"->"<<inf.nom<<")  // transmit to Parameter\n";
				f<<"       *(p_e->processor.params->P_"<<inf.nom_obj<<") = p_"<<inf.nom_class<<"->"<<inf.nom<<";  // transmit to Parameter\n";
			}
		}


		else if(inf.widget == "Color")
		{
			f<<"       //-- we take the ARGB color of the Button and transfer to the c++ variable"<<endl;
			f << "      Colour col =  "<<inf.nom_obj<<"->findColour (TextButton::buttonColourId);\n";

			f<<"        p_"<< inf.nom_class <<"->"<<inf.nom<<" = col.getARGB();  // convert to int\n";
			
			if(inf.attach_function.size()>0)  // si il faut appeler fonction
				f<<"   p_"<< inf.nom_class <<"->"<< inf.attach_function <<"();\n";

						
			if(inf.opt_param == 1)
			{

				f<<"    uint32_t  P_value = *(p_e->processor.params->P1_"<<inf.nom_obj<<") * 0x10000 +  *(p_e->processor.params->P2_"<<inf.nom_obj<<");\n";

				f<<"    uint32_t cpp_value = p_"<<inf.nom_class<<"->"<<inf.nom<<";\n";
				
				f<<"    if(  P_value != cpp_value) // transmit to Parameter\n";
				f<<"    {\n";
				f<<"         *(p_e->processor.params->P1_"<<inf.nom_obj<<") =  cpp_value /  0x10000;\n";
				f<<"         *(p_e->processor.params->P2_"<<inf.nom_obj<<") =  cpp_value %  0x10000;\n";
				f<<"     //.. check \n";
				f<<"     //int  P_value = *(p_e->processor.params->P1_"<<inf.nom_obj<<") * 0x10000 +  *(p_e->processor.params->P2_"<<inf.nom_obj<<");\n";
				f<<"     //cout<<\"    P_value   = \"<< hex << P_value <<\"\\t\\t\"<<flush;\n";
				f<<"     //cout<<\"\\t cpp_value   = \"<< hex <<  cpp_value <<\"      \\r\"<<flush;	\n";
				f<<"    }\n";
			}
		}
		
		else if(inf.widget == "L" || inf.widget == "LB")
		{
			f<<"       	if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != ("<<inf.nom_obj<<"->getSelectedId()-1))\n"; 
			f<<"        {\n";
	    	f<<"           p_"<<inf.nom_class<<"->"<<inf.nom<<" = "<<inf.nom_obj<<"->getSelectedId()-1;"<<endl;
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"           p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();"<<endl;
			
			f<<"        }\n";
			
			if(inf.opt_param == 1)
			{
				f<<"      if( *(p_e->processor.params->P_"<<inf.nom_obj<<") != p_"<<inf.nom_class<<"->"<<inf.nom<<")\n";
				f<<"         *(p_e->processor.params->P_"<<inf.nom_obj<<") = p_"<<inf.nom_class<<"->"<<inf.nom<<";  // transmit to Parameter\n";
			}
		}
		
		f<<"}\n";

		

	} // for inf
 	

//----------------------------

  //---- show window
		


	//---------------------------------
	for(auto inf : L_infos)
		if(inf.widget=="Window" || inf.widget == "Editor")
		{
			f<<"//===================\n";
			f<<"// function to show/hide a window\n";
			f<<"void Com::Show_Hide_Window_"<<inf.nom_obj<<"()\n";
			f<<"{\n";
			f<<"	//---- open window \n";
			f<<"	if("<<inf.nom_obj<<" == nullptr)\n";
			f<<"	{\n";
			f<<"		"<<inf.nom_obj<<" =  new TCanvas_"<<inf.nom_obj<<"(this, \""<< inf.texte  <<"\", juce::Colour(), 1);\n";
			f<<"		auto p = p_e->processor.params; // pointer\n"; 
//			f<<"		juce::Rectangle<int> r ("<< x_window <<", "<< y_window <<", 700, 700);\n";
			f<<"		juce::Rectangle<int> r (p->"<< inf.nom_obj <<"_cx , p->"<< inf.nom_obj <<"_cy ,p->"<< inf.nom_obj <<"_wx ,p->"<< inf.nom_obj <<"_wy);\n";
			if(x_window < 1000)
				x_window += 500;
			else
			{
				x_window += 20;
				y_window += 20;
			}
			
			f<<"		"<<inf.nom_obj<<"->setBoundsConstrained(r);\n";
			f<<"		"<<inf.nom_obj<<"->setResizable(true, true);\n";
			f<<"		"<<inf.nom_obj<<"->setVisible(true);\n";
			f<<"		"<<inf.nom_obj<<"->setAlwaysOnTop(true);\n";
			f<<"		"<<inf.nom_obj<<"_button->setButtonText(\"Close "<<inf.texte<<"\");\n"; 	
			f<<"	}\n";
			f<<"	//---- close window \n";
			f<<"	else\n";
			f<<"	{\n";
			f<<"		delete "<<inf.nom_obj<<";\n";
			f<<"		"<<inf.nom_obj<<" = nullptr;\n";
			f<<"		"<<inf.nom_obj<<"_button->setButtonText(\"Show "<<inf.texte<<"\");\n"; 	
			f<<"	}\n";
			f<<"}\n";

		}

	//---------------------------------
	for(auto inf : L_infos)
		if(inf.widget=="Window2")
		{
			f<<"//===================\n";
			f<<"// function to show/hide a window\n";
			f<<"// we shift: delete -> internal -> external -> delete\n";
			f<<"void Com::Show_Hide_Window_"<<inf.nom_obj<<"()\n";
			f<<"{\n";
			f<<"	//---- open window \n";
			f<<"	if("<<inf.nom_obj<<" == nullptr)  // deleted -> internal\n";

			f<<"	{\n";
			f<<"	  "<<inf.nom_obj<<" = new TCanvas_"<<inf.nom_obj<<"(this, \""<< inf.texte  <<"\", juce::Colour(), 7); // 7:all buttons\n";

			f<<"	  p_Tab_"<< Get_Tab_name(inf.Idj) <<"->addAndMakeVisible("<<inf.nom_obj<<");\n";

			f<<"	  "<<inf.nom_obj<<"->setBounds( "<< inf.x<<", "<<  inf.y +  size_B <<", "<< inf.W <<", "<< inf.H  <<"); // x,y,w,h\n";

		
			f<<"	  "<<inf.nom_obj<<"->status = 0; //internal\n";
			f<<"	  "<<inf.nom_obj<<"_button->setButtonText(\"External "<< inf.texte  <<"\");\n";
			f<<"	}\n";
	
			f<<"	//----\n"; 
			f<<"	else if("<<inf.nom_obj<<" != nullptr != 0 && "<<inf.nom_obj<<"->status == 0) // internal -> external\n";
			f<<"	{\n";
			f<<"	  delete "<<inf.nom_obj<<";\n";
			f<<"	  "<<inf.nom_obj<<" = nullptr;\n";
			f<<"	\n";
			f<<"	  //............\n";
			f<<"	  "<<inf.nom_obj<<" =  new TCanvas_"<<inf.nom_obj<<"(this, \""<< inf.texte  <<"\", juce::Colour(), 7);\n";
			f<<"	  auto p = p_e->processor.params; // pointer\n";
			f<<"	  juce::Rectangle<int> r (p->"<<inf.nom_obj<<"_cx , p->"<<inf.nom_obj<<"_cy ,p->"<<inf.nom_obj<<"_wx ,p->"<<inf.nom_obj<<"_wy);\n";
			f<<"	  "<<inf.nom_obj<<"->setBoundsConstrained(r);\n";
			f<<"	  "<<inf.nom_obj<<"->setResizable(true, true);\n";
			f<<"	  "<<inf.nom_obj<<"->setVisible(true);\n";
			f<<"	  "<<inf.nom_obj<<"->setAlwaysOnTop(true);\n";
			f<<"	\n";

			f<<"	  "<<inf.nom_obj<<"->status = 1; //external\n";
			f<<"	  "<<inf.nom_obj<<"_button->setButtonText(\"Delete "<< inf.texte  <<"\");\n";
			f<<"	}\n";
			f<<"	//----\n"; 
			f<<"	else if("<<inf.nom_obj<<" != nullptr != 0 && "<<inf.nom_obj<<"->status == 1) // external -> delete\n";
			f<<"	{\n";
			f<<"	  delete "<<inf.nom_obj<<";\n";
			f<<"	  "<<inf.nom_obj<<" = nullptr;\n";
			f<<"	  "<<inf.nom_obj<<"_button->setButtonText(\"Internal "<< inf.texte  <<"\");\n";
			f<<"	}\n";
			f<<"}\n";

		}

	

	for(auto inf : L_infos)
		if(inf.widget=="Window" || inf.widget == "Window2" || inf.widget == "Editor")
		{
			f<<"//===================================\n";
			f<<"// from line:"<<inf.ligne<<endl;
			f<<"TCanvas_"<<inf.nom_obj<<"::TCanvas_"<<inf.nom_obj<<"(Com *p_i, const juce::String &name, juce::Colour backgroundColour, int requiredButtons, bool addToDesktop) : juce::DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)\n";
			f<<"{\n";
			f<<"    p_com = p_i;\n";
			f<<"    setResizable(true, true);\n";

			f<<"    auto p = p_com->p_e->processor.params;\n";
			f<<"    setBounds(p->"<< inf.nom_obj <<"_cx, p->"<< inf.nom_obj <<"_cy, p->"<< inf.nom_obj <<"_wx, p->"<< inf.nom_obj <<"_wy);\n";
			f<<"    setUsingNativeTitleBar (true);\n";
			f<<"    setVisible (true);\n";

			if( inf.widget == "Editor")
			{
				f<<"    p_editor = new CodeEditorComponent(p_com->"<<inf.nom_obj<<"_code,  nullptr);\n";
				f<<"    p_editor->loadContent (\"\\nCode Editor\\n\");\n";
				f<<"    addAndMakeVisible(p_editor);\n";
			}
			
			f<<"}\n";
			f<<"\n";
			f<<"//===================================\n";
			f<<"TCanvas_"<<inf.nom_obj<<"::~TCanvas_"<<inf.nom_obj<<"()\n";
			f<<"{\n";
			if( inf.widget == "Editor")
			{
				f<<"  delete p_editor;\n";
				f<<"  p_editor = nullptr;\n";
			}
			f<<"}\n";
			f<<"\n";
			f<<"//===================================\n";
			f<<"void TCanvas_"<<inf.nom_obj<<"::paint(juce::Graphics& g)\n";
			f<<"{\n";
			if( inf.widget=="Window" || inf.widget == "Window2")
				f<<"   p_com->p_"<<inf.nom_class<<"->"<<inf.nom<<"(g);\n";
			f<<"}\n";
			
			f<<"//==================\n";
			f<<"void TCanvas_"<<inf.nom_obj<<"::resized()\n";
			f<<"{\n";
			f<<"	auto p = p_com->p_e->processor.params;\n";
			f<<"	// rem: tests are due to initial call with small width (128)??\n";
			f<<"    if(getWidth() >= 200)\n";
			f<<"       p->"<< inf.nom_obj <<"_wx = getWidth();\n";
			f<<"    if(getHeight() >= 200)\n";
			f<<"       p->"<< inf.nom_obj <<"_wy = getHeight();\n";


			if( inf.widget == "Editor")
			{
				f<<"  if(p_editor != nullptr)\n";
				f<<"      p_editor->setBounds(0, 0,  getWidth(), getHeight());\n";
			}
			
			f<<"}\n";

			
			f<<"//==================\n";
			f<<"void TCanvas_"<<inf.nom_obj<<"::moved()\n";
			f<<"{\n";
			f<<"	auto p = p_com->p_e->processor.params;\n";
			f<<"    p->"<< inf.nom_obj <<"_cx = getX();\n";
			f<<"    p->"<< inf.nom_obj <<"_cy = getY();\n";
			f<<"}\n";
			
			f<<"//==================\n";
			f<<"void TCanvas_"<<inf.nom_obj<<"::closeButtonPressed()\n";
			f<<"{\n";
			f<<"  if(p_com != nullptr)\n";
			f<<"     p_com->Show_Hide_Window_"<<inf.nom_obj<<"();\n";
			f<<"}\n";
			f<<"//==================\n";

/*
			f<<"void TCanvas_"<<inf.nom_obj<<"::mouseDown(const MouseEvent &event)\n";
			f<<"{\n";
			f<<"  	cout<<\"mouseDown, x=\"<<event.getMouseDownX () <<\", y=\"<<event.getMouseDownY () <<endl;\n";
			f<<"}\n";
			f<<"//==================\n";
			f<<"void TCanvas_"<<inf.nom_obj<<"::mouseMove(const MouseEvent &event)\n";
			f<<"{\n";
			f<<"  	cout<<\"mouseMove, x=\"<<event.getMouseDownX () <<\", y=\"<<event.getMouseDownY () <<endl;\n";
			f<<"}\n";
			f<<"//==================\n";
			f<<"void TCanvas_"<<inf.nom_obj<<":: mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel)\n";
			f<<"{\n";
			f<<"  	cout<<\"mouseWheel, x=\"<<wheel.deltaX <<\", y=\"<<wheel.deltaY <<endl;\n";
			f<<"}\n";
			f<<"//==================\n";
			f<<"bool  TCanvas_"<<inf.nom_obj<<"::  keyPressed (const KeyPress &key)\n";
			f<<"{\n";
			f<<"  	cout<<\" keyPressed\"<<endl;\n";
			f<<"  	return true;\n";
			f<<"}\n";
*/
		}


//----- Parameters of Plugin

	f<<"//==================\n";
	f<<"Parameters::Parameters(";

	for(int j=0; j<L_noms_classes.size(); j++)
	{
		auto nc=L_noms_classes[j];
		f<<nc<<" *p"<<nc;
		if(j<(L_noms_classes.size()-1))
			f<<", ";
		else
			f<<")"<<endl;
	}
	
	f<<"{\n";

	
	f<<"\n";
	for(auto nc : L_noms_classes)
	{
		f<<"    p_"<<nc<<" =  p"<<nc<< ";"<<endl;
	
	}
	f<<"\n";
	
	f<< "}\n";
	

	
	f<<"//=====================\n";
	f<<"Parameters::~Parameters()\n";
	f<<"{\n";
	f<<"}\n\n";

	
	f<<"//==================\n";
	f<<"// rem:  id_number >=0 in ParameterID below: order  is important, this is the number parameterIndex = 0,1,2,.. in  Processor::parameterValueChanged ()\n";
	f<<"void Parameters::Add_Automation_Parameters(Processor * processor)\n";
	f<<"{\n";


		
	int ID = 0; // counter, order  is important, this is the number parameterIndex = 0,1,2,.. in  Processor::parameterValueChanged ()
	for(auto &inf : L_infos)
	{
		if(inf.nom.size() == 0 || inf.opt_param == 0)
			continue;
		
		if(inf.widget == "Color" )
		{
			inf.ID = ID;  // memorize for later

			f<<"	{\n";	
			f<<"	 uint32_t temp = "<<inf.val<<";//default value\n";
			f<<"	 uint32_t temp1 =  temp /  0x10000;\n";
			f<<"	 uint32_t temp2 =  temp %  0x10000;\n";
			
			f<<"	 P1_"<<inf.nom_obj<<" = new AudioParameterInt(juce::ParameterID(\"1"<<inf.nom_obj<<"\", "<< inf.ID <<"), \"1"<<inf.nom_obj<<"\",  0x0000,  0xFFFF, temp1); // ID, ID_number, name , min, max, default value\n";
			f<<"	 P2_"<<inf.nom_obj<<" = new AudioParameterInt(juce::ParameterID(\"2"<<inf.nom_obj<<"\", "<< inf.ID <<"), \"2"<<inf.nom_obj<<"\",  0x0000,  0xFFFF, temp2); // ID, ID_number, name , min, max, default value\n";
			f<<"	}\n";
			f<<"	processor->addParameter(P1_"<<inf.nom_obj<<");\n";
			f<<"	processor->addParameter(P2_"<<inf.nom_obj<<");\n";
			f<<"	P1_"<<inf.nom_obj<<"->addListener(processor); // inform when it is changed by the host, call function  Processor::parameterValueChanged ()\n";
			f<<"	P2_"<<inf.nom_obj<<"->addListener(processor);\n";

			f<<"\n";
			
			ID++;
		}
			
		//.......................... Int or Float 
		if(inf.widget == "HS" || inf.widget == "INC")
		{
			inf.ID = ID;  // memorize for later
			

			if(inf.type == "int")
				f<<"	P_"<<inf.nom_obj<<" = new AudioParameterInt(juce::ParameterID(\""<<inf.nom_obj<<"\", "<< inf.ID <<"), \""<<inf.nom_obj<<"\", "<< inf.xmin <<", "<< inf.xmax  <<", "<<inf.val<<"); // ID, ID_number, name , min, max, default value\n";
			else if(inf.type == "double")
				f<<"	P_"<<inf.nom_obj<<" = new AudioParameterFloat(juce::ParameterID(\""<<inf.nom_obj<<"\", "<< inf.ID <<"), \""<<inf.nom_obj<<"\", "<< inf.xmin <<", "<< inf.xmax  <<", "<<inf.val<<"); // ID, ID_number, name , min, max, default value\n";


			f<<"	processor->addParameter(P_"<<inf.nom_obj<<");\n";
			f<<"	P_"<<inf.nom_obj<<"->addListener(processor); // inform when it is changed by the host, call function  Processor::parameterValueChanged ()\n";

			f<<"\n";

			ID++;
		}
		//.......................... Choice
		else if( inf.widget == "L" || inf.widget == "LB")
		{
			inf.ID = ID;  // memorize for later

			if(inf.object !="") // si il y a une liste explicite
			{
				f<<"    juce::StringArray choices_"<<inf.nom_obj<<";\n";
				f<<"    for(int i=0; i < p_"<<inf.nom_class<<"->"<<inf.object<<".size(); i++)\n";
				f<<"    {\n";
				f<<"       choices_"<<inf.nom_obj<<".add(p_"<<inf.nom_class<<"->"<<inf.object<<"[i]);\n";
				f<<"    }\n";
			}
			else
			{
				f<<"    juce::StringArray choices_"<<inf.nom_obj<<" = {";
				
				for(int i = 0; i< inf.L_l.size()-1; i++)
					f<<"\""<<inf.L_l[i]<<"\",";
				f<<"\""<<inf.L_l[inf.L_l.size()-1]<<"\"};\n";
			}
			
			f<<"	P_"<<inf.nom_obj<<" = new AudioParameterChoice(juce::ParameterID(\""<<inf.nom_obj<<"\", "<< inf.ID <<"), \""<<inf.nom_obj<<"\",  choices_"<<inf.nom_obj<<", "<< inf.val <<"); // ID, id_number, name , list, default value\n";


			f<<"	processor->addParameter(P_"<<inf.nom_obj<<");\n";
			f<<"	P_"<<inf.nom_obj<<"->addListener(processor); // inform when it is changed by the host, call function  Processor::parameterValueChanged ()\n";
			f<<"\n";

			ID++;
		}

		//..........................Bool
		else if(inf.widget == "C")
		{
			inf.ID = ID;  // memorize for later
			inf.xmin = "0";
			inf.xmax = "1";
			
			
			f<<"	P_"<<inf.nom_obj<<" = new AudioParameterBool(juce::ParameterID(\""<<inf.nom_obj<<"\", "<< inf.ID <<"), \""<<inf.nom_obj<<"\", "<< inf.val <<"); // ID, id_number, name , min, max, default value\n";
			f<<"	processor->addParameter(P_"<<inf.nom_obj<<");\n";
			f<<"	P_"<<inf.nom_obj<<"->addListener(processor); // inform when it is changed by the host, call function  Processor::parameterValueChanged ()\n";

			f<<"\n";

			ID++;
		}

		


	}// for inf



	f<<"\n";
	f<<"}\n";
	f<<"\n";

	int ID_max = ID; // memorize the number of parameters
	
	f<<"//rem: there are "<<ID_max<<" parameters, indexed from 0->"<<ID_max-1<<"\n\n";
	f<<"//==================\n";
	f<<"// To Save the state of the plugin\n";
	f<<"// c++ variables -> Save to DAW\n";
	f<<"void Parameters::Save_parameters(Processor * processor, MemoryBlock& destData)\n";
	f<<"{\n";

	f<<"	//cout<<\"-----------\"<<endl;\n";
	f<<"	//cout<<\"Parameters::Save\"<<endl;\n";
	f<<"//	mtx_params.lock();\n";
	f<<"\n";
	f<<"    std::unique_ptr<juce::XmlElement> xml (new juce::XmlElement (\"Params\")); // name of the XML file \n";


	f<<"	//... first some automatic parameters of com.h\n";
	for(auto inf : L_infos)
		if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor")
		{
			f<<"	xml->setAttribute(\""<< inf.nom_obj <<"_cx\", "<<inf.nom_obj<<"_cx);\n";
			f<<"	xml->setAttribute(\""<< inf.nom_obj <<"_cy\", "<<inf.nom_obj<<"_cy);\n";
			f<<"	xml->setAttribute(\""<< inf.nom_obj <<"_wx\", "<<inf.nom_obj<<"_wx);\n";
			f<<"	xml->setAttribute(\""<< inf.nom_obj <<"_wy\", "<<inf.nom_obj<<"_wy);\n";
		} // for inf
	f<<"\n";
	
	f<<"	//... parameters of user's objects\n";
	
	for(auto inf : L_infos)
	{
		if(inf.nom.size() == 0 || inf.opt_no_save == 1)
			continue;
		
		if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor" || inf.widget == "HLINK" || inf.widget == "LINK" || inf.widget == "M" || inf.widget == "MS" || inf.widget == "ST" || inf.widget == "TT" || inf.widget == "B" ) 
			continue;

		//		f<<"	*P_"<<inf.nom_obj<<" =   p_"<<inf.nom_class<<"->"<<inf.nom<<"; // variable c++ -> parameter\n";

		
		f<<"	xml->setAttribute(\""<<inf.nom_class<<"_"<<inf.nom<<"\",   p_"<<inf.nom_class<<"->"<<inf.nom<<");\n";		
		if(inf.nom2.size()>0) // 2nd variable
		{
			//f<<"	// inf.nom2='"<<inf.nom2<<"'\n"; 
			f<<"	xml->setAttribute(\""<<inf.nom_class<<"_"<<inf.nom2<<"\",   p_"<<inf.nom_class<<"->"<<inf.nom2<<");\n";
		}
		if(inf.nom3.size()>0) // 3nd variable
			f<<"	xml->setAttribute(\""<<inf.nom_class<<"_"<<inf.nom3<<"\",   p_"<<inf.nom_class<<"->"<<inf.nom3<<");\n";		
							
							
//		f<<"    //cout<<\"      Save     value  p_"<<inf.nom_class<<"->"<<inf.nom<<"   = \"<<  p_"<<inf.nom_class<<"->"<<inf.nom<<"<<endl;\n";
	
	

	}// for inf

	f<<"	processor->copyXmlToBinary(*xml, destData);\n";
	f<<"\n";
	f<<"//	mtx_params.unlock();\n";
	f<<"}\n";
	f<<"\n";




	f<<"//==================\n";
	f<<"// To Load the state of the plugin\n";
	f<<"// i.e. DAW ->   c++ variable ->  widget variables -> parameters\n";
	f<<"void Parameters::Load_parameters(Processor * processor, const void* data, int sizeInBytes)\n";
	f<<"{\n";
	f<<"	//cout<<\"-----------\"<<endl;\n";
	f<<"	//cout<<\"Parameters::Load\"<<endl;\n";
	f<<"//	mtx_params.lock();\n";
	f<<"\n";
	f<<"    std::unique_ptr<juce::XmlElement> xmlState (processor->getXmlFromBinary (data, sizeInBytes));\n";

	f<<"    if (xmlState.get() != nullptr)\n";
	f<<"      if (xmlState->hasTagName (\"Params\"))  // name of the XML file\n";
	f<<"      {\n";




	f<<"	//... first some automatic parameters of com.h\n";
	for(auto inf : L_infos)
		if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor")
		{

			f<<"	"<<inf.nom_obj <<"_cx  =  xmlState->getIntAttribute (\""<< inf.nom_obj  <<"_cx\", 0); // name, default value if not found\n";
			f<<"	"<<inf.nom_obj <<"_cy  =  xmlState->getIntAttribute (\""<< inf.nom_obj  <<"_cy\", 0); // name, default value if not found\n";
			f<<"	"<<inf.nom_obj <<"_wx  =  xmlState->getIntAttribute (\""<< inf.nom_obj  <<"_wx\", 300); // name, default value if not found\n";
			f<<"	"<<inf.nom_obj <<"_wy  =  xmlState->getIntAttribute (\""<< inf.nom_obj  <<"_wy\", 300); // name, default value if not found\n";
			f<<"	if(processor->p_com != nullptr)\n";
			f<<"		p_com->"<< inf.nom_obj <<"->setBounds("<< inf.nom_obj <<"_cx, "<< inf.nom_obj <<"_cy, "<< inf.nom_obj <<"_wx, "<< inf.nom_obj <<"_wy);\n";
		} // for inf
	f<<"\n";
	f<<"\n";
	
	f<<"	//... parameters of user's objects\n";
	for(auto &inf : L_infos)
	{
		if(inf.nom.size() == 0 || inf.opt_no_save == 1)
			continue;
		
		if(inf.widget == "Window" || inf.widget == "Window2" || inf.widget == "Editor" || inf.widget == "HLINK" || inf.widget == "LINK" || inf.widget == "M" || inf.widget == "MS" || inf.widget == "ST" || inf.widget == "TT"  || inf.widget == "B" ) // menu ou ST
			continue;

		//................
		if(inf.type=="double" || inf.type=="float")
		{
			f<<"	   p_"<<inf.nom_class<<"->"<<inf.nom<<"  =  xmlState->getDoubleAttribute (\""<<inf.nom_obj<<"\", "<<inf.val<<"); // name, default value if not found\n";
			f<<"	   if(processor->p_com != nullptr)\n";
			f<<"		   processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";


			if(inf.nom2.size()>0) // 2nd variable
			{
				f<<"	   p_"<<inf.nom_class<<"->"<<inf.nom2<<"  =  xmlState->getDoubleAttribute (\""<<inf.nom_class<<"_"<<inf.nom2<<"\", "<<inf.val2<<"); // name, default value if not found\n";
				f<<"	   if(processor->p_com != nullptr)\n";
				f<<"		   processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";
				
			}

			if(inf.nom3.size()>0) // 3nd variable
			{
				f<<"	   p_"<<inf.nom_class<<"->"<<inf.nom3<<"  =  xmlState->getDoubleAttribute (\""<<inf.nom_class<<"_"<<inf.nom3<<"\", "<<inf.val3<<"); // name, default value if not found\n";
				f<<"	   if(processor->p_com != nullptr)\n";
				f<<"		   processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";
				
			}
			
		}
		
		else 	if(inf.type=="int")
		{
			f<<"	     p_"<<inf.nom_class<<"->"<<inf.nom<<"  = xmlState->getIntAttribute (\""<<inf.nom_obj<<"\", "<<inf.val<<"); // name, default value if not found\n";
			f<<"		     if(processor->p_com != nullptr)\n";
			f<<"		   	    processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";



			if(inf.nom2.size()>0) // 2nd variable
			{
				f<<"	   p_"<<inf.nom_class<<"->"<<inf.nom2<<"  =  xmlState->getIntAttribute (\""<<inf.nom_class<<"_"<<inf.nom2<<"\", "<<inf.val2<<"); // name, default value if not found\n";
				f<<"	   if(processor->p_com != nullptr)\n";
				f<<"		   processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";
				
			}

			if(inf.nom3.size()>0) // 3nd variable
			{
				f<<"	   p_"<<inf.nom_class<<"->"<<inf.nom3<<"  =  xmlState->getIntAttribute (\""<<inf.nom_class<<"_"<<inf.nom3<<"\", "<<inf.val3<<"); // name, default value if not found\n";
				f<<"	   if(processor->p_com != nullptr)\n";
				f<<"		   processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";
				
			}


			
			
		}

		
		else 	if(inf.type=="string")
		{
			f<<"	     p_"<<inf.nom_class<<"->"<<inf.nom<<"  = (xmlState->getStringAttribute (\""<<inf.nom_obj<<"\", "<<inf.val<<")).toStdString(); // name, default value if not found\n";
			f<<"		     if(processor->p_com != nullptr)\n";
			f<<"		   	    processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";




			if(inf.nom2.size()>0) // 2nd variable
			{
				f<<"	   p_"<<inf.nom_class<<"->"<<inf.nom2<<"  =  xmlState->getStringAttribute (\""<<inf.nom_class<<"_"<<inf.nom2<<"\", "<<inf.val2<<"); // name, default value if not found\n";
				f<<"	   if(processor->p_com != nullptr)\n";
				f<<"		   processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";
				
			}

			if(inf.nom3.size()>0) // 3nd variable
			{
				f<<"	   p_"<<inf.nom_class<<"->"<<inf.nom3<<"  =  xmlState->getStringAttribute (\""<<inf.nom_class<<"_"<<inf.nom3<<"\", "<<inf.val3<<"); // name, default value if not found\n";
				f<<"	   if(processor->p_com != nullptr)\n";
				f<<"		   processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";
				
			}

			
		}
		
		f<<"        //cout<<\"      load     value   p_"<<inf.nom_class<<"->"<<inf.nom<<"   = \"<<   p_"<<inf.nom_class<<"->"<<inf.nom<<" <<endl;\n";
	

		
	}// for inf


	f<<"        }// if xmlState\n";
	f<<"\n";
	f<<"//	mtx_params.unlock();\n";

	f<<"\n";
	f<<"}\n";
	f<<"\n";





	f<<"//==================\n";
	f<<"// This function is called if a automation parameter is changed.\n";
	f<<"// i.e.  parameters ->  c++ variable ->  widget variables\n";
	f<<"//  Warning:   c++ variable and widget variable are accessed with the GUI thread, using a Async lambda function.\n";
	f<<"void Parameters::Transmit_Automation_Parameters(Processor * processor, int parameterIndex)\n";
	f<<"{\n";

	f<<"	//cout<<\"-----------\"<<endl;\n";
	f<<"	//cout<<\"Parameters::Transmit\"<<endl;\n";
	f<<"\n";
	f<<"	if(mtx_params.try_lock())\n";
	f<<"    {\n";
	
	for(auto inf : L_infos)
	{
		if(inf.nom.size() == 0 || inf.opt_param == 0)
			continue;

		//........................
		if(inf.widget == "L" || inf.widget == "LB" || inf.widget == "C" || inf.widget == "HS" || inf.widget == "INC")
		{
			f<<"     //---------------------------\n";
			f<<"   	 if(parameterIndex == "<<inf.ID<<")\n";
			f<<"	 {\n";

			f<<"		juce::MessageManager::callAsync([this, processor]() // lambda function,  will be called Async on the GUI thread\n";
			f<<"    	{\n";

			
			if(inf.widget == "L" || inf.widget == "LB")
				f<<"  	      auto temp =  P_"<<inf.nom_obj<<"->getIndex();\n";
			else	if(inf.widget == "C")
				f<<"  	      auto temp =  bool(*P_"<<inf.nom_obj<<");\n";
			else
				f<<"	      auto temp =  P_"<<inf.nom_obj<<"->get();\n";

			f<<"  	      if(temp != p_"<<inf.nom_class<<"->"<<inf.nom<<") // we have to transmit\n";
			f<<"	      {\n";
			f<<"		     p_"<<inf.nom_class<<"->"<<inf.nom<<" = temp; // parameter -> c++ variable\n";
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"		    p_"<< inf.nom_class <<"->"<< inf.attach_function <<"(); // attached function\n";
			f<<"		     if(processor->p_com != nullptr)\n";
			f<<"		   	    processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";

			f<<"		     //cout<<\"      transmit     from parameter *P_"<<inf.nom_obj<<"   = \"<< *P_"<<inf.nom_obj<<"<<endl;\n";
			f<<"		     //cout<<\"      transmit     to c++ variable p_"<<inf.nom_class<<"->"<<inf.nom<<"   = \"<<  p_"<<inf.nom_class<<"->"<<inf.nom<<"<<endl;\n";
			f<<"	       } //if temp\n";



			f<<"    	}); //callAsync\n";
			f<<"	}//if parameterIndex\n";
			f<<"\n";
		}

		//........................
		else if(inf.widget == "Color")
		{
			f<<"     //---------------------------\n";
			f<<"   	 if(parameterIndex == "<<inf.ID<<")\n";
			f<<"	 {\n";

			f<<"		juce::MessageManager::callAsync([this, processor]() // lambda function,  will be called Async on the GUI thread\n";
			f<<"    	{\n";


			f<<"		uint32_t temp1 =  P1_"<<inf.nom_obj<<"->get();\n";
			f<<"		uint32_t temp2 =  P2_"<<inf.nom_obj<<"->get();\n";
			f<<"		uint32_t P_value = temp1 * 0x10000 + temp2;\n";



			f<<"  	      if(P_value  != (uint32_t)p_"<<inf.nom_class<<"->"<<inf.nom<<") // we have to transmit\n";
			f<<"	      {\n";
			f<<"		     p_"<<inf.nom_class<<"->"<<inf.nom<<" = P_value; // parameter -> c++ variable\n";
			if(inf.attach_function.size()>0) // si il faut appeler fonction
				f<<"		    p_"<< inf.nom_class <<"->"<< inf.attach_function <<"(); // attached function\n";
			f<<"		     if(processor->p_com != nullptr)\n";
			f<<"		   	    processor->p_com->Met_a_jour_"<<inf.nom_obj<<"(); // -> widget variable\n";

			f<<"		     //cout<<\"      transmit     from parameter *P_"<<inf.nom_obj<<"   = \"<< *P_"<<inf.nom_obj<<"<<endl;\n";
			f<<"		     //cout<<\"      transmit     to c++ variable p_"<<inf.nom_class<<"->"<<inf.nom<<"   = \"<<  p_"<<inf.nom_class<<"->"<<inf.nom<<"<<endl;\n";
			f<<"	       } //if temp\n";



			f<<"    	}); //callAsync\n";
			f<<"	}//if parameterIndex\n";
			f<<"\n";
		}

		//............
	}// for inf


	f<<"			mtx_params.unlock();\n";
	f<<"	} // try_lock\n";

	
	f<<"}\n";
	f<<"\n";



	
	//.. midicontrols............
	if(L_midicontrol_name.size()>0)
	{
		f<<"//==================\n";
		f<<"// For midicontrols. Transfer value from controller to c++ variable via atomic variable.\n";
		f<<"// Warning: this is in process thread.\n";
		f<<"int Parameters::Scan_Midi_Control_Process(MidiMessage & message)\n";
		f<<"{\n";
		f<<"	//--- step 1: read message\n";
		f<<"	const uint8_t* p = message.getRawData();\n";
		f<<"	int N = message.getRawDataSize();\n";
		f<<"\n";
		f<<"	int M = 0, C=0, V = 0; // Message, Control, Value\n";
		f<<"	if(N >= 1)\n";
		f<<"			M = p[0];\n";
		f<<"	if(N >= 2)\n";
		f<<"		C = p[1];\n";
		f<<"	if(N >= 3)\n";
		f<<"		V = p[2];\n";
		f<<"\n";
		f<<"	int res = 0;\n"; 
		f<<"\n";
		f<<"	//--- step 2 :  treat  message\n";

	
		for(auto inf : L_infos) // boucle sur les objets
		{
			if(inf.midicontrol.size()>0) // if there is midicontrol
			{
				f<<"\n";
				f<<"     //-------------------\n";
				f<<"     // from line:"<<inf.ligne<<endl;
				f<<"   	if(M == "<<inf.midi_M<<"  && C == "<<inf.midi_C<<" )\n";
				f<<"      {\n";



				if(inf.widget == "N" || inf.widget == "HS" || inf.widget == "VS" || inf.widget == "INC") //entree numerique

				{
					f<<"        A_"<<inf.nom_obj<<".store( int(V/127. * ( "<<inf.midi_R2<<" - "<<inf.midi_R1<<") + "<<inf.midi_R1<<")); // scaling. Transfer from controller to atomic variable\n";
					f<<"             A_"<<inf.nom_obj<<"_asked.store(true);\n";
				}
				else if(inf.widget == "B")
				{
					f<<"         if( V >= "<<inf.midi_R1<<" && V <= "<<inf.midi_R2<<") // condition for action\n";
					f<<"             A_"<<inf.nom_obj<<"_asked.store(true);\n";
//				
				}
				else if(inf.widget == "C")
				{
					f<<"         if( V >= "<<inf.midi_R1<<" && V <= "<<inf.midi_R2<<") // condition for action\n";
					f<<"             A_"<<inf.nom_obj<<"_asked.store(true);\n";
				}
				else if(inf.widget == "L")
				{
					f<<"             A_"<<inf.nom_obj<<".store( int(V/127. * ( "<<inf.midi_R2<<" - "<<inf.midi_R1<<") + "<<inf.midi_R1<<")); // scaling. Transfer from controller to atomic variable\n";
					f<<"             A_"<<inf.nom_obj<<"_asked.store(true);\n";
//				
				}



				f<<"        res = 1;\n";
				f<<"      }\n";
				f<<"\n";
				
			} // if
		} // for inf

		

		f<<"\n";
		f<<"	return res;\n";
		f<<"}\n";
		f<<"\n";



		f<<"//==================\n";
		f<<"// For midicontrols. Transfer value from controller to c++ variable via atomic variable.\n";
		f<<"// Warning: this is in the GUI  thread, called by a periodic loop.\n";
		f<<"void Parameters::Scan_Midi_Control_GUI()\n";
		f<<"{\n";

		for(auto inf : L_infos) // boucle sur les objets
		{
			if(inf.midicontrol.size()>0) // if there is midicontrol
			{
				f<<"\n";
				f<<"     //-------------------\n";
				f<<"     // from line:"<<inf.ligne<<endl;

				

				f<<"      if(A_"<<inf.nom_obj<<"_asked.load()  == true)\n";
				f<<"      {\n";


				if(inf.widget == "N" || inf.widget == "HS" || inf.widget == "VS" || inf.widget == "INC") //entree numerique
				{

				
					f<<"        p_"<<inf.nom_class<<"->"<<inf.nom<<" =  A_"<<inf.nom_obj<<".load();// transfer from atomic variable to c++ variable.\n";

				
					f<<"        if(p_com != nullptr)\n";
					f<<"           p_com->Met_a_jour_"<<inf.nom_obj<<"();\n";

				}
				else if(inf.widget == "B")
				{
					f<<"            p_"<<inf.nom_class<<"->"<<inf.nom<<"();"<<endl; // call function
				}
				else if(inf.widget == "C")
				{
					f<<"           if(p_"<<inf.nom_class<<"->"<<inf.nom<<" != 0) // switch value\n"<<endl;
					f<<"              p_"<<inf.nom_class<<"->"<<inf.nom<<" = 0;\n"<<endl;
					f<<"           else\n"<<endl;
					f<<"              p_"<<inf.nom_class<<"->"<<inf.nom<<" = 1;\n"<<endl;

					f<<"        if(p_com != nullptr)\n";
					f<<"           p_com->Met_a_jour_"<<inf.nom_obj<<"();\n";
				}
				else if(inf.widget == "L")
				{
				
					f<<"        p_"<<inf.nom_class<<"->"<<inf.nom<<" =  A_"<<inf.nom_obj<<".load();// transfer from atomic variable to c++ variable.\n";

				
					f<<"        if(p_com != nullptr)\n";
					f<<"           p_com->Met_a_jour_"<<inf.nom_obj<<"();\n";

				}
				
				if(inf.attach_function.size()>0) // si il faut appeler fonction		 	
					f<<"        p_"<<inf.nom_class<<"->"<<inf.attach_function<<"();\n";

				f<<"        A_"<<inf.nom_obj<<"_asked.store(false); // done\n";
				
				f<<"      }\n";
				f<<"\n";
				
			} // if
		} // for inf

		

		
		f<<"}\n";
		f<<"\n";
	


	}// if midicontrols
	
//---------------------------------
	f.close(); // ferme le fichier com.cc

	



	
//------------------------------	
	if(verbose>=1)
	{
		cout<<" Fin de Fonction Ecriture_fichiers_cpp_JUCE()"<<endl;
		cout<<"----------------------------"<<endl<<endl;
	}

	if(verbose>=1)
		Bilan_collecte_infos(); // for information, debug
}


//===========================================
// fonction pour make_gui
void Extrait_infos_from_file(string nom_rep, string nom_fich)
{

//	cout<<"Extrait_infos_from_file(),   nom_rep="<< nom_rep<<"  nom_fich="<<nom_fich<<endl;
	
	string nom_rep_fichier = nom_rep + "/" + nom_fich; 
	ifstream p_fich(nom_rep_fichier);
	if(!p_fich.good())
	{
		cout<<"\n### Erreur ouverture du fichier "<<nom_rep_fichier<<" dans Extrait_infos_from_file()"<<endl;
		cout<<"###   ...we skip, but check, that this is OK.\n"<<endl;
		return;
	}
	else
	{
		if(verbose>=1)
			cout<<" On extrait les infos depuis le fichier: "<<nom_rep_fichier<<":"<<endl<<endl;
	}


	
	int res=1;
	do
		res = Extrait_infos_from_next_class(p_fich, nom_fich);
	while (res!=0);
	
}


//=================================================
/* recherche dans le fichier de nom fliste si le fichier nom_fichier s y trouve  renvoit 1:oui  0:non */

int deja_traite(string & nom_fichier)
{
	if(verbose>=2)
		cout<<"Fonction: deja_traite() pour le fichier: "<<nom_fichier<<endl;

	ifstream pliste(fliste.c_str());

	int res=prochain(pliste,nom_fichier);
	//cout<<"resultat de deja_traite pour fichier:"<< nom_fichier<<" res="<<res<<endl;
	return res;
}

//=================================================
/* rajoute le fichier nom_fichier a la liste de nom fliste*/

void rajoute_liste(string & nom_fichier)
{
	if(verbose>=2)
		cout<<"Rajoute a la liste"<<endl;

	ofstream pliste(fliste.c_str(),ios::app);
	pliste<<compteur<<" : "<<nom_fichier<<"\n ";
}

//===========================================================
/* fonction qui recherche la chaine 
 1):  #include "chemin/toto.h" ou 
 2):  #include "./chemin/toto.h"
dans le fichier pointe par p_fichier_cc (recherche a partir du pointeur).
   si trouve: renvoit 1 (ou 2)   et pointeur sur la chaine "chemin/toto.h"
   sinon renvoit 0.
*/
int recherche_h(ifstream & p_fichier_cc,string & chaine)
{

	
	int res;
	do
    {
		res=prochain(p_fichier_cc,"#include"); //-> res=0 ou 1
		if(res)  // #include trouve
		{
			p_fichier_cc>>chaine;

			
			
			if (chaine[0]=='\"')  // candidat recherche
			{
				chaine.erase(0,1);  // enleve les caracteres " de debut et fin
				chaine.erase(chaine.size()-1,1);

				
				if(chaine[0] == '.') 
					if(chaine[1] == '/') // si "./chemin/toto.h"
					{
						res=2;
						chaine.erase(0,2);  // enleve les caracteres ./ du debut
					}
			}
			else
				res=3; //include non recherche: ex: #include <iostream>
		}
    }
	while (res == 3);
	return res;
}
//==========================================================
/* fonction qui traite le cas d'un fichier toto.h cad operation (B)*/
string traite_h(string nom_rep_h, string  nom_fichier_h, int opt_rep)
{
	
	string text;

	string nom_rep_fichier_h = nom_rep_h + "/" + nom_fichier_h;

	
	if (deja_traite(nom_rep_fichier_h))  // si le fichier a deja ete traite
		return text;
	else
	{
		rajoute_liste(nom_rep_fichier_h); //le rajoute a la liste

		if(opt_rep == 1)
			liste_files_h_cc.push_back(nom_fichier_h);
		else if(opt_rep == 2)
			liste_files_main.push_back(nom_fichier_h);
		
	}

	compteur++;

	if(verbose)
	{
		for (int i=1;i<=compteur;i++) cout<<" ";
		cout<<compteur<<" Traitement du fichier :"<<nom_rep_fichier_h<<"\n";
	}

	{   // debut partie 1
// ouvre le fichier...........................
		ifstream p_fichier_h(nom_rep_fichier_h.c_str());
		if(!p_fichier_h)
		{
			cerr<<"\n### Erreur ouverture du fichier :"<<nom_rep_fichier_h<<" dans (***)\n";
			cerr<<"###   ...we skip, but check, that this is OK.\n"<<endl;
			return "";
		}

// trouve la liste des .cc inclus ... pour (A)
		if(prochain(p_fichier_h,"liste des .cc ="))  // liste des .cc trouvee
		{
 			int nombre;
			p_fichier_h>>nombre;
			for (int i=1;i<=nombre;i++)
			{
				prochain(p_fichier_h);
				string nom_fichier_cc;
				p_fichier_h>>nom_fichier_cc;

				int res=1;
				if(nom_fichier_cc[0] == '.') 
					if(nom_fichier_cc[1] == '/') // si "./chemin/toto.cc"
					{
						res=2;
						nom_fichier_cc.erase(0,2);  // enleve les caracteres ./ du debut
					}

				if(res==1)
					text += traite_cc(rep_src, nom_fichier_cc, 1);       // appelle (A)
				else if (res==2)
				{
					if(n_passage >=2 || opt_makegui==0 || nom_fichier_cc != "com.cc")  // com.h ne doit pas etre traite si existe pas
						text += traite_cc(rep_src2, nom_fichier_cc, 2);       // appelle (A)
				}	

			}
		}
		else
		{

			string chaine_rep2=nom_fichier_h.substr(0,nom_fichier_h.find(".h"))+ ext_cc; // on remplace le suffixe .h par .cc
			if(n_passage >=2 || opt_makegui==0 || chaine_rep2 != ("com" + ext_cc))  // com.h ne doit pas etre traite si existe pas
				text += traite_cc(nom_rep_h, chaine_rep2, opt_rep);
		}
	} // fin partie 1


	{ // debut partie 2

// ouvre le fichier...........................
		ifstream p_fichier_h(nom_rep_fichier_h.c_str());
		if(!p_fichier_h)
		{
			cerr<<"\n### erreur ouverture du fichier :"<<nom_rep_fichier_h<<" dans (*) \n";
			cerr<<"###   ...we skip, but check, that this is OK.\n"<<endl;
			return "";
		}


// recherche les fichiers titi.h  pour (2)
		int test(0);

		string chaine_h;
		string nom_fichier2_h;
		
		while(int res=recherche_h(p_fichier_h,nom_fichier2_h)) // -> nom_fichier2_h et pointeur p_fichier_h
		{


			if(verbose>=2)
				cout<<"res="<<res<<" nom_fichier2_h="<<nom_fichier2_h<<endl;

			if(n_passage == 1  && opt_makegui==1 &&  nom_fichier2_h =="com.h")
				continue;
			
			test=1;     // a trouve
			if(res==1)
			{
				text += traite_h(rep_src, nom_fichier2_h, 1);       // appelle (B)
				chaine_h += "$(SRC)/"+nom_fichier2_h + " ";  // pour (2)
			}
			else if(res==2) // dans repertoire du main
			{
			
					text += traite_h(rep_src2, nom_fichier2_h, 2);       // appelle (B)
					chaine_h += "$(SRC2)/"+nom_fichier2_h + " ";  // pour (2)
			
			}
			
			
		}

// rajoute la dependance de fichier.h .... pour (2)
		if(test)
		{
			text += "$(SRC)/" + nom_fichier_h + " : " + chaine_h + "\n";
			text += "\ttouch $(SYMB2)   \n\n";  //remet la date a jour
		}
	} //fin partie 2

	compteur--;

	return text;
}

//==========================================================
/* fonction qui traite le cas d'un fichier toto.cc cad operation (A)
rep= 1: si repertoire src
rep =2 si repertoire src2
*/
string traite_cc(string nom_rep_cc, string  nom_fichier_cc, int opt_rep)
{
	string text;
	string chaine_o;
	string chaine_rep2;

	string nom_rep_fichier_cc = nom_rep_cc + "/" + nom_fichier_cc;
	if(verbose)
		cout<<" dans traite_cc:  nom_rep_fichier_cc="<< nom_rep_fichier_cc<<endl;


	if (deja_traite(nom_rep_fichier_cc))  // si le fichier a deja ete traite
	{
		cout<<"fichier cc: "<<nom_rep_fichier_cc<<" deja traite"<<endl;
		return text;
	}
	else
	{
		rajoute_liste(nom_rep_fichier_cc); //le rajoute a la liste
		if(opt_rep == 1)
			liste_files_h_cc.push_back(nom_fichier_cc);
		else if(opt_rep == 2)
			liste_files_main.push_back(nom_fichier_cc);
	}

	compteur++;

	if(verbose)
	{
		for (int i=1;i<=compteur;i++)
			cout<<" ";
		cout<<compteur<<" Traitement du fichier :"<<nom_rep_fichier_cc<<"\n";
	}

// rajoute a liste OBJET , pour (1)......
	string rep =  "$(SRC)/";
	if(opt_rep == 2) // si fichier contenant le main()
		rep = "$(SRC2)/";

	string suffix  = nom_fichier_cc.substr(nom_fichier_cc.rfind(".")); // gives ".c" or ".cc" or ".cc"
//	cout<<"suffix="<<suffix<<endl;

	chaine_objets += rep  +  nom_fichier_cc.substr(0,nom_fichier_cc.find(suffix)) + ext_o + " "; // on remplace le suffixe .cc par .o ou .bc
	

// ouvre le fichier...........................
	ifstream p_fichier_cc(nom_rep_fichier_cc.c_str());
	if(!p_fichier_cc)
	{
		cerr<<"\n### erreur ouverture du fichier "<<nom_rep_fichier_cc<<" dans (**)\n";
		cout<<"###   ...we skip, but check, that this is OK.\n"<<endl;
		return "";
	}

//...pour (3)....

	chaine_o= rep + nom_fichier_cc.substr(0,nom_fichier_cc.find(suffix))+ ext_o + " : " + rep  + nom_fichier_cc+" ";
	
// recherche les fichiers .h
	string nom_fichier_h;
	while(int res=recherche_h(p_fichier_cc, nom_fichier_h))
	{	

		if(verbose>=2)
				cout<<"res="<<res<<" nom_fichier_h="<<nom_fichier_h<<endl;

		if(n_passage ==1 && opt_makegui==1 &&  nom_fichier_h =="com.h")
				continue;
			
		if(res==1)
		{
			text += traite_h(rep_src, nom_fichier_h, 1);       // appelle (B)
			chaine_o += "$(SRC)/"+nom_fichier_h + " ";  // pour (3)
		}
		else if(res==2)
		{
//			cout<<"rep_src2="<<rep_src2<<endl;
			text += traite_h(rep_src2, nom_fichier_h, 2);       // appelle (B)
			chaine_o += "$(SRC2)/"+nom_fichier_h + " ";  // pour (3)
		}

	}

// rajoute la dependance de fichier .o ou .bc.... pour (3)
	text += chaine_o + "\n";
	if(suffix == ".cc")
		text += "\t$(CC) $(CFLAGS) $(SYMB)\n\n"; // \n\n"; // rem: $*  reconnait .o mais pas .bc. Alors on a mit $<
//		text += "\t$(CC) $(CFLAGS)  -c  $< -o $@ \n\n"; //  # $< is the name of the first prerequisite, $@ is the file name of the target\n\n"; // rem: $*  reconnait .o mais pas .bc. Alors on a mit $<
	else if(suffix == ".c")
		text += "\t$(C) $(CFLAGS) $(SYMB)\n\n";
	else if(suffix == ".f") // fortran
		text += "\t$(FF)  $(SYMB)\n\n";
	else if(suffix == ".f90") // fortran
		text += "\t$(FF)  $(SYMB)\n\n";
	else if(suffix == ".for") // fortran
		text += "\t$(FF)  $(SYMB)\n\n";
	
//	text += "\t$(C) $(CFLAGS)  -c  $< -o $@ \n\n";
	//  rem : il faudrait  -c $<  -o $@

	compteur--;

	return text;
}



//===================================================================
//Commande:   makef repertoire nomfichier.cc  makef.config    <nom_executable>
int main(int argc,char *argv[])
{
//	if(0)
		for(int i=0; i<argc; i++)
			cout<<"argv["<<i<<"]="<<argv[i]<<endl;

	
	if(argc != 6)
	{
		cout<<"Here argc = "<<argc<<endl;
		cout<<"the command should contains 5 strings, example:"<<endl;
		cout<<"compp /home/faure/c++/musique/midisyn main.cc main g++"<<endl;
		return 0;
	}

	
	cout<<"=========================="<<endl;
	cout<<"MAKEF"<<endl;
	cout<<"--------"<<endl;


	
	compteur=0;
	rep_src2= string(argv[1]); // ex: /home/rep_essai
	src2 = string(argv[2]); // ex: essai.cc
	comp_name =  string(argv[5]); // ex: g++  or emcc or JUCE
	string chaine_exec;
	if(comp_name != "JUCE")
		chaine_exec = src2.substr(0,src2.find(".cc")); // ex: essai
	else
		chaine_exec = src2.substr(0,src2.find(".cc")); // ex: essai
	string chaine_source = rep_src2 + "/" + src2;// ex: /home/rep_essai/essai.cc


//	cout<<"rep_src2="<<rep_src2<<endl;

	//..................;
	string nom_lib;
//	if (argc >= 5)
	cout<<"\nL'executable choisi s'appellera:"<<(nom_lib=argv[4])<<endl;
	//else
	//	cout<<"\nL'executable (par defaut) s'appellera:"<<(nom_lib=chaine_source.substr(0,chaine_source.find(".cc")))<<endl;

	//..................;
	//comp_name = "g++";
	//if (argc >= 6)
	cout<<"\nLe compilateur est:"<<(comp_name = argv[5])<<endl;
	//else
	//	cout<<"\nLe compilateur (par defaut) est "<<comp_name<<endl;
	//..................;
		
	string nom_config = rep_src2 + "/makef.config";
	cout<<endl<<"Recherche du fichier de parametres:"<<endl;
	string com = "ls " + rep_src2 + "/makef.config";
	int res = system(com.c_str());
	if(res != 0) // si fichier non trouve
	{
		nom_config =  argv[3];
		cout<<"on va donc prendre le fichier propose  par defaut:"<<nom_config<<endl;
	}
	else
		cout<<"ok."<<endl<<endl;

//**********
// lecture du fichier de config
	string rep_makef,librairies,chaine_comp;
	
	ifstream f_config(nom_config.c_str()); // fichier de configurations

	prochain(f_config, 1); f_config>>rep_src;  // ex: /home/faure/c++/Utils

	prochain(f_config, 1); f_config>>rep_makef; // ex:  /home/faure/c++/makef

	prochain(f_config, 1); f_config>>verbose;
	prochain(f_config, 1); f_config>>opt_makeh;
	prochain(f_config, 1); f_config>>opt_makegui;
	prochain(f_config, 1); f_config>>opt_make_zip;


	if(comp_name == "g++")
	{
		prochain(f_config,"librairies et include with g++ =", 1); f_config>>librairies;
		prochain(f_config,"compilation with g++ =", 1); f_config>>chaine_comp;
	}
	else if(comp_name == "emcc")
	{
		prochain(f_config,"librairies et include with emcc =", 1); f_config>>librairies;
		prochain(f_config,"compilation with emcc =", 1); f_config>>chaine_comp;
	}
	else if(comp_name == "JUCE")
	{
		ext_cc = ".cc";
	}
	
	int p;
	while(((p=librairies.find("_"))>=0) && (p<=librairies.size()))
		librairies.replace(p,1," ");  // remplace tous les "_" par " "
	while(((p=chaine_comp.find("_"))>=0) && (p<=chaine_comp.size()))
		chaine_comp.replace(p,1," ");  // remplace tous les "_" par " "
	while(((p=librairies.find("&"))>=0) && (p<=librairies.size()))
		librairies.replace(p,1,"_");  // remplace tous les "&" par "_"
	while(((p=chaine_comp.find("&"))>=0) && (p<=chaine_comp.size()))
		chaine_comp.replace(p,1,"_");  // remplace tous les "&" par "_"

	cout<<"Les options sont:"<<endl;
	cout<<" verbose = "<<verbose<<endl;
	cout<<" (for less/more outputs, put verbose = 0,1,2,3  in file makef.config)"<<endl<<endl; 
	cout<<" opt_makeh = "<<opt_makeh<<" :fabrication automatique de .h (pas encore fait..)"<<endl;
	cout<<" opt_makegui = "<<opt_makegui<<" :fabrication automatique d'une interface de widgets"<<endl;
	cout<<" opt_make_zip = "<<opt_make_zip<<" : fabrication automatique d'une archive exportable .zip"<<endl;


    //--- detection du compilateur demandé : g++ ou emcc
	string ext_exec="$(EXE)";
//	comp_name = chaine_comp.substr(0, chaine_comp.find(" "));
//	comp_name = comp_name.substr(comp_name.rfind("/")+1); // -> g++ ou emcc
	cout<<"comp_name="<<comp_name<<endl;

	/*
	if(comp_name=="g++")
		ext_o = ".o";
	else if(comp_name=="emcc")
	{
		ext_o = ".bc";
		ext_exec = ".js";
	}
	else
	{
		cout<<"compilateur non reconnu:"<<comp_name<<endl;
		exit(0);
	}
	*/
	ext_o = ".$(O)";


	
//*****************


	
	string chaine1 = chaine_source.substr(0,chaine_source.rfind("/")) + "/Makefile";
	string chaine2 = chaine_source.substr(0,chaine_source.rfind("/")) + "/Makefile_tmp"; // version to be exported in zip
	string chaine3 = chaine_source.substr(0,chaine_source.rfind("/")) + "/README_tmp"; // version to be exported in  zip
	string chaine4 = chaine_source.substr(0,chaine_source.rfind("/")) + "/Makefile_win32";
	

//	cout<<"\n On va creer un fichier Makefile:"<<endl<<chaine1<<endl;
	
	ofstream fichier_make(chaine1.c_str()); // Makefile
	ofstream fichier_make2(chaine2.c_str()); // Makefile version to be  exported
	ofstream fichier_make_win(chaine4.c_str()); // Makefile version for windows

	ofstream fichier_README(chaine3.c_str());


		
	fichier_README<<"This project can be compiled and executed on  Linux, Unix, MacOs, Windows systems.\n\n";

	fichier_README<<"On Linux and MacOs,\n";
	fichier_README<<"--------------------\n";
	fichier_README<<"To compile, write in a terminal: \tmake all \n";
	if(comp_name=="g++")
		fichier_README<<"To execute, write in a terminal: \t./" + chaine_exec + "\n\n";
	else if (comp_name=="emcc")
		fichier_README<<"To execute, write in a terminal: \tfirefox ./" + chaine_exec + ".html\n\n";


	fichier_README<<"On Windows 10,\n";
	fichier_README<<"--------------------\n";
	fichier_README<<" Open a terminal in this directory:  Menu of Windows/Visual Studio/x86 Native Tools Command Prompt\n";
	fichier_README<<"write: move Makefile_win32 Makefile\n";
	fichier_README<<"To compile, write: \tnmake all \n";
	if(comp_name=="g++")
		fichier_README<<"To execute, write in a terminal: \t" + chaine_exec + "\n\n";
	else if (comp_name=="emcc")
		fichier_README<<"To execute, write in a terminal: \tfirefox " + chaine_exec + ".html\n\n";


	
	fichier_README<<"Informations about this project are in the file: "<<src2<<"\n";
	fichier_README<<"\n\nInstructions how to install c++ and root on your computer:\n";
	fichier_README<<" https://www-fourier.ujf-grenoble.fr/~faure/enseignement/c++/cours_c++/cours_1/cours_1.xhtml \n";
	fichier_README.close();

	
	//--------------------
	


	//..............
	string text1;
	
	text1 += "# This Makefile file is for Linux, Unix, MacOs systems and  has been created automatically by  makef.cc. \n# To compile, write in a terminal: \tmake all \n";
	text1 += "# To execute, write in a terminal:\t./" + chaine_exec + "\n\n";

	fichier_make << text1;
	fichier_make2 << text1;

	fichier_make << "# To make clean: \tmake clean \n";
	fichier_make << "# To create a library: \tmake lib \n";
	fichier_make << "# To export the project (source files): \tmake zip \n \n";
	fichier_make << "# To export only binary files: \tmake zip_bin \n";
	fichier_make << "# To check the OS: \tmake os\n";

	//.............
	fichier_make_win<<"# This Makefile file is for Windows 10 and  has been created automatically by  makef.cc. \n";
	fichier_make_win<<"# Open a terminal in this directory:  Menu of Windows/Visual Studio/x86 Native Tools Command Prompt\n";
	fichier_make_win<<"# Change its name, write: move Makefile_win32 Makefile\n";
	fichier_make_win<<"# To compile, write: \tnmake all \n";
	fichier_make_win<<"# To execute, write:\t" + chaine_exec + ".exe\n\n";
	fichier_make_win<<"# To make clean: \tnmake clean \n";

	
    //...........
	
	text1 = "\n# ----- directories (librairies, sources, and main) ----------------------\n\n";
	fichier_make << text1;
	fichier_make2 << text1;
	fichier_make_win<<text1;

	//......
	
	fichier_make<<"SRC ="<<rep_src<<endl;  // ex: /home/faure/c++/Utils
	fichier_make<<"SRC2 ="<<rep_src2<<endl<<endl; // ex: /home/rep_essai

	fichier_make2<<"SRC = ./Utils"<<endl;
	fichier_make2<<"SRC2 = ."<<endl;

	fichier_make_win<<"SRC = .\\Utils"<<endl;
	fichier_make_win<<"SRC2 = ."<<endl;


	//.....
	ostringstream ss;
	ss<<"# ---- detects operating system on unix like machine"<<endl;
	ss<<"UNAME_S := $(shell uname -s)"<<endl;
	ss<<"ifeq ($(UNAME_S),Linux)"<<endl;
    ss<<"    OSFLAG +=  -D__LINUX_ALSA__ -lasound"<<endl; 
	ss<<"endif"<<endl;
	ss<<endl;
	ss<<"ifeq ($(UNAME_S),Darwin)"<<endl;
	ss<<"   OSFLAG += -D__MACOSX_CORE__   -framework CoreMIDI -framework CoreAudio -framework CoreFoundation"<<endl;
	ss<<"endif"<<endl;
	ss<<endl;
	ss<<"os:"<<endl;
	ss<<"	@echo $(OSFLAG)"<<endl;
	ss<<"#--------------------"<<endl;

 
	fichier_make<<ss.str();
	fichier_make2<<ss.str();
	
	
	//..................
	string text2;
	text2 += "LIBR=" + librairies + "\n \n";

	text2 += "\n#-- instructions, utilities ---------------\n\n";
	text2 += "CC =" + chaine_comp + "    # compileur C++\n";
	text2 += "C  = gcc  -O3  -Wno-unused-result -Wno-format-truncation  -D_GNU_SOURCE -DRESAMP_CUBIC   # compilateur C\n";
	text2 += "FF  = gfortran     # compilateur Fortran\n";
	text2 += "CFLAGS =  -I$(SRC)  -I$(SRC2)     # Include directories\n\n";
	text2 += "LINK = $(CC)  # linker\n";

	if(comp_name=="g++")
	{
		text2 += "O = o\n";
		text2 += "EXE = \n";
	}
	else if(comp_name=="emcc")
	{
		text2 += "O = bc\n";
		text2 += "EXE = .js\n";
	}
	

	
	text2 += "SYMB =  -c  $< -o $@  # rem: $< is the name of the first prerequisite, $@ is the file name of the target \nSYMB2 = $@";
	text2 += "\n#============  targets =======================================\n\n";

	//......
	string text_win; // for windows
	text_win += "CLIBS = C:\\root_v6.24.00\\lib\nCLIBS2 =  C:\\Users\\fredof\\Downloads\\vcpkg\\vcpkg\\installed\\x86-windows\\lib\nLIBR = $(CLIBS)\\libCore.lib $(CLIBS)\\libImt.lib $(CLIBS)\\libRIO.lib $(CLIBS)\\libNet.lib $(CLIBS)\\libHist.lib $(CLIBS)\\libGraf.lib $(CLIBS)\\libGraf3d.lib $(CLIBS)\\libGpad.lib $(CLIBS)\\libROOTVecOps.lib $(CLIBS)\\libTree.lib $(CLIBS)\\libTreePlayer.lib $(CLIBS)\\libRint.lib $(CLIBS)\\libPostscript.lib $(CLIBS)\\libMatrix.lib $(CLIBS)\\libPhysics.lib $(CLIBS)\\libMathCore.lib $(CLIBS)\\libThread.lib $(CLIBS)\\libROOTDataFrame.lib $(CLIBS)\\libGui.lib $(CLIBS2)\\gsl.lib $(CLIBS2)\\fftw3.lib $(CLIBS2)\\lapack.lib $(CLIBS2)\\armadillo.lib $(CLIBS2)\\openblas.lib  winmm.lib\n";

	text_win += "OSFLAG =  -D__WINDOWS_MM__\n\n";
	text_win += "#-- instructions, utilities ---------------\n\n";
	text_win += "CC = cl.exe /std:c++14 /EHsc /MD  $(OSFLAG) # compileur C++\n";
	text_win += "C  = cl.exe  /EHsc /MD  $(OSFLAG) # compileur C\n";
	text_win += "CFLAGS =  /IC:\\root_v6.24.00\\include /I$(SRC)  /I$(SRC2)  /IC:\\Users\\fredof\\Downloads\\vcpkg\\vcpkg\\installed\\x86-windows\\include    # include directoires\n\n";
	text_win += "LINK = link.exe  # linker\nO = obj\nEXE = .exe\nSYMB = -c %s /Fo$@   #  rem: $@ is the file name of the target , $** is all the prerequisite,  %s  is the name of the first prerequisite\nSYMB2 =  $@\n";
	text_win += "#============  targets =======================================\n\n";

	
	//=======================================
	// si opt_makegui==1, il faut deux passages, car:
	// 1er passage: on ne rajoute pas com.h et com.cc a Makefile (car ils n'existent pas encore), mais on lit les infos et on ecrit les fichiers com.h et com.cc
	// 2eme passage: on  rajoute les fichiers com.h et com.cc à Makefile
	string text2_bis;
	
	for(n_passage =1; n_passage <= 1+opt_makegui; n_passage++) // 1 ou 2 passages selon opt_makegui
	{
		cout<<"Numero de passage = "<<n_passage<<endl;
		
		chaine_objets="OBJETS= ";
			
		//---- vide listes

		L_infos.clear();
		L_noms_classes.clear();
		L_noms_fichiers.clear();
		L_noms_menus.clear();
		L_noms_tabs.clear();
		L_noms_TT.clear();

		liste_files_h_cc.clear();
		liste_files_main.clear();

		liste_files_linked.clear();
		liste_files_linked_main.clear();
//----
	
		
		//--- vide le fichier liste.txt ----------------------

		fliste = rep_makef+"/liste.txt";

		ofstream pliste(fliste.c_str()); // crée fichier
		pliste<<endl;
		pliste.close();
		
		//----------------------
	
		if(verbose)
			cout<<"#=== NUMERO DE PASSAGE:  n_passage = "<<n_passage<<endl;
		
		text2_bis = traite_cc(rep_src2, src2, 2);  // fichier .cc principal, contenant main()

		//================= Option on fabrique l'interface de commandes com.h et com.cc
		if(opt_makegui)
		{
			//-- etape 1: on extrait les informations des fichiers
			cout<<"#=========================="<<endl;
			cout<<"MAKE_GUI"<<endl;
			cout<<"--------"<<endl;
			if(verbose>=1)
				cout<<"#== Part1: extraction des informations =========="<<endl;

			for(auto nom_fich : liste_files_h_cc)
				//	if(nom_fich != "com.cc" && nom_fich != "com.h")
				if((!contains(nom_fich, "com.cc")) && (!contains(nom_fich,"com.h")))
					Extrait_infos_from_file(rep_src, nom_fich); 
	
			for(auto nom_fich : liste_files_main)
//				if(nom_fich != "com.cc" && nom_fich != "com.h")
				if((!contains(nom_fich, "com.cc")) && (!contains(nom_fich,"com.h")))
					Extrait_infos_from_file(rep_src2,  nom_fich); 


			//----- etape 1-2: on cree l'arborescence des menus (L_noms_tabs -> L_sous_tabs)
//			vector<string> 	L_noms_tabs ={ "A__A1" , "A__A2", "B", "A__A1__C1", "A__A1__C2", "C", "B__B1"}; // for test
			L_sous_tabs = Cree_arborescence_tabs(L_noms_tabs, "__");

			
			//-------------------
			if(verbose)
				Bilan_collecte_infos();
		
			//-- etape 2  Ecriture des fichiers com.cc com.h

			if(comp_name=="g++")
				Ecriture_fichiers_cpp(); // -> com.cc et com.h
			else if(comp_name=="emcc")
				Ecriture_fichiers_cpp_JS(); // -> com.cc et com.h et index.html
			else if(comp_name=="JUCE")
				Ecriture_fichiers_cpp_JUCE(); // -> com.cc et com.h 
		
		}
		if(verbose>=1)
			for(auto nc: L_noms_classes)
				cout<<"**** nc="<<nc<<endl;

	} // for n_passage

	text2 += text2_bis;
	
	string text2_bis_win = text2_bis;  // copy

	ReplaceStringInPlace(text2_bis_win,"/","\\");  //--- on remplace les / par des \\ 

	ReplaceStringInPlace(text2_bis_win,"touch $(SYMB2)","copy /b $(SYMB2) +,, # ");

	

	text_win += text2_bis_win;
	//===============================================
	text2 += chaine_objets + "\n";  // finit (1)

	string chaine_objets_win = chaine_objets;  // copy
	ReplaceStringInPlace(chaine_objets_win,"/","\\");  //--- on remplace les / par des \\


	text_win += chaine_objets_win + "\n";  // finit (1)

//---------------------
	text2 += "\n#-- build the final binary file ------------- \n\nall:  $(OBJETS) $(SRC2)/" + chaine_exec + ext_o + "  \n\t$(CC) $(CFLAGS)  -o $(SRC2)/" + chaine_exec + ext_exec + "  $(OBJETS)     $(LIBR) \n";
	text_win += "\n#-- build the final binary file ------------- \n\nall:  $(OBJETS) $(SRC2)\\" + chaine_exec + ext_o + "  \n\t$(LINK)  $(OBJETS) $(LIBR) \n";

	fichier_make<<text2;
	fichier_make2<<text2<<endl;
	fichier_make_win<<text_win;
	
	if(opt_make_zip)
	{
		fichier_make <<"\tmake zip\n\n"; // fabrique aussi le projet zip
		fichier_make2<<"\tmake zip\n\n"; // fabrique aussi le projet zip
	}
	
	fichier_make << "clean:   \n\t\\rm -f $(SRC2)/" + chaine_exec + ext_exec + "  $(OBJETS)\n";
	fichier_make2<< "clean:   \n\t\\rm -f $(SRC2)/" + chaine_exec + ext_exec + "  $(OBJETS)\n";
	fichier_make_win<< "clean:   \n\t-del /q $(SRC2)\\" + chaine_exec + ext_exec + "  $(OBJETS)\n";



	fichier_make << "\n#--- build a library ------------------ \n\nlib: $(OBJETS)\n\tar r $(SRC2)/" << chaine_exec << "  $(OBJETS) \n\n";
	fichier_make2<< "\n#--- build a library ------------------ \n\nlib: $(OBJETS)\n\tar r $(SRC2)/" << chaine_exec << "  $(OBJETS) \n\n";



	
    //======= Fabrication de l'exportation project.zip de fichiers source============

	{
		string nom_zip = "project_c++_" + chaine_exec + ".zip"; // ex: project_c++_essai.zip
		string nom_zip_bin = "project_c++_bin_" + chaine_exec + ".zip"; // ex: project_c++_bin_essai.zip
	
		string text3; // for sources files


		//.. rem: && sert a enchainer les instructions comme ; mais garanti de ne le faire que si la precedente est OK
		//.. rem: \ permet de revenir à la ligne
		
		text3 += "\n#--- Creates a .zip that contains all the source files of the project \n\n";
		text3 += "zip:\n";

		text3 += "\tcd $(SRC) && cd .. && \\\n";  // se place dans /home/faure/c++
		text3 += "\trm -rf tmp && \\\n"; // efface repertoire precedant par prevention
		text3 += "\tmkdir tmp && \\\n"; //cree nouveau repertoire





		
		//... rajoute les fichiers .h et .cc
		for(int i=0; i<liste_files_h_cc.size(); i++)
		{
			text3 += "\tzip tmp/" + nom_zip + " Utils/" + liste_files_h_cc[i];
			if(i<liste_files_h_cc.size()-1)
				text3 += " && \\\n";
			else
				text3 += "\n";
		}

		for(int i=0; i<liste_files_linked.size(); i++)
		{
//			cout<<"Add:"<<liste_files_linked[i]<<endl;
			text3 += "\tzip " + nom_zip + " " + liste_files_linked[i];
			text3 += " && \\\n";
		}

		

		text3 += "\tcd $(SRC2) && \\\n";  // se place dans /home/rep_essai
		text3 += "\trm -rf " +  nom_zip + " && \\\n"; // detruit eventuel fichier par prevention

		if(liste_files_h_cc.size()>0)
			text3 += "\tmv $(SRC)/../tmp/"  + nom_zip + " " + rep_src2 + " && \\\n"; //deplace le projet 

	
		//... rajoute les fichiers du main()
		for(int i=0; i<liste_files_main.size(); i++)
		{
			text3 += "\tzip " + nom_zip + " " + liste_files_main[i];
			text3 += " && \\\n";
		}

		for(int i=0; i<liste_files_linked_main.size(); i++)
		{
//			cout<<"Add:"<<liste_files_linked_main[i]<<endl;
			text3 += "\tzip " + nom_zip + " " + liste_files_linked_main[i];
			text3 += " && \\\n";
		}

				
		text3 += "\tzip " + nom_zip + " Makefile_tmp  Makefile_win32 && \\\n";

		text3 += "\tprintf \"@ Makefile_tmp\\n@=Makefile\\n\" | zipnote -w "  + nom_zip + " && \\\n";	 // change le nom Makefile_tmp -> Makefile dans l'archive projet.zip

//		text3 += "\trm Makefile_tmp  && \\\n";

		text3 += "\tzip " + nom_zip + " README_tmp  && \\\n";

		text3 += "\tprintf \"@ README_tmp\\n@=README\\n\" | zipnote -w " + nom_zip + " && \\\n";	 // change le nom README_tmp -> README dans l'archive projet.zip

//		text3 += "\trm README_tmp\n";
		text3 += "\techo Creation of zip finished\n";
		
		fichier_make<<text3;
		fichier_make2<<text3;


		//---------------------------------
		string text4; // for binary files

		text4 += "\n#--- Creates a .zip that contains only binary and document files of the project\n\n";
		text4 += "zip_bin: $(SRC2)/" + chaine_exec + ext_exec + "\n";
		

		text4 += "\tcd $(SRC2) && \\\n";  // se place dans /home/rep_essai
		text4 += "\trm -rf " +  nom_zip_bin + " && \\\n"; // detruit eventuel fichier par prevention

		
		text4 += "\tzip " + nom_zip_bin + "  " +  chaine_exec + ext_exec + " && \\\n"; // add the binary executable file

		for(int i=0; i<liste_files_linked_main.size(); i++)
		{
			text4 += "\tzip " + nom_zip_bin + " " + liste_files_linked_main[i];
			text4 += " && \\\n";
		}
		text4 += "\techo Creation of zip_bin finished\n"; 
		
		fichier_make<<text4;
		fichier_make2<<text4;
				
	}
	
	
	//---------------------
	cout<<"Fabrication du Makefile terminee."<<endl;
	cout<<"=========================="<<endl<<endl;


	
	return 0;
}


