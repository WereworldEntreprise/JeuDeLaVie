#include "Cellule.hpp"

Cellule::Cellule(int x, int y, bool vivante)
    : x(x), y(y), vivante(vivante)
{
}

bool Cellule::estVivante() const {
    return vivante;
}

void Cellule::setVivante(bool etat) {
    vivante = etat;
}

int Cellule::getX() const {
    return x;
}

int Cellule::getY() const {
    return y;
}
