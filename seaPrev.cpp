#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <math.h>
#include <ctime>

using namespace std;

bool isKill(int input, char userMap[], int checkMap[]);
void set_mass(char a[]);
void show(char a[]);
void shipsSet(char userFleet[], int checkMap[]);//\F0\E0\F1\F1\F2\E0\E2\E8\F2\FC \EA\EE\F0\E0\E1\EB\E8 \E8 \EF\F0\EE\E2\E5\F0\E8\F2\FC \F3\F1\EB\EE\E2\E8\FF \EF\EE\F1\F2\E0\ED\EE\E2\EA\E8
void autoShipsSet(char a[], int checkMap[]);//\E0\E2\F2\EE\EC\E0\F2\E8\F7\E5\F1\EA\E8 \F0\E0\F1\F1\F2\E0\E2\E8\F2\FC \EA\EE\F0\E0\E1\EB\E8 \E8 \EF\F0\EE\E2\E5\F0\E8\F2\FC \F3\F1\EB\EE\E2\E8\FF \EF\EE\F1\F2\E0\ED\EE\E2\EA\E8
int getUserInput();
int getMachineInput();
bool isWin(char a[]);
void setInput(int userInput, char userFleet[], char userMap[]);
char checkShot(int input, char a[]);
int checkShip(char a[], int userInputOne, int userInputTwo);
int max(int a, int b);
int min(int a, int b);
void showShipsLeft(int a[]);
void userPlay(char userFleet[], char userMap[], int checkMap[], int shipsLeft[]);
void userSetShips(char userFleet[], int CheckMap[]);
void machineEazyPlay(char machineFleet[], char machineMap[], int checkMap[]);
int machineMediumPlay(char machineFleet[], char machineMap[], int checkMap[]);
void setShipEnviroment(int input, char userMap[], int checkMap[]);
int getShipSize(int input, int checkMap[]);
void killShip(int input, int checkMap[], int shipsLeft[]);

int firstShot, secondShot, shotMode, vector=0, shotsCount=0;

