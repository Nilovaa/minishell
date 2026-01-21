# Minishell

![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black)

## 📝 Description

**Minishell** est une implémentation simplifiée d'un shell UNIX, réalisée dans le cadre du cursus de l'école 42. Ce projet vise à recréer les fonctionnalités de base d'un interpréteur de commandes, similaire à bash ou zsh, en langage C.

### Objectifs du projet

- Comprendre le fonctionnement interne d'un shell UNIX
- Maîtriser les processus et la gestion des signaux sous Linux
- Implémenter un parseur de ligne de commande robuste
- Gérer les redirections et les pipes
- Créer des commandes internes (builtins)

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

- **Système d'exploitation** : Linux ou macOS
- **Compilateur** : GCC avec support C99 ou supérieur
- **Bibliothèques** :
  - `readline` (GNU Readline Library)
  - `ncurses`

#### Installation des dépendances (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install libreadline-dev libncurses5-dev
```

#### Installation des dépendances (macOS)

```bash
brew install readline ncurses
```

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

### Tests avec Valgrind

Pour vérifier les fuites mémoire :

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
         --suppressions=rl.supp ./minishell
```

Note : Le fichier `rl.supp` contient les suppressions pour les fuites connues de la bibliothèque readline.

---

## 📚 Resources

### Documentation officielle

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/) - Documentation complète du shell bash
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) - Standard POSIX pour les shells
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) - Documentation de la bibliothèque readline
- [Linux Man Pages](https://man7.org/linux/man-pages/) - Pages de manuel Linux

### Gestion des processus et signaux

- [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html) - Création de processus
- [execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html) - Exécution de programmes
- [wait(2)](https://man7.org/linux/man-pages/man2/wait.2.html) - Attente de processus fils
- [pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html) - Création de pipes
- [dup2(2)](https://man7.org/linux/man-pages/man2/dup2.2.html) - Duplication de descripteurs de fichiers
- [signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html) - Vue d'ensemble des signaux
- [sigaction(2)](https://man7.org/linux/man-pages/man2/sigaction.2.html) - Gestion avancée des signaux

### Articles et tutoriels

- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) - Guide complet sur la création d'un shell
- [Building a Shell - Part 1](https://brennan.io/2015/01/16/write-a-shell-in-c/) - Tutoriel pratique en C
- [Unix Pipes Implementation](https://toroid.org/unix-pipe-implementation) - Comprendre les pipes UNIX
- [Understanding Environment Variables](https://www.digitalocean.com/community/tutorials/how-to-read-and-set-environmental-and-shell-variables-on-linux) - Guide sur les variables d'environnement

### Ressources 42

- [42 Docs - Minishell](https://harm-smits.github.io/42docs/projects/minishell) - Documentation communautaire
- [Shell Basics](https://github.com/jotavare/42-resources#minishell) - Ressources compilées par la communauté 42

---

## 🤖 Utilisation de l'IA

### Contexte et approche

Dans le cadre de ce projet, l'IA (GitHub Copilot) a été utilisée comme outil d'assistance au développement, tout en respectant les règles pédagogiques de l'école 42.

### Tâches assistées par l'IA

1. **Refactoring et optimisation du code** :
   - Encapsulation de la variable globale `g_signal_received` dans le module `signal.c`
   - Création de fonctions getter/setter (`ft_get_signal_received()`, `ft_reset_signal_received()`)
   - Modification du code existant pour utiliser les nouvelles fonctions d'accès

2. **Débogage et validation** :
   - Vérification de la compilation après modifications
   - Tests de régression pour s'assurer que le comportement reste identique
   - Validation des codes de retour avec `echo $?`

3. **Documentation** :
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

### Méthodologie

L'IA a été utilisée principalement pour :
- Accélérer les tâches répétitives et le refactoring
- Obtenir des suggestions de bonnes pratiques en C
- Générer rapidement de la documentation structurée
- Valider la logique et détecter des erreurs potentielles

Toute suggestion de l'IA a été **relue, comprise et validée** avant intégration, garantissant ainsi une maîtrise complète du code produit.

---

## 🏗️ Structure du projet

```
minishell/
├── Makefile              # Fichier de compilation
├── README.md             # Ce fichier
├── rl.supp               # Suppressions Valgrind pour readline
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

Le projet est organisé en trois modules principaux :

1. **Parsing** : Analyse lexicale et syntaxique de la ligne de commande
2. **Execution** : Gestion des processus, pipes et redirections
3. **Builtins** : Implémentation des commandes intégrées

Cette séparation facilite la maintenance et permet une meilleure testabilité.

### Gestion de la mémoire

- Utilisation systématique de `valgrind` pour détecter les fuites
- Fonctions de libération dédiées pour chaque structure
- Gestion rigoureuse des allocations lors de l'expansion de variables

### Gestion des signaux

- Utilisation de `sigaction()` plutôt que `signal()` pour plus de contrôle
- Contextes différenciés : mode interactif, processus fils, heredoc
- Variable globale encapsulée pour respecter les bonnes pratiques

### Parsing

- Tokenisation en deux passes : détection des séparateurs puis extraction
- Gestion des quotes en maintenant un état (in_quote, in_dquote)
- Expansion des variables lors du parsing pour les double quotes

---

## 👥 Auteurs

- **andriamr** - [@andriamr](https://github.com/andriamr)
- **nyrakoto** - [@Nilovaa](https://github.com/Nilovaa)

---

## 📄 Licence

Ce projet est réalisé dans le cadre du cursus de l'école 42. Le code est libre d'utilisation à des fins éducatives.

---

## 🙏 Remerciements

- L'équipe pédagogique de 42 Antananarivo
- La communauté 42 pour les ressources partagées
- Les créateurs des outils open source utilisés (readline, ncurses)

---

*Projet réalisé en janvier 2026 - 42 Antananarivo*
