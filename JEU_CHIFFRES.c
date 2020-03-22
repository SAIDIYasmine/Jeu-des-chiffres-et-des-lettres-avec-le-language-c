#include "JEU_CHIFFRES.h"
int generer_un_nombre_aleatoire(int inf,int sup)
{
	int a;
	a=(rand()%(sup-inf+1))+inf;
	return a;
}
int _min(int a ,int b){
	if (a<b) return a ;
	else return b;
}
int _max(int a,int b){
	if (a>b) return a;
	else return b;
}
int menu_operande1(int *l,int choix_operande1){
	int operande1,i;
	for(i=0;i<N;i++){
	    if(choix_operande1==i+1) operande1=l[i];
	}
	return operande1;
}
int menu_operande2(int *l,int choix_operande2){
	int operande2,i;
	for(i=0;i<N;i++){
	    if(choix_operande2==i+1) operande2=l[i];
	}
	return operande2;
}
int fonction_resultat(int operande1,int operande2,int choix_operation){
	int resultat;
	switch (choix_operation){
		case 1 : resultat=operande1+operande2;break;
		case 2 : resultat=_max(operande1,operande2)-_min(operande1,operande2);break;
		case 3 : resultat=operande1*operande2;break;
		case 4 : resultat=_max(operande1,operande2)/_min(operande1,operande2);break;
	}
	return resultat;
}
void regles_chiffre(){
	printf("                              ___________________________\n ");
	printf("                            |      JEU DES CHIFFRES     |\n  ");
	printf("                           |___________________________|\n");
	printf("\n\n");
	printf("     les regles sont trop simples :      \n");
	printf("        +un chiffre est suggere selon votre choix <1000 ou >=1000\n");
	printf("        +le nombre de points obtenue = 10 si vous trouvez le nombre\n");
    printf("                                       7 si vous trouvez un nombre avec une marge inferieure a 50\n");
    printf("                                       0 si vous avez rien trouver\n");
    printf("        +il y a des cas pariculiers pour le calcul :\n");
    printf("            -pour la division on divise toujours sur le plus petit des nombres pour eviter le zero\n ");
    printf("            -pour la soustraction on soustrait toujours depuis le plus grand nombre pour eviter les nombres negatifs\n ");
    printf("        +le temps de chaque partie :\n");
	printf("            -si le nombre est inferieur a 1000  : temps = 40sec\n");
	printf("            -si le nombre est superieur a 1000  : temps = 60sec\n");
}
void afficher_instruction(){
	printf("________________________________JEU DES CHIFFRES_______________________________\n\n");
	printf("instructions a suivre :\n");
	printf("1-le temps de jeu depends du niveau choisi\n");
	printf("2-si vous voulez valider votre repense entrer '0'\n\n");
	printf("___________________________________________________________________________________\n");
}
void attendez(int d){
	time_t debut,fin;
	time(&debut);
	time(&fin);
	while(difftime(fin,debut)<d) time(&fin);
}
int jeu_chiffre()
{
    srand(time(NULL));
	int i,score,temp,choix,resultat_joueur,diff,x;char cchoix[2];cchoix[1]='\0';
	int l[N];
	time_t debut,fin;
	etiq13:
	afficher_instruction();
    printf("entrer : \n1-pour choisir un nombre inferieur a 1000\n2-pour choisir un nombre superieur ou egale a 1000\n\nchoix : ");
    scanf("%s",cchoix);
    while(verifier_saisie_(cchoix[0])==-1 || strlen(cchoix)>1){
    	printf("ERREUR : le choix doit etre un chiffre  !");attendez(2);system("cls");goto etiq13;
	}
	choix=char_to_int_(cchoix[0]);
    while(choix!=1 && choix!=2){
        printf("choix invalid ! ");attendez(2);system("cls");goto etiq13;
    }
    if (choix==1){
            temp=40;
            do{
                for (i=0;i<N;i++) l[i]=generer_un_nombre_aleatoire(1,100);
            x=generer_le_nombre(l);
            } while(x>=1000 || x<100);
    }
    else{
            temp=60;
            do{
                for (i=0;i<N;i++) l[i]=generer_un_nombre_aleatoire(1,100);
            x=generer_le_nombre(l);
            } while(x<1000 || x<100);
    }
    int inter,resultat,operande1,operande2,choix_operande1,choix_operande2,choix_operation,k=0;char cc1[2],cc2[2],cc3[2];cc1[1]='\0';cc2[1]='\0';cc3[1]='\0';
    int proposition[3*N],i_proposition=0;
    int n=N;
    time_t debut2,debut1,debut3,fin3,fin1,fin2;
    time(&debut2);
    time(&fin2);

    int l1[N];
    for(i=0;i<N;i++) l1[i]=l[i];
    etiq14:
    i_proposition=0;
    system("cls");
    do{

    	printf("votre nombre est : %d \n",x);
        printf("essayer de trouver le nombre le plus proche de cette nombre en utilisant ces nombres : \n");
        for(i=0;i<n;i++) printf("%d ",l1[i]);
        printf("\n ");
    	printf("______________________________________MENU______________________________________\n");
        if(difftime(fin2,debut2)<temp) printf("                                                             |temps restant : %.0f|\n",temp-difftime(fin2,debut2));
        else break;
        printf("entrer :");
        for (i=0;i<N-n;i++) printf("\n");
        for(i=0;i<n;i++) printf("\n%d pour choisir %d",i+1,l1[i]);
        printf("\nentrer :\n'1' pour choisir la somme\n'2' pour choisir la soustraction\n'3' pour choisir la multiplication\n'4' pour choisir la division\n");
        printf("\n\n");
        if(i_proposition>2){
        printf("les operation effectuees : \n\n");
        printf("   ");
        for (i=0;i<i_proposition-2;i+=4){
            char op;
            switch (proposition[i+1]){
                case 1 : op='+' ; break ;
                case 2 : {op='-'; if (proposition[i]<proposition[i+2]){inter=proposition[i];proposition[i]=proposition[i+2];proposition[i+2]=inter;}; }; break ;
                case 3 : op='*';  break ;
                case 4 : {op='/'; if (proposition[i]<proposition[i+2]){inter=proposition[i];proposition[i]=proposition[i+2];proposition[i+2]=inter;}; }; break ;
            }
            printf("   %d %c %d = %d   |",proposition[i],op,proposition[i+2],proposition[i+3]);
        }
        printf("\n\n");
        }
        else  printf("les operation effectuees : \n\n\n");
        printf("choix du premiere operande : ");
        scanf("%s",cc1);
        while(verifier_saisie_(cc1[0])==-1 || strlen(cc1)>1){
    		printf("ERREUR : le choix doit etre un chiffre  !");attendez(2);time(&fin2);system("cls");goto etiq14;
		}
		choix_operande1=char_to_int_(cc1[0]);
        time(&fin2);
        if(choix_operande1==0 || difftime(fin2, debut2)>temp) break;
        k++;
        while(choix_operande1<0 || choix_operande1>5){
        printf("choix invalid ! ");attendez(2);time(&fin2);system("cls");goto etiq14;
        }
        proposition[i_proposition]=l1[choix_operande1-1];
        i_proposition++;
        operande1=menu_operande1(l1,choix_operande1);
        printf("choix de l'operation : ");
        scanf("%s",cc3);
        while(verifier_saisie_(cc3[0])==-1 || strlen(cc3)>1){
    	printf("ERREUR : le choix doit etre un chiffre  !");attendez(2);time(&fin2);system("cls");goto etiq14;
		}
		choix_operation=char_to_int_(cc3[0]);
        time(&fin2);
        if( choix_operation==0 || difftime(fin2, debut2)>temp) break;
        while(choix_operation<0 || choix_operation>4){
            printf("choix invalid !");attendez(2);time(&fin2);system("cls");goto etiq14;
        }
        proposition[i_proposition]=choix_operation;
        i_proposition++;
        printf("choix du dexieme operande : ");
        time(&fin2);
        scanf("%s",cc2);
        while(verifier_saisie_(cc2[0])==-1 || strlen(cc2)>1){
    	printf("ERREUR : le choix doit etre un chiffre  !");attendez(2);time(&fin2);system("cls");goto etiq14;
		}
		choix_operande2=char_to_int_(cc2[0]);
        if (choix_operande2==0 || difftime(fin2, debut2)>temp) break;
        while(choix_operande2<0 || choix_operande2>5 || choix_operande2==choix_operande1){
			printf("choix invalid !");attendez(2);time(&fin2);system("cls");goto etiq14;
        }
        proposition[i_proposition]=l1[choix_operande2-1];
        i_proposition++;
        operande2=menu_operande2(l1,choix_operande2);
        resultat=fonction_resultat(operande1,operande2,choix_operation);
        proposition[i_proposition]=resultat;
        i_proposition++;
        l1[choix_operande1-1]=resultat;
        inter=l1[choix_operande2-1];
        l1[choix_operande2-1]=l1[n-1];
        l1[n-1]=inter;
        n--;
        time(&fin2);
        system("cls");
        k++;
   }while(resultat!=x && difftime(fin2, debut2)<temp && n>1);
   system("cls");
   if(k==0) return 0;
   else if (k==1) return operande1;
   else if(resultat==x) {printf("bravo vous avez trouvez la solution");return -1;}
   else if(difftime(fin2,debut2)>temp) printf("\n!!!!ooooops le temps est termine!!!!\n");
   else if(n<=1) printf("vous avez terminer \n");
   printf("\n");
	if(resultat==0){ printf("vouz avez rien saisi!!!");score=0;}
	else if (resultat==-1) score=10;
	else {
            printf("votre resultat final est : %d or votre nombre initial est %d \n",resultat,x);
            if (abs(resultat-x)<=50) score=7;
            else score=0;
	}
	printf("\n\nla solution proposee est :\n");
	print(l);
	attendez(8);
	return score;
}
int generer_le_nombre(int *l){
    int x,mi1,ma1,mi2,ma2;
    x=(l[0]+l[1])*l[2];
    mi1=_min(x,l[3]);
    ma1=_max(x,l[3]);
    x=ma1-mi1;
    mi2=_min(x,l[4]);
    ma2=_max(x,l[4]);
    x=ma2/mi2;
    return x;
}
void print(int *l){
    printf("%d + %d = %d\n",l[0],l[1],l[0]+l[1]);
    int x,mi1,ma1,mi2,ma2;
    x=(l[0]+l[1])*l[2];
    printf("%d * %d = %d\n",l[0]+l[1],l[2],x);
    mi1=_min(x,l[3]);
    ma1=_max(x,l[3]);
    x=ma1-mi1;
    printf("%d - %d = %d\n",ma1,mi1,x);
    mi2=_min(x,l[4]);
    ma2=_max(x,l[4]);
    x=ma2/mi2;
    printf("%d / %d = %d",ma2,mi2,x);
}
int char_to_int_(char c){
	int d;
	d=c;
	return d-48;
}

int verifier_saisie_(char d){
	if(isdigit(d)!=0){
		return char_to_int(d);
	}
	else return -1;
}


