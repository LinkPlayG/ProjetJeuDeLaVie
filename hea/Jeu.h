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


#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

class Jeu{
    private:
        const int cellSize = 10;
        int gridWidth = 5;
        int gridHeight = 5;
        const int iterations = 100;
        std::string fname;
        GrilleClassique* grille;
        void Save(std::string fileName);
        void Load(std::string fileName);
        void IG();
        void Console();
    public:
        Jeu();
        void Launch();
};

#endif //JEU_H
