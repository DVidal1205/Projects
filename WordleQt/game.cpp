#include"Game.h"
#include<random>
#include<iostream>
#include<ctime>
#include<QApplication>
#include<QString>
#include<QChar>
#include<QWidget>
#include<QLabel>
#include<QTextStream>
#include<QFile>
#include<QMessageBox>
#define GREEN "QLabel { background-color : rgba(106,170,100,255); color: white; border-style: solid; border-width: 1.5px; border-color: rgba(106,170,100,255); font-size: 45px;}"
#define YELLOW "QLabel { background-color : rgba(201,180,88,255); color: white; border-style: solid; border-width: 1.5px; border-color: rgba(201,180,88,255); font-size: 45px;}"
#define WHITE "QLabel { background-color : white; color: black; border-style: solid; border-width: 1.5px; font-size: 45px;}"
#define GRAY "QLabel { background-color : rgba(120,124,126,255); color: white; border-style: solid; border-width: 1.5px; border-color: rgba(120,124,126,255); font-size: 45px;}"

// Current Try Static Int
int Game::current_try = 0;


// Constructor Function that Allocates the 2D Array
Game::Game(Ui::MainWindow *window){

    // Grab the Main Window for the Object
    UI = window;

    // Create Label Grid
    labels = new QLabel**[6];
    for (int i = 0; i < 6; i++){
        labels[i] = new QLabel*[5];
    }

    // Reset Labels if a Previous Game has Ran
    UI->label0_0->setStyleSheet(WHITE);
    UI->label0_1->setStyleSheet(WHITE);
    UI->label0_2->setStyleSheet(WHITE);
    UI->label0_3->setStyleSheet(WHITE);
    UI->label0_4->setStyleSheet(WHITE);
    UI->label1_0->setStyleSheet(WHITE);
    UI->label1_1->setStyleSheet(WHITE);
    UI->label1_2->setStyleSheet(WHITE);
    UI->label1_3->setStyleSheet(WHITE);
    UI->label1_4->setStyleSheet(WHITE);
    UI->label2_0->setStyleSheet(WHITE);
    UI->label2_1->setStyleSheet(WHITE);
    UI->label2_2->setStyleSheet(WHITE);
    UI->label2_3->setStyleSheet(WHITE);
    UI->label2_4->setStyleSheet(WHITE);
    UI->label3_0->setStyleSheet(WHITE);
    UI->label3_1->setStyleSheet(WHITE);
    UI->label3_2->setStyleSheet(WHITE);
    UI->label3_3->setStyleSheet(WHITE);
    UI->label3_4->setStyleSheet(WHITE);
    UI->label4_0->setStyleSheet(WHITE);
    UI->label4_1->setStyleSheet(WHITE);
    UI->label4_2->setStyleSheet(WHITE);
    UI->label4_3->setStyleSheet(WHITE);
    UI->label4_4->setStyleSheet(WHITE);
    UI->label5_0->setStyleSheet(WHITE);
    UI->label5_1->setStyleSheet(WHITE);
    UI->label5_2->setStyleSheet(WHITE);
    UI->label5_3->setStyleSheet(WHITE);
    UI->label5_4->setStyleSheet(WHITE);

    // Reset Text
    UI->label0_0->setText(" ");
    UI->label0_1->setText(" ");
    UI->label0_2->setText(" ");
    UI->label0_3->setText(" ");
    UI->label0_4->setText(" ");
    UI->label1_0->setText(" ");
    UI->label1_1->setText(" ");
    UI->label1_2->setText(" ");
    UI->label1_3->setText(" ");
    UI->label1_4->setText(" ");
    UI->label2_0->setText(" ");
    UI->label2_1->setText(" ");
    UI->label2_2->setText(" ");
    UI->label2_3->setText(" ");
    UI->label2_4->setText(" ");
    UI->label3_0->setText(" ");
    UI->label3_1->setText(" ");
    UI->label3_2->setText(" ");
    UI->label3_3->setText(" ");
    UI->label3_4->setText(" ");
    UI->label4_0->setText(" ");
    UI->label4_1->setText(" ");
    UI->label4_2->setText(" ");
    UI->label4_3->setText(" ");
    UI->label4_4->setText(" ");
    UI->label5_0->setText(" ");
    UI->label5_1->setText(" ");
    UI->label5_2->setText(" ");
    UI->label5_3->setText(" ");
    UI->label5_4->setText(" ");

    // Allocate 2d Array
    game_grid = new QChar*[6];
    for (int i=0; i < 6; i++){
        game_grid[i] = new QChar[5];
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

    // Reset Style Sheets
    // Populate Grid
    labels[0][0] = UI->label0_0;
    labels[0][1] = UI->label0_1;
    labels[0][2] = UI->label0_2;
    labels[0][3] = UI->label0_3;
    labels[0][4] = UI->label0_4;
    labels[1][0] = UI->label1_0;
    labels[1][1] = UI->label1_1;
    labels[1][2] = UI->label1_2;
    labels[1][3] = UI->label1_3;
    labels[1][4] = UI->label1_4;
    labels[2][0] = UI->label2_0;
    labels[2][1] = UI->label2_1;
    labels[2][2] = UI->label2_2;
    labels[2][3] = UI->label2_3;
    labels[2][4] = UI->label2_4;
    labels[3][0] = UI->label3_0;
    labels[3][1] = UI->label3_1;
    labels[3][2] = UI->label3_2;
    labels[3][3] = UI->label3_3;
    labels[3][4] = UI->label3_4;
    labels[4][0] = UI->label4_0;
    labels[4][1] = UI->label4_1;
    labels[4][2] = UI->label4_2;
    labels[4][3] = UI->label4_3;
    labels[4][4] = UI->label4_4;
    labels[5][0] = UI->label5_0;
    labels[5][1] = UI->label5_1;
    labels[5][2] = UI->label5_2;
    labels[5][3] = UI->label5_3;
    labels[5][4] = UI->label5_4;

    // Get a Random Word for the Game
    srand(time(0));
    int word_position = ((rand() % 5758) * sizeof("pupal\n"));
    QFile words_file("C:/Users/jammi/Documents/WordleQt/fiveLetterWords.txt");

    // Throwing an Exception
    if (!words_file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0, "error", words_file.errorString());
    }

    // Reading Random Word Into Array
    else{

        // Move Read Position to Random Word
        words_file.seek((word_position));

        QTextStream in(&words_file);
        QString random_word = in.readLine();
        random_word = random_word.toUpper();
        qDebug() << "random_word: " << random_word;
        if(random_word.length() == 5){
            for(int i = 0; i < 5; i++){
                if(i < random_word.length())
                    word[i] = random_word[i];
            }
        }
    }
    // Close the File
    words_file.close();
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
void Game::make_guess(QString guess){
    // Update the grid to account for the guess to be used in displaying the game
    for (int i = 0; i < guess.size(); i++){
        game_grid[current_try][i] = QChar(guess.at(i).toLatin1());
    }
    // Display the Game
    disp_game();
}


// Check if the user has won, if so, return true
bool Game::check_win(){
    // Base Case
    bool correct_word = true;
    for (int i = 0; i < 5; i++){
        
        // True to False if not Matched
        if (game_grid[current_try][i] != word.at(i)){
            correct_word = false;
        }
    }

    // Return the win state
    return correct_word;
}


// Display the Game Grid in the Proper Colors
void Game::disp_game(){
    
    // Display the Grid
    int row = current_try;
    for (int g_letter = 0; g_letter < 5; g_letter++){

        // Update Text Regardless, and make it Gray unless Otherwise Updates
        labels[row][g_letter]->setText(game_grid[row][g_letter]);
        labels[row][g_letter]->setStyleSheet(GRAY);

        // Base Case
        bool is_yellow = false;

        // Determine Green
        if (game_grid[row][g_letter] == word[g_letter]){
            labels[row][g_letter]->setStyleSheet(GREEN);
        }

        // Determine Yellow
        else{

            // Starting condition
            for (int w_letter = 0; w_letter < 5; w_letter++){
                if (game_grid[row][g_letter] == word[w_letter]){
                    is_yellow = true;
                }
            }
            // Change Style to Yellow
            if (is_yellow){
                labels[row][g_letter]->setStyleSheet(YELLOW);
            }
        }
    }
}


// Word Accessor Method
QString Game::get_word(){
    return word;
}


// Destructor Function that Deallocates the 2D Array
Game::~Game(){
    
    // Delete Game Board
    for (int i = 0; i < 6; i++){
        delete game_grid[i];
    }
    delete[] game_grid;

    // Delete Label Grid
    for (int i = 0; i < 6; i++){
        delete labels[i];
    }
    delete[] labels;

    // Remove Reference to Board
    UI = nullptr;

    // Reset Current Try
    current_try = 0;
}



