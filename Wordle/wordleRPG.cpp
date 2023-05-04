/*
    
    filename: wordleRPG.cpp
    authors: Dylan Vidal, Jacob Ward, and Fabio Velasquez
    COP2335C

    A menu driven program that emulates New York Time's word game Wordle, displays rules of the game, and creates/displays
    a text file keeping track of the scores of past local users. 

    Input: Menu Choice (1-4).

    Processing: 1. Display the menu, and gather the choice from the user.
                2. Using a switch statement, determine whether to show the rules, play the game, display the results, or quit.
                    1. Print the rules of the game to the user.
                    2. Start the game, initializing a Game object and running 6 rounds where the player guesses a word, and the grid and result are displayed.
                    3. Display the scores of past local users to the user.
                    4. Quit the game and break the menu driven loop.

    Output: Rules, Game, Records, or Quit Message 
    
*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<memory>
#include<windows.h>
#include"Game.cpp"
using namespace std;

// Function Prototypes
int menu();
void disp_rules();
void play();
void show_report();

// Constants
int const SEE_RULES = 1, PLAY_GAME = 2, PERFORMANCE_REPORT = 3, QUIT = 4, NUM_LETTERS = 5, NUM_TRIES = 6;

// Main Function
int main(){
    // Intro
    cout << endl << "Wordle Game. . ." << endl;

    // Menu Switch
    int choice = 0;
    do
    {
        // Get Menu Choice
        choice = menu();
        switch (choice)
        {
            // Display the Rules
            case SEE_RULES:
                disp_rules();
                break;

            // Play the Game
            case PLAY_GAME:
                play();
                break;

            // Display the Performance Report
            case PERFORMANCE_REPORT:
                show_report();
                break;

            // Quit Loop
            case QUIT:
                cout << "Thank you for playing our game. . . :)";
                break;

            // Input Validation
            default:
                cout << "Error. . . Please choose a valid menu option (1-4)";
                break;
        }
    } while (choice != QUIT);

}

// Display the Menu
int menu(){
    int choice;
    cout << endl << "Please choose one of the following options. . ." << endl
        << "\t1. Display the Rules of Wordle" << endl
        << "\t2. Play Wordle" << endl 
        << "\t3. Show the Game Records" << endl 
        << "\t4. Quit" << endl << "Choice: ";
    cin >> choice;
    cout << endl;
    return choice;
}

// Display the Rules
void disp_rules(){
    cout << "Rules of Wordle. . ." << endl
        << "\t1. A game of Wordle lasts 6 rounds" << endl 
        << "\t2. Each round, guess a five letter word" << endl
        << "\t\tA Green letter means the letter is in the word, and in the correct spot" << endl
        << "\t\tA Yellow letter means the letter is in the word, but in the incorrect spot" << endl
        << "\t\tA Gray letter means the letter is not in the word at all, regardless of position" << endl
        << "\t3. To win, guess the five letter Wordle by getting a fully green word." << endl;
}

// Play the Game
void play(){
    // Create a New Game
    Game wordle;
    int current_try = 1;
    bool has_won = false;
    string guess;
    char guess_cstring[NUM_LETTERS];

    // Initialize Game
    try
    {
        wordle.initialize();
        has_won = wordle.check_win();
    }
    catch(string exceptionString)
    {
        cout << exceptionString;
        return;
    }


/*
    char *word_ptr = nullptr;
    word_ptr = wordle.get_word();
    for (int i = 0; i < NUM_LETTERS; i++){
        cout << word_ptr[i];
    }
    cout << endl;
*/


    // Clear the buffer
    cin.ignore();

    // Game Loop
    while ((has_won == false) && (current_try < NUM_TRIES)){
        // Header
        current_try = wordle.get_tries() + 1;
        cout << "Round " << current_try << endl;

        // Get Word
        cout << "Please enter a five letter word: ";
        bool isTrue = true;
        
        // Validate Word
        while (isTrue){
            getline(cin, guess);
            
            // Validate Length
            while (guess.length() != 5){
                cout << "Invalid Input. Please try again: ";
                getline(cin, guess);
            }
           // Validate if the inputted word contains digits 
           if (guess.length() == 5){
                for (int i = 0; i < 5; i++)
                {
                    if (isdigit(guess[i])  || guess.length() != 5)
                    {
                        cout << "Invalid Input. Please try again: ";
                        getline(cin, guess);
                        i = 0;
                    }
                }
                isTrue = false;
            }
        }
        // Convert word to Cstring
        for (int i = 0; i < NUM_LETTERS; i++){
            guess_cstring[i] = guess[i];
        }

        // Make the Guess
        wordle.make_guess(guess_cstring);

        // Display the Grid
        wordle.disp_game();

        // Check if won, then increment turn
        has_won = wordle.check_win();
        wordle.increment_turn();
        cout << endl;
    }

    // Congratulation Message and write the Word
    if (has_won){
        cout << "Magnificent! You have won in (" << current_try << "/6) tries!" << endl; 
        wordle.save_game(current_try);
    }

    // Reveal the Word
    else{
        cout << "The word was: ";
        char *word_ptr = nullptr;
        word_ptr = wordle.get_word();
        for (int i = 0; i < NUM_LETTERS; i++){
            cout << word_ptr[i];
        }
        cout << endl << "Try again next time. . ." << endl;
        wordle.save_game(0);
    }
}

// Displays the text file with the past games and scores
void show_report()
{
    Game::display_save();
}