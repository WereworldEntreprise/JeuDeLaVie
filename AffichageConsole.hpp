#pragma once
#include "Grille.hpp"
#include <iostream>

class ConsoleAffichage {
private:
    std::ostream& flux;

public:
     ConsoleAffichage(std::ostream& sortie = std::cout);
    void afficher(const Grille& g, int generation);
};

