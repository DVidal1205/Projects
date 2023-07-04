import tictactoe as ttt
import copy
import util

# Determine the Minimax Score Recursively
def get_minimax_score(board, minimizing_player, maximizing_player):
    
    # Determine if there is a Winner on this Game
    winner = ttt.check_winner(board)
    if winner is not None:

        # Return 10 points if the Winner is the AI
        if winner == maximizing_player: 
            return 10
        
        # Return -10 points if the Winner is Human
        else: 
            return -10
        
    # Return 0 points if the game is a drwa    
    elif ttt.full_board(board): 
        return 0

    # Gather all Legal Moves
    legal_moves = util.all_legal_moves(board)

    # Gather the best move, depending on minimizing or maximizing
    scores = []
    for move in legal_moves:

        # Create a copy of the board to iterate over recursively
        board_copy = copy.deepcopy(board)
        ttt.make_move(board_copy, move, minimizing_player)

        # Calculate the best score of the opponent recursively
        opponent = util.my_opponent(minimizing_player)
        opponenet_best_score = get_minimax_score(board_copy, opponent, maximizing_player)
        scores.append(opponenet_best_score)

    # Decide if minimizing or maximizing
    if minimizing_player == maximizing_player:
        return max(scores)
    else:
        return min(scores)

# Call all of the Minimax Scores and return the Greatest
def minimax_ai(board, player):
    best_move = None
    best_score = None

    winner = ttt.check_winner(board)
    if winner is None:
        # Iterate through all legal moves on the board and determine their minimax scres
        for move in util.all_legal_moves(board):
            board_copy = copy.deepcopy(board)
            ttt.make_move(board_copy, move, player)

            opponent = util.my_opponent(player)
            score = get_minimax_score(board_copy, opponent, player)
            if best_score is None or score > best_score:
                best_move = move
                best_score = score
        
    return best_move
