#include <iostream>
#include <stdlib.h> //<cstdlib>
#include <time.h> //<ctime>
using namespace std;

int main()
{

	srand(time(NULL));	
	int myInt;

	myInt = rand() % 5 + 1;
	cout << myInt << endl;

	switch (myInt)
	{
		case 1:
		case 2:
		case 3:
			cout << "Oxen didn't like you, go to jail." << endl;
			break;
		case 4:
		case 5:
			cout << "Oxen and I movie coming Summer 2016" << endl;
			break;
		// default:		
			// cout << "What happened?" << endl;
			// break;
	}

	string direction;
	cout << "Walk to the left or right: ";
	cin >> direction;

	int chance = rand() % 5 + 1;
	if (direction == "left")
		chance += 5;

	switch (chance)
	{
		case 1:
			cout << "What were you thinking?!?! Always walk left!" << endl;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			cout << "You live a happy life on the right road!" << endl;
			break;
		case 6:
		case 7:
			cout << "The left path led to a marvelous city!" << endl;
			break;
		case 8:
			cout << "The left-wing trolls ruin your day." << endl;
			break;
		case 9:
		case 10:
			cout << "You made it home!" << endl;
			break;
	}


	return 0;
}