void main()
{
	setlocale(LC_ALL, "russian");
	srand(time(0));

	int input, setSetting, gameMode, level;

	char userOneFleet[12 * 12], userTwoFleet[12 * 12], userOneMap[12 * 12], userTwoMap[12 * 12];
	int userOneCheckMap[12 * 12], userTwoCheckMap[12 * 12];

	int shipsLeftOnFleetOne[4] = { 4,3,2,1 };
	int shipsLeftOnFleetTwo[4] = { 4,3,2,1 };


	

	set_mass(userOneFleet);
	set_mass(userOneMap);
	set_mass(userTwoFleet);
	set_mass(userTwoMap);


	cout << "\C2\FB\E1\E5\F0\E8\F2\E5 \F0\E5\E6\E8\EC \E8\E3\F0\FB " << endl << "0 - \E8\E3\F0\E0 \F1 \EF\EE\EB\FC\E7\EE\E2\E0\F2\E5\EB\E5\EC " << endl << "1 - \E8\E3\F0\E0 \F1 \EA\EE\EC\EF\FC\FE\F2\E5\F0\EE\EC" << endl;

	cin >> gameMode;


	switch (gameMode) {
	case 0:

	
		userSetShips(userOneFleet, userOneCheckMap);
		userSetShips(userTwoFleet, userTwoCheckMap);

		cout << "\CD\C0\D7\C0\CB\CE \C8\C3\D0\DB" << endl;

		while (isWin(userOneMap) && isWin(userTwoMap))
		{
			cout << "\D5\EE\E4 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0: " << endl;
			cout << endl;

			userPlay(userTwoFleet, userOneMap, userTwoCheckMap, shipsLeftOnFleetTwo);

			if (isWin(userOneMap) == false)
				break;
			cout << "\D5\EE\E4 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0: " << endl;
			cout << endl;

			userPlay(userOneFleet, userTwoMap, userOneCheckMap, shipsLeftOnFleetOne);

		}

		if (isWin(userOneMap) == false)
		{

			cout << "\CF\EE\E1\E5\E4\E8\EB \EF\E5\F0\E2\FB\E9 \E8\E3\F0\EE\EA" << endl;

			cout << "\CF\EE\EB\E5 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneFleet);

			cout << "\CF\EE\EB\E5 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoFleet);

		}
		else
		{
			cout << "\CF\EE\E1\E5\E4\E8\EB \E2\F2\EE\F0\EE\E9 \E8\E3\F0\EE\EA" << endl;

			cout << "\CF\EE\EB\E5 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoFleet);

			cout << "\CF\EE\EB\E5 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneFleet);
		}

		system("pause");
		break;

	case 1:

		

		userSetShips(userOneFleet, userOneCheckMap);
		autoShipsSet(userTwoFleet, userTwoCheckMap);

		cout << "\C2\E2\E5\E4\E8\F2\E5 \F3\F0\EE\E2\E5\ED\FC \F1\EB\EE\E6\ED\EE\F1\F2\E8 \EF\F0\EE\F2\E8\E2\ED\E8\EA\E0: \n";
		cout << "0 - \EF\F0\EE\F1\F2\EE\E9 \n";
		cout << "1 - \F1\F0\E5\E4\ED\E8\E9 " << endl;
		

		cin >> level;

		cout << "\CD\C0\D7\C0\CB\CE \C8\C3\D0\DB" << endl;

		int countOne = 0, countTwo = 0;
		while (isWin(userOneMap) && isWin(userTwoMap))
		{

			cout << "\D5\EE\E4 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0: " << endl;

			userPlay(userTwoFleet, userOneMap, userTwoCheckMap, shipsLeftOnFleetOne);

			if (isWin(userOneMap) == false)
				break;

			cout << "\D5\EE\E4 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0: " << endl;
			switch (level)
			{
			case 0:
				machineEazyPlay(userOneFleet, userTwoMap, userOneCheckMap);
				break;
			case 1:
				machineMediumPlay(userOneFleet, userTwoMap, userOneCheckMap);
				break;
			}

		}

		if (isWin(userOneMap) == false)
		{

			cout << "\CF\EE\E1\E5\E4\E8\EB \EF\E5\F0\E2\FB\E9 \E8\E3\F0\EE\EA" << endl;

			cout << "\CF\EE\EB\E5 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneFleet);

			cout << "\CF\EE\EB\E5 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoFleet);

		}
		else
		{
			cout << "\CF\EE\E1\E5\E4\E8\EB \E2\F2\EE\F0\EE\E9 \E8\E3\F0\EE\EA" << endl;

			cout << "\CF\EE\EB\E5 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoFleet);

			cout << "\CF\EE\EB\E5 \E2\F2\EE\F0\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userTwoMap);

			cout << "\CA\EE\F0\E0\E1\EB\E8 \EF\E5\F0\E2\EE\E3\EE \E8\E3\F0\EE\EA\E0" << endl;
			show(userOneFleet);
		}

		system("pause");

		break;
	}

}



