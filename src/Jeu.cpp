//
// Created by lucas on 05/12/2024.
//
#include "../hea/Jeu.h"

void Jeu::Save(){

}
void Jeu::Load(){
  //std::vector <StandardCellule> v;
  //void Jeu::Load() {
    std::ifstream fichier("grille.txt"); // Chemin du fichier à charger
    if (!fichier.is_open()) {
      std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
      return;
    }

    int lignes, colonnes;
    fichier >> lignes >> colonnes; // Lecture des dimensions de la grille
    std::vector<int> Cellules

    for (int i = 0; i < lignes; ++i) {
      for (int j = 0; j < colonnes; ++j) {
        bool etat;
        fichier >> etat; // Lire l'état de chaque cellule (0 ou 1)
        Cellules.push_back(etat);
      }
    }

    fichier.close();

    GrilleClassique Grille(colonnes, lignes, Cellules);


}


void Jeu::Launch(){
  Grille.afficherGrille();
}


