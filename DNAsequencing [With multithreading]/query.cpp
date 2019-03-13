#include "query.h"

query::query(){
	text=NULL;
}
query::query(char* buffer){
	text=buffer;
}
void query::setText(char* buffer){
	text=buffer;
}
char* query::getText(){
	return text;
}
short query::separation(){
	/*indique l'indice de la chaine de caractère où la description et la sequence sont séparés*/
	short i=0;
	while (text[i]!='\n'){
		//Tant qu'on ne détecte pas de passage à la ligne on incrémente de 1 pour connaitre l'indice où commence la séquence dans le fichier 
		i++;
	}
	return i;
}
string query::getDescription(short longueur){
	/*renvoie la description de la séquence (header)
	 * longueur: short contenant la taille de cette description*/
	char* description=new char[longueur+1];//création de la chaine de caractère contenant la description
	description[longueur]='\0';
	for (int i=1;i<longueur;i++){
		description[i-1]=text[i];	
	}
	return (string) description;
}
int query::getLength(short separation){
	/*Renvoie la longueur de la sequence.
	 * separation: short indiquant l'endroit où commence cette séquence
	 * 
	 */
	int i=separation+1;
	int j=0;
	while (i<strlen(text)){
		if ('A'<=text[i] && text[i] <='Z' || text[i]=='*')
		{
			//Si on n'a une lettre ou un * on continue
			j++;
		}
		i++;
	}
	return j+1;
	
}
char* query::getSequence(short begin_sequence,int length){
	/*renvoie la sequence de la protéine
	 * begin_sequence: short indiquant le début de la séquence
	 * length: short donne la longueur*/

	char* sequence=new char[length+1];//initialisation d'un vecteur sequence
	sequence[length+1]='\0';
	int j=0;
	int i=begin_sequence+1;
	while (i<strlen(text)){//commence là ou la séquence d'acide aminée commence dans le fichier 
		if ('A'<=text[i] && text[i] <='Z' || text[i]=='*') {// afin d'éliminer les caractères indésirables exemple:'\n'
			sequence[j]=(unsigned char) text[i];
			j++;
		}
		i++;
	}
	return sequence;
}