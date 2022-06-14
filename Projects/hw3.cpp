// Programmer: John Bramer
// Date: 2/8/2021.
// File: Wordle.cpp
// Assignment: HW2
// Purpose: this file is a word guessing game
// played between 2 players, the objective is for
// player_two to guess player_one's word

#include <iostream>
#include <string>
#include <cctype>

using namespace std;
//Description: This function outputs text based off of how similar the_word and guess are
//Pre: both words, need to be full caps and have a length of 5 characters
//Post: @.@, ^('-')^, ^o^, dependant on simialrities
void word_check(string the_word, string guess, string& wordle_emoji_total);
//Description: This function returns true is the word given contains only alphabetical characters
//Pre: the word needs to be 5 letters long
//Post: true or false
bool does_word_contain_only_valid_characters(string the_word);
//Description: This function greets user to the game wordle
//Pre: none
//Post: prints a greeting message for new users
void greet();
//Description: This function prints the game summary for the latest two users
//Pre: 2 players needed to have already played the game once
//Post: prints both players names, number of rounds played, Initial friendship level, and Current friendship level
void printGameSummary(string player_one, string player_two, int round_count, float inital_friendship_level, float friendship_level);
//Description: This function prints the progress player_two makes twards guessing player_one's word
//Pre: 2 players need to have already played the game once
//Post: Prints both players names, the round history, round and attempt count
void shareWorldle(string player_one, string player_two, int round_count, int attempt_count, string wordle_emoji_total);

int main()
{
    string player_one;
    string player_two;
    string the_word;
    float friendship_level = 0;
    float inital_friendship_level = 0;
    const int MAX_ATTEMPTS = 6;
    int attempt_count = MAX_ATTEMPTS;
    string guess;
    int menu_decision;
    int round_count = 0;
    string wordle_emoji_total;
    string temp;
    const int FRIEND_LEVEL_MIN = 0;
    const int FRIEND_LEVEL_MAX = 100;
    const int WORD_LENGTH = 5;
    const int MENU_ONE = 1;
    const int MENU_TWO = 2;
    const int MENU_THREE = 3;
    const int MENU_FOUR = 4;
    const int MENU_FIVE = 5;
    /*[grader]
      MENU_ONE-MENU-5 don't really need to be constants, since they don't really
      serve to illustrate their meaning, and they'd be unreasonable to change to
      any other value (it would make no sense having MENU_THREE = 7, for instance).
      Otherwise, however, very good use of constants. 
    */
    

    greet();
   

    do {
        cout << "The Wordle's Menu" << endl;
        cout << "-----------------" << endl;
        cout << "1. Start a new game (with new players)" << endl;
        cout << "2. Start a new round (with existing players)" << endl;
        cout << "3. Print game summary (of existing players)" << endl;
        cout << "4. Share result (of last round)" << endl;
        cout << "5. Exit the game (are you sure?)" << endl;

        do {
            cin >> menu_decision;
            if (menu_decision < MENU_ONE || menu_decision > MENU_FIVE)
                cout << "Invalid! Please enter a number 1-5" << endl;
        } while (menu_decision < MENU_ONE || menu_decision > MENU_FIVE);

        if (menu_decision == MENU_ONE) {
            cout << "What is the new name for player #1?" << endl;
            cin >> player_one;
            cout << "what is the new name for player #2?" << endl;
            cin >> player_two;
            round_count = 0;
            attempt_count = MAX_ATTEMPTS;

        }
        if (menu_decision == MENU_THREE or menu_decision == MENU_FOUR) {

            if (round_count == 0) {
                cout << "A round hasn't started before this, please pick another option" << endl;
            }
            else if (menu_decision == MENU_THREE) {
                printGameSummary(player_one, player_two, round_count, inital_friendship_level, friendship_level);
                if(friendship_level < 20) //[grader] -1: 20 should be a constant (PITY_FRIENDSHIP_LEVEL or similar)
                    friendship_level = friendship_level + 2; //[grader] -1: 2 should be a constant (PITY_FRIENDSHIP_BONUS or similar)

            }
            else if (menu_decision == MENU_FOUR) {
                shareWorldle(player_one, player_two, round_count, attempt_count, wordle_emoji_total);
                
                
            }
        }


        if (menu_decision == MENU_TWO && player_one == "") {
            cout << "Invalid, players have not been identified, please pick option #1 to start a new game with new players" << endl;
        }

        else if (menu_decision == MENU_ONE or menu_decision == MENU_TWO) {

            cout << player_one << " enter \"the word\"" << endl;
            do {
                cin >> the_word;

                if (the_word.length() != WORD_LENGTH || !does_word_contain_only_valid_characters(the_word))
                    cout << "Invalid, Please enter a 5 letter word (In all caps) that contains only alphabetical characters" << endl;

            } while (the_word.length() != WORD_LENGTH || !does_word_contain_only_valid_characters(the_word));

            cout << player_one << " enter the friendship level" << endl;
            do {
                cin >> friendship_level;
                if (friendship_level < FRIEND_LEVEL_MIN || friendship_level > FRIEND_LEVEL_MAX)
                    cout << "Invalid! Please enter again." << endl;
            } while (friendship_level < FRIEND_LEVEL_MIN || friendship_level > FRIEND_LEVEL_MAX);
            inital_friendship_level = friendship_level;

            while (attempt_count != 0 && the_word != guess) {
                cout << player_two << " you have " << attempt_count << " attempts to guess " << player_one << "s word correctly" << endl;
                do {
                    cin >> guess;
                    if (guess.length() != WORD_LENGTH)
                        cout << "Invalid, Please enter a 5 letter word (In all caps)" << endl;
                } while (guess.length() != WORD_LENGTH);

                attempt_count = attempt_count - 1;
                word_check(the_word, guess, wordle_emoji_total);

            }
            if (the_word == guess) {
                cout << "Nice! you guessed " << player_one << "'s word correctly!" << endl;
                friendship_level = friendship_level + attempt_count;
            }
            else if (attempt_count == 0) {
                cout << "Looks like you ran out of attempts, good try" << endl;
            }
            the_word = "";
            guess = "";
            round_count++;
        }

    } while (menu_decision != MENU_FIVE);



    if (friendship_level <= FRIEND_LEVEL_MAX) {
        cout << "Your friendship level has now be updated to " << friendship_level << endl;
    }
    else {
        cout << "Your friendship level has exceeded the maximum value of 100." << endl;
    }
    return 0;
}




