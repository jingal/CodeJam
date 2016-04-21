#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <tuple>

using namespace std;

#define LOC(a, b) abs(a - b)

vector<int> gLine;
vector<int> gLineIndex;


int makeLine(const vector<int>& line, int n) {

}


int calc(const tuple<int, int>& pairs) {

}

int total_distance(const vector<tuple<int, int>>& pairs, const vector<int>& line) {
	int sum = 0;

	for (size_t i = 0; i < pairs.size(); i++) {
		const tuple<int, int>& pair = pairs[i];

		const int a = gLineIndex[get<0>(pair)];
		const int b = gLineIndex[get<1>(pair)];

		sum += LOC(a, b);
	}
	
	return sum;
}

int get_distance(const vector<tuple<int, int>>& pairs, const int M) {

	int min;

	gLineIndex.emplace_back(0);
	for (int i = 1; i <= M; i++) {
		gLine.emplace_back(i);
		gLineIndex.emplace_back(i);
	}

	return min;
}
