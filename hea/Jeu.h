//
// Created by lucas on 03/12/2024.
//

#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <fstream>
#include <vector>

#include "AbstractCellule.h"
#include "Grille.h"

class Jeu{
    private:
        const int cellSize = 10;
        int gridWidth = 5;
        int gridHeight = 5;
        const int iterations = 100;
        GrilleClassique* grille;
        void Save();
        void Load();
    public:
        Jeu();
        void Launch();
};

#endif //JEU_H
