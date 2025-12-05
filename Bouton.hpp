#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Bouton {
private:
    sf::RectangleShape shape;
    sf::Text text;
    std::string action;

public:
    Bouton(float x, float y, float largeur, float hauteur,
        const std::string& texte, const sf::Font& police, const std::string& act);

    void afficher(sf::RenderWindow& fenetre);
    bool estClique(const sf::Vector2f& posSouris) const;
    std::string getAction() const;
};
