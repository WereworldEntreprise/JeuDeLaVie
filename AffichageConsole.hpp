#pragma once
#include "Grille.hpp"
#include <string>

class FichierGrille {
public:

    static Grille lireFichier(const std::string& nomFichier);


    static void ecrireFichier(const std::string& nomFichier, const Grille& grille);
};
