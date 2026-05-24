#ifndef Execucao_HPP
#define Execucao_HPP

#include <string>
#include <vector>

class Execucao
{
private:

    int opcao;

public:

    Execucao(int opcao);
    void preKMP();
    void preCorasick();
};

#endif
