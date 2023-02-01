#
# Filename:vingEtUn.py
# Date: December 1st, 2022
# Authors: Dylan Vidal
# 
# Program Description: A menu driven program that will ask the user for their name so it can be written down in the history file after the game ends. Then, the program will prompt
# the user whether to roll the dice, or stay. If staying, it ends their turn then the computer "House" will keep rolling the dice until it reaches 17 points or higher. 
# the program will end when both players have stayed, or one of them has gotten over 21 points and busted.
# 
# Input: Player name
#
# Processing: 1. Program prompts user for their name
#             2. Program starts the round
#             3. Program prompts user whether to roll or stay
#             4. If staying, it ends their turn
#             5. If rolling, it will roll the dice
#             6. If score is over 21, they lose the round
#             7. After their turn is over, it's the computer(House)'s turn
#             8. When both players' turn is over or both chose to stay, the game ends and the winner is written to a history file
#
# Output: Displays the winner of the game
#

import datetime
import random

# Must be installed by running "install --user pyinputplus" into the command prompt
import pyinputplus as pyip

ROLL_ONE_DICE = 14
FORCE_STAY = 17
FULL_HAND = 21
MAX_TRIES = 5

# Main Function
def main():

    # Introduce the Program
    print("\nWelcome to the Ving-Et-Un Dice Game. . .")
    menu_choice = 0

    # Run until the user wants to Quit
    while (menu_choice != 4):
        menu_choice = show_menu()
        menu_choice = int(input('Enter Your Selection (1-4) '))
        if (menu_choice == 1):
            show_rules()
        elif (menu_choice == 2):
            play_game()
        elif (menu_choice == 3):
            show_history()
        elif (menu_choice == 4):
            goodbye()

# Player must enter a number to prompt the next action.
def show_menu():
    
    print('\n~ Game Menu ~')
    print('================================')
    print('1: Show Rules')
    print('2: Play Game')
    print('3: Show History')
    print('4: Quit')
    print('================================')
            

# This function shows the rules of the game.
def show_rules():
    print("\nHere are the rules of the game...")
    print("-" * 11)
    print("1. Whichever player's total is nearest to 21 points, wins.")
    print("2. Whichever player's total is over 21 points, loses the game.")
    print("3. If both players' total are equal to one another, its declared a draw and the game is over.")
    print("4. Two dies are played at the beginning of the round, when a player goes above 14 points, one dice is discarded.")
    print("5. Your turn ends when you choose to stay after you're prompted to stay or roll the dice.")
    print("6. The computer will forcefully choose to stay when reaching 17 points or higher.")

# Play Game Function
def play_game():
    player_total = 0
    house_total = 0
    current_round = 1
    player_bust = False
    house_bust = False
    player_stay = False
    roll_choice = 'y'

    # Gather user and game info
    player_name = str(input("Before we begin, please input your name: "))
    game_date = game_date = datetime.datetime.now()

    # While loop until the game finishes
    while (((player_bust != True) and (player_stay != True)) and (house_bust != True)):
        
        # Introduce the round
        print("\nRound ", current_round, ":", sep='')
        print("Your current total is", player_total)
        print("The houses's current total is", house_total)
        
        # If the player is still in, roll appropriate dice
        if not (player_total > FULL_HAND):
            roll_choice = pyip.inputYesNo("Would you like to roll? (y/n): ", yesVal='y', noVal='n')
            if (roll_choice.lower() == 'n'):
                player_stay = True
        if ((player_bust != True) and (player_stay != True)):       
            if (player_total > FULL_HAND):
                player_bust = True
                print("\nYou have totaled over 21 and have busted")
            elif (player_total < ROLL_ONE_DICE):
                player_total += two_dice()
            elif (player_total >= ROLL_ONE_DICE and player_total <= FULL_HAND):
                player_total += one_dice()


        # If the house has not busted, roll appropriate dice
        if ((house_bust != True)):
            if (house_total > FULL_HAND):
                house_bust = True
                print("\nThe house has totaled over 21 and has busted")
            elif (house_total < ROLL_ONE_DICE):
                house_total += two_dice()
            elif (house_total >= ROLL_ONE_DICE and house_total <= 17):
                house_total += one_dice()

        # Up the round before the next loop
        current_round += 1

    print("\nEnd of round\n")
    print("Player Final Total:", player_total)
    print("House Final Total", house_total)

    
    # Determine the winner once the round is over
    player_difference = FULL_HAND - player_total
    house_difference = FULL_HAND - house_total
    if (player_bust == True and house_bust == True):
        if (player_difference < house_difference):
            winner = player_name
        elif (player_difference == house_difference):
            winner = "Draw"
        else:
            winner = "House"
    elif (player_bust == True and house_bust == False):
        winner = "House"
    elif (player_bust == False and house_bust == True):
        winner = player_name
    elif (player_bust == False and house_bust == False):
        if (player_difference < house_difference):
            winner = player_name
        elif (player_difference == house_difference):
            winner = "Draw"
        else:
            winner = "House"
    print("Winner:", winner)

    # Write the results to the file
    history = open("history.txt","a+")
    history.write("Player Name: ")
    history.write(str(player_name) + "\n")
    history.write("Game Date: ")
    history.write(str(game_date) + "\n")
    history.write("Winner: ")
    history.write(str(winner) + "\n")
    history.close()
    
#This Function will display the game history to the player
def show_history():
    print('\n~ VingEtUn Game History ~')
    print('================================')
    try:
        history = open("history.txt","r")
        contents = history.read()
        print(contents)
        history.close()
    except:
        print('Error Reading File')
    print('================================')

# Roll Two Dice Function
def two_dice():
    
    # Roll two dice by getting 2 random integers 1-6
    roll1 = random.randint(1,6)
    roll2 = random.randint(1,6)

    # Add together and return to the function
    rolled_total = roll1 + roll2
    return rolled_total

# Roll One Dice Function
def one_dice():

    # Roll one dice by getting 1 random integer 1-6
    roll1 = random.randint(1,6)

    # Add together and return to the function
    rolled_total = roll1
    return rolled_total

#This Function will call when player input is invalid and player prompts to end game.
def goodbye():

    print("\n ▣ Thank you for playing ▣ ")
    print('~ Ving-Et-Un Dice Game ~')
    print('================================')
    print('~ Good-Bye! ~\n')
    
main()