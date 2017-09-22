#pragma once
#include "Carte.h"
#include <string>
#include <iostream>
#include <sstream>


class Joueur
{
private:
    const std::string _nom;
    int _nbCarte;
    Carte* _debut;
    Carte* _courante;
    Carte* _fin;
    
public:
    /*
     * Constructeur prenant en paramètre le nom du joueur
     */
    Joueur(const std::string& nom);
    
    /*
     * Méthode qui crée une carte à partir d'une valeur et d'une couleur passé
     * en paramètre et l'ajoute à la fin du paquet du joueur courant.
     * Le nombre de carte du joueur est également incrémenté.
     */
    void ajouterCarte(std::string& valeur, std::string& couleur);
    
    /*
     * Ajoute une carte à la fin du paquet du joueur courant.
     * Le nomnbre de carte du joueur n'est pas incréménté.
     */
    void ajouterCarte(Carte* c);
    
    /*
     * Indique si le joueur a perdu
     */
    bool aperdu();
    
    /*
     * Place le pointeur courant au début du paquet
     */
    void nouveauTour();
    
    /*
     * Déplace le pointeur courant sur la carte suivante
     */
    void carteSuivante();
    
    /*
     * Place les cartes situées entre le pointeur de début et le pointeur courant
     * à la fin du paquet du joueur. Et, place également, les cartes situées entre
     * le début du paquet et le pointeur courant pour le joueur passé en paramètre
     * à la fin du paquet du joueur courant.
     * Le nombre de carte du joueur courant est incrémenté et celui du joueur passé 
     * en paramètre est décrémenté.
     */
    void gagnetour(Joueur& j);
    
    /*
     *Affiche l'ensemble des cartes d'un joueur
     */
    std::string toString();
    
    /*
     * Diminue le nombre de carte du joueur de 1
     */
    void dimNbCarte();
    
    /*
     *Place le pointeur de début sur le pointeur courant
     */
    void debCourant();
    
    
    //Getters et Setters
    /*
     * Renvoie le nom du joueur
     */
    std::string name();
    
    /*
     * Renvoie la carte courante
     */
    Carte* courante();
    
    /*
     * Modification du pointeur de début sur la carte
     */
    void setDebut(Carte* c);
    
    /*
     * Retourne le pointeur de debut
     */
    Carte* deb();
    
    //Destructeur
    ~Joueur();
};

