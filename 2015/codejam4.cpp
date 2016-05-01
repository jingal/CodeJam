#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>
#include <algorithm>
#include <iterator>     // std::distance

using namespace std;

vector<tuple<int, int>> gRoom;

class tree {
	int v;
	tree *left;
	tree *left;
};

int getCenterRoom(vector<tuple<int, int>>& room, const int N, int A, int B) {

	tree node;
	tree *current = &node;

	for (int i = 0; i < room.size(); i++) {
		
		tuple<int, int>& pair = room[i];

		get<0>(pair);
		get<1>(pair);
	}

	return -1;
}
