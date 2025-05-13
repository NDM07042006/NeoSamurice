#pragma once
#include <SDL_ttf.h>

struct textBox {

	int x;
	int y;
	SDL_Color c;
	const char* message;
	int size;

	textBox();
	~textBox();

	void renderText();

};
