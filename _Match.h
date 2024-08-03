#ifndef MATCH_H
#define MATCH_H


#include<string>
using namespace std;

class Match {
	
private:
		bool played;
		bool paired;
		int id1;
		int id2;
		string name1;
		string name2;
		string sName1;
		string sName2;
		string result ; // end result formatted 
		int fullScore1 ; // final score incl extra time 
		int fullScore2;
		int score1;
		int score2 ;
		int ext1 ;
		int ext2 ;
		int plt1 ;
		int plt2 ;
		int round;
public:
	Match()
	{
		// DOKOÑCZYÆ
		 played = false;
		 paired = false;
		 id1;
		 id2;
		 name1;
		 name2;
		 sName1;
		 sName2;
		 result = "0:0"; // end result formatted 
		 fullScore1 = 0; // final score incl extra time 
		 fullScore2 = 0;
		 score1 = 0;
		 score2 = 0;
		 ext1 = 0;
		 ext2 = 0;
		 plt1 = 0;
		 plt2 = 0;
		 round=0;

	}
	//SET RESULT AS FORMAT - NAPISAC FUNKCJÊ
	// SET Round promotion

		void setPlayed(bool p) {
		played = p;
		}

		bool getPlayed() const {
			return played;
		}

		void setPaired(bool p) {
			paired = p;
		}

		bool getPaired() const {
			return paired;
		}

		void setId1(int id) {
			id1 = id;
		}

		int getId1() const {
			return id1;
		}

		void setId2(int id) {
			id2 = id;
		}

		int getId2() const {
			return id2;
		}

		void setName1(string name) {
			name1 = name;
		}

		string getName1() const {
			return name1;
		}

		void setName2(string name) {
			name2 = name;
		}

		string getName2() const {
			return name2;
		}

		void setShortName1(string name) {
			sName1 = name;
		}

		string getShortName1() const {
			return name1;
		}

		void setShortName2(string name) {
			sName2 = name;
		}

		string getShortName2() const {
			return name2;
		}

		void setResult(string r) {
			result = r;
		}

		string getResult() const {
			return result;
		}

		void setFullScore1(int f) {
			fullScore1 = f;
		}

		int getFullScore1() const {
			return fullScore1;
		}

		void setFullScore2(int f) {
			fullScore2 = f;
		}

		int getFullScore2() const {
			return fullScore2;
		}

		void setScore1(int s) {
			score1 = s;
		}

		int getScore1() const {
			return score1;
		}

		void setScore2(int s) {
			score2 = s;
		}

		int getScore2() const {
			return score2;
		}

		void setExtraTime1(int e) {
			ext1 = e;
		}

		int getExtraTime1() const {
			return ext1;
		}

		void setExtraTime2(int e) {
			ext2 = e;
		}

		int getExtraTime2() const {
			return ext2;
		}

		void setPenalties1(int p) {
			plt1 = p;
		}

		int getPenalties1() const {
			return plt1;
		}

		void setPenalties2(int p) {
			plt2 = p;
		}

		int getPenalties2() const {
			return plt2;
		}

		void setRound(int r) {
			round = r;
		}

		int getRound() const {
			return round;
		}

};

#endif // !MATCH_H
