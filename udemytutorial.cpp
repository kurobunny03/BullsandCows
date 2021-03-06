#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//basically substituting words for ue4 compatibility
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
FText GetPlayerChoice();
bool AskToPlayAgain();

FBullCowGame BCGame;
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0;
	}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows! \n\n";

	std::cout << "((...))                ((...))\n";
	std::cout << "( o o )                ( O O )\n";
	std::cout << " \\   /                  \\   /\n";
	std::cout << "  ^_^                   (`_`)     \n " << std::endl;

	std::cout << "A game where you guess the hidden isogram (a word with no repeating letters) using only bulls and cows as your guide. \n\n";

	std::cout << "Bulls mean that a letter in the word you input is correct and is also in the right place. \n\n";

	std::cout << "While cows mean that a letter is correct but is in the wrong place in comparison to the hidden word. \n\n";

	std::cout << GetPlayerChoice();

	return;
}


void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "\n" << "You have a max tries of " << MaxTries << "\n\n";
	
	//Not won but there's still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		//Submit valid guess and receive count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << "\n";
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}
	return; 
}

FText GetPlayerChoice()
{
	std::cout << "Enter the level of difficulty from 3 to 9 letter isogram: \n";
	FText Choice = "";
	std::cin >> Choice;
	std::cin.ignore();
	BCGame.GetPlayerChoice(Choice);

	FText PlayerChoice = "You chose " + Choice + "!\n\nHINT: " + BCGame.GetHint(Choice) + "\n";

	return PlayerChoice;
}

FText GetValidGuess() 
{		
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << MyCurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess : ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Invalid - Must be a " << BCGame.GetHiddenWordLength() << " letter word \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Invalid - Must be a word with no repeating letters \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Invalid - Must be in lowercase letters only \n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until user gives valid guess
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon() == true) 
	{

	std::cout << "Congratulations! You guessed the hidden word ^^ \n" << std::endl;
	}

	else 
	{
      std::cout << "You used up all your tries, better luck next time! \n" << std::endl;

	}
	return;
}

bool AskToPlayAgain()
{
	FText Response = "";
	bool Again = true;
	bool IsValid = false;

	while (!IsValid)
	{

		std::cout << "Wanna play again? Y/N: ";
		std::getline(std::cin, Response);

		switch (Response[0])
		{
		case 'y':
		case 'Y':
			Again = true;
			IsValid = true;
			break;
		case 'n':
		case 'N':
			Again = false;
			std::cout << "Thanks for playing! Hope you enjoyed the game :)\n";
			IsValid = true;
			break;
		default:
			std::cout << "Invalid, must be either Y/N " << std::endl << std::endl;
			IsValid = false;
			break;
		}


	}
	return Again;
}
