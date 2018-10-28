/*

	Pac-Man
	Copyright SAUTER Robin and Joeffrey VILLERONCE 2018-2019 (robin.sauter@orange.fr)
	last modification on this file on version:0.15

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

#ifndef IHM_H
#define IHM_H

#include "lib.h"

class IHM {
public:
	// initialisation des fichiers
	static void initfile(const std::string& log);

	// permet de d'écrire sur la console ainsi que dans le fichier log.txt
	static void logfileconsole(const std::string &msg);

	static void logSDLError(std::ostream &os, const std::string &msg);

	/*
		initialisation de la fenetre, du renderer et du tableau contenant les polices d'ecriture
		retourne true si aucune erreur n'est survenue
		retourne false si une erreur est survenue
	*/
	static bool initsdl(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);

	static void initTile(Tile& map, bool wall, Uint8 entity);

	// creer une forme à partir de la case visée, celle-ci représente le point en haut à gauche de la forme
	static void forme(Tile& tmap, std::vector<std::vector<Tile>>& map, Uint8 length, Uint8 height, bool wall = true);
	
	// Initialisation d'un niveau unique de Pacman
	static void initGrid(Map& map);
	
	/*
		Chargement Textures en fonction de l'ecran (menu, play, score):
		 -> des images
		 -> des boutons
		 -> des textes
	*/
	static void calculimage(Sysinfo&);


public:
	// Handle Mouse Event	BUTTON_LEFT, BUTTON_RIGHT
	static void mouse(Sysinfo& sysinfo, SDL_Event event);
	
	// recherche du bouton par comparaison de string et des positions x et y du clic
	static void cliqueGauche(Sysinfo& sysinfo, SDL_Event event);

	/*
		Demande au joueur son pseudo pour etre placé dans le tableau des scores
		Ne gère que les minuscules et les chiffres 0 à 9 qui ne sont pas sur le pavé numérique
		Fonctionne par cast avec le tableau ASCII
		-> retourne le nom entré par le joueur (std::string)
	*/
	static std::string getName(SDL_Renderer*& renderer, TTF_Font* font[], Var& var,
		std::vector<Texte*> txtScore, std::vector<Texte*> tabScore, unsigned int position);

	/*
		Tri du tableau des scores dans le sens décroissant
		recherche si le score fait lors de cette partie est dans le TOP10
		-> retourne la position du joueur
		-> retourne -1 si le joueur ne figure pas dans le TOP10
	*/
	static int8_t topScore(std::vector<ScorePlayer>& tabScorePlayer, unsigned int score);



public:
	// Affiche toutes les textures ainsi que les boutons ayant l'attribut _statescreen == STATEecrantitre
	static void ecrantitre(Sysinfo& syinfo);
	
	// Affiche toutes les textures ainsi que les boutons ayant l'attribut _statescreen == STATEscore
	static void ecranScore(Sysinfo& syinfo);

	/*
		Affiche toutes les textures ainsi que les boutons ayant l'attribut _statescreen == STATEplay
		Cette fonction est appelée à la meme fréquence que la boucle principale
	*/
	static void alwaysrender(Sysinfo& syinfo);

	/*
		Affiche la map du niveau chargé :
		-> murs
		-> couloir
		-> bonus
	*/
	static void afficherMap(Sysinfo& sysinfo);

	/*
		Affiche le temps passé depuis le début du New Game
		Compte sur le fait que la boucle fonctionne à la fréquence de l'écran (ici 60Hz)
		si la boucle principale prend plus que 1/60 s alors le temps affiché sera décalé
	*/
	static void calculTime(GameTime& gameTime);



public:
	// Destruction des allocations dynamiques et de la fenetre
	static void deleteAll(Sysinfo&);
};
template<class T>
T max(T& a, T& b) {
	if (a >= b)
		return a;
	else
		return b;
}
template<class T>
void deleteDyTabPlayerAndTextures(T& dytab, const std::string& name) {
	unsigned int size = dytab.size();
	for (unsigned int i = 0; i < size; i++) {
		IHM::logfileconsole("Delete " + name + " name = " + dytab[i]->GETname() + " Success");
		delete dytab[i];
		dytab[i] = nullptr;
	}
	for (unsigned int i = 0; i < size; i++)
		dytab.pop_back();
	if (dytab.size() != 0)
		IHM::logfileconsole("___________ERROR : " + name + ".size() != 0");
	else
		IHM::logfileconsole("Delete ALL " + name + " Success");
}


#endif
