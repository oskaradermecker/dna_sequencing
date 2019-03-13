#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
using namespace std;

class database{
	
	private:
		char* text;
	public:
		database();
		database(char* buffer);
	
		void setText(char* buffer);
		char* getText();
		/*Spécifique au fichier .pin*/
		vector<int> getEmplacement();
		int getVersion(vector<int> place);
		string ProteinOrDNA(vector<int> place);
		string getTitle(vector<int> place);
		string getTimestamp(vector<int> place);
		int getNumberOfSequences(vector<int> place);
		int getNumberOfResidues(vector<int> place);
		int getNumberOfLongestSequence(vector<int> place);
		vector <int> getHeaderOffset(vector<int> place,int number_of_sequences);
		vector <int> getSequenceOffset(vector<int> place,int number_of_sequences);
		/*Spécifique au fichier.psq*/
		vector<char> getSequenceFromDatabase(vector<int> offset,int index_seq);
		/*specifique au .phr*/
		char* getHeadersFromDatabase(vector<int> offset,int index_header);
};

int Bytes_to_integer(char* buffer,int emplacement,short nb_byte,bool is_big_endian);



