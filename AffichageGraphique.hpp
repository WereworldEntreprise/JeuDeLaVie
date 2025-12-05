#pragma once
#include "DessinGrille.hpp"
#include "Bouton.hpp"
#include "Grille.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <memory>
#include <string>

class GraphiqueAffichage {
private:
    sf::RenderWindow fenetre;
    sf::View         vue;
    DessinGrille     dessineur;
    int              tailleCellule;
    int              largeurGrille;
    int              hauteurGrille;
    float            facteurZoom;
    std::vector<std::unique_ptr<Bouton>> boutons;
    sf::Font         maFont;
    bool             enTrainDeDesssiner = false;
    bool             modeDessin = true;

    bool positionVersGrille(sf::Vector2i pixelPos, int& x, int& y, const Grille& g);
    void modifierCellule(Grille& g, int x, int y);

public:
    GraphiqueAffichage(int largeur, int hauteur, int tailleCell = 20);
    void afficher(const Grille& g, int generation);
    bool estFerme() const;
    sf::RenderWindow& getFenetre();
    std::string gererEvenements(const sf::Event& event, Grille& g);
};
