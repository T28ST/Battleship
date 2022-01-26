/*
Name: Battleship
Description: Battleship board game in c++
Author: Tyler Stanton
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Account.h"

using namespace std;

//Prototypes
void showMainMenu();
void registerNewAccount();
void userLogIn();
void singleplayer();
void multiplayer();
void leaderboard();
void logOut();
void displayBoard();

//Constants


Account player1;
Account player2;

int main()
{
	// Main menu selection variables
	int choice = 0;	// User input
	int choiceSingleplayer = 1; //menu option 1
	int choiceMultiplayer = 2;	//menu option 2
	int choiceLeaderboard = 3;	//menu option 3
	int choiceLogIn = 4;		//menu option 4
	int choiceRegister = 5;		//menu option 5
	int choiceQuit = 6;			//menu option 6
	int choiceLogOut = 7;		//menu option 7

	while (choice != choiceQuit)
	{
		showMainMenu();
		cin >> choice;
		if (choice < 8 && choice > 0)
		{
			if (choice == choiceSingleplayer)		// user selects singleplayer
			{
				if (!player1.playerLoggedIn)		// Don't start single player if player one is not logged in
				{
					cout << "Please log in to play singleplayer.\n";
					system("pause");
				}
				else if (player2.playerLoggedIn)	// Don't start singleplayer if player two is logged in
				{
					cout << "Please log out player 2 to play singleplayer";
					system("pause");
				}
				else if (player1.playerLoggedIn && !player2.playerLoggedIn)	// Start singleplayer if player one is logged in and player two is not
				{
					singleplayer();
				}
			}
			else if (choice == choiceMultiplayer)	// user selects multiplayer
			{
				if (!player1.playerLoggedIn || !player2.playerLoggedIn)	// do not start multiplayer if either player one or player two are not loggeed in
				{
					cout << "Please log in both players to play multiplayer";
					system("pause");
				}
				else
				{
					multiplayer();
				}
			}
			else if (choice == choiceLeaderboard)	// user selects leaderboard
			{
				player1.saveStatsToLeaderboard();
				// leaderboard();
			}
			else if (choice == choiceLogIn)			//user selects log in
			{
				if (!player1.playerLoggedIn || !player2.playerLoggedIn)	// If neither player is logged in, start the log in process
				{
					userLogIn();
				}
				else
				{
					cout << "Both players are logged in. Please log out a player to log in.\n";
				}
			}
			else if (choice == choiceRegister)		// user selects register
			{
				registerNewAccount();
			}
			else if (choice == choiceLogOut)		// user selects log out
			{
				logOut();
			}
		}
	}
	system("pause");
	return 0;
}

void showMainMenu()
{
	system("cls"); // Clear screen

	cout << R"(
 _           _   _   _           _     _       
| |         | | | | | |         | |   (_)      
| |__   __ _| |_| |_| | ___  ___| |__  _ _ __  
| '_ \ / _` | __| __| |/ _ \/ __| '_ \| | '_ \ 
| |_) | (_| | |_| |_| |  __/\__ \ | | | | |_) |
|_.__/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/ 
                                        | |    
                                        |_|  
)" << endl;
	cout << "Welcome to Battleship ";

	// Display usernames of logged in players
	if (player1.playerLoggedIn)
	{
		cout << player1.username;
		if (player2.playerLoggedIn)
		{
			cout << " and " << player2.username;
		}
	}
	cout << endl << endl << "1. Singleplayer";
	// Show that singleplayer is locked if player one is not logged in or player two is
	if (!player1.playerLoggedIn)
	{
		cout << " [LOCKED - Please log in to play]";
	}
	else if (player2.playerLoggedIn)
	{
		cout << " [LOCKED - Log out player 2 to play]";
	}
	cout << endl << "2. Multiplayer";

	// SHow that multiplayer is locked if both players are not logged in
	if (!player1.playerLoggedIn || !player2.playerLoggedIn)
	{
		cout << " [LOCKED - Please log in both players to play]";
	}
	cout << endl << "3. Leaderboard\n" << "4. Log in\n" << "5. Register an account\n" << "6. Quit\n";

	// Display the log out option if any players are logged in
	if (player1.playerLoggedIn || player2.playerLoggedIn)
	{
		cout << "7. Log out\n";
	}
	return;
}

void registerNewAccount()
{
	fstream userFile;
	string newUsername;
	string newEmail;
	string newPassword;
	int at; // Email input validation
	int dot; // Email input validation

	system("cls"); // Clear screen

	userFile.open("userdata.txt", ios::out | ios::app); // Open userdata file for input

														// Get a username
	cout << "Enter a username. Your username must be under 15 characters.\n";
	cin >> newUsername;

	// Input validation
	while (newUsername.length() > 15)
	{
		cout << "Your username was over 15 characters. Please enter a shorter username.\n";
		cin >> newUsername;
	}

	// Get an Email
	cout << "Enter your Email\n";
	cin >> newEmail;

	// Email format validation
	//Check for an @ sign in the given email
	at = newEmail.find('@');
	while (at == string::npos)
	{
		cout << "Your email address must the format of example@email.com, you are missing an @ sign.\nPlease enter a valid email address: ";
		cin >> newEmail;
		at = newEmail.find('@');
	}

	//Check for a period in the given email
	dot = newEmail.find('.', at + 1);
	while (dot == string::npos)
	{
		cout << "Your email address must have the format of example@email.com, you are missing a '.com'\nPlease enter a valid email address: ";
		cin >> newEmail;
		at = newEmail.find('@');
		while (at == string::npos)
		{
			cout << "Your email address must have an @ sign. \nPlease enter a valid email address: ";
			cin >> newEmail;
			at = newEmail.find('@');
		}
		dot = newEmail.find('.', at + 1);
	}


	// Get a password
	cout << "Enter a password. Your password must not be more than 15 characters and different from your username and email address.\n";
	cin >> newPassword;


	//Input validation
	while (newPassword.length() > 15 || newPassword == newUsername || newPassword == newEmail)
	{
		cout << "The password you entered is not valid.\n" << "Your password must not be more than 15 characters long and must be different from your username and email address.\n" << "Enter your password:";
		cin >> newPassword;
	}

	if (userFile.is_open())
	{
		userFile << newEmail << endl << newUsername << " " << newPassword << endl;
	}
	userFile.close();

	cout << "New user: " << newUsername << " has been registered.\n" << "You will be returned to the main menu. To log in to your new account select the 'log in' option at the main menu.\n";
	system("pause");
}


void userLogIn()
{
	fstream userFile;
	string loginUsername; // user input username
	string loginPassword; // user input password
	string userLogin;	  // login verification string
	string search;
	bool loginFound = false;

	system("cls"); // Clear the screen

	cout << "To login please enter your username and password.\n" << "Username: ";
	cin >> loginUsername;
	cout << "Password: ";
	cin >> loginPassword;

	userLogin = loginUsername + " " + loginPassword; //Search term for login

	userFile.open("userdata.txt", ios::in); // Open user data file
	
	//Search for username
	if (userFile) // Ensure the file is open
	{
		while (!userFile.eof())
		{
			while (getline(userFile, search) && !loginFound)
			{
				if (search.compare(userLogin) == 0) // if exact login info is found
				{
					loginFound = true; // break loop

					if (!player1.playerLoggedIn) // If player one is not logged in, set this log in to player 1
					{
						player1.username = loginUsername;
						player1.playerLoggedIn = true;
					}
					else if (player1.playerLoggedIn && !player2.playerLoggedIn) // If player one is logged in but player two isn't, log in player 2
					{
						player2.username = loginUsername;
						player2.playerLoggedIn = true;
					}
				}
			}
		}
	}
	// Login successful
	if (loginFound)
	{
		cout << "Welcome " << loginUsername << endl;
		system("pause");
		return;
	}
	else if (!loginFound) //Login unsuccessful
	{
		cout << "Login not found.\n" << "Returning to main menu...\n";
		system("pause");
		return;
	}
}

void singleplayer()
{
	// Variables for tracking stats
	int playerHits;
	int playerMisses;
	int playerSinks;
	int playerLosses;
	double score;
	// Gameboard variables
	int COLUMNS;
	int ROWS;
	vector<vector<char>> playerBoard(10, '~');
	char computerBoard[10][10];
	

}

void multiplayer()
{

}

void leaderboard()
{

}

void logOut()
{

	if (player2.playerLoggedIn) // Log out player 2
	{
		cout << "Player " << player2.username << " logged out.\n";
		player2.playerLoggedIn = false;
		player2.username = " ";
		system("pause");
	}
	else if (player1.playerLoggedIn) // Log out player 1
	{
		cout << "Player " << player1.username << " logged out.\n";
		player1.playerLoggedIn = false;
		player1.username = " ";
		system("pause");
	}
	else
	{
		cout << "There are no players logged in.\n" << "Returning to main menu...\n";
		system("pause");
	}
}

void displayBoard()
{

}