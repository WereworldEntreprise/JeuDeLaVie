#include "Regles.hpp"


int RegleJeuDeLaVie::compterVoisins(const Grille& grille, int x, int y) {
    int compteur = 0;

    int largeur = grille.getLargeur();
    int hauteur = grille.getHauteur();

    for (int ligneVoisin = y - 1; ligneVoisin <= y + 1; ligneVoisin++) {
        for (int colonneVoisin = x - 1; colonneVoisin <= x + 1; colonneVoisin++) {

            if (ligneVoisin == y && colonneVoisin == x) {
                continue;
            }


            int colWrap = ((colonneVoisin % largeur) + largeur) % largeur;
            int rowWrap = ((ligneVoisin % hauteur) + hauteur) % hauteur;

            if (grille.getCellule(colWrap, rowWrap).estVivante()) {
                compteur++;
            }
        }
    }

    return compteur;
}


void RegleJeuDeLaVie::appliquerRegles(const Grille& grilleActuelle, Grille& prochaineGrille) {


    for (int y = 0; y < grilleActuelle.getHauteur(); y++) {
        for (int x = 0; x < grilleActuelle.getLargeur(); x++) {


            int voisins = compterVoisins(grilleActuelle, x, y);


            bool estVivante = grilleActuelle.getCellule(x, y).estVivante();


            bool seraVivante = false;

            if (estVivante) {

                if (voisins == 2 || voisins == 3) {
                    seraVivante = true;
                }

            }
            else {

                if (voisins == 3) {
                    seraVivante = true;
                }
            }


            prochaineGrille.setCellule(x, y, seraVivante);
        }
    }
}