/*
    
    filename: Game.cpp
    authors: Dylan Vidal, Jacob Ward, and Fabio Velasquez
    COP2335C

    Implementation file for the Game class for wordleRPG.cpp.
    
*/
#include"Game.h"
#include<random>
#include<iostream>
#include<ctime>
#include<windows.h>

// Current Try Static Int
int Game::current_try = 0;
const int GREEN = 0x2F, YELLOW = 0x6F, GRAY = 0x8F, RESET = 0x07;
const HANDLE COUT_H = GetStdHandle(STD_OUTPUT_HANDLE);

// Constructor Function that Allocates the 2D Array
Game::Game(){
    
    // Allocate 2d Array
    game_grid = new char*[6];
    for (int i=0; i < 6; i++){
        game_grid[i] = new char[5];
    }

    // Populate 2d Array With Empty Grid
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 5; j++){
            game_grid[i][j] = ' ';
        }
    }
}

// Open the fiveLetterWords.txt file and load a random word into the 2D array
void Game::initialize(){

    // New Game, reset Static Int
    current_try = 0;

    // Get a Random Word for the Game
    srand(time(0));
    int word_position = ((rand() % 5758) * sizeof("pupal\n"));
    words_file.open("fiveLetterWords.txt", ios::in);
    
    // Throwing an Exception
    if (!words_file){
        string fileException = "ERROR. . . fiveLetterWords.txt not found. . .\n";
        throw fileException;
    }

    // Reading Random Word Into Array
    else{

        // Move Read Position to Random Word
        words_file.seekg((word_position), ios::beg);
        
        // Read the line and convert to C-string
        string random_word;
        getline(words_file, random_word);
        for(int i = 0; i < 5; i++){
            word[i] = random_word[i];
        }
    }
}

// Accessor Method
int Game::get_tries(){
    return current_try;
}

// Mutator Method
void Game::increment_turn(){
    current_try++;
}

// Add the inputted guess into the 2D array
void Game::make_guess(char guess[5]){
    for (int i = 0; i < 5; i++){
        game_grid[current_try][i] = guess[i];
    }
}

// Check if the user has won, if so, return true
bool Game::check_win(){
    // Start Case
    bool correct_word = true;
    for (int i = 0; i < 5; i++){
        
        // True to False if not Matched
        if (game_grid[current_try][i] != word[i]){
            correct_word = false;
        }
    }
    return correct_word;
}

// Display the Game Grid in the Proper Colors
void Game::disp_game(){
    
    // Display the Grid
    cout << "---------------------\n";
    for (int row = 0; row < 6; row++){
        cout << "|";
        for (int g_letter = 0; g_letter < 5; g_letter++){
            bool is_green = false;
            bool is_yellow = false;
            // Determine Green
            if (game_grid[row][g_letter] == word[g_letter]){
                is_green = true;
                SetConsoleTextAttribute(COUT_H, GREEN);
                cout << ' ' << game_grid[row][g_letter] << ' ';
                SetConsoleTextAttribute(COUT_H, RESET);
            }

            // Determine Yellow
            else{

                // Starting condition
                for (int w_letter = 0; w_letter < 5; w_letter++){
                    if (game_grid[row][g_letter] == word[w_letter]){
                        is_yellow = true;
                    }
                }
                if (is_yellow){
                    SetConsoleTextAttribute(COUT_H, YELLOW);
                    cout << ' ' << game_grid[row][g_letter] << ' ';
                    SetConsoleTextAttribute(COUT_H, RESET);
                }
            }

            // Determine Gray
            if (!is_green && !is_yellow){
                SetConsoleTextAttribute(COUT_H, GRAY);
                cout << ' ' << game_grid[row][g_letter] << ' ';
                SetConsoleTextAttribute(COUT_H, RESET);
            }

            cout << "|";
        }
        cout << endl << "---------------------" << endl;
    }
}

// Return the Word as a Character Array Pointer (For Error Testing in Main)
char* Game::get_word(){
    char *word_ptr = word;
    return word_ptr;
}

// Destructor Function that Deallocates the 2D Array
Game::~Game(){
    
    // Delete Game Board
    for (int i = 0; i < 6; i++){
        delete[] game_grid[i];
    }
    delete[] game_grid;
}

// Function to Save the Game to a text File Named Scores.txt
void Game::save_game(int x) 
{
    fstream score;
    score.open("score.txt", fstream::app);
    if (!score)
        cout << "No scores found, creating one...";
        score << "Wordle Game Records. . .\n";
    for (int i = 0; i < 5; i++){
        score << word[i];
    }
    if (x == 0){
        score << ": Lost\n";
    }
    else{
        score << ": Won in (" << x << "/6) Rounds\n";        
    }
    score.close();
}

// Function to Display the Game from Scores.txt
void Game::display_save() 
{
    string contents;
    ifstream score("score.txt");
    if (!score)
        cout << "Error. . . no scores found to display! You must be the first player on this device, Good Luck!\n";
    if (score.is_open())
    {
        while (!score.eof())
        {
            getline(score, contents);
            cout << contents << endl;
        }
    }
    score.close();
}