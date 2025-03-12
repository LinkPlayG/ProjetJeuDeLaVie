//
// Created by lucas on 05/12/2024.
//
#include "../hea/Jeu.h"

Jeu::Jeu() {
    this->gridHeight = 4;
    this->gridWidth = 4;
    this->titles = "Numéro_d'itération Largeur Hauteur Type_de_Grille(S:Standard;T:Torique)\n";
};

int Jeu::Save(std::string fileName) {
    fileName = "Outputs/" + fileName + "_out.txt";

    if (fs::exists(fileName) && fs::file_size(fileName) != 0) {
        // File exists and not empty, write to it

        std::ifstream fileIn(fileName, std::ios::in);
        std::string existingContent;
        std::string title, token;
        for (int a = 0; a < 4; a++) {
            fileIn >> token;
            title += token + " ";
        }

        fileIn >> this->iterations;
        this->iterations += 1;

        std::ostringstream buffer;
        buffer << fileIn.rdbuf(); // Read entire file into buffer
        existingContent = buffer.str();


        fileIn.close();
        std::ofstream fileOut(fileName, std::ios::trunc); // Overwrite file
        if (fileOut) {
            fileOut << this->titles;
            fileOut << this->iterations << " " << this->gridWidth << " " << this->gridHeight << " " << this->gridType;
            fileOut << std::endl;
            for (int y = 0; y < this->gridHeight; y++) {
                for (int x = 0; x < this->gridWidth; x++) {
                    fileOut << grille->getCellState(x, y) << "   ";
                }
                fileOut << std::endl;
            }
            fileOut << std::endl;
            fileOut << existingContent << std::endl;
            fileOut << std::endl;
            fileOut.close();
        }
        return 1;
    } else {
        // File doesn't exist or empty, create a new file or open the empty one
        this->iterations = 0;
        std::ofstream newFile(fileName, std::ios::trunc);
        if (newFile) {
            newFile << this->titles << " " << this->iterations << " " << this->gridWidth << " " << this->gridHeight <<this->gridType<<std::endl;
            newFile << std::endl;
            for (int y = 0; y < this->gridHeight; y++) {
                for (int x = 0; x < this->gridWidth; x++) {
                    newFile << grille->getCellState(x, y) << "   ";
                }
                newFile << std::endl;
            }
            newFile.close();
            return 1;
        }
    }
    return 1;
}

int Jeu::Load(std::string fileName) {
    std::string temp = "Inputs/" + fileName + ".txt";
    std::cout << "> Loading file: " << temp << std::endl;
    if (fs::exists(temp)) {
        std::ifstream fichier(temp, std::ios::in); // Chemin du fichier à charger

        std::string title, token;
        for (int a = 0; a < 4; a++) {
            fichier >> token;
            title += token + " ";
        }

        fichier >> this->iterations;
        fichier >> gridWidth >> gridHeight; // Lecture des dimensions de la grille

        fichier >> gridType;
        if (gridType == "S") {
            grille = new GrilleClassique(gridWidth, gridHeight);
        } else if (gridType == "T") {
            grille = new GrilleTorique(gridWidth, gridHeight);
        } else {
            std::cout << "> Erreur de Type\n" << std::endl;
            return 0;
        }
        for (int i = 0; i < gridHeight; ++i) {
            for (int j = 0; j < gridWidth; ++j) {
                int etat;
                fichier >> etat; // Lire l'état de chaque cellule (0 ou 1)
                if (etat == 0 || etat == 1) {
                    grille->setCustomCellule(j, i, std::make_shared<StandardCellule>(etat));
                }
                if (etat == 101 || etat == 111) {
                    grille->setCustomCellule(j, i, std::make_shared<Obstacle>(etat));
                }
            }
        }
        fichier.close();

        return 1;
    } else {
        std::cerr << "# Erreur : Impossible d'ouvrir le fichier. Verifiez l'intégrité des données\n" << std::endl;
        return 0;
    }
}


