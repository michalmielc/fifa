// FIFA 
// FOOTBALL SIMULATOR 
//------------------------

#include "TournamentSettings.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main() {

	int menuWindow = 0;
	int tourType = 0;
	Menu menu;
	TournamentSettings ts;

	do {
		system("cls");
		switch (menuWindow) {
			case -1:
				exit(EXIT_FAILURE);
				break;
			case 0:
				menu.intro("TEST 2.0.1");
				menu.getBackwardForward(menuWindow);
				cout << "VALUE: " << menuWindow;
				break;
			case 1:
				menu.displayTournamentTypes(tourType);
				ts.renewSettings(tourType);
				menu.getBackwardForward(menuWindow);
				break;
			case 2:
				menu.getBackwardForward(menuWindow);
				break;
		}
	} while ( menuWindow < 3);


}



// OLD VERSION

//#include <iomanip>
//#include "RandomSettings.h"
//#include "TournamentSettings.h"
//#include <vector>
//#include "Team.h"
// 
//#include "Import.h"

// DECLARATIONS

////
////wyœwietlanie dru¿yn
//void showTeamAtChoise(vector<Team>, vector<Team>, string );
//
//void showTeamAtChoiseByContinent(vector<Team> , string );
//
//
////wskazanie teamow grajacy/ niegraj¹cy
//void swapTeams(vector<Team>&, vector <Team>&);
//
////zamiana miejscami w tablicy
//void swap(int&, int&);



//---------------   MAIN  ------------------------
//------------------------------------------------
//int main()
//{
//	string version = "ver. 1.2.0";
//
//	RandomSettings rndSettings;
//
//	intro(version);
//
//	vector<Team> teams_temp, teams_qualified;
//
//	Import import;
//
//	import.importTeams(teams_temp);  // TEAMS IMPORT 
//
//	//MENU 1
//	TournamentSettings trnSettings;
//
//	char option;
//
//	string view = "ANY";
//
//	do {
//		system("cls");
//
//		intro(version);
//
//		cout << "\n-------------------------------------------------------- \n";
//		cout << "\n YOU NEED TO PICK: " << trnSettings.getNumTeams() << " TEAMS";
//		cout << "\n PICK TEAMS USING OPTIONS:";
//		cout << "\nA- VIEW ALL" << "| B- EUROPE | " << "C- CONBEMOL " << "| D- AFRICA " << "| E- ASIA " << "| F- CONCACAF " << "| G- OCEANIA";
//		cout << "\nS- SWAP TEAMS";
//		cout << "\nR- RESET TEAMS";
//		cout << "\nT- RANDOM TEAMS";
//		cout << "\nW- FORWARD";
//		cout << "\nQ- RETURN";
//		cout << "\n-------------------------------------------------------- \n"; 
//
//		showTeamAtChoise(teams_temp, teams_qualified, view);
//
//		cin >> option;
//
//	
//			if (toupper(option) == 'Q')
//			{
//				/*	trnSettings = nullptr;
//				* POPRAWIÆ KOD
//					delete trnSettings;
//					TournamentSettings* trnSettings = new TournamentSettings;*/
//			}
//
//			else if (toupper(option) == 'S')
//			{
//				swapTeams(teams_temp, teams_qualified);
//			}
//
//
//			else if (toupper(option) == 'R')
//			{
//				char c;
//				do {
//					cout << "DO YOU WANT TO REALLY RESET SEEDING? Y/N? ";
//					cin >> c;
//					if (toupper(c) == 'Y')
//					{
//						teams_temp.clear();
//						teams_qualified.clear();
//						import.importTeams(teams_temp);
//						break;
//					}
//
//				} while (toupper(c) == 'Y' || toupper(c) == 'N');
//
//			}
//
//
//			else if (toupper(option) == 'T')
//			{
//				// LOSOWANIE DRU¯YN
//			}
//
//			else if (toupper(option) == 'A')
//			{
//				view = "ANY";
//			}
//
//			else if (toupper(option) == 'B')
//			{
//				view = "EUROPE";
//			}
//
//			else if (toupper(option) == 'C')
//			{
//				view = "CONBEMOL";
//			}
//
//			else if (toupper(option) == 'D')
//			{
//				view = "AFRICA";
//			}
//
//			else if (toupper(option) == 'E')
//			{
//				view = "ASIA";
//			}
//
//			else if (toupper(option) == 'F')
//			{
//				view = "CONCACAF";
//			}
//
//			else if (toupper(option) == 'G')
//			{
//				view = "OCEANIA";
//			}
//
//		
//
//
//	} while ( toupper(option) != 'W' || toupper(option) !='Q');
//
//}
	// TUTAJ ZAKOÑCZY£EM -------------------------
