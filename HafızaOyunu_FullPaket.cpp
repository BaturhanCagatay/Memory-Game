#include <iostream>
#include <windows.h> 
#include <chrono>
#include <thread>
#include <iomanip>
#include <fstream>
#include <string>


using namespace std;

// Function 13: This function reads the record...
void readRecordedUsers();
//*****************************************************************************************

// Function 12: This function save the movement - point ...
void recordUser(const string& username, int point, int movement, int cardNumber);
//*****************************************************************************************

// Function 11: This Function to save the game state to a file...
void saveGame(int** numberArray, int** zeroArray, int cardNumber, int movement, int point, const string& saveFileName);
//*****************************************************************************************

// Function 10: This function controls the win...
bool gameWin(int** array, int size);
//*****************************************************************************************

// Function 9: This function changes the text color to white...
void systemWhite();
//*****************************************************************************************

// Function 8: This function takes card's row and column's value...
struct cards {
	int fCardR;
	int fCardC;
	int sCardR;
	int sCardC;

	// fCardR = first card's row || fCardC = first card's column || sCardR = second card's row || sCardC = second card's column
};
cards takeCards(int size);
//*****************************************************************************************

// Function 7 : This function cleans the screen...
void systemClear();
//*****************************************************************************************

// Function 6 : This function pauses the code...
void systemWait(int x);
//*****************************************************************************************

// Function 5 : This function shows arrays...
void printArray(int** array, int cardNumber);
//*****************************************************************************************

// Function 1 : This function that finds the total size of the table...
int findingGlass();
//*****************************************************************************************

// Function 2 : This function opens the menu to be selected at the beginning of the game... 
int openingMenu();
//*****************************************************************************************

// Function 3: This function mixes numbers and fills them...
void fillNumbers(int **array, int cardNumber);
//*****************************************************************************************

// Function 4: This function fills zero...
void fillZero(int **array ,int cardNumber);
//*****************************************************************************************


