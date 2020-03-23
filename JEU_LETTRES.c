#include"JEU_LETTRES.h"
//les fonctions utilisée
void regles_lettres(){
	printf("                              ___________________________\n ");
	printf("                            |      JEU DES LETTRES      |\n  ");
	printf("                           |___________________________|\n");
	printf("\n\n");
	printf("     les regles sont trop simples :      \n");
	printf("        +un nombre de lettres est suggere selon votre choix (2<=choix<=10)\n");
	printf("        +vous devez saisir lettre par lettre\n");
	printf("        +vous pouvez en tout moment annulez votre reponse (tout vos lettres choisis seront ecrasees)\n");
	printf("        +le nombre de points obtenue = nombre de lettre de mots trouve..si le mot n'existe pas vous obtenez à :)\n");
	printf("        +le temps de chaque partie :\n");
	printf("            -si le nombre de lettres suggerees est 9 ou 8  : temps = 60sec\n");
	printf("            -si le nombre de lettres suggerees est 7,6 ou 5   : temps = 40sec\n");
	printf("            -si le nombre de lettres suggerees est 4,3 ou 2   : temps = 20sec\n");

	
}
int _rand(int a,int b){//generation d'un nombre aleatoire compris entre a et b
	return rand()%(b-a) +a;
}
char rand_char(){//generation d'une lettre aleatoire
	char c;
	c=_rand(65,90);
	return c;
}
char *rand_seq(){//generation de sequence de 10 lettres aleatoires
	char *seq=(char*)malloc(10*sizeof(char)),i;seq[10]='\0';
	for(i=0;i<10;i++){
		*(seq+i)=rand_char();
	}
	return seq;
}
char *mot(FILE *fichier,int taille_mot){
	char *mot=(char*)malloc(taille_mot*sizeof(char)),actuel;int k=0;mot[taille_mot]='\0';
	actuel=getc(fichier);
	if(actuel==EOF) return NULL;
	while(actuel!=' '){
		mot[k]=actuel;
		actuel=getc(fichier);
		k++;
	}
	return mot;	
}
FILE *ouvrir(int a){
	FILE *fichier=NULL;
	switch(a){
		case 2 : fichier=fopen("2.txt","r+");break;
		case 3 : fichier=fopen("3.txt","r+");break;
		case 4 : fichier=fopen("4.txt","r+");break;
		case 5 : fichier=fopen("5.txt","r+");break;
		case 6 : fichier=fopen("6.txt","r+");break;
		case 7 : fichier=fopen("7.txt","r+");break;
		case 8 : fichier=fopen("8.txt","r+");break;
		case 9 : fichier=fopen("9.txt","r+");break;
		case 10 : fichier=fopen("10.txt","r+");break;
		default : return NULL;
	}
	return fichier;
}
int existe_en_dict(char *chaine){// verfier si un mot existe bien, revoie 1 si oui 0 sinon
	FILE *fichier;int taille=strlen(chaine);
	char *mots,*reserve=(char*)malloc(taille*sizeof(char));
	fichier=ouvrir(taille);
	mots=mot(fichier,taille);
	while(mots!=NULL){
		if(strcmp(chaine,mots)==0){
			fclose(fichier);
			return 1;
		}
		mots=mot(fichier,taille);
	}
	fclose(fichier);
	return 0;	
}
int ajouter_mot_dict(char *nouv){
	int d=strlen(nouv);
	FILE *fichier=NULL;
	fichier=ouvrir(d);
	if(existe_en_dict(nouv)==1){
		fclose(fichier);
		return 0;}
	fseek(fichier, 0, SEEK_END);
	fprintf(fichier,"%s ",nouv);
	fclose(fichier);
	return 1;
}
int occurence(char c,char *chaine){
	int k=0,i;
	for(i=0;i<strlen(chaine);i++){
		if(chaine[i]==c) k++;
	}
	return k;
}
int verifier_lettres(char *chaine1,char *chaine2){//pour verifier si toute les lettres de chaine 1 existent dans chaine2
	int i,a,b;                                        //revoi 1 si oui 0 sinon
	for(i=0;i<strlen(chaine1);i++){
		a=occurence(chaine1[i],chaine1);
		b=occurence(chaine1[i],chaine2);
		if(a>b || b==0) return 0;
	}
	return 1;
}
int nbre_mots_dict(int taille){
	FILE *fichier;char *word;int k=1;
	fichier=ouvrir(taille);
	word=mot(fichier,taille);
	while(word!=NULL){
		word=mot(fichier,taille);
		k++;}
	return k;
	fclose(fichier);
}
char *rand_word(int taille){
	srand(time(NULL));
	FILE *fichier;char *word;int k=nbre_mots_dict(taille),i=_rand(0,k),j=0;
	fichier=ouvrir(taille);
	word=mot(fichier,taille);
	while(j!=i){
		word=mot(fichier,taille);
		j++;
	}
	fclose(fichier);
	return word;
}
char *permuter(char *word){
	int k,i,taille=strlen(word);char inter;
	char *res=(char*)malloc(taille*sizeof(char));
	strcpy(res,word);
	for(i=0;i<taille;i++){
		k=_rand(0,taille-1);
		inter=*(res+i);
		*(res+i)=*(res+k);
		*(res+k)=inter;
	}
	return res;
}
int in_list(int n,int *L,int taille_liste){
	int i,k=0;
	for(i=0;i<taille_liste;i++){
		if(L[i]==n) return 1;
	}
	return 0;
}
int pos_occ(char c,char *chaine){
	int i,k=strlen(chaine);
	for(i=0;i<k;i++){
		if(chaine[i]==c) return i;
	}
	return -1;
}
void aff_instruc(){
	printf("________________________________JEU DES LETTRES________________________________\n\n");
	printf("instructions a suivre :\n");
	printf("1-le temps de jeu depends du niveau choisi\n");
	printf("2-attention les lettres du jeu sont toute en Majiscule!\n");
	printf("3-vous pouvez en tout moment effacer votre reponse en appuyant sur 's' (Miniscule!)\n");
	printf("4-si vous voulez valider votre repense appuyez sur 'v' (Miniscule!)\n\n");
	printf("___________________________________________________________________________________\n");
}
void attendre(int t){
	time_t debut,fin;
	time(&debut);
	time(&fin);
	while(difftime(fin,debut)<t) time(&fin);
}
int jeu_lettres(){
	srand(time(NULL));
	time_t debut,fin;
	int nbr,cpt=0,score=0,list_pos[10],taille_list=0;float temps;char nbrr[2];nbrr[1]='\0';
	etiq9:
	aff_instruc();
	printf("\n");
	printf("choisir le nombre de lettres a suggerer ( entre 2 et 9 ) :");
	scanf("%s",nbrr);
	if(_verifier_saisie(nbrr[0])==-1 || strlen(nbrr)>2){
		printf("ERREUR : le choix doit etre un chiffre !");attendre(2);system("cls");goto etiq9;
	}
	nbr=_char_to_int(nbrr[0]);
	if(nbr<2 || nbr>10){
		printf("choix invalid !");attendre(2);system("cls");goto etiq9;
	}
	switch(nbr){
		case 10 :
		case 9 :
		case 8 :temps=60;break;
		case 7 :
		case 6 :
		case 5 :temps=40;break;
		case 4 :
		case 3 :
		case 2 :temps=20;break;
	}
	char *lettres_sugg,*sol=rand_word(nbr),choix_utilisateur[nbr],choix[2],lettres_copie[nbr];
	lettres_sugg=permuter(sol);
	strcpy(lettres_copie,lettres_sugg);
	printf("c'est parti !");
	attendre(2);
	system("cls");
	time(&debut);
	time(&fin);
	//debut de jeu
	while(difftime(fin,debut)<temps){
		aff_instruc();
		printf("                                                                 |temps restant: %.0f|\n\n",temps-difftime(fin,debut));

		printf("lettres suggerees : ");int i;
		for(i=0;i<nbr;i++){
			if(in_list(i,list_pos,taille_list)==0) printf("%c  ",lettres_sugg[i]);
			else printf("-  ");
			}
		printf("\n");
		if(cpt==0) printf("votre mot :");
		else printf("votre mot : %s\n",choix_utilisateur);
		printf("\n");
		printf("votre choix :");
		scanf("%s",choix);
		time(&fin);
		if(difftime(fin,debut)>50) break;
		if(choix[0]=='v') break;
		if(choix[0]=='s'){
			strcpy(lettres_copie,lettres_sugg);
			taille_list=0;
			cpt=0;
			choix_utilisateur[cpt]='\0';
			system("cls");
			time(&fin);
			continue;
		}
		if(nbr==cpt){
				printf("vous avez epuise toute les lettres!");
				attendre(2);
				time(&fin);
				system("cls");
				continue;
		}
		choix_utilisateur[cpt]=choix[0];choix_utilisateur[cpt+1]='\0';
		if(verifier_lettres(choix_utilisateur,lettres_sugg)!=1){
			printf("choix invalid!");
			choix_utilisateur[cpt]='\0';
			attendre(2);
			system("cls");
			time(&fin);
			continue;}
		else{
			cpt=cpt+1;
			list_pos[taille_list]=pos_occ(choix[0],lettres_copie);
			lettres_copie[list_pos[taille_list]]='-';
			taille_list++;
			}
		time(&fin);
		system("cls");
		}
	printf("\n");
	if(choix[0]!='v') printf("temps termine !\n");
	if(cpt==0){
		printf("vous n'avez rien trouve !\n");
		score=0;}
	else if(existe_en_dict(choix_utilisateur)==1){
			printf("%s existe !\n",choix_utilisateur);
			score=strlen(choix_utilisateur);}
	else{
		printf("%s n'existe pas\n",choix_utilisateur);
		score=0;
		}
	printf("voici la solution optimale : %s\n\n",sol);
	printf("| SCORE : %d |",score);
	attendre(6);
	return score;
}
int _char_to_int(char c){
	int d;
	d=c;
	return d-48;
}

int _verifier_saisie(char d){
	if(isdigit(d)!=0){
		return char_to_int(d);
	}
	else return -1;
}
