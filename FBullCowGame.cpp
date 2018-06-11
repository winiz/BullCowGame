#include "FBullCowGame.h"
#include <map>
#define TMap std::map  

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity (FString Guess) const {
	if (!IsIsogram(Guess)) { // if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (false) {// if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase; //TOOD write function
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

	// loop through all the letters of the word
		// if the letter is in the map
			//we do NOT have an isogram 
		// otherwise
			// add the letter to the map as seen
	return true;
}
