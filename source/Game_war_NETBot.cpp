/*
git add .
git commit -m "draw+map_war"
git push origin master
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <time.h>

#include <iostream>

#include "Neuron_Net.cpp"
/*
#include "Player.сpp"
#include "Entity.сpp"
#include "Bullet.сpp"
#include "Enemy.сpp"
#include "Lines.cpp"
#include "Dijkstra.cpp"
#include "Person.cpp"
#include "Bot.cpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <string>
*/


//#include <SFML/Audio.hpp>

using namespace sf;




int view_distance = 50; //distance that bot can see


float dist[5] = {3.1415/2, 3.1415/4, 0, -3.1415/4, -3.1415/2};


//ATTENTION: NEXT FUNCTION IS THE MOST BIG DERMOKOD IN THIS DERMAKOD-PROGRAMM
// there are 3 types of distance:
// 0 - if the nearest is the WALL
// 1 - if                    BULLET
// 2 - if                    BOT


void GetDistace0(Soldier_without_walls/*Soldier*/* my_bot, Line *line, list<Bullet*>  bullets, list<Soldier_without_walls/*Soldier*/*>  Bots, Person* P) {
    int Bot_x = my_bot->rect.left; int Bot_y = my_bot->rect.top; float alpha = my_bot->da; (*line).owner = my_bot;
    std::list<Bullet*>::iterator bul1;
    std::list<Soldier_without_walls*/*Soldier*/>::iterator Bbot;
//printf("\nBOT_START\n");
    for (int i = 0; i < 5; i++) {
        int x = Bot_x; int y = Bot_y;
        int s = 0;//distance

        int s1 = 0; int yyy = 1;
        line->rect.top = Bot_y; line->rect.left = Bot_x; line->dx = 8*cos(alpha + dist[i]); line->dy = 8*sin(alpha + dist[i]);
        while (s1 < view_distance && yyy) {
            for (bul1 = bullets.begin(); bul1 != bullets.end(); bul1++){
                if ((*bul1)->rect.intersects((*line).rect) &&  (*bul1)->life) {yyy = 0; break;}
            }
            s1++;   line->update(0);
        }
        if (s1 >= view_distance) {s1 = 5 * view_distance;}
//printf("   Bul = %d\n",  s1);

        int s2 = 0; yyy = 1;
        line->rect.top = Bot_y; line->rect.left = Bot_x;
        while (s2 < view_distance && s2 < s1 && yyy) {
            for (Bbot = Bots.begin(); Bbot != Bots.end(); Bbot++){
                if ((*line).rect.intersects((*Bbot)->rect) && (*Bbot)->life && ((*line).owner !=  (*Bbot))) {yyy = 0; break;}
            }
            if ((*P).rect.intersects((*line).rect) && (*P).life) {yyy = 0;}
            s2++;   line->update(0);
        }
        if (s2 >= view_distance) {s2 = 5 * view_distance;}
//printf("   Bot = %d\n",  s2);

        s1 < s2 ? s = s1 : s = s2;
        my_bot->Net.inNeurons[i]->value = float(s);
//printf("dist = %d\n", s);
    }
}


float distance_to_the_bot(float Bbot_x, float Bbot_y, float Bot_x, float Bot_y, float alpha, float *a) {
    float delta_alpha = 3.1415926535/3; // viewing angle
    float gip1 = -1; *a = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            float xxx = Bbot_x + W*16*i - Bot_x; float yyy = -(Bbot_y + H*16*j - Bot_y);
            float gip = sqrt(xxx*xxx + yyy*yyy);
            float angle = asin(yyy/gip);
            if (xxx > 0 && yyy < 0) { angle = 2 * 3.1415926535 + angle; }
            else if (xxx < 0)       { angle =     3.1415926535 - angle; }

            int qqq = 0;
/* if (i == 0 && j == 0) {
    printf("\n\nxxx = %f, yyy = %f, angle = %f\n", xxx, yyy, angle);
    //    printf("x0 = %f, y0 = %f, x = %f, y = %f\n", Bot_x, Bot_y, Bbot_x, Bbot_y);
    printf("a = %f, a + delta = %f, a - delta = %f\n\n\n", alpha, alpha + delta_alpha, alpha - delta_alpha);
} */
            if ((alpha + delta_alpha >= angle) && (alpha - delta_alpha <= angle)) {
                if (( gip1 == -1 ) || ( gip < gip1 )) {
                    (*a) = alpha - angle;
                    gip1 = gip;
                }
            } else if ((alpha + delta_alpha >= angle - 2 * 3.1415926535) && (alpha - delta_alpha <= angle - 2 * 3.1415926535)) {
                 if (( gip1 == -1 ) || ( gip < gip1 )) {
                    (*a) = alpha - angle + 2 * 3.1415926535;
                    gip1 = gip;
                }
            }
  //          printf("gip = %f delta_angle = %f\n", gip1, *a);

        }
    }
