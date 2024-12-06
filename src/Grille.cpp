#include "../hea/Grille.h"

// ----- Méthodes utilitaires -----

int AbstractGrille::getCellState(int x, int y) const {
    return Cellules[y * sizeX + x]; // Convertit les coordonnées 2D en index 1D
}

void AbstractGrille::setCellState(int x, int y, int state) {
    Cellules[y * sizeX + x] = state; // Convertit les coordonnées 2D en index 1D
}

// ----- Constructeurs -----
AbstractGrille::AbstractGrille(): sizeX(2), sizeY(2), Cellules({0,0,0,0}) {}

AbstractGrille::AbstractGrille(int X, int Y, const std::vector<int>& newCellules)
    : sizeX(X), sizeY(Y), Cellules(newCellules) {}

GrilleClassique::GrilleClassique() : AbstractGrille() {}
GrilleClassique::GrilleClassique(int X, int Y, const std::vector<int>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

GrilleTorique::GrilleTorique() : AbstractGrille() {}
GrilleTorique::GrilleTorique(int X, int Y, const std::vector<int>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

Motif::Motif() : AbstractGrille() {}
Motif::Motif(int X, int Y, const std::vector<int>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

// ----- ************** -----

void GrilleClassique::afficherGrille() const {
    // vérifier la taile de la grille
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            std::cout << (getCellState(x, y) ? " 0 " : " * ");
        }
        std::cout << std::endl;
    }
}

int GrilleClassique::VoisinVivant(int x, int y) const {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Ignore la cellule centrale
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < sizeX && ny >= 0 && ny < sizeY) { // Vérifie les limites
                voisinsVivants += getCellState(nx, ny);
            }
        }
    }
    return voisinsVivants;
}

void GrilleClassique::update() {
    std::vector<int> newCellules = Cellules;

    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            int voisinsVivants = VoisinVivant(x, y);
            if (getCellState(x, y)) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    newCellules[y * sizeX + x] = 0; // Meurt
                }
            } else {
                if (voisinsVivants == 3) {
                    newCellules[y * sizeX + x] = 1; // Devient vivante
                }
            }
        }
    }
    Cellules = newCellules; // Mise à jour de l'état de la grille
}

void GrilleTorique::afficherGrille() const {
    if (sizeof(Cellules) != sizeX * sizeY) {
        std::cerr << "Erreur: la taille de la grille ne correspond pas à la taille spécifiée" << std::endl;
        return;
    }

    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            std::cout << (getCellState(x, y) ? " 0 " : " * ");
        }
        std::cout << std::endl;
    }
}

int GrilleTorique::VoisinVivant(int x, int y) const {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = (x + i + sizeX) % sizeX; // Gestion torique
            int ny = (y + j + sizeY) % sizeY; // Gestion torique
            voisinsVivants += getCellState(nx, ny);
        }
    }
    return voisinsVivants;
}

void GrilleTorique::update() {
    std::vector<int> newCellules = Cellules;

    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            int voisinsVivants = VoisinVivant(x, y);
            if (getCellState(x, y)) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    newCellules[y * sizeX + x] = 0;
                }
            } else {
                if (voisinsVivants == 3) {
                    newCellules[y * sizeX + x] = 1;
                }
            }
        }
    }
    Cellules = newCellules;
}

void Motif::afficherGrille() const {
    if (sizeof(Cellules) != sizeX * sizeY) {
        std::cerr << "Erreur: la taille de la grille ne correspond pas à la taille spécifiée" << std::endl;
        return;
    }

    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            std::cout << (getCellState(x, y) ? " 0 " : " * ");
        }
        std::cout << std::endl;
    }
}

int Motif::VoisinVivant(int x, int y) const {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < sizeX && ny >= 0 && ny < sizeY) {
                voisinsVivants += getCellState(nx, ny);
            }
        }
    }
    return voisinsVivants;
}

void Motif::update() {
    // ne fait rien (motif statique)
}
