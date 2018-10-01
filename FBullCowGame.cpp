#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame(){Reset();} //default constructor
using int32 = int;

int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}

bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const {TMap<int32,int32>WordLengthToMaxTries{{3,4},{4,6},{5,7},{6,8},{7,9},{8,9},{9,10}};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

FString FBullCowGame::ChooseIsogram(FString Choice)
{
	TMap<FString, FString> BuzzWord
	{
		{ "3", "sir" },
		{ "4", "care" },
		{ "5", "amber" },
		{ "6", "recoil" },
		{ "7", "lapsing" },
		{ "8", "enshroud" },
	    { "9", "tenacious" }
	};

	if (Choice == "3")
	{
		MyHiddenWord = BuzzWord[Choice];
	}
	else if (Choice == "4")
	{
		MyHiddenWord = BuzzWord[Choice];
	}
	else if (Choice == "5")
	{
		MyHiddenWord = BuzzWord[Choice];
	}
	else if (Choice == "6")
	{
		MyHiddenWord = BuzzWord[Choice];
	}
	else if (Choice == "7")
	{
		MyHiddenWord = BuzzWord[Choice];
	}
	else if (Choice == "8")
	{
		MyHiddenWord = BuzzWord[Choice];
	}
	else if (Choice == "9")
	{
		MyHiddenWord = BuzzWord[Choice];
	}

	MyHiddenWord = BuzzWord[Choice];

	return MyHiddenWord;
}

FString FBullCowGame::GetPlayerChoice(FString Choice)
{
	FString PlayerChoice = ChooseIsogram(Choice);

	return PlayerChoice;
}


FString FBullCowGame::GivePlayerHint(FString TheHint)
{
	TMap<FString, FString>Hints{ {"3", "It's a polite term for men"},{"4", "It's a synonym for love"},{"5", "Fossil/gemstone combo"},{"6", "When a gun fires"},{"7", "Habits are hard to break"}, {"8","Hidden behind a cloak"}, {"9","Another word for persistent"}};
	FString Hint;
	if (TheHint == "3")
	{
		Hint = Hints[TheHint];
	}
	else if (TheHint == "4")
	{
		Hint = Hints[TheHint];
	}
	else if (TheHint == "5")
	{
		Hint = Hints[TheHint];
	}
	else if (TheHint == "6")
	{
		Hint = Hints[TheHint];
	}
	else if (TheHint == "7")
	{
		Hint = Hints[TheHint];
	}
	else if (TheHint == "8")
	{
		Hint = Hints[TheHint];
	}
	else if (TheHint == "9")
	{
		Hint = Hints[TheHint];
	}
	return Hint;
}

FString FBullCowGame::GetHint(FString TheHint)
{
	FString PlayersHint = GivePlayerHint(TheHint);

	return PlayersHint;
}


void FBullCowGame::Reset()
{	
	MyCurrentTry = 1;

	bGameIsWon = false;

	return;
}





EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}

//n receives a VALID guess, increments turn, return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //assuming the same length as guess

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{

		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {

			//if they match
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {

				
				if (MHWChar == GChar) {

					BullCowCount.Bulls++; 
				}
				else {
					BullCowCount.Cows++;
				}

			}
			
	    }
	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
		
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{	
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {return true;}
    
	TMap<char, bool> LetterSeen; // setup map
	for (auto Letter : Word) 	// for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		
	//if letter is in the map
		if (LetterSeen[Letter])
		{
			return false; 
		}
		else {LetterSeen[Letter] = true;} //add the letter to the map as seen
	
	}
	return true; 
	}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
