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





float dist[5] = {3.1415/2, 3.1415/4, 0, -3.1415/4, -3.1415/2};


//ATTENTION: NEXT FUNCTION IS THE MOST BIG DERMOKOD IN THIS DERMAKOD-PROGRAMM
// there are 3 types of distance:
// 0 - if the nearest is the WALL
// 1 - if                    BULLET
// 2 - if                    BOT
void GetDistace0(Soldier* my_bot, Line *line, list<Bullet*>  bullets, list<Soldier*>  Bots, Person* P) {
    int Bot_x = my_bot->rect.left; int Bot_y = my_bot->rect.top; float alpha = my_bot->da; (*line).owner = my_bot;
    std::list<Bullet*>::iterator bul1;
    std::list<Soldier*>::iterator Bbot;
printf("\nBOT_START\n");
    for (int i = 0; i < 5; i++) {
printf("B 1\n");
        int x = Bot_x; int y = Bot_y;
        int s = 0;//distance
        int k1 = 0;//type of distance.
        while (TileMap[int(y/16)][int(x/16)] == '0') {
            x += 8 * cos(alpha + dist[i]); y += 8 * sin(alpha + dist[i]); s++;
        }
printf("   wall = %d type  = %d\n", s, k1);


        int yyy = 0; int s1 = 0;
        line->rect.top = Bot_y; line->rect.left = Bot_x;
        while (!yyy) {
            for (bul1 = bullets.begin(); bul1 != bullets.end(); bul1++){
                if ((*line).rect.intersects((*bul1)->rect) &&  (*bul1)->life) {yyy = 1; break;}
            }
            s1++; if (s1 >= s) {s1 = 0; break;}
            line->rect.left += 8 * cos(alpha + dist[i]); line->rect.top  += 8 * sin(alpha + dist[i]);
        }
printf("B 3\n");
        if (s1 != 0 && s1 < s) {s = s1; k1 = 1;}
printf("   Bul = %d    type = %d\n",  s1, k1);



        s1 = 0; yyy = 0;
        line->rect.top = Bot_y; line->rect.left = Bot_x;
printf("B 2\n");
        while (!yyy) {
            for (Bbot = Bots.begin(); Bbot != Bots.end(); Bbot++){
                if ((*line).rect.intersects((*Bbot)->rect) && (*Bbot)->life && ((*line).owner !=  (*Bbot))) {yyy = 1; break;}
            }
            if ((*line).rect.intersects((*P).rect) &&  (*P).life) {yyy = 1; break;}
            s1++; if (s1 >= s) {s1 = 0; break;}
            line->rect.left += 8 * cos(alpha + dist[i]); line->rect.top  += 8 * sin(alpha + dist[i]);
        }
        if (s1 != 0 && s1 < s) {s = s1; k1 = 2;}
printf("   Bot = %d    type = %d\n",  s1, k1);


        my_bot->Net.inNeurons[2*i]->value = float(s);
        my_bot->Net.inNeurons[2*i + 1]->value = float(k1);
printf("dist = %d, type = %d\n", s, k1);
    }
}


// THIS FUNCTION SHOULD BE DECLARES IN  "NEURON_NET.cpp" BUT it has problems there as two classes reference each other at the same time
void bGetKohonet(Soldier* my_bot, Soldier* Bot, int rnd) {
    int inputs = Bot->Net.inputs; int mids = Bot->Net.mids; int outs = Bot->Net.outs;

    int q = 0;
    for (int i = 0; i < mids; i++) {
        for (int j = 0; j <= inputs/2; j++) {
            int w = rand()%3;//ñ âåðîÿòíîñòüþ 50% ïðîèñõîäèò çàìåíà ÷èñëà
            int rrr =  (Bot)->Net.secNeurons[i]->weights[j];
            if ((w==0) && (rnd > 0)) { rrr = rand()%chislo - chislo/2; }
            my_bot->Net.secNeurons[i]->weights[j]                          = rrr;
            my_bot->Net.secNeurons[mids - i - 1]->weights[inputs - j - 1] = rrr;
            q++;
        }
    }
    for (int j = 0; j < outs; j++) {
        for (int i = 0; i < mids; i++) {
            int w = rand()%3;
            int rrr = (Bot)->Net.outNeurons[j]->weights[i];
            if ((w == 0) && (rnd > 0)) {rrr = rand()%chislo - chislo/2;}
            my_bot->Net.outNeurons[j]->weights[i]                       = rrr;
            my_bot->Net.outNeurons[outs - j - 1]->weights[mids - i - 1] = rrr;
            q++;
        }
    }
}




// áóäó ðàñ÷èòûâàòü èç ñîîáðàæåíèé, ÷òî íà îäíîãî áîòà âûõîäèò bot_squre êâ åä ïëîùàäè (íå õàðîìû, íî è íå îáùàãà â Äîëãîïå)
int bot_squre  = 10 * 6;
int kol_bot = (H * W) / bot_squre;

