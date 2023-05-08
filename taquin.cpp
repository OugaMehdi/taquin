#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "taquin.h"

using namespace std;



Taquin creerTaquin(int matrice[3][3]){
	int caseVideCol, caseVideRow;
	Taquin taquin;
	taquin.h = 0;
	memcpy(taquin.matrice, matrice, sizeof(taquin.matrice));
	printf("Entrez l'emplacement de la case vide (ligne) : ");
    scanf("%d", &caseVideRow);
    taquin.espaceVideRow = caseVideRow;
    printf("Entrez l'emplacement de la case vide (colonne) : ");
    scanf("%d", &caseVideCol);
    taquin.espaceVideCol = caseVideCol;
    taquin.matrice[taquin.espaceVideRow][taquin.espaceVideCol] = 0;
    printf("Voici le taquin : \n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d \t", taquin.matrice[i][j]);
        }
        printf("\n");
    }
    return taquin;
}

Noeud* creerNoeud(int c, Taquin t, Noeud* parent){
	Noeud* n = (Noeud*) malloc(sizeof(Noeud));
	n->c = c;
	n->parent = parent;
	n->taquin = t;
	return n;
}

bool taquinEgal(Taquin t1, Taquin t2){
	for(int i=0; i<3 ; i++ ){
		for(int j = 0; j<3; j++){
			if(t1.matrice[i][j] != t2.matrice[i][j]){
				return false;
			}
		}
	}
	return true;
}

int pieceMalPlacee(Taquin taquin, Taquin taquinBut){
	int malPlacee=0;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if((taquin.matrice[i][j] != 0) && (taquin.matrice[i][j] != taquinBut.matrice[i][j])){
				malPlacee++;
			}
		}
	}
	return malPlacee;
}

void echanger(Taquin& taquin, int row1, int col1, int row2, int col2){
	int temp = taquin.matrice[row1][col1];
	taquin.matrice[row1][col1]=taquin.matrice[row2][col2];
	taquin.matrice[row2][col2] = temp;
}

static bool peutDeplacerHaut(Taquin taquin){
	return taquin.espaceVideRow>0;
}

static bool peutDeplacerBas(Taquin taquin){
	return taquin.espaceVideRow < (taille-1);
}

static bool peutDeplacerGauche(Taquin taquin){
	return taquin.espaceVideCol>0;
}

static bool peutDeplacerDroite(Taquin taquin){
	return taquin.espaceVideCol < (taille-1);
}

static void deplacerHaut(Taquin& t){
	swap(t.matrice[t.espaceVideRow][t.espaceVideCol],t.matrice[t.espaceVideRow-1][t.espaceVideCol]);
	t.espaceVideRow--;
}

static void deplacerBas(Taquin& t){
	swap(t.matrice[t.espaceVideRow][t.espaceVideCol],t.matrice[t.espaceVideRow+1][t.espaceVideCol]);
	t.espaceVideRow++;
}

static void deplacerGauche(Taquin& t){
	swap(t.matrice[t.espaceVideRow][t.espaceVideCol],t.matrice[t.espaceVideRow][t.espaceVideCol-1]);
	t.espaceVideCol--;
}

static void deplacerDroite(Taquin& t){
	swap(t.matrice[t.espaceVideRow][t.espaceVideCol],t.matrice[t.espaceVideRow][t.espaceVideCol+1]);
	t.espaceVideCol++;
}

Taquin deplacement(Taquin t, int direction){
    Taquin t2 = t;
////	memcpy(t2.matrice,t.matrice,sizeof(t.matrice));
	int row = t2.espaceVideRow;
	int col = t2.espaceVideCol;
	switch (direction){
		case 0:
			if(row==0){
				return t;
			}else{
				deplacerHaut(t2);
			}
			break;
		case 1:
			if(row==2){
				return t;
			}else{
				deplacerBas(t2);
			}
			break;
		case 2:
			if(col==0){
				return t;
			}else{
				deplacerGauche(t2);
			}
			break;
		case 3:
			if(col==2){
				return t;
			}else{
				deplacerDroite(t2);
			}
			break;	
	}
	return t2;
}


