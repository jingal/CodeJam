#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

vector<vector<int>> pos = { { 3,1 },{ 0,0 },{ 0,1 },{ 0,2 },{ 1,0 },{ 1,1 },{ 1,2 },{ 2,0 },{ 2,1 },{ 2,2 } };

int dist(vector<int>& a, vector<int>& b) {
	int x = a[0] - b[0];
	int y = a[1] - b[1];
	int d = static_cast<int>(sqrt(x*x + y*y));

	return (d >= 3) ? 2 : d;
}

bool dir(int a, int b, int c) {
	if (a - b == b - c) return true;
	else if ((a == 0 && b - c == 3) || (a -b == -3 && c == 0)) return true;
	return false;
}

int main() {

	std::ifstream input("problem1.in");

	int T;
	input >> T;	

	for (int i = 0; i < T; i++) {
		int N;
		input >> N;

		int min = 100000000;		
		string min_num;
		for (int j = 0; j < N; j++) {
			int point = 0;
			string num;
			input >> num;

			// 1st condition is 0, no point
			// 2nd condition
			point += dist(pos[num[0] - '0'], pos[num[1] - '0']);

			// 3rd condition
			for (unsigned int k = 2; k < num.length(); k++) {
				int a = num[k - 2] - '0';
				int b = num[k - 1] - '0';
				int c = num[k] - '0';

				int d1 = dist(pos[a], pos[b]);
				int d2 = dist(pos[b], pos[c]);

				if (b == c) point += 0;
				else if ((d1 == 1) && (d2 == 1) && dir(a,b,c)) point += 1;
				else if (d2 == 1) point += 2;
				else point += 3;
			}

			if (min > point) {
				min = point;
				min_num = num;
			}
		}

		cout << min_num << endl;
	}

	input.close();
	return 0;
}