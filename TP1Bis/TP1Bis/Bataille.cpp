#include "Bataille.h"
#include <fstream>
using namespace std;

void Bataille::distribue(std::ifstream& fichier){
    //On gŽnre le paquet static permettant de faire un toString des cartes
    Carte::generePaquet();
    string couleurCarte;
    string valeurCarte;
    bool choixJoueur = true;
    
    if(fichier){
        //On lit chaque ligne du fichier et on ajoute les cartes correspondantes au joueur1 ou 2
        while(fichier >> valeurCarte >> couleurCarte){
            if(choixJoueur){
                _joueur1.ajouterCarte(valeurCarte, couleurCarte);
            }else{
                _joueur2.ajouterCarte(valeurCarte, couleurCarte);
            }
            choixJoueur = !choixJoueur;
        }
    }
}

Bataille::Bataille(std::ifstream& name, const std::string& j1, const std::string& j2):_joueur1(j1), _joueur2(j2){
    this->distribue(name);
}

Bataille::~Bataille(){
    /*
     * Pas de new donc vide
     */
}


uint Bataille::joue()
{
	_joueur1.nouveauTour();
	_joueur2.nouveauTour();
	// Affichages des paquets 
	std::cout << "Les paquets de depart sont :" << std::endl;
	std::cout << "Paquet de :" <<  _joueur1.toString() << std::endl;
	std::cout << "Paquet de  :" << _joueur2.toString() << std::endl;
    
	// Boucle principale : le jeu est termine, si une des listes est vide: cad sir un joueur n'a plus de cartes
	std::cout << "Boucle principale" << std::endl;
	while (!_joueur1.aperdu() && !_joueur2.aperdu())
	{
		std::cout << std::endl<<"_________________________________________________________" << std::endl;
		if (_joueur1.aperdu())
		{
			std::cout << "Joueur2 " << _joueur2.name() << " a gagnŽ" << std::endl;
			return 2;
		}

		if (_joueur2.aperdu())
		{
			std::cout << "Joueur1 " << _joueur1.name() << " a gagnŽ" << std::endl;
			return 1;
		}
		
        // detection d'une bataille (i.e. les deux cartes ont la meme valeur)
        //cout << _joueur1.courante() << "  " << _joueur2.courante() << "\n";
		while (_joueur1.courante()->egale(_joueur2.courante()))
		{
			std::cout << "***** bataille ******* " << std::endl;
			std::cout << "Carte de Joueur1 :" << _joueur1.name() << ": ";
			std::cout << _joueur1.courante()->toString() << std::endl;
			std::cout << "Carte de Joueur2 :" << _joueur2.name() << ": ";
			std::cout << _joueur2.courante()->toString() << std::endl;
			std::cout << "***********************"<< std::endl;

			//on suit la règle où on regarde la carte suivante directement (pas la règle où on en retourne une avant et on compare la suivante): celui qui à tous les as au départ gagne à coup sur suivant cette règle
			_joueur1.carteSuivante();
			_joueur2.carteSuivante();
			if (_joueur2.courante()==nullptr && _joueur1.courante()==nullptr)
			{
				std::cout << "PAT!" << std::endl;
				return 0; //PAT à la bataille
			}
			
			if (_joueur1.aperdu())
			{
				return 2;
			}

			if (_joueur2.aperdu())
			{
				return 1;
			}
		}


		if (_joueur1.courante()->superieure(_joueur2.courante()))
		{
			std::cout << "****Joueur1 gagne le tour*****" << std::endl;
			_joueur1.gagnetour(_joueur2);//empoche toutes les cartes et les met à la fin de son jeu

		}
		else
		{
			std::cout << "****Joueur2 gagne le tour*****" << std::endl;
			_joueur2.gagnetour(_joueur1);
		}

		std::cout << "Carte de Joueur1 :" << _joueur1.name() << ": ";
		std::cout << _joueur1.courante()->toString() << std::endl;
		std::cout << "Carte de Joueur2 :" << _joueur2.name() << ": ";
		std::cout << _joueur2.courante()->toString() << std::endl;
		std::cout << "********************************" << std::endl;

		_joueur1.nouveauTour();
		_joueur2.nouveauTour();
		std::cout << "Žtat des mains aprs le tour:" << std::endl;
		std::cout<<_joueur1.toString();
		std::cout  << std::endl;
		std::cout << _joueur2.toString();
	}


	if (_joueur1.aperdu())
	{
		std::cout << "Joueur2 " << _joueur2.name() << " a gagnŽ" << std::endl;
		return 2;
	}

	//si on arrive là c'est le joueur1 qui a gagné
	std::cout << "Joueur1 " << _joueur1.name() << " a gagnŽ" << std::endl;
	return 1;
	
}
