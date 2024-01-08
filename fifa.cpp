// fifa.cpp : 
// 
// Symulator MŒ w pi³ce no¿nej.
// System pucharowy.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cctype>
#include<windows.h>

using namespace std;

//funkcja ustalenie ziarna dla losowania
void setRandom();

//intro 
void intro(string);

//losowanie liczby z przedzia³u
int getRandomInteger(int, int);

//losowanie par
void getRandomPairs(int* , int , int** , int , int, int );

//zamiana miejscami w tablicy
void swap(int&, int&);

//wyszukanie wolnego id w tabeli spotkania
int getNextIdGame(int**, int);

//wyœwietlenie wyników spotkania zakoñczone lub nierozegrane
void displayResults(string**, int, int);

//funkcja znajduj¹ca nazwê kraju wg id
string findNameById(vector<string>, int );

//funkcja zapisuj¹ca dane z tabeli results do tabeli wyniki
void saveResults(vector<string>, int**, string**, int);

//funkcja losuje wynik
void createResult(int*, int*);

//rzuty karne
void penalties(int&, int&);

//funkcja losuj¹ca wyniki
void createResults(int**, int, int*, int*,  int*);

//playoff znacznik gra/odpada
void setPlayOffTeam(int*, int);

//funkcja czy koniec turnieju
bool ifGameEnd(int, int);

//suma goli teamu w meczu  
int sumGoals(int*);

//wybór liczby dru¿yn
int getNumTeams();

//wczytanie dru¿yn z pliku
void importTeams(vector<string>&);

//wyœwietlenie dru¿yn do wyboru
void showTeamAtChoise(vector<string>,int);

//wskazanie teamow grajacy/ niegraj¹cy
void swapTeams(vector<string>&, int);

//ustawienie listy teamów graj¹cych
void setTeams(vector<string>&, int );

//utworzenie tabeli wyników string
string **createTableResultsString(int );

//utworzenie tabeli wyników int
int **createTableResultsInt(int );

//utworzenie tabeli status dry¿yn
int *createTableTeamStatus(int );

//obliczenie iloœci rund
int getRounds(int );

//dogrywka
void extraTime(int&, int&);

//koñcowa klasyfikacja podium
void finalRating(int*, vector<string>);

//---------------   MAIN  ------------------------

int main()
{
	string version = "ver. 1.0.6";
	setRandom();
	intro(version);
	int numTeams = getNumTeams();
	int numGames = numTeams;
	int teamsTotalNum; // LICZBA DRU¯YN Z PLIKU
	vector<string> teams;

	importTeams(teams);
	teamsTotalNum = teams.size();
	system("Color 0A");
	char option;
	// WYBRÓW DRY¯YN
	do{
		system("cls");
		intro(version);
		showTeamAtChoise(teams, numTeams);
		cout << "press S to SKIP or C to continue ( pick other teams)";
		cin >> option;
		if (toupper(option) == 'S')
		{
			break;
		}
		swapTeams(teams, teamsTotalNum);

	} while (toupper(option)!= 'F');

	setTeams(teams, numTeams);
	system("cls");
	showTeamAtChoise(teams, numTeams);


	// TURNIEJ

	//status w turnieju wartoœci to nr rund. Pó³fina³: przegrani + 1, finaliœci +2
	int *teamStatus = createTableTeamStatus(numTeams);

	string **resultsString = createTableResultsString(numGames);

	int **resultsInt = createTableResultsInt(numGames);
	int roundTotal = getRounds(numTeams);
	teamsTotalNum = teams.size();

	//----------------------------------------
		//WYNIK MECZU

	int *teamScore1 = new int[3]{ 0 };   //90min/dog/rz.k
	int *teamScore2 = new int[3]{ 0 };

	//----------------------------------------

	int round = 1;
	bool game = true;

	do {

		system("cls");
		intro(version);
		getRandomPairs(teamStatus, numTeams, resultsInt, numGames, round, roundTotal);
		saveResults(teams, resultsInt, resultsString, numGames);
		displayResults(resultsString, numGames, round);
		system("pause");
		cout << endl;
		createResults(resultsInt, numGames, teamScore1, teamScore2, teamStatus);
		saveResults(teams, resultsInt, resultsString, numGames);
		displayResults(resultsString, numGames, round);
		system("cls");
		intro(version);
		cout << endl;
		round++;
		game = ifGameEnd( round, roundTotal);
	} while (!game);


	system("cls");
	intro(version);
	displayResults(resultsString, numGames, round);

	//wyœwietlenie zwyciêzcy
	
	finalRating(teamStatus, teams);

	//----------------------------------------
	delete[] teamStatus;
	delete[] resultsString;
	delete[] resultsInt;
	delete[] teamScore1;
	delete[] teamScore2;
}

