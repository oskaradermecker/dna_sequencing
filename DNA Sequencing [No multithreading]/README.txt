Comment lancer le programme:
A. Programme non optimisé.
1)Compilation:
$ make
2)Exécution:
$./main nom_de_la_database nom_de_la_query_sequence matrice_blosum gap_open_penalty gap_extend_penalty
ex:
$./main uniprot_sprot.fasta P00533.fasta BLOSUM62.txt 11 1

PS: vérifier que:

1. le fichier pour la query sequence
2. les 3 fichiers .pin .psq et .phr
3. le fichier de la matrice blosum

se trouvent bien dans le repertoire où on execute le programme.
