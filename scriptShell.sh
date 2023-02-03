#!/bin/bash

#déclaration des listes pour simplifier le traitement
declare -a arguments_for_data=("-t1" "-t2" "-t3" "-p1" "-p2" "-p3" "-w" "-h" "-m") #obligatoire mais non exclusif
#declare -a arguments_temperature=("-t1" "-t2" "-t3") #exclusives entre elles 
#declare -a arguments_pression=("-p1" "-p2" "-p3") #exclusives entre elles
declare -a arguments_for_location=("-F" "-G" "-S" "-A" "-O" "-Q") #Exclusif entre elle,si absent alors traiter toutes les stations
declare -a arguments_de_tri=("--tab" "--abr" "--avl") #une parmi les 3, si non spécifié alors considerer le tri en mode avl
#-f suivi du nom du fichier 
#-d suivi de date_début date_fin (format YYYY-MM-DD)
#--help

#################################function vérification format de date##########################
function verifFormatdate {
date=$1
# Expression régulière pour vérifier le format de date YYYY-MM-DD
regex='^[0-9]{4}-[0-9]{2}-[0-9]{2}$'
# Vérification de la date avec l'expression régulière
if [[ $date =~ $regex ]]; then
  echo "La date est valide."
else
  echo "La date n'est pas valide."
fi
}
################FIn function vérification format de date########################


