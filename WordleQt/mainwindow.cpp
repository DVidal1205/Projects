#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Game.h"
#include<QApplication>
#include<QMessageBox>

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup the UI, and Declare and Initialize the new Wordle Game
    ui->setupUi(this);
    wordle = new Game(ui);
    wordle->initialize();

    // Base Case
    has_won = false;
}


// Destructor
MainWindow::~MainWindow()
{
    // Free the ui and game pointers
    delete ui;
    delete wordle;
}


// Slot for Inputted Text and Return Pressed
void MainWindow::on_guessInput_returnPressed()
{
    // Grabs the inputted text as a QString of all caps
    QString guess = ui->guessInput->text();
    guess = guess.toUpper();

    // Ensure the game is not won or over, and validate test length
    if ((has_won != true) && (wordle->get_tries() != 6) && guess.size() == 5){
        // If the game is not over, make the guess and check if this guess was the winning guess
        wordle->make_guess(guess);
        has_won = wordle->check_win();

        // If the User has won...
        if (has_won){
            // Reset the Text Line
            ui->guessInput->setText("");

            // Congratulate the User
            QMessageBox::information(0, "Congratulations!", "You have guessed the correct word! Press Enter to play again. . .");

            // Delete previous game and allocate a new one
            delete wordle;
            wordle = nullptr;
            wordle = new Game(ui);
            has_won = false;
            wordle->initialize();
        }
        // If the User has not won, check if this means they exceeded six tries
        else{
            wordle->increment_turn();
            if (wordle->get_tries() >= 6){
                // Reset the Text Line
                ui->guessInput->setText("");

                // Prompt the User to try again, and reveal the word
                QMessageBox::information(0, "Aww, you ran out of tries.", QString("The word was %1! Hope you win next time!").arg(wordle->get_word()));

                // Delete previous game and allocate a new one
                delete wordle;
                wordle = nullptr;
                wordle = new Game(ui);
                has_won = false;
                wordle->initialize();
            }
        }
        // Reset the Text Line
        ui->guessInput->setText("");
    }
    else{
        // Final case of the word length being incorrect, warn the user of their error and prompt again, leaving the line as is
        QMessageBox::information(0, "Error", "Please enter a word of length 5.");
    }
}


// Convert the displayed input line text to uppercase for consistency
void MainWindow::on_guessInput_textEdited(const QString &arg1)
{
    // Grab text in the line, capitalize it, and set it
    QString text = ui->guessInput->text();
    text = text.toUpper();
    ui->guessInput->setText(text);
}
