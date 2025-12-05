#pragma once

class Cellule {
private:
    int x, y;
    bool vivante;

public:
    Cellule(int x = 0, int y = 0, bool vivante = false);

    bool estVivante() const;
    void setVivante(bool etat);

    int getX() const;
    int getY() const;
};
