#ifndef COMPARADORBUSCAS_HPP
#define COMPARADORBUSCAS_HPP

#include <string>
#include <vector>

class ComparadorBuscas
{
private:

    long long testarIngenua(
        const std::string& texto,
        const std::vector<std::string>& palavras
    );

    long long testarKMP(
        const std::string& texto,
        const std::vector<std::string>& palavras
    );

    long long testarAhoCorasick(
        const std::string& texto,
        const std::vector<std::string>& palavras
    );

public:

    void executarComparacao(
        const std::string& texto,
        const std::vector<std::string>& palavras
    );
};

#endif
