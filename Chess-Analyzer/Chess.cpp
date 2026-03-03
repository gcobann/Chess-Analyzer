#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Structure to hold coordinates(Row and Column)
struct Coords
{
	int rows;
	int cols;
};

// Function to create a random board and save it
void generateBoard()
{
	// --- Random Parameter Generation ---
	int boardSize = 5 + rand() % 26; // Random board size between 5 and 30
	int queensCount = 1 + rand() % (boardSize * 2); // Random number of queens between 1 and 2*boardSize
	int obstaclesCount;


	// Calculate Obstacles (X) based on the rule: 0 <= X <= (N - Q)
	// If (N - Q) <= 0, then X = 0
	if ((boardSize - queensCount) <= 0)
	{
		obstaclesCount = 0;
	}
	else
	{
		obstaclesCount = rand() % ((boardSize - queensCount) + 1); // Random number of obstacles
	}

	// --- Dynamic Memory Allocation ---
	// Dynamic Memory Allocation
	char** tempBoard = new char* [boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		tempBoard[i] = new char[boardSize];
		for (int j = 0; j < boardSize; j++)
		{
			tempBoard[i][j] = '0'; // Initialize board with '0's
		}
	}

	// Place Queens (Q) and Obstacles (X) randomly on the board
	int queensCounter = 0;
	while (queensCounter < queensCount)
	{
		int randRow = rand() % boardSize;
		int randCol = rand() % boardSize;

		if (tempBoard[randRow][randCol] == '0')
		{
			tempBoard[randRow][randCol] = 'Q'; // Place queen
			queensCounter++;
		}
	}

	int obstaclesCounter = 0;
	while (obstaclesCounter < obstaclesCount)
	{
		int randRow = rand() % boardSize;
		int randCol = rand() % boardSize;

		// Only place an obstacle if the cell is empty
		if (tempBoard[randRow][randCol] == '0')
		{
			tempBoard[randRow][randCol] = 'X'; // Place obstacle
			obstaclesCounter++;
		}
	}


	// Saving the raw board representation to input.txt
	ofstream outFile("input.txt");
	if (outFile.is_open())
	{
		for (int ae = 0; ae < boardSize; ae++)
		{
			for (int gs = 0; gs < boardSize; gs++)
			{
				outFile << tempBoard[ae][gs];
			}
			outFile << endl;
		}
		outFile.close();
		cout << "Board created and saved to input.txt" << endl;
	}
	else
	{
		cout << "Unable to open file" << endl;
	}

	// --- Memory Cleanup ---
	// Deallocating the dynamic array to prevent memory leaks
	for (int ae = 0; ae < boardSize; ae++)
	{
		delete[] tempBoard[ae];
	}
	delete[] tempBoard;
}

