#include "Joueur.h"
using namespace std;

Joueur::Joueur(const string& nom):_nom(nom){
    this->_nbCarte = 0;
}

Joueur::~Joueur(){
    Carte* temp = this->_debut;
    Carte* tempBis;
    //Destruction de toutes les cartes du joueur
    for(int i = 0; i < _nbCarte; i++){
        tempBis = temp->suiv();
        delete temp;
        temp = tempBis;
    }
}

void Joueur::ajouterCarte(string& valeur, string& couleur){
    Carte* c = new Carte(Carte::stringToCouleur(couleur),Carte::stringToFigure(valeur));
    this->ajouterCarte(c);
    this->_nbCarte++;
}

void Joueur::ajouterCarte(Carte* c){
    if(this->_nbCarte == 0){
        this->_debut = c;
        this->_courante = c;
        this->_fin = c;
    }else{
        this->_fin->setSuiv(c);
        this->_fin = c;
    }
}

void Joueur::gagnetour(Joueur& j){
    //On met les carte entre le début et le pointeur courant à la fin du jeu
    Carte* temp = this->_debut; //pointeur temp pour aller de début à courant
    
    while(temp != this->_courante){
        //place la carte à la fin du paquet
        this->ajouterCarte(temp);
        temp = temp->suiv();
    }
    /* Pour la dernière carte */
    this->ajouterCarte(temp);
    this->_debut = temp->suiv();
    
    //Pour finir : Ajout de(s) carte(s) de l'adversaire
    temp = j.deb(); //On place temp au début du paquet du joueur j
    Carte* cour = j.courante();
    
    while (temp != cour){
        //place la carte temp du paquet du joueur j à la fin du paquet du joueur courant
        this->ajouterCarte(temp);
        //Diminue le nombre de carte du joueur j de 1
        j.dimNbCarte();
        this->_nbCarte++;
        temp = temp->suiv();
    }
    //Pour la dernière carte
    this->ajouterCarte(temp);
    this->_nbCarte++;
    j.dimNbCarte();
    j.setDebut(temp->suiv());
}


string Joueur::toString(){
    string res = " " + this->_nom + "\n";
    Carte* temp = this->_debut;
    for(int i=0; i< this->_nbCarte; i++){
        res+= temp->toString() + "\n";
        temp = temp->suiv();
    }
    return res;
}

bool Joueur::aperdu(){
    return this->_nbCarte == 0;
}

string Joueur::name(){
    return this->_nom;
}

Carte* Joueur::deb(){
    return this->_debut;
}

void Joueur::setDebut(Carte* c){
    this->_debut = c;
}

void Joueur::dimNbCarte(){
    this->_nbCarte--;
}

void Joueur::debCourant(){
    this->_debut = this->_courante;
}

Carte* Joueur::courante(){
    return this->_courante;
}

void Joueur::nouveauTour(){
    this->_courante = this->_debut;
}

void Joueur::carteSuivante(){
    this->_courante = this->_courante->suiv();
}