//-----------------NOWE FUNKCJE --------------------
int getNumTeams()
{
	int numTeams;
	do {
		cout << "ENTER THE NUMBER OF TEAMS. " << endl;
		cout << "ONLY ARE ALLOWED: 4,8,16,32" << endl;
		cin >> numTeams;
	} while (numTeams != 4 && numTeams != 8 && numTeams != 16 && numTeams != 32);
	return numTeams;
}

void importTeams(vector<string> &teams) {
	ifstream teamsInFile("teams.txt");
	string team;
	while (getline(teamsInFile,team)) {
		teams.push_back(team);
	}
}

void showTeamAtChoise(vector<string> teams, int numTeams) {
	for (int i = 0; i < teams.size(); i++)
	{
			
		if (i+1 == numTeams+1)
		{
			cout << "-----------" << endl;
		}
		cout << i+1 << " " << teams[i] << endl;
	}

	cout << endl;

}

void swapTeams( vector<string> &teams, int numTeams) {

	int num1, num2;
	do {
		cout << "ENTER THE NUMER OF TEAM IT PLAYS: ";
		cin >> num1;
		cout << "ENTER THE NUMER OF TEAM IT WON'T PLAY: ";
		cin >> num2;
	} while (num1<1 || num2 <1 || num1 >(numTeams + 1) || num2 >(numTeams + 1));
	
	swap(teams[num1-1], teams[num2-1]);
}

void setTeams(vector<string>& teams, int numTeams)
{
	do
	{
		teams.pop_back();
	} while (teams.size() > numTeams);
}

string **createTableResultsString(int numGames) {

	//tablica wyników   
	//  indeksy 0-3
	// played | team1 | team2 | wynik | round
	//0-not played not paired, 1- played, 2- not played but paired

	const int NUM_COLS = 5;
	string** resultsString = new string * [numGames];

	for (int i = 0; i < numGames; i++)
	{
		resultsString[i] = new string[NUM_COLS];

		for (int j = 0; j < NUM_COLS; j++)

		{
			resultsString[i][j] = "0"; // inicjalizacja 0
		}

	}

	return resultsString;
}

int **createTableResultsInt(int numGames) {

	// tablica wyników int
	// indeksy 0-8
	// played | team1 | team2 | wynik1|wynik2|dog1|dog2|rzk1|rzk2 |runda
	// played|id1|id2|score1|score2|ext1|ext2|plt1|plt2|round
	//0-not played not paired, 1- played, 2- not played but paired

	const int NUM_COLS = 10;
	int **resultsInt = new int *[numGames];
	for (int i = 0; i < numGames; i++)
	{
		resultsInt[i] = new int[NUM_COLS];
		for (int j = 0; j < NUM_COLS; j++)
		{
			resultsInt[i][j] = 0; // inicjalizacja 0
		}
	}

	return resultsInt;
}

int *createTableTeamStatus(int numTeams) {

	int *teamStatus = new int[numTeams];

	for (int i = 0; i < numTeams; i++)
	{
		teamStatus[i] = 1; // inicjalizacja 1 runda
	}

	return teamStatus;
}

int getRounds(int teamsCounter) {
	int rounds=0;
	switch (teamsCounter) {
	case 32:
		rounds = 6;
		break;
	case 16:
		rounds = 5;
		break;
	case 8:
		rounds = 4;
		break;
	case 4:
		rounds = 3;
		break;
	}
	return rounds;
}

