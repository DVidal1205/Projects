# Imports
import pyinputplus as pyip
import ttt_minimax_ai as ai

# Dimension Constants
BOARD_WIDTH = 3
BOARD_HEIGHT = 3

# Generate new 2D-Array Representing the Game Board
def board_init():
    return [
        [None, None, None],
        [None, None, None],
        [None, None, None]
    ]

# Display the Current Game
def display(board):
    print("\nCurrent Game Board. . .\n")
    print("     0   1   2  ")
    print("   -------------")
    for x, column in enumerate(board):
        print(x, " | ", end='')
        for val in column:
            if val == None:
                print("  | ", end='')
            else:
                print(val, "| ", end='')
        print("\n   -------------")

# Get Move
def get_move(board, current_player_id, player_name):
    
    # Determine if the Player is the Human or the AI
    if player_name == "Human":
        x = pyip.inputInt("\nWhat is the X co-ordinate of your move?: ", min=0, max=2)
        y = pyip.inputInt("What is the Y co-ordinate of your move?: ", min=0, max=2)
        return (y, x)
    elif player_name == "AI":
        return ai.minimax_ai(board, current_player_id)

# Make Player Move
def make_move(board, move_coords, player):
    if move_coords is not None:
        if board[move_coords[0]][move_coords[1]] is not None:
            raise Exception("Illegal Move")   
        board[move_coords[0]][move_coords[1]] = player

# Check for the winner of the game
def check_winner(board):
    
    possible_lines = [
        # Rows
        [(0,0), (0,1), (0,2)],
        [(1,0), (1,1), (1,2)],
        [(2,0), (2,1), (2,2)],
        
        # Columns
        [(0,0), (1,0), (2,0)],
        [(0,1), (1,1), (2,1)],
        [(0,2), (1,2), (2,2)],

        # Diagonals
        [(0, 0), (1, 1), (2, 2)],
        [(0, 2), (1, 1), (2, 0)]       
    ]

    for line in possible_lines:
        line_values = [board[x][y] for (x, y) in line]
        if line_values.count("X") == 3:
            return "X"
        elif line_values.count("O") == 3:
            return "O"
        
    return None
        

# Determine if the board is full
def full_board(board):
    
    # Board is Full til Otherwise
    isFull = True
    # Iterate through Values
    for row in board:
        for val in row:
            # Board is not Full if a Value = None
            if val == None:
                isFull = False
    return isFull

    
# Play the Game
def play(player_name_1, player_name_2):
    # Initialize New Board
    board = board_init()
    
    # Introduction
    print("Tic Tac Toe vs AI. . .\n\tPlayer is X and AI is O")

    # Necessary Variables
    players = [
        ('X', player_name_1),
        ('O', player_name_2)
    ]
    
    turn = 0
    while True:
        
        # Check if there is a Winner
        winner = check_winner(board)
        
        if winner is not None:
            display(board)
            print("\nThe Winner is ", winner, "!!!", sep='')
            pause = input()
            break

        # Check if the Board is Full
        if full_board(board):
            display(board)
            print("\nThe Game is a Draw!!!")
            pause = input()
            break
        
        # Determine who's turn it is
        current_player_id, current_player_name = players[turn % 2]
        display(board)

        # Get the Move from the User
        move = get_move(board, current_player_id, current_player_name)
        make_move(board, move, current_player_id)
        print(board)

        # Increment the Round
        turn += 1
