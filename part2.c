#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAILLE 20

struct instruction{
	int code;
	int donnee;
};

int initPC (struct instruction tab[], FILE* f){
	FILE* copy=f;
	int i=0;
	while (fscanf (copy,"%x\t%x",&tab[i].code, &tab[i].donnee)!=EOF && i<TAILLE){	// cette fonction va copier toutes les instruction en langage machine dans notre tableau PC
		i++;
}
	if (i<TAILLE){
		return i;
	}
	return 0;
}

int trad (int co, int don, int* s,int* p, int m[]){ //Ici co~code,don~donnee, s~SP,p~PC, m~mem
	int x;
	switch (co){
		case 0: //push
			m[(*s)]=m[don];
			(*s)++;
		break;
		case 1: //iPush
			x=m[(*s)-1];
			m[(*s)-1]=m[x];
		break;
		case 2: //push#
			m[(*s)]=don;
			(*s)++;
		break;
		case 3: //pop
			(*s)--;
			m[don]=m[(*s)];
		break;
		case 4: //iPop
			m[m[(*s)-1]]=m[(*s)-2];
			(*s)=(*s)-2;
		break;
		case 5: //dup
			(*s)++;
			m[(*s)]=m[(*s)-1];
		break;
		case 6: //op
			switch (don){
			case 0:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]&m[(*s)];
			break;
			case 1:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]|m[(*s)];
			break;
			case 2:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]^m[(*s)];
			break;
			case 3:
				m[(*s)-1]=~m[(*s)-1];
			break;
			case 4:
				m[(*s)-1]=(-1)*m[(*s)-1];
			break;
			case 5:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]+m[(*s)];
			break;
			case 6:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]-m[(*s)];
			break;
			case 7:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]*m[(*s)];
			break;
			case 8:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]/m[(*s)];
			break;
			case 9:
				(*s)--;
				m[(*s)-1]=m[(*s)-1]%m[(*s)];
			break;
			case 10:
				(*s)--;
				if (m[(*s)-1]==m[(*s)]){
					m[(*s)-1]=0;
				}
				else{
					m[(*s)-1]=1;
				}
			break;
			case 11:
				(*s)--;
				if (m[(*s)-1]==m[(*s)]){
					m[(*s)-1]=1;
				}
				else{
					m[(*s)-1]=0;
				}
			break;
			case 12:
				(*s)--;
				if (m[(*s)-1]<=m[(*s)]){
					m[(*s)-1]=1;
				}
				else{
					m[(*s)-1]=0;
				}
			break;
			case 13:
				(*s)--;
				if (m[(*s)-1]<m[(*s)]){
					m[(*s)-1]=1;
				}
				else{
					m[(*s)-1]=0;
				}
			break;
			case 14:
				(*s)--;
				if (m[(*s)-1]>=m[(*s)]){
					m[(*s)-1]=1;
				}
				else{
					m[(*s)-1]=0;
				}
			break;
			case 15:
				(*s)--;
				if (m[(*s)-1]>m[(*s)]){
					m[(*s)-1]=1;
				}
				else{
					m[(*s)-1]=0;
				}
			break;
			default:
			break;
		}
		break;
		case 7: //jmp
			if (((*p)=(*p)+don)<-1){
				(*p)=-1;
			}
		break;
		case 8: //jpz
			(*s)--;
			x=m[(*s)];
			if (!x){
				(*p)=(*p)+don;
			}
		break;
		case 9: //call
			m[(*s)]=(*p);
			(*s)++;
			(*p)=(*p)+don;
		break;
		case 10: //ret
			(*p)=m[(*s)-1];
			(*s)--;
		break;
		case 11: //rnd
			m[(*s)]=rand()%((don-1));
		break;
		case 12: //write
			printf("%d\n", m[don]);
		break;
		case 13: //read
			printf("Entrez une valeur\n");
			if (scanf("%d", &m[don])!=-1);
		break;
		case 99: //halt
			printf("Fin du Programme\n");
			break;
		default:
			printf("Erreur\n");
			return 1;
		break;
	}
	return 1;
}	

int main (){
int mem[5000];
struct instruction copie[TAILLE];
int SP,PC,co,don;
SP=0;
PC=0;
FILE* code_mach=NULL;
code_mach=fopen("sortie.txt", "r");
time(NULL);
if (code_mach==NULL){
	printf("Erreur fichier non recupere\n");
}
else {
	if (!initPC(copie, code_mach)){
		printf("Taille PC insuffisante\n");
		}
	else {
		do{
			co=copie[PC].code;
			don=copie[PC].donnee;
			if (trad(co, don, &SP, &PC, mem)!=0){
			PC++;
			printf("Registres : PC=%d & SP=%d ", PC, SP);
			printf("Pile : mem[SP]= %d\n", mem[SP]);
		}
			else{
				return 0;
			}
		}while (co!=99);
	}
}
return 0;
}
