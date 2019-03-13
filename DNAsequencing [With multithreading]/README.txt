FR:

Comment lancer le programme:

1)Compilation:
$ make

2)Exécution:
$./main nom_de_la_database nom_de_la_query_sequence matrice_blosum gap_open_penalty gap_extend_penalty nb_cores_computer
ex: ...
	
$./main uniprot_sprot.fasta P00533.fasta BLOSUM62.txt 11 1 8




PS: vérifier que:


	1. le fichier pour la query sequence

	2. les 3 fichiers .pin .psq et .phr

	3. le fichier de la matrice blosum



se trouvent bien dans le repertoire où on execute le programme.



EN:

How to start the program:

A. Non-optimized program.


1)Compilation:
$ make

2)Execution:
$./main name_of_database name_of_query_sequence matrice_blosum gap_open_penalty gap_extend_penalty nb_cores_computer
ex: ...
	
$./main uniprot_sprot.fasta P00533.fasta BLOSUM62.txt 11 1 8




PS: make sure that the following files are located in the folder where the program is executed:

	1. the file of the query sequence
	2. the 3 .pin .psq et .phr
 files
	3. the file with the BLOSUM matrix