#ifndef MENUS_HPP
#define MENUS_HPP

#include "Execucao.hpp"
#include "SimuladorGame.hpp"

class Menus{
    private:
        Execucao execucao;
        SimuladorGame simulador;
        void escolherAlgoritmo(int opcao);
    public:
        void menuInicial();
};

#endif