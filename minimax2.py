from jogo_da_velha import token, branco, veriGanhador
score = {"E" : 0, "X" : 1, "O": -1}

def posicoes(board):
    posicoes = []
    for i in range(3):
        for j in range(3):
            if board[i][j] == branco:
                posicoes.append([i, j])
    return posicoes

def movimentoIA(board, jogador):
    # return jogada
    possibilidades = posicoes(board)
    melhorValor = melhorMovimento = melhorRodada=  None
    for possibilidade in possibilidades:
        board[possibilidade[0]][possibilidade[1]] = token[jogador]
        rodadas = 0
        valor, rodadas = minimax(board, jogador, rodadas)
        board[possibilidade[0]][possibilidade[1]] = branco
        print(possibilidade, valor, rodadas)
        if melhorValor is None:
            melhorValor = valor
            melhorMovimento = possibilidade
            melhorRodada = rodadas
        elif(jogador == 0):
            if valor == melhorValor:
                if rodadas < melhorRodada:
                    melhorValor = valor
                    melhorMovimento = possibilidade
                    melhorRodada = rodadas
            elif valor > melhorValor:
                melhorValor = valor
                melhorMovimento = possibilidade
                melhorRodada = rodadas
        elif(jogador == 1):
            if valor == melhorValor:
                if rodadas < melhorRodada:
                    melhorValor = valor
                    melhorMovimento = possibilidade
                    melhorRodada = rodadas
            if valor < melhorValor:
                melhorValor = valor
                melhorMovimento = possibilidade
                melhorRodada = rodadas
    return melhorMovimento


def minimax(board, jogador, rodadas):
    ganhador = veriGanhador(board)
    if(ganhador):
        return score[ganhador], rodadas
    jogador = (jogador + 1) % 2
    
    possibilidades = posicoes(board)
    melhorValor = None
    
    for possibilidade in possibilidades:
        board[possibilidade[0]][possibilidade[1]] = token[jogador]
        valor, rodadas = minimax(board, jogador, rodadas)
        board[possibilidade[0]][possibilidade[1]] = branco
        
        if melhorValor is None:
            melhorValor = valor
            melhorRodada = rodadas
        elif(jogador == 0):
            if valor == melhorValor:
                if rodadas < melhorRodada:
                    melhorValor = valor
                    melhorRodada = rodadas
            elif valor > melhorValor:
                melhorValor = valor
                melhorRodada = rodadas
        elif(jogador == 1):
            if valor == melhorValor:
                if rodadas < melhorRodada:
                    melhorValor = valor
                    melhorRodada = rodadas
            if valor < melhorValor:
                melhorValor = valor
                melhorRodada = rodadas
    rodadas+=1
    retorno = (melhorValor, rodadas)
    return retorno