###################################################################
## si aucune option on indique le mode d'utilisation du scrpipt en une ligne
if [ $# = 0 ]; then
  echo "-------------------------------------------------------------------------------------------------------------------------------"
  echo "# Usage : scriptShell.sh [-t1 -t2 -t3 mode temperature] [-p1 -p2 -p3 mode pression] [-h altitude] [-m humidité] [--tab --avl --abr mode tri] [-d date_debut date_fin] [-F -O -G -S -A -Q localités] [-f \"nom_fichier\".csv]"
  echo "# $0 --help pour obtenir une aide détaillée"
  echo "--------------------------------------------------------------------------------------------------------------------------------"
  exit 0
fi
##########on va vérifier si un argument est donnée 2 fois###########
i=0
j=0
for var1 in "$@"
do
    #echo "$var1"
   i=$(($i + 1))
   #echo "i = $i"
	for var2 in "$@"
	do	
	j=$(($j + 1))
		#echo "j = $j"

		if [[ "$var1" == "$var2" ]]; then
			if [[ "$i" != "$j" ]]; then
				echo "ERROR: l'argument [$var1] est présent plusieurs fois"
				#echo "i=$i  j=$j"
				exit 1
			fi
		fi
	done
j=0
done
###################### FIn verification d'une option ou argument en double ############

###############################################
# vérifier si au moins un argument
tri=""  #elle contiendra le type de tri --tab, --avl ou --abr
location="" #elle contiendra l'option de la localité -F, -O......
startDate=""
endDate=""
myFile="" #pour le fichier d'entree exemple data.csv
Tmode="" # elle contiendra -t1 ou -t2 ou -t3  si mode temp saisi (si plsuieurs il garde le 1er)
Pmode="" # elle contiendra -p1 ou -p2 ou -t3  si mode pression saisi (si plsuieurs il garde le 1er)
NextArgumentDate=0
NextArgumentFile=0
argumentValide=0
nbre_argument_tri=0
nbre_argument_location=0
lesArgumentsData=() #tableau qui contiendra la liste des arguments data saisis
vent=0
humidite=0
altitude=0
compteurArg=1
for myArg in "$@"
do
	argumentValide=0

	if [[ "$NextArgumentDate"  == 1 ]]; then
		echo "traitement start date..........."
		startDate="$myArg"
		echo $startDate
		verifFormatdate "$myArg"
		NextArgumentDate=2
		argumentValide=1
		continue 
	fi

	if [[ "$NextArgumentDate"  == 2 ]]; then
		echo "traitement end date..........."
		endDate="$myArg"
		echo $endDate
		verifFormatdate "$myArg"
		NextArgumentDate=0
		if [[ "$startDate" > "$endDate" ]]; then
			echo "ERROR : dates non valides : la date fin doit etre superieur à la date debut"
			exit 1
		fi
		argumentValide=1
		continue 
	fi	

	if [[ "$NextArgumentFile"  == 1 ]]; then
		echo "traitement nom du fichier..........."
		myFile="$myArg"
		echo "le nom du fichier en entrée est :$myFile"
		if [[ ! -f "$myFile" ]]; then
			echo "ERROR : fichier introuvable ou non conforme"
			exit 1
		fi
		if [[ ! -s "$myFile" ]]; then
			echo "fichier vide"
			exit 1
		fi
		argumentValide=1
		NextArgumentFile=0
		continue 
	fi	

	for data_argument in "${arguments_for_data[@]}"
	do
		if [[ " ${data_argument} " == " ${myArg} " ]]; then
			# 
			argumentValide=1
			#echo "un argument pour data existe"      
     #on va prendre le 1er mode de temperature trouvé si plusieurs saisis
     if [[ "$myArg" == "-t1" || "$myArg" == "-t2" || "$myArg" == "-t3" ]]; then
          if [[ -z "$Tmode" ]]; then
              Tmode=$myArg
            echo "l'options $Tmode a été ajoutée à la liste"
           else
              echo " option $myArg a été ignorée car il y a déja un mode de temperature"
              continue
          fi
		  fi
      #on va prendre le 1er mode de pression si plusieurs sont données 
      if [[ "$myArg" == "-p1" || "$myArg" == "-p2" || "$myArg" == "-p3" ]]; then
          if [[ -z "$Pmode" ]]; then
              Pmode=$myArg
              echo "l'options $Pmode a été ajoutée à la liste"
           else
              echo " option $myArg a été ignorée car il y a déja un mode pour la pression"
              continue
          fi
		  fi
      lesArgumentsData=( "${lesArgumentsData[@]}" "$myArg" )
     # echo "les arguments data ${lesArgumentsData[@]}"
    fi
	done

	for location_argument in "${arguments_for_location[@]}"
	do
		if [[ " ${location_argument} " == " ${myArg} " ]]; then
			# si plusieurs arguments de localisation ==>error
			argumentValide=1
			echo "un argument pour location est saisi: $myArg"
			location="$myArg"
			nbre_argument_location=$(($nbre_argument_location + 1))
			if [[ "$nbre_argument_location" >1 ]]; then
				echo " ERROR : plusieurs arguments de localication sont saisis"
				exit 1
			fi
		fi
	done
		
	for tri_argument in "${arguments_de_tri[@]}"
	do
		if [[ " ${tri_argument} " == " ${myArg} " ]]; then
			# si plusieurs arguments de tri ==>error
			echo "un argument pour le tri a été saisi"
			argumentValide=1
			tri="$myArg"
			nbre_argument_tri=$(($nbre_argument_tri + 1))
			echo "$tri"
			if [[ "$nbre_argument_tri" >1 ]]; then
				echo " ERROR : plusieurs arguments de tri saisis"
				exit 1
			fi
		fi
	done

	#argument pour dates
	if [[ "$myArg" == "-d" ]]; then
		echo "argument date à traiter"
		NextArgumentDate=1
		argumentValide=1
		continue
	fi
	
	#argument pour le fichier
	if [[ "$myArg" == "-f" ]]; then
		echo "argument fichier à traiter"
		NextArgumentFile=1
		argumentValide=1
		continue
	fi
	if [[ "$myArg" == "--help" ]]; then
		argumentValide=1
    cat help
		exit 0
	fi
	if [[ "$argumentValide" == 0 ]]; then
	
		echo "ERROR : arguments invalides: un argument inattendu a été saisi: $myArg"
		exit 1
	fi
	
done

#vérifier si au moins un argument de type data a été saisi
if [[ ${#lesArgumentsData[@]} < 1 ]]; then
echo "---------"
 echo "ERROR : aucune option pour le type des données n'est spécifiée: [-t1 -t2 -t3 -p1 -p2 -p3 -m -h -w]"
 echo "Exit avec code erreur =1 "

 exit 1
fi
#vérifier que l'option -f est spécifiée, la vérification si le fichier existe dans le dossier est faite plus haut
if [[ -z "$myFile" ]]; then
 echo "-----------"
 echo "ERROR : aucun fichier des données à traiter n'est spécifié"
 echo "Exit avec code erreur =1 "
 exit 1
fi
#########################################################################################################
# on va traiter les options localité
# le script prend en compte en entrée une seul option localité 
# si l'option n'est pas donnée alors on consièdere pour toutes les stations 
echo ""
echo "\-- Quelle zone a été choisie : ----------------------------------------------/"
if [[ "$location" == "-F" ]]; then
#France Métropolitaine + Corse
	echo "on va traiter pour les stations de France Métropolitaine + Corse"
	yMin=40 ; yMax=51
	xMin=-6 ; xMax=10

elif [[ "$location" == "-A" ]]; then
# Antilles
	echo "on va traiter pour les stations  des antilles"
	yMin=15 ; yMax=25 
	xMin=-89 ; xMax=-60

elif [[ "$location" == "-G" ]]; then
#coordonnées GUYANE
	echo "on va traiter pour les stationde la Guyane"
	yMin=2 ; yMax=5
	xMin=-54 ; xMax=-51

elif [[ "$location" == "-O" ]]; then
#Océan Indien
	echo "on va traiter pour les localités d'Ocean Indien"
	yMin=-50 ; yMax=20 
	xMin=20 ; xMax=120

elif [[ "$location" == "-S" ]]; then
#Saint-Pierre et Miquelon
	echo "on va traiter pour Saint-Pierre et Miquelon"
	yMin=46 ; yMax=47 
	xMin=-56 ; xMax=-55

elif [[ "$location" == "-Q" ]]; then
#Antarctique
	echo "on va traiter pour les stations de l'Antarctique"
	yMin=-90 ; yMax=-62
	xMin=-180 ; xMax=180

else 
#toutes les localités
	echo "on va traiter pour TOUTES les stations sans filtre de localités"
	yMin=-90 ; yMax=90
	xMin=-180 ; xMax=180
fi
echo "\---------------------------------------------------------------------------------------------/"
##################################################################################################################
# dans le tableau lesArgumentsData il y a la liste des arguments data saisi: mais au maximum un seul pour le mode temp et idem pour la pression
# par exemple lesArgumentsData = ( -h -w -m -t1 -p2 ) 

# on va traiter filtrer les arguments de type data
echo "\------------------------------------------------------------------------------------------/"
echo " on va générer les fichiers pour les options de type data que vous avez choisies : ["${lesArgumentsData[@]}"] pour la zone [$location] pour la période [$startDate $endDate] "

for myOption in "${lesArgumentsData[@]}"; do
echo "\------------------------------------------------------------------------------------------/"
	case $myOption in
		"-t1")
  echo ">> DEBUT >> génération fichier pour mode t1.........................."
   #format fichier (2 colonnes): id station;temperature
    if [[ ! -z "$startDate" ]]; then
    		# on génère le fichier selon les dates pour  mode 1 de la temperature
		  echo " temperature  mode 1 pour la période de $startDate à $endDate"
      awk  '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v startDate="$startDate" -v endDate="$endDate" -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin && $2>startDate && $2<endDate) print $1,$12}' FS=";" OFS=";" >Tmode1.csv
    else
    	echo " temperature  mode 1 sans filtre de date"
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin) print $1,$12}' FS=";" OFS=";" >Tmode1.csv
    fi
    echo "<<FIN<< génération fichier pour mode t1 "
    ;;
		"-t2" | "-t3")
    echo ">> DEBUT >> génération fichier pour mode t2 ou t3.........................."
		# on génère le fichier selon les dates pour mode 2 ou 3 de la temperature car le meme format du fichier
   #format fichier (3 colonnes): id_station;temperature;date
      if [[ ! -z "$startDate" ]]; then
		  echo " temperature  mode 2 pour la période de $startDate à $endDate"
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v startDate="$startDate" -v endDate="$endDate" -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin && $2>startDate && $2<endDate) print $1,$12,$2}' FS=";" OFS=";" >Tmode2et3.csv
      else
		  echo " temperature  mode 2 sans filtre de dates "
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin) print $1,$12,$2}' FS=";" OFS=";" >Tmode2et3.csv
      fi
    echo "<<FIN<< génération fichier pour mode t2 ou t2"
    ;;

		"-p1")
    echo ">> DEBUT >> génération fichier pour mode p1.................."
		# on génère le fichier selon les dates pour  mode 1 de la pression
   #format fichier (2 colonnes): id station;pression
    if [[ ! -z "$startDate" ]]; then
		echo " pression  mode 1 pour la période de $startDate à $endDate"
  awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v startDate="$startDate" -v endDate="$endDate" -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin && $2>startDate && $2<endDate) print $1,$7}' FS=";" OFS=";" >Pmode1.csv
  else
  	echo " pression  mode 1 pour la période de $startDate à $endDate"
    awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin) print $1,$7}' FS=";" OFS=";" >Pmode1.csv
  fi
  echo "<<FIN<< génération fichier pour mode p1 "
  ;;
  
		"-p2" | "-p3")
    echo ">> DEBUT >> génération fichier pour mode p2 ou p3...................."
		# on génère le fichier selon les dates pour mode 2 ou le mode 3 de la pression car meme format
  #format fichier (3 colonnes) : id_station;pression;date
    if [[ ! -z "$startDate" ]]; then
		  echo " temperature  mode 2 pour la période de $startDate à $endDate"
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v startDate="$startDate" -v endDate="$endDate" -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin && $2>startDate && $2<endDate) print $1,$7,$2}' FS=";" OFS=";" >Pmode2et3.csv
    else
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin) print $1,$7,$2}' FS=";" OFS=";" >Pmode2et3.csv
    fi
  echo "<<FIN<< génération fichier pour mode p2 ou p3 "
    ;;

 		"-m")
     humidite=1
     echo ">> DEBUT >> génération fichier pour humidité........................"
   # format fichier (3 colonnes): Latitude;Longitude;humidité
    if [[ ! -z "$startDate" ]]; then	
   echo " humidité pour la période de $startDate à $endDate"
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v startDate="$startDate" -v endDate="$endDate" -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin && $2>startDate && $2<endDate) print $10,$11,$6}' FS=";" OFS=";" >humidite.csv
     else 
   echo " humidité sans filtre de date................"
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin) print $10,$11,$6}' FS=";" OFS=";" >humidite.csv
     fi
  echo "<<FIN<< génération fichier pour humidité "
    ;;

    "-w")
    vent=1
      echo ">> DEBUT >> génération fichier vent................."
   	# on génère le fichier pour le vent
    # format fichier (3 colonnes): latitude;longitude;orientation_vent;vitesse_vent
    if [[ ! -z "$startDate" ]]; then	
   echo " vent pour la période de $startDate à $endDate"
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v startDate="$startDate" -v endDate="$endDate" -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin && $2>startDate && $2<endDate) print $10,$11,$4,$5}' FS=";" OFS=";" >vent.csv
     else 
   echo "vent sans filtre de date................"
      awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin) print $10,$11,$4,$5}' FS=";" OFS=";" >vent.csv
     fi
      echo "<<FIN<< génération fichier pour vent "
    ;;
    
    "-h")
    altitude=1
      echo ">> DEBUT >> génération fichier pour altitude"
    # format fichier (3 colonnes): latitude;longitude;altitude
    echo "on va traiter pour l'altitude. on s'en fiche de filtre date pour cette option .............."
    awk '{print $1,$2}' FS="," OFS=";" "$myFile" |awk -v xMax="$xMax" -v xMin="$xMin" -v yMax="$yMax" -v yMin="$yMin" '{ if($10<yMax && $10>yMin && $11<xMax && $11>xMin) print $10,$11,$15}' FS=";" OFS=";" >altitude.csv
    
    echo "<<FIN<< génération fichier pour altitude"
    ;;
    
		"*")
		echo "ERROR : autres cas non prix en compte : $myOption "
		exit 4
		;;
	esac
