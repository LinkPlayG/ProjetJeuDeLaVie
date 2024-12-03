//
// Created by lucas on 03/12/2024.
//
#include "../hea\StandardCellule.h"

StandardCellule::StandardCellule():AbstractCellule(){}
StandardCellule::StandardCellule(int x, int y, int state):AbstractCellule(x,y,state){}

int StandardCellule::getX() const {
    return x;
}
int StandardCellule::getY() const {
    return y;
}
int StandardCellule::GetState() {
    return state;
}
void StandardCellule::ChangeState(int s) {
    state = s;
}

