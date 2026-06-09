#include "ComparadorBuscas.hpp"

#include "KMP.hpp"
#include "AhoCorasick.hpp"

#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

long long ComparadorBuscas::testarIngenua(
    const string& texto,
    const vector<string>& palavras)
{
    auto inicio = high_resolution_clock::now();

    for(const string& palavra : palavras)
    {
        int n = texto.size();
        int m = palavra.size();

        for(int i = 0; i <= n - m; i++)
        {
            int j = 0;

            while(j < m &&
                  texto[i + j] == palavra[j])
            {
                j++;
            }
        }
    }

    auto fim = high_resolution_clock::now();

    return duration_cast<microseconds>(
               fim - inicio
           ).count();
}

long long ComparadorBuscas::testarKMP(
    const string& texto,
    const vector<string>& palavras)
{
    auto inicio = chrono::high_resolution_clock::now();

    for(const string& palavra : palavras)
    {
        KMP kmp(palavra);

        vector<int> ocorrencias = kmp.buscar(texto);
    }

    auto fim = chrono::high_resolution_clock::now();

    return chrono::duration_cast<
           chrono::microseconds>
           (fim - inicio).count();
}

long long ComparadorBuscas::testarAhoCorasick(
    const string& texto,
    const vector<string>& palavras)
{
    auto inicio = high_resolution_clock::now();

    AhoCorasick aho;

    for(const string& palavra : palavras)
    {
        aho.inserir(palavra);
    }

    aho.construirFalhas();

    aho.medirBusca(texto);

    auto fim = high_resolution_clock::now();

    return duration_cast<microseconds>(
               fim - inicio
           ).count();
}

void ComparadorBuscas::executarComparacao(
    const string& texto,
    const vector<string>& palavras)
{
    long long tempoIngenua =
        testarIngenua(texto, palavras);

    long long tempoKMP =
        testarKMP(texto, palavras);

    long long tempoAho =
        testarAhoCorasick(texto, palavras);

    cout << "\n===== COMPARACAO =====\n";

    cout << "Busca Ingenua: "
         << tempoIngenua
         << " microssegundos\n";

    cout << "KMP: "
         << tempoKMP
         << " microssegundos\n";

    cout << "Aho-Corasick: "
         << tempoAho
         << " microssegundos\n";
}