done
echo ""
echo "<<FIN générations des fichiers filtrés>>"
echo""
#####################################
 # appel du programme C avec les arguments qu'il faut
echo "afficher le contenu des varriables utiles pour le traitement C"
echo "mode temperature: Tmode=$Tmode" 
echo "mode pression: Pmode=$Pmode"
echo "mode de tri: tri=$tri"
echo "option vent: vent=$vent"
echo "option humidité: humidite=$humidite"
echo "option altitude: altitude=$altitude"


if [[ $Tmode == "-t1" ]]; then
  echo " temp mode 1"
  tmode1=1
  mode=7
fi
if [[ $Tmode == "-t2" ]]; then
  tmode2=1
fi
if [[ $Tmode == "-t3" ]]; then
  tmode3=1
fi
if [[ $Pmode == "-p1" ]]; then
  pmode1=1
  mode=8
fi
if [[ $Tmode == "-p2" ]]; then
  tmode=2
fi
if [[ $Tmode == "-p3" ]]; then
  tmode=3
fi
if [[ $humidite == 1 ]]; then
  humidite=1
  mode=4
fi
if [[ $altitude == 1 ]]; then
  altitude=1
  mode=5
fi
if [[ $vent == 1 ]]; then
  vent=1
fi
type_tri=1 
if [[ $tri == "--abr" ]]; then
  type_tri=2
