//
// Created by lucas on 27/11/2024.
//

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "hea/Grille.h"
#include "hea/AbstractCellule.h"

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;
const int iterations = 100;

int main() {
    /*sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    std::vector<int> cellules;
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            cellules.push_back(std::rand() % 2);  // Randomly initialize cells as alive or dead
        }
    }
    GrilleClassique grille(gridWidth,gridHeight,cellules);

    sf::Event event;

    for (int t=0; t < iterations; t++) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        window.clear();
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                if (grille.getCellState(x,y) == 1) {
                    cell.setPosition(x * cellSize, y * cellSize);
                    window.draw(cell);
                }
            }
        }
        window.display();

        sf::sleep(sf::milliseconds(100));

        grille.update();
    }

    return 0;*/


}