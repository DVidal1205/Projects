/*

    name: Dylan Vidal
    filename: CactPot.cpp
    
    A menu-driven program that prompts the user to: 1. See the Rules, 
    2. Play The Game, 3. See Highest Gold Point Score, or 4. Quit.
    On a choice of 2, generate a 3x3 slots ticket and let the user reveal numbers,
    pick a line, and get a total point score.

    Input: Prompt user for the menu choice

    Processing: 1. Display menu and menu choices
                2. Prompt the user for a choice
                    Case 1 - Show rules
                        - Display a typed out summary of the game and its rules
                    Case 2 - Play the Game
                        - Reveal a random cell
                        - Let the user select three other cells
                        - Select a line to add up
                        - Calculate the score from the scores chart
                        - Determine if the score is a high score, then write it to highScores.txt
                    Case 3 - See Highest Gold Point Score
                        - Read from highScore.txt and display the current high score
                    Case 4 - Quit
                        - Terminate the program after displaying a goodbye message

    Output: Display CactPot lottery game for the user

*/

// Preprocessor Directions
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cmath>
#include<random>
#include<algorithm>
#include<ctime>
using namespace std;

// Menu Choice Global Constants
int const SHOW_RULES_CHOICE = 1, PLAY_GAME_CHOICE = 2, SEE_HIGH_SCORE_CHOICE = 3, QUIT_CHOICE = 4;

// Array Constants
int const NUM_ROWS = 3, NUM_COLUMNS = 3, NUM_PICKS = 3;

// Point Sum Conversion Constants
int const SUM_SIX = 10000, SUM_SEVEN = 36, SUM_EIGHT = 720, SUM_NINE = 360, SUM_TEN = 80, SUM_ELEVEN = 252,
            SUM_TWELVE = 108, SUM_THIRTEEN = 72, SUM_FOURTEEN = 54, SUM_FIFTEEN = 180, SUM_SIXTEEN = 72, SUM_SEVENTEEN = 180,
            SUM_EIGHTEEN = 119, SUM_NINETEEN = 36, SUM_TWENTY = 306, SUM_TWENTY_ONE = 1080, SUM_TWENTY_TWO = 144, 
            SUM_TWENTY_THREE = 1800, SUM_TWENTY_FOUR = 3600;

// Line Choice Constants
int const TOP_ROW = 1, MIDDLE_ROW = 2, BOTTOM_ROW = 3, DIAGONAL_TOP_LEFT = 4, LEFT_COLUMN = 5, MIDDLE_COLUMN = 6, RIGHT_COLUMN = 7, DIAGONAL_TOP_RIGHT = 8;

// High Score Filename
string const HIGH_SCORE_FILE_NAME = "highScores.txt";

// Square Choice
int const SQUARE_ONE = 1, SQUARE_TWO = 2, SQUARE_THREE = 3, SQUARE_FOUR = 4, SQUARE_FIVE = 5, SQUARE_SIX = 6, SQUARE_SEVEN = 7, SQUARE_EIGHT = 8, SQUARE_NINE = 9;

/*
    Square choice conversions

    Square 1 = [0][0]   Square 2 = [0][1]   Square 3 = [0][2]

    Square 4 = [1][0]   Square 5 = [1][1]   Square 6 = [1][2]

    Square 7 = [2][0]   Square 8 = [2][1]   Square 9 = [2][2]

*/

// Function Prototypes
int displayMenu();
void seeRules();
void playGame();
void displayHighScore(string);
void goodbye();
void getInfo(string&, string&);
void generateTicket(int[][NUM_COLUMNS]);
void revealSquare(int[][NUM_COLUMNS], int[][NUM_COLUMNS], int);
int pickSquare(int[][NUM_COLUMNS], int[][NUM_COLUMNS], int);
void showGame(int[][NUM_COLUMNS]);
int selectLine();
void revealFullGame(int[][NUM_COLUMNS], int[][NUM_COLUMNS]);
int calcLineSum(int, int[][NUM_COLUMNS]);
int calcPoints(int);
void determineHighScore(int, string, string, string);


