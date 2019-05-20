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

// áóäó ðàñ÷èòûâàòü èç ñîîáðàæåíèé, ÷òî íà îäíîãî áîòà âûõîäèò bot_squre êâ åä ïëîùàäè (íå õàðîìû, íî è íå îáùàãà â Äîëãîïå)
int bot_squre  = 10 * 10;
int kol_bot = (H * W) / bot_squre;

float dist[5] = {3.1415/2, 3.1415/4, 0, -3.1415/4, -3.1415/2};


//ATTENTION: NEXT FUNCTION IS THE MOST BIG DERMOKOD IN THIS DERMAKOD-PROGRAMM
// there are 3 types of distance:
// 0 - if the nearest is the WALL
// 1 - if                    BULLET
// 2 - if                    BOT
void GetDistace0(Soldier_without_walls/*Soldier*/* my_bot, Line *line, list<Bullet*>  bullets, list<Soldier_without_walls/*Soldier*/*>  Bots, Person* P) {
    int Bot_x = my_bot->rect.left; int Bot_y = my_bot->rect.top; float alpha = my_bot->da; (*line).owner = my_bot;
    std::list<Bullet*>::iterator bul1;
    std::list<Soldier_without_walls/*Soldier*/*>::iterator Bbot;
//printf("\nBOT_START\n");
    for (int i = 0; i < 5; i++) {
        int x = Bot_x; int y = Bot_y;
        int s = 0;//distance
        int k1 = 0;//type of distance.
//printf("   wall = %d type  = %d\n", s, k1);


        int yyy = 0; int s1 = 0;
        line->rect.top = Bot_y; line->rect.left = Bot_x; line->dx = cos(alpha + dist[i]); line->dy = sin(alpha + dist[i]);
        while (s1 < view_distance) {
            for (bul1 = bullets.begin(); bul1 != bullets.end(); bul1++){
                if ((*line).rect.intersects((*bul1)->rect) &&  (*bul1)->life) {yyy = 1; break;}
            }
            s1++;   line->update(0);
        }
        if (s1 < view_distance) {s = s1;}
//printf("   Bul = %d    type = %d\n",  s1, k1);

        s1 = 0; yyy = 0;
        line->rect.top = Bot_y; line->rect.left = Bot_x;
        while (s1 < s || s1 >= view_distance) {
            for (Bbot = Bots.begin(); Bbot != Bots.end(); Bbot++){
                if ((*line).rect.intersects((*Bbot)->rect) && (*Bbot)->life && ((*line).owner !=  (*Bbot))) {yyy = 1; break;}
            }
            if ((*line).rect.intersects((*P).rect) &&  (*P).life) {yyy = 1; break;}
            s1++; line->update(0);
        }
        if (((s != 0) && (s1 < s)) || (s1 < view_distance)) {s = s1;}
        if (s == 0) {s = 5 * view_distance;}
//printf("   Bot = %d    type = %d\n",  s1, k1);

        my_bot->Net.inNeurons[i]->value = float(s);
//printf("dist = %d, type = %d\n", s, k1);
    }
}


// THIS FUNCTION SHOULD BE DECLARES IN  "NEURON_NET.cpp" BUT it has problems there as two classes reference each other at the same time
void bGetKohonet(Soldier_without_walls/*Soldier*/* my_bot, Soldier_without_walls/*Soldier*/* Bot, int rnd) {
    int inputs = Bot->Net.inputs; int mids = Bot->Net.mids; int outs = Bot->Net.outs;

    int q = 0;
    for (int i = 0; i < mids; i++) {
        for (int j = 0; j < inputs; j++) {
            int w = rand()%3;//ñ âåðîÿòíîñòüþ 50% ïðîèñõîäèò çàìåíà ÷èñëà
            int rrr =  (Bot)->Net.secNeurons[i]->weights[j];
            if ((w==0) && (rnd > 0)) { rrr = rand()%chislo - chislo/2; }
            my_bot->Net.secNeurons[i]->weights[j] = rrr;
            q++;
        }
    }
    for (int j = 0; j < outs; j++) {
        for (int i = 0; i < mids; i++) {
            int w = rand()%3;
            int rrr = (Bot)->Net.outNeurons[j]->weights[i];
            if ((w == 0) && (rnd > 0)) {rrr = rand()%chislo - chislo/2;}
            my_bot->Net.outNeurons[j]->weights[i] = rrr;
            q++;
        }
    }
}



