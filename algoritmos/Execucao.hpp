#ifndef Execucao_HPP
#define Execucao_HPP
#include "classesauxiliares/LerArquivo.hpp"
#include "AhoCorasick.hpp"
#include "KMP.hpp"
#include "WordCloud.hpp"
#include "Huffman.hpp"

class Execucao
{
private:
    LerArquivo leitor;
    void escolherAlgoritmo(int opcao);
    void preKMP();
    void preCorasick();
    void preWordCloud();
    void preHuffman();
    int lerOpcao() const;
public:
    void menuInicial();
};

#endif
