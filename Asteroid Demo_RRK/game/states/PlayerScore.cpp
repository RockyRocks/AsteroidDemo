#include "PlayerScore.h"

PlayerScore::PlayerScore():nScore(0),nround(0),strScore("00000"),strround("0")
{

}

PlayerScore::~PlayerScore()
{

}

void PlayerScore::SetScore(const int &score)
{
	nScore = score;
}
void PlayerScore::SetRound(const int &rounds)
{
	nround = rounds;
}
const int& PlayerScore::GetScore()
{
	return nScore;
}
const int& PlayerScore::GetRound()
{
	return nround;
}

void PlayerScore::SetScoreString(const string &score)
{
	strScore = score;
}
void PlayerScore::SetRoundString(const string &rounds)
{
	strround = rounds;
}

const string&PlayerScore::GetScoreString()
{
	return strScore;
}
const string&PlayerScore::GetRoundString()
{
	return strround;
}