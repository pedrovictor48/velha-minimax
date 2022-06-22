
#include <bits/stdc++.h>

using namespace std;

char caracterePC = 'X';
char caractereUsuario = 'O';

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
                if(j < 2) cout << "|";
            }
            if(i < 2) cout << "\n------\n";
        }
        cout << endl;
    }

    bool veri_movimento(int i, int j){
        return this->values[i][j] == ' ';
    }

    bool movimento(int i, int j, char caracter){
        if(veri_movimento(i, j)) {
            this->values[i][j] = caracter;
            return true;
        }
        return false;
    }

    int pegar_resultado(char caracter) {
        char proximo_jogador = 'X';
        if(caracter == 'X') proximo_jogador = 'O';

        if(veri_vitoria(caracter) == 1) return 1;
        else if(veri_vitoria(proximo_jogador) == 1) return -1;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(this->values[i][j] == ' ') return 2;
                //jogo ainda nao acabou
            }
        }

        return 0;
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

vector<pair<int, int>> posicoes(Board &board) {
    vector<vector<char>> &values = board.values;
    vector<pair<int, int>> retorno;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(values[i][j] == ' ') {
                //posicao valida
                retorno.push_back({i, j});
            }
        }
    }
    return retorno;
} 

pair<int, int> minimax(Board &board, bool jogador, int &rodadas) {
    int resultado = board.pegar_resultado(caracterePC);
    if(resultado != 2)
        return {resultado, rodadas};

    jogador = !jogador;

    char token = 'X';
    if(jogador == 1) token = 'O';
    //char token = (jogador == 1) ? 'O' : 'X';

    vector<pair<int, int>> possibilidades = posicoes(board);
    int melhorValor = INT_MIN;
    int melhorRodada = INT_MAX;

    for(pair<int, int> &possibilidade : possibilidades) {
        int linha, coluna;
        linha = possibilidade.first;
        coluna = possibilidade.second;
        //char token = (jogador == 1) ? 'O' : 'X';
        
        board.values[linha][coluna] = token;
        pair<int, int> retorno_filho = minimax(board, jogador, rodadas);
        board.values[linha][coluna] = ' ';
        int valor = retorno_filho.first;
        if(melhorValor == INT_MIN) {
            melhorValor = valor;
            melhorRodada = rodadas;
        }
        else if(token == caracterePC) {
            if(melhorValor < valor) {
                melhorValor = valor;
            }
            else if(melhorValor == valor && rodadas < melhorRodada) {
                melhorRodada = rodadas;
            }
        }
        else {
            if(melhorValor > valor) {
                melhorValor = valor;
            }
            else if(melhorValor == valor && rodadas < melhorRodada) {
                melhorRodada = rodadas;
            }

        }
    }
    rodadas++;
    return make_pair(melhorValor, rodadas);
}

pair<int, int> movimentoIA(Board &board, bool jogador) {
    vector<pair<int, int>> possibilidades = posicoes(board);
    int melhorValor, melhorRodada;
    pair<int, int> melhorMovimento;
    melhorValor = INT_MIN;
    melhorRodada = INT_MAX;

    char token = 'X';
    if(jogador == 1) token = 'O';

    for(pair<int, int> possibilidade : possibilidades) {
        int linha, coluna;
        linha = possibilidade.first;
        coluna = possibilidade.second;

        board.values[linha][coluna] = token;
        int rodadas = 0, valor;
        pair<int, int> retorno_minimax = minimax(board, jogador, rodadas);
        valor = retorno_minimax.first;
        rodadas = retorno_minimax.second;
        //valor, rodadas = retorno
        board.values[linha][coluna] = ' ';

        if(melhorValor < valor) {
            melhorValor = valor;
            melhorMovimento = possibilidade;
        }
        else if(melhorValor == valor && rodadas < melhorRodada) {
            melhorRodada = rodadas;
            melhorMovimento = possibilidade;
        }

        cout << "i: " <<possibilidade.first << " j: "  << possibilidade.second << " " << valor << " " << rodadas << endl;
    }

    cout << melhorValor << endl;

    return melhorMovimento;
}

bool eh_digito(string &s) {
    for(char c : s) 
        if(!isdigit(c)) return false;
    
    return true;
}

int input_valido(string mensagem){
    int n;
    try{
        cout << mensagem;
        cin >> n;
        if(n >= 1 && n <= 3){
            return n-1;
        }
        else{
            cout << "Numero deve estar entre 1 e 3" << endl;
            throw;
        }
    }catch(...){
        cout << "Numero invalido!" << endl;
        return input_valido(mensagem);
    }
}

void perguntar_comeco() {
    string resposta;
    cout << "Deseja começar primeiro? (S/N)\n";
    cin >> resposta;
    resposta[0] = toupper(resposta[0]);
    while(resposta != "S" && resposta != "N") {
        cout << "Deseja começar primeiro? (S/N)\n";
        cin >> resposta;
        resposta[0] = toupper(resposta[0]);
    }

    if(resposta == "S") swap(caracterePC, caractereUsuario);
}

void computador_joga(Board &board) {
    int i, j;
    int jogador = 0;
    if(caracterePC == 'O') jogador = 1;
    pair<int, int> melhorJogada = movimentoIA(board, jogador);
    i = melhorJogada.first;
    j = melhorJogada.second;
    board.movimento(i, j, caracterePC);
}

int main(){
    Board board(' ');
    board.printa_board();
    //perguntar quem começa
    perguntar_comeco();

    int turno = 0;
    bool ganhador = false;
    while(!ganhador && turno < 9){
        char caracter;
        if(turno % 2 == 0) caracter = 'X';
        else caracter = 'O';

        if(caracter == caracterePC)
            cout << "Máquina joga" << endl;
        else cout << "Você joga" << endl;
        
        if(caracter == caracterePC)
            computador_joga(board);
        else if(caracter == caractereUsuario) {
            int i = input_valido("Digite a linha: ");
            int j = input_valido("Digite a coluna: ");

            if(board.veri_movimento(i, j)) {
                board.movimento(i, j, caracter);
            }
            else {
                cout << "Jogada inválida, tente novamente" << endl;
                continue;
            }
        }

        ganhador = board.veri_vitoria(caracter);
        turno++;
        board.printa_board();
    }

    if(board.veri_vitoria(caractereUsuario)) {
        cout << "Voce ganhou!" << endl;
    }
    else if(board.veri_vitoria(caracterePC)) {
        cout << "O computador ganhou!" << endl;
    }
    else {
        cout << "Empate!" << endl;
    }

    return 0;
}
