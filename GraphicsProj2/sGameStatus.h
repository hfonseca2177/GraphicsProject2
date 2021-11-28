#pragma once
#include <string>
#include <sstream>

using namespace std;

//Container for  the state of Hero
struct sGameStatus
{
	string heroStats;
	string heroScore;
	string currentLairItem;
	string lootableFound;
	string result;
	string lootsRemaining;

};