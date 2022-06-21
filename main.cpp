#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using gridType = vector<vector<char>>;

class Board {
    public:
        vector<vector<char>> values;
    Board(char initFill) {
        int boardSize = 3;
        this->values = vector<vector<char>>(boardSize, vector<char>(boardSize, initFill));
    }

    void printa_board(){
        int i,j;
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                cout << values[i][j];
                if(j < 3)
                    cout << "|";
            cout << endl;
            if(i < 3)
                cout << "------";
            cout << endl;
    }

    bool veri_movimento(int i, int j){
        if(values[i][j] != ' '){
            return false;
        }else{
            return true;
        }
    }

    void movimento(int i, int j, char caracter){
        values[i][j] = caracter;
    }
 
    bool veri_vitoria(char caracter) {
        int i;
        // linhas / colunas
        for(i = 0; i < 3; i++){
            if(values[i][0] == values[i][1] == values[i][2] == caracter){
                return true;    
            }
            if(values[0][i] == values[1][i] == values[2][i]){
                return true;
            }
        }

        //diagonais
        if (values[0][0] == values[1][1] == values[2][2] == caracter){
            return true;
        }
        if(values[2][0] == values[1][1] == values[0][2] == caracter){
            return true;
        }
        return false;
    }
};

int input_valido(string mensagem){
    int n;
    try{
        cout << mensagem;
        cin >> n;
        if(n >= 1 && n <= 3){
            return n;
        }else{
            cout << "Numero deve estar entre 1 e 3" << endl;
            throw;
        }
    }catch(...){
        cout << "Numero invalido!" << endl;
        return input_valido(mensagem);
    }
}

int main(){
    Board board(' ');
    board.printa_board();

    int turno = 0;
    char caracter;
    bool ganhador = false;
    while(!ganhador){
        if(turno == 9){
            caracter = 'E';
            break;
        }else if(turno % 2 == 0){
            caracter = 'X';
        }else if(turno % 2 != 0){
            caracter = 'O';
        }

        cout << "Vez do : " << caracter << endl;

        int i = input_valido("Digite a linha: ");
        int j = input_valido("Digite a coluna: ");

        if(board.veri_movimento(i-1, j-1)){
            board.movimento(i-1, j-1, caracter);
        }else{
            continue;
        }

        ganhador = board.veri_vitoria(caracter);
        turno++;
    }

    board.printa_board();
    if(caracter == 'E'){
        cout << "Empatou" << endl;
    }else{
        cout << "O ganhador foi: " << caracter << endl;
    }
    return 0;
}