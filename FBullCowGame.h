#pragma once
#include <string>
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
	void Reset();
	FString GetPlayerChoice(FString);
	FString GetHint(FString);
	FBullCowCount SubmitValidGuess(FString);



private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	FString ChooseIsogram(FString);
	FString GivePlayerHint(FString);
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;	
};
