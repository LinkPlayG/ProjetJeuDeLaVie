//
// Created by lucas on 29/01/2025.
//

//
// Created by lucas on 27/11/2024.
//


#include "../hea/Cell.h"

AbstractCellule::AbstractCellule(): state(0) {
}

AbstractCellule::AbstractCellule(int state): state(state) {
}

StandardCellule::StandardCellule(): AbstractCellule() {
}

StandardCellule::StandardCellule(int state): AbstractCellule(state) {
}

int StandardCellule::GetState() const { return state; }
void StandardCellule::ChangeState(int s) { state = s; }

Obstacle::Obstacle(): AbstractCellule() {
}

Obstacle::Obstacle(int state): AbstractCellule(state) {
}

int Obstacle::GetState() const { return state; }

void Obstacle::ChangeState(int s) {
}
