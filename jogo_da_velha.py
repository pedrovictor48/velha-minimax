branco = " "
token = ["X", "O"]
def criaBoard():
    board = [
        [branco, branco, branco],
        [branco, branco, branco],
        [branco, branco, branco]
    ]
    return board
    

def printBoard(board):
    print()
    for i in range(3):
        print("|".join(board[i]))
        if i < 2:
            print("-"*6)

def inputValido(mensagem):
    try:
        n = int(input(mensagem))
        if n >= 1 and n <= 3:
            return n - 1
        else:
            print("Número deve estar entre 1 e 3. \n")
            return inputValido(mensagem)
    except:
        print("Número inválido. \n")
        return inputValido(mensagem)

def veriMovimento(i,j, board):
    if(board[i][j] != branco):
        return False
    else:
        return True

def movimento(i, j, jogador, board):
    board[i][j] = token[jogador]

def veriGanhador(board):
    #linhas / colunas
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] and board[i][0] != branco:
            return board[i][0]
        if board[0][i] == board[1][i] == board[2][i] and board[0][i] != branco:
            return board[0][i]
        
    #diagonais 
    if board[0][0] == board[1][1] == board[2][2] and board[0][0] != branco:
        return board[0][0]
    elif board[2][0] == board[1][1] == board[0][2] and board[2][0] != branco:
        return board[2][0]
    
    for i in range(3):
        for j in range(3):
            if board[i][j] == branco:
                return False
    
    return "E"