#include "../hea/Grille.h"

// Constructeur de AbstractGrille
AbstractGrille::AbstractGrille(int X, int Y, const std::vector<std::vector<StandardCellule>>& newCellules)
    : sizeX(X), sizeY(Y), Cellules(newCellules) {}

// Constructeur de GrilleClassique
GrilleClassique::GrilleClassique(int X, int Y, const std::vector<std::vector<StandardCellule>>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

// Affichage de GrilleClassique
void GrilleClassique::afficherGrille() const {
    //std::cout << "Grille Classique de taille " << sizeX << " x " << sizeY << std::endl;
    for (const auto& ligne : Cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.GetState() ? "O " : ". ");
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
                if (Cellules[nx][ny].GetState()) {
                    ++voisinsVivants;
                }
            }
        }
    }
    return voisinsVivants;
}

//update des cellules de la grille classique
void GrilleClassique::update() {
    std::vector<std::vector<StandardCellule>> newCellules = Cellules;

    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            int voisinsVivants = VoisinVivant(x, y);
            if (Cellules[x][y].GetState()) {
                // Cellule vivante : meurt si <2 ou >3 voisins vivants
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    newCellules[x][y].ChangeState(0);
                }
            } else {
                // Cellule morte : devient vivante si exactement 3 voisins vivants
                if (voisinsVivants == 3) {
                    newCellules[x][y].ChangeState(1);
                }
            }
        }
    }
    // Mettre à jour la grille
    Cellules = newCellules;
}

// Constructeur de GrilleTorique
GrilleTorique::GrilleTorique(int X, int Y, const std::vector<std::vector<StandardCellule>>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

// Affichage de GrilleTorique
void GrilleTorique::afficherGrille() const {
    //std::cout << "Grille Torique de taille " << sizeX << " x " << sizeY << std::endl;
    for (const auto& ligne : Cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.GetState() ? "O " : ". ");
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
            if (Cellules[nx][ny].GetState()) {
                ++voisinsVivants;
            }
        }
    }
    return voisinsVivants;
}

void GrilleTorique::update() {
    std::vector<std::vector<StandardCellule>> newCellules = Cellules;

    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            int voisinsVivants = VoisinVivant(x, y);
            if (Cellules[x][y].GetState()) {
                // Cellule vivante : meurt si <2 ou >3 voisins vivants
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    newCellules[x][y].ChangeState(0);
                }
            } else {
                // Cellule morte : devient vivante si exactement 3 voisins vivants
                if (voisinsVivants == 3) {
                    newCellules[x][y].ChangeState(1);
                }
            }
        }
    }
    // Mettre à jour la grille
    Cellules = newCellules;
}

// Constructeur de Motif
Motif::Motif(int X, int Y, const std::vector<std::vector<StandardCellule>>& newCellules)
    : AbstractGrille(X, Y, newCellules) {}

// Affichage de Motif
void Motif::afficherGrille() const {
    //std::cout << "Motif de taille " << sizeX << " x " << sizeY << std::endl;
    for (const auto& ligne : Cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.GetState() ? "O " : ". ");
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
                if (Cellules[nx][ny].GetState()) {
                    ++voisinsVivants;
                }
            }
        }
    }
    return voisinsVivants;
}