//printf("gip = %f delta_angle = %f\n", gip1, *a);
    return gip1;

}



void GetDistace_full_view(Soldier_without_walls/*Soldier*/* my_bot, list<Bullet*>  bullets, list<Soldier_without_walls/*Soldier*/*>  Bots, Person* P) {
    int Bot_x = my_bot->rect.left; int Bot_y = my_bot->rect.top; float alpha = my_bot->da;
    std::list<Bullet*>::iterator bul1;
    std::list<Soldier_without_walls*/*Soldier*/>::iterator Bbot;
//printf("\nBOT_START\n");

    int num_seen_bots = 3;  //number of bots that we will record and use in net
// int current_kol = 0;    //numver of bots that we has already seen
    vector <pair<float, float>> mas (num_seen_bots); //mas of the nearest num_seen_bots bots

    for (int i = 0; i < num_seen_bots; i++) {
        mas[i].first    = 5 * view_distance;
        mas[i].second   = 0;
    }

    for (Bbot = Bots.begin(); Bbot != Bots.end(); Bbot++){
        if (Bot_x != (*Bbot)->rect.left || Bot_y != (*Bbot)->rect.top) {
            float a = 0;
            float s = distance_to_the_bot((*Bbot)->rect.left, (*Bbot)->rect.top, Bot_x, Bot_y, alpha, &a);
            for (int i = 0; i < num_seen_bots; i++) {
                if (mas[i].first > s) {
                    float s1 = mas[i].first;    mas[i].first  = s;  s = s1;
                    float a1 = mas[i].second;   mas[i].second = a;  a = a1;
                }
            }
//printf("bot = %f\n\n\n", s);
        }
    }

    for (bul1 = bullets.begin(); bul1 != bullets.end(); bul1++){
        if ((*bul1)->owner != my_bot) {
            float a = 0;
            float s = distance_to_the_bot((*bul1)->rect.left, (*bul1)->rect.top, Bot_x, Bot_y, alpha, &a);
    //printf("bul: s = %d\f, a = %f\n", s, a);
            for (int i = 0; i < num_seen_bots; i++) {
                if (mas[i].first > s) {
                    float s1 = mas[i].first;    mas[i].first = s;   s = s1;
                    float a1 = mas[i].second;   mas[i].second = a;  a = a1;
                }
            }
        }
    }

    float a = 0;
    float s = distance_to_the_bot((*P).rect.left, (*P).rect.top, Bot_x, Bot_y, alpha, &a);
//printf("p:   s = %f, a = %f\n", s, a);

    for (int i = 0; i < num_seen_bots; i++) {
        if (mas[i].first > s) {
            float s1 = mas[i].first;    mas[i].first = s;   s = s1;
            float a1 = mas[i].second;   mas[i].second = a;  a = a1;
        }
    }

//printf("\nNET:\n");
    for (int i = 0; i < num_seen_bots; i++) {
        my_bot->Net.inNeurons[2 * i    ]->value = mas[i].first;
        my_bot->Net.inNeurons[2 * i + 1]->value = mas[i].second;
//printf("mas[i].first = %f, mas[i].second = %f\n", mas[i].first, mas[i].second);
    }
//printf("\n");

}



