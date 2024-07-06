#include "./stdc++.h"

using namespace std;
int finalTime = 99999;

vector<float> getVectorFromInputString(string s){
	vector<float> people;

	int pos = 0;
	string token;
	string delimiter = ",";

	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		people.push_back(stof(token));
		s.erase(0, pos + delimiter.length());
	}
    people.push_back(stof(s));
    return people;
		
}


int passBridge(string state, vector<float> people, int timeTaken, int distance) {
  /*
	 *	The main function for tranfering the hikers accross the bridge.
	 *	
	 *	Strategy is 
	 *	1. Using string "LLLLL" to represent the state. Number of characters in state show the number of hikers 
	 *		and 'L' or 'R' shows whether the hiker is on the left-side of the bridge or right-side of the 
	 *		bridge. Hikers start from left-side and pass to right-side. 
	 *  2. Pick all possible combinations of hikers for the foward pass. Only need to pick one of the two permutations
	 *  	for each pair because (1,2) & (2,1) lead to same result.
	 *  3. Explore the decision tree via recurrsion. Keep adding the time incurred so far.
	 *	4. Always pick the fastest available for the backward pass to bring back the torch.
	 *  5. Whenever all hikers reach the otherside, compare the total time taken against previously best known time.
	 *		Due to the nature of problem, the optimal time for crossing the bridge requires us checking all possible paths. 
	 *		Individual hiker speed can lead optimal solution with variouos approaches (Piggyback strategy/ Non-Piggyback strategy/ Mix)
	 *		but can not provide generalized solution hence we conform to bruteforce. Although this bruteforce is needed for correct 
	 *		execution, it can be further optimized using dynamic programming.
	 *
	 *
	 */

	for (int i=0;i<people.size();i++){
		for (int j=i;j<people.size();j++){
			// making all possible combinations for hikers present on the left-side of bridge
			if (i<j && (state[i]=='L' && state[j]=='L')){

				// forward pass: calculate the time taken to cross the bridge by the chosen pair, and update the state.
        string tempState = state;
        float tempTimeTaken = timeTaken;
				tempTimeTaken = tempTimeTaken + (distance / min(people[i], people[j]));
				tempState[i] = 'R';
				tempState[j] = 'R';

				// clearing condition: check if all hikers have moved to the right. If true, compare the time incurred.
        if (tempState.find('L') == string::npos) {
        	if (tempTimeTaken < finalTime) {
			  		finalTime = tempTimeTaken;
			  	}
        } else {
					// backward pass: find the fastest hiker present on right-side to carry back the torch and update the state.
		      int rightMax = -999;
					int rightMaxIndex = 0;
					for(int k=0;k<people.size();k++){
						if (tempState[k]=='R' and rightMax<people[k]) {
							rightMaxIndex = k;
							rightMax = people[k];
						}
					}
					tempTimeTaken = tempTimeTaken + (distance / rightMax);
					tempState[rightMaxIndex] = 'L';

					// explore the next decision tree along this path.
					passBridge(tempState, people, tempTimeTaken, distance);
				}
			}
		}
  }
	return 0; 
}

int main () {
  // inputs
  string firstBridgeHikers = "100,50,20,10";
  string secondBridgeHikers = "2.5";
  string thirdBridgeHikers = "25,15";
  string state = "LLLL";
  int distance = 100;

  // First bridge
  vector<float> people = getVectorFromInputString(firstBridgeHikers);
  int timeTaken = 0;
  passBridge(state, people, timeTaken, distance);
  cout<<"Time taken to cross first bridge: "<<finalTime<<endl;


  // Second bridge
  distance = 250;
  finalTime = 999;
  state = "LLLLL";
  people = getVectorFromInputString(firstBridgeHikers+","+secondBridgeHikers);
  passBridge(state, people, timeTaken, distance);
  cout<<"Time taken to cross second bridge: "<<finalTime<<endl;


  // Third bridge
  distance = 150;
  finalTime = 999;
  state = "LLLLLLL";
  people = getVectorFromInputString(firstBridgeHikers+","+secondBridgeHikers+","+thirdBridgeHikers);
  passBridge(state, people, timeTaken, distance);
  cout<<"Time taken to cross third bridge: "<<finalTime<<endl;


}

