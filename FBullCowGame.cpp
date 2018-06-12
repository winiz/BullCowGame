#include "FBullCowGame.h"
#include <map>
#include <cstdlib>
#define TMap std::map  

FBullCowGame::FBullCowGame() { Reset(); } // constructor 

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

void FBullCowGame::Reset() {
	TMap<int32, FString> HIDDEN_WORDS {
		{ 1, "a" },
		{ 2, "uh" },
		{ 3, "cat" },
		{ 4, "wale" },
		{ 5, "music" },
		{ 6, "planet" },
		{ 7, "capitol" },
		{ 8, "computer" },
		{ 9, "education" },
		{ 10, "playground" }
	};
	int32 randomNum = rand() % 10 + 1;
	MyHiddenWord = HIDDEN_WORDS[randomNum];
	MyMaxTries = MyHiddenWord.length() * 2;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// This is a implicit dependency (not completely clear that 
// one thing depends on another)
EGuessStatus FBullCowGame::CheckGuessValidity (FString Guess) const {
	if (!IsIsogram(Guess)) { // if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {// if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) {// if the guess length is wrong 
		return EGuessStatus::Wrong_Length;
	}
	else { // otherwise
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// GChar means GuessChar
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the guess
	// MHWChar means MyHiddenWordChar
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare latters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[MHWChar] == MyHiddenWord[GChar]) {
				// if they are in the same place
				if (MHWChar==GChar) {
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; //increment cows 
				}
			}
		}
	}
	if (WordLength == BullCowCount.Bulls) {
		bGameIsWon = true;
	}
	else { bGameIsWon = false; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; //setup our map (Tmap initialize bool to false)

	// loop through all the letters of the word
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case 
		if (LetterSeen[Letter] == true) {  // if the letter is in the map
			return false;                  // we do NOT have an isogram 
		}
		else {                             // otherwise
			LetterSeen[Letter] = true;     // add the letter to the map as seen
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const {
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
