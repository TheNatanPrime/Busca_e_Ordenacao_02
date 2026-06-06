#include "WordCloud.hpp"
#include "classesauxiliares/LerArquivo.hpp"


#include <fstream>
#include <algorithm>
#include <cctype>
#include <iostream>
using namespace std;

WordCloud::WordCloud()
{
    carregarStopwords();
}

void WordCloud::merge(vector<palavra>& v, int inicio, int meio, int fim){

    vector<palavra> aux;

    int esquerda = inicio;
    int direita = meio + 1;

    while(esquerda <= meio && direita <= fim){

        if(v[esquerda].frequencia >= v[direita].frequencia){
        aux.push_back(v[esquerda]);
        esquerda++;
        }else{
            aux.push_back(v[direita]);
            direita++;
        }
    }
    while(esquerda <= meio){
    aux.push_back(v[esquerda]);
    esquerda++;
    }

    while(direita <= fim){
        aux.push_back(v[direita]);
        direita++;
    }

    for(int i = 0; i < aux.size(); i++){
        v[inicio + i] = aux[i];
    }
}

void WordCloud::mergeSort(vector<palavra>& v, int inicio, int fim){
    if(inicio >= fim){
        return;
    }

    int meio = (inicio + fim)/2;

    mergeSort(v, inicio, meio);

    mergeSort(v, meio + 1, fim);

    merge(v, inicio, meio, fim);

}

void WordCloud::carregarStopwords()
{

    vector<string> palavrasProibidas = {"o", "a", "os", "as", "um", "uma",
                                        "de", "do", "da", "e", "que", "para", "era", "mas",
                                        "por", "mais", "como", "foi", "sem", "nem", "dos",
                                        "capitulo", "das", "lhe", "there", "its", "where",
                                        "the", "and", "of", "to", "in", "on", "at",
                                        "he", "she", "it", "that", "you", "was", "his", "her",
                                        "but", "not", "with", "for", "had", "him",
                                        "all", "have", "what", "are", "from", "they",
                                        "this", "your", "their", "which"
                                       };

    for(string p : palavrasProibidas)
    {

        stopwords.inserir(p);

    }

}

string WordCloud::limparPalavra(string palavra)
{
    string resultado;

    for(char c : palavra)
    {
        if(isalpha(c))
        {
            resultado += tolower(c);
        }
    }
    return resultado;
}



void WordCloud::processarArquivo(string nomeArquivo)
{
    stringstream ss(nomeArquivo);

    string palavra;

    while(ss >> palavra)
    {
        palavra = limparPalavra(palavra);

        if(!palavra.empty() && palavra.size() > 2 && !stopwords.contem(palavra))
        {
            tabela.inserir(palavra);
        }
    }
}

void WordCloud::gerar()
{
    LerArquivo leitor;

    try
    {
        vector<string> arquivos = leitor.listarArquivos();

        if(arquivos.empty())
        {
            cout << "Nenhum arquivo encontrado" << endl;
            return;
        }

        cout << "\nArquivos disponiveis: "<<endl;

        for(int i = 0; i < arquivos.size(); i++)
        {
            cout << i + 1 << "-" << arquivos[i] << endl;
        }

        int quantidade;

        cout << "Quantos arquivos deseja utilizar? " << endl;
        cin >> quantidade;

        for(int i = 0; i < quantidade; i++)
        {
            int opcao;
            cout << "digite o numero do arquivo " << i + 1 << ":" << endl;

            cin >> opcao;

            if(opcao < 1 || opcao > arquivos.size())
            {
                cout << "opcao invalida" << endl;
                i--;
                continue;
            }

            auto opcaotexto = leitor.lerArquivo(arquivos[opcao - 1]);

            if(!opcaotexto.has_value())
            {
                cout << "Erro ao abrir arquivo " << endl;
                continue;
            }
            string texto = opcaotexto.value();

            leitor.removerTextoInicio(texto);

            processarArquivo(texto);

        }
        mostrarRanking(20);
    }
    catch(const exception& e)
    {
        cout<<e.what()<<endl;
    }


}

void WordCloud::mostrarRanking(int quantidade)
{
    vector<palavra> palavras = tabela.obterTodas();

    if(!palavras.empty()){
        mergeSort(palavras, 0, palavras.size() - 1);
    }

    cout << "\nTop "<< quantidade << " palavras\n\n";

    for(int i = 0; i< quantidade && i < palavras.size(); i++)
    {
        cout<<i+1<<"-"<< palavras[i].texto<<"->"<< palavras[i].frequencia<<endl;

    }
}
