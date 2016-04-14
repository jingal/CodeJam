#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <array>

using namespace std;

int start(const string& input_file_name, const string& output_file_name) {

	std::ifstream input(input_file_name);
	std::ofstream output(output_file_name);

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
			goto PRINT_NO;			
		}

		// order by y
		sort(points.begin(), points.end(), [](const vector<long>& a, const vector<long>& b){ return a[1] < b[1]; });

		int bottom_min = 0, bottom_max = 0, top_min = 0, top_max = 0;

		for (int j = N-K-1; j > 1; j--) {
			if (points[j][1] - points[j-1][1] > W) {
				top_min = j;
				break;
			}
		}

		for (int j = top_min+1; j < N; j++) {
			if (points[top_min][1] + W < points[j][1]) {
				top_max = j-1;
				break;
			}

			if (j == N) top_max = N-1;
		}

		for (int j = K+1; j < N; j++) {
			if (points[K][1] + W < points[j][1]) {
				bottom_max = j-1;
				break;
			}
		}

		for (int j = bottom_max-1; j >= 0; j--) {			
			if (points[bottom_max][1] - W > points[j][1]) {
				bottom_min = j+1;
				break;
			}
			if (j == 0) bottom_min = 0;
		}

		int k_sum = (bottom_min) + (N - top_max - 1);
		if (k_sum == K) { //y 조건은 충족하였으므로, x 조건에 대해서 만족하는지만 확인, 내부 사각형에 포함여부만 확인
			for (int j = bottom_max+1; j < top_min; j++) {				
				if (points[j][0] > left[0] + W && points[j][0] < right[0] - W) {
					goto PRINT_NO;
					break;
				}
			}

			goto PRINT_YES;
		}
		else {
			goto PRINT_NO;
		}

	PRINT_YES : 
		cout << "YES" << endl;
		output << "YES\n";
		continue;

	PRINT_NO:
		cout << "NO" << endl;		
		output << "NO\n";
	}

	input.close();
	output.close();
	return 0;
}
