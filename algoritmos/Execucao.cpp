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

void Execucao::preWordCloud()
{
    int opcao = 1;
    do
    {
        WordCloud nuvem;
        nuvem.gerar();

        cout <<"\n1 - Gerar nova nuvem de palavras"<<endl
             <<"0 - Sair"<<endl
             << "Escolha uma opcao: "<<endl;

        opcao = Utilidades::lerOpcao(0, 1);
    }
    while(opcao != 0);
}

void Execucao::preHuffman()
{
    int opcao;

    do
    {
        cout << "1 - Compactar arquivo" << endl << 
        "2 - Descompactar arquivo" << endl
        << "0 - Voltar" << endl << "Opcao: ";

        opcao = Utilidades::lerOpcao(0, 2);

        switch(opcao)
        {
            case 1:
            {
                string nome = LerArquivo::solicitarNomeArquivo();

                auto texto = LerArquivo::lerArquivo(nome);

                if(!texto.has_value())
                {
                    cout << "Erro ao abrir arquivo" << endl;
                    break;
                }

                LerArquivo::removerTextoInicio(*texto);

                Huffman h;
                h.processarTexto(*texto, nome);

                break;
            }

            case 2:
            {
                vector<string> arquivos =
                    LerArquivo::listarCompactados();

                if(arquivos.empty())
                {
                    cout << "Nenhum arquivo compactado encontrado"
                         << endl;
                    break;
                }

                cout << "\nArquivos compactados:\n";

                for(int i = 0; i < (int)arquivos.size(); i++)
                {
                    cout << i + 1
                         << " - "
                         << arquivos[i]
                         << endl;
                }

                int escolha;

                cout << "\nEscolha um arquivo: ";
                cin >> escolha;

                if(escolha < 1 ||
                   escolha > (int)arquivos.size())
                {
                    cout << "Opcao invalida!" << endl;
                    break;
                }

                Huffman h;

                h.descompactar(
                    arquivos[escolha - 1]
                );

                break;
            }

            case 0:
                break;

            default:
                cout << "Opcao invalida!" << endl;
        }

    } while(opcao != 0);
}
