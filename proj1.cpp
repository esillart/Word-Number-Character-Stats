#include <iostream>
#include <vector> 
#include <string>
#include <map>
#include <iterator>

using namespace std;

//INFO ABOUT PROGRAM:  PROGRAM DOES NOT SORT OUTPUTS WITH EQUAL NUMBER BY WHEN IT SHOWS UP IN INPUT. PROGRAM ALSO DOES NOT OUTPUT NUMBER OF OUTPUTS BUT DOES STATE AMOUNT IN LIST.	

void storeNumber(vector<char> & numV, map <string, int>  & tempMap);
void storeLetter(vector<char> & letterV, map <string, int> & tempMap);
void storeWord(vector<char> & wordV, map <string, int> & tempMap);
void printMap(map <string, int> & tempMap);

int main() {

	map <string, int> numberMap; 
	map <string, int> letterMap;
	map <string, int> wordMap;

	vector<char> wordVector;						 
	vector<char> numberVector;						
	vector<char> input;
	vector<char> superVector;

	bool wordFlag = false;
	bool numberFlag = false;

	char ch;
	while(cin.get(ch)){								//grab input from source

	  input.push_back(ch);
	};



	unsigned int letterCounter = 0;							

	for (int i = 0; i < input.size(); i++) {					//iterate though input

	  superVector.push_back(input[i]);							//no matter what, take each character and put it into a vector to be stored into a map and then deleted from vector
	  storeLetter(superVector, letterMap);							

		if (isalnum(input[i])) {							//if the value is a letter or number, will be true. Continue through if statement

			if (isdigit(input[i])) {						//check if value is a digit

				
				if (wordFlag == true) {						//if wordFlag is true, then check if it's just a single letter or not. Call appropriate function if 1 or not

					if (letterCounter == 1) {

						storeLetter(wordVector, wordMap);
					}
					else {

						storeWord(wordVector, wordMap);
					}

					letterCounter = 0;						//reset letter counter back to 
				}

				numberFlag = true; 							//if it is, set appropriate flags for later function calling 
				wordFlag = false;

				numberVector.push_back(input[i]);					//push the digit onto the number Vector 


			}
			else{									//if it gets to this else, means value is a letter

				if (isupper(input[i])) {					//if uppercase then switch to lowercas

					input[i] = tolower(input[i]);
				}

				if (numberFlag == true) {					//check to see if numberFlag has been set.  If so, pass number vector to function to be added to map and delete

					storeNumber(numberVector, numberMap);

					letterCounter = 0;
				}

				wordFlag = true;						//set approrpriate flags and increment counter at the end. Add input to wordVector
				numberFlag = false;

				letterCounter++;

				wordVector.push_back(input[i]);



			}

		}
		else {									//if isalnum returns false, is not a valid value and will continue through iteration
			if(numberFlag == true) {			//if at this point, reached invalid character.  Check to see which flags are set to call appropriate functions

				storeNumber(numberVector, numberMap);		//if numFlag is true, means last input was a number, store number

				letterCounter = 0; 
			}
			else if(wordFlag == true) {				//if word flag true, means last input was a word, store word

				if(letterCounter == 1) {

					storeLetter(wordVector, wordMap);
				}
				else {
				
					storeWord(wordVector, wordMap);
				}

				letterCounter = 0;
			}


			numberFlag = wordFlag = false;					//reset flags and counter for invalid character
			letterCounter = 0;
		}

		if (i == input.size() - 1) {				//there's an issue where the last vector doesn't get added to the map.  This code fixes that (essentially a copy of previous lines of code).

			if (numberFlag == true) {			

				storeNumber(numberVector, numberMap);

				letterCounter = 0;
			}
			else if (wordFlag == true) {

				if (letterCounter == 1) {

					storeLetter(wordVector, wordMap);
				}
				else {

					storeWord(wordVector, wordMap);
				}

				letterCounter = 0;
			}


			numberFlag = wordFlag = false;
			letterCounter = 0;

		}

	}

	cout << "Total __ different characters, __ most used characters" << endl;		//three function calls to print the top 10 in each category
	printMap(letterMap);
	cout << endl;

	cout << "Total __ different words, __ most used words" << endl;
	printMap(wordMap);
	cout << endl;

	cout << "Total __ different numbers, __ most used numbers" << endl; 
	printMap(numberMap);
	cout << endl;	

	return 0;
}


void storeNumber(vector<char> & numV, map <string, int> & tempMap) {					//this function takes in a vector by reference and adds it to a map before deleting contents in vector

	string tempStr;																	//create temporary string to store value from vector

	for (int i = 0; i < numV.size(); i++) {

		tempStr += numV.at(i);																	//add values from vector to string
	}

	if (tempMap.empty()) {																	//if the map is empty, simply add to map
	  tempMap.insert(pair <string, int> (tempStr, 1));
	}
	else {
		if (tempMap.count(tempStr) == 1) {												//if map isn't empty, check to see if key already exists in map

			tempMap.find(tempStr)->second += 1;												//if so, increment value key is attached to by 1
		}
		else {																				//if the key wasn't found

			
			tempMap.insert(pair <string, int> (tempStr, 1));								//then add to the map
		}

	}

	numV.erase(numV.begin(), numV.end());													//erase contents in vector containing old string
}

void storeLetter(vector<char> & letterV, map <string, int> & tempMap) {

	string tempStr;

	for (int i = 0; i < letterV.size(); i++) {

		tempStr += letterV.at(i);
	}

	if (tempMap.empty()) {																	//if the map is empty, simply add to map
		tempMap.insert(pair <string, int>(tempStr, 1));
	}
	else {
		if (tempMap.count(tempStr) == 1) {												//if map isn't empty, check to see if key already exists in map

			tempMap.find(tempStr)->second += 1;												//if so, increment value key is attached to by 1
		}
		else {																				//if the key wasn't found

			tempMap.insert(pair <string, int>(tempStr, 1));								//then add to the map
		}

	}

	letterV.erase(letterV.begin(), letterV.end());
}

void storeWord(vector<char> & wordV, map <string, int> & tempMap) {

	string tempStr;

	for (int i = 0; i < wordV.size(); i++) {

		tempStr += wordV.at(i);
	}

	if (tempMap.empty()) {																	//if the map is empty, simply add to map
		tempMap.insert(pair <string, int>(tempStr, 1));
	}
	else {
		if (tempMap.count(tempStr) == 1) {												//if map isn't empty, check to see if key already exists in map

			tempMap.find(tempStr)->second += 1;												//if so, increment value key is attached to by 1
		}
		else {																				//if the key wasn't found

			tempMap.insert(pair <string, int>(tempStr, 1));								//then add to the map
		}

	}

	wordV.erase(wordV.begin(), wordV.end());
}

void printMap(map <string, int> & tempMap){

	int largestValue = 0;										//variable to hold amount of times word shows up
	string largestKey;										//string to hold the words that show up

	map <string, int>::iterator itr;

	for (int i = 0; i < 10; i++) {											//do a total of 10 times
	
	  if (tempMap.empty()) break;

		for (itr = tempMap.begin(); itr != tempMap.end(); ++itr) {					//iterate through map to find most common key

		  if (itr->second > largestValue) {

		    largestValue = itr->second;												//keep replacing with most common
		    largestKey = itr->first;
		  }
		}
	
		
	  cout << "No. " << i << ": " <<  largestKey << '\t' << largestValue << endl;
	  tempMap.erase(largestKey);												//after outputting key with value, erase from map and loop
	  largestValue = 0;
	}
}


