//
// Created by lucas on 03/12/2024.
//

#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Cell.h"
#include "Grille.h"


#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

class Jeu{
    private:
        const int cellSize = 20;
        int gridWidth = 5;
        int gridHeight = 5;
        int iterations = 100;
        std::string fname;
        AbstractGrille* grille;
        int Save(std::string fileName);
        int Load(std::string fileName);
        int IG();
        int Console();
        int Editor();
    public:
        Jeu();
        int Launch();
};

#endif //JEU_H