// General Game Function....
void generalFlow() {
	
	jump:

	int choice;
	choice = openingMenu();
	int cardNumber;

	if (choice == 1) {
		cardNumber = findingGlass();
		int point = 0;
		int movement = 0;
		bool gameControl = true;

		int** numberArray = new int* [cardNumber];
		for (int i = 0; i < cardNumber; i++) {
			numberArray[i] = new int [cardNumber];
		}

		int** zeroArray = new int* [cardNumber];
		for (int i = 0; i < cardNumber; i++) {
			zeroArray[i] = new int[cardNumber];
		}

		fillNumbers(numberArray, cardNumber);
		printArray(numberArray, cardNumber);
		systemWait(2);
		systemClear();

		fillZero(zeroArray, cardNumber);
		printArray(zeroArray, cardNumber);

		while (gameControl) {

			systemWhite();
			cout << "Your Number Of Move:" << movement << endl;

			cards selectedCard = takeCards(cardNumber);
			systemWhite();

			cout << "First Card's Row: " << selectedCard.fCardR << "And Column: " << selectedCard.fCardC << endl;;
			cout << "Second Card's Row: " << selectedCard.sCardR << "And Column: " << selectedCard.sCardC<<endl;
			cout << "First Value: " << numberArray[selectedCard.fCardR][selectedCard.fCardC]<<endl;
			cout << "Second Value: " << numberArray[selectedCard.sCardR][selectedCard.sCardC] << endl;
			movement++;
			
			if (selectedCard.fCardR == selectedCard.sCardR && selectedCard.sCardC == selectedCard.fCardC) {
				string saveFileName;
				cout << "Enter the save file name: " << endl;
				cin >> saveFileName;
				saveGame(numberArray,zeroArray,cardNumber,movement,point,saveFileName);
				break;
			}


			if (numberArray[selectedCard.fCardR][selectedCard.fCardC] != 0) {
				zeroArray[selectedCard.fCardR][selectedCard.fCardC] = numberArray[selectedCard.fCardR][selectedCard.fCardC];
				numberArray[selectedCard.fCardR][selectedCard.fCardC] = 0;
			}

			else {
				cout << "Please Enter Row And Column Value For An Unopened Card..." << endl;
			}

			if (numberArray[selectedCard.sCardR][selectedCard.sCardC] != 0) {
				zeroArray[selectedCard.sCardR][selectedCard.sCardC] = numberArray[selectedCard.sCardR][selectedCard.sCardC];
				numberArray[selectedCard.sCardR][selectedCard.sCardC] = 0;
			}

			else {
				cout << "Please Enter Row And Column Value For An Unopened Card..."<<endl;
			}

			printArray(zeroArray, cardNumber);
			
			if (zeroArray[selectedCard.fCardR][selectedCard.fCardC] != zeroArray[selectedCard.sCardR][selectedCard.sCardC]) {
				int var1, var2;
				var1 = zeroArray[selectedCard.fCardR][selectedCard.fCardC];
				zeroArray[selectedCard.fCardR][selectedCard.fCardC] = numberArray[selectedCard.fCardR][selectedCard.fCardC];
				numberArray[selectedCard.fCardR][selectedCard.fCardC] = var1;

				var2 = zeroArray[selectedCard.sCardR][selectedCard.sCardC];
				zeroArray[selectedCard.sCardR][selectedCard.sCardC] = numberArray[selectedCard.sCardR][selectedCard.sCardC];
				numberArray[selectedCard.sCardR][selectedCard.sCardC] = var2;

				point -= 1;
				cout << "Your Guess Is Not Correct..." << endl;
				cout << "Point: " << point << endl;
				
				systemWait(2);
				systemClear();

			}
			
			else {
				point += 3;
				cout << "Your Guess Is Correct..." << endl;
				cout << "Point: " << point << endl;
				systemWait(2);
				systemClear();
			}

			gameControl = gameWin(zeroArray, cardNumber);
			
		}
		// Record Part...
		string name;
		cout << "Can You Write User Name:" << endl;
		cin >> name;
		recordUser(name, point, movement, cardNumber);


		//Delete Parts
		for (int i = 0; i < cardNumber; i++) {
			delete[] numberArray[i];
		}
		delete[] numberArray;

		for (int i = 0; i < cardNumber; i++) {
			delete[] zeroArray[i];
		}
		delete[] zeroArray;
	}

	else if(choice == 2){
		
		string saveFileName;
		cout << "Enter the save file name: ";
		cin >> saveFileName;
		ifstream file(saveFileName);

		if (file.is_open()) {
			int savedCardNumber, savedMovement, savedPoint;

			file >> savedCardNumber;
			file >> savedMovement;
			file >> savedPoint;

			int** savedNumberArray = new int* [savedCardNumber];
			int** savedZeroArray = new int* [savedCardNumber];

			for (int i = 0; i < savedCardNumber; i++) {
				savedNumberArray[i] = new int[savedCardNumber];
				for (int j = 0; j < savedCardNumber; j++) {
					file >> savedNumberArray[i][j];
				}
			}

			for (int i = 0; i < savedCardNumber; i++) {
				savedZeroArray[i] = new int[savedCardNumber];
				for (int j = 0; j < savedCardNumber; j++) {
					file >> savedZeroArray[i][j];
				}
			}

			file.close();
			bool gameControl = true;
			printArray(savedNumberArray, savedCardNumber);
			printArray(savedZeroArray, savedCardNumber);
			while (gameControl) {

				systemWhite();
				cout << "Your Number Of Move:" << savedMovement << endl;

				cards selectedCard = takeCards(savedCardNumber);
				systemWhite();

				cout << "First Card's Row: " << selectedCard.fCardR << "And Column: " << selectedCard.fCardC << endl;;
				cout << "Second Card's Row: " << selectedCard.sCardR << "And Column: " << selectedCard.sCardC << endl;
				cout << "First Value: " << savedNumberArray[selectedCard.fCardR][selectedCard.fCardC] << endl;
				cout << "Second Value: " << savedNumberArray[selectedCard.sCardR][selectedCard.sCardC] << endl;
				savedMovement++;

				if (selectedCard.fCardR == selectedCard.sCardR || selectedCard.sCardC == selectedCard.fCardC) {
					string saveFileName;  // Declare a variable to store the save file name
					cout << "Enter the save file name: " << endl;
					cin >> saveFileName;
					saveGame(savedNumberArray, savedZeroArray, savedCardNumber, savedMovement, savedPoint,saveFileName);
					break;
				}


				if (savedNumberArray[selectedCard.fCardR][selectedCard.fCardC] != 0) {
					savedZeroArray[selectedCard.fCardR][selectedCard.fCardC] = savedNumberArray[selectedCard.fCardR][selectedCard.fCardC];
					savedNumberArray[selectedCard.fCardR][selectedCard.fCardC] = 0;
				}

				else {
					cout << "Please Enter Row And Column Value For An Unopened Card..." << endl;
				}

				if (savedNumberArray[selectedCard.sCardR][selectedCard.sCardC] != 0) {
					savedZeroArray[selectedCard.sCardR][selectedCard.sCardC] = savedNumberArray[selectedCard.sCardR][selectedCard.sCardC];
					savedNumberArray[selectedCard.sCardR][selectedCard.sCardC] = 0;
				}

				else {
					cout << "Please Enter Row And Column Value For An Unopened Card..." << endl;
				}

				printArray(savedZeroArray, savedCardNumber);

				if (savedZeroArray[selectedCard.fCardR][selectedCard.fCardC] != savedZeroArray[selectedCard.sCardR][selectedCard.sCardC]) {
					int var1, var2;
					var1 = savedZeroArray[selectedCard.fCardR][selectedCard.fCardC];
					savedZeroArray[selectedCard.fCardR][selectedCard.fCardC] = savedNumberArray[selectedCard.fCardR][selectedCard.fCardC];
					savedNumberArray[selectedCard.fCardR][selectedCard.fCardC] = var1;

					var2 = savedZeroArray[selectedCard.sCardR][selectedCard.sCardC];
					savedZeroArray[selectedCard.sCardR][selectedCard.sCardC] = savedNumberArray[selectedCard.sCardR][selectedCard.sCardC];
					savedNumberArray[selectedCard.sCardR][selectedCard.sCardC] = var2;

					savedPoint -= 1;
					cout << "Your Guess Is Not Correct..." << endl;
					cout << "Point: " << savedPoint << endl;

					systemWait(2);
					systemClear();

				}

				else {
					savedPoint += 3;
					cout << "Your Guess Is Correct..." << endl;
					cout << "Point: " << savedPoint << endl;
					systemWait(2);
					systemClear();
				}

				gameControl = gameWin(savedZeroArray,savedCardNumber);


			}
			
		}
		else {
			cout << "No saved game state found!" << endl;
			goto jump;
		}
		
		
}

	else if (choice == 3) {
		systemClear();
		readRecordedUsers();
		goto jump;
	}

	else if (choice == 4) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 13);
		
		cout << "       Rules......" << endl;
		cout << "1) When Entering Card Number, It Must Be Even Number" << endl;
		cout << "2) Be Careful to Choose Unopened Cards While Choosing Cards." << endl;
		cout << "3) While playing the game, if you enter the same row and column value in both card selections, it will switch to the save game screen and save the game to the name you want." << endl;
		cout << "4)If you are going to open the game in saved games, you must enter the file name in the same way."<<endl;
		
		char button;
		cout << "\n If you want to return to the menu, press CTRL.\n";
		SetConsoleTextAttribute(hConsole, 15);

		while (true) {
			if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
				system("cls");
				goto jump;
			}
		}

	}

	else if (choice == 5) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 14);

		cout << "... Exiting the game ..." << endl;
		
		systemWait(1);
		systemClear();
		exit(0);
	}
}
//****************************************************************************************



