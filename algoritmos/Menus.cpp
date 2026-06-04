#include "Menus.hpp"
#include "classesauxiliares/Uteis.hpp"
#include <iostream>

using namespace std;

void Menus::menuInicial(){
    int opcao;
    do{
        cout << "-------Menu-------" << endl << 
        "1 - Buscar apenas uma palavra(KMP)"<< endl << 
        "2 - Buscar mais de uma palavra(Aho-Corasik)" << endl << 
        "3 - Simulador Penney's Game" << endl << 
        "0 - Finalizar" << endl <<
        "Escolha uma opcao: ";
        opcao = Utilidades::lerOpcao(0,3);
        escolherAlgoritmo(opcao);
    } while(opcao != 0);
}

void Menus::escolherAlgoritmo(int opcao){
    switch(opcao){
        case 1:
            execucao.preKMP();
            break;
        case 2:
            execucao.preCorasick();
            break;
        case 3:
            simulador.menuSimuladorGame();
            break;
        case 0:
            cout << "\nFinalizando...\n" << endl;
            break;
        default:
            cout << "\nOpcao invalida\n" << endl;
    }
}