#ifndef IMPORT_H
#define IMPORT_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Team;

class Import {

public:

	void importTeams(vector<Team>& teams);

	void getTeamFromLine(Team& t, string line);

};

#endif // !IMPORT_H