int main()
{
	generalFlow();
}



//****************************************************************************************

// Function 1 : The function that finds the total size of the table...
int findingGlass() {
	int choice = 0;
	bool flag = false;

	while (!false) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, 11);
		cout << "How Many Cards Would You Like To Play With?" << endl;
		cin >> choice;


		if (choice % 2 != 0) {
			SetConsoleTextAttribute(hConsole, 5);
			cout << "Please Divide The Number You Have Chosen By 2 !" << endl;
			flag = false;
		}
		else if (choice < 2) {
			SetConsoleTextAttribute(hConsole, 5);
			cout << "The Number Must Be Greater Than 2 !" << endl;
			flag = false;
		}
		else {
			return choice;
			flag = true;
		}
	}
	return choice;
}
//*****************************************************************************************


// Function 2 : This function opens the menu to be selected at the beginning of the game... 
int openingMenu() {

	int choice;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 5);
	cout << "Menu..." << endl;

	SetConsoleTextAttribute(hConsole, 10);
	cout << "1)Start A New Game..." << endl;

	SetConsoleTextAttribute(hConsole, 11);
	cout << "2)Load From Saved Game..." << endl;

	SetConsoleTextAttribute(hConsole, 12);
	cout << "3)Records..." << endl;

	SetConsoleTextAttribute(hConsole, 9);
	cout << "4)Rules..." << endl;

	SetConsoleTextAttribute(hConsole, 14);
	cout << "5)Exit..." << endl;

	SetConsoleTextAttribute(hConsole, 15);
	cout << "Please Enter The Number Of Transaction You Want To Do?\n";
	cin >> choice;


	return choice;
}
//*****************************************************************************************