int main()
{
    int menuChoice;

    // Intro Message
    cout << endl << "Welcome to the CactPot Lottery Game. . ." << endl;
    
    // Play til Quit Loop
    do
    {
        // Display Menu and Get user choice
        menuChoice = displayMenu();

        // Switch decision structure
        switch (menuChoice)
        {
            // Show the Rules
            case SHOW_RULES_CHOICE:
                seeRules();
                break;

            // Play the Game
            case PLAY_GAME_CHOICE:
                playGame();
                break;

            // See High Score
            case SEE_HIGH_SCORE_CHOICE:
                displayHighScore(HIGH_SCORE_FILE_NAME);
                break;

            // Quit
            case QUIT_CHOICE:
                goodbye();
                break;

            // Input Validation
            default:
                cout << endl << "Error. . . Please enter a valid menu choice. . ." << endl << endl;
                break;
        }

    } while (menuChoice != 4);
    
    return 0;
    
}


// Display the menu to the user and return menuChoice to main switch function
int displayMenu()
{
    int menuChoice;

    cout << "\nChoose One Of The Following Option:" << endl
        << "\t1. See the Rules" << endl
        << "\t2. Play the Game" << endl
        << "\t3. See Highest Gold Point Score" <<endl
        << "\t4. Quit" << endl << endl
        << "Choice: ";
    cin >> menuChoice;

    return menuChoice;
}


// Display an easy-to-read summation of the game rules and how to play
void seeRules()
{
    cout << fixed << left << "\nHow to Play:" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << fixed << left << "1. After a random square is revealed, pick three others to display" << endl << endl;
    cout << fixed << left << "2. Once you have picked your three squares, choose a line to add up" << endl << endl;
    cout << fixed << left << "3. Your reward will be calculated based off the payout chart below" << endl << endl;
    cout << "\t\t\t\t\tPayout" << endl;
    cout << "Sum" << "\t\tGold Point Rewards" << "\t\tSum" << "\t\tGold Point Rewards" << endl;
    cout << "6" << "\t\t10,000" << "\t\t\t\t16" << "\t\t72" << endl;
    cout << "7" << "\t\t36" << "\t\t\t\t17" << "\t\t180" << endl;
    cout << "8" << "\t\t720" << "\t\t\t\t18" << "\t\t119" << endl;
    cout << "9" << "\t\t360" << "\t\t\t\t19" << "\t\t36" << endl;
    cout << "10" << "\t\t80" << "\t\t\t\t20" << "\t\t306" << endl;
    cout << "11" << "\t\t252" << "\t\t\t\t21" << "\t\t1,080" << endl;
    cout << "12" << "\t\t108" << "\t\t\t\t22" << "\t\t144" << endl;
    cout << "13" << "\t\t72" << "\t\t\t\t23" << "\t\t1,800" << endl;
    cout << "14" << "\t\t54" << "\t\t\t\t24" << "\t\t3,600" << endl;
    cout << "15" << "\t\t180" << "\t\t\t\t" << "\t\t" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}


// Play the game
void playGame()
{
    int revealedGame[NUM_ROWS][NUM_COLUMNS] = {{0,0,0}, {0,0,0}, {0,0,0}};
    int hiddenGame[NUM_ROWS][NUM_COLUMNS];
    int userPick, lineChoice, totalPoints, lineSum;
    string userName, gameDate;

    getInfo(userName, gameDate);
    cout << endl << "Generating randomized ticket. . ." << endl << endl;
    generateTicket(hiddenGame);

    srand(time(0));
    int randomFirstPick = rand() % 9 + 0; 
    revealSquare(revealedGame, hiddenGame, randomFirstPick);

    cout << "Please enter three squares to reveal (1-9)" << endl << endl;
    for (int pickCount = 0; pickCount < NUM_PICKS; pickCount++)
    {
        userPick = pickSquare(revealedGame, hiddenGame, pickCount);
        revealSquare(revealedGame, hiddenGame, userPick);
    }

    lineChoice = selectLine();

    revealFullGame(revealedGame, hiddenGame);
    lineSum = calcLineSum(lineChoice, revealedGame);
    totalPoints = calcPoints(lineSum);
    showGame(revealedGame);
    cout << "Your line added up to a total of " << lineSum << "." << endl; 
    cout << "You received a total of " << totalPoints << " points!" << endl << endl;

    determineHighScore(totalPoints, userName, gameDate, HIGH_SCORE_FILE_NAME);
    
}


