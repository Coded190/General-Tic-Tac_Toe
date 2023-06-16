//meaningful names, not extensible
#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

Player set_player(int);
void generate_board(int&, int&);
void set_board(char[][15]);
void game(char[][15], Player[], int&, int, int, int&);
void display_board(char[][15], int, int);
string get_choice(Player[], int, char[][15], int, int);
char set_choice(char[][15], Player[], int&, int, int, string, int&);
char check_status(char[][15], Player[], int, int, int, int, int&);
void display_full_statistics(Player[], int&, int);
char to_UpperCase(char);
string upper_case_name(string);
void display_board_num(char[][15], int, int);
void display_board_lines(char[][15], int, int);
void display_board_letters(char[][15], int, int, char&, int);
char is_game_over(char[][15], Player[], int, int);
int letter_to_int(char);
int validate_player_count(int);
void validate_name(string&, string&);
void validate_choice(string&, char[][15], int, int);
char to_LowerCase(char);
string validateName(string);

const int MAX_ROW = 11;
const int MAX_COL = 15;

int main()
{
	int player_count = 0;
	Player player[6];
	int player_number = 0;
	int starting_player = 2;
	int game_starter = 0;
	int row = 0;
	int col = 0;
	char board_max[MAX_ROW][MAX_COL];
	char status_of_game = 'y';
	char again = 'y';
	int total_games = 0;

	cout << "Welcome to Tic-Tac-Toe!\n";
	cout << "\nPlease enter the number of players for each game (MIN 3 / MAX 6): ";
	player_count = validate_player_count(player_count);
	cout << endl;

	for (int i = 0; i < player_count; i++)
	{
		player_number++;
		player[i] = set_player(player_number);
	}
	string again2 = "y";

	do
	{
		game_starter = starting_player;
		total_games++;
		generate_board(row, col);
		set_board(board_max);
		do
		{
			game(board_max, player, starting_player, row, col, player_number);
			status_of_game = check_status(board_max, player, starting_player,
				row, col, player_number, total_games);

			starting_player++;
			if (status_of_game == 'd')
			{
				starting_player = game_starter + 1;
			}

			if (starting_player == player_number)
			{
				starting_player = 0;
			}

		} while (status_of_game == 'y');
		cout << "Would you like to play again (y/n): ";

		getline(cin >> ws, again2);
		for (int i = 0; i < again2.length(); i++)
		{
			again2[i] = to_LowerCase(again2[i]);
		}
		cout << endl;

	} while (again2 == "y" || again2 == "yes");

	return 0;
}


//-------------------------------------------------------------
// Validates the name inputed by the user to fit 
// specifications and return the string
// 
// @param - string
// @return - string
//-------------------------------------------------------------

string validateName(string str)
{
	bool flag = false;
	bool whiteSpaceFlag = false;
	int nameCount = 0;
	int whitespace = 0;
	cout << "Please enter a name: ";
	getline(cin >> ws, str);

	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]))
		{
			cout << "Try again: \n";

			return validateName(str);
		}
		if (isalpha(str[i]))
		{
			nameCount++;
			while (isalpha(str[i]))
			{
				i++;
			}
		}
		if (nameCount > 2)	
		{
			cout << "Try again: \n";
			return validateName(str);
		}

		string first;
		string last;
		string name = str;
		string tempFirst;
		string tempLast;
		bool change = false;
		bool leading = false;
		for (int i = 0; i < name.length(); i++)
		{
			while (name[i] == ' ' && !leading)
			{
				i++;
			}
			leading = true;

			while (name[i] == ' ' && leading)
			{
				change = true;
				i++;
			}

			if (!change)
			{
				tempFirst += name[i];
			}

			if (change)
			{
				tempLast += name[i];
			}
		}

		tempFirst += " ";
		tempFirst += tempLast;
		name = tempFirst;

		bool flag = false;

		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] == ' ')
			{
				flag = true;
				continue;
			}

			if (!flag)
			{
				first += name[i];
			}

			if (flag)
			{
				last += name[i];
			}
		}

		for (int i = 0; i < first.length(); i++)
		{
			if (!(isalpha(first[i])))
			{
				cout << "Try again: \n";

				return validateName(str);
			}
		}

		for (int i = 0; i < last.length(); i++)
		{
			if (!(isalpha(last[i])))
			{
				cout << "Try again: \n";

				return validateName(str);
			}
		}
	}
	return str;
}


