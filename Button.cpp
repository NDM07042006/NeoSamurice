#include "Button.h"
#include <iostream>

Button::Button(SDL_Renderer* ren, TTF_Font* f, const std::string& text, int x, int y, int w, int h)
    : renderer(ren), font(f), label(text), isHovered(false) {

    rect = { x, y, w, h };
    textColor = { 255, 255, 255, 255 };
    defaultColor = { 70, 70, 70, 255 };
    hoverColor = { 100, 100, 100, 255 };
}

void Button::render() {
    SDL_Rect renderRect = rect;
    int fontSize = 30;

    if (isHovered) {
        renderRect.x -= 5;
        renderRect.y -= 5;
        renderRect.w += 10;
        renderRect.h += 10;
        fontSize = 40;
    }


    SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
    SDL_RenderFillRect(renderer, &renderRect);


    TTF_Font* dynamicFont = TTF_OpenFont("font/ShortBaby.ttf", fontSize);
    if (!dynamicFont) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(dynamicFont, label.c_str(), textColor);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, surface);
    int tw, th;
    SDL_QueryTexture(textTex, NULL, NULL, &tw, &th);
    SDL_FreeSurface(surface);
    TTF_CloseFont(dynamicFont);

    SDL_Rect textRect = {
        renderRect.x + (renderRect.w - tw) / 2,
        renderRect.y + (renderRect.h - th) / 2,
        tw, th
    };

    SDL_RenderCopy(renderer, textTex, NULL, &textRect);
    SDL_DestroyTexture(textTex);
}


bool Button::handleEvent(SDL_Event* e) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    isHovered = (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);

    if (isHovered && e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        return true;
    }

    return false;
}


SDL_Texture* Button::createTextTexture(const std::string& text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Button::setText(const std::string& newText) {
    label = newText;
}

void Button::setColor(SDL_Color newColor) {
    defaultColor = newColor;
}

void Button::setHoverColor(SDL_Color hover) {
    hoverColor = hover;
}
