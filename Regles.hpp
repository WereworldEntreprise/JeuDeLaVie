#pragma once
#include "Grille.hpp"

class RegleJeuDeLaVie {
public:

    void appliquerRegles(const Grille& grilleActuelle, Grille& prochaineGrille);

private:

    int compterVoisins(const Grille& grille, int x, int y);
};
