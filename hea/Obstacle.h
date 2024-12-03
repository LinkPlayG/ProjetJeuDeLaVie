//
// Created by lucas on 03/12/2024.
//

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "AbstractCellule.h"

class Obstacle:public AbstractCellule{
  public:
    Obstacle();
    Obstacle(int x,int y, int state);
    int getX()const override;
    int getY()const override;
    int GetState() override;
};

#endif //OBSTACLE_H