// THIS FUNCTION SHOULD BE DECLARES IN  "NEURON_NET.cpp" BUT it has problems there as two classes reference each other at the same time
void bGetKohonet(Soldier_without_walls/*Soldier*/* my_bot, Soldier_without_walls/*Soldier*/* Bot, int rnd) {
    int inputs = Bot->Net.inputs; int mids = Bot->Net.mids; int outs = Bot->Net.outs;
    if (Bot == NULL) {Bot = my_bot;}
    int q = 0;
    for (int i = 0; i < mids; i++) {
        for (int j = 0; j < inputs; j++) {
            int w = rand()%5;//ñ âåðîÿòíîñòüþ 50% ïðîèñõîäèò çàìåíà ÷èñëà
            int rrr =  (Bot)->Net.secNeurons[i]->weights[j];
            if ((w==0) && (rnd > 0)) { rrr = rand()%chislo - chislo/2; }
            my_bot->Net.secNeurons[i]->weights[j] = rrr;
            q++;
        }
    }
    for (int j = 0; j < outs; j++) {
        for (int i = 0; i < mids; i++) {
            int w = rand()%5;
            int rrr = (Bot)->Net.outNeurons[j]->weights[i];
            if ((w == 0) && (rnd > 0)) {rrr = rand()%chislo - chislo/2;}
            my_bot->Net.outNeurons[j]->weights[i] = rrr;
            q++;
        }
    }
}

void random_rect(Player* pl) {
    (*pl).rect.left = float((rand() % (W-2) + 1) * 16);
    (*pl).rect.top  = float((rand() % (H-2) + 1) * 16);
}



void Game_war() {
int yyy = 0;
fast_game = false;
bool visual = true;
bool who = true; //\F0\E5\F9\E0\E5\F2, \E1\F3\E4\E5\F2 \EB\E8 \F2\F3\F2 \F0\F3\F7\ED\EE\E5 \F3\EF\F0\E0\E2\EB\E5\ED\E8\E5 \E8\EB\E8 \ED\E5\F2.
int inputs =  7; int outs = 2; int mids = 5; // number of neurons in the net of the bots.
// áóäó ðàñ÷èòûâàòü èç ñîîáðàæåíèé, ÷òî íà îäíîãî áîòà âûõîäèò bot_squre êâ åä ïëîùàäè (íå õàðîìû, íî è íå îáùàãà â Äîëãîïå)
int bot_squre  = 10 * 20;
int kol_bot = (H * W) / bot_squre;


bool use_old_expirience = true; // if use last net

int lives_for_kill      =  3;
int lives_for_collision = -1;
int lives_for_lost_bul  = -3;
int lives_first         =  3;
int lives_hurt_bul      = -1;
int lives_for_bul       =  1;



    RenderWindow window(VideoMode(960, 960), "SFML works!");

    Texture t;
    t.loadFromFile("2.png");
    Sprite tile(t);

     // êóäà ÿ ñîõðàíÿþ íàøó ñåòêó. îòêóäà
    ofstream f_net_out;
    f_net_out.open("f_net_out.txt");
    ifstream f_net_in;
    f_net_in.open("f_net_in.txt");
    int mas_weights[inputs * mids + mids * outs + 10];


    sf::Font font;
    if (!font.loadFromFile("times-new-roman.ttf")){ printf("NO FONT\n");}
    sf::Text text;
    // select the font
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString("3.q");
    // set the character size
    text.setCharacterSize(20); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::Black);

    sf::Text text1; text1.setFont(font); text1.setCharacterSize(20); text1.setFillColor(sf::Color::Black);text1.setPosition(800, 870);
    sf::Text text2; text2.setFont(font); text2.setCharacterSize(20); text2.setFillColor(sf::Color::Black);
    sf::Text text3; text3.setFont(font); text3.setCharacterSize(20); text3.setFillColor(sf::Color::Black);text3.setPosition(800, 895);
    text.setString("Max_kills");  text.setPosition(700, 870 );//задаем позицию текста, центр камеры
    text2.setString("Max_age");   text2.setPosition(700, 895 );

    //÷èòàþ êàðòó
    ifstream f_map("Map_war_withot_walls.txt");
    for (int i = 0; i < H; i++) {
        std::string str;
        std::getline(f_map, str);
        TileMap[i] = str;
    }


//printf("A  3\n");


    //îïðåäåëÿþ, ãäå âîçðàäèòñÿ íàø ãåðîé
    int x_start = 0; int y_start = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (TileMap[i][j] == '3') {
                x_start = j; y_start = i;
                break;
            }
        }
    }


//printf("A  4\n");




    //ìàññèâ âñåõ îáúåêòîâ êàðòû (ïðèöåë). Âîçìîæíî, íå íóæåí, ïîêà õç