void Game_war() {
int yyy = 0;

printf("A  1\n");



bool visual = true;
bool who = true; //\F0\E5\F9\E0\E5\F2, \E1\F3\E4\E5\F2 \EB\E8 \F2\F3\F2 \F0\F3\F7\ED\EE\E5 \F3\EF\F0\E0\E2\EB\E5\ED\E8\E5 \E8\EB\E8 \ED\E5\F2.
const int num_of_bots = 10;
int inputs =  11; int outs = 2; int mids = 6; // number of neurons in the net of the bots.


printf("A  2\n");


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


    //÷èòàþ êàðòó
    ifstream f_map("Map_war.txt");
    for (int i = 0; i < H; i++) {
        std::string str;
        std::getline(f_map, str);
        TileMap[i] = str;
    }


printf("A  3\n");


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


printf("A  4\n");




    //ìàññèâ âñåõ îáúåêòîâ êàðòû (ïðèöåë). Âîçìîæíî, íå íóæåí, ïîêà õç
    std::list<Entity*>  entities;
    std::list<Bullet*>  bullets; //ìàññèâ ïóëü, êîòîðûå åñòü íà êàðòå
    std::list<Soldier*>  Bots_life;//çäåñü ÿ õðàíþ æèâûõ áîòîâ. Êàæäûé òàêò ÿ îáíîâëÿþ èõ òåêóùåå ïîëîæåíèå
    std::list<Soldier*> Bots_death;//çäåñü ÿ õðàíþ ìåðòâûõ. Òåõ, ÷òî ñòîëêíóëèñü ñî ñòåíîé. Êîãäà âñå áîòû óìèðàþò, ÿ âûáèðàþ èç ýòîãî ñïèñêà áîòîâ áîòà, êîòîðûé îêàçàëñÿ áëèæå âñåõ ê ôèíèøó.
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it1;
    std::list<Soldier*>::iterator Bbot;
    std::list<Soldier*>::iterator Bbot1;
    std::list<Bullet*>::iterator bul;
    std::list<Bullet*>::iterator bul1;
    Line line(t);

    Line L(t);  //íóæíî äëÿ ðèñîâàíèÿ ïðèöåëà è íàõîæäíèé ðàññòîÿíèé äî ñòåíîê
    Person p(1);
    p.Player_maker(t, x_start, y_start);



printf("A  5\n");




    for (int i = 0; i < 2/*kol_bot*/; i++) {
//âñÿêèå ìèíóñû ïîñòàâëåíû äëÿ òîãî, ÷òîáû èãðîê ðîæäàëñÿ íå â ñòåíêàõ êàðòû
        Bots_life.push_back(new Soldier(t, 5, 5 + i*10,/*rand()%(W - 2) + 1, rand()%(H - 2) + 1,*/ inputs, mids, outs));
    }

printf("A  6\n");


    Enemy Enemy(t); //õðåíü, â êîòîðóþ ÿ ñòðåëÿþ. òèïà ìèøåíü



    //Driver Driver(0); // øòóêà, êîòîðàÿ óïðàâëÿåò èãðîêîì!  (äà-äà-äà, ñàìà!)

    bool space = false; //êîíòðîëèò, íàæàò ëè SPACE èëè íåò. Íàäî äëÿ ñòðåëüáû, ÷òîáû î÷åðåäè íå áûëî
    bool Right_key = false; //êîíòðîëèò, íàæàò ëè Right èëè íåò. Íàäî äëÿ íîâîé ãåíåðàöèè áîòîâ.
    Clock clock; // ÷òîáû ñêîðîñòü áûëà ïðèâÿçàíà êî âðåìåíè, à íå ê òàêòîâîé ÷àñòîòå ïðîöåññîðà

    bool next_generation = false; //êîãäà true - óáèâàþ âñåõ áîòîâ è ïåðåðîæäàþ ëó÷øèõ!



printf("A  7\n");

int lll = 0;

    while (window.isOpen()){
printf("A\n");

printf("\n\n\nNEW\n");


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
//printf("AAA\n");
            if (p.control(pos)) {
//printf("AAA1\n");
                float dx2 = pos.x-p.rect.left; float dy2 = pos.y - p.rect.top;
                float m = sqrt(dx2*dx2 + dy2 * dy2);
                bullets.push_back(new Bullet(p.rect.left, p.rect.top, t, speed_bul*dx2/m, speed_bul*dy2/m, NULL));
            }
            p.update(time);
//printf("AAA2\n");
        }



//çäåñü ÿ óïðàâëÿåò áîò! NO_HUMAN!
        bool qqq = false;//ïðîâåðÿþ, åñòü ëè åùå æèâûå áîòû
        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
printf("C255\n");
//next function -  EYES for bot
//            GetDistace0(*Bbot, &line, bullets, Bots_life, &p);
printf("C258\n");
            if ((*Bbot)->control()) { bullets.push_back(new Bullet((*Bbot)->rect.left, (*Bbot)->rect.top, t, speed_bul*cos((*Bbot)->da), speed_bul*sin((*Bbot)->da), *Bbot));}
            if ((*Bbot)->life) {(*Bbot)->life = ((*Bbot)->update(time));} //áîò óìèðàåò, êàê òîëüêî ñòîëêíóëñÿ ñî ñòåíîé
printf("c264\n");
        }
        if (next_generation) {
            next_generation = false;
            for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++){
                (*Bbot)->rect.left = float((rand() % (W-2) + 1) * 16);
                (*Bbot)->rect.top  = float((rand() % (H-2) + 1) * 16);
//printf("x = %d, y = %d\n", int((*Bbot)->rect.left), int((*Bbot)->rect.top));
               // (*Bbot)->kills = 0;
                (*Bbot)->lives = 3;
                (*Bbot)->life = true;
            }
        }

