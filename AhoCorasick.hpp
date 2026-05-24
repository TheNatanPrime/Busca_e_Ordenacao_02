#ifndef AHOCORASICK_HPP
#define AHOCORASICK_HPP

#include "No.hpp"
#include <string>
#include <vector>

class AhoCorasick
{
private:

    No* raiz;

    int contadorEstados;

public:

    AhoCorasick();

    void inserir(std::string palavra);
    void construirFalhas();
    void buscar(std::string texto);

};
#endif
