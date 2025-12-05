#include<iostream>
#include "Grille.hpp"

Grille::Grille(int largeur, int hauteur)
    : largeur(largeur), hauteur(hauteur)
{
    cellules.resize(hauteur);
    for (int y = 0; y < hauteur; y++) {
        cellules[y].resize(largeur);
        for (int x = 0; x < largeur; x++) {
            cellules[y][x] = Cellule(x, y, false);
        }
    }
}

int Grille::getLargeur() const { return largeur; }
int Grille::getHauteur() const { return hauteur; }

const Cellule& Grille::getCellule(int x, int y) const { 
    return cellules[y][x];
}

Cellule& Grille::getCellule(int x, int y) {
    return cellules[y][x];
}

void Grille::setCellule(int x, int y, int etat) {
    cellules[y][x].setVivante(etat != 0);
}