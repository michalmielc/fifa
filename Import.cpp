//#include "Team.h"
//#include "Import.h"
//#include <vector>
//using namespace std;
//
//void Import::importTeams(vector<Team>& teams) {
//
//	fstream teamsInFile("teams.txt", ios::in);
//	string line;
//	int id = 1;
//
//	if (teamsInFile)
//	{
//
//		while (getline(teamsInFile, line)) {
//
//			// reading line without comment
//			if (line.find('#') == string::npos)
//			{
//				Team t;
//				t.setId(id);
//				id++;
//				getTeamFromLine(t, line);
//				teams.push_back(t);
//			}
//		}
//	}
//
//	else
//	{
//		std::cout << "CANNOT LAUNCH THE GAME!";
//	}
//
//	teamsInFile.close();
//
//}
//
//void Import::getTeamFromLine(Team& t, string line) {
//
//	// readed line:
//	// Name | ShortName | Potential | Continent
//
//	int delPos = line.find('|');
//
//	t.setName(line.substr(0, delPos));
//	line = line.substr(delPos + 1, line.length() - delPos);
//
//	delPos = line.find('|');
//	t.setShortName(line.substr(0, delPos));
//	line = line.substr(delPos + 1, line.length() - delPos);
//
//	delPos = line.find('|');
//	t.setPotential(stoi(line));
//	line = line.substr(delPos + 1, line.length() - delPos);
//
//	t.setContinent(line);
//
//	//default
//	t.setQualified(false);
//
//}