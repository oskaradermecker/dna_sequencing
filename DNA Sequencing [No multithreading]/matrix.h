#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
using namespace std;

class matrix{
	private:
		char* text;
	public:
	/*constructeur*/
		matrix();
		matrix(char* buffer);
	
	/*getters et setters*/
		void setText(char* buffer);
		char* getText();
	/*fonctions*/
		short getBegin();
		short getDimension(short begin);
		vector<vector<short> > getMatrix (short length,short begin);
		
		
};
int getValueOf(char letter);
