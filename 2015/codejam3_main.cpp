#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <time.h>
#include <tuple>

#define _DEBUG

int get_distance(const vector<tuple<int, int>>& pairs, const int M);
void print_result(const clock_t& begin, const clock_t& end);

using namespace std;

const string input_file_name = "codejam3.in.small.txt";
const string output_file_name = "codejam3.out.small.txt";
const string solution_file_name = "codejam3.solution.small.txt";
const string result_file_name = "codejam3.result.small.txt";

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
	
	for (int i = 0; i < T; i++) {
		int N, M;
		input_if >> N >> M;

		vector<tuple<int, int>> pairs;
		for (int j = 0; j < M; j++) {
			int P, Q;
			input_if >> P >> Q;

			auto pair = make_tuple(P, Q);
			pairs.emplace_back(pair);
		}

		int min = calcMinimum(pairs, M);

		cout << min << endl;
		output_if << min;
	}

	end = clock();

	input_if.close();
	output_if.close();

	#ifdef _DEBUG
	print_result(begin, end);
	#endif //_DEBUG

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
