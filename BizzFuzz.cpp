
// BizzFuzz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map> 
#include <functional>
#include <string>
#include <algorithm>
using namespace std;
using Predicate = std::function<string(int)>;


//basic_fizzbuzz:
// Goes from 1-100, outputting Fizz for multiplies of 3 and Buzz for multiplies of 5 and FizzBuzz for both.
// otherwise just printing the numbers.
void basic_fizzbuzz()
{
    for (int i = 1; i <= 100; i++)
    {
        std:string result = "";
        if (i % 3 == 0)
        {
            result += "Fizz";
        }
        if (i % 5 == 0)
        {
            result += "Buzz";
        }

        result = (result != "") ? std::string{result} + "\n" : to_string(i) + "\n";
        std::cout << result;
    }

}


//complex_fizzbuzz:
// Goes from 1-100, outputting certain words depending on the number and the list given in the parameter.
// with some words overriding others otherwise just printing the numbers.
void complex_fizzbuzz(std::vector<pair<Predicate, std::vector<std::string>>> list)
{
    std::vector<std::string> applied; //The strings that have been applied.
    for (int i = 1; i <= 100; i++)
    {
        std::string result = ""; //The resulting word

        //Cycle through every possible query.
        for (const auto& pair : list)
        {
            //If the number returns a word.
            if (pair.first(i) != "")
            {
                //Check if that any current word is overriden by this new word.
                for (const auto& overrides : pair.second) {
                    bool found = std::find(applied.begin(), applied.end(), overrides) == applied.end();
                        if (found)
                        {
                            result = "";
                            applied.clear();
                            break;
                        }
                }
                
                result = pair.first(i);
                applied.push_back(pair.first(i));
            } 
        }
        //If there's a result, print it out, if not just make the result the number and print it.
        result = (result != "") ? std::string{result} + "\n" : to_string(i) + "\n";
        std::cout << result;
    }
}

//main:
//initializes all the Predicate's and the list of conditionals for the complex fizzbuzz.
int main()
{
    std::cout << "Basic FizzBuzz\n";
    basic_fizzbuzz();
    std::cout << "------------------------------\n";
    std::cout << "Complex FizzBuzz\n";

    Predicate Fizz = [](int n) { return (n % 3 == 0) ? "Fizz" : ""; };
    Predicate Buzz = [](int n) { return (n % 5 == 0) ? "Buzz" : ""; };
    Predicate FizzBazz = [](int n) { return ((n % 3 == 0) && (n % 5 == 0)) ? "FizzBazz" : ""; };
    Predicate CrizzCrazz = [](int n) { return ((n % 10 == 0)) ? "CrizzCrazz" : ""; };

    std::vector<pair<Predicate, std::vector<std::string>>> conditionals{make_pair(Fizz, std::vector<std::string>{}),
        make_pair(Buzz, std::vector<std::string>{}),
        make_pair(FizzBazz, std::vector<std::string>{"Fizz", "Buzz"}),
        make_pair(CrizzCrazz, std::vector<std::string>{"Fizz", "Buzz", "CrizzCrazz"})
    };

    complex_fizzbuzz(conditionals);

}