//-------------------------------------------------
void setRandom() {
	unsigned seed = time(0);
	srand(seed);
}
void intro(string version) {
	system("Color 0B"); // DOMYŒLNY KOLOR

	cout <<  endl;
	cout << "-------WELCOME TO FIFA GAME ---------" << endl;
	cout << "-------------------------------------" << endl;
	cout << "------#####---#---#####-----#--------" << endl;
	cout << "------#-------#---#--------#-#-------" << endl;
	cout << "------#####---#---#####---#####------" << endl;
	cout << "------#-------#---#-------#---#------" << endl;
	cout << "------#-------#---#-------#---#------" << endl;
	cout << "-------------------------------------" << endl;
	cout << "-------------------------------------" << endl;
	cout <<  " " << version << endl;
	cout << endl;
}
int getRandomInteger(int min, int max) {	
	int rndInt = (rand() % (max - min + 1)) + min;
	return rndInt;
}
void swap(int& x, int& y) {

	int temp;
	temp = y;
	y = x;
	x = temp;
}
int getNextIdGame(int **resultsInt, int numGames) {
	int id = 0;
	while (id<numGames)
	{
		if (resultsInt[id][0] == 0)
		{
			break;
		}
		id++;
	}
	return id;
}
void getRandomPairs(int *teamStatus, int sizeTeam, int **resultsInt, int numGames, int round, int roundTotal) {

	vector<int>teamsToDraw; //INDEKSY DRU¯YN DO LOSOWANIA
	vector<int>teamsPaired; //PAROWANIE DRU¯YN 1-2 3-4 ETC
	
	// JE¯ELI TO NIE JEST PÓ£FINA£
	if (round <= roundTotal - 2)
	{
		for (int i = 0; i < sizeTeam; i++)
		{
			if (teamStatus[i] == round)
			{
				teamsToDraw.push_back(i);
			}
		}

		while (!teamsToDraw.empty()) {
			int rndindex = getRandomInteger(0, teamsToDraw.size() - 1);
			teamsPaired.push_back(teamsToDraw[rndindex]);
			swap(teamsToDraw[rndindex], teamsToDraw[teamsToDraw.size() - 1]);
			teamsToDraw.pop_back();
		}


		int k = getNextIdGame(resultsInt, numGames);


		//SKOJARZONE PARY WPROWADZAMY DO TABLICY RESULTS

		for (int i = 0; i < teamsPaired.size(); i = i + 2)
		{
			resultsInt[k][0] = 2;
			resultsInt[k][1] = teamsPaired[i];
			resultsInt[k][2] = teamsPaired[i + 1];
			resultsInt[k][9] = round;
			k++;
		}

	}

	//MECZ O 3
	else if (round == roundTotal - 1) {
		for (int i = 0; i < sizeTeam; i++)
		{
			if (teamStatus[i] == round)
			{
				teamsPaired.push_back(i);
			}
		}

		resultsInt[numGames- 2][0] = 2;
		resultsInt[numGames - 2][1] = teamsPaired[0];
		resultsInt[numGames - 2][2] = teamsPaired[1];
		resultsInt[numGames - 2][9] = round;
	}

	//FINAL 
	else {
		for (int i = 0; i < sizeTeam; i++)
		{
			if (teamStatus[i] == round + 1)
			{
				teamsPaired.push_back(i);
			}
		}

		resultsInt[numGames - 1][0] = 2;
		resultsInt[numGames - 1][1] = teamsPaired[0];
		resultsInt[numGames - 1][2] = teamsPaired[1];
		resultsInt[numGames - 1][9] = round;
	}
}
void displayResults(string **resultsString, int numGames, int roundTotal) {
	
	string round = resultsString[0][4];
	cout << "ROUND: " << round << endl;
	cout << "---------------------------------------------------------------" << endl;


	for (int i = 0; i < numGames; i++)
	{
	
		if (resultsString[i][1] != "0") {
			if (i > 0)
			{
				if (resultsString[i][4] != resultsString[i - 1][4])
				{
					cout << "ROUND: " << resultsString[i][4] << endl;
					cout << "---------------------------------------------------------------" << endl;

				}
			}

			string str1 = resultsString[i][1];
			string str2 = resultsString[i][2];
			string str3 = resultsString[i][3];

			cout << setw(10) << " " << setw(20) << right << str1 << " - " << str2 << " " << str3 << endl;

		}
	}
}
void saveResults(vector<string> teams,int **resultsInt, string **resultsString, int numGames) {
	
	for (int i = 0; i < numGames; i++)
	{
		if (resultsInt[i][0] != 0)
		{
			resultsString[i][0] = to_string(resultsInt[i][0]);
			resultsString[i][1] = findNameById(teams, resultsInt[i][1]);
			resultsString[i][2] = findNameById(teams, resultsInt[i][2]);
		

			//brak remisu
			if (resultsInt[i][3]!= resultsInt[i][4])
			{
				resultsString[i][3] = to_string(resultsInt[i][3]) + " : " + to_string(resultsInt[i][4]);
			}
			//remis
			else if (resultsInt[i][3] == resultsInt[i][4]){
				if (resultsInt[i][7] != resultsInt[i][8])
				{
					resultsString[i][3] = to_string(resultsInt[i][5]+ resultsInt[i][3]) + " : " + to_string(resultsInt[i][6]+ resultsInt[i][4]) +
					"(" + to_string(resultsInt[i][3]) + " : " + to_string(resultsInt[i][4]) + ")" +
						"p. " + to_string(resultsInt[i][7]) + " : " + to_string(resultsInt[i][8]);
				}
				else {
					resultsString[i][3] = to_string(resultsInt[i][5]+ resultsInt[i][3]) + " : " + to_string(resultsInt[i][6]+ resultsInt[i][4]) +
					"(" + to_string(resultsInt[i][3]) + " : " + to_string(resultsInt[i][4]) + ")";
						
				}
			}
			// zapisanie nr rundy
		
			if (i ==numGames-1)
			{
				resultsString[i][4] = "FINAL";
			}

			else if (i == numGames - 2)
			{
				resultsString[i][4] = "THIRD PLACE";
			}

			else {
				resultsString[i][4] = to_string(resultsInt[i][9]);
			}
		}
	}
}
string findNameById(vector<string> teams, int id) {
	return teams[id];
}
void createResult(int *teamScore1, int *teamScore2) {
	
	//wyzerowanie
	for (int i = 0; i < 3; i++)
	{
		teamScore1[i] = 0;
		teamScore2[i] = 0;
	}
	
	
		// 90 minut
		int scores[] = { 0,0,0,0,1,1,1,2,2,3,4,5 }; // TABLICA WYNIKÓW
	
		int index = getRandomInteger(0, 11);
		teamScore1[0] = scores[index];
		
		index = getRandomInteger(0, 11);	
		teamScore2[0] = scores[index];
	
		if (teamScore1[0] == teamScore2[0]) {
			// ET

			extraTime(teamScore1[1], teamScore2[1]);

			if (teamScore1[1] == teamScore2[1]) {
				penalties(teamScore1[2], teamScore2[2]);
			}

		}
	
		
	}
