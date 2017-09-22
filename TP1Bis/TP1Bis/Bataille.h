#pragma once
#include "Carte.h"
#include "Joueur.h"
#include <algorithm>
#include <iostream>
#include <string>

typedef unsigned int uint;
typedef const uint cuint;



class Bataille
{
	Joueur _joueur1;
	Joueur _joueur2;
public:
    /*
     * Constructeur de la bataille qui créer les deux joueurs et lance la méthode
     * distribue.
     */
    Bataille(std::ifstream& name, const std::string& j1, const std::string& j2);
    
    /*
     * Répartie les cartes présentes dans le fichier entre les deux joueurs
     */
	void distribue(std::ifstream& fichier);
    
    /*
     * Méthode qui lance la partie
     */
	uint joue();
    
    /*
     * Destructeur
     */
	~Bataille();
};