void set_mass(char a[])   //\EC\E0\F1\F1\E8\E2 12 \ED\E0 12, \EF\E5\F0\E2\E0\FF \F1\F2\F0\EE\F7\EA\E0 - \E1\F3\EA\E2\FB, \EB\E5\E2\FB\E9 \F1\F2\EE\EB\E1\E5\F6 - \F6\E8\F4\F0\FB, \EF\EE\F1\E5\F0\E5\E4\E8\ED\E5 - \E8\E3\F0\EE\E2\EE\E5 \EF\EE\EB\E5 10 \ED\E0 10
{
	int i;
	int count = 0;
	char letters[12] = { ' ' , 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' , ' ' };

	for (i = 0; i < 144; i++)
		a[i] = ' ';

	for (i = 0; i < 12; i++) //\E7\E0\EF\EE\EB\ED\E5\ED\E8\E5 \E1\F3\EA\E2\E0\EC\E8
		a[i] = letters[i];

	for (i = 12; i <= 120; i += 12)
	{
		a[i] = count + '0'; //\EF\E5\F0\E5\E2\EE\E4 \F6\E8\F4\F0 \E2 char \E8 \E7\E0\EF\EE\EB\ED\E5\ED\E8\E5 \E8\EC\E8
		count++;
	}
	count = 0;

	for (i = 13; i <= 130; i++) //\E7\E0\EF\EE\EB\ED\E5\ED\E8\E5 \E8\E3\F0\EE\E2\EE\E3\EE \EF\EE\EB\FF
	{
		if (count == 10)
		{
			count = 0;
			i += 2;
		}
		a[i] = '~';
		count++;
	}
}

void show(char a[]) //\EF\EE\EA\E0\E7\FB\E2\E0\E5\F2 \EE\E4\ED\EE\EC\E5\F0\ED\FB\E9 \EC\E0\F1\F1\E8\E2 \E2 \E2\E8\E4\E5 \F2\E0\E1\EB\E8\F6\FB
{
	int i, count = 0;

	for (i = 0; i < 144; i++)
	{
		if (count == 12)
		{
			cout << endl;
			count = 0;
		}

		cout << setw(4) << a[i];
		count++;

	}
	cout << endl;

}

void shipsSet(char userFleet[], int checkMap[])
{
	int i, k, userInputOne, userInputTwo, size;
	int shipTopCoordinate, shipBottomCoordinate;
	int shipsLeft[4] = { 4,3,2,1 };            //\F1\F7\E5\F2\F7\E8\EA \EE\F1\F2\E0\E2\F8\E8\F5\F1\FF \EA\EE\F0\E0\E1\EB\E5\E9 (\F7\E5\F2\E2\E5\F0\EA\E8, \F2\F0\E5\F8\EA\E8, \E4\E2\F3\F8\EA\E8, \EE\E4\ED\F3\F8\EA\E8)

	for (i = 0; i < 10; i++) { //10 \EA\EE\F0\E0\E1\EB\E5\E9

		do
		{
			cout << "\C2\E2\E5\E4\E8\F2\E5 \EA\EE\EE\F0\E4\E8\ED\E0\F2\F3 \ED\E0\F7\E0\EB\E0 \EA\EE\F0\E0\E1\EB\FF: ";
			userInputOne = getUserInput();
			cout << "\C2\E2\E5\E4\E8\F2\E5 \EA\EE\EE\F0\E4\E8\ED\E0\F2\F3 \EA\EE\ED\F6\E0 \EA\EE\F0\E0\E1\EB\FF: ";
			userInputTwo = getUserInput();

			if (abs(userInputOne - userInputTwo) < 4)            //\E2\FB\F7\E8\F1\EB\E5\ED\E8\E5 \F0\E0\E7\EC\E5\F0\E0 \EA\EE\F0\E0\E1\EB\FF \E2 \E7\E0\E2\E8\F1\E8\EC\EE\F1\F2\E8 \EE\F2 \EF\EE\EB\EE\E6\E5\ED\E8\FF
				size = abs(userInputOne - userInputTwo);
			else
				size = abs(userInputOne - userInputTwo) / 12;


		} while (checkShip(userFleet, userInputOne, userInputTwo) == 0 || shipsLeft[size] == 0);   //\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \EF\EE\EB\EE\E6\E5\ED\E8\E5 \E8 \ED\E0 \EE\F1\F2\E0\F2\EE\EA \EA\EE\F0\E0\E1\EB\E5\E9 \E2 \E7\E0\EF\E0\F1\E5

		shipTopCoordinate = min(userInputOne, userInputTwo);
		shipBottomCoordinate = max(userInputOne, userInputTwo);

		switch (checkShip(userFleet, userInputOne, userInputTwo))
		{

		case 1:

			for (k = shipTopCoordinate; k <= shipBottomCoordinate; k += 12)   //\EF\EE\F1\F2\E0\ED\EE\E2\EA\E0 \EA\EE\F0\E0\E1\EB\FF
			{
				userFleet[k] = '!';
				checkMap[k] = shipTopCoordinate + 2000;
			}

			killShip(shipTopCoordinate, checkMap, shipsLeft); //\E2\FB\F7\E8\F2\E0\ED\E8\E5 \EA\EE\F0\E0\E1\EB\FF \E8\E7 \F1\EF\E8\F1\EA\E0 \EE\F1\F2\E0\E2\F8\E8\F5\F1\FF
			showShipsLeft(shipsLeft);

			show(userFleet);

			break;

		case 2:

			for (k = min(userInputOne, userInputTwo); k <= max(userInputOne, userInputTwo); k++)
			{
				userFleet[k] = '!';
				checkMap[k] = shipTopCoordinate + 1000;
			}

			killShip(shipTopCoordinate, checkMap, shipsLeft);
			showShipsLeft(shipsLeft);

			show(userFleet);

			break;
		}

	}
}

void autoShipsSet(char machineFleet[], int checkMap[]) 
{
	int i, k, machineInputOne, machineInputTwo, size;
	int shipTopCoordinate, shipBottomCoordinate;
	int currentSize = 3; //\EF\E5\F0\E2\FB\EC \F0\E0\F1\F1\F2\E0\E2\EB\FF\E5\F2\F1\FF \EA\EE\F0\E0\E1\EB\FC \F1 \F0\E0\E7\EC\E5\F0\EE\EC 3
	int countOfInputs = 0;
	int shotMode = 0;
	bool incorrectInput;
	int shipsLeft[4] = { 4,3,2,1 };            //\F1\F7\E5\F2\F7\E8\EA \EE\F1\F2\E0\E2\F8\E8\F5\F1\FF \EA\EE\F0\E0\E1\EB\E5\E9 (\F7\E5\F2\E2\E5\F0\EA\E8, \F2\F0\E5\F8\EA\E8, \E4\E2\F3\F8\EA\E8, \EE\E4\ED\F3\F8\EA\E8)

	for (i = 0; i < 10; i++) { //10 \EA\EE\F0\E0\E1\EB\E5\E9

		incorrectInput = true;

			while (incorrectInput)
			{

				machineInputOne = getMachineInput();

				while (incorrectInput)
				{

					if (countOfInputs == 8)
					{
						countOfInputs = 0;
						break;
					}

					switch (rand() % 4) {

					case 0:

						machineInputTwo = machineInputOne + 1 * currentSize;
						countOfInputs++;
						break;

					case 1:

						machineInputTwo = machineInputOne - 1 * currentSize;
						countOfInputs++;

						break;

					case 2:

						machineInputTwo = machineInputOne + 12 * currentSize;
						countOfInputs++;
						break;

					case 3:

						machineInputTwo = machineInputOne - 12 * currentSize;
						countOfInputs++;
						break;

					}

					if (abs(machineInputOne - machineInputTwo) < 4)            //\E2\FB\F7\E8\F1\EB\E5\ED\E8\E5 \F0\E0\E7\EC\E5\F0\E0 \EA\EE\F0\E0\E1\EB\FF \E2 \E7\E0\E2\E8\F1\E8\EC\EE\F1\F2\E8 \EE\F2 \EF\EE\EB\EE\E6\E5\ED\E8\FF
						size = abs(machineInputOne - machineInputTwo);
					else
						size = abs(machineInputOne - machineInputTwo) / 12;

					if (checkShip(machineFleet, machineInputOne, machineInputTwo) != 0 && shipsLeft[size] != 0)
						incorrectInput = false;//\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \EF\EE\EB\EE\E6\E5\ED\E8\E5 \E8 \ED\E0 \EE\F1\F2\E0\F2\EE\EA \EA\EE\F0\E0\E1\EB\E5\E9 \E2 \E7\E0\EF\E0\F1\E5

				}
				}

			shipTopCoordinate = min(machineInputOne, machineInputTwo);
			shipBottomCoordinate = max(machineInputOne, machineInputTwo);

			switch (checkShip(machineFleet, machineInputOne, machineInputTwo))   //\E2\FB\F7\E8\F1\EB\E5\ED\E8\E5 \EF\EE\EB\EE\E6\E5\ED\E8\FF \EA\EE\F0\E0\E1\EB\FF
			{
			case 1:

				for (k = shipTopCoordinate; k <= shipBottomCoordinate; k += 12) { //\EF\EE\F1\F2\E0\ED\EE\E2\EA\E0 \EA\EE\F0\E0\E1\EB\FF
					
					machineFleet[k] = '!';
					checkMap[k] = shipTopCoordinate + 2000;
				}

				killShip(shipTopCoordinate, checkMap, shipsLeft);

				break;

			case 2:

				for (k = shipTopCoordinate; k <= shipBottomCoordinate; k++) {
					machineFleet[k] = '!';
					checkMap[k] = shipTopCoordinate + 1000;
				}

				killShip(shipTopCoordinate, checkMap, shipsLeft);

				break;
			}

			if (shipsLeft[getShipSize(shipTopCoordinate, checkMap) - 1] == 0)
				currentSize--;

		}

	}

int getUserInput()
{
	char userLetter;
	int userNumber;
	map <char, int> lettersToNumbers;
	lettersToNumbers['A'] = 11;
	lettersToNumbers['B'] = 10;
	lettersToNumbers['C'] = 9;
	lettersToNumbers['D'] = 8;
	lettersToNumbers['E'] = 7;
	lettersToNumbers['F'] = 6;
	lettersToNumbers['G'] = 5;
	lettersToNumbers['H'] = 4;
	lettersToNumbers['I'] = 3;
	lettersToNumbers['J'] = 2;

	lettersToNumbers['a'] = 11;
	lettersToNumbers['b'] = 10;
	lettersToNumbers['c'] = 9;
	lettersToNumbers['d'] = 8;
	lettersToNumbers['e'] = 7;
	lettersToNumbers['f'] = 6;
	lettersToNumbers['g'] = 5;
	lettersToNumbers['h'] = 4;
	lettersToNumbers['i'] = 3;
	lettersToNumbers['j'] = 2;

	do
	{


		cin >> userLetter >> userNumber;

		if (userNumber < 0 || userNumber > 9 || lettersToNumbers[userLetter] == 0)
			cout << "\CD\E5\EA\EE\F0\F0\E5\EA\F2\ED\FB\E9 \E2\E2\EE\E4" << endl;

		cin.clear();

	} while (userNumber < 0 || userNumber >9 || lettersToNumbers[userLetter] == 0);


	return (userNumber + 2) * 12 - lettersToNumbers[userLetter];   //\EF\E5\F0\E5\E2\EE\E4 \EA\EE\EE\F0\E4\E8\ED\E0\F2 \EF\EE\EB\FC\E7\EE\E2\E0\F2\E5\EB\FF \F1 \EF\EE\EB\FF 10\F510 \E2 \EF\EE\EB\E5 12\F512

}

int getMachineInput() {

	char letters[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	map <char, int> lettersToNumbers;
	lettersToNumbers['A'] = 11;
	lettersToNumbers['B'] = 10;
	lettersToNumbers['C'] = 9;
	lettersToNumbers['D'] = 8;
	lettersToNumbers['E'] = 7;
	lettersToNumbers['F'] = 6;
	lettersToNumbers['G'] = 5;
	lettersToNumbers['H'] = 4;
	lettersToNumbers['I'] = 3;
	lettersToNumbers['J'] = 2;


	return (rand() % 10 + 2) * 12 - lettersToNumbers[letters[rand() % 10]];
}

void setInput(int userInput, char userFleet[], char userMap[]) {    //\E2\E2\EE\E4 \EF\EE\EB\FC\E7\EE\E2\E0\F2\E5\EB\FF, \EF\F0\EE\E2\E5\F0\EA\E0 \E2\FB\F1\F2\F0\E5\EB\E0 \EF\EE \F4\EB\EE\F2\F3 , \E7\E0\ED\E5\F1\F2\E8 \E2\FB\F1\F2\F0\E5\EB \ED\E0 \EA\E0\F0\F2\F3
	if (checkShot(userInput, userFleet) != '0')
		userMap[userInput] = checkShot(userInput, userFleet);
}

char checkShot(int input, char a[])  //\EA\E0\EA\EE\E5 \EF\EE\EF\E0\E4\E0\ED\E8\E5 \EF\F0\EE\E8\E7\EE\F8\EB\EE
{
	if (a[input] == '~')
		return 'O';
	else if (a[input] == '!')
		return 'X';
	else
		return '0';
}

int checkShip(char a[], int userInputOne, int userInputTwo)
{
	int i, j;
	if (abs(userInputOne - userInputTwo) % 12 == 0 && abs(userInputOne - userInputTwo) / 12 < 4)  //\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \EF\EE\EB\EE\E6\E5\ED\E8\E5 \E8 \E4\E8\E0\E3\EE\ED\E0\EB\FC
	{

		for (i = min(userInputOne, userInputTwo); i <= max(userInputOne, userInputTwo); i+=12)
			if (a[i] != '~')
				return 0;

		for (i = min(userInputOne, userInputTwo) - 13; i <= max(userInputOne, userInputTwo) + 11; i += 12)  // \EF\F0\EE\E2\E5\F0\EA\E0 \EE\EA\F0\F3\E6\E5\ED\E8\FF \EA\EE\F0\E0\E1\EB\FF \E4\EB\FF \E8\E7\E1\E5\E6\E0\ED\E8\FF "\F1\F2\E0\EB\EA\E8\E2\E0\ED\E8\FF"
			for (j = i; j < i + 3; j++)
				if (a[j] == '!')
					return 0; // \EF\F0\EE\E2\E5\F0\EA\F3 \ED\E5 \EF\F0\EE\F8\E5\EB
		return 1;  //\EA\EE\F0\E0\E1\EB\FC \ED\E0\F5\EE\E4\E8\F2\F1\FF \E2 \E2\E5\F0\F2\E8\EA\E0\EB\FC\ED\EE\EC \EF\EE\EB\EE\E6\E5\ED\E8\E8
	}
	else if (abs(userInputOne - userInputTwo) < 4) //\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \E4\E8\E0\E3\EE\ED\E0\EB\FC
	{

		for (i = min(userInputOne, userInputTwo); i <= max(userInputOne, userInputTwo); i++)
			if (a[i] != '~')
				return 0;

		for (i = min(userInputOne, userInputTwo) - 13; i <= min(userInputOne, userInputTwo) + 11; i += 12) //\EF\F0\EE\E2\E5\F0\EA\E0 \EE\EA\F0\F3\E6\E5\ED\E8\FF
			for (j = i; j <= i + 2 + abs(userInputOne - userInputTwo); j++)
				if (a[j] == '!')
					return 0;
		return 2; //\EA\EE\F0\E0\E1\EB\FC \ED\E0\F5\EE\E4\E8\F2\F1\FF \E2 \E3\EE\F0\E8\E7\EE\ED\F2\E0\EB\FC\ED\EE\EC \EF\EE\EB\EE\E6\E5\ED\E8\E8
	}
	return 0;

}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

bool isWin(char a[]) {  //\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \EF\EE\E1\E5\E4\F3
	int i, count = 0;
	for (i = 0; i < 144; i++)
		if (a[i] == 'X')
			count++;
	cout << "Count = " << count << endl;
	if (count == 20)
		return false;
	return true;
}

void showShipsLeft(int a[]) {

	cout << "\D7\E5\F2\E2\E5\F0\EE\EA \EE\F1\F2\E0\EB\EE\F1\FC: " << a[3] << endl;
	cout << "\D2\F0\E5\F8\E5\EA \EE\F1\F2\E0\EB\EE\F1\FC: " << a[2] << endl;
	cout << "\C4\E2\F3\F8\E5\EA \EE\F1\F2\E0\EB\EE\F1\FC: " << a[1] << endl;
	cout << "\CE\E4\ED\F3\F8\E5\EA \EE\F1\F2\E0\EB\EE\F1\FC: " << a[0] << endl;
}

bool isKill(int input, char userMap[], int checkMap[])
{
	int size, i, shots;

	switch (checkMap[input] / 1000)
	{
	case 1:

		size = getShipSize(input, checkMap);

		shots = 0;

		for (i = checkMap[input] % 1000; i <= checkMap[input] % 1000 + 3; i++)
			if (userMap[i] == 'X')
				shots++;

		if (shots == size)
			return true;

		break;
	case 2:

		size = getShipSize(input, checkMap);

		shots = 0;

		for (i = checkMap[input] % 1000; i <= checkMap[input] % 1000 + 12 * 3; i += 12)
			if (userMap[i] == 'X')
				shots++;

		if (shots == size)
			return true;

		break;
	}
	return false;
}

void userPlay(char userFleet[], char userMap[], int checkMap[], int shipsLeft[]) {

	
	showShipsLeft(shipsLeft);

	cout << endl;

	while (true)
	{
		int input;

		

		show(userMap);

		cout << "\C2\E0\F8 \F5\EE\E4: ";

		do
		{
			input = getUserInput();
		} while (checkShot(input, userFleet) == '0' || checkShot(input, userMap) == '0'); //\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \E2\E2\EE\E4

		setInput(input, userFleet, userMap);


		if (checkShot(input, userFleet) == 'X') {   //\E2\EE\E7\E2\F0\E0\F9\E0\E5\F2 \F5 \E5\F1\EB\E8 \EA\EB\E5\F2\EE\F7\EA\E0 \F0\E0\E2\ED\E0 ~

			if (isKill(input, userMap, checkMap)) {
				cout << "\D3\ED\E8\F7\F2\EE\E6\E5\ED" << endl;
				killShip(input, checkMap, shipsLeft);
				setShipEnviroment(input, userMap, checkMap);

			}
			else
				cout << "\C2\FB \EF\EE\EF\E0\EB\E8" << endl;

		}
		else
		{
			cout << "\C2\FB \EF\F0\EE\EC\E0\E7\E0\EB\E8" << endl;
			show(userMap);
			system("pause");
			break; //\E7\E0\EA\E0\ED\F7\E8\E2\E0\E5\F2 \F6\E8\EA\EB \F5\EE\E4\EE\E2 \EF\F0\E8 \EF\F0\EE\EC\E0\F5\E5
		}
		if (isWin(userMap) == false)
			break;
	}

	system("cls");

}

int machineMediumPlay(char userFleet[], char machineMap[], int userFleetMap[]) {

	int randomNextShot;
	 // \EA\E0\F0\F2\E0 \E2\FB\F1\F2\F0\E5\EB\EE\E2. 1 - \EC\EE\E6\ED\EE \F1\F2\F0\E5\EB\FF\F2\FC, 0 - \ED\E5\EB\FC\E7\FF
	while (true)
	{
		switch (shotMode)
		{
		
		case 1:
			switch (vector) 
			{
			case 0:
				do
				{
			
					randomNextShot = rand() % 4;
					

					switch (randomNextShot) {

					case 0:

						secondShot = firstShot + 1;
					

						break;

					case 1:

						secondShot = firstShot - 1;
						
						break;

					case 2:

						secondShot = firstShot + 12;

						break;

					case 3:

						secondShot = firstShot - 12;

						break;

					}
				} while (checkShot(secondShot, userFleet) == '0' || checkShot(secondShot, machineMap) == '0');
				break;

			case 1: //\F1\F2\F0\E5\EB\FC\E1\E0 \E2\E5\F0\F2\E8\EA\E0\EB\FC\ED\EE

				do
				{
					randomNextShot = rand() % 2;

					switch (randomNextShot) {

					case 0:

						secondShot = secondShot + 12;

						break;

					case 1:

						secondShot = secondShot - 12;

						break;

					}

				} while (checkShot(secondShot, userFleet) == '0' || checkShot(secondShot, machineMap) == '0');
				break;

			case 2:
				do
				{
					randomNextShot = rand() % 2;

					switch (randomNextShot) {

					case 0:

						secondShot = secondShot + 1;

						break;

					case 1:

						secondShot = secondShot - 1;

						break;

					}
				} while (checkShot(secondShot, userFleet) == '0' || checkShot(secondShot, machineMap) == '0');
				break;
			}

			cout << "Machine shot = " << secondShot << endl;
			setInput(secondShot, userFleet, machineMap);

			if (checkShot(secondShot, userFleet) == 'X')
			{

				cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \EF\EE\EF\E0\EB" << endl;
	
				if (isKill(firstShot, machineMap, userFleetMap))
				{
					cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \F3\ED\E8\F7\F2\EE\E6\E8\EB" << endl;
					shotMode = 0;
					vector = 0;
					shotsCount = 0;
					setShipEnviroment(firstShot, machineMap, userFleetMap);
					show(machineMap);
					system("pause");
					return 0;
				}

				shotsCount++;

				if (abs(firstShot - secondShot) % 12 == 0) //\EA\EE\F0\E0\E1\EB\FC \F1\F2\EE\E8\F2 \E2\E5\F0\F2\E8\EA\E0\EB\FC\ED\EE 
				{
					vector = 1;
				}
				else
				{
					vector = 2;
				}

				show(machineMap);

				system("pause");

			}
			else 
			{

				cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \EF\F0\EE\EC\E0\E7\E0\EB" << endl;
				if (shotsCount >= 2)
					secondShot = firstShot;
				    
				show(machineMap);

				system("pause");
				return 0; ////\E7\E0\EA\E0\ED\F7\E8\E2\E0\E5\F2 \F6\E8\EA\EB \F5\EE\E4\EE\E2 \EF\F0\E8 \EF\F0\EE\EC\E0\F5\E5
			}

				break;

		case 0:

			do
			{

				firstShot = getMachineInput();

			} while (checkShot(firstShot, userFleet) == '0' || checkShot(firstShot, machineMap) == '0'); //\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \E2\E2\EE\E4

			cout << "Machine shot 2 = " << secondShot << endl;
			setInput(firstShot, userFleet, machineMap);

			if (checkShot(firstShot, userFleet) == 'X')
			{

				cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \EF\EE\EF\E0\EB" << endl;
				

				if (isKill(firstShot, machineMap, userFleetMap))
				{
					cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \F3\ED\E8\F7\F2\EE\E6\E8\EB" << endl;
					setShipEnviroment(firstShot, machineMap, userFleetMap);
					show(machineMap);
					system("pause");
					return 0;
				}

				shotMode = 1;
				shotsCount++;

				show(machineMap);

				system("pause");

			}
			else
			{

				cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \EF\F0\EE\EC\E0\E7\E0\EB" << endl;

				show(machineMap);

				system("pause");


				return 0; ////\E7\E0\EA\E0\ED\F7\E8\E2\E0\E5\F2 \F6\E8\EA\EB \F5\EE\E4\EE\E2 \EF\F0\E8 \EF\F0\EE\EC\E0\F5\E5
			}

			break;
		}

		if (isWin(machineMap) == false)
			break;

	

	}
	return 1;
}

void machineEazyPlay(char machineFleet[], char machineMap[], int checkMap[]) {

	while (true)
	{

		int input;

		do
		{

			input = getMachineInput();

		} while (checkShot(input, machineFleet) == '0' || checkShot(input, machineMap) == '0'); //\EF\F0\EE\E2\E5\F0\EA\E0 \ED\E0 \E2\E2\EE\E4



		setInput(input, machineFleet, machineMap);


		if (checkShot(input, machineFleet) == 'X')
		{

			cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \EF\EE\EF\E0\EB" << endl;
			
			show(machineMap);

			system("pause");

		}
		else
		{

			cout << "\CA\EE\EC\EF\FC\FE\F2\E5\F0 \EF\F0\EE\EC\E0\E7\E0\EB" << endl;

			show(machineMap);

			system("pause");
			break; //\E7\E0\EA\E0\ED\F7\E8\E2\E0\E5\F2 \F6\E8\EA\EB \F5\EE\E4\EE\E2 \EF\F0\E8 \EF\F0\EE\EC\E0\F5\E5
		}

		if (isWin(machineMap) == false)
			break;
	}

	system("cls");

}

void userSetShips(char userFleet[], int CheckMap[]) {

	show(userFleet);

	int setSetting;
	cout << "\C2\FB\E1\E5\F0\E8\F2\E5 \F0\E0\F1\F1\F2\E0\ED\EE\E2\EA\F3" << endl << " 0 - \EF\EE\EB\FC\E7\EE\E2\E0\F2\E5\EB\FC\F1\EA\E0\FF \F0\E0\F1\F1\F2\E0\ED\EE\E2\EA\E0 " << endl << " 1 - \E0\E2\F2\EE \F0\E0\F1\F1\F2\E0\ED\EE\E2\EA\E0 " << endl;
	cin >> setSetting;
	if (setSetting == 0)
		shipsSet(userFleet, CheckMap);
	else
		autoShipsSet(userFleet, CheckMap);

	show(userFleet);

	system("pause");
	system("cls");
}

void setShipEnviroment(int input, char userMap[], int checkMap[])
{

	int i, j, size;

	switch (checkMap[input] / 1000)

	{

	case 1:

		size = getShipSize(input, checkMap);

		for (i = checkMap[input] % 1000 - 13; i <= checkMap[input] % 1000 + 11; i += 12)
			for (j = i; j <= i + 1 + size; j++)
				if (userMap[j] == '~')
					userMap[j] = 'O'; //\E3\EE\F0\E8\E7\EE\ED\F2\E0\EB\FC\ED\EE 

		break;
	case 2:

		size = getShipSize(input, checkMap);

		for (i = checkMap[input] % 1000 - 13; i <= checkMap[input] % 1000 - 13 + 12 * (1 + size); i += 12)  // \EF\F0\EE\E2\E5\F0\EA\E0 \EE\EA\F0\F3\E6\E5\ED\E8\FF \EA\EE\F0\E0\E1\EB\FF \E4\EB\FF \E8\E7\E1\E5\E6\E0\ED\E8\FF "\F1\F2\E0\EB\EA\E8\E2\E0\ED\E8\FF"
			for (j = i; j < i + 3; j++)
				if (userMap[j] == '~')
					userMap[j] = 'O';

		break;
	}

}

int getShipSize(int input, int checkMap[]) {
	int size = 0, i;
	switch (checkMap[input] / 1000)
	{
	case 1:
		for (i = checkMap[input] % 1000; i <= checkMap[input] % 1000 + 3; i++)
			if (checkMap[i] == checkMap[checkMap[input] % 1000]) //\E2\FB\F7\E8\F1\EB\E5\ED\E8\FF \F0\E0\E7\EC\E5\F0\E0 \EA\EE\F0\E0\E1\EB\FF \EF\EE \EA\EE\F0\E0\E1\EB\FE. 
				size++;
		break;
	case 2:
		for (i = checkMap[input] % 1000; i <= checkMap[input] % 1000 + 12 * 3; i += 12)
			if (checkMap[i] == checkMap[checkMap[input] % 1000])
				size++;
		break;
	}
	return size;

}

void killShip(int input, int checkMap[], int shipsLeft[])
{
	int size;
	size = getShipSize(input, checkMap);
	shipsLeft[size - 1]--;
}
