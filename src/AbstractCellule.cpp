//
// Created by lucas on 27/11/2024.
//

#include "../hea\AbstractCellule.h"


AbstractCellule::AbstractCellule():x(0),y(0),state(0){}
AbstractCellule::AbstractCellule(int x,int y,int state):x(x),y(y),state(state){}

int AbstractCellule::getX()const{return x;}
int AbstractCellule::getY()const{return y;}
int AbstractCellule::GetState() {return state;}