void greet() {
    cout << "Welcome to Wordle For Friends!" << endl;
    cout << "≤^.^≥" << endl;
}


void printGameSummary(string player_one, string player_two, int round_count, float inital_friendship_level, float friendship_level) {

    cout << "Game Summary" << endl;
    cout << "\tPlayer 1: " << player_one << endl;
    cout << "\tPlayer 2: " << player_two << endl;
    cout << "\tNumber of rounds played: " << round_count << endl;
    cout << "\tInitial friendship level: " << inital_friendship_level << endl;
    cout << "\tCurrent friendship level: " << friendship_level << endl;
}



void shareWorldle(string player_one, string player_two, int round_count, int attempt_count, string worldle_emoji_total) {
    cout << "Wordle For Friends " << "(" << player_one << " and " << player_two << ")" << endl;
    cout << worldle_emoji_total << endl;
    cout << "Worldle Round  " << round_count << "  " << attempt_count << "/6" << endl;

}


bool does_word_contain_only_valid_characters(string the_word) {
    return the_word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos; //[grader] Clever!
}

void word_check(string the_word, string guess, string& wordle_emoji_total)
{

    for (size_t i = 0; i < the_word.length(); i++) {
        if (the_word.at(i) == guess.at(i)) {
            wordle_emoji_total += "^o^ ";
            cout << guess.at(i) << " ^o^" << endl;
            
        }
        else if (the_word.at(i) != guess.at(i) && (the_word.find(guess.at(i)) != string::npos)) {
            wordle_emoji_total += "^-^ ";
            cout << guess.at(i) << " ^-^" << endl;
            
        }
        else {
            wordle_emoji_total = wordle_emoji_total + "@.@ ";
            cout << guess.at(i) << " @.@" << endl;
            
        }
    }
    wordle_emoji_total += "\n";
}








