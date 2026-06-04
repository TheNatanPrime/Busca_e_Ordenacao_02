#include "Uteis.hpp"
#include <iostream>
#include <limits>

void Utilidades::aguardarEnter() {
    std::cout << "\nPressione Enter para continuar:";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Utilidades::limparTela() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

int Utilidades::lerOpcao(int min, int max) {
    int opcao;
    while (!(std::cin >> opcao) || opcao < min || opcao > max) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Opcao invalida. Digite um numero entre " << min << " e " << max << ": ";
    }
    return opcao;
}

std::string Utilidades::lerTexto(const std::string& mensagem) {
    std::string texto;
    do {
        std::cout << mensagem;
        std::getline(std::cin >> std::ws, texto);
        
        if (texto.empty()) {
            std::cout << "O texto nao pode ser vazio. Tente novamente.\n";
        }
    } while (texto.empty());
    
    return texto;
}