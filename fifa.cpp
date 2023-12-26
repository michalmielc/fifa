// fifa.cpp : 
// 
// Symulator MŒ w pi³ce no¿nej.
// System pucharowy.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

//funkcja ustalenie ziarna dla losowania
void setRandom();

//intro 
void intro();

//losowanie liczby z przedzia³u
int getRandomInteger(int, int);

//losowanie par
void getRandomPairs(bool[], int, int[][10], int);

//zamiana miejscami w tablicy
void swap(int&, int&);

//wyszukanie wolnego id w tabeli spotkania
int getNextIdGame(int[][10], int);

//wyœwietlenie wyników spotkania zakoñczone lub nierozegrane
void displayResults(string[][4], int);

//funkcja znajduj¹ca nazwê kraju wg id
string findNameById(string [], int );

//funkcja zapisuj¹ca dane z tabeli results do tabeli wyniki
void saveResults(string[], int[][10], string[][4], int);

//funkcja losuje wynik
void createResult(int&, int&, int&, int&, int&, int&);

//rzuty karne
void penalties(int&, int&);

//funkcja losuj¹ca wyniki
void createResults(int[][10], int, int&, int&, int&, int&, int&, int&, bool[]);

//playoff znacznik gra/odpada
void setPlayOffTeam(bool[], int);

//funkcja czy koniec turnieju
bool ifGameEnd(bool[], int);