static void afficherChemin(Noeud* n){
	vector<Noeud*> chemin;
		while(n != NULL){
			chemin.push_back(n);
			n = n->parent;
		}
		reverse(chemin.begin(),chemin.end());
		printf("---------Chemin trouve---------\n");
		for(int k=0; k<chemin.size(); k++ ){
			printf("\nEtape %d\n",k);
			printf("Matrice : \n");
			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++){
					printf("%d\t",chemin[k]->taquin.matrice[i][j]);
				}
				printf("\n");
			}
			printf("Cout: %d  Heuristique: %d\n",chemin[k]->c,chemin[k]->taquin.h);
		}
		
}


void explorationAEtoile(Noeud* noeudInit, Noeud* noeudBut){
	noeudInit->taquin.h = pieceMalPlacee(noeudInit->taquin, noeudBut->taquin);
	Noeud* noeudChercher = noeudBut;
	Noeud* noeudExtrait = noeudInit;
	priority_queue<Noeud*, vector<Noeud*>, comparerNoeuds> frontiere;
	vector<Taquin> visite;
	frontiere.push(noeudExtrait);
	while(!frontiere.empty()){
		memcpy(&noeudExtrait,&(frontiere.top()), sizeof(Noeud));
		frontiere.pop();
        visite.push_back(noeudExtrait->taquin);
		if (taquinEgal(noeudExtrait->taquin,noeudChercher->taquin))
        {
			afficherChemin(noeudExtrait);
            return;
        }
		  for(int i = 0; i<4; i++ ){
		  	Noeud* nvNoeud = creerNoeud(noeudExtrait->c,noeudExtrait->taquin,noeudExtrait->parent);
            nvNoeud->taquin = deplacement(nvNoeud->taquin,i);
            nvNoeud->c++;
            nvNoeud->taquin.h = pieceMalPlacee(nvNoeud->taquin, noeudBut->taquin);
           	nvNoeud->parent = noeudExtrait;
            if (!(find(visite.begin(), visite.end(), nvNoeud->taquin) != visite.end()))
            {
                frontiere.push(nvNoeud);
            }
		  }
	}
	
}



static Resultat EPL_CONTOUR(Noeud* noeudCourant, Noeud* noeudBut, int f_limite){
	int next_f = INT_MAX;
	noeudCourant->taquin.h = pieceMalPlacee(noeudCourant->taquin, noeudBut->taquin);
	int f= (noeudCourant->c) + (noeudCourant->taquin.h);
	if(f > f_limite){
		return {NULL,f};
	}
	if(taquinEgal(noeudCourant->taquin,noeudBut->taquin)){
		return {noeudCourant,f_limite};
	}
	for(int i = 0; i<4; i++ ){
		Noeud* nvNoeud = creerNoeud(noeudCourant->c,noeudCourant->taquin,noeudCourant->parent);
        nvNoeud->taquin = deplacement(nvNoeud->taquin,i);
        nvNoeud->c++;
		nvNoeud->taquin.h = pieceMalPlacee(nvNoeud->taquin, noeudBut->taquin);
       	nvNoeud->parent = noeudCourant;
        Resultat res = EPL_CONTOUR(nvNoeud, noeudBut, f_limite);
        if(res.noeud != NULL) return res;
        next_f = min(next_f,res.limite);
    }
	return {NULL,next_f};
}

void idaEtoile(Noeud* noeudInit, Noeud* noeudBut, int limite_max) {
	int f_limite=0;
	noeudInit->taquin.h = pieceMalPlacee(noeudInit->taquin, noeudBut->taquin);
    f_limite = (noeudInit->c) + (noeudInit->taquin.h);
    while (f_limite <= limite_max) {
        Resultat res = EPL_CONTOUR(noeudInit, noeudBut, f_limite);
        if(res.noeud != NULL){
        	afficherChemin(res.noeud);
        	return;
		}
        if (res.limite == INT_MAX) {
            printf("Pas de solution trouvée\n");
            return;
        }
        f_limite = res.limite;
    }
}


