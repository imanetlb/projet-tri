Sommaire : 
  - Nos fichiers
  - Utilisation et compilation
  - Informations importantes


Ce projet comporte plusieurs fichiers qui forment un programme complet. 

Les fichiers sont :

-main.c :
  Contient la fonction main qui est le point d'entrée du programme. Il utilise les fonctions définies dans fonction.c en incluant le fichier fonction.h.

-fonction.c : 
  Contient les implémentations des fonctions, les fonctions utilisés dans le main.c.

-fonction.h : 
  Contient les déclarations des fonctions définies dans le fichier fonction.c. Il est inclus par main.c pour permettre l'utilisation des fonctions dans ce dernier.

-help : 
  Ce fichier est une aide destinée à l'utilisateur pour l'aider à l'utilisation du programme.

-Makefile : 
  Ce fichier permet d'automatiser les tâches de construction et de compilation du projet.

-scriptShell.sh :
Ce script shell automatise les tâches du projet. Il compile par exemple le code source en utilisant le Makefile ou exécute des tests.

********************************************************************

Compilation :

##facultative car effectuée par le scriptShell.sh : en utilisant cette commande "bash scriptShell.sh <arg> <option> nom_fichier"##

Le fichier Makefile se charge de la compilation automatiquement.
Pour compiler le projet, veuillez utiliser la commande suivante dans le terminal :
      
      make -f MakeFile 

Exécution : 

##facultative car effectuée par le scriptShell.sh : en utilisant cette commande "bash scriptShell.sh <arg> <option> nom_fichier"##

  Pour exécuter le programme, veuillez utiliser la commande suivante dans le terminal :

      ./tri <type_tri> <mode> <fichier.csv>     

  <type_tri> :
    - --avl pour un tri avec AVL 
    - --abr pour un tri avec ABR
    - --tab pour un tri avec liste chainée

  <mode> : 
    - X pour X
    - Y pour Y
    - ....

Utilisation du script shell : 
  
  Pour executer le script shell, veuillez utiliser la commande suivante dans le terminal :

      ./scriptShell.sh  

-un fichier.png est créé à la fin du script, le script affiche également sur le terminal le nom du fichier png créé (ce fichier.png correspond aux graphiques créés)

Aide : 

  Pour plus d'informations sur l'utilisation du programme, appelez le fichier help en utilisant la commande suivante dans le terminal :

      cat help


********************************************************************


Informations Importantes :

- Si l'utilisateur rentre deux fois la même option mais avec deux mode différent, seul le premier mode de l'option sera pris en compte.

- Le scriptShell traite toutes les options du cahier des charges tandis que le C, lui, ne traite pas les options -t3 et -p3 ainsi que les cartes découlant de ces deux options.

- Le programme en C pour l'humidité n'est fonctionnel qu'avec le type "--abr"