// ------------------------------------------

	//Match *ptrMatch = createTableMatches(set->numGames);


	//do {

	//	system("cls");
	//	intro(version);
	//	getRandomPairs(teams, ptrMatch, set);
	//	displayResults(ptrMatch,set);

	//	system("pause");

	//	createResults(teams, ptrMatch, set, true);
	//	system("cls");


	//	intro(version);
	//	displayResults(ptrMatch, set);

	//	system("pause");

	//	set->currRound++;
	//	set->game = ifGameEnd( ptrMatch,set->numGames);
	//} while (!set->game);


	//system("cls");
	//intro(version);

	//displayResults(ptrMatch,set);

	//////wyœwietlenie zwyciêzcy
	//
	//finalRating( teams);

	//////----------------------------------------
	//
	//
	//delete set;
	//delete[] ptrMatch;



//-----------------DEFINITIONS --------------------

//
//void showTeamAtChoise(vector<Team> teamsTemp, vector<Team> teamsQualified, string continent) {
//
//	vector<string> displayedTeams;
//	string line;
//	int i = 0; //counter lines
//
//	
//	while (i < teamsTemp.size())
//	{
//		bool emptyLine = true;
//
//		if (continent == "ANY")
//		{
//			emptyLine = false;
//			line = teamsTemp[i].getStringId() + ". " + teamsTemp[i].getName();
//			line = line.append("				");
//		}
//
//		else
//		{
//			if (teamsTemp[i].getContinent() == continent)
//			{
//				emptyLine = false;
//				line = teamsTemp[i].getStringId() + ". " + teamsTemp[i].getName();
//				line = line.append("				");
//			}
//		}
//
//		if (!emptyLine) {
//			displayedTeams.push_back(line);
//		}
//
//		i++;
//	 }
//
//	i = 0;
//
//	while(i < teamsQualified.size())
//		{
//			if (i< displayedTeams.size())
//			{
//				displayedTeams[i] = displayedTeams[i].append(teamsQualified[i].getStringId() + ". " + teamsQualified[i].getName());
//
//			}
//
//			else
//			{
//				line = "				";
//				line.append(teamsQualified[i].getStringId() + ". " + teamsQualified[i].getName());
//				displayedTeams.push_back(line);
//			}
//			i++;
//		}
//
//	
//	
//
//	for (int j = 0; j < displayedTeams.size(); j++)
//		{
//			cout << displayedTeams[j] << endl;
//		}
//
//}
//
//void showTeamAtChoiseByContinent(vector<Team> teams,  string continent) {
//
//	for (int i = 0; i < teams.size(); i++)
//	{
//
//		if (continent=="ANY")
//		{
//			cout << i + 1 << " ";
//			teams[i].printTeam();
//		}
//
//		else if (teams[i].getContinent() == continent)
//		{
//			cout << i + 1 << " ";
//			teams[i].printTeam();
//		}
//
//	}
//
//}
//
//void swapTeams(vector<Team>& teamsTemp, vector<Team>& teamsQualified ) {
//
//	int num1, num2;
//	
//		cout << "ENTER THE NUMER OF TEAM WHICH WILL PLAY: ";
//		cin >> num1;
//		cout << "SEED WTH NUMBER: ";
//		cin >> num2;
//		int last = teamsTemp.size() - 1;
//		swap(teamsTemp[num1 - 1], teamsTemp[last]);
//		teamsTemp[last].setQualified(true);
//		teamsQualified.push_back(teamsTemp[last]);
//		teamsTemp.pop_back();
//}
//
//void swap(int& x, int& y) {
//
//	int temp;
//	temp = y;
//	y = x;
//	x = temp;
//}
//
//void setRandomQualifiers(RandomSettings rndSettings, int numTeams, vector<Team> teamsTemp, vector<Team> teamsQualified) {
//	int* ptr = rndSettings.createRandomOrderIndexes(numTeams);
//
//	for (int i = 0; i < numTeams; i++)
//	{
//		int last = teamsTemp.size() - 1;
//		swap(teamsTemp[num1 - 1], teamsTemp[last]);
//		teamsTemp[last].setQualified(true);
//		teamsQualified.push_back(teamsTemp[last]);
//		teamsTemp.pop_back();
//	}
//
//	delete[]ptr;
//
//}