// Function 3: This function mixes numbers and fills them...
void fillNumbers(int **array, int cardNumber) {
	int num = 1;
	int constant = 0;
	int** numbers = new int* [cardNumber];
	for (int i = 0; i < cardNumber; i++) {
		numbers[i] = new int[cardNumber];
		for (int j = 0; j < cardNumber; j++) {
			numbers[i][j] = num;
			constant += 1;
			if (constant == 2) {
				num ++ ;
				constant =0;
			}
		}
	}
	srand(time(NULL));
	int control = 0;
	for (int i = 0; i < cardNumber; i++) {
		for (int j = 0; j < cardNumber; j++) {
			// a random row and column are selected...
			int row = rand() % cardNumber;
			int col = rand() % cardNumber;
			// continue selecting a random cell as long as the selected cell in the numbers array is 0...
			while (*(*(numbers + row) + col) == 0) {
				row = rand() % cardNumber;
				col = rand() % cardNumber;
			}
			// the number in the selected cell of the numbers array is assigned to the corresponding cell in the array, and the selected cell in the numbers array is set to 0...
			*(*(array + i) + j) = *(*(numbers + row) + col);
			*(*(numbers + row) + col) = 0;
			control++;
			// if all cells have been checked, all numbers have been assigned to the array...
			if (control == cardNumber* cardNumber) {
				break;
			}
		};
	}

	// numbers array is deallocated...
	for (int i = 0; i < cardNumber; i++) {
		delete[] numbers[i];
	}
	delete[] numbers;


	// filling numbers four by four...
}
//*****************************************************************************************


// Function 4: This function fills zero...
void fillZero(int **array,int cardNumber) {
	int** zero = new int* [cardNumber];
	for (int i = 0; i < cardNumber; i++) {
		zero[i] = new int[cardNumber];
		for (int j = 0; j < cardNumber; j++) {
			zero[i][j] = 0;
		}
	}
	for (int i = 0; i < cardNumber; i++) {
		for (int j = 0; j < cardNumber; j++) {
			array[i][j] = zero[i][j];
		}
	}

	for (int i = 0; i < cardNumber; i++) {
		delete[] zero[i];
	}
	delete[] zero;

}
//*****************************************************************************************


//Function 5 : The function shows arrays...
void printArray(int** array, int size) {
	cout << "   ";
	for (int j = 0; j < size; j++) {
		
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 15);
		cout << setw(6) << j + 1;  // Use setw to set the width of each column

	}
	cout << endl;

	for (int i = 0; i < size; i++) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 15);
		cout << setw(2) << i + 1 << "  ";  // Use setw to set the width of row numbers

		for (int j = 0; j < size; j++) {
			int num = array[i][j];
			if (num == 0) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "| " << setw(2) << num << " |";  // Use setw to set the width of each square
			}
			else {
				int color = (num % 6) + 1; // pick a color based on the number (1-6)
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, color);
				cout << "| " << setw(2) << array[i][j] << " |";  // Use setw to set the width of each square
			}
		}
		cout << "\n";
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}
//*****************************************************************************************


