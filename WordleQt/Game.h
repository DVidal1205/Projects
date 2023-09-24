#ifndef GAME_H
#define GAME_H
#include "./ui_mainwindow.h"
#include<fstream>
#include<string>
#include<QApplication>
#include<QMainWindow>
#include<QChar>
#include<QWidget>

using namespace std;
class Game{
    private:
        static int current_try;
        Ui::MainWindow *UI;
        QChar **game_grid = nullptr;
        QString word = "     ";
        ifstream words_file;
        string filename = "fiveLetterWords";
        bool has_won = false;
        QLabel ***labels;

    public:
        Game(Ui::MainWindow *window);
        void initialize();
        QString get_word();
        int get_tries();
        void make_guess(QString guess);
        bool check_win();
        void disp_game();
        void increment_turn();
        ~Game();
};
#endif
