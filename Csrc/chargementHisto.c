#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.h"
#ifndef CONST_H
#define CONST_H
#include "const.h"
#endif
/*--------------------------------------------------------------------*/
/*----------------CALCUL FICHIER HISTOGRAMMES COULEUR-----------------*/
/*--------------------------------------------------------------------*/
void calculHistogramme(char* nom, float* histo){
  int i,j;
  CIMAGE cim;
  
  //Lecture image à traiter
  printf("Image %s \n", nom);
  read_cimage(nom,&cim);
  
  //On initialise l'histogramme à 0
  for(i=0; i <64; i++){histo[i]=0.0;}
  
  //On fait passer le nombre de valeur possible de 256 à 4
  for (j = 0; j < cim.ny; j++) {       
    for (i = 0; i < cim.nx; i++) {   
      cim.r[i][j]=cim.r[i][j]*4/256;
      cim.g[i][j]=cim.g[i][j]*4/256;
      cim.b[i][j]=cim.b[i][j]*4/256;
    }
  }
  
  //On incrémente les couleurs dans notre tableau
  int k = 0;
  for (j = 0; j < cim.ny; j++) {       
    for (i = 0; i < cim.nx; i++) {  	 
	  k = cim.r[i][j]+cim.g[i][j]*4+cim.b[i][j]*16;
      histo[k]++;
    }
  }
  
  //On normalise les valeurs
  float t = cim.ny*cim.nx;
  for(i=0;i<64;i++){
	  float f = histo[i]/t;
	  histo[i] = f;
	  //printf("%f - ",histo[i]);
	  
  }
  //printf("\n");
  free_cimage(nom,&cim);
  
  return;
}

void creationFichierHistogrammeCouleur()
{
  float monHisto[64];
  int len;
  int indexFichier;
  
  //Liste de l'ensemble des fichiers
  char **liste = readList(FICHIER_LISTE_IMAGE_URL, &len);
  
  //Fichier qui contient contiendra l'index
  FILE* efe = fopen(FICHIER_HISTO_COULEUR,"wb+");
  
  //Pour chaque fichier on : 
  for(indexFichier = 0; indexFichier<len; indexFichier++)
  {
	//calcul son histogramme
	calculHistogramme(liste[indexFichier], monHisto);  
	//Ecrit le tableau dans un fichier
	fwrite(monHisto,sizeof(float),64,efe);
  }
  
  //on ferme le fichier
  fclose(efe);
  freeList(liste,len); 
}


/*--------------------------------------------------------------------*/
/*-----------------CALCUL FICHIER HISTOGRAMMES CLUSTER----------------*/
/*--------------------------------------------------------------------*/
void unhistoDeClasse(char *file, int taille, float* monHisto)
{
	//printf("%s\n",file);
	int indice =0;
	int tailleMAXLu = 5;
	char chaine[tailleMAXLu];
	
	for(indice=0; indice <taille; indice++)
	{
		monHisto[indice]=0.0;
	}
	
	FILE* f = fopen(file,"r");
	int t=0;
	if(f)
	{
		while (fgets(chaine, tailleMAXLu, f) != NULL)
		{
			indice = atoi(chaine);
			monHisto[indice]++;
			t++;
		}
		for(indice=0; indice <taille; indice++)
		{
			monHisto[indice]=monHisto[indice]/t;
		}
	}
	fclose(f);
}

void calculHistogrammeDeClasse(int taille)
{

  float monHisto[taille];
  int len;
  int indexFichier;
  char **liste = readList(FICHIER_LISTE_CLUSTER_URL, &len);
  //Fichier qui contient contiendra l'index
  FILE* efe = fopen(FICHIER_HISTO_CLUSTER,"wb+");
  //Pour chaque fichier on : 
  for(indexFichier = 0; indexFichier<len; indexFichier++)
  {
	  
	unhistoDeClasse(liste[indexFichier],taille,monHisto);
	//for(indice = 0; indice<taille; indice++)
	//{
	//	printf("%f - ", monHisto[indice]);
	//}
	//printf("\n\n");
	fwrite(monHisto,sizeof(float),taille,efe);
  }
  //on ferme le fichier
  fclose(efe);
  freeList(liste,len); 
}