void extraTime(int &teamScore1, int &teamScore2) {

		int index;
		int scoresEt[] = { 0,0,0,0,0,0,0,0,1,1,1,2 }; // TABLICA WYNIKÓW
		index = getRandomInteger(0, 11);
		teamScore1 = scoresEt[index];

		index = getRandomInteger(0, 11);
		teamScore2 = scoresEt[index];

}

void penalties(int &scoreTeam1, int &scoreTeam2) {

	bool scores[] = { true,true,false,true,false,true,true,false,true,false,true }; // TABLICA WYNIKÓW
	int index;
	const int MAX_PEN = 5;
	
	int round = 1;
	int toScore13 = MAX_PEN;
	int toScore23 = MAX_PEN;

	do {

		index = scores[getRandomInteger(0, 10)];
		if (index) {
			scoreTeam1++;
		}

		toScore13--;

		if (scoreTeam2 + toScore23 < scoreTeam1)
		{
			break;
		}

		if (scoreTeam1 + toScore13 < scoreTeam2)
		{
			break;
		}

		index = scores[getRandomInteger(0, 9)];
		if (index) {
			scoreTeam2++;
	
		}

		toScore23--;

		if (scoreTeam2 + toScore23 < scoreTeam1)
		{
			break;
		}

		if (scoreTeam1 + toScore13 < scoreTeam2)
		{
			break;
		}

		round++;
	}

	while (round <= MAX_PEN);

	if (scoreTeam1 == scoreTeam2) {

		do {
			index = scores[getRandomInteger(0, 9)];
			if (index) {
				scoreTeam1++;
	
			}
		
			index = scores[getRandomInteger(0, 9)];
			if (index) {
				scoreTeam2++;
			}
		
			} while (scoreTeam1 == scoreTeam2);
	}


}
void createResults(int **resultsInt, int numGames, int *teamScore1, int* teamScore2, int *teamStatus) {
	for (int i = 0; i < numGames; i++)
	{
		if (resultsInt[i][0]!=2)
		{
			continue;
		}

		else
		{
			createResult(teamScore1, teamScore2);
			resultsInt[i][0] = 1;
			resultsInt[i][3] = teamScore1[0];
			resultsInt[i][4] = teamScore2[0];
			resultsInt[i][5] = teamScore1[1];
			resultsInt[i][6] = teamScore2[1];
			resultsInt[i][7] = teamScore1[2];
			resultsInt[i][8] = teamScore2[2];
			//wygrana1
			if (sumGoals(teamScore1) > sumGoals(teamScore2))
			{
				setPlayOffTeam(teamStatus, resultsInt[i][1]);
				// pó³fna³
				if (i == numGames - 3 || i == numGames - 4)
				{
					
					setPlayOffTeam(teamStatus, resultsInt[i][1]); //TRZYKROTNE DODANIE
					setPlayOffTeam(teamStatus, resultsInt[i][1]); //TRZYKROTNE DODANIE
					setPlayOffTeam(teamStatus, resultsInt[i][2]);
				}

			}
			//wygrana 2
			else if (sumGoals(teamScore1) < sumGoals(teamScore2))
			{
				setPlayOffTeam(teamStatus, resultsInt[i][2]);
				// pó³fna³
				if (i == numGames - 3 || i == numGames - 4)
				{
		
					setPlayOffTeam(teamStatus, resultsInt[i][2]);//TRZYKROTNE DODANIE
					setPlayOffTeam(teamStatus, resultsInt[i][2]);
					setPlayOffTeam(teamStatus, resultsInt[i][1]);
				}
			}
			//remis
			else {
				
			}
		}
	}
}
void setPlayOffTeam(int *teamStatus,  int id) {

	teamStatus[id] ++;
}
bool ifGameEnd( int round, int roundTotal) {

	bool gameEnd = false;

		if (roundTotal < round)
		{
			gameEnd = true;
		}
		return gameEnd;
}
int sumGoals(int *score)
{
	int sum = score[0] + score[1] + score[2];
	return sum;
}

void finalRating(int* teamStatus, vector<string> teams) {
	
	int firstPlace;
	firstPlace =  teamStatus[0];
	string podium[3] = { teams[0], teams[0], teams[0] };


	for (int i = 1; i < teams.size(); i++)
	{
		if (firstPlace < teamStatus[i])
		{
			firstPlace = teamStatus[i];
			podium[0] = teams[i];
		}

	}

	for (int i = 1; i < teams.size(); i++)
	{
		if (teamStatus[i] == firstPlace-1)
		{
			podium[1] = teams[i];
		}

		else if (teamStatus[i] == firstPlace - 2)
		{

			podium[2] = teams[i];
		}

	}

	cout << endl << "****************************************" << endl;
	cout << endl << " WORLD CHAMPION: " << podium[0] << endl;
	cout << endl << " SECOND PLACE: " << podium[1] << endl;
	cout << endl << " THIRD PLACE: " << podium[2] << endl;
	cout << endl << "****************************************" << endl;
}

