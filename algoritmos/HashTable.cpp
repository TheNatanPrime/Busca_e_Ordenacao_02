#include "HashTable.hpp"



using namespace std;

HashTable::HashTable(int tamanho)
{
    this->tamanho = tamanho;
    tabela.resize(tamanho);
}

bool HashTable::contem(string texto)
{
    int indice = funcaoHash(texto);

    for(palavra &p : tabela[indice])
    {
        if(p.texto == texto)
        {
            return true;
        }

    }
    return false;
}

int HashTable::funcaoHash(string palavra)
{

    int soma = 0;

    for(unsigned char c : palavra)
    {
        soma += c;
    }

    return (soma * 31)% tamanho;


}

void HashTable::inserir(string texto)
{
    int indice = funcaoHash(texto);

    for(palavra &p : tabela[indice])
    {
        if(p.texto == texto)
        {
            p.frequencia++;
            return;
        }
    }

    tabela[indice].push_back(palavra(texto));
}

vector<palavra> HashTable::obterTodas()
{
    vector<palavra> Palavras;

    for(auto &lista : tabela)
    {
        for(auto &p : lista)
        {
            Palavras.push_back(p);
        }
    }
    return Palavras;
}
