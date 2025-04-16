#include <iostream>
#include <string>
#include <cmath>

// used std::stoi(var) function to convert the string var to integer
/** 
I've recieved this problem via email from a newsletter called  "Sloth Bytes" who
has a youtube channel called "The Coding Sloth" BTW

The Problem is: find the next happy year
a happy year is year that all its digits are distinct (no duplicates):
The next happy year from (2021) is (2031) 

There is two ways to solve this problem: (I did the second)
1. The first is to increment the give year by 1 and check if it has duplicates
        using nested loops and keep incrementing the year by 1 until finding the happy year.
2. The second solution is to start comparing the digits starting from the larger digits as follows:
        1. Increment the given year by 1
        2. Finding out how many digits in the year
        3. Creates an array of integers to fit the digits of the year with extra index.
        4. The digits are stored in the array in reverse order: (2041) is stored like { 1, 4, 0, 2, 0}
        5. Now we go in nested loops starting from left to right to test if there is duplicate digit
        6. If there is a duplicate digit, we increment the lesser digit by 1 if this digit is not equal to 9
        7. If the digit is equal to 9 then, zeor-initialize this digit and all lesser digit, and move the incrementing to the next bigger digit.
        8. If the spare index is used, increment the arr_size so the next loops include and start looping process all over again until finding the happy year.
        9. Convert the array to int back again.
**/

// find how many digits in a given number
int numDigits(int number){
    int digits = 0;
    if (number < 0) 
        digits = 1; // remove this line if '-' counts as a digit
        
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

// Increment the index or bigger digit by 1 while zeroing the rest of less than index digits of the "arr"
// The "arr" is passed by pointer and "size" represent the last index in "arr"
// Returns true if the spare last index of "arr" is used, false otherwise
// in order adjust the counter of for loops inside the happyYear() 
bool increment(int index, int *arr, int size){
    for (int i = index; i < size+1 ; ++i){
        if (arr[i] == 9 ){
            arr[i] = 0;
            continue;
        }
        arr[i]++;
        break;
    }
  
    for (int i = 0; i < index ; ++i)
        arr[i] = 0;
    
    if (arr[size] > 0 )
        return true;
    return false;
}

int happyYear(int year){
    ++year;
    int arr_size { numDigits(year) }; //how many digits in the year
    
    int array [arr_size + 1 ];
    array[arr_size] = 0; // so there isn't any memory garbage value in there that affects the process
  
    // using methos like year%10 or similar calculations is usually going to miss the '0' digit and its applicable if the number of digits is fixed
    std::string s { std::to_string(year) };  
    int count { 0 };
    for ( int i = arr_size - 1; i > -1 ; --i ){
        array[i] = s[count] - '0';
        count++;
    }
    
    bool happy {false};
    while ( !happy ){
        for ( int i = arr_size -1 ; i > 0 ; --i){  // break from it by making i = 0
            for ( int j = i -1; j >= 0 ; --j){
                if ( array[i] == array[j] ){
                    if (increment(j, array, arr_size)){
                        arr_size++; // to include the spare digit in the comming calculations
                    }
                    i = 0;
                    happy = false;
                    break;
                }else
                    happy = true;
            }
        }
    }
    
    std::string answer { "" };
    for (int i = arr_size; i >= 0 ; --i)
        answer += std::to_string(array[i]);
        
    return std::stoi(answer);
}


int main() {
    std::cout << happyYear(9912)   // should print 10234
    std::cout << happyYear(1450);  // should print 1452
    std::cout << happyYear(1987);  // should print 2013
    std::cout << happyYear(999);   // should print 1023
    return 0;
}
