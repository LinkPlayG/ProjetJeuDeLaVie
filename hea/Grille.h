#ifndef GRILLE_H
#define GRILLE_H

#include "Cell.h"
#include <iostream>
#include <vector>

#include <unordered_map>
#include <memory>

struct Hash {
    size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

// Classe abstraite de grille
class AbstractGrille {
protected:
    int sizeX; // Largeur de la grille
    int sizeY; // Hauteur de la grille
    std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> Cellules;
    // Grille stockée sous forme de tableau 1D
public:
    AbstractGrille();

    AbstractGrille(int X, int Y);

    AbstractGrille(int X, int Y,
                   std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> cellules);

    virtual ~AbstractGrille();

    int getCellState(int x, int y) const; // Récupère l'état d'une cellule
    void setCellState(int x, int y, std::shared_ptr<AbstractCellule> cellule); // Modifie l'état d'une cellule
    void setCustomCellule(int x, int y, std::shared_ptr<AbstractCellule> cellule);

    virtual void update() = 0; // Mise à jour de la grille (à implémenter)
    virtual void afficherGrille() const = 0; // Méthode d'affichage virtuelle pure
};

// Classe pour une grille classique
class GrilleClassique : public AbstractGrille {
public:
    GrilleClassique();

    GrilleClassique(int X, int Y);

    GrilleClassique(int X, int Y,
                    std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> cellules);

    ~GrilleClassique();

    void afficherGrille() const override; // Affiche la grille
    int VoisinVivant(int x, int y) const; // Compte les voisins vivants
    void update() override; // Met à jour les cellules selon les règles
};

// Classe pour une grille torique
class GrilleTorique : public AbstractGrille {
public:
    GrilleTorique();

    GrilleTorique(int X, int Y);

    GrilleTorique(int X, int Y,
                  std::unordered_map<std::pair<int, int>, std::shared_ptr<AbstractCellule>, Hash> cellules);

    ~GrilleTorique();

    void afficherGrille() const override;

    int VoisinVivant(int x, int y) const;

    void update() override;
};

// Classe pour un motif (grille statique ou préconfigurée)
class Motif : public AbstractGrille {
public:
    Motif();

    Motif(int X, int Y);

    Motif(int X, int Y, std::vector<std::shared_ptr<AbstractCellule> > cellules);

    ~Motif();

    void afficherGrille() const override;

    int VoisinVivant(int x, int y) const;

    void update() override;
};

#endif // GRILLE_H
