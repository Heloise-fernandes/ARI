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
	//cat ./mapping/2008_000001.sift | sort -n|uniq -c >testClusterShell.txt 
	  //float monHisto[256];
	  //int indice = 0;
	  //unhistoDeClasse("./mapping/2008_000001.sift", 256, monHisto);
	  /*int indice =0;
	  int tailleMAXLu = 5;
	  char chaine[tailleMAXLu];
	
	  for(indice=0; indice <256; indice++)
	  {
		 monHisto[indice]=0.0;
	  }
	
	  FILE* f = fopen("./mapping/2008_000001.sift","r");
	  int t=0;
	  if(f)
	  {  
		while (fgets(chaine, tailleMAXLu, f) != NULL)
		{
			indice = atoi(chaine);
			//printf("%d %s\n",indice,chaine);
			monHisto[indice]++;
			t++;
		}
		
		printf("t = %d\n", t);
		for(indice=0; indice <256; indice++)
		{
			monHisto[indice]=monHisto[indice]/t;
			printf("%f\n",monHisto[indice]);
		}
	  }
	  printf("\n");
	  fclose(f);
	*/
	/*for(indice=0; indice <256; indice++)
	{
		printf("%f\n",monHisto[indice]);
	}*/
		
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
		printf("\n\n"); 
	}
	else
	{
		printf("Il manque un argument. Le programme se lance de deux manière différente :\n histo <fichier_Requete> <fichier_sift>\n histo {1,2}, permet de chrger le fichier des hitogramme de couleur(1) ou de cluster(2)\n");
	}
	exit(0);
}
