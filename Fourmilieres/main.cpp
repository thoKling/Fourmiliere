#include "Application.h"

#include <iostream>

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	Application app;
	app.start();
	return EXIT_SUCCESS;
}