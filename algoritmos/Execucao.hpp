#ifndef Execucao_HPP
#define Execucao_HPP
#include "classesauxiliares/LerArquivo.hpp"
#include "AhoCorasick.hpp"
#include "KMP.hpp"
#include "WordCloud.hpp"
#include "Huffman.hpp"
#include "ComparadorBuscas.hpp"

class Execucao{
    public:
        void preKMP();
        void preCorasick();
        void preWordCloud();
        void preHuffman();
        void preComparacao();
};

#endif
