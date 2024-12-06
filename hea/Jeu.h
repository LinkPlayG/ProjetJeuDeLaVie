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
    void Save();
    void Load();
  public:
    void Launch();
};

#endif //JEU_H
