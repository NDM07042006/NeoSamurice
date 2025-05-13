#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Button {
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text,
           int x, int y, int w, int h);

    void render();
    bool handleEvent(SDL_Event* e);

    void setText(const std::string& newText);
    void setColor(SDL_Color newColor);
    void setHoverColor(SDL_Color hover);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    std::string label;
    SDL_Rect rect;

    SDL_Color textColor;
    SDL_Color defaultColor;
    SDL_Color hoverColor;

    bool isHovered;

    SDL_Texture* createTextTexture(const std::string& text, SDL_Color color);
};



#endif // BUTTON_H_INCLUDED
