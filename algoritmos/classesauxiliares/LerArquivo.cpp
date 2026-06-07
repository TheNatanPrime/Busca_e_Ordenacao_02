#include "LerArquivo.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

vector<string> LerArquivo::listarArquivos() {
    vector<string> arquivos;

    if(!filesystem::exists("textos") || !filesystem::is_directory("textos")){
        cout << "Pasta de textos nao encontrada" << endl;
        return arquivos;
    }

    for(const auto& entrada : filesystem::directory_iterator("textos")){
        if(entrada.path().extension() == ".txt")
            arquivos.push_back(entrada.path().stem().string());
    }
    return arquivos;
}

vector<string> LerArquivo::listarCompactados(){
    vector<string> arquivos;

    if(!filesystem::exists("compactados") || !filesystem::is_directory("compactados")){
        cout << "Pasta de textos nao encontrada" << endl;
        return arquivos;
    }

    for(const auto& entrada : filesystem::directory_iterator("compactados")){
        if(entrada.path().extension() == ".huff")
            arquivos.push_back(entrada.path().stem().string());
    }
    return arquivos;
}

string LerArquivo::solicitarNomeArquivo() {
    int nomearquivo;
    while(true){
        auto arquivos = listarArquivos(); 

        if(arquivos.empty())
            throw runtime_error("Nenhum arquivo .txt encontrado");

        cout << "\nArquivos disponiveis" << endl;
        for(int i = 0; i < (int)arquivos.size();i++){
            cout << i + 1 << " - " << arquivos[i] << endl;
        }

        cout << "Digite a opcao do arquivo com o texto desejado: ";
        cin >> nomearquivo;

        if(nomearquivo < 1 || nomearquivo > (int)arquivos.size())
            throw runtime_error("Opcao invalida");

        if(lerArquivo(arquivos[nomearquivo - 1]).has_value())
            return arquivos[nomearquivo - 1];
        
        cout << "Arquivo não encontrado" << endl;
        cout << "1 - Abrir outro arquivo." << endl << 
        "0 - Sair" << endl << 
        "Escolha uma opcao: ";
        int opcao;
        cin >> opcao;
        if(opcao != 1)
            throw runtime_error("Nenhum arquivo selecionado");
    }
}

optional<string> LerArquivo::lerArquivo(const string& nome) {
    ifstream arquivo("textos/" + nome + ".txt");

    if(!arquivo)
        return nullopt;

    string texto, linha;

    while(getline(arquivo, linha)){
        texto += linha;
        texto += '\n';
    }

    return texto;
}

void LerArquivo::removerTextoInicio(string &texto) {
    if(texto.size() >= 3 && (unsigned char)texto[0] == 239 && (unsigned char)texto[1] == 187 && (unsigned char)texto[2] == 191)
        texto.erase(0, 3);
}