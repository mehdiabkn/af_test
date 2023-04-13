

<h1>Test case CPOO “Flights” </h1>


Messieurs Ponchon et Amrane, 

Je vous transmets avec mon travail un court compte rendu reprenant mes observations et questionnements. 
J’ai documenté et organisé le code de sorte à ce qu’il soit rapide à comprendre et j’ai fait un main reprenant chacune des questions. 
Cette documentation sera également dans le Readme.md du repository github.

<h2> Conception, UML </h2>

D’abord, une passe rapide sur la conception pour simplement évoquer la relation d’agrégation entre la classe o&d et la classe Flight Nbr. 
La vie de l’objet O&D ne dépend pas de la vie de l’objet FlightNbr, autrement la nature de la relation serait une composition.





<img src="https://github.com/mehdiabkn/af_test/blob/main/conception.PNG">
Image 1 : Relation d’agrégation entre les deux classes du test case (Diagramme UML)




<h2>  Observations </h2>


J’ai trouvé le test assez clair et je pense avoir totalement traité chacune des questions.
Je me suis quand même rendu compte d’une petite subtilité que j’aimerais relever quand au choix d’une structure de données.
L'utilisation d’un set<long> dans le cadre d’une liste de tarifs sur laquelle appliquer des statistiques me paraît concéder une petite limite quant aux cas où un tarif est très redondant. 
En effet, toutes les valeurs d’un set doivent être uniques et si on cherche à ajouter une valeur déjà existante dans le set, elle sera ignorée.

Imaginons un cas pour mesurer le problème : 

Admettons qu’il existe dix vols reliant CDG à JFK. 
Neuf de ces vols ont un tarif de 1000€ (contexte classique). Le dixième a un tarif qui s’élève à 5000€ (contexte exceptionnel). 
Dans la configuration actuelle, nous aurons un tarif moyen noté avgtarif de 3000€ alors que l’on constate bien que la moyenne doit être bien moins élevée (1400€). 

Aussi, le type long semble ne pas convenir car il y a des valeurs décimales dans le fichier csv contenant les o&d et tarifs. Float ou double serait peut-être plus adapté?
  <h2> Approfondir </h2>

On pourrait imaginer aller plus loin dans ce use case et concevoir une UI pour ce logiciel, de le connecter à une base de données et des pipelines pour alimenter en continu la base de données de tarifs ainsi qu’un serveur (ex: Jenkins) permettant d’exécuter le code de manière régulière (une fois par jour / par semaine).
