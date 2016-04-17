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

	if (!input.is_open()) {
		cout << "invalid file name : " << input_file_name << endl;
		return -1;
	}

	if (!output.is_open()) {
		cout << "invalid file name : " << output_file_name << endl;
		return -1;
	}

	int T = 0;
	input >> T;
	
	for (int i = 0; i < T; i++) {
		int N, K, W;
		input >> N >> K >> W;

		vector<vector<long>> points{{0,0}};
		long left_max = 0;
		long right_max = 0;
		
		input >> points[0][0] >> points[0][1];
		left_max = points[0][0];

		for (int j = 1; j < N; j++) {			
			vector<long> point{ 0,0 };
			input >> point[0] >> point[1];

			if (point[0] < left_max) { //store left point to decrease loop
				left_max = point[0];				
			}

			if (point[0] > right_max) { //store right point to decrease loop
				right_max = point[1];
			}

			points.emplace_back(point);
		}

		if (N == K || N < K) {
			goto PRINT_NO;			
		}

//		if (N - K < 5) {
//			goto PRINT_YES;
//		}

		// order by y
		sort(points.begin(), points.end(), [](const vector<long>& a, const vector<long>& b){ return a[1] < b[1]; });

		int included_index = 0;
		long left_min = left_max+W , right_min = right_max-W;
		int bottom_min = 0, bottom_max = 0, top_min = 0, top_max = 0;

		long top_sum = 0, top_avr = 0;
		for (int j = N - 1 - K, k = 0; j >= 0; j--, k++) {
			if (points[N - K - 1][1] - points[j][1] <= W) {				
				top_sum += points[j][1];
			}
			else {
				top_min = j+1;
				top_avr = top_sum / k;
				break;
			}
		}

		if (top_min == N-1) top_max = top_min;
		else {
			for (int j = N - 1 - K, k = 0; j >= 0; j--, k++) {
				if (points[N - K - 1][1] - points[j][1] <= W) {
					top_sum += points[j][1];
				}
				else {
					top_min = j + 1;
					top_avr = top_sum / k;
					break;
				}
			}
		}

		int bottom_k = K - (N - 1 - top_max);
		for (int j = bottom_k-1; j >= 0; j--) {
			if (points[bottom_k][1] - points[j][1] <=W && points[bottom_k][1] - points[j-1][1] > W) {
				bottom_min = j;
				break;
			}
		}
		
		for (int j = bottom_min+1; j < top_min; j++) {
			if ( points[j][1] - points[bottom_min][1] <= W && points[j + 1][1] - points[bottom_min][1] > W && points[j][0] > left_max && points[j][0] < right_min) {
				bottom_max = j;
				break;
			}
		}

		if (bottom_max == 0) bottom_max = bottom_min;

		if (bottom_min == 0 && top_max == N-1) {
			for (int j = top_min; j < top_max; j++) {
				if (points[j][0] > left_max && points[j][0] < right_min) {
					goto PRINT_NO;
					break;
				}
			}
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