//-------------------------------------------------------------
// Set the player object with first and last name, and symbol.
// 
// @param - int
// @return - Player
//-------------------------------------------------------------

Player set_player(int player_number)
{
	Player player;
	string first;
	string last;
	string name;

	//cout << "Enter Player " << player_number <<
	//	"'s first and last name (separated by a space) : ";
	//cin.clear();
	//getline(cin >> ws, name);

	name = validateName(name);


	string tempFirst;
	string tempLast;
	bool change = false;
	bool leading = false;
	for (int i = 0; i < name.length(); i++)
	{
		while (name[i] == ' ' && !leading)	//doesn't work with 3 input names
		{			
			i++;
		}
		leading = true;

		while (name[i] == ' ' && leading)
		{
			change = true;
			i++;
		}

		if (!change)
		{
			tempFirst += name[i];
		}

		if (change)
		{
			tempLast += name[i];
		}
	}

	tempFirst += " ";
	tempFirst += tempLast;
	name = tempFirst;

	bool flag = false;

	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] == ' ')
		{
			flag = true;
			continue;
		}

		if (!flag)
		{
			first += name[i];
		}

		if (flag)
		{
			last += name[i];
		}
	}

	validate_name(first, last);
	first = upper_case_name(first);
	last = upper_case_name(last);
	player.setFirstName(first);
	player.setLastName(first);
	player.setFullName(first, last);

	switch (player_number)
	{
	case 1:
		player.setSymbol('a');
		break;
	case 2:
		player.setSymbol('b');
		break;
	case 3:
		player.setSymbol('c');
		break;
	case 4:
		player.setSymbol('d');
		break;
	case 5:
		player.setSymbol('e');
		break;
	default:
		player.setSymbol('f');
		break;
	}

	return player;
	cout << endl;
}


//-------------------------------------------------------------
// Generates the board based on the user input for row and 
// column.
// 
// @param - int&
// @return - int&
//-------------------------------------------------------------

void generate_board(int& row, int& col)
{
	string str;
	string fullString;
	bool flag;
	bool flag2;

	cout << "Please enter the dimension of the board.\n\n";
	cout << "Enter the number of rows    -> ";
	cin.clear();
	getline(cin >> ws, fullString);

	do
	{
		flag = false;
		flag2 = false;
		for (int i = 0; i < fullString.length(); i++)
		{
			if (fullString[i] == ' ')
			{
				flag2 = true;
			}
		}

		if (flag2)
		{
			cout << "Please enter a valid number: ";
			cin.clear();
			getline(cin >> ws, fullString);
		}
		else
		{
			str = fullString;
			for (int i = 0; i < str.length(); i++)
			{
				if ((!(isdigit(str[i]))))
				{
					flag = true;
				}
			}

			if (flag)
			{
				cout << "Please enter a valid number! (MIN 3 / MAX 11):here ";
				cin.clear();
				getline(cin >> ws, fullString);

				//cin >> str;
				//cin.clear();
				//cin.ignore(INT_MAX, '\n');
			}
			else
			{
				row = stoi(str);

				if (row < 3 || row > 11)
				{
					cout << "Please enter a valid number! (MIN 3 / MAX 11):HERE ";
					cin.clear();
					getline(cin >> ws, fullString);

					//cin >> str;
					//cin.clear();
					//cin.ignore(INT_MAX, '\n');
					flag = true;
				}
			}
		}
	} while (flag || flag2);

	cout << "\nEnter the number of columns -> ";
	cin.clear();
	getline(cin >> ws, fullString);

	do
	{
		flag = false;
		flag2 = false;
		for (int i = 0; i < fullString.length(); i++)
		{
			if (fullString[i] == ' ')
			{
				flag2 = true;
			}
		}

		if (flag2)
		{
			cout << "Please enter a valid number: ";
			cin.clear();
			getline(cin >> ws, fullString);
		}
		else
		{
			str = fullString;
			for (int i = 0; i < str.length(); i++)
			{
				if ((!(isdigit(str[i]))))
				{
					flag = true;
				}
			}

			if (flag)
			{
				cout << "Please enter a valid number! (MIN 3 / MAX 15): ";
				cin.clear();
				getline(cin >> ws, fullString);

				//cin >> str;
				//cin.clear();
				//cin.ignore(INT_MAX, '\n');
			}
			else
			{
				col = stoi(str);

				if (col < 3 || col > 15)
				{
					cout << "Please enter a valid number! (MIN 3 / MAX 15): ";
					cin.clear();
					getline(cin >> ws, fullString);

					//cin >> str;
					//cin.clear();
					//cin.ignore(INT_MAX, '\n');
					flag = true;
				}
			}
		}
	} while (flag || flag2);

	cout << endl;
}


