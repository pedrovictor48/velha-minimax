#include <bits/stdc++.h>

using namespace std;

char caracterePC = 'O';
char caractereUsuario = 'X';

class Board {
    public:
        vector<vector<char>> values;
    Board(char initFill) {
        int boardSize = 3;
        this->values = vector<vector<char>>(boardSize, vector<char>(boardSize, initFill));
    }

    void printa_board(){
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cout << this->values[i][j];
                if(j < 3) cout << "|";
            }
            cout << endl;
            if(i < 3) cout << "------";
            cout << endl;
        }
    }

    bool veri_movimento(int i, int j){
        if(values[i][j] != ' '){
            return false;
        }else{
            return true;
        }
    }

    void movimento(int i, int j, char caracter){
        this->values[i][j] = caracter;
    }
 
    bool veri_vitoria(char caracter) {
        // linhas / colunas
        for(int i = 0; i < 3; i++){
            if(values[i][0] == values[i][1] && values[i][1] == values[i][2] && values[i][2] == caracter){
                return true;    
            }
            if(values[0][i] == values[1][i] && values[1][i] == values[2][i] && values[2][i] == caracter){
                return true;
            }
        }

        //diagonais
        if (values[0][0] == values[1][1] && values[1][1] == values[2][2] && values[2][2] == caracter){
            return true;
        }
        if(values[2][0] == values[1][1] && values[1][1] == values[0][2] && values[0][2] == caracter){
            return true;
        }
        return false;
    }
};

int minimax(char jogador_atual, Board &board, int nivel) {
    //primeiramente casos base
    if(board.veri_vitoria(caracterePC)) return 1;
    if(board.veri_vitoria(caractereUsuario)) return -1;
    if(nivel == 9) return 0; //empatou

    char proximo_jogador = jogador_atual == 'O' ? 'X' : 'O';

    //agora vamos calcular o possível minimo e o possível maximo
    int possivel_minimo, possivel_maximo;
    possivel_minimo = INT_MAX;
    possivel_maximo = INT_MIN;
    for(int linha = 0; linha < 3; linha++) {
        for(int coluna = 0; coluna < 3; coluna++) {
            //se esta coluna ja estiver ocupada, passe
            if(board.values[linha][coluna] != ' ') continue;
            //do contrário tente:
            board.values[linha][coluna] = jogador_atual;
            int retorno_filho = minimax(proximo_jogador, board, nivel + 1);
            board.values[linha][coluna] = ' ';

            //atualizando os possíveis máximos e mínimos
            possivel_maximo = max(possivel_maximo, retorno_filho);
            possivel_minimo = min(possivel_minimo, retorno_filho);
        }
    }

    return possivel_minimo;
    //no final, decidir se retornamos o máximo ou o mínimo, dependendo de quem é o atual:
    if(jogador_atual == caracterePC) return possivel_minimo;
    else return possivel_maximo;
}

pair<int, int> decidindido(Board &board, int nivel) {
    //percorrer todas as possibilidades e decidir qual me retornar o máximo
    //e então retornar esse par linha coluna:
    int maior_ate = INT_MIN;
    pair<int, int> resposta;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board.values[i][j] != ' ') continue;

            board.values[i][j] = caracterePC;
            int atual = minimax(caracterePC, board, nivel);
            board.values[i][j] = ' ';

            if(atual > maior_ate) {
                maior_ate = atual;
                resposta = {i, j};
            }
        }
    }
    cout << "maior dessa vez: " << maior_ate << endl;
    return resposta;
}

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

        int i, j;
        if(turno %2 == 0) {
            i = input_valido("Digite a linha: ");
            j = input_valido("Digite a coluna: ");
        }
        else {
            pair<int, int> decisao = decidindido(board, turno);
            i = decisao.first + 1;
            j = decisao.second + 1;
        }
        

        if(board.veri_movimento(i-1, j-1)){
            board.movimento(i-1, j-1, caracter);
        }else{
            continue;
        }

        ganhador = board.veri_vitoria(caracter);
        turno++;
        board.printa_board();
    }

    if(caracter == 'E'){
        cout << "Empatou" << endl;
    }else{
        cout << "O ganhador foi: " << caracter << endl;
    }
    return 0;
}