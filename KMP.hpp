#ifndef KMP_HPP
#define KMP_HPP

#include <string>
#include <vector>

class KMP
{
private:
    std::string palavra;
    std::vector<std::vector<int>> transicao;

    void construirAFD();

public:
    KMP(std::string palavra);

    std::vector<int> buscar(std::string texto);
};

#endif