//-------------------------------------------------------------
// Sets the board with empty spaces
// 
// @param - char[][15]
// @return - void
//-------------------------------------------------------------

void set_board(char board_max[][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			board_max[i][j] = ' ';
		}
	}
}


//-------------------------------------------------------------
// Displays current board, then prompts user for their choice. 
// Sets the choice on the board.
// 
// @param - char[][15], Player[], int&, int, int, int&
// @return - void
//-------------------------------------------------------------

void game(char board_max[][MAX_COL], Player player[6], int& starting_player,
	int row, int col, int& player_number)
{
	string choice;
	char valid;

	display_board(board_max, row, col);
	cout << endl;

	do
	{
		valid = 'y';
		choice = get_choice(player, starting_player, board_max, row, col);

		valid = set_choice(board_max, player, starting_player, row, col,
			choice, player_number);

	} while (valid == 'n');
}


//-------------------------------------------------------------
// Displays the updated board.
// 
// @param - char[][15], int, int
// @return - void
//-------------------------------------------------------------

void display_board(char board_max[][MAX_COL], int row, int col)
{
	char row_char = 'A';

	display_board_num(board_max, row, col);

	display_board_lines(board_max, row, col);

	for (int i = 0; i < row; i++)
	{
		display_board_letters(board_max, row, col, row_char, i);
		display_board_lines(board_max, row, col);
	}

	display_board_num(board_max, row, col);
}


//-------------------------------------------------------------
// Displays the board numbers.
// 
// @param - char[][15], int, int
// @return - void
//-------------------------------------------------------------

void display_board_num(char board_max[][MAX_COL], int row, int col)
{
	cout << " ";
	for (int i = 1; i <= col; i++)
	{
		if (i == 10)
		{
			cout << " ";
		}

		if (i < 10)
		{
			cout << "   " << i;
		}
		else
		{
			cout << "  " << i;
		}
	}

	cout << endl;
}


//-------------------------------------------------------------
// Displays the board lines.
// 
// @param - char[][15], int, int
// @return - void
//-------------------------------------------------------------

void display_board_lines(char board_max[][MAX_COL], int row, int col)
{
	cout << "  ";
	for (int i = 1; i <= col; i++)
	{
		cout << " ---";
	}
	cout << endl;
}


//-------------------------------------------------------------
// Displays the board letters and player pieces.
// 
// @param - char[][15], int, int, char&, int
// @return - void
//-------------------------------------------------------------

void display_board_letters(char board_max[][MAX_COL], int row, int col,
	char& row_char, int j)
{
	cout << row_char << " |";

	for (int i = 0; i < col; i++)
	{
		cout << " " << board_max[j][i] << " |";
	}

	cout << " " << row_char << endl;

	row_char++;
}


//-------------------------------------------------------------
// Prompts user by name for their choice, then validates 
// choice.
// 
// @param - Player[], int, char[][15], int, int
// @return - string
//-------------------------------------------------------------

