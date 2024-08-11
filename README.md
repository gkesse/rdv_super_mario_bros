# Introduction

Bienvenue dans ce tutoriel consacré à la présentation du processus de création d'un Jeu de Super Mario Bro en C++ avec Qt 6 sous Windows.
Nous utiliserons la bibliothèque de création d'interfaces homme machine Qt en C++ sous Windows.
Nous utiliserons le compilateur (MinGW) pour compiler notre projet Qt.
Qt fournit un environnement de développement intégré (Qt Creator)
et un designer d'interfaces graphiques (Qt Designer), un assistant d'aide (Qt Assistant)
et un moyen d'internationalisation de nos projets vers toutes les langues de notre choix (Qt Translation).
Nous sommes libres d'utiliser un éditeur de notre choix (Eclipse, VS Code ou Microsoft Visual Studio)
pour éditer nos fichiers sources puis passer en ligne de commande pour construire,
compiler et déboguer notre projet Qt, d'ailleurs, c'est cette solution que nous utiliserons
dans notre projet pour plus de flexibilité, même si Qt fournit tout l'écosystème pour faire bien plus
de choses que ça. Nous utiliserons le fichier projet (*.pro) pour construire notre projet Qt.
Tout le long du développement, nous nous efforcerons à respecter les bonnes pratiques en ingénierie
logiciel. Nous veillerons à respecter les principes SOLID pour faciliter la compréhension du code ainsi
que sa maintenance et son évolution, les principes RAII pour faciliter la gestion de nos ressources
en considérant l'acquisition d'une ressource comme une initialisation afin d'éviter les fuites de
mémoire et profiter pleinement du destructeur automatique de classe lorsqu'un objet sort de sa portée,
les principes DRY pour éviter la duplication de base de code et nous nous interdirons de créer des
objets incomplets.

# Lien

Le tutoriel est disponible sur ce lien:  
[Accédez au tutoriel](https://readydev.ovh/home/tutoriels/cpp/application/super_mario_bros)