#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int branco = -1;

int cria_board(int board[][3]){
    for(int i = 0; i < 3; i++)
        for(int j; j < 3; j++)
            board[i][j] = branco;
}

void printa_board(int board[][3]){
    cout << "entrou";
}

int input_valido(string  mensagem){

}

bool veri_movimento(int i, int j, int board){

}

bool veri_ganhar(int caracter, int board){

}