string get_choice(Player player[6], int starting_player, char board_max[][15],
	int row, int col)
{
	string choice;
	cout << player[starting_player].getFirstName() << " (" << 
		player[starting_player].getSymbol() << "), please enter your choice: ";
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	validate_choice(choice, board_max, row, col);

	cout << endl;

	return choice;
}


//-------------------------------------------------------------
// Sets user's choice to spot on board. 
// Validates it's spot is valid
// 
// @param - char[][15], Player[], int&, int, int, string, int&
// @return - char
//-------------------------------------------------------------

char set_choice(char board_max[][MAX_COL], Player player[6], int& starting_player,
	int row, int col, string choice, int& player_number)
{
	char valid = 'y';
	char letter = choice[0];
	int letter_row = letter_to_int(letter);
	int num = 0;

	if (choice.length() == 2)
	{
		num = choice[1] - '1';
	}
	else if (choice.length() == 3)
	{
		int number1 = choice[1] - '0';
		int number2 = choice[2] - '1';
		num = (number1 * 10) + number2;
	}

	char symbol = player[starting_player].getSymbol();
	if (board_max[letter_row][num] != ' ')
	{
		valid = 'n';
		cout << "That spot is taken! Pick another. \n\n";
	}
	else
	{
		board_max[letter_row][num] = symbol;
	}

	return valid;
}


//-------------------------------------------------------------
// Checks the board for wins, draws, or continue playing 
// the game.
// 
// @param - char[][15], Player[], int, int, int, int, int&
// @return - char
//-------------------------------------------------------------

char check_status(char board_max[][MAX_COL], Player player[6], int starting_player,
	int row, int col, int player_number, int& total_games)
{
	char status = ' ';
	int current_player = 0;

	status = is_game_over(board_max, player, row, col);

	if (status == 'w')
	{
		cout << endl << player[starting_player].getFullName() << " wins!\n\n";
		display_board(board_max, row, col);

		for (int i = 0; i < player_number; i++)
		{
			if (current_player == starting_player)
			{
				player[current_player].win();
			}
			else
			{
				player[current_player].loss();
			}
			current_player++;
		}
		display_full_statistics(player, total_games, player_number);
	}
	else if (status == 'd')
	{
		cout << "Draw Game!\n\n";
		display_board(board_max, row, col);

		for (int i = 0; i < player_number; i++)
		{
			player[i].draw();
		}
		display_full_statistics(player, total_games, player_number);
	}
	else
	{
		status = 'y';
	}
	cout << endl;

	return status;
}


//-------------------------------------------------------------
// Checks the rows, columns, and diagonals for 3 consecutive 
// same symbols.
// 
// @param - char[][15], Player[], int, int
// @return - char
//-------------------------------------------------------------

