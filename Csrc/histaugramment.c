#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#ifndef RDJPEG_H
#define RDJPEG_H
#include "rdjpeg.h"
#include "proc.h"
#endif

#include "calculHistogrammes.h"
#include "affichage.h"

void calculPertinenceCouleur(char * req)
{
	int len; 
    char **liste = readList("../Liste/urls2.txt", &len); 
    freeList(liste,len); 
   
    printf("TRI :\n"); 
    KEY distance[len]; 
    histogrammeDistance(req, "../histogrammes/indexes", distance, 64, len); 
    printf("\n\n"); 
     
    printf("ETAPE AFFICHAGE :\n"); 
    AfficherResultatHTML(distance,len,"../Liste/urls2.txt",req,"../histogrammes/final1.html"); 
    printf("\n\n"); 

}



/*
void chargement(char *url) 
{
  printf("ETAPE 1 :\n"); 
  //float monHisto[64]; 
  //int i =0; 
  //calculHistogramme("./images/2008_000001.jpg", monHisto); 
  printf("\n\n"); 
   
  //Etape 2 
  printf("ETAPE 2 :\n"); 
  calculHistogrammeDeCouleur(url); 
  printf("\n\n"); 

}
 

void CalculHistogramesPertinences(char *req, char* path, char* final) 
{ 
    int len; 
    char **liste = readList(path, &len); 
    freeList(liste,len); 
   
    printf("ETAPE 3 :\n"); 
    KEY distance[len]; 
    histogrammeDistance(req,path,distance); 
    printf("\n\n"); 
   
    printf("ETAPE TRI :\n"); 
    TriPertinence(distance, len); 
    printf("\n\n"); 
     
    printf("ETAPE AFFICHAGE :\n"); 
    AfficherResultatHTML(distance,len,path,req,final); 
    printf("\n\n"); 
} 

void filtrageSift(char *fichier) 
{ 
    //execlp
}*/

int main(int argc, char *argv[])
{
	if(argc>1)
	{
		//Etape 1 
		printf("PREMIERE PARTIE :\n\n");

		//creationFichierHistogrammeCouleur();
		//calculPertinenceCouleur("../images/2008_000001.jpg");
		calculPertinenceCouleur(argv[1]);
		printf("\n\n"); 

		printf("DEUXIEME PARTIE :\n\n"); 

		printf("\n\n"); 

		printf("TROISIEME PARTIE :\n\n");
		printf("\n\n"); 
	}
	else
	{
		printf("Il manque un argument : histo <fichier_Requete>\n");
		}
	exit(0);
}
