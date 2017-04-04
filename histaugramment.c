#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"
#include "proc.c"


void calculHistogramme(char* nom, float* histo){
  int i,j,n;
  CIMAGE cim;
  /*------------------------------------------------*/
  /* lecture d'une image requête                    */
  /*------------------------------------------------*/
  
  printf("Image %s \n", nom);
  
  read_cimage(nom,&cim);
  
  //On initialise le tableau à 0
  for(i=0; i <64; i++)
  {
	  histo[i]=0.0;
  }
  
  //On fait passer le nombre de valeur possible de 256 à 4
  for (j = 0; j < cim.ny; j++) {       
    for (i = 0; i < cim.nx; i++) {   
      cim.r[i][j]=cim.r[i][j]*4/256;
      cim.g[i][j]=cim.g[i][j]*4/256;
      cim.b[i][j]=cim.b[i][j]*4/256;
    }
  }
  
  /*------------------------------------------------*/
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

void calculHistogrammeDeCouleur(char *pathList)
{
  //le tableau qui contient les couleurs
  float monHisto[64];
  //Le nombre de fichier
  int len;
  //indice
  int fichier;
  //Liste de l'ensemble des fichiers
  char **liste = readList(pathList, &len);
  
  //Fichier qui contient contiendra l'index
  FILE* efe = fopen("./histogrammes/indexes","wb+");
  
  //Pour chaque fichier on : 
  for(fichier = 0; fichier<len; fichier++)
  {
	//calcul sont histogramme
	calculHistogramme(liste[fichier], monHisto);  
	//Ecrit le tableau dans un fichier
	fwrite(monHisto,sizeof(float),64,efe);
  }
  //on ferme le fichier
  fclose(efe);
  freeList(liste,len); 
}



void histogrammeDistance(char* requete, char *pathURL, KEY *res) 
{
	int len;
	int i = 0;
	float histoReq[64];
	float histoCourant[64];
	
	for(i=0; i <64; i++) 
	{ 
		  histoReq[i]=0.0; 
		  histoCourant[i]=0.0; 
	}
	
	//trouver numero requete dans liste fichier
	char **liste = readList(pathURL, &len);
	int numRequete = -1;
	
	for(i=0;i<len;i++)
	{
		if(strcmp(liste[i],requete)==0)
		{numRequete=i;break;}
	
	}
	printf("Le fichier %s correspond au numéro %d - %s\n",requete,numRequete,liste[i]);

	//Calcule distance pour tout les fichiers
	FILE* efe = fopen("/home/fernandes/Documents/S8/ARI/Partie2/ARI_Image/ARI/histogrammes/indexes","rb");
	
	fseek(efe,64*sizeof(float)*numRequete,SEEK_SET); 
    fread(histoReq,sizeof(histoReq),1,efe); 
	rewind(efe);
	
    for(i=0;i<64;i++)
	{
		printf("%f-",histoReq[i]);
	}
	printf("\n");
	
	//Affichage
    float distanceCourante;
    int j=0;
	for(i = 0; i<len; i++)
	{
		distanceCourante = 0;
		fread(histoCourant,sizeof(histoReq),1,efe); 
		for(j=0;j<64;j++)
		{
			distanceCourante= distanceCourante + fabs(histoCourant[j]-histoReq[j]);
		}
		res[i].d = distanceCourante; 
		res[i].k = i; 
	}
	fclose(efe);
	
	for(i=0;i<len;i++)
	{
		printf("%s / %f\n",liste[i],res[i].d);
	}
	freeList(liste,len); 
}

void TriPertinence(KEY *res, int len) 
{ 
  qsort(res,len,sizeof(KEY),keyCompare); 
  int i = 0; 
  for(i=0;(i<len)&&(i<10);i++) 
  { 
    printf("%d / %f\n",res[i].k,res[i].d); 
  } 
} 
 
void AfficherResultatHTML(KEY *res, int len , char* pathURLS,char *req, char* final) 
{ 
  //Charger liste 
  int len2; 
  char **liste = readList(pathURLS, &len2); 
   
  //Ouvrir fichier 
  FILE* efe = fopen(final,"w+"); 
     
  //Ecrire requete 
  fprintf(efe, "<HEAD>\n</HEAD>\n<BODY>\n"); 
  fprintf(efe, "<p>La requete %s </p>\n<IMG SRC=\".%s\">\n", req,req); 
   
  //Ecrire 10 + pertinent 
  int i = 0; 
  for(i=0;(i<len)&&(i<10);i++) 
  { 
    fprintf(efe, "<p>N°%d : %s </p>\n<IMG SRC=\".%s\">\n", i,liste[i],liste[i]);
  }   
  fprintf(efe, "</BODY>\n"); 
  //Fermer et free 
  fclose(efe); 
  freeList(liste,len2); 
} 
 
 
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
    //Ouvrir fichier
    FILE* efe = fopen(fichier,"w+");
    
    
    //skip les trois premièr ligne
    
    //lire carc par carc
}

int main(int argc, char *argv[])
{
  //Etape 1 
  printf("PREMIERE PARTIE :\n\n");
  //chargement("/home/fernandes/Documents/S8/ARI/Partie2/ARI_Image/ARI/urls2.txt");
  //CalculHistogramesPertinences("./images/2008_000001.jpg","/home/fernandes/Documents/S8/ARI/Partie2/ARI_Image/ARI/urls2.txt","./histogrammes/ResultatPart1.html"); 
  printf("\n\n"); 
  
  printf("DEUXIEME PARTIE :\n\n"); 
  
  printf("\n\n"); 
  
  printf("TROISIEME PARTIE :\n\n");
  printf("\n\n"); 
 exit(0);
}
