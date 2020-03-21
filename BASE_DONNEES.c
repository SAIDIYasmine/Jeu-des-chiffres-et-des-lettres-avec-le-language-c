#include"BASE_DONNEES.h"

//IMPLEMENTATION DES FONCTIONS ---------------------------------------------
void _attendre(int d){
	time_t debut,fin;
	time(&debut);time(&fin);
	while(difftime(fin,debut)<d) time(&fin);
}
_admin *adminstr(){
	_admin *admin=(_admin*)malloc(sizeof(admin));
	char nomm[]="ADMIN_PROJET\0";
	char mdpp[]="ADMIN_MDP\0";
	admin->nom=(char*)malloc(30*sizeof(char));
	admin->mdp=(char*)malloc(30*sizeof(char));
	strcpy(admin->nom,nomm);strcpy(admin->mdp,mdpp);
	return admin;
}
int comp(char *chaine1,char *chaine2){
	int i;
	if(strlen(chaine1)!=strlen(chaine2)) return 0;
	for (i=0;i<strlen(chaine1);i++) {
	if (*(chaine1+i)!=*(chaine2+i)) return 0;}
	return 1;
}

_joueur *existe_nom_util(_jeux *jeu,char *nom_util){
	if(jeu->joueur==NULL) return NULL;
	while (jeu!=NULL && strcmp(jeu->joueur->nom_util,nom_util)!=0)
	    jeu=jeu->suivant;
	if(jeu==NULL) return NULL;
	return jeu->joueur;
}
int valide_size_char(char *donnee){
	if(strlen(donnee)<size_min){
		printf("trop court ! reessayer :");
		return 0;
	}
	else if(strlen(donnee)>size_max){
		printf("trop long ! reessayer :");
		return 0;
	}
	return 1;
}


_joueur *connexion(_jeux *jeu){
	system("cls");
	intro();
	printf("\n\n");
	char *nom_util=(char*)malloc(size_max*sizeof(char)),*mdp=(char*)malloc(size_max*sizeof(char));
	_joueur *joueur;
	int choix;
	printf("nom d'utilisateur :");
	scanf("%s",nom_util);
	printf("mot de passe :");
	scanf("%s",mdp);
	if(existe_nom_util(jeu,nom_util)==NULL){
		char Ch[2];Ch[1]='\0';
		printf("mot de passe ou nom d'utilisateur incorrecte !\n");
		printf("entre 1 pour reessayer ou 2 pour cree un compte\nvotre choix :");etiq8:
		scanf("%s",Ch);
		if(verifier_saisie(Ch[0])==-1 || strlen(Ch)>1){
			printf("ERREUR : le choix doit etre un chiffre !");_attendre(2);
			system("cls");intro();printf("\n\n");
			printf("mot de passe ou nom d'utilisateur incorrecte !\n");
			printf("entre 1 pour reessayer ou 2 pour cree un compte\nvotre choix :");goto etiq8;
		}
		choix=char_to_int(Ch[0]);
		if(choix!=1 && choix!=2){
			printf("choix invalide !");_attendre(2);
			system("cls");intro();printf("\n\n");
			printf("mot de passe ou nom d'utilisateur incorrecte !\n");
			printf("entre 1 pour reessayer ou 2 pour cree un compte\nvotre choix :");
			goto etiq8;
		}
		if(choix==1) joueur=connexion(jeu);
		else{
			system("cls");
			intro();
			printf("\n\n");
			joueur=creej(jeu);
			inserer(jeu,joueur);
			}
	}
	else{
		joueur=existe_nom_util(jeu,nom_util);
		if(strcmp(joueur->mdp,mdp)!=0){
			printf("mot de passe ou nom d'utilisateur incorrecte !\n");_attendre(2);
			joueur=connexion(jeu);
		}
	}
	system("cls");
	intro();
	printf("\n\n");
	return joueur;
}