// Function 6 : This function pauses the code
void systemWait(int x) {
	this_thread::sleep_for(std::chrono::seconds(x));
}
//*****************************************************************************************


// Function 7 : This function cleans the screen
void systemClear() {
	system("cls");
}
//*****************************************************************************************


// Function 8: This function takes card's row and column's value... 
cards takeCards(int size) {
	int fCardR, fCardC, sCardR, sCardC;
	bool flag = false;
	bool error1 = false;
	bool error2 = false;


	while (!flag) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 5);
		cout << "Could You Please Enter the Row And Column Values Of The 1st Number In Order?" << endl;
		cin >> fCardR >> fCardC;

		SetConsoleTextAttribute(hConsole, 6);
		cout << "Could You Please Enter The Row And Column Values Of The 2nd Number In Order?" << endl;
		cin >> sCardR >> sCardC;

		if (fCardR < 0 || fCardR > size || fCardC < 0 || fCardC > size) {
			SetConsoleTextAttribute(hConsole, 8);
			cout << "Please Review The Values You Entered For The First Card Again..." << endl;
			error1 = true;
		}
		if (sCardR < 0 || sCardR > size || sCardC < 0 || sCardC > size) {
			SetConsoleTextAttribute(hConsole, 8);
			cout << "Please Review The Values You Entered For The Second Card Again..." << endl;
			error2 = true;
		}

		if (error1 || error2) {
			flag = false;
			error1 = false;
			error2 = false;
		}
		else {
			flag = true;
		}
	}

	cards result;
	result.fCardR = fCardR-1;
	result.fCardC = fCardC-1;
	result.sCardR = sCardR-1;
	result.sCardC = sCardC-1;

	return result;
}
//*****************************************************************************************


// Function 9: This function changes the text color to white...
void systemWhite() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}
//*****************************************************************************************


// Function 10: This function controls the win...
bool gameWin(int** array, int size) {

	int total=0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (array[i][j] != 0) {
				total += 1;	 
			}
		}
	}
	if (total == (size * size)) {

		return false;
	}
	return true;
}
//*****************************************************************************************


// Function 11: This Function to save the game state to a file...
void saveGame(int** numberArray, int** zeroArray, int cardNumber, int movement, int point, const string& saveFileName) {
	ofstream file(saveFileName);
	if (file.is_open()) {
		file << cardNumber << "\n";
		file << movement << "\n";
		file << point << "\n";
		for (int i = 0; i < cardNumber; i++) {
			for (int j = 0; j < cardNumber; j++) {
				file << numberArray[i][j] << " ";
			}
			file << "\n";
		}
		for (int i = 0; i < cardNumber; i++) {
			for (int j = 0; j < cardNumber; j++) {
				file << zeroArray[i][j] << " ";
			}
			file << "\n";
		}
		file.close();
		cout << "Game saved successfully!\n";
	}
	else {
		cout << "Unable to save the game!\n";
	}
}
//*****************************************************************************************


// Function 12: This function saves the movement - point ...
void recordUser(const string& username, int point, int movement, int cardNumber) {
	ofstream outputFile("record_users.txt", ios::app);
	if (outputFile.is_open()) {
		outputFile << "Username: " << username << endl;
		outputFile << "Point: " << point << endl;
		outputFile << "Movement: " << movement << endl;
		outputFile << "Card Number: " << cardNumber << endl;
		outputFile << "---------------------------" << endl;
		outputFile.close();
		cout << "User record has been saved successfully." << endl;
	}
	else {
		cout << "Unable to open the record_users.txt file." << endl;
	}
}
//*****************************************************************************************


// Function 13: This function reads the record...
void readRecordedUsers() {
	ifstream inputFile("record_users.txt");
	if (inputFile.is_open()) {
		string line;
		while (getline(inputFile, line)) {
			cout << line << endl;
		}
		inputFile.close();
	}
	else {
		cout << "Unable to open the record_users.txt file." << endl;
	}
}
//*****************************************************************************************