#ifndef LerArquivo_HPP
#define LerArquivo_HPP

#include <string>
#include <optional>
#include <vector>

class LerArquivo{
    public:
        std::string solicitarNomeArquivo() const;
        void removerTextoInicio(std::string &texto) const;
        std::optional<std::string> lerArquivo(const std::string& nome) const;
        std::vector <std::string> listarArquivos() const;
};

#endif