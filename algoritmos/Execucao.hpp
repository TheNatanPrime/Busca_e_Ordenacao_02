#ifndef Execucao_HPP
#define Execucao_HPP
#include "classesauxiliares/LerArquivo.hpp"
#include "AhoCorasick.hpp"
#include "KMP.hpp"

class Execucao{
    public:
        void preKMP();
        void preCorasick();
};

#endif
