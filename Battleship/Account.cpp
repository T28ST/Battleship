#include "Account.h"
#include <iostream>
#include <string>
#include <fstream>


// addWin adds a win to the stats if a player wins a game
int Account::addWin()
{
	++wins;
	return wins;
}

// addLoss adds a loss to the stats if a player loses a game
int Account::addLoss()
{
	++losses;
	return losses;
}

// getWinRatop gets the ratio of wins in the total number of games
double Account::getWinRatio()
{
	int total;
	double ratio;
	total = wins + losses;	// Get total number of games
	ratio = wins / total;	// Get percent of total games won
	return ratio;			// Return the ratio of games won

}

// addHits adds the hits from a game to the accounts stats
int Account::addHits(int gameHits)
{
	hits = hits + gameHits;
	return hits;
}

// addMisses adds the misses from a game to the account stats
int Account::addMisses(int gameMisses)
{
	misses = misses + gameMisses;
	return misses;
}

// setAccuracy adds the current hits and misses for a total amount of shots and determines what percentage were hits
double Account::setAccuracy()
{
	int total;
	int newAccuracy;
	total = hits + misses;		// Get total number of shots
	newAccuracy = hits / total;	// Determine the percent of shots that were hits;
	return newAccuracy;			// Return the new accuracy of shots
}

// addShipsSunk adds the number ships the player sunk to the account total
int Account::addShipsSunk(int gameShipsSunk)
{
	shipsSunk = shipsSunk + gameShipsSunk;
	return shipsSunk;
}

// addShipsLost adds the number of ships the player lost to their account total
int Account::addShipsLost(int gameShipsLost)
{
	shipsLost = shipsLost + gameShipsLost;
	return shipsLost;
}

// setSunkLostRatio sets the ratio of ships the player sunk and the ships the player lost
double Account::setSunkLostRation()
{
	double ratio;
	ratio = shipsSunk / shipsLost;
	return ratio;
}

// setTopScore sets the accounts new top score if the player scored higher in the most recent game
double Account::setTopScore(double score)
{
	if (score > topScore)
	{
		std::cout << "Congratulations!\n" << "Your score of " << score << " is higher than your previous high score of " << topScore << std::endl;
		std::cout << score << " is now your new top score.\n";
		topScore = score;
		return topScore;
	}
	else
	{
		return topScore;
	}
}

// Save stats to a file
void Account::saveStatsToFile()
{
	std::ofstream statsFile;
	std::string filename; //create a file with the name of the user

	filename = username + ".txt";
	// Open or create file with the name of the user
	statsFile.open(filename.c_str());
	if (statsFile) // ensure the file is open
	{
		// Write user's stats to the file
		// Overwrite is fine for when the user improves their stats.
		statsFile << username << "'s Stats: \n";
		statsFile << "Top Score: " << topScore << std::endl;
		statsFile << "Wins: " << wins << " Losses: " << losses << " W/L Ratio: " << winLossRatio << std::endl;
		statsFile << "Hits: " << hits << " Misses: " << misses << " Accuracy: " << accuracy << std::endl;
		statsFile << "Ships Sunk: " << shipsSunk << " Ships Lost: " << shipsLost << " Sunk/Lost Ratio: " << sunkLostRatio << std::endl;
	}
	else
	{
		std::cout << "Unable to open user file for stats\n";
	}
	statsFile.close();
}

void Account::saveStatsToLeaderboard()
{
	std::fstream leaderboardFile;
	std::string search;
	bool usernameFound = false;

	leaderboardFile.open("leaderboard.txt");

	if (leaderboardFile)
	{
		std::cout << "file opened\n";
		while (getline(leaderboardFile, search) && !usernameFound)
		{
			if (search.find(username) != std::string::npos)
			{
				leaderboardFile << username << " | Top Score: " << topScore << " | Accuracy: " << accuracy << " | Sunk/Lost Ratio: " << sunkLostRatio << std::endl;
			}
			else
			{
				leaderboardFile.seekg(0, std::ios::end);
				leaderboardFile << username << " | Top Score: " << topScore << " | Accuracy: " << accuracy << " | Sunk/Lost Ratio: " << sunkLostRatio << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Could not open leaderboard file";
	}
	system("pause");
	leaderboardFile.close();
}