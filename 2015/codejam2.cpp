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
		right_max = points[0][0];

		for (int j = 1; j < N; j++) {			
			vector<long> point{ 0,0 };
			input >> point[0] >> point[1];

			if (point[0] < left_max) { //store left point to decrease loop
				left_max = point[0];				
			}

			if (point[0] > right_max) { //store right point to decrease loop
				right_max = point[0];
			}

			points.emplace_back(point);
		}

		if (N == K || N < K) {
			goto PRINT_NO;			
		}

		long left_min = left_max + W, right_min = right_max - W;
		if (left_max + W >= right_max) goto PRINT_YES;
		if (left_min >= right_min) goto PRINT_NO;

		// order by y
		sort(points.begin(), points.end(), [](const vector<long>& a, const vector<long>& b){ return a[1] < b[1]; });		
		
		int k = 0;
		do {
			long bottom_min = points[k][1]+W, bottom_max = points[k][1], top_min = points[N-(K-k)-1][1] - W, top_max = points[N-(K-k)-1][1];
			if (top_max - bottom_max <= W) goto PRINT_YES;
			if (top_min - bottom_min <= 0) goto PRINT_NO;

			int bottom_min_idx = 0;
			for (int j = k; j < N; j++) {
				long y = points[j][1];
				if ( y > bottom_min) {
					bottom_min_idx = j;
					break;
				}
			}

			int top_min_idx = 0;
			//for (int j = N- (K - k) -1; j >= bottom_min_idx; j--) {
			for (int j = N - (K - k) - 1; j >= k; j--) {
				long y = points[j][1];
				if (y < top_min) {
					top_min_idx = j;
					break;
				}
			}
			if (top_min_idx == 0) top_min_idx = N - (K - k) - 1 ;

			//if (bottom_min_idx > top_min_idx) goto PRINT_YES;

			int ruin = 0;
			for (int j = bottom_min_idx; j <= top_min_idx; j++) {
				long x = points[j][0];
				if (x > left_min && x < right_min) { ruin++; break; }				
			}

			//cout << "k : " << k << ", ruin : " << ruin << endl;
			if (ruin == 0) goto PRINT_YES;
			k++;
		} while (k <= K);

		goto PRINT_NO;

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
