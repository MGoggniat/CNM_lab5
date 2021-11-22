#ifndef LABO_05_INPUT_VALIDATION_H
#define LABO_05_INPUT_VALIDATION_H

/*
name      : get_input
objective : Get and validate the user input in unsigned int.
param     : min : The minimum value required (included)
param     : max : The maximum value required (included)
return    : the user input
exception : n/a
*/
unsigned get_input(unsigned min, unsigned max);

// Commented deprecated functions to be reworked

/*
name      : get_input
objective : Get and validate the user input in string. Note that this function only
            gets a single character. If the user enters more than one character, it
            will be considered false.
param     : min : The minimum value required (included)
param     : max : The maximum value required (included)
param     : user_input : The user input
return    : n/a
exception : n/a
*/
//void get_input(const std::string& min, const std::string& max,
//               std::string& user_input);

/*
name      : get_two_options_input
objective : Get input with only 2 valid options (type string). Note that this
            function only gets a single character. If the user enters more than
            one character, it will be considered false.
param     : opt1 : One of the two available option
param     : opt2 : One of the two available option
param     : user_input : The user input
return    : n/a
exception : n/a
*/
//void get_two_options_input(const std::string& opt1, const std::string& opt2,
//                           std::string& user_input);

#endif
