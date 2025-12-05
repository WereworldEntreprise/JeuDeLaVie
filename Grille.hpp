
#pragma once
#include <vector>
#include "Cellule.hpp"

class Grille {
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<Cellule>> cellules;

public:
    Grille(int largeur, int hauteur);

    int getLargeur() const;
    int getHauteur() const;

    const Cellule& getCellule(int x, int y) const;
    Cellule& getCellule(int x, int y);

    void setCellule(int x, int y, int etat);
};