int Jeu::Launch() {
    std::string answer;

    sf::sleep(sf::milliseconds(500));

    std::cerr <<
            "Voulez vous utiliser une grille aléatoire, un Motif ou un fichier d'entrée ?\n1) Un fichier généré aléatoirement\n2) Un fichier contenant des paramètres d'entrée\n99) Entrer en mode édition\n";
    std::cin >> answer;
    if (answer != "99") {
        if (answer == "1") {
            std::cerr << "Entrez le nombre de lignes et de colonnes de la grille\n";
            std::cin >> gridHeight >> gridWidth;
            std::cerr << "Entrez le type de la grille : \n1) Standard\n2) Torique\n";
            std::cin >> answer;
            if (answer == "1") {
                grille = new GrilleClassique(gridWidth, gridHeight);
            } else if (answer == "2") {
                grille = new GrilleTorique(gridWidth, gridHeight);
            } else {
                std::cerr << "# Type invalide\n";
                return 1;
            }
            std::random_device rd;
            std::mt19937 gen(rd()); // Mersenne Twister generator
            std::uniform_int_distribution<int> dist(1, 100); // Range [1, 100]
            for (int i = 0; i < gridHeight; ++i) {
                for (int j = 0; j < gridWidth; ++j) {
                    int etat = dist(gen);
                    if (etat <= 40) {
                        grille->setCustomCellule(i, j, std::make_shared<StandardCellule>(0));
                    } else if (etat <= 80) {
                        grille->setCustomCellule(i, j, std::make_shared<StandardCellule>(1));
                    } else if (etat <= 90) {
                        grille->setCustomCellule(i, j, std::make_shared<Obstacle>(101));
                    } else {
                        grille->setCustomCellule(i, j, std::make_shared<Obstacle>(111));
                    }
                }
            }
        } else if (answer == "2") {
            std::cerr << "\rEntrez le nom du fichier d'entrée\n";
            std::cin >> fname;
            if (!Load(fname)) {
                return 0;
            }
        } else {
            std::cerr << "# Paramètre invalide\n";
            return 0;
        }
        std::cerr << "Voulez vous utiliser \n1) La console\n2) L'interface Graphique\n";
        std::cin >> answer;
        sf::sleep(sf::milliseconds(1000));
        if (stoi(answer) == 1) {
            std::cerr << "\n? Vous pouvez utiliser Ctrl+C peu importe le mode pour arrêter la simulation.\n";
            Console();
            return 1;
        } else if (stoi(answer) == 2) {
            std::cerr << "\n? Vous pouvez utiliser Ctrl+C peu importe le mode pour arrêter la simulation.\n";
            IG();
            return 1;
        } else {
            std::cerr << "# Paramètre invalide\n";
            return 0;
        }
        return 1;
    } else {
        std::cerr << "Entrez le nombre de lignes et de colonnes de la grille\n";
        std::cin >> gridHeight >> gridWidth;
        std::cerr << "Entrez le type de la grille : \n1) Standard\n2) Torique\n";
        std::cin >> answer;
        if (answer == "1") {
            gridType = "S";
            grille = new GrilleClassique(gridWidth, gridHeight);
        } else if (answer == "2") {
            gridType = "T";
            grille = new GrilleTorique(gridWidth, gridHeight);
        } else {
            std::cerr << "Erreur de Type\n";
        }
        std::cerr << "\n? Vous pouvez utiliser Ctrl+C peu importe le mode pour arrêter la simulation.";
        std::cerr <<
                "\n? En mode Editeur vous pouvez cliquer sur les cellules pour changer leur type.\n? Par défaut les cellules sont mortes et suivent un cycle morte->vivante->obstacle morte->obstacle vivante.";
        std::cerr <<
                "\n? Appuyez sur la touche Entrée pour quitter le mode Edition en sauvegardant dans le fichier Editor_out.txt ou sur la touche ESC pour quitter sans sauvegarder.\n";
        sf::sleep(sf::milliseconds(5000));
        Editor();
        return 1;
    }
}

int Jeu::IG() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    sf::Event event;

    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !(
                sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::C))) {
            std::cerr << "> Stopping the simulation\n" << std::endl;
            return 1;
        }
        window.clear();
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                if (grille->getCellState(x, y) == 0) {
                    cell.setFillColor(sf::Color(196, 0, 0));
                    cell.setPosition(x * cellSize, y * cellSize); //v v m r o v b o m n
                    window.draw(cell);
                } else if (grille->getCellState(x, y) == 1) {
                    cell.setFillColor(sf::Color(0, 212, 58));
                    cell.setPosition(x * cellSize, y * cellSize);
                    window.draw(cell);
                } else if (grille->getCellState(x, y) == 101) {
                    cell.setFillColor(sf::Color(0, 0, 0));
                    cell.setPosition(x * cellSize, y * cellSize);
                    window.draw(cell);
                } else if (grille->getCellState(x, y) == 111) {
                    cell.setFillColor(sf::Color(255, 255, 255));
                    cell.setPosition(x * cellSize, y * cellSize);
                    window.draw(cell);
                }
            }
        }
        window.display();

        sf::sleep(sf::milliseconds(500));

        grille->update();
        Save("AutoGen");
    }
    return 1;
}

int Jeu::Console() {
    std::cerr << "> Starting the simulation\n";
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        grille->afficherGrille();
        std::cout << std::endl;
        grille->update();
        sf::sleep(sf::milliseconds(1000));
        Save(fname);
    }
    std::cerr << "> Stopping the simulation\n" << std::endl;
    return 0;
}

//WIP
int Jeu::Editor() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    sf::Event event;

    sf::Mouse mouse;
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grille->setCustomCellule(x, y, std::make_shared<StandardCellule>(0));
            cell.setFillColor(sf::Color(196, 0, 0)); // green
            cell.setPosition(x * cellSize, y * cellSize); //v v m r o v b o m n
            window.draw(cell);
        }
    }


    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (
                sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::C))) {
            std::cerr << "> Stopping the simulation\n" << std::endl;
            return 0;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            Save("Editor");
            std::cerr << "> Stopping the simulation\n" << std::endl;
            return 0;
        }
        sf::Vector2i coords = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int gridX = coords.x / cellSize;
            int gridY = coords.y / cellSize;
            cell.setPosition(gridX * cellSize, gridY * cellSize);
            if (grille->getCellState(gridX, gridY) == 0) {
                grille->setCustomCellule(gridX, gridY, std::make_shared<StandardCellule>(1));
                cell.setFillColor(sf::Color(0, 212, 58)); // green
                window.draw(cell);
            } else if (grille->getCellState(gridX, gridY) == 1) {
                grille->setCustomCellule(gridX, gridY, std::make_shared<Obstacle>(101));
                cell.setFillColor(sf::Color(0, 0, 0)); // black
                window.draw(cell);
            } else if (grille->getCellState(gridX, gridY) == 101) {
                grille->setCustomCellule(gridX, gridY, std::make_shared<Obstacle>(111));
                cell.setFillColor(sf::Color(255, 255, 255)); // white
                window.draw(cell);
            } else if (grille->getCellState(gridX, gridY) == 111) {
                grille->setCustomCellule(gridX, gridY, std::make_shared<StandardCellule>(0));
                cell.setFillColor(sf::Color(196, 0, 0)); // red
                window.draw(cell);
            }
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            }
        }
        window.display();
    }
    return 0;
}
