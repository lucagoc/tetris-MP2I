#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*Fonction qui à partir de seulement un ID génère un bloc en mémoire*/
int* generation_bloc(int id);

/*Chaque tetromino de couleur/formes différentes possède un ID différents, voir la documentation correspondante a leur forme pour plus d'informations*/
const int VIDE;
const int O;
const int I;
const int S;
const int Z;
const int L;
const int J;
const int T;

#endif