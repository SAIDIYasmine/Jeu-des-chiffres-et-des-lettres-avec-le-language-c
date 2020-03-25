#include"intro.c"
#include"BASE_DONNEES.c"
#include"JEU_LETTRES.c"
#include"JEU_CHIFFRES.c"
	
int main(){
	char cc[2];cc[1]='\0';int c1,c;
	time_t t=time(NULL);
	struct tm tm=*localtime(&t);
	_jeux *jeu=charger_jeux();_joueur *joueur;
	etiq1:
	intro();
	printf("\n\n");
	printf("Bienvenu ! entrer :\n1-si vous etes administrateur\n2-si vous etes utilisateur\n3-n'importe quel chiffre pour sortir\n\nvotre choix :");
	scanf("%s",cc);
	if(verifier_saisie(cc[0])==-1 || strlen(cc)>1){
		printf("ERREUR : le choix doit etre un chiffre !");attendre(2);system("cls");
		goto etiq1;
	}
	c=char_to_int(cc[0]);
	system("cls");
	if(c==2){
		do{
		etiq2:
		intro();
		printf("\n\n");
		char cc1[2];cc1[1]='\0';
		printf("entrer :\n1-pour se connecter\n2-pour s'inscrire\nvotre choix :");
		scanf("%s",cc1);
		while(verifier_saisie(cc1[0])==-1 || strlen(cc1)>1){
			printf("ERREUR : le choix doit etre un chiffre !");attendre(2);system("cls");
			goto etiq2;
		}
		c1=char_to_int(cc1[0]);
		if(c1==1){
		system("cls");
		intro();
		printf("\n\n");
		joueur=connexion(jeu);}
		else if(c1==2){
		system("cls");
		intro();
		printf("\n\n");
		joueur=creej(jeu);
		inserer(jeu,joueur);
		printf("votre compte est cree avec succes !\n");attendre(2);system("cls");
		continue;
		}
		else{
			printf("choix invalide !");
			attendre(2);
		}
		system("cls");
		}while(c1!=1 && c1!=2);
		intro();
		printf("\n\n");
		printf("                                            bonjour %s %s !",joueur->nom,joueur->prenom);
		attendre(2);
		int ch1,ch2,ch3,v=0;char cch1[2],cch2[2];cch1[1]='\0';cch2[1]='\0';
		while(v==0){
		etiq3:
		system("cls");
		printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
		printf("1-jouer une partie solo\n2-jouer avec autre joueur\n3-acceder a votre profile\n4-afficher le classement des utilisateurs\n5-afficher les regles de jeu\n6-contactez nous\n7-deconnexion\n\nvotre choix :");
		scanf("%s",cch1);
		while(verifier_saisie(cch1[0])==-1 || strlen(cch1)>1){
			printf("ERREUR : le choix doit etre un chiffre !");attendre(2);goto etiq3;
		}
		ch1=char_to_int(cch1[0]);
		switch(ch1){
			case 1:{
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				printf("                                          JEU DES LETTRES");attendre(3);
				system("cls");
				int score1,score2;
				score1=jeu_lettres();
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				printf("                                          JEU DES CHIFFRES");attendre(3);system("cls");
				score2=jeu_chiffre();
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				printf("                             Partie terminee, votre score final est %d",score1+score2);attendre(3);
				joueur->score+=score1+score2;
				break;
			}
			case 2:{
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				printf("le 2eme joueur doit se connecter maintenant\n");attendre(4);
				_joueur *joueur1;
				joueur1=connexion(jeu);int score1,score2,score3,score4;
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				printf("                                          JEU DES LETTRES");attendre(3);system("cls");
				printf("%s va commencer ",joueur->nom_util);attendre(4);system("cls");score1=jeu_lettres();system("cls");
				printf("le tour de %s",joueur1->nom_util);attendre(5);system("cls");score3=jeu_lettres();system("cls");
				printf("                                          JEU DES CHIFFRES");attendre(3);system("cls");
				printf("%s va commencer ",joueur1->nom_util);attendre(4);system("cls");score4=jeu_chiffre();system("cls");
				printf("le tour de %s",joueur->nom_util);attendre(5);system("cls");score2=jeu_chiffre();system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				printf("                             Partie terminee\n\n%s : %d\n%s : %d\n\n",joueur->nom_util,score1+score2,joueur1->nom_util,score3+score4);attendre(2);
				if(score1+score2>score3+score4){
					printf("gangnat : %s ...Bravoo",joueur->nom_util);
					joueur->score+=score1+score2;}
				else if(score1+score2<score3+score4){
					printf("gangnat : %s ...Bravoo",joueur1->nom_util);
					joueur1->score+=score3+score4;}
				else{
					printf("egalitée :) \n");
					joueur->score+=score1+score2;
					joueur1->score+=score3+score4;}
				attendre(5);	
				break;
			}
			case 3:{
					etiq4:
					system("cls");
					printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
					printf("vos information :\n");
					affj(joueur);printf("\n\n");
					printf("1-changer votre mot de pass\n2-modifier votre nom\n3-modifier votre prenom\n4-ou n'import quel chiffre pour revenir au menu principal\n\nvotre choix :");
					scanf("%s",cch2);
					while(verifier_saisie(cch2[0])==-1 || strlen(cch2)>1){
						printf("ERREUR : le choix doit etre un chiffre !");attendre(2);
						goto etiq4;
					}
					ch2=char_to_int(cch2[0]);
					switch(ch2){
						case 1 :{
							system("cls");
							printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
							char *actuel=(char*)malloc(15*sizeof(char));
							printf("il faut entrer votre mdp pour cettre operation : ");scanf("%s",actuel);
							if(strcmp(actuel,joueur->mdp)==0){
								changer_mdp(joueur);printf("mot de pass change avec succes !");attendre(2);goto etiq4;
							}
							else{
								printf("mot de pass incorrecte !!!!");
								attendre(2);goto etiq4;
							}
							break;
						}
						case 2 :{
							system("cls");
							printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
							char *actuel=(char*)malloc(15*sizeof(char));
							printf("il faut entrer votre mdp pour cettre operation : ");scanf("%s",actuel);
							if(strcmp(actuel,joueur->mdp)==0){
								changer_nom(joueur);printf("nom change avec succes !");attendre(2);goto etiq4;
							}
							else{
								printf("mot de pass incorrecte !!!!");
								attendre(2);goto etiq4;
							}
							break;
						}
						case 3 :{
							system("cls");
							printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
							char *actuel=(char*)malloc(15*sizeof(char));
							printf("il faut entrer votre mdp pour cettre operation : ");scanf("%s",actuel);
							if(strcmp(actuel,joueur->mdp)==0){
								changer_prenom(joueur);printf("prenom change avec succes !");attendre(2);goto etiq4;
							}
							else{
								printf("mot de pass incorrecte !!!!");
								attendre(2);goto etiq4;
							}
							break;
						}
						default : break;
					}
					break;
			}
			case 4 :{
				char cc[2];
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				classement(jeu);printf("\nappuyez sur n'importe quelle touche pour revenir au menu principal : ");scanf("%s",cc);
				break;
			}
			case 5 :{
				char ca[2];
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				regles_lettres();
				regles_chiffre();
				printf("appuyez sur n'importe quelle touche pour revenir au menu principal : ");scanf("%s",ca);
				break;
			}
			case 6:{
				system("cls");
				printf("| %s | score : %d |_____________________________________________________________________| %d / %d / %d |\n\n",joueur->nom_util,joueur->score,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
				printf("vous pouvez seulement ecrire un message de 60 lettres\nattention !les mots doivent etres separees par '_' et pas des espaces!!\n\nvotres message :");
				char *message=(char*)malloc(60*sizeof(char));scanf("%s",message);
				if(strlen(message)>60) message[60]='\0';ecrire_message(joueur,message);
				printf("\nmerci pour votre message !");attendre(2);
				break;
			}
			case 7 :{v=1;
					printf("au revoir %s %s",joueur->nom,joueur->prenom);attendre(2);system("cls");goto etiq1;
					break;
			}
			default :{printf("choix invalid !");attendre(3);
				break;
			}
		}}
	}
	
	else if(c==1){
		int a=1;
		intro();
		printf("\n\n");
		_admin *admin=adminstr();
		char *nom=(char*)malloc(30*sizeof(char)),*mdp=(char*)malloc(30*sizeof(char));
		while(a==1){
		system("cls");intro();printf("\n\n");
		printf("nom : ");scanf("%s",nom);printf("mot de pass : ");scanf("%s",mdp);
		if(strcmp(nom,admin->nom)==0 && strcmp(mdp,admin->mdp)==0){
				int C1,C2,C3,v=1;a=2;char CC1[2],CC2[2];CC1[1]='\0';CC2[1]='\0';
				while(v==1){
					etiq6:
					system("cls");
					printf("| MENU ADMIN : %s|_____________________________________________________________________| %d / %d / %d |\n\n",admin->nom,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
					printf("1-afficher tout les informations des utilisateurs\n2-ajouter un mot au dictionnaire\n3-acceder a votre boite de messages\n4-deconnecter\n\nvotre choix :");
					scanf("%s",CC1);
					while(verifier_saisie(CC1[0])==-1 || strlen(CC1)>1){
						printf("ERREUR : le choix doit etre un chiffre !");attendre(2);goto etiq6;
					}
					C1=char_to_int(CC1[0]);
					switch(C1){
						case 1:{
							int aa[2];
							system("cls");
							printf("| MENU ADMIN : %s|_____________________________________________________________________| %d / %d / %d |\n\n",admin->nom,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
							affl(jeu);printf("\n| nombre totale des utilisateurs : %d|\n",nbr_util(jeu));
							printf("appuyez sur n'importe quelle touche pour revenir au menu principal : ");
							scanf("%s",aa);
							break;
						}
						case 2:{
							system("cls");
							printf("| MENU ADMIN : %s|_____________________________________________________________________| %d / %d / %d |\n\n",admin->nom,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
							char *mot=(char*)malloc(10*sizeof(char));
							printf("entre le mot a ajouter :");scanf("%s",mot);
							if(ajouter_mot_dict(mot)==0){
								printf("ce mot existe deja !");attendre(3);}
							else{
								printf("le mot a ete ajoute avec succes !");attendre(3);}
							break;
						}
						case 3:{

							char aa[2];
							etiq7:
							system("cls");
							printf("| MENU ADMIN : %s|_____________________________________________________________________| %d / %d / %d |\n\n",admin->nom,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
							printf("1-lire votre messagerie\n2-vider la boite des messages\n\nvotre choix : ");
							scanf("%s",CC2);
							while(verifier_saisie(CC2[0])==-1 || strlen(CC2)>1){
								printf("ERREUR : le choix doit etre un chiffre !");attendre(2);goto etiq7;
							}
							C2=char_to_int(CC2[0]);
							while(C2!=1 && C2!=2){
								printf("choix invalid !");attendre(2);goto etiq7;}
							if(C2==1){
								system("cls");
								printf("| MENU ADMIN : %s|_____________________________________________________________________| %d / %d / %d |\n\n",admin->nom,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
								afficher_messagerie();
								printf("\nappuez sur un n'import quelle touche pour revenir au menu principal : ");
								scanf("%s",aa);}
							else{
								system("cls");
								printf("| MENU ADMIN : %s|_____________________________________________________________________| %d / %d / %d |\n\n",admin->nom,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
								vider_messagerie();
								printf("votre boite de message a ete videe !");attendre(3);								
							}
							break;
						}
						case 4:{
							v=0;printf("au revoir %s",admin->nom);attendre(2);system("cls");goto etiq1;
							break;
						}
						default:{
							printf("choix invalid !");attendre(2);
							break;
						}}
				}
				}
				
		else{
			char aa[2];aa[1]='\0';
			etiq5:
			system("cls");
			intro();
			printf("\n\n");
			printf("donnees incorrectes !!\n1-reessayer\n2-quitter\n\nvotre choix :");scanf("%s",aa);
			while(verifier_saisie(aa[0])==-1 || strlen(aa)>1){
				printf("ERREUR : le choix doit etre un chiffre !");attendre(2);
				goto etiq5;
			}
			a=char_to_int(aa[0]);
			while(a!=1 && a!=2){
				printf("choix invalid!");attendre(2);system("cls");
				goto etiq5;}
			}
			if(a==2){
				system("cls");goto etiq1;
			}
			
		}
		
	}
	else{
	system("cls");
	intro();
	printf("\n\n");printf("merci ! A la prochaine :) !");
	}
	
	enregistrer(jeu);
	
}
