#include "AffichageConsole.hpp"
#include <iomanip>
#include <string>

ConsoleAffichage::ConsoleAffichage(std::ostream& sortie)
    : flux(sortie)
{
}

void ConsoleAffichage::afficher(const Grille& g, int generation)
{
    flux << "Generation " << generation << '\n';

    for (int y = 0; y < g.getHauteur(); ++y) {
        for (int x = 0; x < g.getLargeur(); ++x) {
            flux << (g.getCellule(x, y).estVivante() ? "█" : ".");
        }
        flux << '\n';
    }

    flux << std::string(20, '-') << "\n\n";
}

