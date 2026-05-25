#ifndef Execucao_HPP
#define Execucao_HPP
#include "classesauxiliares/LerArquivo.hpp"
#include "AhoCorasick.hpp"
#include "KMP.hpp"

class Execucao{
    private:
        LerArquivo leitor;
        void escolherAlgoritmo(int opcao);
        void preKMP();
        void preCorasick();
        int lerOpcao() const;
    public:
        void menuInicial();
};

#endif
