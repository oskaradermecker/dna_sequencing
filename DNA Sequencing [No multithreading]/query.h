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
		short separation();
		string getDescription(short longueur);
		int getLength(short separation);
		vector<char> getSequence(short begin_sequence,int length);
		
		
};

