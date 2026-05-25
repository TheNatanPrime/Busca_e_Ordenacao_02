#include "AhoCorasick.hpp"
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

AhoCorasick::AhoCorasick()
{
    contadorEstados = 0;
    raiz = new No(contadorEstados++);
}

void AhoCorasick::inserir(const string& palavra)
{
    No* atual = raiz;

    for(char c : palavra)
    {
        if(atual->filhos.find(c) == atual->filhos.end())
        {
            atual->filhos[c] = new No(contadorEstados++);
        }
        atual = atual->filhos[c];
    }

    atual->saidas.push_back(palavra);
}

void AhoCorasick::construirFalhas()
{
    queue<No*> fila;
    raiz->falha = raiz;

    for(auto par : raiz->filhos)
    {
        par.second->falha = raiz;

        fila.push(par.second);
    }

    while(!fila.empty())
    {
        No* atual = fila.front();
        fila.pop();

        for(auto par : atual->filhos)
        {
            char c = par.first;

            No* filho = par.second;

            No* falhaAtual = atual->falha;

            while(falhaAtual != raiz && falhaAtual->filhos.find(c) == falhaAtual->filhos.end())
            {
                falhaAtual = falhaAtual->falha;
            }

            if(falhaAtual->filhos.find(c)!= falhaAtual->filhos.end())
            {
                filho->falha = falhaAtual->filhos[c];
            }
            else
            {
                filho->falha = raiz;
            }
            for(string s : filho->falha->saidas)
            {
                filho->saidas.push_back(s);
            }
            fila.push(filho);
        }
    }

}

void AhoCorasick::buscar(const string& texto){

    No* atual = raiz;

    for(int i = 0; i < int(texto.size()); i++){
        char c = texto[i];

        while(atual != raiz && atual->filhos.find(c) == atual->filhos.end()){
        atual = atual->falha;
        }

        if(atual->filhos.find(c)!= atual->filhos.end()){
        atual = atual->filhos[c];
        }

        for(string palavra : atual->saidas){
        cout<< "Palavra "<< palavra << " encontrada no indice "<< i-palavra.size()+ 1 << endl;
        }
    }
}

