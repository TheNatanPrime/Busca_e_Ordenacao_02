#include <iostream>
#include <fstream>
#include <vector>
#include "Execucao.hpp"
#include <string>

using namespace std;

void Execucao::menuInicial(){
    int opcao;
    do{
        cout << "Menu" << endl << 
        "1 - Buscar apenas uma palavra(KMP)"<< endl << 
        "2 - Buscar mais de uma palavra(Aho-Corasik)" << endl << 
        "0 - Finalizar" << endl <<
        "Escolha uma opcao: ";
        cin >> opcao;
        escolherAlgoritmo(opcao);
    } while(opcao != 0);
}

void Execucao::escolherAlgoritmo(int opcao){
    switch(opcao){
        case 1:
            preKMP();
            break;
        case 2:
            preCorasick();
            break;
        case 0:
            cout << "Finalizando..." << endl;
            break;
        default:
            cout << "Opcao invalida" << endl;
    }
}

int Execucao::lerOpcao() const{
    int opcao;
    cin.clear();
    while(!(cin >> opcao)){
        cin.clear();
        cout << "Entrada invalida. Digite um numero: ";
    }
    if(opcao < 0 || opcao > 1){
        cout << "Opcao invalida" << endl;
        opcao = 0;
    }
    return opcao;
}

void Execucao::preKMP()
{
    int opcao;
    do
    {
        try{
            string nome = leitor.solicitarNomeArquivo();
            auto texto = leitor.lerArquivo(nome);
            leitor.removerTextoInicio(*texto);

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
        opcao = lerOpcao();
    } while(opcao != 0);
}

void Execucao::preCorasick()
{
    int opcao;
    do{
        try{
            string nome = leitor.solicitarNomeArquivo();
            auto texto = leitor.lerArquivo(nome);
            leitor.removerTextoInicio(*texto);

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
        opcao = lerOpcao();
    } while(opcao != 0);
}
