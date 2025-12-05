#pragma once
#include "Grille.hpp"
#include "AffichageGraphique.hpp"
#include "AffichageConsole.hpp"
#include "Regles.hpp"

class Simulation {
private:
    Grille grille;
    RegleJeuDeLaVie regles;

    void modeGraphique();
    void modeConsole();
    int afficherMenu();

public:
    Simulation(int largeur, int hauteur);
    void lancer();
};
