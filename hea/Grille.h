#ifndef GRILLE_H
#define GRILLE_H

#include "AbstractCellule.h"
#include <vector>
#include <iostream>

class AbstractGrille {
protected:
    int sizeX;
    int sizeY;
    std::vector<std::vector<CelluleClassique>> Cellules;

public:
    AbstractGrille(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules);
    virtual void afficherGrille() const = 0;
    virtual ~AbstractGrille() = default;
    //virtual void update() = 0;
};

class GrilleClassique : public AbstractGrille {
public:
    GrilleClassique(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules);
    void afficherGrille() const override;
    int VoisinVivant(int x, int y) const;
    //void update() override;
};

class GrilleTorique : public AbstractGrille {
public:
    GrilleTorique(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules);
    void afficherGrille() const override;
    int VoisinVivant(int x, int y) const;
    //void update() override;
};

class Motif : public AbstractGrille {
public:
    Motif(int X, int Y, const std::vector<std::vector<CelluleClassique>>& newCellules);
    void afficherGrille() const override;
    int VoisinVivant(int x, int y) const;
};

#endif //GRILLE_H
