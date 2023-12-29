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

using namespace std;

//funkcja ustalenie ziarna dla losowania
void setRandom();

//intro 
void intro(string);

//losowanie liczby z przedzia³u
int getRandomInteger(int, int);

//losowanie par
void getRandomPairs(bool[], int, int[][11], int, int);

//zamiana miejscami w tablicy
void swap(int&, int&);

//wyszukanie wolnego id w tabeli spotkania
int getNextIdGame(int[][11], int);

//wyœwietlenie wyników spotkania zakoñczone lub nierozegrane
void displayResults(string[][5], int, int);

//funkcja znajduj¹ca nazwê kraju wg id
string findNameById(string [], int );

//funkcja zapisuj¹ca dane z tabeli results do tabeli wyniki
void saveResults(string[], int[][11], string[][5], int);

//funkcja losuje wynik
void createResult(int [3], int [3]);

//rzuty karne
void penalties(int&, int&);

//funkcja losuj¹ca wyniki
void createResults(int[7][11], int, int[], int[],  bool[]);

//playoff znacznik gra/odpada
void setPlayOffTeam(bool[], int);

//funkcja czy koniec turnieju
bool ifGameEnd(bool[], int);

//informacje techniczne, zawartoœæ tabel
void showTables(string resultsString[7][4], int resultsInt[7][11], bool teamStatus[8]) {

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << resultsString[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << resultsInt[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	for (int j = 0; j < 8; j++)
	{
		cout << teamStatus[j] << " ";
	}
	cout << endl;
}

//suma goli teamu w meczu  
int sumGoals(int[]);

int main()
{
	string version = "1.0.3";
	setRandom();
	const int NUM_TEAMS = 8;
	const int NUM_GAMES = 7;
	string teams[NUM_TEAMS] = {
		"BRAZIL", "ARGENTINA", "ITALY", "FRANCE", "GERMANY", "MEXICO", "EGYPT", "JAPAN" };
	//status w turnieju
	bool teamStatus[NUM_TEAMS] = { true,true, true, true, true, true, true, true };
	//tablica wyników played | team1 | team2 | wynik 
	//0-not played not paired, 1- played, 2- not played but paired
	string resultsString[NUM_GAMES][5] = { {"0"},{"0"},{"0"},{"0"},{"0"},{"0"},{"0"} };
	// tablica wyników int
	// played|id1|id2|score1|score2|ext1|ext2|plt1|plt2|1x2|| runda
	//0-not played not paired, 1- played, 2- not played but paired
	int resultsInt[NUM_GAMES][11] = { {0},{0},{0},{0},{0},{0},{0} };

	//WYNIK MECZU
	//int score11 = 0, score21 = 0; // wynik 90min
	//int score12 = 0, score22 = 0; // dogrywka
	//int score13 = 0, score23 = 0; // rzuty karne

	int teamScore1[3] = { 0,0,0 };  // wynik 90min/dogrywka/rz. karne
	int teamScore2[3] = { 0,0,0 };

	int round = 1;
	bool game = true;

	do {

		system("cls");
		intro(version);
	//	showTables(resultsString, resultsInt, teamStatus);

		getRandomPairs(teamStatus, NUM_TEAMS, resultsInt, NUM_GAMES, round);
		saveResults(teams, resultsInt, resultsString, NUM_GAMES);
		displayResults(resultsString, NUM_GAMES, round);
		system("pause");
		cout << endl;
	    createResults(resultsInt, NUM_GAMES, teamScore1, teamScore2, teamStatus);
		saveResults(teams, resultsInt, resultsString, NUM_GAMES);
	  	displayResults(resultsString, NUM_GAMES, round);
		system("cls");
		intro(version);
		cout << endl;
	//	showTables(resultsString, resultsInt, teamStatus);
		game = ifGameEnd(teamStatus, NUM_TEAMS);
		round++;
	}
	while (!game);

	round--;
	system("cls");
	intro(version);
	displayResults(resultsString, NUM_GAMES, round);

	//wyœwietlenie zwyciêzcy
	int i = 0;
	for (auto winner: teamStatus)
	{
		if (winner)
		{
			cout << endl << "****************************************" << endl;
			cout << endl << " WORLD CHAMPION: " << teams[i] << endl;
			cout << endl << "****************************************" << endl;
			break;
		}
		i++;
	}

	
}

void setRandom() {
	unsigned seed = time(0);
	srand(seed);
}
void intro(string version) {
	cout << "-------WELCOME TO FIFA GAME ---------" << endl;
	cout << "-------------------------------------" << endl;
	cout << "------#####---#---#####-----#--------" << endl;
	cout << "------#-------#---#--------#-#-------" << endl;
	cout << "------#####---#---#####---#####------" << endl;
	cout << "------#-------#---#-------#---#------" << endl;
	cout << "------#-------#---#-------#---#------" << endl;
	cout << "-------------------------------------" << endl;
	cout << "-------------------------------------" << endl;
	cout << version << endl;
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
int getNextIdGame(int resultsInt[][11], int resultsIntSize) {
	int id = 0;
	while (resultsInt[id][0] != 0)
	{
		id++;
	}
	return id;
}
void getRandomPairs(bool teamStatus[], int sizeTeam, int resultsInt[][11],int resultsIntSize, int round) {

	vector<int>teamsToDraw; //INDEKSY DRU¯YN DO LOSOWANIA
	vector<int>teamsPaired; //PAROWANIE DRU¯YN 1-2 3-4 ETC

	for (int i = 0; i < sizeTeam; i++)
	{
		if (teamStatus[i])
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

	cout << endl;
	int k = getNextIdGame(resultsInt, resultsIntSize);
	
	//SKOJARZONE PARY WPROWADZAMY DO TABLICY RESULTS

	for (int i = 0; i < teamsPaired.size(); i=i+2)
	{
		resultsInt[k][0] = 2;
		resultsInt[k][1] = teamsPaired[i];
		resultsInt[k][2] = teamsPaired[i + 1];
		resultsInt[k][10] = round;

		k++;
	}

}
void displayResults(string resultsString[][5], int games, int round) {
	
	cout << "ROUND: " << round << endl;
	cout << "-------------------------------------------" << endl;
	
	for (int i = 0; i < games; i++)
	{
		if (resultsString[i][0]!="0")
		{
		//	cout << resultsString[i][1] << " " << resultsString[i][2] << " " << resultsString[i][3] << endl;
		}

		cout << setw(20);
		cout << left << resultsString[i][4] << " " << right << resultsString[i][1] << " " << left << resultsString[i][2] << " \t\t" << left << resultsString[i][3] << endl;

	}
}
void saveResults(string teams[] ,int resultsInt[][11], string resultsString[][5], int games) {
	for (int i = 0; i < games; i++)
	{
		if (resultsInt[i][0] != 0)
		{
			resultsString[i][0] = to_string(resultsInt[i][0]);
			resultsString[i][1] = findNameById(teams, resultsInt[i][1]);
			resultsString[i][2] = findNameById(teams, resultsInt[i][2]);
		/*	if (i == games-2)
			{
				resultsString[i][4] = "THIRD PLACE";
			}*/
			 if (i == games-1)
			{
				resultsString[i][4] = "FINAL";
			}
			else {
				resultsString[i][4] = "Round " + to_string(resultsInt[i][10]);
			}

			
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
			

		}
	}
}
string findNameById(string teams[], int id) {
	return teams[id];
}
void createResult(int teamScore1[3], int teamScore2[3]) {
	
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
			int scoresEt[] = { 0,0,0,0,0,0,0,0,1,1,1,2 }; // TABLICA WYNIKÓW
			index = getRandomInteger(0, 11);
			teamScore1[1] = scoresEt[index];

			index = getRandomInteger(0, 11);
			teamScore2[1] = scoresEt[index];

			if (teamScore1[1] == teamScore2[1]) {
				penalties(teamScore1[2], teamScore2[2]);
			}

		}
	
		
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
void createResults(int resultsInt[7][11], int size, int teamScore1[3], int teamScore2[3], bool teamStatus[]) {
	for (int i = 0; i < size; i++)
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
				resultsInt[i][9] = 1;
				setPlayOffTeam(teamStatus, resultsInt[i][2]);
			}
			//wygrana 2
			else if (sumGoals(teamScore1) < sumGoals(teamScore2))
			{
				resultsInt[i][9] = 2;
				setPlayOffTeam(teamStatus, resultsInt[i][1]);
			}
			//remis
			else {
				resultsInt[i][9] = 0;
			}
		}
	}
}
void setPlayOffTeam(bool teamStatus[],  int id) {
	teamStatus[id] = false;
}
bool ifGameEnd(bool teamStatus[], int size) {

	bool gameEnd = true;
	int k = 0;
	int playing = 0;
	
	while (k<size && playing <2) {
		if (teamStatus[k])
		{
			playing++;
		}
		k++;
		}
		
	if (playing >= 2)
	{
		gameEnd = false;
	}
	return gameEnd;
}
int sumGoals(int score[])
{
	int sum = score[0] + score[1] + score[2];
	return sum;
}
