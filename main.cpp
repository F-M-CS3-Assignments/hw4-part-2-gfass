#include "bdc.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <set>

// uncomment for part 2
#include <random>


int main() {

	// Test 1 (example from assignment description)
	vector<int> values = {28, 22, 7, 2, 8, 14, 24, 56};
	vector<int> ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	set<int> answerSet(ans.begin(), ans.end());
	set<int> soln = {56, 14, 7, 28};
	bool first = (answerSet == soln);
	soln = {56, 14, 2, 28};
	bool second = (answerSet == soln);
	assert(first || second);

	// Test 2
	values = {10, 5, 3, 15, 20};
	ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	soln = {20, 5, 10};
	set<int> answerSet2(ans.begin(), ans.end());
	assert(answerSet2 == soln);


	// The random number test creates a massive 28,000 value input vector.  
	// Solving the problem with such a large input is not feasible using recursion, 
	// but with dynamic programming it should take just a few seconds.  
	
	vector<int> random_values;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 40000);
	while (random_values.size() < 28000) {
		random_values.push_back(dist(gen));
	}

	cout << "\nCalculating answer for input of size: " << random_values.size() << "..." << endl;
	time_t start = time(0);
	ans = biggest_divisible_conglomerate(random_values);
	time_t end = time(0);
	cout << "\x1B[32m" << "\tDone!  The answer is: " << vec_to_string(ans) << "\033[0m" << endl;
	time_t duration = end - start;
	cout << "It took " << duration << " seconds.  Wow!" << endl;\
	
	
	return 0;
}
