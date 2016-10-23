#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameController.h"
#include <string>

int main()
{
	std::srand(time(NULL));
	GameController gc;

	gc.Run();
	// RUNS THE WHOLE GAME


	return 0;
}