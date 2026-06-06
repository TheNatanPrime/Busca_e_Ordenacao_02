#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include "HashTable.hpp"
#include <string>
#include <queue>
#include <fstream>

using namespace std;

struct NoHuffman
{
    string caractere;

    int frequencia;

    NoHuffman* esquerda;
    NoHuffman* direita;

    NoHuffman(string caractere, int frequencia);
};

struct comparador
{
    bool operator()(NoHuffman* a, NoHuffman* b);
};

struct Vcodigo{
    string caractere;
    string codigo;
};

class Huffman
{
    private:

    NoHuffman* raiz;

    vector<Vcodigo> codigos;

    NoHuffman* construirArvore(string texto);

    void gerarCodigos(NoHuffman* no, string codigo);

    string buscarCodigo(string caractere);

    string compactar(string texto);

public:

    void descompactar(string nomeArquivo);

    Huffman();

    void processarTexto(string texto, string nomeArquivo);
};

#endif // HUFFMAN_HPP
