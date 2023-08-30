#include <vector>
#include <random>
#include <cstdlib>

using namespace std;

int initialDraw(vector<vector<int>>& deck) {
	int r = rand() % 4;
	int c = rand() % 13;
	while (deck[r][c] == 0) {
		r = rand() % 4;
		c = rand() % 13;
	}
	int ret = deck[r][c];
	deck[r][c] = 0;
	return ret;
}

void mainDraw(int& Hand, vector<vector<int>>& deck) {

	while (Hand < 17) {
		int r = rand() % 4;
		int c = rand() % 13;
		while (deck[r][c] == 0) {
			r = rand() % 4;
			c = rand() % 13;
		}
		Hand += deck[r][c];
		if (deck[r][c] == 11 && Hand > 21) { Hand -= 10; }
		deck[r][c] = 0;
	}

}

char Stand(int PHand, int DHand, vector<vector<int>>& deck) {

	mainDraw(DHand, deck);

	if (DHand > 21) { return 'W'; }
	else {
		if (PHand > DHand) { return 'W'; }
		else if (PHand == DHand) {
			return 'D';
		}
		else { return 'L'; }
	}

}

int main()
{
	srand(time(0));

	int HardTotalWDL[17][10][3] = { }, SoftTotalWDL[8][10][3] = { }, PairsWDL[10][10][3] = { };

	for (unsigned int i = 0; i < 1000000; i++) {

		vector<vector<int>> deck = { {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10},
						{11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10},
						{11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10},
						{11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10} };

		int PHand1 = initialDraw(deck), PHand2 = initialDraw(deck), DHand = initialDraw(deck), PHand = PHand1 + PHand2;

		if (PHand == 22) { PHand = 12; }

		char result = Stand(PHand, DHand, deck);

		if (PHand == 21) {
			HardTotalWDL[16][DHand - 2][0]++;
			continue;
		}
		
		if (PHand1 == PHand2) {
			if (result == 'W') { PairsWDL[PHand1 - 2][DHand - 2][0]++; }
			if (result == 'D') { PairsWDL[PHand1 - 2][DHand - 2][1]++; }
			if (result == 'L') { PairsWDL[PHand1 - 2][DHand - 2][2]++; }
		}
		else {
			if (PHand1 == 11 || PHand2 == 11) {
				int other = (PHand1 == 11) ? (PHand2) : (PHand1);
				if (result == 'W') { SoftTotalWDL[other - 2][DHand - 2][0]++; }
				if (result == 'D') { SoftTotalWDL[other - 2][DHand - 2][1]++; }
				if (result == 'L') { SoftTotalWDL[other - 2][DHand - 2][2]++; }
			}
			else {
				if (result == 'W') { HardTotalWDL[PHand - 5][DHand - 2][0]++; }
				if (result == 'D') { HardTotalWDL[PHand - 5][DHand - 2][1]++; }
				if (result == 'L') { HardTotalWDL[PHand - 5][DHand - 2][2]++; }
			}
		}
	}

	




	return 0;
}