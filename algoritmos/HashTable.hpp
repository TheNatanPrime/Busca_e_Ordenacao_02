#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <string>
#include <vector>

struct palavra
{
    std::string texto;
    int frequencia;

    palavra(std::string texto)
    {
        this->texto = texto;
        frequencia = 1;
    }
};

class HashTable
{
private:
    std::vector<std::vector<palavra>> tabela;

    int tamanho;

    int funcaoHash(std::string palavra);

public:

    HashTable(int tamanho = 1000);

    void inserir(std::string palavra);

    bool contem(std::string palavra);

    std::vector<palavra> obterTodas();
};

#endif
