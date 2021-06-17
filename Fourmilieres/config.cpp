#include "config.h"

int Config::_nbrOfTickPerTurn = 16;
bool Config::debugMode = false;

void Config::setNbrOfTickPerTurn(int newNbrOfTickPerTurn) {
	_nbrOfTickPerTurn = newNbrOfTickPerTurn;
}

int Config::getNbrOfTickPerTurn() {
	return _nbrOfTickPerTurn;
}