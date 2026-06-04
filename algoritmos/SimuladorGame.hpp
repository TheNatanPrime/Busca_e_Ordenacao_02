#ifndef SIMULADORGAME_HPP
#define SIMULADORGAME_HPP

#include <vector>
#include <string>

struct ResultadosSimulacao{
    int numeroJogo;
    std::string historicoMoedas;
    std::string vencedor;
};

class SimuladorGame{
    private:
        std::vector<std::vector<int>> construirAFD(const std::string& sequencia);
        std::string obterJogadaMaquina(const std::string & j1);
        bool validarJogada(std::string& jogada);
        void iniciarRodada(const std::string& nomeJ1, const std::string & jogadaJ1, const std::string &nomeJ2, const std::string& jogadaJ2);
        void simularMilRodadas(const std::string& jogadaJ1, const std::string& jogadaJ2);
    public:
        SimuladorGame();
        void menuSimuladorGame();
};

#endif