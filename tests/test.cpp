//
// Created by lucas on 27/11/2024.
//
/*
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../hea/Jeu.h"

//#include "Grille.h"
#include <iostream>
#include <vector>
#include <cassert> // Fournit des assertions pour vérifier les conditions

// Fonction utilitaire pour afficher le succès d'un test
void printTestResult(const std::string& testName, bool success) {
    std::cout << testName << " : " << (success ? "PASS" : "FAIL") << std::endl;
}

// Test des constructeurs et de l'initialisation
void testConstructeurs() {
    std::vector<int> cellules = {0, 1, 0, 1, 1, 0, 0, 1, 0}; // 3x3
    GrilleClassique gc(3, 3, cellules);
    GrilleTorique gt(3, 3, cellules);
    Motif motif(3, 3, cellules);

    assert(gc.getCellState(1, 0) == 1);
    assert(gc.getCellState(2, 1) == 0);

    assert(gt.getCellState(0, 2) == 0);
    assert(gt.getCellState(1, 1) == 1);

    assert(motif.getCellState(1, 2) == 1);
    assert(motif.getCellState(2, 2) == 0);

    printTestResult("testConstructeurs", true);
}

// Test de `setCellState` et `getCellState`
void testSetGetCellState() {
    std::vector<int> cellules(9, 0); // 3x3 grille vide
    GrilleClassique gc(3, 3, cellules);

    gc.setCellState(0, 0, 1);
    gc.setCellState(1, 1, 1);
    gc.setCellState(2, 2, 1);

    assert(gc.getCellState(0, 0) == 1);
    assert(gc.getCellState(1, 1) == 1);
    assert(gc.getCellState(2, 2) == 1);

    printTestResult("testSetGetCellState", true);
}

// Test de `VoisinVivant`
void testVoisinVivant() {
    std::vector<int> cellules = {
        0, 1, 0,
        1, 1, 0,
        0, 0, 1
    }; // 3x3
    GrilleClassique gc(3, 3, cellules);
    GrilleTorique gt(3, 3, cellules);

    assert(gc.VoisinVivant(0, 0) == 3);
    assert(gc.VoisinVivant(1, 1) == 3);
    assert(gc.VoisinVivant(2, 2) == 1);

    assert(gt.VoisinVivant(0, 0) == 4); // Gestion torique : les bords se rejoignent
    assert(gt.VoisinVivant(1, 1) == 3);
    assert(gt.VoisinVivant(2, 2) == 3);

    printTestResult("testVoisinVivant", true);
}

// Test de l'affichage (`afficherGrille`)
void testAfficherGrille() {
    std::vector<int> cellules = {
        0, 1, 0,
        1, 0, 1,
        1, 1, 0
    }; // 3x3
    GrilleClassique gc(3, 3, cellules);

    std::cout << "Affichage attendu : \n *  0  * \n 0  *  0 \n 0  0  * \n";
    std::cout << "Affichage réel : \n";
    gc.afficherGrille();

    printTestResult("testAfficherGrille (visuel)", true);
}

// Test de `update`
void testUpdate() {
    std::vector<int> cellules = {
        0, 1, 0,
        1, 1, 0,
        0, 0, 1
    }; // 3x3
    GrilleClassique gc(3, 3, cellules);

    // État attendu après une mise à jour (règles de Game of Life)
    std::vector<int> expected = {
        1, 1, 0,
        1, 1, 0,
        0, 1, 0
    };

    gc.update();

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            assert(gc.getCellState(x, y) == expected[y * 3 + x]);
        }
    }

    printTestResult("testUpdate", true);
}

// Fonction principale des tests
int main() {
    testConstructeurs();
    testSetGetCellState();
    testAfficherGrille();
    testVoisinVivant();

    //testUpdates();

    std::cout << "Tous les tests sont terminés !" << std::endl;
    return 0;
}
*/