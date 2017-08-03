#include <iostream>
#include <string> 

using namespace std;

string printNumber(int n) {
	switch (n) {
		case 0:
			return "ZERO";
			break;
		case 1:
			return "ONE";
			break;
		case 2:
			return "TWO";
			break;
		case 3:
			return "THREE";
			break;
		case 4:
			return "FOUR";
			break;
		case 5:
			return "FIVE";
			break;
		case 6:
			return "SIX";
			break;
		case 7:
			return "SEVEN";
			break;
		case 8:
			return "EIGHT";
			break;
		case 9:
			return "NINE";
			break;
		case 10:
			return "TEN";
			break;
		case 11:
			return "ELEVEN";
			break;
		case 12:
			return "TWELVE";
			break;
		case 13:
			return "THIRTEEN";
			break;
		default:
			return "ERROR";
	}

}

string getStateName(int carryOver, int stackGuess, bool first = true) {
	string retName = "";
	if (first)
		retName += "f_";
	else
		retName += "s_";
	retName += to_string(carryOver);
	retName += "_";
	retName += printNumber(stackGuess);
	return retName;
}

//for f states only
void printCallTransitions(int carryOver, int stackGuess, int numOfPals) {
	string stateName = getStateName(carryOver, stackGuess, true);
	char letter;
	if ((carryOver + stackGuess) % 2 == 0)
		letter = 'a';
	else
		letter = 'b';
	int rem = (carryOver + stackGuess) / 2;
	for (int i = 0; i <= numOfPals; i++) {
		cout << "("<<stateName<<" "<<letter<<" "<<getStateName(rem, i, true)<<")\n";
	}
	cout<<endl;
}

//for s states only
void printReturnTransitions(int carryOver, int numOfPals, int maxCarryOver) {
	string stateName = "s";
	stateName += to_string(carryOver);
	char letter;
	if (carryOver % 2 == 0)
		letter = 'e';
	else
		letter = 'f';
	for (int i = 0; i <= numOfPals; i+=2) {
		for (int j = 0; j <= maxCarryOver; j++) {
			cout << "(" << stateName << " " << getStateName(j, i, true) << " " << letter 
				<< " s" << (carryOver + i)/2<<")\n";
		}
		cout<<endl;
	}
	if (carryOver % 2 == 0)
		letter = 'f';
	else
		letter = 'e';	
	for (int i = 1; i <= numOfPals; i+=2) {
		for (int j = 0; j <= maxCarryOver; j++) {
			cout << "(" << stateName << " " << getStateName(j, i, true) << " " << letter 
				<< " s" << (carryOver + i)/2<<")\n";
		}
		cout<<endl;
	}
	cout<<endl;
}

void addInternalTransitions(int numOfPals, int maxCarryOver) {
	for (int i = 0; i <= maxCarryOver; i++) {
		for (int j = 0; j <= numOfPals; j++) {
			char letter;
			if ((i + j) % 2 == 0)
				letter = 'c';
			else
				letter = 'd';
			for (int k = 0; k <= numOfPals; k++) {
				string name = getStateName(i, k);
				cout << "(" << name << " " << letter << " s" << (i+j)/2<<")\n";
			}
			cout<<endl;
		}
	}
}

void addAcceptTransition(int maxCarryOver) {

	cout << "(s4 c n0)\n";
	cout << "(n0 c q)\n";
	cout << "(n1 d q)\n";
	cout << "(q d acc)\n";
	if (maxCarryOver >= 5)

		cout << "(s5 d n0)\n";
	if (maxCarryOver >= 6)
		cout << "(s6 c n1)\n";
	if (maxCarryOver >= 7)
		cout << "(s7 d n1)\n";
}

void createAutomaton (int numOfPals) {
	int maxCarryOver = numOfPals - 1;
	cout << "NestedWordAutomaton palChecker"<<printNumber(numOfPals)<<" = (\n";
	cout << "callAlphabet = { a b },\ninternalAlphabet = { c d },\nreturnAlphabet = { e f },\n";
	cout << "states = { \n";
	for (int carry = 0; carry <= maxCarryOver; carry++) {
		for (int j = 0; j <= numOfPals; j++)
			cout<<getStateName(carry, j, true)<<" ";
		cout<<endl;
	}
	for (int carry = 0; carry <= maxCarryOver; carry++) {
		cout<<"s"<<carry<<" ";
	}
	cout<<"n0 n1 q acc},\n";
	cout << "initialStates = {" << getStateName(0, numOfPals, true) << "},\nfinalStates = {acc},\n";
	cout << "callTransitions = {\n";
	for (int carry = 0; carry <= maxCarryOver; carry++) {
		for (int j = 0; j <= numOfPals; j++)
			printCallTransitions(carry, j, numOfPals);
	}
	cout << "},\n";
	cout << "internalTransitions = {\n";
	addInternalTransitions(numOfPals, maxCarryOver);
	addAcceptTransition(maxCarryOver);
	cout << "},\n";
	cout << "returnTransitions = {\n";
	for (int i = 0; i <= maxCarryOver; i++)
		printReturnTransitions(i, numOfPals, maxCarryOver);
	cout << "}\n";
	cout << ");\n";

	// cout << "NestedWordAutomaton palCheckerComp"<<printNumber(numOfPals)<<" = Complement(palChecker" << printNumber(numOfPals)<< ");\n";
}

int main() {
	// createAutomaton(1, 0);
	// createAutomaton(2, 1);
	// createAutomaton(3, 2);
	// createAutomaton(4, 3);
	createAutomaton(5);
	// createAutomaton(6);
	// createAutomaton(7);
	// createAutomaton(8);
	// createAutomaton(9);
	// createAutomaton(10);

	// cout << "NestedWordAutomaton IntAll = Intersect(palCheckerComp" << printNumber(5)<< ", palCheckerComp"<<printNumber(6)<<");\n";
	// cout << "IntAll = Intersect(IntAll, palCheckerComp"<<printNumber(7)<<");\n";
	// cout << "IntAll = Intersect(IntAll, palCheckerComp"<<printNumber(8)<<");\n";
	// cout << "IntAll = Intersect(IntAll, palCheckerComp"<<printNumber(9)<<");\n";
	// cout << "IntAll = Intersect(IntAll, palCheckerComp"<<printNumber(10)<<");\n";

	// cout << "NestedWordAutomaton FinalAut = Complement(IntAll);\n";
}