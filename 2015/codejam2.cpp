#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <array>

using namespace std;

int main() {

	std::ifstream input("problem2.in.small.txt");

	int T;
	input >> T;
	
	for (int i = 0; i < T; i++) {
		int N, K, W;
		input >> N >> K >> W;

		vector<vector<long>> points{{0,0}};
		vector<long> left{0,0};
		vector<long> right{0,0};
		
		input >> left[0] >> left[1];

		right[0] = left[0];
		right[1] = left[1];
		
		points[0][0] = left[0];
		points[0][1] = left[1];

		for (int j = 1; j < N; j++) {			
			vector<long> point{ 0,0 };
			input >> point[0] >> point[1];

			if (point[0] < left[0]) { //store left point to decrease loop
				left[0] = point[0];
				left[1] = point[1];
			}

			if (point[0] > right[0]) { //store right point to decrease loop
				right[0] = point[0];
				right[1] = point[1];
			}

			points.emplace_back(point);
		}

		if (N == K || N < K) {
			cout << "NO" << endl;
			continue;
		}

		sort(points.begin(), points.end(), [](const vector<long>& a, const vector<long>& b){ return a[1] < b[1]; });

		long top_count = 1, bottom_count = 1, top_y = points[N-K][1], bottom_y = points[K][1], bottom_result = 0, top_result = 0;
		for (int j = K+1; j < N - K - 1 ; j++) { // 남북 성벽 흔적의 갯수를 알 수 없으므로 우선 남북으로 K개 만큼 빼고 평균치를 구해서 남/북성벽 Y값을 Estimation
			if (points[j][1] <= points[K][1] + W) {
				bottom_y += points[j][1];
				bottom_count++;
			}
			else {
				top_y += points[j][1];
				top_count++;
			}
		}

		bottom_result = bottom_y / bottom_count;
		top_result = top_y / top_count;

		long bottom_min = 0;
		for (int j = K; j > 0; j--) {
			if (points[j][1] >= bottom_result - W) {
				bottom_y += points[j][1];
				bottom_min++;
			}
		}
		bottom_result = bottom_y / (bottom_count + bottom_min); // bottom 평균

		int top_max = 0;
		for (int j = N-K; j < N; j++) {
			if (points[j][1] <= top_result + W) {
				top_y += points[j][1];
				top_max++;
			}
		}
		top_result = top_y / (top_count + top_max); // top 평균

		int sum = 0;
		for (int j = K- bottom_min; j < N-K+top_max; j++) { // 남북 성벽 흔적의 갯수를 알 수 없으므로 우선 남북으로 K개 만큼 빼고 나머지에 대해서 계산.
			if (points[j][0] <= left[0] + W) sum++; // left wall
			else if (points[j][0] >= right[0] - W) sum++;
			else if (points[j][1] <= top_result + W && points[j][1] >= top_result - W) sum++;
			else if (points[j][1] >= bottom_result - W && points[j][1] <= bottom_result + W) sum++;
		}

		cout << ((sum == N - K) ? "YES" : "NO") << endl;
	}

	input.close();
	return 0;
}
