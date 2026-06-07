#include "SimuladorGame.hpp"
#include "classesauxiliares/Uteis.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>

using namespace std;

SimuladorGame::SimuladorGame(){
    srand(time(NULL));
}

vector<vector<int>> SimuladorGame::construirAFD(const string& sequencia){
    int N = sequencia.size();
    vector<vector<int>> transicao(256, vector<int>(N+1, 0));

    transicao[(unsigned char)sequencia[0]][0] = 1;
    int x = 0;

    for(int j = 1; j < N; j++){
        for(int c = 0; c < 256; c++){
            transicao[c][j] = transicao[c][x];
        }
        transicao[(unsigned char)sequencia[j]][j] = j+1;
        x = transicao[(unsigned char)sequencia[j]][x];
    }
    return transicao;
}

string SimuladorGame::obterJogadaMaquina(const string& j1){
    char inversoMeio = (j1[1] == 'C') ? 'K' : 'C';
    return string(1, inversoMeio) + j1.substr(0,2);
}

bool SimuladorGame::validarJogada(string& jogada){
    if(jogada.size() != 3)
        return false;
    for(char& c : jogada){
        c = toupper(c);
        if(c != 'C' && c != 'K')
            return false;
    }
    return true;
}

void SimuladorGame::iniciarRodada(const string& nomeJ1, const string & jogadaJ1, const string& nomeJ2, const string& jogadaJ2){
    if(jogadaJ1 == jogadaJ2){
        cout << "As sequencias nao podem ser iguais!" << endl;
        return;
    }

    auto afd1 = construirAFD(jogadaJ1);
    auto afd2 = construirAFD(jogadaJ2);
    
    int estado1 = 0;
    int estado2 = 0;

    string historico = "";

    cout << "\nJogando moedas (C = Cara, K = Coroa): \n";
    while(estado1 < 3 && estado2 < 3){
        char moeda = (rand()%2 == 0) ? 'C' : 'K';
        historico += moeda;
        cout << moeda << " ";

        estado1 = afd1[(unsigned char)moeda][estado1];
        estado2 = afd2[(unsigned char)moeda][estado2];
    }

    cout << "\n\nHistorico Final: " << historico << endl;

    if(estado1 == 3){
        cout << "Jogador " << nomeJ1 << " venceu com a sequncia " << jogadaJ1 << "!!!" <<endl;
    }
    else{
        cout << "Jogador " << nomeJ2 << " venceu com a sequncia " << jogadaJ2 << "!!!" << endl;
    }
    Utilidades::aguardarEnter();
}

void SimuladorGame::simularMilRodadas(const string& jogadaJ1, const string& jogadaJ2){
    auto afd1 = construirAFD(jogadaJ1);
    auto afd2 = construirAFD(jogadaJ2);

    vector<ResultadosSimulacao> historicoGeral;
    int vitoriasJ1 = 0;
    int vitoriasMaquina = 0;
    const int TOTAL_JOGOS = 1000;

    cout << "\nSimulando " << TOTAL_JOGOS << " jogos. Aguarde...\n";

    for(int i=1; i<=TOTAL_JOGOS; i++){
        int estado1 = 0;
        int estado2 = 0;
        string historicoMoedas = "";

        while(estado1 < 3 && estado2 < 3){
            char moeda = (rand()%2 == 0) ? 'C' : 'K';
            historicoMoedas += moeda;
            cout << moeda << " ";

            estado1 = afd1[(unsigned char)moeda][estado1];
            estado2 = afd2[(unsigned char)moeda][estado2];
        }

        ResultadosSimulacao resultado;
        resultado.numeroJogo = i;
        resultado.historicoMoedas = historicoMoedas;
        if(estado1 == 3){
            resultado.vencedor = "Jogador";
            vitoriasJ1++;
        }
        else{
            resultado.vencedor = "Maquina";
            vitoriasMaquina++;
        }
        historicoGeral.push_back(resultado);
    }

    cout << "\n---Historico da Simulacao---\n";
    for(const auto& jogo : historicoGeral){
        cout << "Jogo " << jogo.numeroJogo << " | Vencedor: " << jogo.vencedor <<
        " | Sequencia: " << jogo.historicoMoedas << "\n";
    }
    double porcentagemJ1 = ((double)vitoriasJ1/TOTAL_JOGOS) * 100.0;
    double porcentagemMaquina = ((double)vitoriasMaquina/TOTAL_JOGOS) * 100.0;

    cout << "\n\n---Dados da Simulacao---\n";
    cout << "Escolha do Jogador: " << jogadaJ1 << "\n";
    cout << "Escolha da Maquina: " << jogadaJ2 << "\n";
    printf("Vitorias do Jogador: %d (%.2f%%)\n", vitoriasJ1, porcentagemJ1);
    printf("Vitorias da Maquina: %d (%.2f%%)\n", vitoriasMaquina, porcentagemMaquina);
    Utilidades::aguardarEnter();
}

void SimuladorGame::menuSimuladorGame(){
    int opcao;
    do{
        cout << "\n--- Simulador Penney's Game ---" << endl;
        cout << "1 - Jogador vs Jogador" << endl;
        cout << "2 - Jogador vs Maquina" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";

        opcao = Utilidades::lerOpcao(0,2);

        string j1, j2, nome1, nome2;

        switch (opcao){
            case 1:
                nome1 = Utilidades::lerTexto("\nJogador 1 - Digite seu nome: ");
                cout << nome1 << " - Digite sua sequencia de 3 moedas (C/K): ";
                cin >> j1;
                if(!validarJogada(j1)){
                    cout << "Jogada invalida!\n";
                    break;
                }

                nome2 = Utilidades::lerTexto("\nJogador 2 - Digite seu nome: ");
                cout << nome2 << " - Digite sua sequencia de 3 moedas (C/K): ";
                cin >> j2;
                if(!validarJogada(j2)){
                    cout << "Jogada invalida!\n";
                    break;
                }
                Utilidades::aguardarEnter();
                iniciarRodada(nome1, j1, nome2, j2);
                break;

            case 2:
                nome1 = Utilidades::lerTexto("\nJogador 1 - Digite seu nome: ");
                cout << nome1 << " - Digite sua sequencia de 3 moedas (C/K): ";
                cin >> j1;
                if(!validarJogada(j1)){
                    cout << "Jogada invalida!\n";
                    break;
                }

                j2 = obterJogadaMaquina(j1);
                cout << "A maquina escolheu a jogada: " << j2 << endl;
                Utilidades::aguardarEnter();
                int opcaoSimulacao;
                cout << "\n--- Jogador VS Maquina---\n";
                cout << "1 - Simular 1 rodada\n";
                cout << "2 - Simular 1000 rodadas\n";
                cout << "Escolha uma opcao: ";
                opcaoSimulacao = Utilidades::lerOpcao(1, 2);

                if(opcaoSimulacao == 1){
                    iniciarRodada(nome1, j1, "Maquina", j2);
                }
                else{
                    simularMilRodadas(j1,j2);
                }
                break;

            case 0:
                cout << "\nFinalizando...\n" << endl;
                break;

            default:
                cout << "\nOpcao invalida!\n" << endl;
        }
    } while(opcao != 0);
}

