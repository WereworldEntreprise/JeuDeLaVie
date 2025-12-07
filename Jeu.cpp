#include "Jeu.hpp"
#include "AffichageConsole.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System.hpp>
#include <iostream>

Simulation::Simulation(int largeur, int hauteur)
    : grille(largeur, hauteur)
{
}

int Simulation::afficherMenu() {
    std::cout << "\n=== MENU ===\n";
    std::cout << "Choisissez le mode d'affichage :\n";
    std::cout << "1 - Mode graphique (SFML)\n";
    std::cout << "2 - Mode console\n";
    std::cout << "3 - Quitter\n";
    std::cout << "Votre choix : ";

    int choix;
    std::cin >> choix;
    return choix;
}

void Simulation::modeGraphique() {
    GraphiqueAffichage affichage(grille.getLargeur(), grille.getHauteur(), 20);
    int generation = 0;
    bool enPause = true;
    int delaiMs = 150;

    while (!affichage.estFerme()) {
        while (const std::optional<sf::Event> eventOpt = affichage.getFenetre().pollEvent()) {
            sf::Event event = *eventOpt;
            if (event.is<sf::Event::Closed>()) {
                affichage.getFenetre().close();
            }
            
            std::string action = affichage.gererEvenements(event, grille);
            
            if (action == "play") {
                enPause = false;
                std::cout << "Play!" << std::endl;
            } else if (action == "pause") {
                enPause = true;
                std::cout << "Pause!" << std::endl;
            } else if (action == "lancerapide") {
                delaiMs = (delaiMs == 150) ? 50 : 150;
                std::cout << "Vitesse: " << delaiMs << "ms" << std::endl;
            } else if (action == "reset") {
                for (int y = 0; y < grille.getHauteur(); ++y) {
                    for (int x = 0; x < grille.getLargeur(); ++x) {
                        grille.getCellule(x, y).setVivante(false );
                    }
                }
                generation = 0;
                enPause = true;
                std::cout << "Reset!" << std::endl;
            }
        }
        
        if (!enPause) {
            Grille prochaineGrille(grille.getLargeur(), grille.getHauteur());
            regles.appliquerRegles(grille, prochaineGrille);
            grille = prochaineGrille;
            generation++;
        }
        
        affichage.afficher(grille, generation);
        sf::sleep(sf::milliseconds(delaiMs));
    }

    std::cout << "\nFenetre fermee. Retour au menu...\n";
}

void Simulation::modeConsole() {
    std::string fichierEntree;
    std::cout << "Nom du fichier d'entree (ex: grille_initiale.txt) : ";
    std::cin >> fichierEntree;


    Grille grilleTemp = FichierGrille::lireFichier(fichierEntree);


    if (grilleTemp.getLargeur() == 0 || grilleTemp.getHauteur() == 0) {
        std::cout << "Erreur de lecture du fichier.\n";
        return;
    }


    grille = grilleTemp;

    int iterations;
    std::cout << "Nombre d'iterations : ";
    std::cin >> iterations;

    std::string nomBaseFichier;
    std::cout << "Nom de base pour les fichiers de sortie (ex: generation) : ";
    std::cin >> nomBaseFichier;


    FichierGrille::ecrireFichier(nomBaseFichier + "_0.txt", grille);


    Grille prochaineGrille(grille.getLargeur(), grille.getHauteur());


    for (int i = 1; i <= iterations; i++) {
        regles.appliquerRegles(grille, prochaineGrille);
        grille = prochaineGrille;


        std::string nomFichier = nomBaseFichier + "_" + std::to_string(i) + ".txt";
        FichierGrille::ecrireFichier(nomFichier, grille);
    }

    std::cout << "\nSimulation terminee. " << (iterations + 1) << " fichiers generes.\n";
    std::cout << "Retour au menu...\n";
}

void Simulation::lancer() {
    bool continuer = true;

    while (continuer) {
        int choix = afficherMenu();

        if (choix == 1) {
            modeGraphique();
        }
        else if (choix == 2) {
            modeConsole();
        }
        else if (choix == 3) {
            std::cout << "Au revoir !\n";
            continuer = false;
        }
        else {
            std::cout << "Choix invalide. Veuillez reessayer.\n";
        }
    }
}
