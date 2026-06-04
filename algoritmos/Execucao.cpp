#include <iostream>
#include <fstream>
#include <vector>
#include "Execucao.hpp"
#include <string>
#include "classesauxiliares/Uteis.hpp"

using namespace std;

void Execucao::preKMP()
{
    int opcao;
    do
    {
        try{
            string nome = LerArquivo::solicitarNomeArquivo();
            auto texto = LerArquivo::lerArquivo(nome);
            LerArquivo::removerTextoInicio(*texto);

            string palavra;
            cout << "Digite uma palavra para buscar: ";
            cin >> palavra;

            KMP kmp(palavra);
            auto indices = kmp.buscar(*texto);
            for(int indice : indices)
                cout << indice << endl;
        }
        catch (const runtime_error& e){
            cout << e.what() << endl;
            break;
        }
        cout << "1 - Fazer uma nova busca." << endl << 
        "0 - Sair" << endl << 
        "Escolha uma opcao: ";
        opcao = Utilidades::lerOpcao(0, 1);
    } while(opcao != 0);
}

void Execucao::preCorasick()
{
    int opcao;
    do{
        try{
            string nome = LerArquivo::solicitarNomeArquivo();
            auto texto = LerArquivo::lerArquivo(nome);
            LerArquivo::removerTextoInicio(*texto);

            int quantidade;
            cout << "Quantas palavras deseja buscar: " << endl;
            cin >> quantidade;

            AhoCorasick aho;
            for(int i = 0; i < quantidade; i++){
                string palavra;
                cout << "Digite a palavra "<< i+1<< ": ";
                cin >> palavra;
                aho.inserir(palavra);
            }

            aho.construirFalhas();
            aho.buscar(*texto);
        }
        catch(const runtime_error& e){
            cout << e.what() << endl;
            break;
        }
        cout << "1 - Fazer uma nova busca." << endl << 
        "0 - Sair" << endl << 
        "Escolha uma opcao: ";
        opcao = Utilidades::lerOpcao(0, 1);
    } while(opcao != 0);
}
