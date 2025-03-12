#include "../hea/Grille.h"

// ----- Méthodes utilitaires -----

int AbstractGrille::getCellState(int x, int y) const {
    auto it = Cellules.find({x, y});
    if (it != Cellules.end()) {
        return it->second->GetState();
    }
    return 0; // Si la cellule n'existe pas, retour 0 (cellule morte)
}

void AbstractGrille::setCellState(int x, int y, std::shared_ptr<AbstractCellule> cellule) {
    //std::cout << cellule->GetState() << std::endl;
    if (Cellules.find({x, y}) != Cellules.end()) {
        if (Cellules[{x, y}]->GetState() != 0) {
            Cellules[{x, y}]->ChangeState(cellule->GetState());
        } else {
            Cellules.erase({x, y});
        }
    } else if (cellule->GetState() != 0) {
        Cellules[{x, y}] = cellule;
    }
}

void AbstractGrille::setCustomCellule(int x, int y, std::shared_ptr<AbstractCellule> cellule) {
    if (Cellules.find({x, y}) != Cellules.end()) {
        Cellules[{x, y}] = cellule;
    } else {
        Cellules[{x, y}] = cellule;
    }
}


// ----- Constructeurs -----
AbstractGrille::AbstractGrille(): sizeX(2), sizeY(2) {
}

AbstractGrille::AbstractGrille(int X, int Y): sizeX(X), sizeY(Y) {
}

AbstractGrille::AbstractGrille(int X, int Y,
                               std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash>
                               cellules): sizeX(X), sizeY(Y) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            Cellules[{i, j}] = cellules[{i, j}];
        }
    }
}

AbstractGrille::~AbstractGrille() { Cellules.clear(); }

GrilleClassique::GrilleClassique() : AbstractGrille() {
}

GrilleClassique::GrilleClassique(int X, int Y): AbstractGrille(X, Y) {
}

GrilleClassique::GrilleClassique(int X, int Y,
                                 std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash>
                                 cellules): AbstractGrille(X, Y, cellules) {
}

GrilleClassique::~GrilleClassique() { Cellules.clear(); }

GrilleTorique::GrilleTorique() : AbstractGrille() {
}

GrilleTorique::GrilleTorique(int X, int Y): AbstractGrille(X, Y) {
}

GrilleTorique::GrilleTorique(int X, int Y,
                             std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash>
                             cellules): AbstractGrille(X, Y, cellules) {
}

GrilleTorique::~GrilleTorique() { Cellules.clear(); }

// ----- ************** -----

void GrilleClassique::afficherGrille() const {
    // vérifier la taille de la grille
    for (int y = 0; y < sizeY; ++y) {
        std::cout << "  ";
        for (int x = 0; x < sizeX; ++x) {
            if (Cellules.find({x, y}) != Cellules.end()) {
                if (getCellState(x, y) == 101) {
                    std::cout << " ◇ ";
                } else if (getCellState(x, y) == 111) {
                    std::cout << " ◆ ";
                } else {
                    std::cout << (getCellState(x, y) ? " ■ " : " □ ");
                }
            } else {
                std::cout << " □ ";
            }
            std::cout << "  ";
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
            if (nx >= 0 && nx < sizeX && ny >= 0 && ny < sizeY) {
                // Vérifie les limites
                if (getCellState(nx, ny) == 111 || getCellState(nx, ny) == 1) {
                    voisinsVivants += 1;
                }
            }
        }
    }
    return voisinsVivants;
}

void GrilleClassique::update() {
    std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> newCells = Cellules;
    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            int voisinsVivants = VoisinVivant(x, y);
            if (getCellState(x, y) == 1) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    setCellState(x, y, std::make_shared<StandardCellule>(0)); // Meurt
                }
                if (getCellState(x, y) == 0) {
                }
                if (voisinsVivants == 3) {
                    setCellState(x, y, std::make_shared<StandardCellule>(1)); // Devient vivante
                }
                // Exemple de mise à jour de cellule morte
            }
        }
    }
    Cellules = newCells; // Mise à jour de la grille
}

void GrilleTorique::afficherGrille() const {
    for (int y = 0; y < sizeY; ++y) {
        std::cout << "  ";
        for (int x = 0; x < sizeX; ++x) {
            if (Cellules.find({x, y}) != Cellules.end()) {
                if (getCellState(x, y) == 101) {
                    std::cout << " ◇ ";
                } else if (getCellState(x, y) == 111) {
                    std::cout << " ◆ ";
                } else {
                    std::cout << (getCellState(x, y) ? " ■ " : " □ ");
                }
            } else {
                std::cout << " □ ";
            }
            std::cout << "  ";
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
            if (getCellState(nx, ny) == 111 || getCellState(nx, ny)) {
                voisinsVivants += 1;
            }
        }
    }
    return voisinsVivants;
}

void GrilleTorique::update() {
    std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> newCellules = Cellules;

    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            int voisinsVivants = VoisinVivant(x, y);
            if (getCellState(x, y) == 1) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    setCellState(x, y, std::make_shared<StandardCellule>(0)); // Meurt
                }
                if (voisinsVivants == 3) {
                    setCellState(x, y, std::make_shared<StandardCellule>(1)); // Devient vivante
                }
                // Exemple de mise à jour de cellule morte
            }
        }
    }
    Cellules = newCellules;
}
