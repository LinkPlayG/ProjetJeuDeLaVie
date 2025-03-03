//
// Created by lucas on 05/12/2024.
//
#include "../hea/Jeu.h"

Jeu::Jeu(){
  this->gridHeight = 4;
  this->gridWidth = 4;
  this->iterations = 10;
};

int Jeu::Save(std::string fileName){
    std::string temp;
    temp="../output";
    std::ofstream file(temp, std::ios::app);
    if (!file.is_open()) {
      std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
      return 0;
    }
    //file<<this->gridWidth<<" "<<this->gridHeight<<std::endl;
    file<<std::endl;
    for(int y=0;y<this->gridHeight;y++){
        for(int x=0;x<this->gridWidth;x++){
          file<<grille->getCellState(x,y)<<"   ";
        }
        file<<std::endl;
    }
    file.close();
    return 1;
}

int Jeu::Load(std::string fileName){
  //std::vector <StandardCellule> v;
  //void Jeu::Load() {
 	std::string temp;
    temp="../"+fileName;
    std::ifstream fichier(temp, std::ios::in); // Chemin du fichier à charger
    if (!fichier.is_open()) {
      std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
      return 0;
    }

    fichier >> gridWidth >> gridHeight; // Lecture des dimensions de la grille
    grille=new GrilleClassique(gridWidth, gridHeight);
    for (int i = 0; i < gridHeight; ++i) {
      for (int j = 0; j < gridWidth; ++j) {
        int etat;
        fichier >> etat; // Lire l'état de chaque cellule (0 ou 1)
		if (etat == 0 || etat == 1) {
            grille->setCellState(j,i,std::make_shared<StandardCellule>(etat));
		}
        if (etat == 101 || etat == 111) {
            grille->setCellState(j,i,std::make_shared<Obstacle>(etat));
        }
      }
    }
    fichier.close();

    return 1;
}


int Jeu::Launch(){
    //std::cout<<"Voulez vous utiliser un Motif (fonction non fonctionnelle pour l'instant)\n* Entrez 0 pour utiliser un fichier";
    std::string answer;

    sf::sleep(sf::milliseconds(500));

	std::cout<<"Voulez vous utiliser une grille aléatoire, un Motif ou un fichier d'entrée ?\n1) Un fichier généré aléatoirement\n2) Un Motif\n3) Un fichier contenant des paramètres d'entrée\n";
    std::cin>>answer;
    if (answer != "99"){
      if (answer == "1") {
      std::cout<<"Entrez le nombre de lignes et de colonnes de la grille\n";
      std::cin >> gridHeight >> gridWidth;
      grille=new GrilleClassique(gridWidth, gridHeight);
    	for (int i = 0; i < gridHeight; ++i) {
      		for (int j = 0; j < gridWidth; ++j) {
                int etat;
                etat = rand() % 100 + 1; // 0 ou 100
				if (etat> 0 && etat <= 33) {
            		grille->setCustomCellule(i,j,std::make_shared<StandardCellule>(0));
				}
        		if (etat > 33 || etat <= 66) {
          			Obstacle newCellule(1);
            		grille->setCustomCellule(i,j,std::make_shared<StandardCellule>(1));
        		}
                if (etat> 66 && etat <= 83) {
                  grille->setCellState(j,i,std::make_shared<Obstacle>(etat));
            		grille->setCustomCellule(i,j,std::make_shared<Obstacle>(101));
				}
        		if (etat > 83 || etat <= 100) {
          			Obstacle newCellule(1);
            		grille->setCustomCellule(i,j,std::make_shared<Obstacle>(111));
        		}
            }
      	}
    }
    else if (answer == "2") {
      std::cout<<"Work In Progress\n";
    }
    else if (answer == "3") {
      std::cout<<"\rEntrez le nom du fichier d'entrée\n";
      std::cin>>fname;
    	if (!Load(fname)){
    		return 0;
    	}
    }
    else if (answer == "3") {
      std::cout<<"\rEntrez le nom du fichier d'entrée\n";
      std::cin>>fname;
    	if (!Load(fname)){
    		return 0;
    	}
    }
    else{
      std::cout<<"Parametre invalide\n";
      return 0;
    }
    	std::cout<<"Voulez vous utiliser \n1)La console\n2)L'interface Graphique\n";
    	std::cin>>answer;
    	if(stoi(answer)==1){
      		Console();
      		return 1;
    	}
    	else if(stoi(answer)==2){
        	IG();
        	return 1;
    	}
    	else{
        	std::cout<<"Veuillez Réésayer\n";
        	return 0;
    	}
    	return 1;
    }
    else{
      Editor();
      return 1;
    }
}

