#define NO_HPP
#ifdef NO_HPP

#include <unordered_map>
#include <vector>
#include <string>

class No{
    public:

    std::unordered_map<char, No*> filhos;

    No* falha;

    std::vector<std::string> saidas;

    int estado;

    No(int estado){

    this->estado = estado;

    falha = nullptr;
    }
};

#endif
