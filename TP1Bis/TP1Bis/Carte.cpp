#include "Carte.h"
using namespace std;

//Tableau statique
string Carte::paquet[4][13];

//Constructeurs
Carte::Carte( Couleur c, Figure v):_couleur(c),_figure(v){
}

bool Carte::egale(const Carte* c) const{
    return this->_figure == c->getFigure();
}

Figure Carte::getFigure() const{
    return this->_figure;
}

bool Carte::superieure(const Carte* c) const{
    return this->_figure > c->getFigure();
}

Carte::~Carte(){
    /*
     * Pas de new donc rien
     */
}

Figure Carte::stringToFigure(const std::string& ch)
{
	if (ch == "roi") return roi;
	if (ch == "dame") return dame;
	if (ch == "valet") return valet;
	if (ch == "dix") return dix;
	if (ch == "neuf") return neuf;
	if (ch == "huit") return huit;
	if (ch == "sept") return sept;
	if (ch == "six") return six;
	if (ch == "cinq") return cinq;
	if (ch == "quatre") return quatre;
	if (ch == "trois") return trois;
	if (ch == "deux") return deux;
	if (ch == "as") return as;
	
	exit(EXIT_FAILURE);
}
Couleur Carte::stringToCouleur(const std::string& ch)
{
	if (ch == "pique") return pique;
	if (ch == "trefle") return trefle;
	if (ch == "carreau") return carreau;
	if (ch == "coeur") return coeur;
	exit(EXIT_FAILURE);
}

std::string Carte::toString(Couleur c, Figure f)
{
    std::string str;
    switch(f)
    {
        case as:
            str = "as";
            break;
            case deux:
            str = "deux";
            break;
        case trois:
            str = "trois";
            break;
        case quatre:
            str = "quatre";
            break;
        case cinq:
            str = "cinq";
            break;
        case six:
            str = "six";
            break;
        case sept:
            str = "sept";
            break;
        case huit:
            str = "huit";
            break;
        case neuf:
            str = "neuf";
            break;
        case dix:
            str = "dix";
            break;
        case valet:
            str = "valet";
            break;
        case dame:
            str = "dame";
            break;
        case roi:
            str = "roi";
            break;
        default:
            // cette position ne devrait jamais etre atteinte
            assert(false);
            break;
    }
	str += "/";
	switch (c)
	{
	case pique:
		str+= "pique";
		break;
	case trefle:
		str+= "trefle";
		break;
	case coeur:
		str+= "coeur";
		break;
	case carreau:
		str+= "carreau";
		break;
	default:
		// cette position ne devrait jamais etre atteinte
		assert(false);
		break;
	}
    return str;
}

std::string Carte::toString() const
{
	return paquet[_couleur][_figure];
}

void Carte::setSuiv(Carte* n)  
{
	_suivante = n;
}

Carte* Carte::suiv()  
{ 
	return _suivante; 
}

void Carte::generePaquet()
{
	if (paquet[0][0].empty())
	{
		for (uint f = 0; f <= 12; ++f)
			for (uint c = 0; c < 4; ++c)
				paquet[c][f] = toString(static_cast<Couleur>(c),static_cast<Figure>(f));
	}
}
