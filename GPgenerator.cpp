#include <iostream>
#include <string> 

using namespace std;

string getQStateName(int carry, int i, int j, int k) {
	return ("q_"+to_string(carry)+to_string(i)+"_"+to_string(j)+"_"+to_string(k));
}

void printSReturnTransitions(int sameLengthNumber, int minusOneNumber) {
	for (int stateCarry = 0; stateCarry < sameLengthNumber + minusOneNumber; stateCarry++) {
		string currName = "s"+to_string(stateCarry);
		for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
			for (int i = 0; i <= sameLengthNumber; i++) {
				for (int j = 0; j <= minusOneNumber; j++) {
					for (int k = 0; k <= minusOneNumber; k++) {
						string topName = getQStateName(carry,i,j,k);
						int bit = (stateCarry + i + k) % 2;
						int newCarry = (stateCarry + i+k) / 2;
						char inp = 'e' + bit;
						cout<<"("<<currName<<" "<<topName<<" "<<inp<<" "<<"s"<<newCarry<<")\n";
					}
				}
			}
		}
	}
}

void printSingleQReturn(int c, string currName, int sameLengthNumber, int minusOneNumber) {
	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		for (int i = 0; i <= sameLengthNumber; i++) {
			for (int j = 0; j <= minusOneNumber; j++) {
				for (int k = 0; k <= minusOneNumber; k++) {
					string topName = getQStateName(carry,i,j,k);
					int bit = (c + i + k) % 2;
					int newCarry = (c + i+k) / 2;
					char inp = 'e' + bit;
					cout<<"("<<currName<<" "<<topName<<" "<<inp<<" "<<"s"<<newCarry<<")\n";
				}
			}
		}
	}
}

void printQReturnTransitions(int sameLengthNumber, int minusOneNumber) {
	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		for (int i = 0; i <= sameLengthNumber; i++) {
			for (int j = 0; j <= minusOneNumber; j++) {
				for (int k = 0; k <= minusOneNumber; k++) {
					string name = getQStateName(carry,i,j,k);
					printSingleQReturn(carry, name, sameLengthNumber, minusOneNumber);
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

void printSingleCall(string name, char letter, int carry, int k, int sameLengthNumber, int minusOneNumber) {
	for (int i = 0; i <= sameLengthNumber; i++) {
		for (int j = 0; j <= minusOneNumber; j++) {
			cout<<"("<<name<<" "<<letter<<" "<<getQStateName(carry, i, j, k)<<")\n";
		}
	}
}

void printCallTransitions(int sameLengthNumber, int minusOneNumber) {

	cout << "callTransitions = {\n";

	for (int carry = 0; carry < sameLengthNumber + minusOneNumber; carry++) {
		for (int i = 0; i <= sameLengthNumber; i++) {
			for (int j = 0; j <= minusOneNumber; j++) {
				for (int k = 0; k <= minusOneNumber; k++) {
					string name = getQStateName(carry,i,j,k);
					int bit = (carry + i + j) % 2;
					int newCarry = (carry + i+j) / 2;
					char inp = 'a' + bit;
					printSingleCall(name, inp, newCarry, j, sameLengthNumber, minusOneNumber);
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

	cout << "},\ninitialStates = {";
	for (int i = 0; i <= sameLengthNumber; i++) {
		for (int j = 0; j <= minusOneNumber; j++) {
			cout << getQStateName(0, i,j,0)<<" ";
		}
	}
	cout<<"},\nfinalStates = {s0},\n";
}

void createAutomaton (int sameLengthNumber, int minusOneNumber) {
	cout << "NestedWordAutomaton gpalChecker = (\n";
	cout << "callAlphabet = { a b },\ninternalAlphabet = { c d },\nreturnAlphabet = { e f },\n";
	createStates(sameLengthNumber, minusOneNumber);
	printCallTransitions(sameLengthNumber, minusOneNumber);
	printInternalTransitions(sameLengthNumber, minusOneNumber);
	printReturnTransitions(sameLengthNumber, minusOneNumber);
	cout << "print(numberOfStates(gpalChecker));\n";
}

int main() {
	createAutomaton(2, 1);
}