void Game_war() {
int yyy = 0;

//printf("A  1\n");



bool visual = true;
bool who = true; //\F0\E5\F9\E0\E5\F2, \E1\F3\E4\E5\F2 \EB\E8 \F2\F3\F2 \F0\F3\F7\ED\EE\E5 \F3\EF\F0\E0\E2\EB\E5\ED\E8\E5 \E8\EB\E8 \ED\E5\F2.
const int num_of_bots = 10;
int inputs =  11; int outs = 2; int mids = 6; // number of neurons in the net of the bots.


//printf("A  2\n");


    RenderWindow window(VideoMode(960, 960), "SFML works!");

    Texture t;
    t.loadFromFile("1.png");
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
    p.Player_maker(t, x_start, y_start);



//printf("A  5\n");




    for (int i = 0; i < kol_bot; i++) {
//âñÿêèå ìèíóñû ïîñòàâëåíû äëÿ òîãî, ÷òîáû èãðîê ðîæäàëñÿ íå â ñòåíêàõ êàðòû
        Bots_life.push_back(new Soldier_without_walls/*Soldier*/(t, rand()%(W - 2) + 1, rand()%(H - 2) + 1, inputs, mids, outs));
    }
    Bbot2 = Bots_life.begin();

//printf("A  6\n");



    //Driver Driver(0); // øòóêà, êîòîðàÿ óïðàâëÿåò èãðîêîì!  (äà-äà-äà, ñàìà!)

    bool space = false; //êîíòðîëèò, íàæàò ëè SPACE èëè íåò. Íàäî äëÿ ñòðåëüáû, ÷òîáû î÷åðåäè íå áûëî
    bool Right_key = false; //êîíòðîëèò, íàæàò ëè Right èëè íåò. Íàäî äëÿ íîâîé ãåíåðàöèè áîòîâ.
    Clock clock; // ÷òîáû ñêîðîñòü áûëà ïðèâÿçàíà êî âðåìåíè, à íå ê òàêòîâîé ÷àñòîòå ïðîöåññîðà

    bool next_generation = false; //êîãäà true - óáèâàþ âñåõ áîòîâ è ïåðåðîæäàþ ëó÷øèõ!


//each static_update updates we will update best-killer and long-liver
    int static_update = 500; int update_time = 0;
    int best_age = 0; int best_kills = 0;


    while (window.isOpen()){

//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nNEW\n");
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
                bullets.push_back(new Bullet(p.rect.left, p.rect.top, t, speed_bul*dx2/m, speed_bul*dy2/m, NULL));
            }
            p.update(time);
        }



//çäåñü ÿ óïðàâëÿåò áîò! NO_HUMAN!
        bool qqq = false;//ïðîâåðÿþ, åñòü ëè åùå æèâûå áîòû
        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
          //  GetDistace0(*Bbot, &line, bullets, Bots_life, &p);
            if (!(*Bbot)->life || (*Bbot)->lives <= 0) {
                (*Bbot)->rect.left = float((rand() % (W-2) + 1) * 16);
                (*Bbot)->rect.top  = float((rand() % (H-2) + 1) * 16);
                (*Bbot)->life = true; (*Bbot)->lives = 3; (*Bbot)->age = 0; (*Bbot)->kills = 0; (*Bbot)->age_without_killing = 0;
                bGetKohonet(*Bbot, *Bbot, 1);
            }
            if ((*Bbot)->control()) { bullets.push_back(new Bullet((*Bbot)->rect.left, (*Bbot)->rect.top, t, speed_bul*cos((*Bbot)->da), speed_bul*sin((*Bbot)->da), *Bbot));}
            (*Bbot)->life = ((*Bbot)->update(time)); //áîò óìèðàåò, êàê òîëüêî ñòîëêíóëñÿ ñî ñòåíîé
        }

        //÷òîáû çàïóñòèòü íîâûé ðîä (óáèòü âñåõ âðàùàþùèõñÿ íà ìåñòå)
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (Right_key == false) {
                Right_key = true;
                for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){ (*Bbot)->life = false; }
            }
        } else {
            Right_key = false;
        }




//îáíîâëÿþ òåêóùåå ïîëîæåíèå îáúåêòîâ êàðòû (òàêèõ êàê ïóëè, ëèíèè ïðèöåëà)
//obnovleniye pul
        for (bul = bullets.begin(); bul != bullets.end();){
			Bullet *b = *bul;//äëÿ óäîáñòâà, ÷òîáû íå ïèñàòü (*it)->
			b->update(time);//âûçûâàåì ô-öèþ update äëÿ âñåõ îáúåêòîâ (ïî ñóòè äëÿ òåõ, êòî æèâ)
			if (b->life == false)	{
                if ((*bul)->owner != NULL) {(*bul)->owner->lives--;}
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
                }
            }
		}

// stolknovenie PULA + BOT
        for (bul1 = bullets.begin(); bul1 != bullets.end(); bul1++){
            for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){
                if ((*bul1)->rect.intersects((*Bbot)->rect) && (*bul1)->life && (*Bbot)->life && ((*bul1)->owner != (*Bbot))) {
                    (*Bbot)->lives -= 1;
                    if ((*Bbot)->lives <= 0) {
                        (*Bbot)->lives = 3; (*Bbot)->life = true; (*Bbot)->age = 0; (*Bbot)->kills = 0; (*Bbot)->age_without_killing = 0;
                        if ((*bul1)->owner != NULL) {
                            bGetKohonet(*Bbot, (*bul1)->owner, 1);
                            (*bul1)->owner->lives += 2; (*bul1)->owner->age_without_killing = 0; (*bul1)->owner->kills += 1;
                        } else {bGetKohonet(*Bbot, *Bbot, 1);}
                        (*Bbot)->rect.left = float((rand() % (W-2) + 1) * 16);
                        (*Bbot)->rect.top  = float((rand() % (H-2) + 1) * 16);
                    } else if ((*bul1)->owner != NULL) { (*bul1)->owner->lives += 1; }
                (*bul1)->life = false;
                }
            }
		}

/*// srolknoveniye BOT + BOT
        for (Bbot1 = Bots_life.begin(); Bbot1 != Bots_life.end(); Bbot1++){
            for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){
                if ((*Bbot1)->rect.intersects((*Bbot)->rect) && (*Bbot1)->life && (*Bbot)->life && Bbot != Bbot1) {
                    (*Bbot)->life = false;
                    (*Bbot1)->life = false;
                }
            }
		}
*/
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
            if(who) {L.rect.left = p.rect.left; L.rect.top = p.rect.top + 4; int s = 0; L.dx = cos(p.da); L.dy = sin(p.da);
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



