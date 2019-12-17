// busMatches.cpp

#include "busMatches.hpp"
#include "LLQueue.hpp"

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// This is a demo of the code to show you how to read from istream
// Please see the assignment description to see the exact format
// you can expect the input to be.
std::map<int, int> assignBusSeats(std::istream & in)
{
	std::string line;
	int numSeats;  // could be unsigned.
	getline(in, line); //get line of istream in
	int p;

	

	numSeats = atoi(line.c_str()); 

    std::vector<LLQueue<int>> wPrefQueues(numSeats + 1, LLQueue<int>()); //vector of pref lists for window ppl (in queue form)

	std::vector<std::map<int, int>> aPrefPositions(numSeats+ 1, std::map<int, int>()); //vector of pref lists for each aisle person A (in map form)
														   				//(k,v) -> k = window person #, v = k's position in A's pref list
	std::map<int, int> matches; //map of matches, k = window person, v = aisle person
	LLQueue<int> windowPpl; //queue of window ppl to be matched
	std::map<int, int> aislePplMatched; //map of matches, k = A, v = W

	for (int i = 1; i <= numSeats; i++) // run through n lines (line 1 = pref list for person 1) (stores info into array of queues)
	{
		std::stringstream ss; 

		getline(in, line); //retrieve line
		ss << line; //input it into the stringstream
		LLQueue<int> prefQueue; //pref list as a queue

		for (int j = 1; j <= numSeats; j++) {

			std::string str;
			ss >> str; //get the jth number in line
			p = atoi(str.c_str());
			prefQueue.enqueue(p); 
		}

		wPrefQueues[i] = prefQueue;
		windowPpl.enqueue(i);

	}


	for (int i = 1; i <= numSeats; i++) // run through n lines (line 1 = pref list for person 1) (stores info into vector of maps)
	{
		std::stringstream ss; 

		getline(in, line); //retrieve line
		ss << line; //input it into the stringstream
		std::map<int, int> prefPositions;


		for (int j = 1; j <= numSeats; j++) {
			ss >> p; //get the jth number in line
			prefPositions.insert(std::pair<int, int> (p, j));
		}

		aPrefPositions[i] = prefPositions;
	}


	while (!windowPpl.isEmpty()) { //while there still are window ppl to be matched

		int W = windowPpl.front(); 

		windowPpl.dequeue(); //remove top from queue

		int A = wPrefQueues[W].front();

		wPrefQueues[W].dequeue();

		if (aislePplMatched.count(A) == 0) { //if A does not have a buddy

			matches.insert(std::pair<int, int> (W, A));
			aislePplMatched.insert(std::pair<int, int> (A, W));

		}
		else { 


			int seatBuddy = aislePplMatched.at(A);
			
			std::map<int, int> aMap = aPrefPositions[A];

			if (aMap[W] > aMap[seatBuddy]) { //if A prefers seatBuddy to W
				windowPpl.enqueue(W);
			}
			else { //if A prefers W
				matches.erase(seatBuddy); //erase previous mapping (seatBuddy, A)
				aislePplMatched.erase(A); //erase previous mapping (A, seatBuddy)


				matches.insert(std::pair<int, int> (W, A));

				aislePplMatched.insert(std::pair<int, int> (A, W));

				windowPpl.enqueue(seatBuddy);
			}


		}



	}


	return matches;  // this is obviously a stub and is not what you want.
}
