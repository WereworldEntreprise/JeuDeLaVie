#include "DessinGrille.hpp"

DessinGrille::DessinGrille(float tailleCellule)
    : tailleCellule(tailleCellule)
{
}

void DessinGrille::dessiner(sf::RenderWindow& fenetre, const Grille& g) const
{
    sf::RectangleShape rectangle(sf::Vector2f(tailleCellule, tailleCellule));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1.0f);

    for (int y = 0; y < g.getHauteur(); ++y) {
        for (int x = 0; x < g.getLargeur(); ++x) {
            rectangle.setPosition(sf::Vector2f(x * tailleCellule, y * tailleCellule));
            rectangle.setFillColor(g.getCellule(x, y).estVivante() ? sf::Color::Black : sf::Color::White);
            fenetre.draw(rectangle);
        }
    }
}