_joueur *creej(_jeux *jeu){//pour cree un nouveau compte

	_joueur *joueur=(_joueur*)malloc(sizeof(_joueur));

	joueur->mdp=(char*)malloc(size_max*sizeof(char));
	joueur->nom=(char*)malloc(size_max*sizeof(char));
	joueur->nom_util=(char*)malloc(size_max*sizeof(char));
	joueur->prenom=(char*)malloc(size_max*sizeof(char));
	joueur->code=0;
	printf("entrer votre nom : ");
	scanf("%s",joueur->nom);
	while(valide_size_char(joueur->nom)==0)
		scanf("%s",joueur->nom);
	printf("entrer votre prenom : ");
	scanf("%s",joueur->prenom);
	while(valide_size_char(joueur->prenom)==0)
		scanf("%s",joueur->prenom);
	printf("choisir votre nom d'utilsateur : ");
	scanf("%s",joueur->nom_util);//il faut verifier qu'il n'existe pas...valide
	while(valide_size_char(joueur->nom_util)==0)
		scanf("%s",joueur->nom_util);
	while(existe_nom_util(jeu,joueur->nom_util)!=NULL){
		printf("ce nom d'utilisateur existe deja ! reessayer :");
		scanf("%s",joueur->nom_util);
	}
	printf("tapez un mot de passe : ");
	scanf("%s",joueur->mdp);
	verifier_mdp(joueur->mdp);
	joueur->score=0;
	return joueur;
}


void verifier_mdp(char *mdp){
	if(strlen(mdp)>size_max){
		printf("trop long\n");
		printf("reessayer :");
		scanf("%s",mdp);
		verifier_mdp(mdp);
	}
	else if(strlen(mdp)<size_min){
		printf("trop court\n");
		printf("reessayer :");
		scanf("%s",mdp);
		verifier_mdp(mdp);
	}
	return;
}


void inserer(_jeux *jeu,_joueur *joueur){//pour inserer le joueur dans la liste chainée
	int cpt=1;
	if(jeu->joueur==NULL) jeu->joueur=joueur;
	else{
		_jeux *nv=(_jeux*)malloc(sizeof(_jeux));
		nv->joueur=joueur;nv->suivant=NULL;
		while(jeu->suivant!=NULL){
			jeu=jeu->suivant;
			cpt++;
		}
		joueur->code=cpt;
		jeu->suivant=nv;
		}
}
void changer_mdp(_joueur *j){
	char *nv_mdp=(char*)malloc(15*sizeof(char));
	printf("nouveau mot de pass :");scanf("%s",nv_mdp);
	verifier_mdp(nv_mdp);
	strcpy(j->mdp,nv_mdp);
}
void changer_nom(_joueur *j){
	char *nv_nom=(char*)malloc(15*sizeof(char));
	printf("modifier le nom :");scanf("%s",nv_nom);
	verifier_mdp(nv_nom);
	strcpy(j->nom,nv_nom);
}
void changer_prenom(_joueur *j){
	char *nv_prenom=(char*)malloc(15*sizeof(char));
	printf("modifier le prenom :");scanf("%s",nv_prenom);
	verifier_mdp(nv_prenom);
	strcpy(j->prenom,nv_prenom);
}
void affj(_joueur *j){
	printf("nom : %s\n",j->nom);
	printf("prenom : %s\n",j->prenom);
	printf("nom d'utilisateur : %s\n",j->nom_util);
	printf("N d'inscription : %d\n",j->code);
	printf("score : %d\n",j->score);
}
void affl(_jeux *j){
	_jeux *ptr=j;
	while(ptr!=NULL){
		affj(ptr->joueur);
		printf("\n\n");
		ptr=ptr->suivant;}
}

