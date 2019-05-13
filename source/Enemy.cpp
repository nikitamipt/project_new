#pragma once

#include "Entity.cpp"

using namespace sf;


//этот класс для тупой мишени, которая
class Enemy : public Entity{
public:

    Enemy(Texture &image) {
        sprite.setTexture(image);
        life = false;
        update(0);
    }


    bool update(float time1) {
        if (!life) {
            srand(time(0));
            rect = FloatRect((1 + (rand()%(H-2)))*16, (1 + (rand()%(W-2)))*16, 16, 16);
            sprite.setTextureRect(IntRect(18, 0, 16, 16) );
            sprite.setPosition(rect.left, rect.top);
            life = true;
        }
        return true; //он дальше нигде не используется
    }

};

