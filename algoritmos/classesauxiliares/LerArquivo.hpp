#ifndef LERARQUIVO_HPP
#define LERARQUIVO_HPP

#include <string>
#include <optional>
#include <vector>

namespace LerArquivo {
    std::string solicitarNomeArquivo();
    void removerTextoInicio(std::string &texto);
    std::optional<std::string> lerArquivo(const std::string& nome);
    std::vector<std::string> listarArquivos();
}

#endif