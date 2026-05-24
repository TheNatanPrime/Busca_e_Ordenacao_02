#include <iostream>
#include <fstream>
#include <vector>
#include "Execucao.hpp"
#include "KMP.hpp"
#include "AhoCorasick.hpp"

using namespace std;

void Execucao::preCorasick()
{

    string nomearquivo;
    string palavra;
    string texto;
    string linha;
    int opcao = 1;

    do
    {
        cout << "Digite o nome do arquivo com o texto(nomedoarquivo.txt): " << endl;
        cin >> nomearquivo;

        fstream arquivo(nomearquivo);

        if(!arquivo)
        {
            cout << "Arquivo não foi aberto " << endl;
            cout << "Escolha uma opcao: "<< endl << "1 - Abrir outro arquivo." << endl << "0 - Sair"<<endl;
            cin >> opcao;
        }
        else
        {
            while(getline(arquivo, linha))
            {
                texto += linha;
                texto += '\n';
            }

            arquivo.close();

            if(texto.size() >= 3 && (unsigned char)texto[0] == 239 && (unsigned char)texto[1] == 187 && (unsigned char)texto[2] == 191)
                texto.erase(0, 3);

                AhoCorasick aho;
                int quantidade;

                cout << "quantas palavras deseja buscar: " << endl;
                cin >> quantidade;

                for(int i = 0; i < quantidade; i++){
                    cout << "digite a palavra "<< i+1<<endl;
                    cin >> palavra;

                    aho.inserir(palavra);
                }

                aho.construirFalhas();
                aho.buscar(texto);

            texto.clear();

            cout << "1 - Fazer uma nova busca."<<endl<<"0 - sair" << endl;
            cin >> opcao;
        }

    }
    while(opcao != 0);
}


void Execucao::preKMP()
{

    string nomearquivo;
    string palavra;
    string texto;
    string linha;
    int opcao = 1;

    do
    {
        cout << "Digite o nome do arquivo com o texto(nomedoarquivo.txt): " << endl;
        cin >> nomearquivo;

        fstream arquivo(nomearquivo);

        if(!arquivo)
        {
            cout << "Arquivo não foi aberto " << endl;
            cout << "Escolha uma opcao: "<< endl << "1 - Abrir outro arquivo." << endl << "0 - Sair"<<endl;
            cin >> opcao;
        }
        else
        {
            while(getline(arquivo, linha))
            {
                texto += linha;
                texto += '\n';
            }

            arquivo.close();

            if(texto.size() >= 3 && (unsigned char)texto[0] == 239 && (unsigned char)texto[1] == 187 && (unsigned char)texto[2] == 191)
                texto.erase(0, 3);

            cout << "Digite uma palavra para buscar no texto: " << endl;
            cin >> palavra;

            KMP kmp(palavra);

            vector<int> indices = kmp.buscar(texto);

            cout << "Palavra encontrada nos indices: " << endl;

            for(int indice : indices)
            {
                cout << indice << endl;
            }
            texto.clear();

            cin.get();

            cout << "1 - Fazer uma nova busca."<<endl<<"0 - sair" << endl;
            cin >> opcao;
        }

    }
    while(opcao != 0);
}



Execucao::Execucao(int opcao)
{
    this->opcao = opcao;

    switch(opcao)
    {
    case 1:
        preKMP();
        break;
    case 2:
    preCorasick();
    break;
    /*case 3:
    break;
    case 4;
    break;*/
    default:
        break;
    }
}
