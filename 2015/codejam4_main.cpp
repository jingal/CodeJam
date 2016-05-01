#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <time.h>
#include <tuple>

#define _LOCAL_DEBUG

using namespace std;

const string input_file_name = "codejam4.in.small.txt";
const string output_file_name = "codejam4.out.small.txt";
const string solution_file_name = "codejam4.solution.small.txt";
const string result_file_name = "codejam4.result.small.txt";


void print_result(const clock_t& begin, const clock_t& end);
extern int getCenterRoom(vector<tuple<int, int>>& room, const int N, int A, int B);

int main() {

	std::ifstream input_if(input_file_name);
	std::ofstream output_if(output_file_name);

	if (!input_if.is_open()) {
		cout << "invalid file name : " << input_file_name << endl;
		return -1;
	}

	clock_t begin, end;
	begin = clock();

	int T = 0;
	input_if >> T;
	#ifdef _LOCAL_DEBUG
	cout << "T : " << T << endl;
	#endif //_LOCAL_DEBUG
	
	for (int i = 0; i < T; i++) {
		int N, K;
		input_if >> N >> K;

		#ifdef _LOCAL_DEBUG
		cout << "N : " << N << ", K : " << K << endl;
		#endif //_LOCAL_DEBUG

		vector<tuple<int, int>> room;

		//vector<tuple<int, int>> pairs;
		for (int j = 0; j < N-1; j++) {
			int P, Q;
			input_if >> P >> Q;

			#ifdef _LOCAL_DEBUG
			cout << "P : " << P << ", Q : " << Q << endl;
			#endif //_LOCAL_DEBUG

			auto pair = make_tuple(P-1, Q-1);
			room.emplace_back(pair);
		}

		for (int j = 0; j < K; j++) {
			int A, B;
			input_if >> A >> B;

			#ifdef _LOCAL_DEBUG
			cout << "A : " << A << ", B : " << B << endl;
			#endif //_LOCAL_DEBUG
			
			int r = getCenterRoom(room, N, A, B);

			cout << r << endl;
			output_if << r << endl;
		}
	}

	end = clock();

	input_if.close();
	output_if.close();

	#ifdef _LOCAL_DEBUG
	print_result(begin, end);
	#endif //_LOCAL_DEBUG

	return 0;
}

void print_result(const clock_t& begin, const clock_t& end) {
	std::ifstream output_if(output_file_name);
	std::ifstream solution_if(solution_file_name);
	std::ofstream result_of(result_file_name);

	vector<string> src;
	vector<string> dst;

	while (!solution_if.eof()) {
		string str;
		solution_if >> str;
		src.emplace_back(str);
	}
	solution_if.close();
	
	while (!output_if.eof()) {
		string str;
		output_if >> str;
		dst.emplace_back(str);
	}
	output_if.close();

	int src_count = src.size();
	int dst_count = src.size();
	int wrong_count = 0;
	if (src_count == dst_count) {
		for (int i = 0; i < src_count; i++) {
			if (src[i] == dst[i]) {
				result_of << i + 1 << " CORRECT : " << src[i] << " " << dst[i] << "\n";
			}
			else {
				result_of << i + 1 << " WRONG : " << src[i] << " " << dst[i] << "\n";
				wrong_count++;
			}
		}
	}
	else {
		cout << "Failed, Invalid Results, try again" << endl;
		wrong_count++;
	}

	cout << "============================================================" << endl;
	cout << "Results : " << ((wrong_count > 0) ? "Failed" : "Success") << " [COUNT : " << src_count - wrong_count << "/" << src_count << ", Elasped Time : " << (end - begin) << "]" << endl;
	cout << "============================================================" << endl;
	
	result_of.close();	
	return;
}
