#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#include "taquin.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int m1[3][3] = {{8, 1, 3}, {0, 4, 5}, {2, 7, 6}};
    int m2[3][3] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
    Taquin t1 = creerTaquin(m1);
    Taquin t2 = creerTaquin(m2);
    Noeud* n1 = creerNoeud(0,t1,NULL);
	Noeud* n2 = creerNoeud(0,t2,NULL);
//    explorationAEtoile(n1,n2);
	idaEtoile(n1, n2, 30);
	return 0;
}
