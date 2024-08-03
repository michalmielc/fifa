#ifndef TEAMSTATS_H
#define TEAMSTATS_H

class TeamStats {

private:
	bool playing;
	int round;
	int matches;
	int points;
	int wins;
	int draws;
	int losts;
	int sGoals;
	int lGoals;
public:

	void setPlaying(bool p) {
		playing = p;
	}

	void setRound(int r) {
		round = r;
	}

	void setMatches(int m) {
		matches = m;
	}

	void setPoints(int p) {
		points = p;
	}

	void setWins(int w) {
		wins = w;
	}

	void setDraws(int d) {
		draws = d;
	}

	void setLosts(int l) {
		losts = l;
	}

	void setScoredGoals(int s) {
		sGoals =s;
	}

	void setLostGoals(int l) {
		lGoals = l;
	}

	bool getPlaying() const {
		return playing;
	}

	int getRound() const {
		return round;
	}

	int getMatches() const{
		return matches;
	}

	int getPoints() const {
		return points;
	}

	int getWins() const {
		return wins;
	}

	int getDraws() const {
		return draws;
	}
	int getLosts() const {
		return losts;
	};
	int getScoredGoals() const {
		return sGoals;
	}
	int getLostGoals() const {
		return lGoals;
	}
};
#endif // !TEAMSTATS_H


