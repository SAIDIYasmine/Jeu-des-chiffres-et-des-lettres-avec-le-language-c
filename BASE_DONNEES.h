#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
//DECLARATION DES CONSTANTES
#define size_max 15
#define size_min 3
//DECLARATION DES STRUCTURES ----------------------------------------------
typedef struct joueur{
	int code;
	char *nom_util;
	char *nom;
	char *prenom;
	char *mdp;
	int score;
}_joueur;

typedef struct jeux{
	_joueur *joueur;
	struct jeux *suivant;
}_jeux;
typedef struct admin{
	char *nom;
	char *mdp;
}_admin;

//PROTOTYPES DES FONCTIONS UTILISEES ----------------------------------------
_admin *adminstr();
_joueur *existe_nom_util(_jeux *jeu,char *nom_util);
void verifier_mdp(char *mdp);
int valide_size_char(char *donnee);
_joueur *connexion(_jeux *jeu);
_joueur *creej(_jeux *jeu);
void inserer(_jeux *jeu,_joueur *joueur);
void verifier_mdp(char *mdp);
void changer_mdp(_joueur *j);
void changer_nom(_joueur *j);
void changer_prenom(_joueur *j);
void affj(_joueur *j);
void affl(_jeux *j);
void ecrire(_joueur *joueur,FILE *fichier);
void enregistrer(_jeux *jeux);
_joueur *charger_joueur(FILE *fichier);
_jeux *charger_jeux();
int nbr_util(_jeux *jeu);
void ecrire_message(_joueur *j,char *msg);
void vider_messagerie();
void afficher_messagerie();
void tri_a_bulle(int *t,int n);
int _in_list(int n,int *L,int taille_liste);
void classement(_jeux *jeu);
int char_to_int(char c);
int verifier_saisie(char d);

