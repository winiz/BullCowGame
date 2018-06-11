#pragma once 
#include <string>

using FString = std::string;
using int32 = int;

// all value initailized to 0;
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus //strongly typed enum
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};  

class FBullCowGame {
public: 
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	 
	void Reset(); //TODO make a more rich return value.
	
	
	// counts bulls & cows, and increases try # assuming valid guess 
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
};
