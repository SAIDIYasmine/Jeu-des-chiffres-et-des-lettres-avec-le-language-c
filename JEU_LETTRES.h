#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
void regles();
int _rand(int a,int b);
char rand_char();
char *rand_seq();
char *mot(FILE *fichier,int taille_mot);
FILE *ouvrir(int a);
int existe_en_dict(char *chaine);
int ajouter_mot_dict(char *nouv);
int occurence(char c,char *chaine);
int verifier_lettres(char *chaine1,char *chaine2);
int nbre_mots_dict(int taille);
char *rand_word(int taille);
char *permuter(char *word);
int in_list(int n,int *L,int taille_liste);
int pos_occ(char c,char *chaine);
void aff_instruc();
void attendre(int t);
int jeu_lettres();
int _char_to_int(char c);
int _verifier_saisie(char d);


