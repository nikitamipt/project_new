#pragma once


#include <vector>
#include <iomanip>
#include <fstream>
using std::stringstream;
#include <iostream>

#include "Neuron.cpp"
#include "Bot_war_soldier_without_walls.cpp"

//#include "Bot_war_soldier.cpp"


/*
const int inputs = 5; //5 входов
const int mids = 3;   //3 средних
const int outs = 1;    //1 выход
*/
int chislo = 10; //максимальный коэффициент весов

using namespace std;



class Player;
class Soldier;
class KohonenNet{
public:

    std::vector<InputNeuron*> inNeurons;
    std::vector<Neuron*> outNeurons;
    std::vector<Neuron*> secNeurons;
    int ID; //for debug, no function
    int inputs;
    int mids;
    int outs;

    KohonenNet(int _inputs, int _mids, int _outs) {
        inputs = _inputs; mids = _mids; outs = _outs;
        for (int i = 0; i < inputs; i++) { inNeurons.push_back(new InputNeuron());}
        for (int i = 0; i < mids; i++)   { secNeurons.push_back(new Neuron());}
        for (int i = 0; i < outs; i++)   { outNeurons.push_back(new Neuron()); }
        for (int i = 0; i < mids; i++) {
            for (int j = 0; j < inputs; j++) {
                secNeurons[i]->dendrits.push_back(inNeurons[j]);
                secNeurons[i]->weights.push_back( rand()%chislo - chislo/2);
            }
        }
        for (int j = 0; j < outs; j++) {
            for (int i = 0; i < mids; i++) {
                outNeurons[j]->dendrits.push_back(secNeurons[i]);
                outNeurons[j]->weights.push_back(rand()%chislo - chislo/2);
            }
        }
    }

    ~KohonenNet() {
//printf("deleteNET\n");
        for (int i = 0; i < inputs; i++)    { delete(inNeurons[i]);  }
        for (int i = 0; i < mids; i++)      { delete(secNeurons[i]); }
        for (int i = 0; i < outs; i++)      { delete(outNeurons[i]); }
    }
   /* void Delete_KohonenNet() {
        for (int i = 0; i < inputs; i++) {
            delete(inNeurons[i]);
        }
        for (int i = 0; i < mids; i++) {
            delete(secNeurons[i]);
        }
        for (int i = 0; i < outs; i++) {
            delete(outNeurons[i]);
        }
    }*/

//сохраняет сетку в файл
    void fSaveKohonet(ofstream &fout) {
        for (int i = 0; i < mids; i++) {
            for (int j = 0; j < inputs; j++) {
              //  fout << std::fixed <<  std :: setprecision ( 5 )<< secNeurons[i]->weights[j] << " ";
                fout << secNeurons[i]->weights[j] << " ";
            }
        }
        for (int j = 0; j < outs; j++) {
            for (int i = 0; i < mids; i++) {
                //fout << std::fixed << std :: setprecision ( 5 )<<  outNeurons[j]->weights[j] << " ";
                fout << outNeurons[j]->weights[i] << " ";
            }
        }
        fout << '\n';
    }
    void rSaveKohonet() {
        for (int i = 0; i < mids; i++) {
            for (int j = 0; j < inputs; j++) {
               // cout << std::fixed <<  std :: setprecision ( 5 )<< secNeurons[i]->weights[j] << " ";
                cout << secNeurons[i]->weights[j] << " ";
            }
        }
        for (int j = 0; j < outs; j++) {
            for (int i = 0; i < mids; i++) {
              //  cout << std::fixed << std :: setprecision ( 5 )<<  outNeurons[j]->weights[j] << " ";
                cout << outNeurons[j]->weights[i] << " ";

            }
        }
        cout << '\n';
    }

    //сохраняет сетку в массив
    void mSaveKohonet(int* mas) {
        int q = 0;
        for (int i = 0; i < mids; i++) {
            for (int j = 0; j < inputs; j++)    {mas[q] = secNeurons[i]->weights[j]; q++;}
        }
        for (int j = 0; j < outs; j++) {
            for (int i = 0; i < mids; i++)      {mas[q] = outNeurons[j]->weights[i]; q++;}
        }
    }

    //загружает сетку из файла
    void fGetKohonet(ifstream &fin) {
        for (int i = 0; i < mids; i++) {
            for (int j = 0; j < inputs; j++) {
                fin >> secNeurons[i]->weights[j];
                //fin >> std::fixed >> std :: setprecision ( 5 ) >>  secNeurons[i]->weights[j] >> " ";
            }
        }
        for (int j = 0; j < outs; j++) {
            for (int i = 0; i < mids; i++) {
                fin >> outNeurons[j]->weights[i];
               // fin >> std::fixed >> std :: setprecision ( 5 ) >>  outNeurons[j]->weights[j] >> " ";
            }
        }
        printf("\n");
    }



    //загружает сетку из массива  //rnd = 1 - когда 10% массива надо заменить на рандомные числа
    //заметь, что сетка будет симметричная
    void mGetKohonet(int* mas, int rnd) {
        int q = 0;
        for (int i = 0; i < mids; i++) {
            for (int j = 0; j < inputs; j++) {
                int w = rand()%3;//с вероятностью 50% происходит замена числа
                int rrr =  mas[q];
                if ((w==0) && (rnd > 0)) { rrr = rand()%chislo - chislo/2; }
                secNeurons[i]->weights[j]                         = rrr;
            //    secNeurons[mids - i - 1]->weights[inputs - j - 1] = rrr;
                q++;
            }
        }
        for (int j = 0; j < outs; j++) {
            for (int i = 0; i < mids; i++) {
                int w = rand()%3;
                int rrr = mas[q];
                if ((w == 0) && (rnd > 0)) {rrr = rand()%chislo - chislo/2;}
                outNeurons[j]->weights[i]                       = rrr;
//                outNeurons[outs - j - 1]->weights[mids - i - 1] = rrr;
                q++;
            }
        }
    }

/*
    //копирую сетку с бота, немного ее изменяя
    void bGetKohonet(Soldier* Bot, int rnd) {
        int q = 0;
        for (int i = 0; i < mids; i++) {
            for (int j = 0; j <= inputs/2; j++) {
                int w = rand()%3;//с вероятностью 50% происходит замена числа
                int rrr =  (Bot)>Net.secNeurons[i].weights[j];
                if ((w==0) && (rnd > 0)) { rrr = rand()%chislo - chislo/2; }
                secNeurons[i]->weights[j]                          = rrr;
                secNeurons[mids - i - 1]->weights[inputs - j - 1] = rrr;
                q++;
            }
        }
        for (int j = 0; j < outs; j++) {
            for (int i = 0; i < mids; i++) {
                int w = rand()%3;
                int rrr = (Bot)->Net->outNeurons[j]->weights[i];
                if ((w == 0) && (rnd > 0)) {rrr = rand()%chislo - chislo/2;}
                outNeurons[j]->weights[i]                       = rrr;
                outNeurons[outs - j - 1]->weights[mids - i - 1] = rrr;
                q++;
            }
        }
    }
*/

};