//    std::list<Entity*>  entities;
    std::list<Bullet*>  bullets; //ìàññèâ ïóëü, êîòîðûå åñòü íà êàðòå
    std::list<Soldier_without_walls/*Soldier*/*>  Bots_life;//çäåñü ÿ õðàíþ æèâûõ áîòîâ. Êàæäûé òàêò ÿ îáíîâëÿþ èõ òåêóùåå ïîëîæåíèå
//    std::list<Soldier*> Bots_death;//çäåñü ÿ õðàíþ ìåðòâûõ. Òåõ, ÷òî ñòîëêíóëèñü ñî ñòåíîé. Êîãäà âñå áîòû óìèðàþò, ÿ âûáèðàþ èç ýòîãî ñïèñêà áîòîâ áîòà, êîòîðûé îêàçàëñÿ áëèæå âñåõ ê ôèíèøó.
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it1;
    std::list<Soldier_without_walls/*Soldier*/*>::iterator Bbot;
    std::list<Soldier_without_walls/*Soldier*/*>::iterator Bbot1;
    std::list<Soldier_without_walls/*Soldier*/*>::iterator Bbot2;
    std::list<Bullet*>::iterator bul;
    std::list<Bullet*>::iterator bul1;
    Line line(t);

    Line L(t);  //íóæíî äëÿ ðèñîâàíèÿ ïðèöåëà è íàõîæäíèé ðàññòîÿíèé äî ñòåíîê
    Person p(1);
    p.Player_maker(t, 2, 2);



//printf("A  5\n");




    for (int i = 0; i < kol_bot; i++) {
        Bots_life.push_back(new Soldier_without_walls/*Soldier*/(t, rand()%(W - 2) + 1, rand()%(H - 2) + 1, inputs, mids, outs));
        //Bots_life.push_back(new Soldier_without_walls/*Soldier*/(t, 10, 10 + 10 * i, inputs, mids, outs));
    }
    for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){ (*Bbot)->killer = (*Bbot);}
    if (use_old_expirience) {
        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){
            (*Bbot)->Net.fGetKohonet(f_net_in);
          //  (*Bbot)->Net.rSaveKohonet();
        }
    }

    Bbot2 = Bots_life.begin();


    bool space = false; //êîíòðîëèò, íàæàò ëè SPACE èëè íåò. Íàäî äëÿ ñòðåëüáû, ÷òîáû î÷åðåäè íå áûëî
    bool Right_key = false; //êîíòðîëèò, íàæàò ëè Right èëè íåò. Íàäî äëÿ íîâîé ãåíåðàöèè áîòîâ.
    bool Left_key  = false;
    Clock clock; // ÷òîáû ñêîðîñòü áûëà ïðèâÿçàíà êî âðåìåíè, à íå ê òàêòîâîé ÷àñòîòå ïðîöåññîðà

    bool next_generation = false; //êîãäà true - óáèâàþ âñåõ áîòîâ è ïåðåðîæäàþ ëó÷øèõ!



//each static_update updates we will update best-killer and long-liver
    int static_update = 500; int update_time = 0;
    int best_age = 0; int best_kills = 0;


    while (window.isOpen()){


//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNEW\n");
        float time = clock.getElapsedTime().asMicroseconds();
        time = time / 500; //äàòü ïðîøåäøåå âðåìÿ.
        if (time > 20) time = 20;
        time = 20;
        clock.restart(); //ïåðåçàãðóæàåò âðåìÿ. Òàê ìû èçìåðèì ñêîðîñòü òàêòà.

        Vector2i pixelPos = Mouse::getPosition(window);//çàáèðàåì êîîðä êóðñîðà
		Vector2f pos = window.mapPixelToCoords(pixelPos);//ïåðåâîäèì èõ â èãðîâûå (óõîäèì îò êîîðä îêíà)
		//std::cout << pixelPos.x << "\n";//ñìîòðèì íà êîîðäèíàòó Õ ïîçèöèè êóðñîðà â êîíñîëè (îíà íå áóäåò áîëüøå øèðèíû îêíà)
		//std::cout << pos.x << "\n";//ñìîòðèì íà Õ,êîòîðàÿ ïðåîáðàçîâàëàñü â ìèðîâûå êîîðäèíàòû



        bool window_close = false; //for closing window...
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close(); window_close = true;
        }



        if (who) {
    //çäåñü ïðîèñõîäèò ñ÷èòûâàèíèå êëàâèàòóðû. p.control == true, åñëè ïðîèçîøåë âûñòðåë.
            if (p.control(pos)) {
                float dx2 = pos.x-p.rect.left; float dy2 = pos.y - p.rect.top;
                float m = sqrt(dx2*dx2 + dy2 * dy2);
                bullets.push_back(new Bullet(p.rect.left, p.rect.top, t, speed_bul*dx2/m, speed_bul*dy2/m, nullptr));
            }
            p.update(time);
        }



