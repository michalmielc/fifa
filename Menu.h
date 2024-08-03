#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::setw;

class Menu {

private:

public:

	Menu() {

	}
	void intro(string version) {
	system("Color 0B"); // DOMYŒLNY KOLOR
	emptyLines(3);
	cout << setw(70) << "----------------WELCOME TO FIFA GAME ------------------" << endl;
	cout << setw(70) << "-------------------------------------------------------" << endl;
	cout << setw(70) << "----------------#####---#---#####-----#----------------" << endl;
	cout << setw(70) << "----------------#-------#---#--------#-#---------------" << endl;
	cout << setw(70) << "----------------#####---#---#####---#####--------------" << endl;
	cout << setw(70) << "----------------#-------#---#-------#---#--------------" << endl;
	cout << setw(70) << "----------------#-------#---#-------#---#--------------" << endl;
	cout << setw(70) << "-------------------------------------------------------" << endl;
	cout << setw(70) << "-------------------------------------------------------" << endl;
	cout << setw(70) << "-------------------------------------------------------" << endl;
	emptyLines(2);
	cout << version << endl;
}

	void emptyLines(int lines) {
		for (int i = 0; i < lines; i++)
		{
			cout << "\n";
		}
	}

	// it returns variant of tournament
	void  displayTournamentTypes(int & tourType) {

		emptyLines(1);

		do {
			cout << setw(0);
			cout << "**********************************************************" << endl;
			cout << setw(50) << " CHOOSE TYPE OF TOURNAMENT:                 " << endl;
			cout << setw(50) << " 1. PLAY OFF | BEST OF 4,8,16,32,64         " << endl;
			cout << setw(50) << " 2. 8 TEAMS - 2 GROUPS X 4  | BEST OF 4  ***" << endl;
			cout << setw(50) << " 3. 10 TEAMS - 2 GROUPS X 5 | BEST OF 4  ***" << endl;
			cout << setw(50) << " 4. 12 TEAMS - 4 GROUPS X 3 | BEST OF 8  ***" << endl;
			cout << setw(50) << " 5. 16 TEAMS - 4 GROUPS X 4 | BEST OF 8  ***" << endl;
			cout << setw(50) << " 6. 20 TEAMS - 4 GROUPS X 5 | BEST OF 8  ***" << endl;
			cout << setw(50) << " 7. 24 TEAMS - 6 GROUPS X 4 | BEST OF 16 ***" << endl;
			cout << setw(50) << " 8. 32 TEMAS - 8 GROUPS X 4 | BEST OF 16 ***" << endl;
			cout << setw(50) << " 9. QUIT GAME ---------------------------***" << endl;
			cout << "**********************************************************" << endl;

			do {
				cout << "TYPE NUM 1-9: ";
				cin >> tourType;
				if (cin.fail()) {
					cin.clear(); 
					cin.ignore(); 
				}
			} while (tourType<1 || tourType >9);
			
				// END OF GAME
			if (tourType == 9)
			{
				exit(EXIT_FAILURE);
			}

		} while (tourType < 1 || tourType >9);

	}

	// it returns num of teams at playoff tournament
	int  displayNumTeamsPlayOff() {

		emptyLines(1);

		int numTeams = 0;

		do {
			cout << "YOU'VE CHOOSEN PLAY OFF \n";
			cout << "ENTER THE NUMBER OF TEAMS. " << endl;
			cout << "ONLY ARE ALLOWED: 4,8,16,32,64" << endl;
			cin >> numTeams;
		} while (numTeams % 4 != 0 && numTeams < 65 && numTeams >3);

		return numTeams;
	}

	// << B- BACK  FORWARD-F >>
	void getBackwardForward(int& menuWindow) {
		// << B- BACK  FORWARD-F >>
		char option;
		do {
			cout << "<< B- BACK  FORWARD-F >> \n";
			cin >> option;
			if (toupper(option) == 'B')
			{
				menuWindow--;
			}
			else if (toupper(option) == 'F') {
				menuWindow++;
			}
		} while (toupper(option) != 'B' && toupper(option) != 'F');
	}
};

#endif // !MENU_H