printf("C320\n");

        //÷òîáû çàïóñòèòü íîâûé ðîä (óáèòü âñåõ âðàùàþùèõñÿ íà ìåñòå)
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (Right_key == false) {
                Right_key = true;
                for (Bbot = Bots_life.begin(); Bbot != Bots_life.end();Bbot++){
                    (*Bbot)->life = false;
                }
                next_generation = true;
            }
        } else {
            Right_key = false;
        }




        Enemy.update(0);


//îáíîâëÿþ òåêóùåå ïîëîæåíèå îáúåêòîâ êàðòû (òàêèõ êàê ïóëè, ëèíèè ïðèöåëà)
//obnovleniye pul
        for (bul = bullets.begin(); bul != bullets.end();){
			Bullet *b = *bul;//äëÿ óäîáñòâà, ÷òîáû íå ïèñàòü (*it)->
			b->update(time);//âûçûâàåì ô-öèþ update äëÿ âñåõ îáúåêòîâ (ïî ñóòè äëÿ òåõ, êòî æèâ)
			if (b->life == false)	{ bul = bullets.erase(bul); delete b; }// åñëè ýòîò îáúåêò ìåðòâ, òî óäàëÿåì åãî
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
                    (*Bbot)->lives--;
                    if ((*Bbot)->lives <= 0) {
                        (*Bbot)->lives = 3; (*Bbot)->life = true;
                        //(*Bbot)->killer = (*bul1)->owner;
                       // bGetKohonet(*Bbot, (*bul1)->owner, 1);
                        (*Bbot)->rect.left = float((rand() % (W-2) + 1) * 16);
                        (*Bbot)->rect.top  = float((rand() % (H-2) + 1) * 16);
                    }
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
printf("C398\n");

if (visual)  {

printf("C402\n");
        window.clear(Color::White);

        for (int i=0; i<H; i++) {
			 for (int j=0; j<W; j++)
			  {
				if (TileMap[i][j]=='1')  tile.setTextureRect( IntRect(143-ZZ*3,112,ZZ,ZZ) );
                if (TileMap[i][j]=='2')  tile.setTextureRect( IntRect(143-ZZ*2,112 + 16,ZZ,ZZ) );
                if (TileMap[i][j]=='3')  tile.setTextureRect( IntRect(143-ZZ*3,112 + 16,ZZ,ZZ) );
                if (TileMap[i][j]=='4')  tile.setTextureRect( IntRect(143-ZZ*2,112,ZZ,ZZ) );
				if (TileMap[i][j]=='0') continue;

  			    tile.setPosition(j*ZZ,i*ZZ) ;
		        window.draw(tile);
		     }
        }

printf("C420\n");

        //ðèñóþ ïðèöåë
        if(who) {L.rect.left = p.rect.left; L.rect.top = p.rect.top + 4;
printf("C423\n");
        while (1) {
            int xx = int(L.rect.top/16); int yy = int(L.rect.left/16);
            if ((yy < 0 || yy >= H || xx < 0 || xx >= W) || (TileMap[xx][yy] != '0')) { break;}
            L.rect.left += 8 * cos(p.da); L.rect.top += 8 * sin(p.da); L.update(0);
            window.draw(L.sprite);
        }
        }


printf("C429\n");


        window.draw(Enemy.sprite);
        if (who) {window.draw(p.sprite);}



        for (it = entities.begin(); it != entities.end(); it++){ window.draw((*it)->sprite);}
printf("C438\n");

        int kk = 0;
        for (bul = bullets.begin(); bul != bullets.end(); bul++){window.draw((*bul)->sprite);}

printf("C443\n");

        for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); Bbot++) {
            window.draw((*Bbot)->sprite);
        }

printf("C449\n");

        window.display();

printf("C453\n");


}

    }

printf("A   %d\n", yyy++);



    /*Bot.Net.GetKohonet(f_net_in);
    Bot.Net.SaveKohonet(f_net_out);*/
    f_net_out.close();

    for (Bbot = Bots_life.begin(); Bbot != Bots_life.end(); ){
        Soldier *b = *Bbot;//äëÿ óäîáñòâà, ÷òîáû íå ïèñàòü (*it)->
        Bbot = Bots_life.erase(Bbot); delete b; // åñëè ýòîò îáúåêò ìåðòâ, òî óäàëÿåì åãî
    }

printf("A   %d\n", yyy++);



}



