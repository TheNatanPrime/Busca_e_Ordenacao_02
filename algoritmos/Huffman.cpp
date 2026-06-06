#include "Huffman.hpp"
#include <iostream>
#include <queue>


using namespace std;

NoHuffman::NoHuffman(string caractere, int frequencia)
{
    this->caractere = caractere;
    this->frequencia = frequencia;

    esquerda = nullptr;
    direita = nullptr;
}

bool comparador::operator()(NoHuffman* a, NoHuffman* b)
{
    return a->frequencia > b->frequencia;
}

Huffman::Huffman()
{
    raiz = nullptr;
}

NoHuffman* Huffman::construirArvore(string texto)
{
    HashTable tabela;
    for(char c : texto)
    {
        string letra(1, c);

        tabela.inserir(letra);
    }
    vector<palavra> frequencias = tabela.obterTodas();

    priority_queue < NoHuffman*, vector<NoHuffman*>, comparador> fila;

    for(auto& p : frequencias)
    {
        fila.push(new NoHuffman(p.texto, p.frequencia));
    }

    while(fila.size()>1)
    {
        NoHuffman* esquerda = fila.top();
        fila.pop();

        NoHuffman* direita = fila.top();
        fila.pop();

        NoHuffman* pai = new NoHuffman("", esquerda->frequencia + direita->frequencia);
        pai->esquerda = esquerda;
        pai->direita = direita;

        fila.push(pai);
    }

    if(fila.empty())
    {
        return nullptr;
    }
    return fila.top();
}

void Huffman::gerarCodigos(NoHuffman* no, string codigo)
{
    if(no == nullptr)
    {
        return;
    }

    if(no->esquerda == nullptr && no->direita == nullptr)
    {
        Vcodigo c;

        c.caractere = no->caractere;
        c.codigo = codigo;

        codigos.push_back(c);
    }

    gerarCodigos(no->esquerda, codigo + "0");
    gerarCodigos(no->direita, codigo + "1");
}

void Huffman::processarTexto(string texto, string nomeArquivo)
{
    double taxaCompressao = 0;

    codigos.clear();
    raiz = construirArvore(texto);

    gerarCodigos(raiz, "");

    string compactado = compactar(texto);

    ofstream arquivo("compactados/" + nomeArquivo + ".huff");

    for(auto& c : codigos)
    {
        arquivo << c.caractere << "=" << c.codigo << endl;
    }
    arquivo << "---" << endl;

    arquivo << compactado;

    arquivo.close();

    long long originalSize = texto.size() * 8;
    long long compressedSize = compactado.size();

    cout << "Arquivo compactado com sucesso" << endl;

    cout << "Tamanho Original: " << originalSize << " Bits" << endl;
    cout << "Tamanho apos a compressão: " << compressedSize << " Bits" <<endl;

    if(originalSize > 0)
    {
        taxaCompressao = 100 * (1 - (double)compressedSize/originalSize);
    }

    cout << "Taxa de compressão: " << taxaCompressao << "%" << endl;
}

string Huffman::buscarCodigo(string caractere)
{
    for(auto& c : codigos)
    {
        if(c.caractere == caractere)
        {
            return c.codigo;
        }
    }
    return "";
}


string Huffman::compactar(string texto)
{
    string resultado;

    for(auto &c : texto)
    {
        string letra(1, c);

        resultado += buscarCodigo(letra);
    }
    return resultado;
}

void Huffman::descompactar(string nomeArquivo)
{

    ifstream arquivo("compactados/" + nomeArquivo + ".huff");

    if(!arquivo)
    {
        cout << "Erro ao abrir arquivo" << endl;
        return;
    }
    codigos.clear();

    string linha;

    while(getline(arquivo, linha))
    {
        if(linha == "---")
            break;

        size_t pos = linha.find('=');

        if(pos == string::npos)
        {
            continue;
        }

        Vcodigo c;

        c.caractere = linha.substr(0, pos);
        c.codigo = linha.substr(pos + 1);

        codigos.push_back(c);
    }
    string bits;

    getline(arquivo, bits);

    string atual;
    string textoOriginal;

    for(char bit : bits)
    {
        atual += bit;

        for(auto& c : codigos)
        {
            if(c.codigo == atual)
            {
                textoOriginal += c.caractere;
                atual.clear();
                break;
            }

        }
    }
    ofstream saida("descompactados/"+nomeArquivo+".txt");
    saida << textoOriginal;
    saida.close();

    cout << "Arquivo restaurado com sucesso! " <<endl;
}
