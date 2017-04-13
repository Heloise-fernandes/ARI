#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.c"

char* FICHIER_HISTO_COULEUR = "../histogrammes/indexes";
char* FICHIER_LISTE_IMAGE_URL = "../Liste/urls2.txt";

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

void TriPertinence(KEY *res, int len) 
{ 
  qsort(res,len,sizeof(KEY),keyCompare); 
} 

/*--------------------------------------------------------------------*/
/*----------------------CALCUL FICHIER HISTOGRAMMES-------------------*/
/*--------------------------------------------------------------------*/
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
/*-----------------------CALCUL FICHIER DISTANCES---------------------*/
/*--------------------------------------------------------------------*/
//len correspond au nombre de fichier
//res un tableau de clé, ce tableau sera trié par odre croissant
void histogrammeDistance(char* requete, char *ficherHistogrammes, KEY *res, int size, int len) 
{
	//initialisation
	int i = 0;
	float histoReq[size];
	float histoCourant[size];
	
	for(i=0; i <size; i++) 
	{ 
		  histoReq[i]=0.0; 
		  histoCourant[i]=0.0; 
	}
	
	//charger histogramme requete : 
	printf("Le fichier reque est %s \n",requete);
	calculHistogramme(requete, histoReq);
	
	
	//Calcule distance pour tout les fichiers
	FILE* efe = fopen(ficherHistogrammes,"rb");	
    
    printf("%f",histoReq[0]);
    for(i=1;i<size;i++)
	{
		printf("- %f",histoReq[i]);
	}
	printf("\n");
	
	//Affichage
    float distanceCourante;
    int j=0;
	for(i = 0; i<len; i++)
	{
		distanceCourante = 0;
		fread(histoCourant,sizeof(histoCourant),1,efe); 
		for(j=0;j<size;j++)
		{
			distanceCourante= distanceCourante + pow(histoCourant[j]-histoReq[j],2);
		}
		res[i].d = sqrt(distanceCourante); 
		res[i].k = i; 
	}
	fclose(efe);
	
	TriPertinence(res,len);
	
	for(i=0;i<20;i++)
	{
		printf("%d / %f\n",res[i].k,res[i].d);
	}
}
