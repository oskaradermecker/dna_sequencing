#include "matrix.h"

matrix::matrix()
{
	text=NULL;
}

matrix::matrix(char* buffer){
	text=buffer;
}

void matrix::setText(char* buffer){
	text=buffer;
}
char* matrix::getText(){
	return text;
}

short matrix::getBegin(){
	/*renvoie là où les descriptions de la matrice sont finies*/
	int i=1;
	while (text[i]!='\n' || text[i+1]!=' '){
		
		i++;
	}
	return i+1;
}

short matrix::getDimension(short begin){
	/*renvoie la dimension de la matrice*/
	
	short j=0;
	short i=begin;
	while (text[i]!='\n'){
		if (text[i]!=' ')/*On prend tous les caractères et on évite les espaces*/
		{
			j++;	
		}
		i++;
	}
return j;
}

int getValueOf(char letter){
	/*Trouver l'indice d'une lettre dans une matrice 
 * On peut profiter du fait que cet ordre est le même pour toute les matrices blosum*/

switch (letter) { 
case 'A': return  0; break;
case 'R': return  1; break; 
case 'N': return  2; break; 
case 'D': return  3; break; 
case 'C': return  4; break; 
case 'Q': return  5; break; 
case 'E': return  6; break; 
case 'G': return  7; break; 
case 'H': return  8; break; 
case 'I': return  9; break; 
case 'L': return 10; break; 
case 'K': return 11; break; 
case 'M': return 12; break; 
case 'F': return 13; break; 
case 'P': return 14; break; 
case 'S': return 15; break; 
case 'T': return 16; break; 
case 'W': return 17; break; 
case 'Y': return 18; break; 
case 'V': return 19; break; 
case 'B': return 20; break; 
case 'Z': return 21; break; 
case 'X': return 22; break; 
case '*': return 23; break;} 
return 23;
   
}

vector<vector<short> > matrix::getMatrix (short dim,short begin){
	/*crée une matrice (deux dimensions) de short*/
	
	short i=begin;/* on commence la où il n'y a plus les descriptions*/
	i++;
	short l=-1;/*-1 car sur la première ligne il n 'y aura que des lettres*/
	short c=0;
	vector<vector<short> > colonne(dim,vector<short>(dim));
	/*initialisation de la matrice*/
           
	while (i<strlen(text)-2){
		
		if (text[i]=='\n' and l<dim)/*s'il est en fin de ligne*/
		{	
			l++;
			c=0;
		}
		else if ((short)(text[i]-'0')<=9 && (short)(text[i]-'0')>=0 &&(short)text[i]!=32)
		/*traduction: s'il s'agit d'un chiffre (surcondition: 
		 * et si ce n'est pas un espace)*/
		{
			if (text[i-1]!='-'){
				colonne[l][c]=(short)(text[i]-'0');
				/*renvoie un nombre positif s'il n'y a pas de 
				 * - devant le caractère*/
				while (text[i+1]<='9' && text[i+1]>='0'){
					//Si le nombre fait plusieurs chiffres
					colonne[l][c]=colonne[l][c]*10+(short)(text[i+1]-'0');	
					i++;
				}
			}	
			else{
				colonne[l][c]=-(short)text[i]+48;/* =-(short)(text[i]-'0')*/
				while (text[i+1]<='9' && text[i+1]>='0'){
					colonne[l][c]=colonne[l][c]*10-(short)(text[i+1]-'0');
					
					i++;
				}
			}				
			c++;
		}
		i++;
		
	}
	return colonne;
}