#include "./stdc++.h"

using namespace std;
int minimumTimeOfBridge = INT_MAX;

void getVectorFromFile(string filename, string variable, vector<string> &returnString){
	ifstream file(filename); 
  
    // String to store each line of the file. 
    string line; 
    string tempStr;
  	string delimiter = "-";
    if (file.is_open()) { 
        // Read each line from the file and store it in the 
        // 'line' variable. 
    		int gotField = 0;
        while (getline(file, line)) { 
        		if (line.find(variable) != string::npos) {
        			gotField = 1;
        		} else if (gotField == 1 && line.find(delimiter)!= string::npos) {
        			tempStr = line.erase(0, line.find(delimiter) + delimiter.length());
        			returnString.push_back(tempStr);
        			tempStr = "";
        		} else {
        			gotField = 0;
        		}
        } 
        // Close the file stream once all lines have been 
        // read. 
        file.close(); 
	
    } 
    else { 
        // Print an error message to the standard error 
        // stream if the file cannot be opened. 
        cerr << "Unable to open file!" << endl; 
    }
  
}

vector<float> getVectorFromInputString(vector<float> people, string s){
	/*
	 *	helper function to popolate the hikers array from input string 
	 *	of individual hiker speeds. Any new hikers are appended in existing
	 *	array and we progress bridges.
	 */

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

string getStateString(vector<float> people, string state){
	/*
	 *	Helper function to construct the machine state according to
	 *	number of hikers present at the bridge
	 */

	for (int i=0;i<people.size();i++){
		state = state+"L";
	}
	return state;
}


int passBridge(string state, vector<float> people, int timeTaken, int distance) {
  /*
	 *	The main function for tranfering the hikers accross the bridge.
	 *	
	 *	Strategy: 
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
        	if (tempTimeTaken < minimumTimeOfBridge) {
			  		minimumTimeOfBridge = tempTimeTaken;
			  	}
        } else {
					// backward pass: find the fastest hiker present on right-side to carry back the torch and update the state.
		      int rightMax = -INT_MAX;
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

int main (int argc, char const *argv[]) {
  // inputs reading from yaml file
	vector<string> returnString;
	getVectorFromFile(argv[1], "numBridges", returnString);

	int numBridges = stoi(returnString[0]);	

  returnString.clear();
	getVectorFromFile(argv[1], "bridgeLengths", returnString);
	vector<int> bridgeLengths;
	for (int i=0;i<returnString.size();i++){
		bridgeLengths.push_back(stoi(returnString[i]));
	}

	returnString.clear();
	getVectorFromFile(argv[1], "hikersSpeedsAtEachBridge", returnString);
	vector<string> hikers;
	for (int i=0;i<returnString.size();i++){
		hikers.push_back(returnString[i]);
	}


	// variables
  string state = "";
	vector<float> people;
	float totalTime = 0;

	// main logic
  int counter = 0;
  while (counter < numBridges) {
  	people = getVectorFromInputString(people, hikers[counter]);
  	state = getStateString(people, state);
	  passBridge(state, people, 0, bridgeLengths[counter]);
		cout<<"Time taken to cross "<<counter<<" bridge: "<<minimumTimeOfBridge<<endl;
		totalTime = totalTime + minimumTimeOfBridge;
		// reseting state for next bridge
		state = "";
	  minimumTimeOfBridge = INT_MAX;
  	counter++;
  }
  cout<<"It took "<<totalTime<<" minutes to complete all crossings."<<endl;


}

