#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace Utilidades {
    void aguardarEnter();
    void limparTela();
    int lerOpcao(int min, int max);
    std::string lerTexto(const std::string& mensagem);
}

#endif