//çäåñü ÿ óïðàâëÿåò áîò! NO_HUMAN!
        bool qqq = false;//ïðîâåðÿþ, åñòü ëè åùå æèâûå áîòû
        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
            if (!(*Bbot)->life || (*Bbot)->lives <= 0) {
                random_rect(*Bbot);
                (*Bbot)->life = true; (*Bbot)->lives = lives_first; (*Bbot)->age = 0; (*Bbot)->kills = 0; (*Bbot)->age_without_killing = 0;
                bGetKohonet(*Bbot, (*Bbot)->killer, 1); (*Bbot)->killer = (*Bbot);
            }

            GetDistace_full_view(*Bbot, bullets, Bots_life, &p);

            if ((*Bbot)->control()) { bullets.push_back(new Bullet((*Bbot)->rect.left, (*Bbot)->rect.top, t, speed_bul*cos((*Bbot)->da), speed_bul*sin((*Bbot)->da), *Bbot));}
            (*Bbot)->update(time); //áîò óìèðàåò, êàê òîëüêî ñòîëêíóëñÿ ñî ñòåíîé

        }

        //÷òîáû çàïóñòèòü íîâûé ðîä (óáèòü âñåõ âðàùàþùèõñÿ íà ìåñòå)
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (Right_key == false) {
                Right_key = true;
                for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){ (*Bbot)->life = false; }
            }
        } else { Right_key = false; }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (!Left_key) { fast_game ? fast_game = false : fast_game = true;  Left_key = true;}
        } else Left_key = false;




//îáíîâëÿþ òåêóùåå ïîëîæåíèå îáúåêòîâ êàðòû (òàêèõ êàê ïóëè, ëèíèè ïðèöåëà)
//obnovleniye pul
        for (bul = bullets.begin(); bul != bullets.end();){
			Bullet *b = *bul;//äëÿ óäîáñòâà, ÷òîáû íå ïèñàòü (*it)->
			b->update(time);//âûçûâàåì ô-öèþ update äëÿ âñåõ îáúåêòîâ (ïî ñóòè äëÿ òåõ, êòî æèâ)
			if (b->life == false)	{
                if ((*bul)->owner != NULL) {(*bul)->owner->lives += lives_for_lost_bul;}
                bul = bullets.erase(bul); delete b;
            }
            else bul++;//è èäåì êóðñîðîì (èòåðàòîðîì) ê ñëåä îáúåêòó. òàê äåëàåì ñî âñåìè îáúåêòàìè ñïèñêà
		}


//çäåñü ïðîèñçîäò îáðàáîòêà ïóëü. Ïóëÿ â ïóëþ - äâó ïóëè ïîãèáàþò. Ïóëÿ â áîòà - îáà ïîìèðàþò, ê õîçÿèíó ïóëè äîáàâëÿåòñÿ îäíî î÷êî
//stolknovenie PULA + PULA
        for (bul = bullets.begin(); bul != bullets.end(); bul++){
            for (bul1 = bullets.begin(); bul1 != bullets.end(); bul1++){
                if (bul1 != bul && (*bul)->rect.intersects((*bul1)->rect) && (*bul)->life && (*bul1)->life) {
                    (*bul)->life = false; (*bul1)->life = false;
                    if ((*bul)->owner  != NULL) {(*bul)->owner->lives  += lives_for_bul;}
                    if ((*bul1)->owner != NULL) {(*bul1)->owner->lives += lives_for_bul;}
                }
            }
		}

