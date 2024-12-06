#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <iostream>

// Classe abstraite de grille
class AbstractGrille {
protected:
    int sizeX;                      // Largeur de la grille
    int sizeY;                      // Hauteur de la grille
    std::vector<int> Cellules;      // Grille stockée sous forme de tableau 1D

public:
    AbstractGrille(int X, int Y, const std::vector<int>& newCellules);
    virtual void afficherGrille() const = 0;  // Méthode d'affichage virtuelle pure
    virtual ~AbstractGrille() = default;      // Destructeur virtuel
    virtual void update() = 0;                // Mise à jour de la grille (à implémenter)

    int getCellState(int x, int y) const;     // Récupère l'état d'une cellule
    void setCellState(int x, int y, int state); // Modifie l'état d'une cellule
};

// Classe pour une grille classique
class GrilleClassique : public AbstractGrille {
public:
    GrilleClassique(int X, int Y, const std::vector<int>& newCellules);
    void afficherGrille() const override; // Affiche la grille
    int VoisinVivant(int x, int y) const; // Compte les voisins vivants
    void update() override;               // Met à jour les cellules selon les règles
};

// Classe pour une grille torique
class GrilleTorique : public AbstractGrille {
public:
    GrilleTorique(int X, int Y, const std::vector<int>& newCellules);
    void afficherGrille() const override;
    int VoisinVivant(int x, int y) const;
    void update() override;
};

// Classe pour un motif (grille statique ou préconfigurée)
class Motif : public AbstractGrille {
public:
    Motif(int X, int Y, const std::vector<int>& newCellules);
    void afficherGrille() const override;
    int VoisinVivant(int x, int y) const;
    void update() override;
};

#endif // GRILLE_H
