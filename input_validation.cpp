/*
-----------------------------------------------------------------------------------
File name     : input_validation.cpp
Authors       : Émilie Bressoud, Leandro Saraiva Maia
Creation date : 10.11.2021

Changes made  :
                * 21.11.2021 Translated the error messages to english
                * 22.11.2021 Rework get_input for unsigned and commented all the
                * others functions (to be rework later)

Description   : Set of function to retrieve user input more easily. It handles
                wrong values types and specific values ranges.

Remark(s)     : The letters type is string and not char, which prevents to
                validate an input with more than 1 character.
                The get_input() function doesn't check if the user enter spaces
                between 2 or more correct values.

Compiler      : Works with :
                - Apple clang 13.0.0
                - Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <iostream> // required for cout
#include <limits>   // used to empty the buffer (<streamsize>::max())
#include <string>   // used for string and .length()

using namespace std;

unsigned get_input(const unsigned min, const unsigned max) {
	bool     error;
	unsigned user_input;

	do {
		cin >> user_input;

		error = cin.fail() || user_input < min || user_input > max;
		if (error) {
			cout << "Please only enter a number between "
			     << min << " and " << max << endl;
			cin.clear();
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // empty buffer

	} while(error);

	return user_input;
}

/* Commented deprecated functions, to be rework

// Do not use, deprecated
void get_input(const string& min, const string& max, string& user_input) {
   bool                 error;
   unsigned long long   size;

	do {
		cin >> user_input;

		size = user_input.length();
		error = cin.fail() || size > 1ull || user_input < min || user_input > max ;

		if (error) {
			cout << "Please only enter a letter from "
			     << min << " to " << max << endl;
			cin.clear();
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while(error);
}

// Do not use, deprecated
void get_two_options_input(const string& opt1, const string& opt2,
                           string& user_input) {
	bool                 error;
   unsigned long long   size;

	do {
		cin >> user_input;

		size = user_input.length();
		error = cin.fail() || size > 1ull
		        || !(user_input == opt1 || user_input == opt2);

		if (error) {
			cout << "Pleaser enter either " << opt1 << " or " << opt2 << endl;
			cin.clear();
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while(error);
}

 */