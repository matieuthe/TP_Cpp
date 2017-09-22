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

	//un choix de mod�lisation simple: les cartes se chainent elles m�me 
	/// \brief pointeur sur la carte suivante de la main
	//Carte* _suivante;

	//un jeu des 52 cartes possibles, le m�me peu importe l'instance, on a la repr�sentation chaine de caract�re de la carte Figure/Couleur � l'intersection [Couleur][Figure]
	//permet de montrer les attributs statiques et accessoirement de g�n�rer les mains plus facilement � partir du fichier de donn�es qui repr�sente l'ordre des cartes
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
	Carte* suiv(); //normalement un getters serait const et renverrait "const Carte*" pour �viter la modification de la carte depuis l'ext�rieur de la classe, mais les attributs de la classe sont const donc non modifiables, pour simplifier on autorise l'acc�s en �criture au pointeur suivant pour changer le chainage des cartes
	//une autre fa�on aurait �t� de d�clarer const Carte* suiv() const, et de mettre le pointeur suiv mutable dans la d�claration de l'attribut, mais comme Figure et Couleur sont des attributs constants, on peut faire comme �a et �a revient au m�me
    //@}

    /**
     * \brief Teste l'egalit� de 2 cartes, au niveau de leur valeur.
     * \param c La carte avec laquelle tester l'egalite.
     * \return Vrai si les cartes ont la meme valeur, faux sinon.
     */
    bool egale(const Carte* c) const;

    /**
     * \brief Teste la superiorite de 2 cartes au niveau de leur valeur.
     * \param c La carte avec laquelle tester la superiorite.
     * \return Vrai si la carte a une valeur superieure � celle de c, faux sinon.
     */
    bool superieure(const Carte* c) const;
	
	/**
	* \brief met � jour l'adresse de la carte suivante
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
    
	//m�thodes non li�es � une instance
	static std::string toString( Couleur c,Figure f);////converti un couple Couleur Figure en repr�sentation string pour initier le paquet statique
	static Figure stringToFigure(const std::string& ch);//converti un string en Figure
	static Couleur stringToCouleur(const std::string& ch);//converti un string en Couleur
	static void generePaquet(); //initie l'attribut statique paquet avec la liste des 52 cartes possibles


};


//-----------------------------------------------------------------------------
#endif // CARTE_H

