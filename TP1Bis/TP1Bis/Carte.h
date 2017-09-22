#ifndef CARTE_H
#define CARTE_H
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <cassert>
typedef unsigned int uint;
typedef const uint cuint;

//-----------------------------------------------------------------------------
/**
 * \brief Type pour representer la couleur d'une carte.
 */
enum Couleur
{
    pique = 0,
    trefle,
    coeur,
    carreau
};
//-----------------------------------------------------------------------------
/**
 * \brief Type pour representer la valeur d'une carte.
 */
enum Figure
{
    deux,
    trois,
    quatre,
    cinq,
    six,
    sept,
    huit,
    neuf,
    dix,
    valet,
    dame,
    roi,
	as
};
//-----------------------------------------------------------------------------
/**
 * \brief Representation d'une carte.
 * \author Christian Raymond (2016)
 */
class Carte
{

	/// \brief Couleur de la carte.
	const Couleur _couleur;

	/// \brief Valeur de la carte.
	const Figure _figure;

	//un choix de modélisation simple: les cartes se chainent elles même 
	/// \brief pointeur sur la carte suivante de la main
	//Carte* _suivante;

	//un jeu des 52 cartes possibles, le même peu importe l'instance, on a la représentation chaine de caractère de la carte Figure/Couleur à l'intersection [Couleur][Figure]
	//permet de montrer les attributs statiques et accessoirement de générer les mains plus facilement à partir du fichier de données qui représente l'ordre des cartes
	static std::string paquet[4][13];

public:
    Carte* _suivante;
    /// \name Constructeurs et destructeur
    //@{
    /**
     * \brief Constructeur.
     * \param c	La couleur de la carte.
     * \param v	La hauteur de la carte.
     */
    Carte( Couleur c, Figure v);
    //@}
	
	
	Carte(Couleur c, Figure v, Carte* s);
   
    /**
     * \brief Retourne la carte suivante.
     * \return La carte suivante.
     */
	Carte* suiv(); //normalement un getters serait const et renverrait "const Carte*" pour éviter la modification de la carte depuis l'extérieur de la classe, mais les attributs de la classe sont const donc non modifiables, pour simplifier on autorise l'accès en écriture au pointeur suivant pour changer le chainage des cartes
	//une autre façon aurait été de déclarer const Carte* suiv() const, et de mettre le pointeur suiv mutable dans la déclaration de l'attribut, mais comme Figure et Couleur sont des attributs constants, on peut faire comme ça et ça revient au même
    //@}

    /**
     * \brief Teste l'egalité de 2 cartes, au niveau de leur valeur.
     * \param c La carte avec laquelle tester l'egalite.
     * \return Vrai si les cartes ont la meme valeur, faux sinon.
     */
    bool egale(const Carte* c) const;

    /**
     * \brief Teste la superiorite de 2 cartes au niveau de leur valeur.
     * \param c La carte avec laquelle tester la superiorite.
     * \return Vrai si la carte a une valeur superieure à celle de c, faux sinon.
     */
    bool superieure(const Carte* c) const;
	
	/**
	* \brief met à jour l'adresse de la carte suivante
	* \param n la nouvelle adresse
	*/
	void setSuiv(Carte* n) ;
    
    /*
     * Retourne la valeur de la carte
     */
    Figure getFigure() const;
    
	 /**
     * \brief Retourne la representation string d'une carte
     */
    std::string toString() const;
    
    // Destructeur
    ~Carte();
    
	//méthodes non liées à une instance
	static std::string toString( Couleur c,Figure f);////converti un couple Couleur Figure en représentation string pour initier le paquet statique
	static Figure stringToFigure(const std::string& ch);//converti un string en Figure
	static Couleur stringToCouleur(const std::string& ch);//converti un string en Couleur
	static void generePaquet(); //initie l'attribut statique paquet avec la liste des 52 cartes possibles


};


//-----------------------------------------------------------------------------
#endif // CARTE_H

