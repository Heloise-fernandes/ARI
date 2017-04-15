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
	printf("Le fichier requete est %s \n",requete);
	if(type == 2){unhistoDeClasse(requete,256, histoReq);}
	else{calculHistogramme(requete, histoReq);}
	
	
	//Calcule distance pour tout les fichiers
	FILE* efe = fopen(ficherHistogrammes,"rb");	
    
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
    
    TriPertinence(distance,len);
    
    printf("ETAPE AFFICHAGE :%s\n",req); 
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
    
    	TriPertinence(distance,len); 
     
    	printf("ETAPE AFFICHAGE :\n"); 
    	AfficherResultatHTMLCLUSTER(distance,len,FICHIER_LISTE_IMAGE_URL,reqImages,"./final2.html"); 
    	printf("\n\n"); 

}

void calculPertinenceMoy(char * reqImages, char* reqSIFT)
{
	int len; 
    	char **liste = readList(FICHIER_LISTE_CLUSTER_URL, &len); 
    	freeList(liste,len); 
   
    	printf("TRI :\n"); 
    	KEY distanceColor[len]; 
    	KEY distanceCluster[len]; 
    	KEY distance[len]; 
    	histogrammeDistance(reqImages, FICHIER_HISTO_COULEUR, distanceColor, 64, len,1); 
    	histogrammeDistance(reqSIFT, FICHIER_HISTO_CLUSTER, distanceCluster, 256, len,2); 
    	printf("\n\n"); 
    
    	int i =0;
    	for(i=0; i < len; i++)
    	{
		distance[i].k = distanceColor[i].k;
		distance[i].d = (distanceColor[i].d+distanceCluster[i].d)/2;
	}
    	TriPertinence(distance,len); 
    
    	printf("ETAPE AFFICHAGE :\n"); 
    	AfficherResultatHTMLCLUSTER(distance,len,FICHIER_LISTE_IMAGE_URL,reqImages,"./final3.html"); 
    	printf("\n\n"); 
}

float min(float a, float b)
{
	if(a<b){return a;}
	return b;
}

void calculPertinenceMin(char * reqImages, char* reqSIFT)
{
	int len; 
    	char **liste = readList(FICHIER_LISTE_CLUSTER_URL, &len); 
    	freeList(liste,len); 
   
    	printf("TRI :\n"); 
    	KEY distanceColor[len]; 
    	KEY distanceCluster[len]; 
    	KEY distance[len]; 
    	histogrammeDistance(reqImages, FICHIER_HISTO_COULEUR, distanceColor, 64, len,1); 
    	histogrammeDistance(reqSIFT, FICHIER_HISTO_CLUSTER, distanceCluster, 256, len,2); 
    	printf("\n\n"); 
    
    	int i =0;
    	for(i=0; i < len; i++)
    	{
		distance[i].k = distanceColor[i].k;
		distance[i].d = min(distanceColor[i].d,distanceCluster[i].d);
	}
    	TriPertinence(distance,len); 
    
    	printf("ETAPE AFFICHAGE :\n"); 
    	AfficherResultatHTMLCLUSTER(distance,len,FICHIER_LISTE_IMAGE_URL,reqImages,"./final4.html"); 
    	printf("\n\n"); 
}
