/* 

File: RomanNumeralConverter.cpp
Author: James Henry 
Functionality: We're starting LeetCode to transform Roman Numerals into Integers
Complexity: O(n)

*/

//start here
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include <locale>

//prototype functions
void read(std::string fileName);
std::string toRoman(int num);

//note: stoi can store integers! It's built into the <string> library.

int messageCount = 0; //keeps track of message counter 

//First step - read the file for numbers and non-numbers.
void read(std::string fileName){
    std::ifstream input; //Lecture with Program4 taught us to open files. That's what I am doing.
    input.open(fileName);

    if(!input) { // Handles Base Case
        std::cout << "Cannot open the file, either corrupted or invalid." << ' ';
    } else { 
        //if there is an input file...
        char ch; ; //variable that stores current character from string, defined globally as to not redefin each iteration in while loop
        std::string currentNumber = ""; //stores the current number being read from the file & initializes using empty string.
        int sum = 0; //initializing sum of all numbers integer

        while(input){ //didn't use 'input.get(ch)' because then we wouldn't be able to use the 'peek' function within while loop
            ch = input.get();

            //main part: number detector
            if (isdigit(ch)){ //isdigit checks for numbers
                currentNumber += ch; // append the digit to the current number
            } else { //else, if we detect anything that is not a number
                if (!currentNumber.empty()) { //Continue, checks if number needs to be added into array by seeing if it's not empty
                    sum += std::stoi(currentNumber); // adds the FULL current number to sum
                    currentNumber = ""; // reset the current number
                }
            }

            //detects if this is the end of the current message
            if((ch == '\n') || (ch == EOF)){ // '\n' is considered a character, covers both cases of having another message after or end of file, no more input chars
                ch = input.peek(); //redefining ch with value of next char without extracting said value
                if((ch == '\n') || (ch == EOF)){ //if the next char is a new line, then increment message counter (since it can't be when next char is ran), or end of file
                    messageCount += 1;
                    //OUTPUT MESSAGE NUMBER, SECRET CODE, AND ROMAN NUMERALS
                    std::cout << "Message " << messageCount << ":\n";
                    //find secret code
                    int secretCode = 0;
                    std::string sumString = std::to_string(sum); //uses to_string from std string namespace to convert sum integer to string in order to access indices
                    for(std::string::size_type i=0; i < sumString.size(); i++){ //for loop to go through each index of the integer
                        int temp = sumString[i] - '0'; //sumString[i] returns ASCII value, to isolate digit, subtract by '0' or ASCII 0
                        secretCode += temp;
                    }
                    std::cout << "Code: " << secretCode << "\n";
                    //finds Roman Numeral by calling toRoman function and passing in the secretCode
                    std::cout << "Roman Numeral: " << toRoman(secretCode) << "\n\n";
                    sum = 0; //reset sum
                    ch = input.get(); //catches ch up because of the two newlines
                }
            }
            
        }
    }
    
}

std::string toRoman(int num) {
    // Check if the input number is within the valid range for Roman numerals
    if (num <= 0 || num >= 4000) {
        return "Invalid"; // Return "Invalid" if the number is out of range
    }

    // Initialize an empty string to store the Roman numeral representation
    std::string result = "";

    // Define symbols and their corresponding values
    const char symbols[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'}; // Roman numeral symbols
    const int values[] = {1000, 500, 100, 50, 10, 5, 1}; // Corresponding numerical values

    // Iterate through the symbols and values
    for (int i = 0; i < 7; ++i) {
        // Repeat the current symbol while the value is less than or equal to the number
        while (num >= values[i]) {
            result += symbols[i]; // Append the symbol to the result string
            num -= values[i]; // Subtract the value from the number
        }
        // Handle the subtraction cases (e.g., IV, IX, XL, XC, etc.)
        // These cases involve subtracting one symbol from another
        if (i % 2 == 0 && i < 6) { // Check if the symbol is one of M, C, or X (i.e., 1000, 100, or 10)
            int nextValueIndex = i + 2; // Calculate the index of the next value for subtraction
            int difference = values[i] - values[nextValueIndex]; // Calculate the difference between the current and next values
            if (num >= difference) { // Check if the difference can be subtracted from the number
                result += symbols[nextValueIndex]; // Append the next symbol to the result string
                result += symbols[i]; // Append the current symbol to the result string
                num -= difference; // Subtract the difference from the number
            }
        }
    }
    return result; // Return the final Roman numeral representation
}
int main() {
    std::string fileName = "input.txt"; // Change this to your actual file name
    read(fileName); // Calls the read function to process the file
    return 0; // Return 0 to indicate successful execution
}


