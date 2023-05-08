const int taille = 3;
struct Taquin{
	int matrice[taille][taille];
	int espaceVideRow, espaceVideCol;
	int h;
	bool operator==(const Taquin& t) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (t.matrice[i][j] != matrice[i][j]) {
                return false;
            }
        }
    }
    return true;
}
} ;


struct Noeud{
	Taquin taquin;
	int c;
	Noeud* parent;
};

struct Resultat{
	Noeud* noeud;
	int limite;
};

struct comparerNoeuds{
	bool operator()(const Noeud* n1, const Noeud* n2) const {
		return (n1->c + n1->taquin.h) > (n2->c + n2->taquin.h);
	}
};

Taquin creerTaquin(int matrice[3][3]);
Noeud* creerNoeud(int c, Taquin t, Noeud* parent);
bool taquinEgal(Taquin t1, Taquin t2);
int pieceMalPlacee(Taquin taquin, Taquin taquinBut);
void echanger(Taquin& taquin, int row1, int col1, int row2, int col2);
//bool peutDeplacerHaut(Taquin taquin);
//bool peutDeplacerBas(Taquin taquin);
//bool peutDeplacerGauche(Taquin taquin);
//bool peutDeplacerDroite(Taquin taquin);
//void deplacerHaut(Taquin& taquin);
//void deplacerBas(Taquin& taquin);
//void deplacerGauche(Taquin& taquin);
//void deplacerDroite(Taquin& taquin);

Taquin deplacement(Taquin t, int direction);

void explorationAEtoile(Noeud* noeudInit,Noeud* noeudBut);
void idaEtoile(Noeud* noeudInit, Noeud* noeudBut, int limite_max);
