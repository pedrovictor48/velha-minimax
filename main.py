from jogo_da_velha import *
#from minimax import *
from minimax2 import *
print("Bem-vindo ao Jogo da Velha\n")

while True:
    board = criaBoard()
    ganhador = False
    
    while True:
        begin = input("Deseja comecar?[s/n] ").lower().strip()
        if begin == "s":
            jogador = 1
        elif begin == "n":
            jogador = 0
        else:
            print("Digite uma opcao valida!\n")
            continue
        break
    
    while not ganhador:
        printBoard(board)
        print(f"\nVez do: {token[jogador]}")
        
        if jogador == 0:
            i, j = movimentoIA(board, jogador)
        else: 
            #i, j = movimentoIA(board, jogador)
            i = inputValido("Digite a linha: ")
            j = inputValido("Digite a coluna: ")

        if veriMovimento(i, j, board):
            movimento(i, j, jogador, board)
            jogador = (jogador + 1) % 2
        else:
            print("Ja existe nessa posição!")
            continue
        ganhador = veriGanhador(board)
    
    printBoard(board)
    print("\n", "==="*15, "\n")
    
    if ganhador == "E":
        print("Empatou")
    else:
        print(f"Ganhador: {ganhador}!")
    print("\n","==="*15)
    
    while True:
        denovo = input("Deseja jogadar de novo?[s/n] ").lower().strip()
        if begin == "s":
            denovo = 1
        elif begin == "n":
            denovo = 0
        else:
            print("Digite uma opcao valida!\n")
            continue
        break
    if denovo == 0:
        break
print("Programa encerrado!\n")