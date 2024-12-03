//
// Created by lucas on 03/12/2024.
//

#ifndef STANDARDCELLULE_H
#define STANDARDCELLULE_H


#include "AbstractCellule.h"


class StandardCellule: public AbstractCellule{
  public:
    StandardCellule();
    StandardCellule(int x, int y, int state);
    int getX() const override;
    int getY() const override;
    int GetState() override;
    void ChangeState(int s);
};



#endif //STANDARDCELLULE_H
