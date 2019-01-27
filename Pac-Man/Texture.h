  /*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.17

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Pac-Man

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

/*

	* Ce Header concerne la classe Texture et ces h�ritiers permettant d'afficher des images sur la fenetre
	* La classe Texture est la classe m�re
	* Texture a 2 h�ritiers : Texte et ButtonImage
	* Texte a 1 h�ritier : ButtonTexte

*/

#include "LIB.h"

#ifndef Texture_H
#define Texture_H

/* *********************************************************
	*					 Constantes
  ********************************************************* */

//--- Constantes concernant la taille des diff�rents tableaux  --------------------------------------------------------------------------------------

// nombre maximal de polices de la font (ici arial)
const Uint8 MAX_FONT = 160;

//--- Constantes concernant la SDL  -----------------------------------------------------------------------------------------------------------------

/*
	SDL_Color name {Red, Green, Blue, Alpha (transparance)}
	chaque parametre est cod� sur 8 bit -> Uint8  (de 0 � 255)
*/

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color Yellow = { 255, 255, 0, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris
const SDL_Color NoColor = { 0, 0, 0, 0 };

// font utilis�e pour ce programme
const std::string fontFile = "arial.ttf";



/* *********************************************************
	*					 Enum
  ********************************************************* */

//--- enum concernant les objets Texture  -----------------------------------------------------------------------------------------------------------

/*
	* type de texte :
	*	-> blended : sans couleur de fond
	*	-> shaded : avec une couleur de fond
*/
enum Texte_Type : Uint8 { blended, shaded };

/*
	* type de transparance :
	*	-> 0 transparance totale
	*	-> 255 totalement visible
*/
enum Transparance_Type : Uint8 { transparent = 0, semiTransparent = 128, nonTransparent = 255 };

/*
	* type de centrage :
	*	-> nocenter : les positions x et y ne changent pas
	*	-> center_x : la position y ne change pas et centre la position x en focntion de la longueur du texte
	*	-> center_y : la position x ne change pas et centre la position y en focntion de hauteur du texte
	*	-> center : centre totalement le texte en fonction de sa longueur et de sa hauteur
*/
enum Center_Type : Uint8 { nocenter, center_x, center_y, center };



/* *********************************************************
	*					 Classes
  ********************************************************* */

//--- Texture --------------------------------------------------------------------------------------------------------------------------------------
/*
	* La classe Texture permet de d'afficher des images sur la fenetre � partir de fichier image (.png, jpg, .bmp)
	* Pour cr�er un objet Texture 2 m�thodes peuvent etre utilis�es :
	*		1] utiliser LoadImage (recommand�)
	*		2] directement utiliser le constructeur (pr�alable : d�ja avoir le ptr SDL_Texture)

*/
class Texture {

	/* *********************************************************
	*					Texture::STATIC
	 ********************************************************* */
public:
	/*
		* Pour cr�er un objet Texture 1] loadImage :

		*	- SDL_Renderer*& renderer				- le ptr sur la variable contenant SDL_Renderer
		*	- std::vector<Texture*>& tabTexture		- le tableau dans lequel sera stock� la Texture (allocation dynamique)
		*	- Uint8 stateScreen, Uint8 select		- les variables qui d�crivent les diff�rents �tat de l'�cran et les sp�cifications de la s�l�ction
		*	- std::string path						- le chemin d'acc�s ainsi que le nom de l'image � partir du fichier (inclure le type .png , .bmp ...)
		*	- std::string msg						- le nom qui permettra d'identifier la Texture dans le tableau
		*	- Uint8 alpha							- la valeur de transparance de la Texture -> enum Transparance_Type
		*	- int x, int y							- les valeurs en pixel de la future position
		*	- unsigned int w, unsigned int h		- les valeurs de longueur et de largeur permettant de changer la d�finition de l'image originale sinon mettre NULL
		*	- Uint8 cnt								- le type de centrage -> enum Center_Type
	*/
	static void loadImage(SDL_Renderer*& renderer, std::vector<Texture*>& tabTexture, Uint8 stateScreen, Uint8 select,
		std::string path, std::string msg, Uint8 alpha, int x, int y, unsigned int w, unsigned int h, Uint8 cnt = nocenter);

	/*
		permet de centrer la Texture selon :
	*	-> nocenter : les positions x et y ne changent pas
	*	-> center_x : la position y ne change pas et centre la position x en focntion de la longueur du texte
	*	-> center_y : la position x ne change pas et centre la position y en focntion de hauteur du texte
	*	-> center : centre totalement le texte en fonction de sa longueur et de sa hauteur
	*/
	static void centrage(int&, int&, int, int, Uint8 cnt = nocenter);


	/* *********************************************************
		*				Texture::METHODES
	 ********************************************************* */
public:
	Texture(SDL_Renderer*& renderer,
		SDL_Texture* image, std::string msg, Uint8 stateScreen, Uint8 select,
		unsigned int x, unsigned int y, int w, int h, Uint8 alpha, Uint8 center = nocenter);
	~Texture();

public:
	// Cr�ation d'un SDL_Rect � partir des positions x, y et des longueur et hauteur
	SDL_Rect rectangle(int xc, int yc, int w, int h);

public: // op�rations sur l'objet et affichage
	// Permet de rendre la Texture au coordonn�es voulues
	virtual void render(int = -1, int = -1);

	// Test les attributs _stateScreen et _select qui correspondent au moment de l'appel puis permet de rendre la Texture au coordonn�es voulues
	virtual void renderTextureTestStates(Uint8 stateScreen, Uint8 select, int x = -1, int y = -1);

	// Test les attributs _stateScreen et _select qui correspondend au moment de l'appel puis permet de rendre la Texture au coordonn�es voulues avec un angle
	virtual void renderTextureTestStatesAngle(Uint8 stateScreen, int xc = -1, int yc = -1, unsigned int angle = 0);

	// Test l'attribut _name qui correspond au moment de l'appel puis permet de rendre la Texture au coordonn�es voulues
	virtual bool renderTextureTestString(std::string msg, int xc = -1, int yc = -1);

	// Test l'attribut _name qui correspond au moment de l'appel puis permet de rendre la Texture au coordonn�es voulues avec un angle
	virtual bool renderTextureTestStringAndStates(std::string msg, Uint8 stateScreen, int xc = -1, int yc = -1);

public: // assesseurs
	inline virtual SDL_Texture* GETtexture() const { return _texture; };
	inline virtual SDL_Texture* GETtextureNonConst() { return _texture; };
	inline virtual SDL_Rect GETdst()const { return _dst; };
	inline virtual int GETdstx()const { return _dst.x; };
	inline virtual int GETdsty()const { return _dst.y; };
	inline virtual int GETdstw()const { return _dst.w; };
	inline virtual int GETdsth()const { return _dst.h; };
	inline virtual std::string GETname() const { return _name; };
	inline virtual Uint8 GETstateScreen() const { return _stateScreen; };
	inline virtual Uint8 GETselect()const { return _select; };
	inline virtual Uint8 GETalpha()const { return _alpha; };
	inline virtual Uint8 GETcenter()const { return _center; };

	inline virtual void SETtexture(SDL_Texture* texture) {
		if (_texture != texture) {
			if (_texture != nullptr) {
				SDL_DestroyTexture(_texture);
				_texture = nullptr;
			}
			_texture = texture;
		}
	};
	inline virtual void SETdstx(int x) { _dst.x = x; };
	inline virtual void SETdsty(int y) { _dst.y = y; };
	inline virtual void SETdstw(int w) { _dst.w = w; };
	inline virtual void SETdsth(int h) { _dst.h = h; };
	inline virtual void SETname(std::string msg) { _name = msg; };
	inline virtual void SETalpha(Uint8 alpha){
		if (_alpha != alpha) {
			_alpha = alpha;
			if (SDL_SetTextureAlphaMod(_texture, _alpha) != 0)
				_alpha = 255;
		}
	}
	inline virtual void SETcenter(Uint8) {
		if (_center != center) {
			_center = center;
			centrage(_dst.x, _dst.y, _dst.w, _dst.h, _center);
		}
	};


protected:// assesseurs
	inline SDL_Renderer *& GETrenderer() { return _renderer; };

	/* *********************************************************
		*				Texture::ATTRIBUTS
	 ********************************************************* */
private:
	// ptr sur le renderer cr�e par la SDL
	SDL_Renderer* _renderer;

	// ptr sur la SDL_Texture : image 
	SDL_Texture* _texture;

	// rectangle des positions en x et y et la longueur et hauteur
	SDL_Rect _dst;

	// nom de la Texture
	std::string _name;

	// ecran dans le quel la Texture s'affiche (titre, play, score)
	Uint8 _stateScreen;

	// selection pour l'affichage (selectnothing, pause, win, lost)
	Uint8 _select;

	// transparance de la Texture
	Uint8 _alpha;

	// centrage de la Texture (nocenter, center_x, center_y, center)
	Uint8 _center;
};
#endif Texture_H

#ifndef Texte_H
#define Texte_H
//--- Texte ----------------------------------------------------------------------------------------------------------------------------------------

class Texte : public Texture {

	/* *********************************************************
		*				Texte::STATIC
	 ********************************************************* */
public:
	/*
		permet de cr�er un ptr sur une SDL_Texture pour par la suite cr�er un objet Texte
		*	-> retourne un ptr de la nouvelle SDL_Texture
	*/
	static SDL_Texture* createSDL_TextureFromTexte(SDL_Renderer*& renderer, Uint8 type,
		std::string message, SDL_Color color, SDL_Color colorback, TTF_Font* font);

	/*
		cr�ation et ajout d'un objet Texte dans le tableau de Texte choisi
	*/
	static void loadTexte(SDL_Renderer*& renderer, TTF_Font* font[], Uint8 stateScreen, Uint8 select,
		std::vector<Texte*>& tabTexte, Uint8 type, std::string msg,
		SDL_Color color, SDL_Color backcolor, Uint8 size, int x, int y, Uint8 alpha, Uint8 cnt = nocenter);

	/*
		cr�er un ptr sur SDL_Texture temporaire pour afficher le texte � l'�cran
		le ptr et la SDL_Texture sont d�truit apr�s l'affichage
	*/
	static void writeTexte(SDL_Renderer*& renderer, TTF_Font* font[], Uint8 type, std::string msg, SDL_Color color,
		SDL_Color backcolor, Uint8 size, unsigned int x, unsigned int y, Uint8 cnt = nocenter);


	/* *********************************************************
		*				Texte::METHODES
	 ********************************************************* */
public:
	Texte(SDL_Renderer*& renderer, TTF_Font* font[],
		SDL_Texture* image, std::string msg, Uint8 stateScreen, Uint8 select, int x, int y, int w, int h,
		Uint8 type, SDL_Color txtcolor, SDL_Color backcolor, Uint8 size, Uint8 alpha, Uint8 center = nocenter);
	~Texte();

public: // op�rations sur l'objet
	/*
		test de 2 couleurs de type SDL_Color
		*	-> retourne false si les 2 couleurs sont diff�rentes
		*	-> retourne true si les 2 couleurs sont les meme
	*/
	virtual bool isSameColor(SDL_Color, SDL_Color) const;

public:
	/*
		recentre le Texte lors de changement de taille du texte
	*/
	virtual void resizeTexte();

public: // assesseurs
	inline virtual Uint8 GETtype()const { return _type; };
	inline virtual SDL_Color GETtxtcolor() const { return _txtcolor; };
	inline virtual SDL_Color GETbackcolor() const { return _backcolor; };
	inline virtual Uint8 GETsize()const { return _size; };

	virtual void SETname(std::string msg);
	virtual void SETtype(Uint8 type);
	virtual void SETsize(Uint8 type);
	virtual void SETtxtcolor(SDL_Color txtcolor);
	virtual void SETbackcolor(SDL_Color backcolor);

protected:
	inline TTF_Font** GETfont() { return _font; };

	/* *********************************************************
		*				Texte::ATTRIBUTS
	 ********************************************************* */
private:

	// tableau des diff�rents polices de la font 
	TTF_Font* _font[MAX_FONT];

	/*
		* type de texte :
		*	-> blended : sans couleur de fond
		*	-> shaded : avec une couleur de fond
	*/
	Uint8 _type;

	// couleur appliqu�e au texte
	SDL_Color _txtcolor;

	// couleur appliqu�e au sous texte
	SDL_Color _backcolor;

	// taile du texte (int 1 - 160)
	Uint8 _size;
};
#endif Texte_H

#ifndef ButtonImage_H
#define ButtonImage_H
//--- ButtonImage ---------------------------------------------------------------------------------------------------------------------------------------

class ButtonImage : public Texture {

	/* *********************************************************
		*				ButtonImage::STATIC
	 ********************************************************* */
public:
	/*
		cr�ation et ajout d'un objet ButtonTexte dans le tableau de ButtonTexte choisi
	*/
	static void createButtonImage(SDL_Renderer*& renderer, std::vector<ButtonImage*>& tabButtonImage, Uint8 stateScreen, Uint8 select,
		std::string path, std::string msg, Uint8 alpha, int x, int y, unsigned int w, unsigned int h, Uint8 cnt = nocenter);

	/* *********************************************************
						ButtonImage::METHODES
	 ********************************************************* */
public:
	ButtonImage(SDL_Renderer*& renderer,
		SDL_Texture* image, const std::string& msg, Uint8 stateScreen, Uint8 select, int x, int y, int w, int h,
		Uint8 alpha, SDL_Texture* imageOn, Uint8 center = nocenter);
	~ButtonImage();

public: // op�rations sur l'objet
	virtual unsigned int searchButtonImage(std::string msg, Uint8 stateScreen, signed int x, signed int y);
	virtual unsigned int searchButtonImageName(std::string& msg, Uint8 stateScreen);

	virtual bool renderButtonImage(Uint8 stateScreen);
	virtual bool renderButtonImageTestString(Uint8 stateScreen, std::string& msg, int newx = -1, int newy = -1, Uint8 cnt = nocenter);

	// alterne l'attribut bool�en _on
	virtual void changeOn();

public: // assesseurs
	virtual SDL_Texture* GETimageOn() const;
	virtual bool GETon() const;

	virtual void SETname(std::string msg);
	virtual void SETalpha(Uint8 alpha);
	virtual void SETon(bool);


	/* *********************************************************
		*				ButtonImage::ATTRIBUTS
	 ********************************************************* */
private:
	// ptr sur la SDL_Texture : image du bouton activ�
	SDL_Texture* _imageOn;

	// bouton on/off : permet de changer la couleur du bouton
	bool _on;
};
#endif ButtonImage_H

#ifndef ButtonTexte_H
#define ButtonTexte_H
//--- ButtonTexte ---------------------------------------------------------------------------------------------------------------------------------------
/*

	ButtonTexte :
	Cette classe est la repr�sentation d'un objet ButtonTextes qui est heriti� de la classe m�re Texte

	Un ButtonTextes est d�fini par une image et une imageOn qui sont contenu dans SDL_Texture* de la classe m�re et celle-ci
	Cet objet h�rite de tous les attributs de la classe Texture
	_on repr�sente l'�tat du bouton l'image est normal ou On

	searchButtonTexte permet de chercher le bouton en fonction de son nom ainsi que de l'ecran et de la position x,y
	renderButtonTexteTexte permet d'afficher le bouton avec l'aide de la fonction de la SDL2.0.6 SDL_RenderCopy
	resetOnstateScreen permet de reset l'image si l'on n'est plus sur la bonne s�l�ction ou sur le bon �cran
	resetOnPlayer permet de reset l'image si le joueur s�l�ctionner n'est plus le meme
	changeOn permet de changer entre l'imageOn et l'image

*/
class ButtonTexte : public Texte {

	/* *********************************************************
		*				ButtonTexte::STATIC
	 ********************************************************* */
public:
	/*
		cr�ation et ajout d'un objet ButtonTexte dans le tableau de ButtonTexte choisi
	*/
	static void createButtonTexte(SDL_Renderer*& renderer, TTF_Font* font[], Uint8 stateScreen, Uint8 select,
		std::vector<ButtonTexte*>& tabButtonTexte, Uint8 type, std::string msg,
		SDL_Color color, SDL_Color backcolor, Uint8 size, int x, int y, Uint8 alpha, Uint8 centerButtonTexte = nocenter);


	/* *********************************************************
		*				ButtonTexte::METHODES
	 ********************************************************* */
public:
	ButtonTexte(SDL_Renderer *renderer, TTF_Font *font[],
		SDL_Texture* image, std::string msg, Uint8 stateScreen, Uint8 select, int x, int y, int w, int h,
		Uint8 type, SDL_Color txtcolor, SDL_Color backcolor, Uint8 size, Uint8 alpha, SDL_Texture* imageOn, Uint8 center = nocenter);
	~ButtonTexte();

public: // op�rations sur l'objet
	virtual bool searchButtonTexte(std::string msg, Uint8 stateScreen, signed int x, signed int y);
	virtual bool searchButtonTexteName(std::string msg, Uint8 stateScreen);

	virtual void resetOnstateScreen(Uint8 select, unsigned int selectnothing);
	virtual void resetOnPlayer(unsigned int, std::vector<std::string>);
	virtual bool renderButtonTexte(Uint8 stateScreen);
	virtual bool renderButtonTexteTestString(Uint8 stateScreen, std::string msg, int newx = -1, int newy = -1, Uint8 cnt = nocenter);

	// alterne l'attribut bool�en _on
	virtual void changeOn();

public: // assesseurs
	virtual SDL_Texture* GETimageOn() const;
	virtual bool GETon() const;

	virtual void SETname(std::string msg);
	virtual void SETalpha(Uint8 alpha);
	virtual void SETon(bool);


	/* *********************************************************
		*				ButtonTexte::ATTRIBUTS
	 ********************************************************* */
private:
	// ptr sur la SDL_Texture : image du bouton activ�
	SDL_Texture* _imageOn;

	// bouton on/off : permet de changer la couleur du bouton
	bool _on;
};
#endif ButtonTexte_H

