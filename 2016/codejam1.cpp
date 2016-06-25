#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>


using namespace std;

void FindMaxChild(int ancestor, std::vector<pair<bool, pair<int, int>>>& family, int depth, std::vector<int>& k) {

    if (family.empty()) {
        if (k[ancestor - 1] < depth) k[ancestor-1] = depth;
		//cout << "idx " << ancestor - 1 << ", depth " << k[ancestor - 1] << endl;
        return;
    }

	//cout << "family size : " << family.size() << endl;
	for (auto it = family.begin(); it != family.end(); ) {
		auto& pnode = *it;
		auto& node = pnode.second;

        //cout << "[ancestor : " << ancestor << "] first " << node.first << ", second " << node.second << endl;
				
        if (!pnode.first && node.first == ancestor) {
            //cout << "first " << node.first << ", second " << node.second << endl;
			pnode.first = true;
            FindMaxChild(node.second, family, depth+1, k);
		}
		else {
			++it;
		}
    }

    if (k[ancestor - 1] < depth) k[ancestor - 1] = depth;
    //cout << "idx " << ancestor - 1 << ", depth " << k[ancestor - 1] << endl;
}

int max_element(std::vector<int>& k) {
    int max = -1, idx = 0;
    for (int i = 0; i < k.size(); i++) {
        if (max < k[i]) {
            max = k[i];
            idx = i;
        }
    }

    return idx;
}

int min_element(std::vector<int>& k) {
    int min = 50001, idx = 0;
    for (int i = 0; i < k.size(); i++) {
        if (min > k[i]) {
            min = k[i];
            idx = i;
        }
    }

    return idx;
}

int main() 
{
	std::ifstream input("problem_1_Set2.in");
    std::ofstream output("problem_1_Set2.out");

    if (!output.is_open())
    {
        cout << "invalid file" << endl;
        return -1;
    }

	int T;
	input >> T;	

	for (int i = 0; i < T; i++) {
		int N;
		input >> N;

        std::vector<pair<bool, pair<int,int>>> family;
        std::vector<int> K(N);

        // Input
		for (int j = 0; j < N-1; j++) {
            int p, c;
			input >> p >> c;
            K[c-1]++;
            pair<int, int> node(p, c);
            family.push_back(pair<bool, pair<int, int>>(false, node));
		}

        int ancestor = min_element(K);
        //cout << "ancesotr :" << ancestor+1 << endl;

        std::vector<int> L(N);
        FindMaxChild(ancestor+1, family, 1, L);

        int leaf = max_element(L);

        output << L[leaf] << endl;
        cout << L[leaf] << endl;
	}

	input.close();
    output.close();
	return 0;
}