
# Jeu des carrés : Immersion groupe 6

## Description :

Le "Jeu des Carrés" est un projet étudiant en C développé pour une machine Linux (Debian 12). . 
Le projet inclut la gestion du jeu, des tests unitaires avec un aperçu graphique, et la génération de documentation. La compilation et la gestion des tâches se font via plusieurs Makefiles.



## Prérequis

Avant de commencer, assurez-vous que votre machine répond aux prérequis suivants :

OS : Linux (Debian 12 ou équivalent)

Compilateur C : gcc

Outils nécessaires :
   * make pour la gestion des Makefiles.
   * doxygen pour la génération de documentation
   * lcov pour la génération de rapport de tests

## Structure du projet

``` src/ ``` : Contient le code source du jeu (.c et .h)

``` build/ ``` : Contient les fichiers exécutables générés après compilation

``` tests/ ``` : Contient les fichiers de test unitaire + le fichiers Lcov

``` docs/ ``` : Contient la documentation générée par Doxygen.

``` Makefile ``` : Fichier principal pour la gestion des tâches de compilation.
## Installation

Installer le projet

```bash
  svn checkout 	https://svn.ensisa.uha.fr/scm/svn/imm2425-gr6
  cd imm2425-gr6
```
    
## Compilation

Compiler tout le projet : le jeu avec les tests et la documentation

```bash
  make all
```

Compiler uniquement les tests

```bash
  make tests
```

Compiler uniquement la documentation

```bash
  make docs
```
La documentation sera générée dans le répertoire docs/

Supprimer les fichiers ajoutés

```bash
  make clean
```

## Utilisation

Lancement en local, deux adversaires sur le même exécutable

``` bash
./game -l
```

Lancements en réseau mode manuel

``` bash
./game -s 5555
./game -c 127.0.0.1:5555
```

Lancements en réseau mode ia

``` bash
./game -s -ia 5555
./game -c -ia 127.0.0.1:5555
```