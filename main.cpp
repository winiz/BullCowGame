/* 
	This is the console executatble, that makes use of the 
	BullCow class, this acts as the view in a MVC pattern, 
	and is responsible for all user interaction. For Game 
	logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; //FText used for user intereaction
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgin();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game 

//The Entry of this application 
int main() {
	bool PlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PlayAgain = AskToPlayAgin();
	} while (PlayAgain == true);
	return 0;
}


void PrintIntro() {
	// INTRODUCE THE GAME
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I am thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining 
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 
		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << ". Cows =  " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();
	return;
}

//loop continually untill the user gives a valid guess
FText GetValidGuess() { 
	FText guessInstance = "";
	EGuessStatus Status = EGuessStatus::Invalid_status;
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, guessInstance);

		Status = BCGame.CheckGuessValidity(guessInstance);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a Isogram (word without repeating letters). \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter in all Lowercase letters. \n";
			break;
		default:
			// assume the guess is valid 
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return guessInstance;
}

bool AskToPlayAgin() {
	std::cout << "Do you want to play again with the same hidde word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	bool flag = (Response[0] == 'y') || (Response[0] == 'Y');
	return flag;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "YOU WON!!!!!!!" << std::endl;
	}
	else if (BCGame.GetCurrentTry() > BCGame.GetMaxTries()) {
		std::cout << "Bad luck, Maybe next time?" << std::endl;
	}
	return;
}