void ecrire(_joueur *joueur,FILE *fichier){
	fprintf(fichier,"%d\n",joueur->code);
	fprintf(fichier,"%s\n%s\n%s\n%s\n",joueur->mdp,joueur->nom,joueur->nom_util,joueur->prenom);
	fprintf(fichier,"%d\n",joueur->score);
	fprintf(fichier,"\n");
}
void enregistrer(_jeux *jeux){
	FILE *fichier=NULL;
	fichier=fopen("BASE.txt","w");
	_jeux *ptr=jeux;
	while(ptr!=NULL){
		ecrire(ptr->joueur,fichier);
		ptr=ptr->suivant;
	}
	fclose(fichier);
}
_joueur *charger_joueur(FILE *fichier){
	_joueur *joueur=(_joueur*)malloc(sizeof(_joueur));int d;
	fscanf(fichier,"%d\n",&d);
	joueur->code=d;
	joueur->mdp=(char*)malloc(size_max*sizeof(char));fscanf(fichier,"%s\n",joueur->mdp);
	joueur->nom=(char*)malloc(size_max*sizeof(char));fscanf(fichier,"%s\n",joueur->nom);
	joueur->nom_util=(char*)malloc(size_max*sizeof(char));fscanf(fichier,"%s\n",joueur->nom_util);
	joueur->prenom=(char*)malloc(size_max*sizeof(char));fscanf(fichier,"%s\n",joueur->prenom);
	fscanf(fichier,"%d\n",&d);
	joueur->score=d;
	return joueur;
}
_jeux *charger_jeux(){
	FILE *fichier=NULL;
	fichier=fopen("BASE.txt","r");
	_jeux *jeux=(_jeux*)malloc(sizeof(_jeux));jeux->joueur=NULL;jeux->suivant=NULL;
	while(fgetc(fichier)!=EOF){
		fseek(fichier, -1, SEEK_CUR);
		inserer(jeux,charger_joueur(fichier));
	}
	fclose(fichier);
	return jeux;
}
int nbr_util(_jeux *jeu){
	int k=0;
	_jeux *ptr=jeu;
	while(ptr!=NULL){
		ptr=ptr->suivant;
		k++;}
	return k;
}
void ecrire_message(_joueur *j,char *msg){
	FILE *fichier=NULL;
	fichier=fopen("MESSAGES.txt","a");
	fprintf(fichier,"message de %s : %s\n\n",j->nom_util,msg);
	fclose(fichier);
}
void vider_messagerie(){
	FILE *fichier=NULL;
	fichier=fopen("MESSAGES.txt","w");fclose(fichier);
}
void afficher_messagerie(){
	FILE *fichier=NULL;
	fichier=fopen("MESSAGES.txt","r");
	char message[60];
	while(fgets(message,70,fichier)!=NULL) printf("%s",message);

    fclose(fichier);
}
#define TRUE 1
#define FALSE 0
void tri_a_bulle(int *t,int n){
	int j =0; int tmp =0; int en_desordre =1;
	while (en_desordre){
	en_desordre = FALSE;
	for(j =0; j < n-1; j++){
		if(t[j]<t[j+1]){
			tmp=t[j+1];t[j+1]=t[j];t[j]=tmp;
			en_desordre=TRUE;}
	}}}
int _in_list(int n,int *L,int taille_liste){
	int i,k=0;
	for(i=0;i<taille_liste;i++){
		if(L[i]==n) return 1;
	}
	return 0;
}
char *remplir(int d){
	char *ch=(char*)malloc(d*sizeof(char));int i;
	for(i=0;i<d;i++) ch[i]=' ';
	ch[d]='\0';
	return ch;
}
void classement(_jeux *jeu){
	int k,i=0,j=0,score;
	k=nbr_util(jeu);
	int *T=(int*)malloc(k*sizeof(int)),*L=(int*)malloc(k*sizeof(int));
	_jeux *ptr=jeu;
	while(ptr!=NULL){
		T[i]=ptr->joueur->score;
		i++;
		ptr=ptr->suivant;}
	tri_a_bulle(T,k);
	char *ch;
	while(j<k){
		score=T[j];
		ptr=jeu;
		while(ptr!=NULL){
			if(score==ptr->joueur->score){
				ch=remplir(32-strlen(ptr->joueur->nom_util));
				if(_in_list(ptr->joueur->code,L,j)==0){
					printf("%d-%s%s%d\n",j+1,ptr->joueur->nom_util,ch,score);
					L[j]=ptr->joueur->code;j++;}
			}
			ptr=ptr->suivant;}
	}
}
int char_to_int(char c){
	int d;
	d=c;
	return d-48;
}

int verifier_saisie(char d){
	if(isdigit(d)!=0){
		return char_to_int(d);
	}
	else return -1;
}

