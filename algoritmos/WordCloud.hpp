#ifndef WORDCLOUD_HPP
#define WORDCLOUD_HPP

#include "HashTable.hpp"
#include <string>
#include <sstream>


class WordCloud
{
private:

    HashTable tabela;

    HashTable stopwords;

    std::string limparPalavra(std::string palavra);

    void carregarStopwords();

    void mergeSort(std::vector<palavra>& V, int inicio, int fim);

    void merge(std::vector<palavra>& v, int inicio, int meio, int fim);

public:

    WordCloud();

    void gerar();

    void processarArquivo(std::string texto);

    void mostrarRanking(int quantidade);
};

#endif
