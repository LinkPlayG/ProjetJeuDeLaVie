# Projet Jeu De La Vie
Ceci est un projet basé sur le jeu de la vie de Conway.
Il a été réalisé en C++20 sur un environnement Linux.

## Dépendances
Pour pouvoir l'utiliser, il est nécessaire d'installer g++ sur votre environnement linux :
```
sudo apt-get install g++
```
Et aussi la bibliothèque sfml, pour l'affichage graphique :
```
sudo apt-get install libsfml-dev
```

## Lancement du jeu
### Invite de commandes linux
Pour compiler le jeu, placez vous dans l'invite de commandes linux et tapez ceci :
```
make main
```
Cela créera l'éxécutable permettant de lancer le programme.
Vous pourrez ensuite lancer l'éxécutable et suivre les instructions.
```
./main
```

### Clion
Le Jeu est configuré pour fonctionner automatiquement avec Clion lors du clônage. Cependant, il se peut que vous ayez une configuration de fichiers différente, c'est pourquoi le fichier Makefile est positionné dans le dossier source du projet. 
En cas de problème, quittez Clion supprimez le dossier **.idea** si il existe et réouvez le dossier qui contient le projet. 

Pour plus d'informations de compatibilié, voir la documentation de Clion sur le sujet :
[Documentation Makefile](https://www.jetbrains.com/help/clion/makefiles-support.html)

## Remerciement
Merci à mon collaborateur [@Moyakeko](https://github.com/Moyakeko) dont la participation à été de 100 % pour ce projet.
