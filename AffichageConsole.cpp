#include "AffichageConsole.hpp"
#include <fstream>
#include <iostream>

Grille FichierGrille::lireFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << nomFichier << "\n";
        return Grille(0, 0);
    }

    int largeur, hauteur;
    fichier >> largeur >> hauteur;

    Grille grille(largeur, hauteur);

    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            int valeur;
            fichier >> valeur;
            grille.setCellule(x, y, valeur);
        }
    }

    fichier.close();
    return grille;
}

void FichierGrille::ecrireFichier(const std::string& nomFichier, const Grille& grille) {
    std::ofstream fichier(nomFichier);

    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible de créer le fichier " << nomFichier << "\n";
        return;
    }

    fichier << grille.getLargeur() << " " << grille.getHauteur() << "\n";

    for (int y = 0; y < grille.getHauteur(); y++) {
        for (int x = 0; x < grille.getLargeur(); x++) {
            fichier << (grille.getCellule(x, y).estVivante() ? 1 : 0) << " ";
        }
        fichier << "\n";
    }

    fichier.close();
    std::cout << "Grille sauvegardée dans " << nomFichier << "\n";
}
