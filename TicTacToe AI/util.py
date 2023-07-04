# Quality of Life Function to Return Opponent
def my_opponent(player):
    if player == 'X':
        return 'O'
    elif player == 'O':
        return 'X'
    else:
        raise Exception("Unknown Player")

# Generate the Coordinates for all Legal Moves on the Board
def all_legal_moves(board):
    legal_moves = []
    for y, column in enumerate(board):
        for x, val in enumerate(column):
            if val is None:
                legal_moves.append((y, x))
    return legal_moves