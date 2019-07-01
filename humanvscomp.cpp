/* --------------------------------------------------------
 * GuessingGame.cpp
 *     Text-based version of a 0/1 number guessing game,
 *     where the computer tries to forecast the human's guess.
 *     A correct computer forecast results in decrementing the score by 1.
 *     An incorrect computer forecast results in incrementing the score by 1
 *     Reaching -10 (computer wins) or +10 (human wins) ends the game.
 *
   Running the program looks like:
 
 */

#include <iostream>
#include <cstdlib>	   // For abs() on some systems
#include <cctype>
#include <iomanip>     // For cout << setw()
using namespace std;

// Global constants
const int  TableSize = 8;   // 8 rows, corresponding to binary 000 through 111

//--------------------------------------------------------------------
// Display ID info
void displayIDInfo()
{
    cout << "Author:  Harsh Devprakash Gupta            \n"
         << endl;
}//end displayIDInfo()


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to the 0/1 guessing game!                                  \n"
         << "                                                                   \n"
         << "Enter 0 or 1, trying to outsmart the computer, which is going to   \n"
         << "attempt to forecast your guesses.  On each move the score indicator\n"
         << "moves to the right if the computer guesses correctly, and moves    \n"
         << "to the left if the computer does not.                              \n"
         << "    Enter 't' to toggle displaying the data table.                 \n"
         << "    Enter 'r' to reset the board.                                  \n"
         << "    Enter 'x' to exit.                                             \n"
         << "Good luck, you'll need it!                                         \n"
         << endl;
}//end displayInstructions()


//--------------------------------------------------------------------
// ScoreValue varies from -10 to 10, and is represented using ASCII graphics.
void displayScoreStatusBar( int scoreValue)
{
    // Display the header
    cout << endl
         << "Computer          Human  " << endl
         << "x---------x+++++++++x  "
         << endl;
    
    // Display the pointer to reflect the current score
    // Leave initial spaces to then have the pointer be in the correct position.
    for( int i=0; i<scoreValue+10; i++) {
        cout << " ";
    }
    cout << "^" << endl;
}//end displayScoreStatusBar()


//--------------------------------------------------------------------
// Update the score and display an appropriate message.  This handles
// both wins as well as intermediate values as score varies back and forth.
void updateScoreAndDisplayMessage( int &scoreValue, int computerPrediction, int userInput)
{
    // Display whether the human or the computer got the point on this move.
    if( computerPrediction == userInput) {
        cout << "   Computer gets a point." << endl;
        scoreValue--;
    }
    else {
        cout << "   Human gets a point." << endl;
        scoreValue++;
    }
    
    // Redisplay the score if there was a win
    if( abs( scoreValue) >= 10) {
        displayScoreStatusBar( scoreValue);
    }
    
    // Display a message if there was a win
    if( scoreValue >= 10) {
        cout << "*** Human wins! ***" << endl;
    }
    else if( scoreValue <= -10) {
        cout << "*** Silicon rules! ***" << endl;
    }
    else if( scoreValue == -5) {
        cout << ">>> You're going to lose! <<<" << endl;
    }
    else if( scoreValue == 5) {
        cout << "<<< Humans are the best! >>>" << endl;
    }
}//end updateScoreAndDisplayMessage()


//--------------------------------------------------------------------
// Interpret the last three moves as a binary number, and return the
// decimal number corresponding to that 000...111 binary value.
int convertBinaryToDecimal( int lastThreeMoves[])
{
    // examine the bits one at a time, going from right to left
    int result = lastThreeMoves[ 2];
    if( lastThreeMoves[ 1] == 1) result = result + 2;
    if( lastThreeMoves[ 0] == 1) result = result + 4;
    
    return result;
}//end convertToBinary()


