#pragma once
#include "Player.cpp"
#include "Neuron_Net.cpp"


using namespace sf;


//float dist[5] = {3.1415/2, 3.1415/4, 0, -3.1415/4, -3.1415/2};


int GetDistace1(int x, int y, float qqq, float da) {
    int s = 0;
    while (TileMap[int(y/16)][int(x/16)] == '0') {
        x += 8 * cos(da + qqq); y += 8 * sin(da + qqq); s++;
    }
   // //printf("s = %d\n\n", s);
    return s;
}


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
        kills = 0; lives = 1; age = 0; age_without_killing = 0;
        space = false;
        dsp = 1; da = 0;
        life = true;
        last_shot = 0;
    }

    bool control() {
//printf("Bot 51 \n");
        age++; age_without_killing++;
        if (age_without_killing > 200) {lives--;}
        Net.inNeurons[10]->value = float(clock() - last_shot);
//printf("Bot 53\n");
        float fight = Net.outNeurons[1]->kernelFunction();
//printf("fight = %f\n ", fight);
//printf("Bot 56\n");
        float da1 = float(Net.outNeurons[0]->kernelFunction())/100000000;
//sprintf("da1 = %f\n\n", da1);
//printf("Bot 59\n");
        if (da1 < -3.1415/2){da1 = -3.1415/2;} if (da1 > 3.1415/2) {da1 = 3.1415/2;}
        da += da1; dx = dsp*cos(da); dy = dsp*sin(da);
        if (clock() - last_shot > 2000000 && fight > 4000000) { //перезадрядка 1000милисек
            last_shot = clock();
            return true;
        }
        return false;
    }

};


