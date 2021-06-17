#pragma once

#define toRadians PI / 180.0
#define toDegrees 180.0 / PI

#define WINDOWS_HEIGHT 768
#define WINDOWS_WIDTH 1024

#define MS_PER_UPDATE 1000/60

class Config {
public:
	static void setNbrOfTickPerTurn(int newNbrOfTickPerTurn);
	static int getNbrOfTickPerTurn();
	// True en mode debug
	static bool debugMode;

private:
	// Nombre de tick d'update entre chaque tour de jeu
	static int _nbrOfTickPerTurn;
};