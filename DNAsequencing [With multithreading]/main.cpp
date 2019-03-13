#include "database.h"
#include "query.h"
#include "matrix.h"
#include "ProgressBar.h"
#include <ctime>
#include <fstream>
#include <pthread.h>
#include <sys/time.h>
#include <algorithm>
using namespace std;
const char table[28]={'-','A','B','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','U','*','O','J'};
vector <pair<int,int> > scores;
char* create_buffer_bin(char* filename){
	/*Fonction qui prend un nom de fichier en argument et qui renvoie le contenue du fichier sous forme de char
	 * filename: char* contenant le nim du fichier
	 */ 
	ifstream fichier(filename, ios::in | ios::binary);//lecture du fichier en mode binaire
	if (!fichier.is_open())
	//Si le fichier ne s'ouvre pas
		{
		cout<<"fichier pas ouvert: "<<(string) filename<<endl;
		return NULL;//On renvoie un NULL
		}

	else
		{
		fichier.seekg(0,fichier.end);//parcours le fichier jusqu' à la fin
		int length=fichier.tellg();//Donne la taille du fichier
		fichier.seekg(0,fichier.beg);//Reviens au début du fichier
		char* buffer = new char[length];//Création du char* qui va contenir le contenu du fichier
		fichier.read(buffer,length);//Lecture du fichier et stockage de son contenu dans buffer
		fichier.close();//fermeture du fichier
		return buffer;

		}
	}
	
bool my_compare(const pair<int,int> &a, const pair<int,int>&b)
		{return a.first> b.first;}	
		

	
int compute_Hij(char* query, char* data,int beg,const unsigned int size_query, const unsigned int size_data,vector<int> matrice, int col,const unsigned int gap_open_penalty, const unsigned int gap_extend_penalty)
{	
	/*Fonction implémentant l'algotithme de Rognes (voir reférences) et renvoyant le score pour l'alignement de la séquence query
	 * avec une séquence de la database.
	 * query : vector<char> contenant la 'query sequence'
	 * data: vector<char> contenant une séquence de la base de donnée
	 * size_query: const unsigned int étant la longueur de la 'query sequence'
	 * size_data: const unsigned int étant la longueur de la séquence de la base de donnée
	 * matrice: vector<int> de la matrice BLOSUM comparant deux résidues 
	 * col: int étant le nombre de colonnes de la matrice
	 * gap_open_penalty: const unsigned int 
	 * gap_extend_penalty: const unsigned int
	 */ 
	 //initialisation des variables (voir références)  
	int H[size_query+1]; 
	int E[size_query+1];
	for (unsigned int i(0); i < size_query+1; i++)
	{
		H[i] = 0;
		E[i] = 0;
	}
	int F;
	char dj; 
	int P,MAX(0), htemp(0), hiold(0);
	const int Q=(gap_extend_penalty + gap_open_penalty);
	const int R=gap_extend_penalty;
	//boucle (size_data*size_query) 
	for (unsigned int j(1); j <= size_data; j++)
	{
		dj = table[(int) data[beg+j-1]]; //Résidues de la séquence de la base de donnée
		F = 0;
		for (unsigned int i(1); i <= size_query; i++)
		{
			P = matrice[getValueOf(query[i-1])*col+getValueOf(dj)];//Comparaison de ces deux résidues
			//Voir Réferences pour l'algorithme
		
			E[i] = max(H[i] - Q, E[i] - R);
			F = max(H[i-1] - Q, F - R);
			htemp = H[i]; 
			H[i] = max(max(E[i], F),max(hiold + P, 0)); 
			hiold = htemp;
			if (H[i]>MAX){
				MAX=H[i];
			}
		}
		
	}
	return MAX;
}

