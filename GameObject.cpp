#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* texturesheet, int x, int y) {
    objectTexture = TextureManager::Load_texture(texturesheet);

    xpos = x;
    ypos = y;

}

void GameObject::Update() {


    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 90;
    srcRect.h = 90;


    desRect.x = xpos;
    desRect.y = ypos;
    desRect.w = srcRect.w  ;
    desRect.h = srcRect.h  ;



}

void GameObject::Render() {
    TextureManager::Draw(objectTexture, srcRect, desRect);
}
