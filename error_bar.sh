#!/bin/bash
# nom du fichier de données
fichier_donnee=$1
nom_graph=$2

# nom du fichier gnuplot
fichier_plot="graphe_erreur.gp"

# créer le fichier gnuplot
cat > $fichier_plot << EOL
set term png
set output "$nom_graph.png"
set style data yerrorbars
set datafile separator ";"
set xlabel "Identifiant de la station"
set ylabel "Valeur"
set title "Diagramme d'erreur"
plot "$fichier_donnee" using 1:3:4 with filledcurve fc rgb "#80E0A080" title "Valeurs possible", '' using 1:2 smooth mcspline lw 2 title "Moyenne"
EOL

# exécuter gnuplot pour générer le diagramme
gnuplot $fichier_plot

# supprime le fichier gnuplot
rm $fichier_plot