// stolknovenie PULA + BOT
        for (bul1 = bullets.begin(); bul1 != bullets.end(); bul1++){
            for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){
                if ((*bul1)->rect.intersects((*Bbot)->rect) && (*bul1)->life && (*Bbot)->life && ((*bul1)->owner != (*Bbot))) {
                    (*Bbot)->lives -= lives_for_lost_bul;
                    if ((*Bbot)->lives <= 0) {
                        (*Bbot)->life = false;
                        if ((*bul1)->owner != NULL) {(*Bbot)->killer = (*bul1)->owner;}
                    }
                    if ((*bul1)->owner != NULL) {
                        (*bul1)->owner->lives += lives_for_kill;
                        (*bul1)->owner->age_without_killing = 0;
                        (*bul1)->owner->kills += 1;
                    }
                    (*bul1)->life = false;
                }
            }
		}

// srolknoveniye BOT + BOT
        for (Bbot1 = Bots_life.begin(); Bbot1 != Bots_life.end(); Bbot1++){
            for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){
                if ((*Bbot1)->rect.intersects((*Bbot)->rect) && (*Bbot1)->life && (*Bbot)->life && Bbot != Bbot1) {
                    (*Bbot)->lives += lives_for_collision;  (*Bbot1)->lives += lives_for_collision;
                }
            }
		}

//printf("C398\n");

        update_time++;
        if (update_time > static_update) {
            (*Bbot2)->sprite.setTextureRect(IntRect(5*16, 9*16, 16, 16));
            best_age = 0; best_kills = 0; update_time = 0;
            for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){
                if ((*Bbot)->age >  best_age) { best_age = (*Bbot)->age; Bbot2 = Bbot; }
                if ((*Bbot)->kills > best_kills) {best_kills = (*Bbot)->kills;}
            }
            text1.setString(std::to_string(best_kills));
            text3.setString(std::to_string(best_age));
            (*Bbot2)->sprite.setTextureRect(IntRect(7*16, 9*16, 16, 16));
            (*Bbot2)->Net.fSaveKohonet(f_net_out);

        }


        if (visual)  {
            window.clear(Color::White);
            for (int i=0; i<H; i++) {
                 for (int j=0; j<W; j++) {
                    if (TileMap[i][j]=='1')  tile.setTextureRect( IntRect(143-ZZ*3,112,ZZ,ZZ) );
                    if (TileMap[i][j]=='2')  tile.setTextureRect( IntRect(143-ZZ*2,112 + 16,ZZ,ZZ) );
                    if (TileMap[i][j]=='3')  tile.setTextureRect( IntRect(143-ZZ*3,112 + 16,ZZ,ZZ) );
                    if (TileMap[i][j]=='4')  tile.setTextureRect( IntRect(143-ZZ*2,112,ZZ,ZZ) );
                    if (TileMap[i][j]=='0') continue;
                    tile.setPosition(j*ZZ,i*ZZ) ;
                    window.draw(tile);
                 }
            }

    //printf("C420\n");

            //ðèñóþ ïðèöåë


            if(who) {L.rect.left = p.rect.left; L.rect.top = p.rect.top + 4; int s = 0; L.dx = 8*cos(p.da); L.dy = 8*sin(p.da);
                while (s < view_distance) {
                    L.update(0); s++; window.draw(L.sprite);
                }
            }


            if (who) {window.draw(p.sprite);}
            for (bul = bullets.begin(); bul != bullets.end(); bul++){window.draw((*bul)->sprite);}
            for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++) { window.draw((*Bbot)->sprite); }

    //printf("C449\n");

            window.draw(text); window.draw(text2); window.draw(text1); window.draw(text3);
            window.display();

    //printf("C453\n");


        }

    }

//printf("A   %d\n", yyy++);



    /*Bot.Net.GetKohonet(f_net_in);
    Bot.Net.SaveKohonet(f_net_out);*/
    f_net_out.close();

    for (bul = bullets.begin(); bul != bullets.end(); ){
        Bullet *b = *bul;
        bul = bullets.erase(bul); delete b;
    }

    for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); ){
        Soldier_without_walls/*Soldier*/ *b = *Bbot;//äëÿ óäîáñòâà, ÷òîáû íå ïèñàòü (*it)->
        Bbot = Bots_life.erase(Bbot); delete b; // åñëè ýòîò îáúåêò ìåðòâ, òî óäàëÿåì åãî
    }

//printf("A   %d\n", yyy++);



}



