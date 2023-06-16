//Header File for the Player Class

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
using namespace std;

class Player {
private:
	string firstName, lastName, fullName;
	char symbol;
	int wins, losses, draws;

public:
	Player()
	{
		firstName = " ";
		lastName = " ";
		fullName = " ";
		symbol = ' ';
		wins = 0;
		losses = 0;
		draws = 0;
	}

	~Player()
	{

	}

	string getFirstName() const
	{
		return firstName;
	}

	string getLastName() const
	{
		return lastName;
	}

	string getFullName() const
	{
		return fullName;
	}

	char getSymbol() const
	{
		return symbol;
	}

	int getWins() const
	{
		return wins;
	}

	int getLosses() const
	{
		return losses;
	}

	int getDraws() const
	{
		return draws;
	}

	void setFirstName(string new_first)
	{
		firstName = new_first;
	}

	void setLastName(string new_last)
	{
		lastName = new_last;
			
	}

	void setFullName(string new_first, string new_last)
	{
		fullName = new_first + " " + new_last;
	}

	void setSymbol(char new_sym)
	{
		symbol = new_sym;
	}

	void win()
	{
		++wins;
	}

	void loss()
	{
		++losses;
	}

	void draw()
	{
		++draws;
	}
};

#endif