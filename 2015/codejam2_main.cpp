#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <time.h>

using namespace std;

int start(const string& input_file_name, const string& output_file_name);

int main() {

	//string input_file_name = "problem2.in.test.txt";
	//string solution_file_name = "problem2.out.test.solution.txt";
	//string output_file_name = "problem2.output.test.";
	//string result_file_name = "problem2.result.test";

	//string input_file_name = "problem2.in.short";
	//string solution_file_name = "problem2.out.short.solution";
	//string output_file_name = "problem2.output.short";
	//string result_file_name = "problem2.result.short";

	//string input_file_name = "problem2.in.small.txt";
	//string solution_file_name = "problem2.out.small.solution.txt";
	//string output_file_name = "problem2.output.small";
	//string result_file_name = "problem2.result.small";

	string input_file_name = "problem2.in.large.txt";
	string solution_file_name = "problem2.out.large.solution.txt";
	string output_file_name = "problem2.output.large";
	string result_file_name = "problem2.result.large";


	clock_t begin, end;
	begin = clock();        // 시간설정
	start(input_file_name, output_file_name);
	end = clock();          // 시간설정
	//cout << "수행시간 : " << ((end - begin) / CLOCKS_PER_SEC) << endl;

	std::ifstream solution_if(solution_file_name);
	std::ifstream output_if(output_file_name);
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
				result_of << i+1 << " CORRECT : " << src[i] << " " << dst[i] << "\n";
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
	

	//cout << "============================================================" << endl;
	//cout << "Results : " << ((wrong_count > 0) ? "Failed" : "Success") << " [COUNT : " << src_count - wrong_count << "/" << src_count << ", Elasped Time : " << (end - begin) << "]" << endl;
	//cout << "============================================================" << endl;
			
	result_of.close();
	return 0;
}
