#ifndef AHOCORASICK_HPP
#define AHOCORASICK_HPP

#include "No.hpp"
#include <string>
#include <vector>

class AhoCorasick{
    private:
        No* raiz;
        int contadorEstados;

        void destruir(No* no);

    public:
        AhoCorasick();
        ~AhoCorasick();
        void inserir(const std::string& palavra);
        void construirFalhas();
        void buscar(const std::string& texto);
        int medirBusca(const std::string& texto);

};
#endif
