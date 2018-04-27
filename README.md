# Projet FaroShell

## Objectifs

Ce projet a pour but de créer un mini shell en langage C dans lequel les commandes suivantes seront possibles à utilisées :

- cd     ✓
- mkdir  ✓  (Options disponibles : -m)
- ls     ✓  (Options disponibles : -a -c -h -l)
- cat    ✓  (Options disponibles : -A -E -n -T)
- mv     ✓  (Options disponibles : -i -v)
- cp     ✓  (sans options)
- rm     ✓  (Options disponibles : -r -f)
- du     ✓  (Options disponibles : -a -c -h)
- chmod  ✓  
- chgrp  ✓
- echo   ✓  (Options disponibles : -n -e)
- su     ✓

## L'équipe

Simon Bessenay, Guillaume Potier, Arthur Millet, Sébastien Berlioux, Bastien Jean

## Installation et utilisation du programme

Téléchargez la dernière version, et à partir du dossier racine lancez dans un terminal :

    make && ./faroShell

Les exécutables de chaque commande sont situés dans le répertoire bin/cmd.
Pour les exécuter, faites dans un terminal :

    cd bin/cmd
    ./nomExecutable [arguments]

## Organisation du code

Le répertoire principal comporte le Makefile et le README ainsi qu'un dossiers src qui contient le code source du projet. Celui-ci contient 3 dossiers :
- cmd : contient les dossiers avec les fichiers de code de chaque commandes exécutables dans le shell
- interpreter : contient les fichiers de code nécessaires à l'interpréteur
- utils : contient les fichiers de code des fonctions utiles a tout le projet

A la compilation du projet, 2 dossiers sont créés à la racine du projet :
- obj : contient les fichiers objets générés à la compilation
- bin : contient les fichiers binaires c'est-à-dire les exécutables et les libraires statiques et dynamiques


## La répartition du travail

Groupe interpréteur | Groupe commandes
:-: | :-:
Simon & Bastien | Arthur, Sébastien & Guillaume
