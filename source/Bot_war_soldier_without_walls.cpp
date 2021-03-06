#pragma once
//#include "Player.cpp"
#include "Player_without_walls.cpp"
#include "Neuron_Net.cpp"


using namespace sf;


class KohonenNet;
class Soldier_without_walls : public Player {
public:
    bool space;
    int lives; //each bot has 3 lives. Num of lives doesn't save them from the wall((
    int kills;// kill-score bot. Just for statics.o
    int age;  // just for static;
    int age_without_killing; //just for static. Each 1000? updates without kills - minus live..
    Soldier_without_walls* killer; //bot that killed this one
    KohonenNet Net;
    //next 2 characteristics you can delete, they are not needed
    int dist_to_finish;
    unsigned long long  int score;
    ofstream fout;

// ÝÒÎ ÊÎÑÒÛËÜ. ÊÀÊ ÍÅ ÏÎÂÒÎÐßÒÜ ÒÎÒ ÆÅ ÒÅÊÑÒ, ÷òî è PERSON
    Soldier_without_walls(Texture &image, int x_start, int y_start, int inputs, int mids, int outs) : Net(inputs, mids, outs){
        sprite.setTexture(image);  //ñíà÷àëà â sprite çàãðóæàþ êàðòèíó
        rect = FloatRect(x_start * 16, y_start * 16,16,16);//òåêóùèå êîîðäèíàòû, ãäå ÿ çàñïàìëþñü
        sprite.setPosition(rect.left, rect.top);
        sprite.setTextureRect(IntRect(5*16, 9*16, 16, 16));
        dx = 0; dy = 0;
        currentFrame = 0;
        kills = 0; lives = 3; age = 0; age_without_killing = 0; last_shot = 0;
        space = false;
        dsp = 1;
        da =  0;
        life = true;
        last_shot = 0;
    }



    bool control() {
        age++; age_without_killing++; last_shot++;
        if (age_without_killing > 350) {lives--;}
        Net.inNeurons[6]->value = float(last_shot);
        float fight = Net.outNeurons[1]->kernelFunction();
//printf("fight = %f\n", fight);
        float da1 = float(Net.outNeurons[0]->kernelFunction())/5;//100000;
//printf("da1 = %f\n\n", da1);
        if (da1 < -3.141592/2){da1 = -3.141592/2;} if (da1 > 3.1415/2) {da1 = 3.141592/2;}
        da += da1;
        if (da < 0.) {da += 2 * 3.141592;} else if (da >= 2 * 3.141592) {da -= 2 * 3.141592;}
        dx = dsp*cos(da); dy = dsp*sin(da);
        if (last_shot > 50 && fight > 1/*000*/) { //ïåðåçàäðÿäêà 1000ìèëèñåê
            last_shot = 0;
            return true;
        }
        return false;
    }

};