// Open the filename from the function argument, read the score, name, and date, then display it to the user
void displayHighScore(string filename)
{
    fstream highScoreFile;
    highScoreFile.open(filename, ios::in);
    int highScore;
    string userName, gameDate;
    if (!highScoreFile)
        cout << endl << "There is no high score to read. . . You must be the first player!" << endl;
    else
    {
        highScoreFile >> highScore;
        highScoreFile.ignore();
        getline(highScoreFile, userName);
        getline(highScoreFile, gameDate);

        cout << endl << "----------------------" << endl << "The Current High Score:" << endl << endl
            << "Score: " << highScore << endl << "User Name: "
            << userName << endl << "Date of Game: " << gameDate << endl << "----------------------" << endl;

        highScoreFile.close();
    }
    
}


// Print a kind and nice goodbye message, and then call the exit() function
void goodbye()
{
    cout << endl << "Goodbye. . . " << endl << "Thank you for playing our game :)";
    exit(EXIT_SUCCESS);
}


// At the start of the game, gather the users name and the date of the game
void getInfo(string& userName, string& gameDate)
{
    cout << endl << "Before you begin, please enter your name and the date (xx/xx/xxxx) below" << endl
        << "\tName: ";
    cin.ignore();
    getline(cin, userName);
    cout << "\tDate: ";
    getline(cin, gameDate);
}


// Create an array of numbers 1-9, shuffle it, and assign all of its elements to each element in the 2x2 hidden game array
void generateTicket(int hiddenGame[][NUM_COLUMNS])
{
    int numCount = 0, randomNumbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    srand(time(0));
    random_shuffle(begin(randomNumbers), end(randomNumbers));

    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int column = 0; column < NUM_COLUMNS; column++)
        {
            hiddenGame[row][column] = randomNumbers[numCount];
            numCount++;
        }
    }
}


// Take the inputted square into a switch statement for which row and column it corresponds to, then set hidden game to revealed game in that element
void revealSquare(int revealedGame[][NUM_COLUMNS], int hiddenGame[][NUM_COLUMNS], int pickedSquare)
{
    switch(pickedSquare)
    {
        case SQUARE_ONE:
            revealedGame[0][0] = hiddenGame[0][0];
            break;

        case SQUARE_TWO:
            revealedGame[0][1] = hiddenGame[0][1];
            break;

        case SQUARE_THREE:
            revealedGame[0][2] = hiddenGame[0][2];
            break;

        case SQUARE_FOUR:
            revealedGame[1][0] = hiddenGame[1][0];
            break;

        case SQUARE_FIVE:
            revealedGame[1][1] = hiddenGame[1][1];
            break;

        case SQUARE_SIX:
            revealedGame[1][2] = hiddenGame[1][2];
            break;

        case SQUARE_SEVEN:
            revealedGame[2][0] = hiddenGame[2][0];
            break;

        case SQUARE_EIGHT:
            revealedGame[2][1] = hiddenGame[2][1];
            break;

        case SQUARE_NINE:
            revealedGame[2][2] = hiddenGame[2][2];
            break;
    }
    showGame(revealedGame);
}


