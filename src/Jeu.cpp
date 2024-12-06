//
// Created by lucas on 05/12/2024.
//
#include "../hea/Jeu.h"

Jeu::Jeu(){
  this->gridHeight = 5;
  this->gridWidth = 5;
  this->grille = new GrilleClassique();
};

void Jeu::Save(){
    std::ofstream file;
    file.open("../output", std::ios::out);
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

void Jeu::Load(){
  //std::vector <StandardCellule> v;
  //void Jeu::Load() {
    std::ifstream fichier("../input"); // Chemin du fichier à charger
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
        std::cout<<etat<<std::endl;
        Cellules.push_back(etat);
      }
    }

    fichier.close();

    grille=new GrilleClassique(gridWidth, gridHeight, Cellules);


}
void Jeu::Launch(){
	Load();
    grille->afficherGrille();
    Save();
}


