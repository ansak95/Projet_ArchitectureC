#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 256


void remplacer (char tab[], char sort[],int nbr[], char tmp[], char eti[]) {
  int j, ctr, i, l;
  j=0;
  ctr=0;
  i=0;
  l=0;
  while(tab[i]!=':' && tab[i]!='\0') {
	  eti[i]=tab[i];
    i++;
  }
  if (i==strlen(tab)) {
	   eti[0]='\0';
    i=1;
  }
  else {
	  eti[i-1]='\0';
    i+=2;
  }
  while (tab[i]!='\0') {
    while ((tab[i]!='\t' && tab[i]!=' ') && !ctr) {
      sort[j]=tab[i];
      if (tab[i]=='\0'||tab[i]=='\n') {
        sort[j]='\0';
        nbr[0]=0;
        return;
      }
      j++;
      i++;
    }
      if ((tab[i]!='\t' || tab[i]!=' ') && !ctr) {
        i++;
      }
      ctr=1;
        tmp[l]=tab[i];
        l++;
        i++;
    }
  tmp[l-1]='\0';
  nbr[0]=atoi(tmp);
  sort[j]='\0';
}


int main () {
  FILE* dic=NULL;
  FILE* entree=NULL;
  FILE* entree2=NULL;
  FILE* sortie=NULL;
  int j, ligne,saut;
  saut=0;
  j=0;
  ligne=0;
  char recup[256];
  char recup2[256];
  char mot[26];
  char tab[26];
  int dico[1];
  char mot2[26];
  char etiq[26];
  int nbr[1];
  dic=fopen("dico.txt", "r");
  entree=fopen("entree.txt", "r");
  sortie=fopen("sortie.txt", "w");
  entree2=fopen("entree.txt", "r");
  if (dic==NULL) {
    printf("Ouverture de fichier impossible\n");
  }
  else {
	while (fgets(recup, TAILLE_MAX, entree)!=NULL){
      remplacer(recup, mot, &nbr[0], etiq, tab);
       if (strstr(etiq, " ")!=NULL){
		   printf("To much args in the %d lines", ligne+1);
		   return 0;
	   }
	   if (nbr[0]<0 || nbr[0]>5000){
		   printf("! segmentation fault ligne(%d) n'appartient pas à [0,5000] ==> Pas assez de cases memoire.\n", ligne+1);
		   return 0;
	   }
      while (fscanf(dic, "%s\t%d", mot2, &dico[0])!=EOF && j!=1) {
        if (!strcmp(mot, mot2)) {
          if (!strcmp(mot, "jpz") || !strcmp(mot, "jmp") || !strcmp(mot ,"call")) { /*on sait qu'il s'agit d'une rupture de sequence,donc on cherche non plus un int mais un char pour l'adresse*/
            if (atoi(etiq)==0 && etiq[0]!='0'){
			strcpy(mot, etiq);
            int l=0;
            int s=0;
            char tmp[256];
            char etiqu[256];
            char word[20];
            int nbr1[1];
            while (fgets(recup2, TAILLE_MAX, entree2)!=NULL && s!=1) { /*On connait deja la structure des etiquette : nometiq\t:*/
              remplacer(recup2, word, &nbr1[0],tmp, etiqu);
               if (strcmp(mot, etiqu)==0) {
                  saut=l-ligne-1;
                s=1;
              }
              l++; // !! au cas ou on ne trouve pas l'etiquette
            }
             //~ printf("%s %d %d\n", etiqu, ligne, l);
             if (s==0){
				 printf("Pas d'etiquette trouvee  pour la %d ligne\n", ligne+1);
				 return 0;
			 }
              fprintf(sortie, "0%X\t%08X\n", dico[0], saut);
		  
              rewind(entree2);
          }
          else{
			  fprintf(sortie, "0%X\t%08X\n", dico[0], nbr[0]);
	  }
  }
          else {
            if (dico[0]<14) {
                if(!nbr[0] && dico[0]!=10 && dico[0]!=1 && dico[0]!=4 && dico[0]!=5){
                    printf("Warning : Too few arguments in the %d line old man!\n", ligne+1 );
                    fprintf(sortie, "0%X\t%08X\n", dico[0], nbr[0]);
                    return 0;
                    }

              else{
				  fprintf(sortie, "0%X\t%08X\n", dico[0], nbr[0]);
			  }
            }
            else {
              fprintf(sortie, "%X\t%08X\n", dico[0], nbr[0]);
            }
          }
          j=1;
        }
      } if(!j) {printf("Il y'a une erreur à la %d e ligne.", ligne+1);
      return 0;
      }
      rewind(dic);
      j=0;
      ligne++;
    }
  }
  fclose(dic);
  fclose(entree);
  fclose(entree2);
  printf("Fin du programme\n");
  return 0;
}
