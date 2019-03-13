#include "database.h"
const char table[28]={'-','A','B','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','U','*','O','J'};
//Constructeur
database::database()
{
	text=NULL;
}
database::database(char* buffer){
	text=buffer;
}
//getter et setter
void database::setText(char* buffer){
	text=buffer;
}
char* database::getText(){
	return text;
}


/*methodes*/
vector <int> database::getEmplacement()
{/*tampon (char*) : voir au dessus
	cette fonction renvoie les emplacement des élements du fichier sous forme 
	* d'un vector de int*/
	vector <int> emplacement(12);
	emplacement[0]=0;/*version de la database*/
	emplacement[1]=4+emplacement[0];/*proteine ou adn */
	emplacement[2]=4+emplacement[1];/* nombre de caractère du titre*/
	emplacement[3]=4+emplacement[2];/*première lettre du titre*/
	emplacement[4]=emplacement[3]+Bytes_to_integer(text,emplacement[2],4,true);/*nombre de caractère de la date de création de la database*/
	emplacement[5]=4+emplacement[4];/*premier caractère de la date de création de la database*/
	emplacement[6]=emplacement[5]+Bytes_to_integer(text,emplacement[4],4,true);/*nombre  de sequence*/
	if (Bytes_to_integer(text,emplacement[6],4,true) == 0){
		emplacement[6]=4+emplacement[6];
		if (Bytes_to_integer(text,emplacement[6],4,true) == 0){
			emplacement[6]+=4;
			
		}
	}
	emplacement[7]=emplacement[6]+4;/*nombre de résidues*/
	emplacement[8]=emplacement[7]+8;/*nombre de résidues de la plus grande sequence la plus grande sequence*/
	emplacement[9]=emplacement[8]+4;/*headers offset*/
	emplacement[10]=emplacement[9]+(1+Bytes_to_integer(text,emplacement[6],4,true))*4;//sequence offset
	emplacement[11]=emplacement[10]+(1+Bytes_to_integer(text,emplacement[6],4,true))*4;
	return emplacement;
}
				
int database::getVersion(vector<int> place){
	/* Renvoie le numéro de la version de la database*/
	return Bytes_to_integer(text,place[0],4,true);
}
string database::ProteinOrDNA(vector<int> place){
	/*indique s'il s'agit d'une proteine ou de l'adn*/
	string result="DNA";
	if (Bytes_to_integer(text,place[1],4,true)==1){
		result="Protein";
	}
	return result;
}

string database::getTitle(vector<int> place){
	/*renvoie le titre de la database*/
	int NumberOfChar=Bytes_to_integer(text,place[2],4,true);
	char* title=new char[NumberOfChar+1];
	title[NumberOfChar]='\0';
	for(int i=0;i<NumberOfChar;i++){
		title[i]=text[i+place[3]];
	}
	return (string) title;
}

string database::getTimestamp(vector<int> place){
	/*renvoie la date de création de la database*/
	int NumberOfChar=Bytes_to_integer(text,place[4],4,true);
	char* timestamp=new char[NumberOfChar+1];
	timestamp[NumberOfChar]='\0';
	for(int i=0;i<NumberOfChar;i++){
		timestamp[i]=text[i+place[5]];		
	}
	return (string) timestamp;
}
int database::getNumberOfSequences(vector<int> place){
	return Bytes_to_integer(text,place[6],4,true);
}
int database::getNumberOfResidues(vector<int> place){
	return Bytes_to_integer(text,place[7],8,false);
}
int database::getNumberOfLongestSequence(vector<int> place){
	return Bytes_to_integer(text,place[8],4,true);
	}
vector <int> database::getHeaderOffset(vector<int> place,int number_of_sequences){
	/*Retourne une liste d'offset(headers), c'est à dire la position du 
	 * ième header de la ième sequence dans le fichier psq
	 * place: vector<int> donnant les emplacements des différents 
	 * éléments du fichier.pin
	 * number_of_sequences: int est le nombre de sequences dans la database
	 * */
	vector<int> offsetsheader(number_of_sequences+1);
	int j=place[9];
	for (int i=0;i<number_of_sequences+1;i++){
		offsetsheader[i] = Bytes_to_integer(text,j,4,true);
		j=j+4;
	}
	return offsetsheader;
}

vector <int> database::getSequenceOffset(vector<int> place,int number_of_sequences){
	/*Retourne une liste d'offset, c'est à dire la position de la ième sequence dans le fichier psq*/
	vector<int> offsetsequence(number_of_sequences+1);
	int j=place[10];
	for (int i=0;i<number_of_sequences+1+1;i++){
		offsetsequence[i] = Bytes_to_integer(text,j,4,true);
		j=j+4;
	}
	return offsetsequence;
}
	
char* database::getHeadersFromDatabase(vector<int> offset,int index_header){
	/*Prend les parties importantes des headers du fichier phr
	 * offset: vector<int> contenant les offsets de chaque header dans le fichier .phr
	 * index_header: int donnant l'indice du header
	 * */
	int begin=offset[index_header];
	int i=begin;
	//Petit raccourci pour ne pas devoir décoder tout le phr
	while (text[i+1]!='s' || text[i+2]!='p' || text[i+3]!='|'){
		i++;
	}
	int length=Bytes_to_integer(text,i,1,true);
	i+=1;
	char* name=new char[length+1];
	name[length]='\0';
	for (short j=0;j<length;j++)
	{
		name[j]=text[i];
		i+=1;
	}
	return name;
}

vector<char> database::getSequenceFromDatabase(vector<int> offset,int index_seq){
	/*Fonction donnant en sortie une sequence de la base de donnée
	 * offset: vector<int> contenant les offsets du debut d'une sequence 
	 * dans le fichier .psq
	 * index_seq: int donnant l'indice de la sequence 
	 * */
	int begin= offset[index_seq];
	int length=offset[index_seq+1]-begin-1;
	//longueur de la sequence (on retire le '-' à la fin)
	vector<char> seq(length);
	for (int i=0;i<length;i++){
		/*seq[i]=table[(int)text[i+begin]];*/
		seq[i]=table[(short) text[i+begin]];	
	}
	return seq;
}

int Bytes_to_integer(char* buffer,int emplacement,short nb_byte,bool is_big_endian){
	unsigned char* Byte=new unsigned char[nb_byte];
	//On crée une chaine de caractère avec le nombre de bytes 
	//mis en paramètres 
	for (int i=0;i<nb_byte;i++){
		Byte[i]=buffer[emplacement+i];
		// on remplit la chaine de caractères par les bytes du buffer
	}
	//décodage des bytes
	int result=0;
	if (!is_big_endian)//little endian
		for (int n = nb_byte-1; n >= 0; n--)
			result = (result << 8) +Byte[ n ];
	else//Big endian
		for (unsigned n = 0; n < nb_byte; n++)
			result = (result << 8) +Byte[ n ];
	return result;
    
}