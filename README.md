This project has been created as part of the 42 curriculum by <andriamr>[, <nyrakoto>[, ]]

This project is untitled #minishell

## 📝 Description

**Minishell** est une implémentation simplifiée d'un shell UNIX, réalisée dans le cadre du cursus de l'école 42. Ce projet vise à recréer les fonctionnalités de base d'un interpréteur de commandes, similaire à bash, en langage C avec une utilisation des fonction limitees.

### Objectifs du projet

- Comprendre le fonctionnement interne d'un shell UNIX
- Maîtriser les processus et la gestion des signaux sous Linux
- Implémenter un parseur de ligne de commande robuste
- Gérer les redirections et les pipes
- Recréer des commandes internes (builtins)
- Comprendre le multitasking au niveau processus

### Vue d'ensemble

Le minishell offre une interface en ligne de commande permettant à l'utilisateur d'exécuter des programmes, de gérer des variables d'environnement, d'utiliser des redirections de fichiers et de chaîner des commandes avec des pipes. Il reproduit le comportement de bash pour les fonctionnalités implémentées.

---

## ✨ Fonctionnalités

### Commandes intégrées (Builtins)

- **`echo`** : Affiche des arguments avec option `-n` (sans retour à la ligne)
- **`cd`** : Change le répertoire courant (avec chemins relatifs et absolus)
- **`pwd`** : Affiche le chemin du répertoire courant
- **`export`** : Définit des variables d'environnement
- **`unset`** : Supprime des variables d'environnement
- **`env`** : Affiche les variables d'environnement
- **`exit`** : Quitte le shell avec un code de retour optionnel

### Fonctionnalités avancées

- **Gestion des quotes** : Simple quotes `'` et double quotes `"`
- **Expansion de variables** : `$VAR` et `$?` (code de retour)
- **Redirections** :
  - `<` : Redirection d'entrée
  - `>` : Redirection de sortie (écrasement)
  - `>>` : Redirection de sortie (ajout)
  - `<<` : Here-document
- **Pipes** : Chaînage de commandes avec `|`
- **Gestion des signaux** :
  - `Ctrl-C` : Affiche un nouveau prompt
  - `Ctrl-D` : Quitte le shell
  - `Ctrl-\` : Ignoré
- **Historique des commandes** : Navigation avec les flèches haut/bas
- **Gestion des erreurs** : Messages d'erreur appropriés et codes de retour

---

## 🛠️ Instructions

### Prérequis

- **Système d'exploitation** : Linux
- **Compilateur** : GCC, CC ou CLANG avec support C99 ou supérieur
- **Bibliothèques** :
  - `readline` (GNU Readline Library)
  - `ncurses`

### Compilation

Pour compiler le projet, utilisez simplement le Makefile fourni :

```bash
make
```

Cela générera l'exécutable `minishell` à la racine du projet.

### Nettoyage

```bash
# Supprime les fichiers objets
make clean

# Supprime les fichiers objets et l'exécutable
make fclean

# Recompile complètement le projet
make re
```

### Exécution

Pour lancer le minishell :

```bash
./minishell
```

Vous verrez alors apparaître le prompt :

```
minishell$
```

### Exemples d'utilisation

```bash
# Commande simple
minishell$ echo "Hello World"
Hello World

# Expansion de variables
minishell$ export NAME=John
minishell$ echo "Hello $NAME"
Hello John

# Code de retour
minishell$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2

# Pipes
minishell$ ls -l | grep minishell | wc -l
1

# Redirections
minishell$ echo "Test" > output.txt
minishell$ cat < output.txt
Test
minishell$ echo "Line 2" >> output.txt
minishell$ cat output.txt
Test
Line 2

# Here-document
minishell$ cat << EOF
> Hello
> World
> EOF
Hello
World

# Commandes chainées
minishell$ echo "First" | cat -e | cat -e
First$

# Changement de répertoire
minishell$ cd /tmp
minishell$ pwd
/tmp
minishell$ cd -
minishell$ pwd
/home/user

