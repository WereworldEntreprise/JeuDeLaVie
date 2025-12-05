#pragma once
#include <SFML/Graphics.hpp>
#include "Grille.hpp"

class DessinGrille {
private:
    float tailleCellule;

public:
    DessinGrille(float tailleCellule = 20.0f);
    void dessiner(sf::RenderWindow& fenetre, const Grille& g) const;
};
