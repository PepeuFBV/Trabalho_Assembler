#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

void montandoBinario(string linha, unordered_map<string, int> labels);
void montandoHexadecimal();

int main() {

    ifstream file("entrada.asm");
    if (!file.is_open() && !file.bad()) {
        cerr << "Arquivo n�o pode ser aberto\n"; //exibe a mensagem de erro
        return 1;
    }

    string linhaAtual;
    unordered_map<string, int> labels;
    int nLinha = 0;

    while (getline(file, linhaAtual)) { //loop que l� de linha em linha
        nLinha++;

        size_t indice = linhaAtual.find(':'); //encontra indice de ':'
        if (indice != string::npos) { //verifica se ':' foi encontrado, se n�o, apenas seguir lendo as linhas
            string label = linhaAtual.substr(0, indice); //cria uma nova substring cortando a partir do in�cio at� o �ndice - 1
            labels[label] = nLinha; //salva no map com o label e linha (virar� endere�o) do comando
        }

    }
    file.close(); //le o arquivo pela primeira vez pegando os labels


    file.open("entrada.asm"); //abre o arquivo pela segunda vez para ai realmente transformar em bin�rio
    if (!file.is_open() && !file.bad()) {
        cerr << "Arquivo n�o pode ser aberto\n"; //exibe a mensagem de erro
        return 1;
    }

    char tabulacao = '\t';
    while (getline(file, linhaAtual)) { //loop que l� de linha em linha

        size_t indice = linhaAtual.find(':'); //encontra indice de ':'
        if (indice != string::npos) { //verifica se ':' foi encontrado, se n�o, apenas seguir lendo as linhas
            //cria uma nova substring cortando a partir do fim do label at� o final da string completa
            linhaAtual = linhaAtual.substr(indice+2, linhaAtual.length());
        }
        //remove as ocorrencias de '/t'
        linhaAtual.erase(remove(linhaAtual.begin(), linhaAtual.end(), tabulacao), linhaAtual.end());

        montandoBinario(linhaAtual, labels); //coloca o bin�rio no outro arquivo
        montandoHexadecimal(); //coloca o hexadecimal no outro arquivo, a patir do arquivo bin�rio criado

    }

    return 0;
}


void montandoBinario(string linha, unordered_map<string, int> labels) { //consertar
    switch (true) {
        case (linha.find("add") != string::npos):
           binAdd();
           break;
        case (linha.find("sub") != string::npos):
            binSub();
            break;
        case (linha.find("mult") != string::npos):
            binMult();
            break;
        case (linha.find("div") != string::npos):
            binDiv();
            break;
        case (linha.find("jmp") != string::npos):
            binJmp();
            break;


        case default
            break;
    }
}




}

void montandoHexadecimal() {

}