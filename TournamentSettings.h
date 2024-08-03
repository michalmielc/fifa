#ifndef TOURNAMENTSETTINGS_H
#define TOURNAMENTSETTINGS_H

// --- TYPE OF TOURNAMENT 

#include "Menu.h"

typedef enum TOURNAMENT_TYPE {
	PLAYOFF = 1,GROUP8,	GROUP10, GROUP12,
	GROUP16, GROUP20, GROUP24, 	GROUP32 };

class TournamentSettings  {

private:

	Menu menu;
	TOURNAMENT_TYPE tType; // tournament type
	int numTeams; // 
	int numGames;
	int numRounds;
	int currRound;
	bool game; // if game is still going on

public:

	TournamentSettings()
	{
		tType = TOURNAMENT_TYPE::PLAYOFF;
		game = true;
		currRound = 1;
		numTeams = 0; 
		numGames = 0;
		numRounds = 0;

		//setTournamentType();
		//setNumTeams();
		//setNumGames();
		//setNumRounds();
	
	}

	void renewSettings(int tourType)

	{
		tType = TOURNAMENT_TYPE::PLAYOFF;
		game = true;
		currRound = 1;
		numTeams = 0; // 
		numGames = 0;
		numRounds = 0;


		setTournamentType( tourType);
		setNumTeams();
		setNumGames();
		setNumRounds();

	}

	void setGame(bool g) {
		game = g;
	}

	void setNumTeams() {

		int nTeams=0;
		switch(tType)
		{
			case PLAYOFF:
				numTeams = menu.displayNumTeamsPlayOff();
				break;
			case GROUP8:
				numTeams = 8;
				break;
			case GROUP10:
				numTeams = 10;
				break;
			case GROUP12:
				numTeams = 12;
				break;
			case GROUP16:
				numTeams = 16;
				break;
			case GROUP20:
				numTeams = 20;
				break;
			case GROUP24:
				numTeams = 24;
				break;
			case GROUP32:
				numTeams = 32;
				break;
		}

	}

	void setNumGames() 
	{
		switch (tType)
		{
		case PLAYOFF:
			numGames = numTeams;
			break;
		case GROUP8:
			numGames = 16;
			break;
		case GROUP10:
			numGames = 28;
			break;
		case GROUP12:
			numGames = 20;
			break;
		case GROUP16:
			numGames = 32;
			break;
		case GROUP20:
			numGames = 48;
			break;
		case GROUP24:
			numGames = 52;
			break;
		case GROUP32:
			numGames = 64;
			break;
		}
	}

	void setNumRounds() {

		switch (tType)
		{
		case PLAYOFF:
			if (numTeams==64)
			{
				numRounds = 7;
			}
			else if (numTeams == 32)
			{
				numRounds = 6;
			}
			else if (numTeams == 16)
			{
				numRounds = 5;
			}
			else if (numTeams == 8)
			{
				numRounds = 4;
			}
			else if (numTeams == 4)
			{
				numRounds = 3;
			}
			break;
		case GROUP8:
			numRounds = 4;
			break;
		case GROUP10:
			numGames = 4;
			break;
		case GROUP12:
			numGames = 5;
			break;
		case GROUP16:
			numGames = 5;
			break;
		case GROUP20:
			numGames = 5;
			break;
		case GROUP24:
			numGames = 6;
			break;
		case GROUP32:
			numGames = 6;
			break;
		}
	}

	void setTournamentType(int tourType) {

		switch (tourType) {
		case 1:
			tType = PLAYOFF;
			break;
		case 2:
			tType = GROUP8;
			break;
		case 3:
			tType = GROUP10;
			break;
		case 4:
			tType = GROUP12;
			break;
		case 5:
			tType = GROUP16;
			break;
		case 6:
			tType = GROUP20;
			break;
		case 7:
			tType = GROUP24;
			break;
		case 8:
			tType = GROUP32;
			break;
		default:
			break;
		}
	}

	bool getGame() const {

		return game;
	}

	int getNumTeams() const {
		return numTeams;
	}

	int getNumGames() const {
		return numGames;
	}

	int getNumRounds() const {
		return numRounds;
	}

	TOURNAMENT_TYPE getTournamentType() const {
		return tType;
	}

};

#endif // !TOURNAMENTSETTINGS_H
