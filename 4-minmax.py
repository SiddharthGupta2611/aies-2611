b = [" "] * 9
wins = [(0, 1, 2), (3, 4, 5), (6, 7, 8), (0, 3, 6), (1, 4, 7), (2, 5, 8), (0, 4, 8), (2, 4, 6)]

def win(p):
    for x, y, z in wins:
        if b[x] == b[y] == b[z] == p:
            return True
    return False

def minimax(player):
    if win("O"): 
        return 1
    if win("X"): 
        return -1
    if " " not in b: 
        return 0

    if player == "O":
        best = -float('inf')
        for i in range(9):
            if b[i] == " ":
                b[i] = "O"
                score = minimax("X")
                b[i] = " "
                best = max(best, score)
        return best
    else:
        best = float('inf')
        for i in range(9):
            if b[i] == " ":
                b[i] = "X"
                score = minimax("O")
                b[i] = " "
                best = min(best, score)
        return best

def computer_move():
    best = -float('inf')
    move = 0
    for i in range(9):
        if b[i] == " ":
            b[i] = "O"
            score = minimax("X")
            b[i] = " "
            if score > best:
                best = score
                move = i
    return move

def display():
    print(b[0:3])
    print(b[3:6])
    print(b[6:9])
    print()

game_over = False
for turn in range(9):
    if turn % 2 == 0:
        pos = int(input("Enter position (1-9): ")) - 1
        b[pos] = "X"
        player = "X"
    else:
        pos = computer_move()
        b[pos] = "O"
        player = "O"
        
    display()
    
    if win(player):
        print(f"{player} wins!")
        game_over = True
        break

if not game_over:
    print("Draw!")
#O(9!)