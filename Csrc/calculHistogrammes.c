#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.h"
#include "chargementHisto.h"
#include "affichage.h"

#ifndef CONST_H
#define CONST_H
#include "const.h"
#endif

/*--------------------------------------------------------------------*/
/*-----------------------CALCUL FICHIER DISTANCES---------------------*/
/*--------------------------------------------------------------------*/
//len correspond au nombre de fichier
//res un tableau de clé, ce tableau sera trié par odre croissant
void TriPertinence(KEY *res, int len) 
{ 
  qsort(res,len,sizeof(KEY),keyCompare); 
} 

void histogrammeDistance(char* requete, char *ficherHistogrammes, KEY *res, int size, int len, int type) 
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
	if(type == 2){unhistoDeClasse(requete,256, histoReq);}
	else{calculHistogramme(requete, histoReq);}
	
	
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

/*--------------------------------------------------------------------*/
/*--------------CALCUL FICHIER HISTOGRAMMES PERTINENCE----------------*/
/*--------------------------------------------------------------------*/
void calculPertinenceCouleur(char * req)
{
	int len; 
    char **liste = readList(FICHIER_LISTE_IMAGE_URL, &len); 
    freeList(liste,len); 
   
    printf("TRI :\n"); 
    KEY distance[len]; 
    histogrammeDistance(req, FICHIER_HISTO_COULEUR, distance, 64, len,1); 
    printf("\n\n"); 
     
    printf("ETAPE AFFICHAGE :%s, %d , %s\n",req,len,FICHIER_LISTE_IMAGE_URL); 
    AfficherResultatHTMLCOULEUR(distance,len,FICHIER_LISTE_IMAGE_URL,req,"./final1.html"); 
    printf("\n\n"); 

}

void calculPertinenceForme(char * reqImages, char* reqSIFT)
{
	int len; 
    char **liste = readList(FICHIER_LISTE_CLUSTER_URL, &len); 
    freeList(liste,len); 
   
    printf("TRI :\n"); 
    KEY distance[len]; 
    histogrammeDistance(reqSIFT, FICHIER_HISTO_CLUSTER, distance, 256, len,2); 
    printf("\n\n"); 
     
    printf("ETAPE AFFICHAGE :\n"); 
    AfficherResultatHTMLCLUSTER(distance,len,FICHIER_LISTE_IMAGE_URL,reqImages,"./final2.html"); 
    printf("\n\n"); 

}
