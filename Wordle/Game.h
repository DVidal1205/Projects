/*
    
    filename: Game.h
    authors: Dylan Vidal, Jacob Ward, and Fabio Velasquez
    COP2335C

    Header file for the Game class for wordleRPG.cpp.

*/
#ifndef GAME_H
#define GAME_H
#include<fstream>
#include<string>
using namespace std;
class Game{
    private:
        static int current_try;
        char **game_grid = nullptr;
        char word[5];
        ifstream words_file;
        string filename = "fiveLetterWords";
        bool has_won = false;

    public:
        Game();
        void initialize();
        char *get_word();
        int get_tries();
        void make_guess(char guess[5]);
        bool check_win();
        void disp_game();
        void increment_turn();
        void save_game(int);
        static void display_save();
        ~Game();
};
#endif