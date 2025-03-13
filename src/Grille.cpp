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
    if (Cellules.find({x, y}) != Cellules.end()) {
        if (cellule->GetState() != 0) {
            Cellules[{x, y}]->ChangeState(cellule->GetState());
        } else {
            Cellules.erase({x, y});
        }
    } else if (cellule->GetState() != 0) {
        Cellules[{x, y}] = cellule;
    }
}

void AbstractGrille::setCustomCellule(int x, int y, std::shared_ptr<AbstractCellule> cellule) {
    Cellules[{x, y}] = cellule;
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
            int nx = x + j, ny = y + i;
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
    std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> newCellules;
    
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            int voisinsVivants = VoisinVivant(x, y);
            int currentState = getCellState(x, y);
            
            if (currentState == 1 || currentState == 111) {
                // Cellule vivante
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    // Meurt par sous-population ou surpopulation
                    newCellules[{x, y}] = std::make_shared<StandardCellule>(0);
                } else {
                    // Survit
                    newCellules[{x, y}] = std::make_shared<StandardCellule>(currentState);
                }
            } else if (currentState == 0) {
                // Cellule morte
                if (voisinsVivants == 3) {
                    // Naissance
                    newCellules[{x, y}] = std::make_shared<StandardCellule>(1);
                }
            } else if (currentState == 101) {
                // Obstacle - ne change pas
                newCellules[{x, y}] = Cellules.at({x, y});
            }
        }
    }
    
    // Mettre à jour la grille
    for (const auto& pair : newCellules) {
        setCellState(pair.first.first, pair.first.second, pair.second);
    }
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
            int nx = (x + j + sizeX) % sizeX; // Gestion torique
            int ny = (y + i + sizeY) % sizeY; // Gestion torique
            int state = getCellState(nx, ny);
            if (state == 111 || state == 1) {
                voisinsVivants += 1;
            }
        }
    }
    return voisinsVivants;
}

void GrilleTorique::update() {
    std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> newCellules;
    
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            int voisinsVivants = VoisinVivant(x, y);
            int currentState = getCellState(x, y);
            
            if (currentState == 1 || currentState == 111) {
                // Cellule vivante
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    // Meurt par sous-population ou surpopulation
                    newCellules[{x, y}] = std::make_shared<StandardCellule>(0);
                } else {
                    // Survit
                    newCellules[{x, y}] = std::make_shared<StandardCellule>(currentState);
                }
            } else if (currentState == 0) {
                // Cellule morte
                if (voisinsVivants == 3) {
                    // Naissance
                    newCellules[{x, y}] = std::make_shared<StandardCellule>(1);
                }
            } else if (currentState == 101) {
                // Obstacle - ne change pas
                newCellules[{x, y}] = Cellules.at({x, y});
            }
        }
    }
    
    // Mettre à jour la grille
    for (const auto& pair : newCellules) {
        setCellState(pair.first.first, pair.first.second, pair.second);
    }
}
