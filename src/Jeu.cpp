//
// Created by lucas on 05/12/2024.
//
#include "../hea/Jeu.h"

Jeu::Jeu(){
  this->gridHeight = 5;
  this->gridWidth = 5;
  this->grille = new GrilleClassique();
};

void Jeu::Save(std::string fileName){
   	std::ofstream file;
    std::string temp;
    temp="../"+fileName+"_out";
    file.open(temp, std::ios::out);
    if (!file.is_open()) {
      std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
      return;
    }
    file<<this->gridWidth<<" "<<this->gridHeight<<std::endl;
    for(int y=0;y<this->gridHeight;y++){
        for(int x=0;x<this->gridWidth;x++){
          file<<this->grille->getCellState(x,y)<<" ";
        }
        file<<std::endl;
    }
    file.close();
}

void Jeu::Load(std::string fileName){
  //std::vector <StandardCellule> v;
  //void Jeu::Load() {
 	std::string temp;
    temp="../"+fileName;
    std::ifstream fichier(temp); // Chemin du fichier à charger
    if (!fichier.is_open()) {
      std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
      return;
    }

    fichier >> gridHeight >> gridWidth; // Lecture des dimensions de la grille
    std::cout<<gridHeight<<" "<<gridWidth<<std::endl;
    std::vector<int> Cellules;

    for (int i = 0; i < gridHeight; ++i) {
      for (int j = 0; j < gridWidth; ++j) {
        bool etat;
        fichier >> etat; // Lire l'état de chaque cellule (0 ou 1)
        Cellules.push_back(etat);
      }
    }

    fichier.close();

    grille=new GrilleClassique(gridWidth, gridHeight, Cellules);


}
void Jeu::Launch(){
    //std::cout<<"Voulez vous utiliser un Motif (fonction non fonctionnelle pour l'instant)\n* Entrez 0 pour utiliser un fichier";
    std::string answer;

	std::cout<<"Entrez le nom du fichier d'entrée\n";

    std::cin>>fname;
    Load(fname);

    std::cout<<"Entrez le nombre d'itérations que voous voulez\n";
    std::cin>>answer;
    stoi(answer)>>this->iterations;

    std::cout<<"Voulez vous utiliser \n1)La console\n2)L'interface Graphique";
    std::cin>>answer;
    if(stoi(answer)==1){
      	Console();
    }
    else if(stoi(answer)==2){
        IG();
    }
    else{
        std::cout<<"Veuillez Réésayer\n";
    }

}

void Jeu::IG(){
  	sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    std::vector<int> cellules;
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
    Save(fname);

	}
}
void Jeu::Console(){
    for (int t=0; t < iterations; t++) {
      grille->afficherGrille();
      grille->update();
    }
}
