#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
using namespace std;

class query{
	private:
		char* text;
	public:
		/*constructeur*/
		query();
		query(char* buffer);
		
		/*getters et setters*/
		void setText(char* buffer);
		char* getText();
		/*fonctions*/
		short separation(); /*indique l'indice de la chaine de caractère où la description et la sequence sont séparés*/
		string getDescription(short longueur); /*renvoie la description de la séquence (header)*/
		int getLength(short separation); /*Renvoie la longueur de la séquence.*/
		char* getSequence(short begin_sequence,int length); /*renvoie la séquence de la protéine*/		
};