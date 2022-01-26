#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

class Account
{
private:
	//Score variables
	int wins;
	int losses;
	double winLossRatio;
	int hits;
	int misses;
	double accuracy;
	int shipsSunk;
	int shipsLost;
	double sunkLostRatio;
	double topScore;
	
public:
	//Score mutators
	int addWin();
	int addLoss();
	double getWinRatio();
	int addHits(int);
	int addMisses(int);
	double setAccuracy();
	int addShipsSunk(int);
	int addShipsLost(int);
	double setSunkLostRation();
	double setTopScore(double);
	bool playerLoggedIn = false;

	std::string username;

	// Save stats to a file
	void saveStatsToFile();
	// Save stats to leaderboard
	void saveStatsToLeaderboard();
};

#endif