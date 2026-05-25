#include "KMP.hpp"
#include <iostream>
#include <fstream>

using namespace std;

KMP::KMP(string palavra){
    this->palavra = palavra;
    construirAFD();
}

void KMP::construirAFD()
{
    int N = palavra.size();

    transicao.resize(256, vector<int>(N+1, 0));

    transicao[(unsigned char)palavra[0]][0] = 1;

    int x = 0;

    for(int j = 1; j < N; j++){
        for(int c = 0; c < 256;c++){
            transicao[c][j] = transicao[c][x];
        }
        transicao[(unsigned char)palavra[j]][j] = j + 1;
        x=transicao[(unsigned char)palavra[j]][x];
    }
}

vector<int> KMP::buscar(const string& texto)
{
    vector<int> indices;

    int estado = 0;

    int N = palavra.size();

    for(int i = 0; i < int(texto.size()); i++){
        estado = transicao[(unsigned char)texto[i]][estado];
        if(estado == N){
        indices.push_back(i-N+1);
        }

    }
    return indices;
}