#include "FontGame.h"
#include <SDL.h>
#include "game.h"


int score;
int highscore;


textBox::textBox() {
	x = 0;
	y = 0;
	c = { 255,255,255 };
	message = "test";
	size = 24;
};
textBox::~textBox() {};

void textBox::renderText() {

	TTF_Init();
	TTF_Font* Sans = TTF_OpenFont("font/ShortBaby.ttf", size);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, message, c);
	TTF_CloseFont(Sans);
	TTF_Quit();

	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.w = surfaceMessage->w;
	Message_rect.h = surfaceMessage->h;
	Message_rect.x = x - (Message_rect.w /2);
	Message_rect.y = y - (Message_rect.h / 2);

	SDL_RenderCopy(Game::renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