// Prompt the user for a square, validating the range of 1-9. Then, use a switch statement to determine which element the square is. Check if that element == 0 in revealed game, or reprompt for a non-repeat value
int pickSquare(int revealedGame[][NUM_COLUMNS], int hiddenGame[][NUM_COLUMNS], int pickCount)
{
    int pickedSquare;
    bool isRepeat;
    
    cout << "Pick " << pickCount + 1 <<  ": ";
    cin >> pickedSquare;

    while (pickedSquare < 1 || pickedSquare > 9)
    {
        cout << endl << "Error. . . Please enter a valid square choice (1-9)" << endl << endl
            << "Pick " << pickCount + 1 << ": ";
        cin >> pickedSquare;
    }

    do
    {
        switch (pickedSquare)
        {
            case 1:
                if (revealedGame[0][0] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;

            case 2:
                if (revealedGame[0][1] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;

            case 3:
                if (revealedGame[0][2] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;
            
            case 4:
                if (revealedGame[1][0] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;

            case 5:
                if (revealedGame[1][1] != 0)
                    isRepeat = true;
                break;

            case 6:
                if (revealedGame[1][2] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;
            
            case 7:
                if(revealedGame[2][0] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;

            case 8:
                if (revealedGame[2][1] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;

            case 9:
                if (revealedGame[2][2] != 0)
                    isRepeat = true;
                else
                    isRepeat = false;
                break;
        }

        if (isRepeat)
        {
            cout << endl << "Error. . . Please enter a square that has not been revealed already. . ." << endl
                << endl << "Pick " << pickCount + 1 << ": ";
            cin >> pickedSquare;

            while (pickedSquare < 1 || pickedSquare > 9)
                {
                    cout << endl << "Error. . . Please enter a valid square choice (1-9)" << endl
                        << "Pick " << pickCount + 1 << ": ";
                    cin >> pickedSquare;
                }            
        }
        
    } while (isRepeat);
    
    return pickedSquare;
}


// Use a for statement to format and print revealedGame
void showGame(int revealedGame[][NUM_COLUMNS])
{
    cout << "-------------------" << endl
            << "|  " << revealedGame[0][0] << "  |  " << revealedGame[0][1] << "  |  " << revealedGame[0][2] << "  |" << endl 
            << "-------------------" << endl
            << "|  " << revealedGame[1][0] << "  |  " << revealedGame[1][1] << "  |  " << revealedGame[1][2] << "  |" << endl 
            << "-------------------" << endl
            << "|  " << revealedGame[2][0] << "  |  " << revealedGame[2][1] << "  |  " << revealedGame[2][2] << "  |" << endl 
            << "-------------------" << endl << endl;
}


// Prompt the user for a line choice, and describe what each number corresponds to (ex. Row 1 (1), Row 2 (2), Row 3 (3), Column 1 (4), Column (5)....). Make sure to reject values out of range
int selectLine()
{
    int lineChoice;
    cout << "Now, select a line to sum and calculate your total" << endl 
        << "\t1. Row 1" << endl << "\t2. Row 2" << endl << "\t3. Row 3" << endl
        << "\t4. Column 1" << endl << "\t5. Column 2" << endl << "\t6. Column 3" << endl
        << "\t7. Diagonal top left to bottom right" << endl << "\t8. Diagonal top right to bottom left"
        << endl << "A reminder of the Payout Rewards Chart. . ." << endl << endl; 
    cout << "----------------------------------------------------------------------------------" << endl << "\t\t\t\t\tPayout" << endl;
    cout << "Sum" << "\t\tGold Point Rewards" << "\t\tSum" << "\t\tGold Point Rewards" << endl;
    cout << "6" << "\t\t10,000" << "\t\t\t\t16" << "\t\t72" << endl;
    cout << "7" << "\t\t36" << "\t\t\t\t17" << "\t\t180" << endl;
    cout << "8" << "\t\t720" << "\t\t\t\t18" << "\t\t119" << endl;
    cout << "9" << "\t\t360" << "\t\t\t\t19" << "\t\t36" << endl;
    cout << "10" << "\t\t80" << "\t\t\t\t20" << "\t\t306" << endl;
    cout << "11" << "\t\t252" << "\t\t\t\t21" << "\t\t1,080" << endl;
    cout << "12" << "\t\t108" << "\t\t\t\t22" << "\t\t144" << endl;
    cout << "13" << "\t\t72" << "\t\t\t\t23" << "\t\t1,800" << endl;
    cout << "14" << "\t\t54" << "\t\t\t\t24" << "\t\t3,600" << endl;
    cout << "15" << "\t\t180" << "\t\t\t\t" << "\t\t" << endl;
    cout << "----------------------------------------------------------------------------------";
    cout << endl << endl << "Please enter your line choice: ";
    cin >> lineChoice;
    while (lineChoice < 1 || lineChoice > 8)
    {
        cout << endl << "Error. . . Please enter a valid choice (1-8): ";
        cin >> lineChoice;
        cout << endl;
    }

    return lineChoice;
}


// Set every element of revealed game and hidden game equal to each other, revealing all hidden numbers.
void revealFullGame(int revealedGame[][NUM_COLUMNS], int hiddenGame[][NUM_COLUMNS])
{
    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int column = 0; column < NUM_COLUMNS; column++)
        {
            revealedGame[row][column] = hiddenGame[row][column];
        }
    }   
}


// Use a switch statement to determine the sum of the line. (ex. case lineChoice = ROW_ONE, lineSum = revealedGame[0][0] + revealedGame[0][1] + revealedGame[0][2]). Then return lineSum
int calcLineSum(int lineChoice, int revealedGame[][NUM_COLUMNS])
{
    int lineSum;
    switch (lineChoice)
    {
        case 1: 
            lineSum = revealedGame[0][0] + revealedGame[0][1] + revealedGame[0][2];
            break;
        
        case 2:
            lineSum = revealedGame[1][0] + revealedGame[1][1] + revealedGame[1][2];
            break;

        case 3:
            lineSum = revealedGame[2][0] + revealedGame[2][1] + revealedGame[2][2];
            break;

        case 4:
            lineSum = revealedGame[0][0] + revealedGame[1][0] + revealedGame[2][0];
            break;

        case 5:
            lineSum = revealedGame[0][1] + revealedGame[1][1] + revealedGame[2][1];
            break;

        case 6:
            lineSum = revealedGame[0][2] + revealedGame[1][2] + revealedGame[2][2];
            break;

        case 7:
            lineSum = revealedGame[0][0] + revealedGame[1][1] + revealedGame[2][2];
            break;

        case 8: 
            lineSum = revealedGame[0][2] + revealedGame[1][1] + revealedGame[2][0];
            break;
    }
    return lineSum;
}


// Use yet another switch statement to determine the points on the chart (ex. case 19, totalPoints = SUM_NINETEEN)
int calcPoints(int lineSum)
{
    int totalPoints;
    switch (lineSum)
    {
        case 6:
            totalPoints = SUM_SIX;
            break;

        case 7:
            totalPoints = SUM_SEVEN;
            break;

        case 8:
            totalPoints = SUM_EIGHT;
            break;

        case 9:
            totalPoints = SUM_NINE;
            break;
        
        case 10:
            totalPoints = SUM_TEN;
            break;

        case 11:
            totalPoints = SUM_ELEVEN;
            break;

        case 12:
            totalPoints = SUM_TWELVE;
            break;

        case 13:
            totalPoints = SUM_THIRTEEN;
            break;

        case 14:
            totalPoints = SUM_FOURTEEN;
            break;
            
        case 15:
            totalPoints = SUM_FIFTEEN;
            break;
            
        case 16:
            totalPoints = SUM_SIXTEEN;
            break;
            
        case 17:
            totalPoints = SUM_SEVENTEEN;
            break;
            
        case 18:
            totalPoints = SUM_EIGHTEEN;
            break;
            
        case 19:
            totalPoints = SUM_NINETEEN;
            break;
            
        case 20:
            totalPoints = SUM_TWENTY;
            break;
            
        case 21:
            totalPoints = SUM_TWENTY_ONE;
            break;
            
        case 22:
            totalPoints = SUM_TWENTY_TWO;
            break;
            
        case 23:
            totalPoints = SUM_TWENTY_THREE;
            break;
            
        case 24:
            totalPoints = SUM_TWENTY_FOUR;
            break;
    }
    return totalPoints;
}


// At the end of the game, open the high score file, read the first line, and compare the high score points to the current points. If it is lower, congratulate the user and overwrite the score, name, and date
void determineHighScore(int totalPoints, string userName, string gameDate, string filename)
{
    int highScorePoints;
    fstream highScoreFile;
    highScoreFile.open(filename, ios::in);

    if (!highScoreFile)
    {
        cout << "Hmm. . . It seems you are the first player! Congratulations on the high score " << userName << "!" << endl;
        highScoreFile.close();
        highScoreFile.open(filename, ios::out);
        highScoreFile << totalPoints << endl << userName << endl << gameDate << endl;
        highScoreFile.close();
    }
    else
    {
        highScoreFile >> highScorePoints;
        if (totalPoints > highScorePoints)
        {
            cout << "Congratulations, " << userName << "! You have beat the high score of " << highScorePoints <<"!" << endl
                << "Recording your new high score. . ." << endl << endl;

            highScoreFile.close();
            highScoreFile.open(filename, ios::out);
            highScoreFile << totalPoints << endl << userName << endl << gameDate << endl;
            highScoreFile.close();
        }
        else
            cout << "I'm sorry " << userName << ", you did not get the high score. . ." << endl << "Try again next time :)" << endl;
    }
}