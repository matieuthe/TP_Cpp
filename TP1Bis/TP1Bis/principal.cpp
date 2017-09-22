/**
 * \brief Main du TP1.
 *
 * Usage :  .\TP1 < fichier_a_lire
 */

#include "Bataille.h"
#include <iostream>
#include <fstream> 

int main()
{
	std::ifstream fin("/Users/mathieuthe/Documents/cours/4A/POO/TP1Bis/TP1Bis/donne.txt");
	if (!fin) {
		std::cerr << "fichier introuvable" << std::endl;
		exit(EXIT_FAILURE);
	}

	Bataille bat(fin,"Obama","Poutine");
	fin.close();
	std::cout << "Gagnant est joueur "<<bat.joue();
    return EXIT_SUCCESS;
}

