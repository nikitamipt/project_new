#pragma once

#include <vector>
#include <cmath>

//using namespace std;

int aaa = 0;


class Neuron {
public:
    std::vector <int> weights;
    std::vector <Neuron*> dendrits;
    float value;
    Neuron() { value = 1; };

    float getSignal() {
        return (1 / (1 + exp(-(kernelFunction())))) ;
       // return kernelFunction();
    }

/*Суммирующая функция, которая суммирует(В самом простом случае)
входные сигналы*/
    virtual float kernelFunction() {
        float result = 0;
//aaa++;
        for(int i = 0; i < dendrits.size(); i++){
            float dentr = dendrits[i]->getSignal();
            result += dentr * float(weights[i]);
//for (int i = 0; i < aaa; i++) { printf("          ");} printf("dentris[%d] = %d    weight = %d    cerresult = %d\n", i, dentr, weights[i], result);
        }
//for (int i = 0; i < aaa; i++) { printf("          ");} printf("%d\n", result);
//aaa--;
        return result;
    }
};


class InputNeuron : public Neuron {
public:
    virtual float kernelFunction() {
//aaa++;
//for (int i = 0; i < aaa; i++) { printf("          ");} printf("%d\n", value);
//aaa--;
        return value;
    }

};
