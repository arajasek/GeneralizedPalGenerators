#include <iostream>
#include <string> 

using namespace std;

//Q States are 4-tuples
// a carry
// i, the next length-n guess
// j, the next n-2 guess
// k, the previous n-2 guess

string getQStateName(int carry, int i, int j, int k) {
	return ("q_"+to_string(i)+"_"+to_string(j)+"_"+to_string(k));
}

void printSReturnTransitions(int sameLengthNumber, int minusOneNumber) {
	
}

void printQReturnTransitions(int sameLengthNumber, int minusOneNumber) {
	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		for (int i = 0; i <= sameLengthNumber; i++) {
			for (int j = 0; j <= minusOneNumber; j++) {
				for (int k = 0; k <= minusOneNumber; k++) {
					string name = getQStateName(carry,i,j,k);
					int bit = (carry + i + j) % 2;
					int newCarry = (carry + i+j) / 2;
					char inp = 'a' + bit;
					printSingleCall(name, inp, newCarry, j);
				}
			}
		}
	}
}

void printReturnTransitions(int sameLengthNumber, int minusOneNumber) {
	cout << "returnTransitions = {\n";
	printQReturnTransitions(sameLengthNumber, minusOneNumber);
	printSReturnTransitions(sameLengthNumber, minusOneNumber);
	cout << "}\n);\n";
}

void printInternalTransitions(int sameLengthNumber, int minusOneNumber) {
	cout << "internalTransitions = {\n";

	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		for (int i = 0; i <= sameLengthNumber; i++) {
			for (int j = 0; j <= minusOneNumber; j++) {
				string name = getQStateName(carry,i,j,j);
				int bit = (carry + i + j) % 2;
				int newCarry = (carry + i+j) / 2;
				char inp = 'c' + bit;
				cout<<"("<<name<<" "<<inp<<" s"<<newCarry<<")\n";
			}
		}
	}

	cout << "},\n";
}

void printSingleCall(string name, char letter, int carry, int k) {
	for (int i = 0; i <= sameLengthNumber; i++) {
		for (int j = 0; j <= minusOneNumber; j++) {
			cout<<"("<<name<<" "<<letter<<" "<<getQStateName(carry, i, j, k)<<")\n";
		}
	}
}

void printCallTransitions(int carryOver, int stackGuess, int numOfPals) {

	cout << "callTransitions = {\n";

	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		for (int i = 0; i <= sameLengthNumber; i++) {
			for (int j = 0; j <= minusOneNumber; j++) {
				for (int k = 0; k <= minusOneNumber; k++) {
					string name = getQStateName(carry,i,j,k);
					int bit = (carry + i + j) % 2;
					int newCarry = (carry + i+j) / 2;
					char inp = 'a' + bit;
					printSingleCall(name, inp, newCarry, j);
				}
			}
		}
	}

	cout << "},\n";
}

void createStates (int sameLengthNumber, int minusOneNumber) {
	cout << "states = { \n";
	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		for (int i = 0; i <= sameLengthNumber; i++) {
			for (int j = 0; j <= minusOneNumber; j++) {
				for (int k = 0; k <= minusOneNumber; k++) {
					cout << getQStateName(carry,i,j,k)<<endl;
				}
			}
		}
	}
	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		cout<<"s"<<carry<<" ";
	}

	cout << "}\ninitialStates = {" 
	for (int i = 0; i <= sameLengthNumber; i++) {
		for (int j = 0; j <= minusOneNumber; j++) {
			cout << getQStateName(0, i,j,0)<<" ";
		}
	}
	cout<<"},\nfinalStates = {s0},\n";
}

void createAutomaton (int sameLengthNumber, int minusOneNumber) {
	int maxCarryOver = sameLengthNumber + minusOneNumber - 1;
	cout << "NestedWordAutomaton palChecker = (\n";
	cout << "callAlphabet = { a b },\ninternalAlphabet = { c d },\nreturnAlphabet = { e f },\n";
	createStates();
	printCallTransitions(sameLengthNumber, minusOneNumber);
	printInternalTransitions(sameLengthNumber, minusOneNumber);
	printReturnTransitions(sameLengthNumber, minusOneNumber);
	cout << "print(numberOfStates(palChecker));\n";
	cout << "NestedWordAutomatonfinalAut = shrinkNwa(palChecker);\n";
	cout << "print(numberOfStates(finalAut));\n";
}

int main() {
	createAutomaton(2, 1);
}