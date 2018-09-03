#include "lib.h"
#include "Pac_Man_lib.h"
#include "mainLoop.h"
#include "renduecran.h"
#include "sdl.h"
#include "deleteAll.h"

int main(int argc, char** argv) {
	sysinfo information;

	srand((unsigned int)time(NULL));

	logfileconsole("________PROGRAMME START________");

	initsdl(information.ecran.window, information.ecran.renderer, information.allTextures.font);
	initfile(information);
	calculimage(information);

	ecrantitre(information);

	mainLoop(information);


	deleteAll(information);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	logfileconsole("SDL_Quit Success");
	logfileconsole("________PROGRAMME FINISH________");
	return 0;
}