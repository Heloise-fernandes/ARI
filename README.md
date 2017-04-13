# ARI

Les fichiers générés sont stockés dans histogrammes

## Partie 1 : comparaison de couleur 

**Compilation :** 
```
	make
```
**Utilisation :** 
```
	histo 1
	histo nom_image_requête
```
**Résultat :** 
```
	./histogrammes/final1.html
```

## Partie  2 : Comparaison des formes

### Partie filtrage des descripteur :

**Commande :** 
```
	./filtrage
```
**Resultat:**
```
	../histogrammes/sample.txt
```

### Partie clustering

**Commande :** 
```
	./clusterring
```
**Resultat:**
```
	../histogrammes/centers256.txt
```

### Partie mapping

taskset -c 1,2,3,4 ./process_1nn_sift.sh


Pour réaliser un descripteur pour une image et la mapper lancer la commande suivante:

./descripteur nom_image

**Commande :** 
```
	../script/process_1nn_sift.sh 
```
**Resultat:**
```
	../histogrammes/centers256.txt
```

### Partie affichage des résultats

```
	histo 2
	histo nom_image_requête nom_sift_image_requete
```

## Partie  3 : Combiner

```
	histo nom_image_requête nom_sift_image_requete
```
	
### Exemple lancement

```
./histo ./rouge.jpg ./rouge.sift 
./histo ./images/2008_000001.jpg ./mapping/2008_000001.sift 
./histo ./chien-de-montagne-des-pyrenees.jpg ./chien-de-montagne-des-pyrenees.sif 

```