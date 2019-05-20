#pragma once

#include "Entity.cpp"
//#include "Bot_war_soldier.cpp"
#include "Bot_war_soldier_without_walls.cpp"
using namespace sf;


class Bullet : public Entity {
public:
    int age; //Bullet has only 10 "days" for living((
    Soldier_without_walls/*Soldier*/* owner;
    Bullet(float x, float y, Texture &image, float _dx, float _dy, Soldier_without_walls/*Soldier*/* _owner) {
        owner = _owner;
        life = true;
        sprite.setTexture(image);  //сначала в sprite загружаю картину
        //sprite.setTextureRect(IntRect(0, 244, 40, 50)); // теперь я ограничиваю эту картинку заданными координатами
        rect = FloatRect(x,y,12,12);//текущие координаты, где я заспамлюсь
    //    sprite.setPosition(40, 40); /
        sprite.setTextureRect(IntRect(112, 144, 12, 12));
        dx = _dx; dy = _dy; age = 0;
    }

    bool update(float time) {
        if (age++ > 60) {life = false; return false;}
        rect.left += dx * time / 10; rect.top += dy * time / 10;
        if (rect.left < 0) {rect.left += (16 * W);} else if (rect.left >= (16 * W)) {rect.left -= (16 * W);}
        if (rect.top  < 0) {rect.top  += (16 * H);} else if (rect.top  >= (16 * H)) {rect.left -= (16 * H);}
        sprite.setPosition(rect.left, rect.top ); // координаты x, y
        return true; //он не нужен. Вывод не считывается.
    }

    void Collision(int dir) {
        for (int i = rect.top/16; i < (rect.top + rect.height)/16; i++) {
            for (int j = rect.left/16; j < (rect.left + rect.width)/16; j++) {
				 if (TileMap[i][j]=='1') {life = false;       }

            }
        }
    }
};

