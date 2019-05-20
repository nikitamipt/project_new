#pragma once
#include "Player.cpp"
#include "Neuron_Net.cpp"

grtgbbgrkjntkjbbg;bgjn s jtenv;jkn
lgrkm
int a  = 5390ioijlfg;
using namespace sf;


class KohonenNet;
class Soldier : public Player {
public:
    bool space;
    int lives; //each bot has 3 lives. Num of lives doesn't save them from the wall((
    int kills;// kill-score bot. Just for statics.
    int age;  // just for static;
    int age_without_killing; //just for static. Each 1000? updates without kills - minus live..
    Soldier* killer; //bot that killed this one
    KohonenNet Net;
    //next 2 characteristics you can delete, they are not needed
    int dist_to_finish;
    unsigned long long  int score;
    ofstream fout;

// ЭТО КОСТЫЛЬ. КАК НЕ ПОВТОРЯТЬ ТОТ ЖЕ ТЕКСТ, что и PERSON
    Soldier(Texture &image, int x_start, int y_start, int inputs, int mids, int outs) : Net(inputs, mids, outs){
        sprite.setTexture(image);  //сначала в sprite загружаю картину
        rect = FloatRect(x_start * 16, y_start * 16,16,16);//текущие координаты, где я заспамлюсь
        sprite.setPosition(rect.left, rect.top);
        sprite.setTextureRect(IntRect(5*16, 9*16, 16, 16));
        dx = 0; dy = 0; da = 0;
        currentFrame = 0;
        kills = 0; lives = 3; age = 0; age_without_killing = 0;
        space = false;
        dsp = 1; da = 0;
        life = true;
        last_shot = 0;
    }

    bool control() {
        age++; age_without_killing++;
        if (age_without_killing > 200) {lives--;}
        Net.inNeurons[10]->value = float(clock() - last_shot);
        float fight = Net.outNeurons[1]->kernelFunction();
        float da1 = float(Net.outNeurons[0]->kernelFunction())/100000000;
//sprintf("da1 = %f\n\n", da1);
        if (da1 < -3.1415/2){da1 = -3.1415/2;} if (da1 > 3.1415/2) {da1 = 3.1415/2;}
        da += da1; dx = dsp*cos(da); dy = dsp*sin(da);
        if (clock() - last_shot > 500000 && fight > 4000000) { //перезадрядка 1000милисек
            last_shot = clock();
            return true;
        }
        return false;
    }

};


