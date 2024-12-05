#include "../hea/Grille.h"

// Constructeur de AbstractGrille
AbstractGrille::AbstractGrille(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules)
    : sizeX(X), sizeY(Y), Cellules(newCellules) {}

// Constructeur de GrilleClassique
GrilleClassique::GrilleClassique(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

// Affichage de GrilleClassique
void GrilleClassique::afficherGrille() const {
    //std::cout << "Grille Classique de taille " << sizeX << " x " << sizeY << std::endl;
    for (const auto& ligne : Cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.getEtat() ? "O " : ". ");
        }
        std::cout << std::endl;
    }
}

// Calcul des voisins vivants pour GrilleClassique
int GrilleClassique::VoisinVivant(int x, int y) const {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < sizeX && ny >= 0 && ny < sizeY) {
                if (Cellules[nx][ny].getEtat()) {
                    ++voisinsVivants;
                }
            }
        }
    }
    return voisinsVivants;
}

// Constructeur de GrilleTorique
GrilleTorique::GrilleTorique(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

// Affichage de GrilleTorique
void GrilleTorique::afficherGrille() const {
    //std::cout << "Grille Torique de taille " << sizeX << " x " << sizeY << std::endl;
    for (const auto& ligne : Cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.getEtat() ? "O " : ". ");
        }
        std::cout << std::endl;
    }
}

// Calcul des voisins vivants pour GrilleTorique
int GrilleTorique::VoisinVivant(int x, int y) const {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = (x + i + sizeX) % sizeX;
            int ny = (y + j + sizeY) % sizeY;
            if (Cellules[nx][ny].getEtat()) {
                ++voisinsVivants;
            }
        }
    }
    return voisinsVivants;
}

// Constructeur de Motif
Motif::Motif(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

// Affichage de Motif
void Motif::afficherGrille() const {
    //std::cout << "Motif de taille " << sizeX << " x " << sizeY << std::endl;
    for (const auto& ligne : Cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.getEtat() ? "O " : ". ");
        }
        std::cout << std::endl;
    }
}

// Calcul des voisins vivants pour Motif
int Motif::VoisinVivant(int x, int y) const {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < sizeX && ny >= 0 && ny < sizeY) {
                if (Cellules[nx][ny].getEtat()) {
                    ++voisinsVivants;
                }
            }
        }
    }
    return voisinsVivants;
}
