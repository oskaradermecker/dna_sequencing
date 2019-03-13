# dna_sequencing

Being able to find the optimal alignment of two biological sequences of nucleotides is an important challenge in bioinformatics. Since there are (m+n)!/(m!)² ways of alligning two sequences of lengths m and n, smart ways of comparing DNA sequences had to be developed. This program implements a sequence alignment algorithm, as well as mutlithreading, based on the algorithm of Smith and Waterman and Rogue's improvements, available in the literature. [1] provides more information on the input files used. 

Sources:

[1] Farrar, Michael S. 2010. “NCBI BLAST Database Format” 4: 1–9.
[2] Gotoh, Osamu. 1982. “An Improved Algorithm for Matching Biological Sequences.” Journal of Molecular Biology 162 (3): 705–8.     https://doi.org/10.1016/0022-2836(82)90398-9.
[3] Rognes, Torbjørn. 2011. “Faster Smith-Waterman Database Searches with Inter-Sequence SIMD Parallelisation.” BMC Bioinformatics 12 (1). BioMed Central Ltd: 221. https://doi.org/10.1186/1471-2105-12-221.
[4] Smith, T.F., and M.S. Waterman. 1981. “Identification of Common Molecular Subsequences.” Journal of Molecular Biology 147 (1): 195–97. https://doi.org/10.1016/0022-2836(81)90087-5.

[French version below]

How to start the program?

1)Compilation: $ make

2)Execution: $./main name_of_database name_of_query_sequence matrice_blosum gap_open_penalty gap_extend_penalty nb_cores_computer
For example: $./main uniprot_sprot.fasta P00533.fasta BLOSUM62.txt 11 1 8

PS: make sure that the following files are located in the folder where the program is executed:
	1. the file of the query sequence
	2. the 3 .pin .psq et .phr files
	3. the file with the BLOSUM matrix

French:

Comment lancer le programme?

1)Compilation: $ make

2)Exécution: $./main nom_de_la_database nom_de_la_query_sequence matrice_blosum gap_open_penalty gap_extend_penalty nb_cores_computer
Par exemple: $./main uniprot_sprot.fasta P00533.fasta BLOSUM62.txt 11 1 8

PS: vérifier que les fichiers suivants se trouvent bien dans le repertoire où le programme est exécuté:
	1. le fichier pour la query sequence
	2. les 3 fichiers .pin .psq et .phr
	3. le fichier de la matrice blosum