// Function to read the board from input.txt, analyze movement possibilities, and show output
void showOutput()
{
	// --- File Reading and Preparation ---
	ifstream inFile("input.txt");
	if (!inFile.is_open())
	{
		cout << "Unable to open input.txt" << endl;
		return;
	}

	// Determine board size from the first line
	string line;
	int boardSize = 0;
	if (getline(inFile, line))
	{
		boardSize = line.length();
	}

	// Reset file pointer to the beginning to read the board
	inFile.clear();
	inFile.seekg(0);

	// --- Dynamic Allocation for Analysis ---
	char** board = new char* [boardSize]; // To hold the board
	bool** visited = new bool* [boardSize]; // To track reachable squares

	// Dynamic arrays to hold queen and obstacle coordinates
	Coords* queens = new Coords[boardSize * boardSize];
	Coords* obstacles = new Coords[boardSize * boardSize];

	int qCount = 0;
	int xCount = 0;

	// Reading the file and populating our data structures
	for (int ae = 0; ae < boardSize; ae++)
	{
		board[ae] = new char[boardSize];
		visited[ae] = new bool[boardSize];
		inFile >> line;

		for (int gs = 0; gs < boardSize; gs++)
		{
			board[ae][gs] = line[gs];
			visited[ae][gs] = false; // Initialize visited to false

			// If we find, store queen and obstacle coordinates 
			if (board[ae][gs] == 'Q')
			{
				queens[qCount].rows = ae;
				queens[qCount].cols = gs;
				qCount++;
			}
			else if (board[ae][gs] == 'X')
			{
				obstacles[xCount].rows = ae;
				obstacles[xCount].cols = gs;
				xCount++;
			}
		}
	}
	inFile.close();

	// --- Movement Analysis ---
	// Directions: up, right, left, down, up-left, up-right, down-left, down-right
	int mRow[] = { -1, 0, 0, 1, -1, -1, 1, 1 };
	int mCol[] = { 0, 1, -1, 0, -1, 1, -1, 1 };

	// Analyze each queen's movement
	for (int h = 0; h < qCount; h++)
	{
		int startRow = queens[h].rows;
		int startCol = queens[h].cols;

		// Check all 8 directions for current queen
		for (int m = 0; m < 8; m++)
		{
			int nextRow = startRow + mRow[m];
			int nextCol = startCol + mCol[m];

			// Move in the current direction until hitting an obstacle or board edge
			while (nextRow >= 0 && nextRow < boardSize && nextCol >= 0 && nextCol < boardSize)
			{
				// Stop if we hit an obstacle or another queen
				if (board[nextRow][nextCol] == 'X' || board[nextRow][nextCol] == 'Q')
				{
					break;
				}

				// Mark the square as reachable
				visited[nextRow][nextCol] = true;

				// Move to the next square in the same direction
				nextRow += mRow[m];
				nextCol += mCol[m];
			}
		}
	}

	// --- Calculating Results ---
	// Count total reachable squares
	int totalReachable = 0;
	for (int ae = 0; ae < boardSize; ae++)
	{
		for (int gs = 0; gs < boardSize; gs++)
		{
			if (visited[ae][gs])
			{
				totalReachable++;
			}
		}
	}

	// --- Reporting ---
	// Prepare output file
	ofstream outFile("output.txt");

	// Print basic info (to console and file)
	cout << "Board Size: " << boardSize << "x" << boardSize << endl;
	if (outFile.is_open())
	{
		outFile << "Board Size: " << boardSize << "x" << boardSize << endl;
	}

	cout << "Number of Queens: " << qCount << endl;
	if (outFile.is_open())
	{
		outFile << "Number of Queens: " << qCount << endl;
	}

	cout << "Number of Obstacles: " << xCount << endl;
	if (outFile.is_open())
	{
		outFile << "Number of Obstacles: " << xCount << endl;
	}

	// Print queen positions
	cout << "Queen Positions: ";
	if (outFile.is_open())
	{
		outFile << "Queen Positions: ";
	}

	for (int ae = 0; ae < qCount; ae++)
	{
		cout << "(" << queens[ae].rows + 1 << ", " << queens[ae].cols + 1 << ") ";
		if (outFile.is_open())
		{
			outFile << "(" << queens[ae].rows + 1 << ", " << queens[ae].cols + 1 << ") ";
		}
	}

	cout << endl;
	if (outFile.is_open())
	{
		outFile << endl;
	}

	cout << endl;
	if (outFile.is_open())
	{
		outFile << endl;
	}

	// Print obstacle positions
	cout << "Obstacle Positions: ";
	if (outFile.is_open())
	{
		outFile << "Obstacle Positions: ";
	}
	for (int ae = 0; ae < xCount; ae++)
	{
		cout << "(" << obstacles[ae].rows + 1 << ", " << obstacles[ae].cols + 1 << ") ";
		if (outFile.is_open())
		{
			outFile << "(" << obstacles[ae].rows + 1 << ", " << obstacles[ae].cols + 1 << ") ";
		}
	}

	cout << endl;
	if (outFile.is_open())
	{
		outFile << endl;
	}

	cout << endl;
	if (outFile.is_open())
	{
		outFile << endl;
	}

	// Print total reachable squares
	cout << "Total Reachable Squares: " << totalReachable << endl;
	if (outFile.is_open())
	{
		outFile << "Total Reachable Squares: " << totalReachable << endl;
	}

	cout << endl;
	if (outFile.is_open())
	{
		outFile << endl;
	}

	// Print list of reachable points
	cout << "Reachable Points: ";
	if (outFile.is_open())
	{
		outFile << "Reachable Points: ";
	}
	for (int ae = 0; ae < boardSize; ae++)
	{
		for (int gs = 0; gs < boardSize; gs++)
		{
			if (visited[ae][gs])
			{
				cout << "(" << ae << ", " << gs << ") ";
				if (outFile.is_open())
				{
					outFile << "(" << ae << ", " << gs << ") ";
				}
			}
		}
	}

	cout << endl;
	if (outFile.is_open())
	{
		outFile << endl;
	}

	// --- Visual Board Representation ---
	cout << "\n---------------------------" << endl;
	cout << "CHESS BOARD" << endl;
	cout << "Q - Queens" "\nX - Obstacles" "\n0 - Empty/unreachable Cell" "\n + - Possible Movement" << endl;
	cout << "---------------------------" << endl;

	if (outFile.is_open())
	{
		outFile << "\n---------------------------" << endl;
		outFile << "CHESS BOARD" << endl;
		outFile << "Q - Queens" "\nX - Obstacles" "\n0 - Empty/unreachable Cell" "\n+ - Possible Movement" << endl;
		outFile << "---------------------------" << endl;
	}

	// Loop to print the board with symbols
	for (int ae = 0; ae < boardSize; ae++)
	{
		cout << "|";
		if (outFile.is_open())
		{
			outFile << "|";
		}

		for (int gs = 0; gs < boardSize; gs++)
		{
			char symbol;
			if (board[ae][gs] == 'Q')
			{
				symbol = 'Q';
			}
			else if (board[ae][gs] == 'X')
			{
				symbol = 'X';
			}
			else if (visited[ae][gs])
			{
				symbol = '+'; // Possible empty cell
			}
			else
			{
				symbol = '0'; // Unreachable empty cell
			}

			// Print to console and file
			cout << " " << symbol << " ";
			if (outFile.is_open())
			{
				outFile << " " << symbol << " ";
			}
		}

		// End of row with border
		cout << "|" << endl;
		if (outFile.is_open())
		{
			outFile << "|" << endl;
		}
	}

	// Bottom border line
	cout << "---------------------------" << endl;
	if (outFile.is_open())
	{
		outFile << "---------------------------" << endl;
	}

	if (outFile.is_open())
	{
		outFile.close();
	}

	// --- Memory Cleanup ---
	// Deallocating all dynamic arrays used in this function
	for (int ae = 0; ae < boardSize; ae++)
	{
		delete[] board[ae];
		delete[] visited[ae];
	}
	delete[] board;
	delete[] visited;

	delete[] queens;
	delete[] obstacles;
}

// --- Main Function with Menu ---
int main()
{
	srand(time(0)); // Seed for random number generation

	int choice;
	do
	{
		cout << "\n ---Main Menu---" << endl;
		cout << "1.Create a new board" << endl;
		cout << "2.Show output" << endl;
		cout << "3.Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			generateBoard();
			break;
		case 2:
			showOutput();
			break;
		case 3:
			cout << "Exiting program." << endl;
			break;
		default:
			cout << "Invalid choice!";
		}
	} while (choice != 3);

	return 0;
}