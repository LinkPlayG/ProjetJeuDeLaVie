//
// Created by lucas on 03/12/2024.
//
#include "../hea/Obstacle.h"

Obstacle::Obstacle():AbstractCellule(){}
Obstacle::Obstacle(int x, int y, int state) :AbstractCellule(x, y, state){}

int Obstacle::getX()const {return x;}
int Obstacle::getY()const{return y;}
int Obstacle::GetState(){return state;}


