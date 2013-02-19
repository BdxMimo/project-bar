CONVENTIONS DE DEVELOPPEMENT DU PROJET BOITE A RYTHMES :

- Les classes cr��es par nous-m�mes commenceront par BAR et seront �crites en "camel case". Exemple : BARCompletelyUselessTab.
- Les variables et fonctions seront aussi �crites en camel case et commenceront par une minuscule. Exemple : int uselessVariable.
- Le nom des classes, des variables, les commentaires et la documentation seront �crites en anglais.
- Ne jamais utiliser de noms pas �vidents pour les variables ou les fonctions. Exemple : pr�f�rer "nbSongs" � "n".
- Seule exception au point pr�c�dent : les variables de boucle qui sont assimilables � des indices (donc "i","j","k") et les it�rateurs (qu'on peut nommer "it")
- Commenter le code au fur et � mesure. Utilisez d'ores et d�j�, pour les classes et leurs attributs et m�thodes, la syntaxe de doxygen (http://www.stack.nl/~dimitri/doxygen/manual/commands.html) que je mettrai de toute fa�on en place. De pr�f�rence en anglais histoire d'internationaliser le projet.

BONNES PRATIQUES RELATIVES A GIT :

- Faites des commits souvent !
- Avant chaque commit, faites un pull (on sait jamais, d'autres membres ont peut-�tre fait un commit avant vous !)
- Faites des commits / push souvent, mais il ne faut pas qu'il y ait de bug ou de code incomplet !
- Mettez un message de commit clair et compr�hensible � chaque fois.

UTILISATION DE DOXYGEN :

- T�l�chargez et installez Doxygen : http://www.stack.nl/~dimitri/doxygen/download.html
- Sous Qt Creator, ouvrez le projet puis cliquez sur l'onglet "Projets" (� gauche)
- Dans les �tapes de compilation, cliquez sur "Ajouter l'�tape Compiler" puis s�lectionnez "Etape personnalis�e"
- Remplir les trois champs : Commande : doxygen, Arguments : doxygen_config, R�pertoire de travail : %{sourceDir}