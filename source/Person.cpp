//#include "Player.cpp"
#include "Player_without_walls.cpp"

bool fast_game = false;//for Game_war


using namespace sf;


class Person : public Player {
public:
    Person(int i) {}

    bool control(Vector2f pos) {
        last_shot++;
        bool space1 = false;
        dsp = 0;
        if (Keyboard::isKeyPressed(Keyboard::Right) or (Keyboard::isKeyPressed(Keyboard::D))) { da += 0.03; }
        if (Keyboard::isKeyPressed(Keyboard::Left)  or (Keyboard::isKeyPressed(Keyboard::A))) { da -= 0.03; }
        if (Keyboard::isKeyPressed(Keyboard::Up)    or (Keyboard::isKeyPressed(Keyboard::W))) { dsp = 1;  }
        if (Keyboard::isKeyPressed(Keyboard::Down)  or (Keyboard::isKeyPressed(Keyboard::S))) { dsp = -1; }
        if (Keyboard::isKeyPressed(Keyboard::Space) and (last_shot > 10)) { //перезадрядка 1000милисек
            space1 = true;
            last_shot = 0;
        }
        else {space1 = false;}
        if (da < 0.) {da += 2 * 3.141592;} else if (da >= 2 * 3.141592) {da -= 2 * 3.141592;}

        if (fast_game) {
            int lll = clock();
            while (clock() - lll < 10000) {}
        }

        dx = dsp*cos(da); dy = dsp*sin(da);
        return space1;
    }


};