int char_to_int(char* p) {
	/*Cette fonction transforme une chaine de caractère en un entier
	 * char* p: pointeur pointant vers un char (ici utilisé comme chaine de caractère)
	 */ 
	int number=0;
	for (int i = 0; p[i] != '\0'; ++i) {
		number *= 10; 
		number += p[i] - '0';
	}
	return number;
}
class Threads
{
public:
	char* tamp;//Contenu d'un fichier
	int thread;//indice du thread
	int length_of_query;//longueur de la query
    vector <int> offset;//les offsets
    char* query;//la query
    vector<int> Matrice;
    int nb_col;
    int first;//on commence à l''first'ième séquence de la database 
    int last;//On termine à last
    int open;//gap open penalty
    int extend;//gap extend penalty
    int NBT;//nombre de thread
    static void *alignement(void *arguments);
};

void *Threads::alignement(void *arguments)
{
	/*Fonction qui va aligner la query avec plusieurs sequence de la 
	 * database
	 */
	Threads *arg = (Threads*)arguments;
	int prem = arg->first;
	int der = arg->last;
	int t = arg->thread;
	vector<int> mat=arg->Matrice;
	int col=arg->nb_col;
	int o_gap=arg->open;
	int e_gap=arg->extend;
	int n = arg->NBT;
	int l=arg->length_of_query;
	vector<int> soffset=arg->offset;
	char* queryseq=arg->query;
	
   
	for (int i = prem+t*(der-prem)/n; i < prem+(t+1)*(der-prem)/n; i += 1) //toutes les db sequences
	{
		
		scores[i].first=compute_Hij(queryseq,arg->tamp,soffset[i],l,soffset[i+1]-1-soffset[i],mat,col,o_gap,e_gap);
		scores[i].second=i;
		
		
	}
}
int main (int argc, char* argv[]){
	

    //Variables du timer
    struct timeval tbegin,tend;
    double texec=0.;

    //Start Timer
    gettimeofday(&tbegin,NULL);
    //Vérification du nombre de paramètres
    if (argc<7)	
    {cout<<"Il manque des paramètres d'entrées"<<endl;
	return 1;}
	else if (argc>7)	
    {cout<<"Il y a des paramètres d'entrées en trop"<<endl;
	return 1;}
	int nb_threads=char_to_int(argv[6]);
	//Création des noms de fichiers .pin .psq .phr
	string param=argv[1];
	string fpsq=param+".psq";
	string fphr=param+".phr";
	string fpin=param+".pin";
	
	//transformer en entier les paramètres gap extend penalty et gap open penalty
	int o_gap=char_to_int(argv[4]);
	int e_gap=char_to_int(argv[5]);
	

	cout<<"Lecture des fichiers..."<<endl;
	//Lecture des fichiers
	char* fichier_pin=create_buffer_bin((char*) fpin.c_str());
	char* fichier_phr=create_buffer_bin((char *) fphr.c_str());
	char* fichier_psq=create_buffer_bin((char *) fpsq.c_str());
	char* matrix1=create_buffer_bin(argv[3]);
	char* query_1=create_buffer_bin(argv[2]);
	
	//On crée les objets relatifs à chaque fichier
	database pin(fichier_pin);
	database phr(fichier_phr);
	matrix blosum(matrix1);
	query q1(query_1);
	
	//On efface les char* crée par create_buffer_bin
	fichier_pin=NULL;
	fichier_phr=NULL;
	matrix1=NULL;
	query_1=NULL;


	cout<<"fin de lecture"<<endl;

	/*Quelques constantes utiles*/
	vector<int> place=pin.getEmplacement();//Contient l'emplacement des diverses informations contenu dans le pin
	int number_of_residues=pin.getNumberOfResidues(place);
	int number_of_sequences=pin.getNumberOfSequences(place);
	cout<<"pin: ok"<<endl;
	
	/*mettre la query en memoire*/
	short sep = q1.separation();//(sep est l'indice où commence la sequence dans le fichier)
	char* query_sequence=q1.getSequence(sep,q1.getLength(sep));//stockage de la query sequence
	int length_of_query=q1.getLength(sep);
	cout<<"query: ok"<<endl;

	/*mettre la matrice blosum en memoire*/
	short a=blosum.getBegin();
	short b=blosum.getDimension(a);
	vector<vector<short> >Mat=blosum.getMatrix(b,a);
	int line=Mat.size();
	int col=Mat.size();
	int s=0;
	//On stocke notre matrice 2 dimensions sur une matrice à une dimension
	//car ça accélere l'accès à celle-ci
	vector<int> mat_rac(line*col);
	for (int m=0;m<line;m++){
		//cout<<endl;
		
		for (int n=0;n<col;n++){
			mat_rac[s]=Mat[m][n];
			//cout<<mat_rac[s]<<": ";
			s++;
		}
	}
	
	cout<<"matrice: ok"<<endl;

	/*Mettre les Offsets en mémoire*/
	vector<int> hoffset=pin.getHeaderOffset(place,number_of_sequences);
	vector<int> soffset=pin.getSequenceOffset(place,number_of_sequences);
	cout<<"offsets: ok"<<endl;
	
	cout<<"Comparaison de la protéine..."<<endl;	
	
	/*Début de l'ecriture sur le fichier*/
	ofstream ofs;
	ofs.open ("Result.txt", ofstream::out | ofstream::trunc);
	ofs<<"Jaïdi Hossein, Nougba Hamza, Radermecker Oskar"<<endl;
	ofs<<"Program Version:        "<<"1.7+"<<endl;
	ofs<<"Score matrix file:      "<<argv[3]<<endl;
	ofs<<"Database Name:          "<<pin.getTitle(place)<<endl;
	ofs<<"Version:                "<<pin.getVersion(place)<<endl;
	ofs<<"Last Database Update:   "<<pin.getTimestamp(place)<<endl;
	ofs<<"Type:                   "<<pin.ProteinOrDNA(place)<<endl;
	ofs<<"Number of sequences:    "<<pin.getNumberOfSequences(place)<<endl;
	ofs<<"Number of residues:     "<<pin.getNumberOfResidues(place)<<endl;
	ofs<<"Query Description:      "<<q1.getDescription(q1.separation())<<endl;
	ofs<<"\n"<<"\n"<<"Sequences:"<<"\n"<<"Score            Proteins"<<"\n"<<endl;
	 
	/*Comparaison de la proteine avec la database et tri des scores avec threads*/
	scores.resize(number_of_sequences);
	
	pthread_t tds[nb_threads];
	int return_val;
    Threads arg[nb_threads];
	for (int f = 0; f< nb_threads; f++){
		arg[f].tamp=fichier_psq;
		arg[f].thread=f;
		arg[f].length_of_query=length_of_query;
		arg[f].offset=soffset;
		arg[f].query=query_sequence;
		arg[f].Matrice=mat_rac;
		arg[f].nb_col=col;
		arg[f].first=0;
		arg[f].last=number_of_sequences;
		arg[f].open=o_gap;
		arg[f].extend=e_gap;
		arg[f].NBT=nb_threads;
	}
	//On crée les threads
	for (int i = 0; i < nb_threads; i++) 
		pthread_create(&tds[i], NULL, &Threads::alignement, (void *)&arg[i]);
	//On les joint
	for (int i = 0; i < nb_threads; i++)
		pthread_join(tds[i], NULL);
	
	
	sort(scores.begin(), scores.end(),my_compare);// fonction triant le vector selon la fonction my_compare
	for (int j=0; j<50;j++){
		ofs<<scores[j].first<<"       "<<phr.getHeadersFromDatabase(hoffset,scores[j].second)<<endl;
	}
	ofs<<endl;
	cout<<"Résultats affichés dans le fichier : Result.txt"<<endl;
	// End timer
    gettimeofday(&tend,NULL);

    // Compute execution time
    texec=((double)(1000*(tend.tv_sec-tbegin.tv_sec)+((tend.tv_usec-tbegin.tv_usec)/1000)))/1000.;
	std::cout << "Execution time : " << texec << " secondes." << endl;
}



	
