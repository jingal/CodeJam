#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <tuple>
#include <algorithm>
#include <iterator>     // std::distance
#include <list>

using namespace std;

vector<tuple<int, int>> gPairs;
int solution = 1000000;

int total_distance(const vector<int>& line) {
	int sum = 0;

	for (size_t i = 0; i < gPairs.size(); i++) {
		const tuple<int, int>& pair = gPairs[i];

		auto a = find(line.begin(), line.end(), get<0>(pair));
		auto b = find(line.begin(), line.end(), get<1>(pair));

		int dist = distance(a, b);

		sum += abs(dist);
	}
	
	return sum;
}

int makeLine(int begin, int end, vector<int>& line, int seatSize) {
	int score;
	
	if (seatSize == 0) {
		score = total_distance(line);

		if (score < solution) {			
			solution = score;
		}
		
		return score;
	}

	for (int i = 0; i < seatSize; i++) {
		if (line[i] == -1) {
			line[i] = begin;
			makeLine(begin + 1, end, line, seatSize - 1);
			line[i] = -1;
		}
		if (line[i] == -1) {
			line[i] = end;
			makeLine(begin, end - 1, line, seatSize - 1);
			line[i] = -1;
		}
	}

	return solution;
}

int get_distance(const int N) {
	
	vector<int> line;
	for (int i = 0; i < N; i++) {
		line.push_back(-1);
	}

	solution = 10000000;
	int min = makeLine(0, N-1, line, N);

	cout << "return min : " << min << endl;
	
	return min;
}