int Jeu::IG(){
  	sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    sf::Event event;

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.clear();
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
              	if (grille->getCellState(x,y) == 0) {
                  	cell.setFillColor(sf::Color(196, 0, 0));
                    cell.setPosition(x * cellSize, y * cellSize);//v v m r o v b o m n
                    window.draw(cell);
              	}
                else if (grille->getCellState(x,y) == 1) {
                  	cell.setFillColor(sf::Color(0, 212, 58));
                    cell.setPosition(x * cellSize, y * cellSize);
                    window.draw(cell);
                }
                else if (grille->getCellState(x,y) == 101) {
                  	cell.setFillColor(sf::Color(0, 0, 0));
                    cell.setPosition(x * cellSize, y * cellSize);
                    window.draw(cell);
                }
                else if (grille->getCellState(x,y) == 111) {
                  	cell.setFillColor(sf::Color(255, 255, 255));
                    cell.setPosition(x * cellSize, y * cellSize);
                    window.draw(cell);
                }
            }
        }
        window.display();

        sf::sleep(sf::milliseconds(500));

        grille->update();
        Save(fname);
	}
	std::cout<<"> Stopping the simulation"<<std::endl;
	return 0;
}
int Jeu::Console(){
  	std::cout<<"> Starting the simulation\n";
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
      grille->afficherGrille();
      std::cout<<std::endl;
      grille->update();
      sf::sleep(sf::milliseconds(500));
      Save(fname);
    }
    std::cout<<"> Stopping the simulation"<<std::endl;
    return 0;
}

//WIP
int Jeu::Editor(){
  	std::cout<<"Enter the size of your grid : Width Height\n";
  	std::cin>>gridHeight>>gridWidth;
    grille=new GrilleClassique(gridWidth, gridHeight);
  	sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    sf::Event event;

    sf::Mouse mouse;
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grille->setCustomCellule(x, y, std::make_shared<StandardCellule>(0));
        }
    }


    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      sf::Vector2i coords = sf::Mouse::getPosition(window);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        int gridX = coords.x / cellSize;
        int gridY = coords.y / cellSize;
        cell.setPosition(gridX * cellSize, gridY * cellSize);
        if (grille->getCellState(gridX, gridY) == 0) {
          StandardCellule cellu(1);
          grille->setCustomCellule(gridX, gridY, std::make_shared<StandardCellule>(1));
          cell.setFillColor(sf::Color(0, 212, 58)); // green
          window.draw(cell);
        }
        if (grille->getCellState(gridX, gridY) == 1) {
          grille->setCustomCellule(gridX, gridY, std::make_shared<Obstacle>(101));
          cell.setFillColor(sf::Color(0, 0, 0)); // black
          window.draw(cell);
        }
        if (grille->getCellState(gridX, gridY) == 101) {
          grille->setCustomCellule(gridX, gridY, std::make_shared<Obstacle>(111));
          cell.setFillColor(sf::Color(255, 255, 255)); // white
          window.draw(cell);
        }
        if (grille->getCellState(gridX, gridY) == 111) {
          StandardCellule cellu(0);
          grille->setCustomCellule(gridX, gridY, std::make_shared<StandardCellule>(0));
          cell.setFillColor(sf::Color(196, 0, 0)); // red
          window.draw(cell);
        }
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        }
      }
        window.display();
	}
	std::cout<<"> Stopping the simulation"<<std::endl;
	return 0;
}