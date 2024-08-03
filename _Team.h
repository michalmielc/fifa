#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <iostream>
#include "TeamStats.h"
#include "Import.h"
using namespace std;


class Team {
private:
	int id;
	string name;
	string shortName;
	int potential; // si³a dru¿yny
	TeamStats stats;
	string continent;
	bool qualified;

public:


	friend void Import::importTeams(vector<Team>&);

	void printTeam() {
		cout << getName() << " " << getShortName() << " " << getPotential() << " " << getContinent() << endl;
	}

	void setId(int i) {
		id = i;
	}

	void setName(string n) {
		name= n;
	}

	void setShortName(string n) {
		shortName = n;
	}

	void setPotential(int p) {
		potential = p;
	}

	void setContinent(string c) {
		continent = c;
	}

	void setQualified(bool q) {
		qualified = q;
	}

	bool getQualified() const {
		return qualified;
	}

	int getId() const {
		return id;
	}

	string getStringId() const {
		return to_string(id);
	}

	string getName() const {
		return name;
	}

	string getShortName() const {
		return shortName;
	}

	int getPotential() const {
		return potential;
	}

	string getContinent() const {
		return continent;
	}

};

#endif // !TEAM_H

