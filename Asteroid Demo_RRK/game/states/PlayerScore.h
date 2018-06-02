#ifndef __PLAYERSCORE_H
#define __PLAYERSCORE_H

#include <iostream>
#include <string>
#include <fstream>
#include <strstream>

using namespace std;

class PlayerScore
{
private:
	int		nScore;
	int		nround;
	string  strScore;
	string  strround;
public:
	PlayerScore();
	~PlayerScore();
	void SetScore(const int &score);
	void SetRound(const int &rounds);

	void SetScoreString(const string &score);
	void SetRoundString(const string &rounds);

	const int&GetScore();
	const int&GetRound();

	const string&GetScoreString();
	const string&GetRoundString();
};

#endif