void showTables(string resultsString[7][4], int resultsInt[7][10], bool teamStatus[8]) {

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


int main()
{
	setRandom();
	const int NUM_TEAMS = 8;
	const int NUM_GAMES = 7;
	string teams[NUM_TEAMS] = {
		"BRAZIL", "ARGENTINA", "ITALY", "FRANCE", "GERMANY", "MEXICO", "EGYPT", "JAPAN" };
	//status w turnieju
	bool teamStatus[NUM_TEAMS] = { true,true, true, true, true, true, true, true };
	//tablica wyników played | team1 | team2 | wynik
	//0-not played not paired, 1- played, 2- not played but paired
	string resultsString[7][4] = { {"0"},{"0"},{"0"},{"0"},{"0"},{"0"},{"0"} };
	// tablica wyników int
	// played|id1|id2|score1|score2|ext1|ext2|plt1|plt2|1x2|
	//0-not played not paired, 1- played, 2- not played but paired
	int resultsInt[7][10] = { {0},{0},{0},{0},{0},{0},{0} };

	//WYNIK MECZU
	int score11 = 0, score21 = 0; // wynik 90min
	int score12 = 0, score22 = 0; // dogrywka
	int score13 = 0, score23 = 0; // rzuty karne
	int round = 1;
	bool game = true;


	do {

		system("cls");
		intro();
	//	showTables(resultsString, resultsInt, teamStatus);
		cout << "ROUND: " << round << endl;
		cout << "-------------------------------------------"<< endl;
		system("pause");
		getRandomPairs(teamStatus, NUM_TEAMS, resultsInt, NUM_GAMES);
		saveResults(teams, resultsInt, resultsString, NUM_GAMES);
		displayResults(resultsString, NUM_GAMES);
		system("pause");
		cout << endl;
	    createResults(resultsInt, NUM_GAMES, score11, score21, score12, score22, score13, score23, teamStatus);
		saveResults(teams, resultsInt, resultsString, NUM_GAMES);
	  	displayResults(resultsString, NUM_GAMES);
		cout << endl;
	//	showTables(resultsString, resultsInt, teamStatus);
		system("pause");
		game = ifGameEnd(teamStatus, NUM_TEAMS);
		round++;
	}
	while (!game);
	
}

void setRandom() {
	unsigned seed = time(0);
	srand(seed);
}
void intro() {
	cout << "-------WELCOME TO FIFA GAME ---------" << endl;
	cout << "-------------------------------------" << endl;
	cout << "------#####---#---#####-----#--------" << endl;
	cout << "------#-------#---#--------#-#-------" << endl;
	cout << "------#####---#---#####---#####------" << endl;
	cout << "------#-------#---#-------#---#------" << endl;
	cout << "------#-------#---#-------#---#------" << endl;
	cout << "-------------------------------------" << endl;
	cout << "ver. 1.0" << endl;
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
int getNextIdGame(int resultsInt[][10], int resultsIntSize) {
	int id = 0;
	while (resultsInt[id][0] != 0)
	{
		id++;
	}
	return id;
}
void getRandomPairs(bool teamStatus[], int sizeTeam, int resultsInt[][10],int resultsIntSize) {

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
		k++;
	}

}
void displayResults(string resultsString[][4], int games) {
	for (int i = 0; i < games; i++)
	{
		if (resultsString[i][0]!="0")
		{
		//	cout << resultsString[i][1] << " " << resultsString[i][2] << " " << resultsString[i][3] << endl;
		}

		cout << resultsString[i][1] << " " << resultsString[i][2] << " " << resultsString[i][3] << endl;

	}
}
void saveResults(string teams[] ,int resultsInt[][10], string resultsString[][4], int games) {
	for (int i = 0; i < games; i++)
	{
		if (resultsInt[i][0] != 0)
		{
			resultsString[i][0] = to_string(resultsInt[i][0]);
			resultsString[i][1] = findNameById(teams, resultsInt[i][1]);
			resultsString[i][2] = findNameById(teams, resultsInt[i][2]);
			
			if (resultsInt[i][3]!= resultsInt[i][4])
			{
				resultsString[i][3] = to_string(resultsInt[i][3]) + " : " + to_string(resultsInt[i][4]);
			}

			else if (resultsInt[i][3] == resultsInt[i][4]){
				if (resultsInt[i][7] != resultsInt[i][8])
				{
					resultsString[i][3] = to_string(resultsInt[i][5]) + " : " + to_string(resultsInt[i][6]) +
					"(" + to_string(resultsInt[i][3]) + " : " + to_string(resultsInt[i][4]) + ")" +
						"p. " + to_string(resultsInt[i][7]) + " : " + to_string(resultsInt[i][8]);
				}
				else {
					resultsString[i][3] = to_string(resultsInt[i][5]) + " : " + to_string(resultsInt[i][6]) +
					"(" + to_string(resultsInt[i][3]) + " : " + to_string(resultsInt[i][4]) + ")";
						
				}
			}
			

		}
	}
}
string findNameById(string teams[], int id) {
	return teams[id];
}
void createResult(int& score11, int& score12, int& score21, int& score22, int& score13, int& score23) {
	
		score11 = score21 =  score12 =  score22 = score13 = score23 = 0; // wyzerowanie
	
		// 90 minut
		int scores[] = { 0,0,0,0,1,1,1,2,2,3,4,5 }; // TABLICA WYNIKÓW
	
		int index = getRandomInteger(0, 11);
		score11 = scores[index];
		
		index = getRandomInteger(0, 11);	
		score21 = scores[index];
	
		if (score11 == score21) {
			// ET
			int scoresEt[] = { 0,0,0,0,0,0,0,0,1,1,1,2 }; // TABLICA WYNIKÓW
			index = getRandomInteger(0, 11);
			score12 = scoresEt[index];

			index = getRandomInteger(0, 11);
			score22 = scoresEt[index];

			if (score12 == score22) {
				penalties(score13, score23);
			}

		}
	
		
	}
void penalties(int& score13, int& score23) {

	bool scores[] = { true,true,false,true, false,true,true,false,true,false,true,true,false }; // TABLICA WYNIKÓW
	int index;
	const int MAX_PEN = 5;
	
	int round = 1;
	int toScore13 = MAX_PEN;
	int toScore23 = MAX_PEN;

	do {
		index = getRandomInteger(0, 12);
		if (index) {
			score13++;
		}

		toScore13--;

		if (score23 + toScore23 < score13)
		{
			break;
		}

		if (score13 + toScore13 < score23)
		{
			break;
		}

		index = getRandomInteger(0, 9);
		if (index) {
			score23++;
	
		}

		toScore23--;

		if (score23 + toScore23 < score13)
		{
			break;
		}

		if (score13 + toScore13 < score23)
		{
			break;
		}

		round++;
	}

	while (round <= MAX_PEN);

	if (score13 == score23) {

		do {
			index = getRandomInteger(0, 9);
			if (index) {
				score13++;
	
			}
		
			index = getRandomInteger(0, 9);
			if (index) {
				score23++;
			}
		
			} while (score13 == score23);
	}


}
void createResults(int resultsInt[7][10], int size, int &score11, int &score21, int &score12, int &score22, int &score13, int &score23, bool teamStatus[]) {
	for (int i = 0; i < size; i++)
	{
		if (resultsInt[i][0]!=2)
		{
			continue	;
		}

		else
		{
			createResult(score11, score12, score21, score22, score13, score23);
			resultsInt[i][0] = 1;
			resultsInt[i][3] = score11;
			resultsInt[i][4] = score21;
			resultsInt[i][5] = score12;
			resultsInt[i][6] = score22;
			resultsInt[i][7] = score13;
			resultsInt[i][8] = score23;
			//wygrana1
			if (score11 + score12 + score13 > score21 + score22 + score23)
			{
				resultsInt[i][9] = 1;
				setPlayOffTeam(teamStatus, resultsInt[i][2]);
			}
			//wygrana 2
			else if (score11 + score12 + score13 < score21 + score22 + score23)
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