char is_game_over(char board_max[][MAX_COL], Player player[6], int row, int col)
{
	char status = ' ';

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < (col - 2); j++)
		{
			if (board_max[i][j] != ' ' &&
				to_LowerCase(board_max[i][j]) == to_LowerCase(board_max[i][j + 1]) &&
				to_LowerCase(board_max[i][j + 1]) ==
				to_LowerCase(board_max[i][j + 2]))
			{
				board_max[i][j] = to_UpperCase(board_max[i][j]);
				board_max[i][j + 1] = to_UpperCase(board_max[i][j + 1]);
				board_max[i][j + 2] = to_UpperCase(board_max[i][j + 2]);
				status = 'w';
			}
		}
	}

	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < (row - 2); i++)
		{
			if (board_max[i][j] != ' ' &&
				to_LowerCase(board_max[i][j]) == to_LowerCase(board_max[i + 1][j]) &&
				to_LowerCase(board_max[i + 1][j]) ==
				to_LowerCase(board_max[i + 2][j]))
			{
				board_max[i][j] = to_UpperCase(board_max[i][j]);
				board_max[i + 1][j] = to_UpperCase(board_max[i + 1][j]);
				board_max[i + 2][j] = to_UpperCase(board_max[i + 2][j]);
				status = 'w';
			}
		}
	}

	for (int i = 0; i < (row - 2); i++)
	{
		for (int j = 0; j < (col - 2); j++)
		{
			if (board_max[i][j] != ' ' &&
				to_LowerCase(board_max[i][j]) == to_LowerCase(board_max[i + 1][j + 1]) &&
				to_LowerCase(board_max[i + 1][j + 1]) ==
				to_LowerCase(board_max[i + 2][j + 2]))
			{
				board_max[i][j] = to_UpperCase(board_max[i][j]);
				board_max[i + 1][j + 1] = to_UpperCase(board_max[i + 1][j + 1]);
				board_max[i + 2][j + 2] = to_UpperCase(board_max[i + 2][j + 2]);
				status = 'w';
			}

		}
	}

	for (int i = 0; i < (row - 2); i++)
	{
		for (int j = (col - 1); j > 1; j--)
		{
			if (board_max[i][j] != ' ' &&
				to_LowerCase(board_max[i][j]) == to_LowerCase(board_max[i + 1][j - 1]) &&
				to_LowerCase(board_max[i + 1][j - 1]) ==
				to_LowerCase(board_max[i + 2][j - 2]))
			{
				board_max[i][j] = to_UpperCase(board_max[i][j]);
				board_max[i + 1][j - 1] = to_UpperCase(board_max[i + 1][j - 1]);
				board_max[i + 2][j - 2] = to_UpperCase(board_max[i + 2][j - 2]);
				status = 'w';
			}

		}
	}

	return status;
}


//-------------------------------------------------------------
// Displays the table for player name, wins, losses, and draws.
// 
// @param - Player[], int&, int
// @return - void
//-------------------------------------------------------------

void display_full_statistics(Player player[6], int& total_games, int player_number)
{
	string name[6];

	for (int i = 0; i < player_number; i++)
	{
		name[i] = player[i].getFullName();
	}
	string largest = player[0].getFullName();
	cout << "\n\nTotal games played = " << total_games << endl << endl;

	for (int i = 0; i < (player_number - 1); i++)
	{
		if (name[i].length() < name[i + 1].length())
		{
			largest = name[i + 1];
		}
	}

	for (int i = 0; i < largest.length(); i++)		
	{
		cout << " ";
	}
	cout << " ";

	for (int i = 0; i < 3; i++)			
	{
		cout << " ------";
	}
	cout << endl;

	for (int i = 0; i < largest.length(); i++)		
	{
		cout << " ";
	}
	cout << " ";

	cout << "|  WIN | LOSS | DRAW |\n";

	for (int i = 0; i < largest.length(); i++)		
	{
		cout << " ";
	}

	cout << " ";

	for (int i = 0; i < 3; i++)			
	{
		cout << " ------";
	}
	cout << endl;

	int i = 0;

	while (i < player_number)
	{
		for (int j = 0; j < (largest.length() - player[i].getFullName().length()); j++)	
		{
			cout << " ";
		}

		cout << player[i].getFullName() << " |    " << player[i].getWins();
		cout << " |    " << player[i].getLosses() << " |    " << player[i].getDraws() << " |\n";

		for (int i = 0; i < largest.length(); i++)		
		{
			cout << " ";
		}

		cout << " ";

		for (int i = 0; i < 3; i++)			
		{
			cout << " ------";
		}
		cout << endl;

		i++;
	}
}


//-------------------------------------------------------------
// Converts the user's row selection to corresponding row 
// number.
// 
// @param - char
// @return - int
//-------------------------------------------------------------

int letter_to_int(char letter)
{
	switch (letter)
	{
	case 'a':
	case 'A':
		return 0;
	case 'b':
	case 'B':
		return 1;
	case 'c':
	case 'C':
		return 2;
	case 'd':
	case 'D':
		return 3;
	case 'e':
	case 'E':
		return 4;
	case 'f':
	case 'F':
		return 5;
	case 'g':
	case 'G':
		return 6;
	case 'h':
	case 'H':
		return 7;
	case 'i':
	case 'I':
		return 8;
	case 'j':
	case 'J':
		return 9;
	default:
		return 10;
	}
}


