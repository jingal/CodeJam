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
        long left_max = 2000000000;
        long right_max = -2000000000;
		
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



		// order by y
		sort(points.begin(), points.end(), [](const vector<long>& a, const vector<long>& b){ return a[1] < b[1]; });

		long left_min = left_max+W , right_min = right_max-W;
        if (left_min >= right_min) {
            goto PRINT_NO;
        }

        long bottom_min = points[0][1]+W, bottom_max = points[0][1], top_min = points[N-1][1] - W, top_max = points[N-1][1];
        if (top_min <= bottom_min) {
            goto PRINT_NO;
        }

        
        int ruin = 0;
        for (int j = 0; j < N; j++) {
            long x = points[j][0], y = points[j][1];
            if (y >= top_min && y <= top_max) { ruin++; continue; }
            if (y >= bottom_max && y <= bottom_min) { ruin++; continue; }
            if (x >= left_max && x <= left_min) { ruin++; continue; }
            if (x >= right_min && x <= right_max) { ruin++; continue; }
        }

        if (N <= ruin + K) goto PRINT_YES;
        else goto PRINT_NO;

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
