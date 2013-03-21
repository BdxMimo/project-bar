CONVENTIONS DE DEVELOPPEMENT DU PROJET BOITE A RYTHMES :

- Les classes créées par nous-mêmes commenceront par BAR et seront écrites en "camel case". Exemple : BARCompletelyUselessTab.
- Les variables et fonctions seront aussi écrites en camel case et commenceront par une minuscule. Exemple : int uselessVariable.
- Le nom des classes, des variables, les commentaires et la documentation seront écrites en anglais.
- Ne jamais utiliser de noms pas évidents pour les variables ou les fonctions. Exemple : préférer "nbSongs" à "n".
- Seule exception au point précédent : les variables de boucle qui sont assimilables à des indices (donc "i","j","k") et les itérateurs (qu'on peut nommer "it")
- Commenter le code au fur et à mesure. Utilisez d'ores et déjà, pour les classes et leurs attributs et méthodes, la syntaxe de doxygen (http://www.stack.nl/~dimitri/doxygen/manual/commands.html) que je mettrai de toute façon en place. De préférence en anglais histoire d'internationaliser le projet.

BONNES PRATIQUES RELATIVES A GIT :

- Faites des commits souvent !
- Avant chaque commit, faites un pull (on sait jamais, d'autres membres ont peut-être fait un commit avant vous !)
- Faites des commits / push souvent, mais il ne faut pas qu'il y ait de bug ou de code incomplet !
- Mettez un message de commit clair et compréhensible à chaque fois.

UTILISATION DE DOXYGEN :

- Téléchargez et installez Doxygen : http://www.stack.nl/~dimitri/doxygen/download.html
- Sous Qt Creator, ouvrez le projet puis cliquez sur l'onglet "Projets" (à gauche)
- Dans les étapes de compilation, cliquez sur "Ajouter l'étape Compiler" puis sélectionnez "Etape personnalisée"
- Remplir les trois champs : Commande : doxygen, Arguments : doxygen_config, Répertoire de travail : %{sourceDir}