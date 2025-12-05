#include "AffichageGraphique.hpp"
#include <cmath>
#include <memory>
#include <algorithm>

GraphiqueAffichage::GraphiqueAffichage(int largeur, int hauteur, int tailleCell)
    : fenetre(sf::VideoMode(sf::Vector2u(largeur * tailleCell, hauteur * tailleCell)), "Jeu de la vie"),
      dessineur(static_cast<float>(tailleCell)),
      tailleCellule(tailleCell),
      largeurGrille(largeur),
      hauteurGrille(hauteur),
      facteurZoom(1.0f)
{
    float largeurTotale = static_cast<float>(largeur * tailleCell);
    float hauteurTotale = static_cast<float>(hauteur * tailleCell);
    vue.setCenter({largeurTotale / 2.0f, hauteurTotale / 2.0f});
    vue.setSize({largeurTotale, hauteurTotale});

    if (maFont.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        boutons.push_back(std::make_unique<Bouton>(10, 10, 80, 40, "Play", maFont, "play"));
        boutons.push_back(std::make_unique<Bouton>(100, 10, 80, 40, "Pause", maFont, "pause"));
        boutons.push_back(std::make_unique<Bouton>(190, 10, 110, 40, "LanceRapide", maFont, "lancerapide"));
        boutons.push_back(std::make_unique<Bouton>(310, 10, 80, 40, "Reset", maFont, "reset"));
    }
}

bool GraphiqueAffichage::positionVersGrille(sf::Vector2i pixelPos, int& x, int& y, const Grille& g) {
    sf::Vector2f positionMonde = fenetre.mapPixelToCoords(pixelPos, vue);
    x = static_cast<int>(std::floor(positionMonde.x / tailleCellule));
    y = static_cast<int>(std::floor(positionMonde.y / tailleCellule));
    return (x >= 0 && x < g.getLargeur() && y >= 0 && y < g.getHauteur());
}

void GraphiqueAffichage::modifierCellule(Grille& g, int x, int y) {
    g.getCellule(x, y).setVivante(modeDessin);
}

void GraphiqueAffichage::afficher(const Grille& g, int generation) {
    fenetre.clear();
    fenetre.setView(vue);
    dessineur.dessiner(fenetre, g);

    fenetre.setView(fenetre.getDefaultView());
    for (auto& btn : boutons) {
        btn->afficher(fenetre);
    }

    fenetre.display();
}

bool GraphiqueAffichage::estFerme() const {
    return !fenetre.isOpen();
}

sf::RenderWindow& GraphiqueAffichage::getFenetre() {
    return fenetre;
}

std::string GraphiqueAffichage::gererEvenements(const sf::Event& event, Grille& g) {
    if (const auto* mouseWheel = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (mouseWheel->wheel == sf::Mouse::Wheel::Vertical) {
            float facteur = (mouseWheel->delta > 0) ? 1.1f : (1.0f / 1.1f);
            facteurZoom = std::clamp(facteurZoom * facteur, 0.5f, 5.0f);

            float largeurTotale = static_cast<float>(largeurGrille * tailleCellule);
            float hauteurTotale = static_cast<float>(hauteurGrille * tailleCellule);
            vue.setSize({largeurTotale / facteurZoom, hauteurTotale / facteurZoom});
        }
    }

    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2f posSourisUI = fenetre.mapPixelToCoords(mouseButton->position, fenetre.getDefaultView());

            for (auto& btn : boutons) {
                if (btn->estClique(posSourisUI)) {
                    return btn->getAction();
                }
            }

            enTrainDeDesssiner = true;
            int x, y;
            if (positionVersGrille(mouseButton->position, x, y, g)) {
                modeDessin = !g.getCellule(x, y).estVivante();
                modifierCellule(g, x, y);
            }
        }
    }

    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            enTrainDeDesssiner = false;
        }
    }

    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
        if (enTrainDeDesssiner) {
            int x, y;
            if (positionVersGrille(mouseMoved->position, x, y, g)) {
                modifierCellule(g, x, y);
            }
        }
    }

    return "";
}