//--------------------------------------------------------------------
// Given the history table of previous moves, use the last three moves
// as a binary number to find which row of the table reflects the current
// last-three-moves situation.  Find out which of 0 or 1 is most likely
// given past history, and return that value.  If it is tied, then simply
// return the opposite of the most recent move.
int getComputerPrediction( int movesHistory[ ][ 2], int lastThreeMoves[])
{
    int rowIndex = convertBinaryToDecimal( lastThreeMoves);
    
    if( movesHistory[ rowIndex][ 0] > movesHistory[ rowIndex][ 1]) {
        return 0;
    }
    else if( movesHistory[ rowIndex][ 0] < movesHistory[ rowIndex][ 1]) {
        return 1;
    }
    else {
        // The two values are equal, so return the opposite of the most recent move.
        if( lastThreeMoves[2] == 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}//end getComputerPrediction()


//--------------------------------------------------------------------
// Given an integer number, convert it to binary and store the resulting
// three binary digits in the binaryNumber array.
//        0.  000
//        1.  001
//        2.  010
//        3.  011
//        4.  100
//        5.  101
//        6.  110
//        7.  111
void convertNumberToBinary( int number, int binaryNumber[])
{
    // Successively set the right-most bit by checking to see
    // if the number is even or odd.  Then divide the number
    // by 2 to right-shift it and repeat to get the next bit.
    // The first time through we set the right-most bit ( binaryNumber[2] )
    // then the next time the middle bit ( binaryNumber[1] ) and
    // the third time the left bit ( binaryNumber[0] )
    for( int i=2; i>=0; i--) {
        if( number % 2 == 1) {
            // It is odd, so right-most bit is 1
            binaryNumber[ i] = 1;
        }
        else {
            // It is even, so right-most bit is 0
            binaryNumber[ i] = 0;
        }
        number = number / 2;
    }
}//end convertNumberToBinary()


//--------------------------------------------------------------------
// Display the table information, the last three moves and the current
// computer prediction. The move history table has the rows:
//        0.  000
//        1.  001
//        2.  010
//        3.  011
//        4.  100
//        5.  101
//        6.  110
//        7.  111
void displayTableInformation( int movesHistory[][2],    // History table of all previous moves
                              int lastThreeMoves[],     // Last three moves, each of them 0 or 1
                              int computerPrediction)   // Computer prediction (0 or 1)
{
    int binaryNumber[ 3] = {0,0,0};       // Stores decimal number converted to 3 bits.
    
    // Display table header
    cout << "         0   1  \n"
         << "       --- ---    " << endl;
    
    // Display contents of each table row, with table row number as a binary number.
    for( int i=0; i<TableSize; i++) {
        // Display row index as a binary number.
        convertNumberToBinary( i, binaryNumber);
        cout << "   ";
        cout << binaryNumber[ 0] << binaryNumber[ 1] << binaryNumber[ 2];
        
        // Display the table values
        cout << setw(4) << movesHistory[ i][ 0] << setw(4) << movesHistory[ i][ 1] << endl;
    }
    
    // Display the last three moves and the compute forecast.
    cout << "   Previous three: " << lastThreeMoves[ 0] << lastThreeMoves[ 1] << lastThreeMoves[ 2]
         << ".  Forecast: " << computerPrediction << endl;
}//end displayTableInformation()


//--------------------------------------------------------------------
//  Prompt for 16 values to be used to reset the table.
//  Also reset the last three moves and the move number.
void resetValues( int movesHistory[ ][ 2], int lastThreeMoves[], int &moveNumber)
{
    cout << "Enter 16 values to be used to set the moves history table: ";
    for( int row=0; row<TableSize; row++) {
        for( int col=0; col<2; col++) {
            cin >> movesHistory[ row][ col];
        }
    }
    
    // Reset the last three moves and the move number
    for( int row=0; row<3; row++) {
        lastThreeMoves[ row] = 0;
    }
    moveNumber = 1;
}//end resetValues()


//--------------------------------------------------------------------
// Update the moves history array if there have been more than 3 moves.
void updateMoveHistoryAndLastThreeMoves(
                int movesHistory[ ][ 2],
                int lastThreeMoves[],
                int moveNumber,
                int userInput)
{
    int theRow = convertBinaryToDecimal( lastThreeMoves);
    // Only update the moves history if there have been more than 3 moves already
    if( moveNumber > 3) {
        movesHistory[ theRow][ userInput]++;        // Add one to the appropriate moves history entry
    }
    // Left-shift the last three moves array.
    lastThreeMoves[ 0] = lastThreeMoves[ 1];
    lastThreeMoves[ 1] = lastThreeMoves[ 2];
    lastThreeMoves[ 2] = userInput;
}//end updateMoveHistoryAndLastThreeMoves()


//--------------------------------------------------------------------
int main()
{
    int scoreValue = 0;               // Varies from -10 (computer wins) to 10 (human wins)
    int moveNumber = 1;
    int computerPrediction = -1;      // Should be 0 or 1
    int movesHistory[ TableSize][ 2]; // 2D array used to accumulate human guessing patterns
    int lastThreeMoves[ 3] = {0,0,0}; // Last three moves, with oldest move being in position 0
    char userInput;                   // Character for the user input.  If in the range '0'..'1'
                                      //    then convert it to a numerical value 0 or 1
    int userMove;                     // Stores above userInput as a number when it is '0'..'1'
    bool tableDisplayEnabled = false; // Flag to indicate whether or not moves history table is displayed
    
    displayIDInfo();          // Display ID info
    displayInstructions();    // Display game instructions

    // Initialize the moves history table with all 0 values;
    for( int i=0; i<TableSize; i++) {
        movesHistory[ i][ 0] = 0;
        movesHistory[ i][ 1] = 0;
    }
    
    // Main game-playing loop
    while( abs( scoreValue) < 10) {
        // Display the current score status bar.
        displayScoreStatusBar( scoreValue);
        
        // Have the computer generate its prediction
        computerPrediction = getComputerPrediction( movesHistory, lastThreeMoves);
        
        // If table display is toggled on, then display the table, the last three moves, and the computer forecast
        if( tableDisplayEnabled) {
            displayTableInformation( movesHistory, lastThreeMoves, computerPrediction);
        }
        
        // Prompt for and get the user input
        cout << moveNumber << ". Your input: ";
        cin >> userInput;
        userInput = toupper( userInput);
        if( userInput == 'X') {
            break;    // break out of game-playing loop
        }
        if( userInput == 'T') {
            tableDisplayEnabled = ! tableDisplayEnabled;    // Toggle the table display flag
            continue;       // Loop back up without changing anything else, to retry this move
        }
        if( userInput == 'R') {
            resetValues( movesHistory, lastThreeMoves, moveNumber);
            continue;
        }
        // If we got to this point, userInput was '0' or '1'.  Convert this to the value 0 or 1
        userInput = userInput - '0';
        
        // Update the score and display messages
        updateScoreAndDisplayMessage( scoreValue, computerPrediction, userInput);
        
        // Update information in preparation for the next loop iteration.
        updateMoveHistoryAndLastThreeMoves( movesHistory, lastThreeMoves, moveNumber, userInput);
        
        moveNumber++;
    }
    
    cout << endl;
    return 0;
}//end main()



