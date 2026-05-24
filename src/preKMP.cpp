#include "preKMP.h"
#include "KMP.hpp"

class preKMP{

    private void

    public void executar(){
    string nomearquivo;
    string palavra;
    string texto;
    string linha;
    int opcao = 1;

    do
    {
        cout << "Digite o nome do arquivo com o texto: " << endl;
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

}