//-------------------------------------------------------------
// Returns a char to its upper case form.
// 
// @param - char
// @return - char
//-------------------------------------------------------------

char to_UpperCase(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c;
	}
	else
	{
		return c - ('a' - 'A');
	}
}


//-------------------------------------------------------------
// Returns a string with uppercase first letter
// 
// @param - string
// @return - string
//-------------------------------------------------------------

string upper_case_name(string str)
{
	string temp = str;
	str = to_UpperCase(temp[0]);
	int index = 1;

	while (temp[index] != '\0')
	{
		str = str + to_LowerCase(temp[index]);
		index++;
	}

	return str;
}


//-------------------------------------------------------------
// Validates the user's choice for MIN and MAX choice.
// 
// @param - int
// @return - int
//-------------------------------------------------------------

int validate_player_count(int player_count)
{
	bool flag;
	do
	{
		flag = false;

		string str;
		cin >> str;

		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '.' || (!(isdigit(str[i]))))
			{
				flag = true;
				break;
			}
		}

		if (!flag)
		{
			player_count = stoi(str);
		}

		if (cin.fail() || player_count < 3 || player_count > 6)
		{
			cout << "\nPlease make a valid choice: ";
			flag = true;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (flag);

	return player_count;
}


//-------------------------------------------------------------
// Validates the name of user for no digits or symbol.
// 
// @param - string&
// @return - string&
//-------------------------------------------------------------

void validate_name(string& first, string& last)
{
	bool first_flag = false;
	bool last_flag = false;
	do
	{
		for (int i = 0; i < first.length(); i++)
		{
			if (!(isalpha(first[i])))
			{
				first_flag = true;
				break;
			}
			else
			{
				first_flag = false;
			}
		}

		for (int i = 0; i < last.length(); i++)
		{
			if (!(isalpha(last[i])))
			{
				last_flag = true;
				break;
			}
			else
			{
				last_flag = false;
			}
		}

		if (first_flag || last_flag)
		{
			cout << "\nPlease enter a valid name: ";
			cin >> first >> last;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

	} while (first_flag || last_flag);

	cout << endl;
}


//-------------------------------------------------------------
// Returns a lower form of an alphabet character.
// 
// @param - char
// @return - char
//-------------------------------------------------------------

char to_LowerCase(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return c;
	}
	else
	{
		return c + ('a' - 'A');
	}
}


//-------------------------------------------------------------
// Set the player object with first and last name, and symbol.
// 
// @param - string&, char[][15], int, int
// @return - void
//-------------------------------------------------------------

void validate_choice(string& str, char board_max[][15], int row, int col)
{
	bool flag;

	do
	{
		flag = false;
		string numTemp;


		for (int i = 0; i < str.length(); i++)
		{
			if (i == 0 && isdigit(str[0]))
			{
				flag = true; 
				break;
			}

			if (i == 0)
			{
				if (!(to_LowerCase(str[i]) >= 'a' &&
					to_LowerCase(str[i]) <= char('`' + row)))
				{
					flag = true;
				}
			}
			else
			{
				if (!(isdigit(str[i])))
				{
					flag = true;
				}
				if (str[1] == '0')
				{
					flag = true;
				}
				numTemp = numTemp + str[i];
			}
		}

		if (!(isdigit(str[0])))
		{
			if (stoi(numTemp) > col)
			{
				flag = true;
			}

		}

		if (str.length() == 3)
		{
			for (int i = 0; i < numTemp.length(); i++)
			{
				if ((!(isdigit(numTemp[i]))))
				{
					flag = true;
					break;
				}

				if (stoi(numTemp) < 1 || stoi(numTemp) > col)
				{
					flag = true;
				}
			}
		}

		if (flag || str.length() < 2 || str.length() > 3)
		{
			cout << "Please enter a valid choice (d2...b12): ";
			cin >> str;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

	} while (flag || str.length() < 2 || str.length() > 3);

}