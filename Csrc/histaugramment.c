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

#include "chargementHisto.h"



int main(int argc, char *argv[])
{
		
	if(argc==2)
	{
		if(atoi(argv[1])==1)
		{
			creationFichierHistogrammeCouleur();
		}
		else if(atoi(argv[1])==2)
		{
			calculHistogrammeDeClasse(256);
		}
	}
	else if(argc>2)
	{
		//Etape 1 
		printf("PREMIERE PARTIE :\n\n");
		calculPertinenceCouleur(argv[1]);
		printf("\n\n"); 

		printf("DEUXIEME PARTIE :\n\n"); 
		calculPertinenceForme(argv[1],argv[2]);
		printf("\n\n"); 

		printf("TROISIEME PARTIE :\n\n");
		calculPertinenceMin(argv[1],argv[2]);
		calculPertinenceMoy(argv[1],argv[2]);
		printf("\n\n"); 
	}
	else
	{
		printf("Il manque un argument. Le programme se lance de deux manière différente :\n histo <fichier_Requete> <fichier_sift>\n histo {1,2}, permet de chrger le fichier des hitogramme de couleur(1) ou de cluster(2)\n");
	}
	exit(0);
}
