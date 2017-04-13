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

int MAX = 10;
int MEAN = 5;
int POURCENTAGE_TAILLE_IMAGE_REQ = 25;
int POURCENTAGE_TAILLE_IMAGE = 50;
void AfficherResultatHTML(KEY *res, int len , char* pathURLS,char *req, char* final) 
{ 
  //Charger liste 
  char **liste = readList(pathURLS, &len); 
   
  //Ouvrir fichier 
  FILE* efe = fopen(final,"w+"); 
  
  fprintf(efe, "<!doctype html>\n<HTML>\n<HEAD> <title> Similaritee Couleur </title>\n");    
  fprintf(efe, "<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />\n</HEAD>\n<BODY>\n");    
  

  
  //Ecrire requete   
  fprintf(efe, "<div align = center><p>La requete %s </p>\n<IMG SRC=\"%s\" width=\"%d%%\" ></div>\n", req,req,POURCENTAGE_TAILLE_IMAGE_REQ); 
   
  //Ecrire 10 + pertinent dans un tableau
  int i = 0; 
  fprintf(efe, "<div align = center> <table>\n"); 
  
  for(i=0;(i<len)&&(i<10);i+=2) 
  { 
	fprintf(efe, "<tr>\n");    
    fprintf(efe, "<td>N°%d : %s</td>\n", i,liste[res[i].k]);
    fprintf(efe, "<td>N°%d : %s</td>\n", i+1,liste[res[i+1].k]);
    fprintf(efe, "</tr>\n");
    
    fprintf(efe, "<tr>\n");
    fprintf(efe, "<td><IMG SRC=\"%s\" width=\"%d%%\"></td>\n", liste[res[i].k],POURCENTAGE_TAILLE_IMAGE);
    fprintf(efe, "<td><IMG SRC=\"%s\" width=\"%d%%\"></td>\n", liste[res[i+1].k],POURCENTAGE_TAILLE_IMAGE);
    fprintf(efe, "</tr>\n");
  }  
  fprintf(efe, "</table></n>\n"); 
  
  //Fermeture des balises
  fprintf(efe, "</BODY></HTML>\n"); 
  
  //Fermer et free 
  fclose(efe); 
  freeList(liste,len); 
} 
