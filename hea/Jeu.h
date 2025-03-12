//
// Created by lucas on 03/12/2024.
//

#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iomanip>
#include <random>

#include "Cell.h"
#include "Grille.h"


#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

class Jeu {
private:
    const int cellSize = 20;
    int gridWidth = 5;
    int gridHeight = 5;
    int iterations = 0;
    std::string fname;
    std::string titles;
    std::string gridType;
    AbstractGrille *grille;

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