fi
if [[ $tri == "--tab" ]]; then
  type_tri=3
fi
 

 # je t'ai pas montré pour flex mais pour que tu puisse expliquer si besoin
 # comme vous compilez tjrs les fichiers dans chacun des if
 # et que votre code va obligatoirement dans un des ifs, autant le faire
 # avant le 1e if
 # concretement, ça me permet de tester avec et sans le makefile
 # en modifiant juste les ligne 457 et 458 okkkkkk ( tu m'as dit de venir dans le read me j'y vais)

make -f MakeFile
if [ "$altitude" = "1" ] ; then
  ./tri $type_tri $mode altitude.csv
  mv fichierTrie.txt altitudeTrie.dat 
  rm altitude.csv
  bash carte_couleur.sh altitudeTrie.dat altitudeCarte
  echo altitudeCarte.png créé
fi
if [ "$vent" = "1" ] ; then
  ./tri $type_tri $mode altitude.csv
  mv fichierTrie.txt ventTrie.dat
  rm vent.csv
fi
if [ "$humidite" = "1" ] ; then
  ./tri $type_tri $mode altitude.csv
  sort -nr -k 1.1,1.3 fichierTrie.txt > humiditeTrie.dat
  rm fichierTrie.txt
  rm humidite.csv 
  bash carte_couleur.sh humiditeTrie.dat humidite
  echo humidite.png créé
fi
if [ "$tmode1" = "1" ] ; then
  ./tri $type_tri $mode Tmode1.csv
  mv fichierTrie.txt Tmode1Trie.dat
  rm Tmode1.csv
  bash error_bar.sh Tmode1Trie.dat temp_erreur_graphe
  echo temp_erreur_graphe.png créé
fi
if [ "$pmode1" = "1" ] ; then
  ./tri $type_tri $mode Pmode1.csv 
  mv fichierTrie.txt Pmode1Trie.dat 
  bash error_bar.sh Pmode1Trie.dat pression_erreur_graphe
  echo pression_erreur_graphe.png créé
  rm Pmode1.csv
fi


exit 0