# Quitter le shell
minishell$ exit 42
```

## 📚 Resources

### Documentation officielle

- Peer to peer learning
- [Linux Man Pages] - On UNIX terminal
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/) - Documentation complète du shell bash
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) - Standard POSIX pour les shells
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) - Documentation de la bibliothèque readline
 ...

---

## 🤖 Utilisation de l'IA
- Pour mieux comprendre les demarches et pour faire le conception du projet afin de n'est pas commencer sur n'importe quoi
- Pour tester la robustesse
- Aider pour bien comprendre l'utilisation des fonctions autorises et les differencies
- Dans le cadre de ce projet, l'IA (GitHub Copilot) a été utilisée comme outil d'assistance au conception de projet pour le rendre plus a realiser
- Génération de ce fichier README.md
- Structuration et formatage de la documentation
- Suggestions d'exemples d'utilisation


### Parties développées sans IA

- **Architecture globale du projet** : Conception des structures de données et de l'organisation modulaire
- **Implémentation du parseur** : Tokenisation, gestion des quotes, expansion des variables
- **Logique métier des builtins** : Implémentation de `cd`, `echo`, `export`, `unset`, etc.
- **Gestion des processus** : Fork, exec, pipes, redirections
- **Gestion des signaux** : Handlers SIGINT, SIGQUIT pour les différents contextes
- **Gestion de la mémoire** : Allocation/libération et prévention des fuites mémoire

---

## 🏗️ Structure du projet

```
minishell/
├── Makefile              # Fichier de compilation
├── README.md             # Ce fichier
├── include/
│   └── minishell.h       # Header principal avec structures et prototypes
├── LIBFT/                # Bibliothèque libft (fonctions utilitaires)
│   ├── ft_*.c
│   ├── libft.h
│   └── Makefile
└── src/
    ├── builtins/         # Commandes intégrées
    │   ├── cd.c
    │   ├── echo.c
    │   ├── env.c
    │   ├── exit.c
    │   ├── export.c
    │   ├── pwd.c
    │   ├── unset.c
    │   └── check_builtins.c
    ├── execution/        # Exécution des commandes
    │   ├── main.c
    │   ├── cmd_line.c
    │   ├── execution.c
    │   ├── pipe.c
    │   ├── pipeline.c
    │   ├── pipeline_utils.c
    │   ├── redirection.c
    │   └── signal.c
    └── parsing/          # Analyse et traitement des entrées
        ├── tokenisation.c
        ├── split_token.c
        ├── ft_expander.c
        ├── expander_utils.c
        ├── ft_quote.c
        ├── checker_pipe.c
        ├── split_by_pipe.c
        ├── add_cmd.c
        ├── put_cmd.c
        ├── list_pars.c
        ├── pars_utils.c
        ├── token_utils.c
        ├── split_utils.c
        ├── struct_init.c
        ├── ft_list_str.c
        └── ft_exit.c
```

---

## 🔧 Choix techniques

### Architecture modulaire

Le projet est organisé en deux modules principaux :

1. **Parsing** : Analyse lexicale et syntaxique de la ligne de commande
2. **Execution** : Gestion des processus, pipes et redirections, builtins

Cette séparation facilite la maintenance et permet une meilleure testabilité.

### Gestion de la mémoire

- Utilisation systématique de `valgrind` pour détecter les fuites
- Fonctions de libération dédiées pour chaque structure
- Gestion rigoureuse des allocations lors de l'expansion de variables

### Parsing

- Separation par pipe
- Tokenisation en deux passes : détection des séparateurs puis extraction
- Gestion des quotes en maintenant un état (in_quote, in_dquote)
- Expansion des variables lors du parsing pour les double quotes

---

## 🙏 Remerciements

- L'équipe de l'ecole 42
- L'équipe pédagogique de 42 Antananarivo
- La communauté 42 pour les ressources partagées

---

*Projet réalisé en janvier 2026 - 42 Antananarivo*
