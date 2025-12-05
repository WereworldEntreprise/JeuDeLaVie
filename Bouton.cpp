#include "Bouton.hpp"

Bouton::Bouton(float x, float y, float largeur, float hauteur,
    const std::string& texte, const sf::Font& police, const std::string& act)
    : text(police), action(act) {

    shape.setPosition({ x, y });
    shape.setSize({ largeur, hauteur });
    shape.setFillColor(sf::Color::Blue);

    text.setString(texte);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setPosition({ x + 10, y + 10 });
}

void Bouton::afficher(sf::RenderWindow& fenetre) {
    fenetre.draw(shape);
    fenetre.draw(text);
}

bool Bouton::estClique(const sf::Vector2f& posSouris) const {
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();
    return posSouris.x >= pos.x && posSouris.x <= pos.x + size.x &&
           posSouris.y >= pos.y && posSouris.y <= pos.y + size.y;
}

std::string Bouton::getAction() const {
    return action;
}
