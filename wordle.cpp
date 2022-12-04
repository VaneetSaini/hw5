// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

void guessHelper(
	std::set<std::string>& guessList,
	unsigned int current_index,
	unsigned int spaceAmt,
	const std::string& in,
	std::string& _floating,
	std::string& current,
	const std::set<std::string>& dict
);

// Add prototypes of helper functions here
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		
    unsigned int current_index = 0; //index to iterate through in
    std::set<std::string> guessList; //set of guesses
		std::string _floating = floating;
		std::string current = "";
		unsigned int spaceAmt = 0;
		unsigned int len = in.size();
		for (unsigned int i = 0; i < len; ++i)
		{
			if (in[i] == '-') spaceAmt++;
		}
		std::cout << spaceAmt << endl;
		guessHelper(guessList, current_index, spaceAmt, in, _floating, current, dict);
		return guessList;
    
}
// Define any helper functions here
void guessHelper(
	std::set<std::string>& guessList,
	unsigned int current_index,
	unsigned int spaceAmt,
	const std::string& in,
	std::string& _floating,
	std::string& current,
	const std::set<std::string>& dict
)
{
	unsigned int len = in.size();
	if (current.size() == len)
	{
		if (dict.find(current) == dict.end()) return;
		else
		{
			guessList.insert(current);
			return;
		}
	}
	else
	{
		if (in[current_index] != '-')
		{
			current += in[current_index];
			guessHelper(guessList, current_index+1, spaceAmt, in, _floating, current, dict);
			current.pop_back();
			return;
		}
		else
		{
			for (unsigned int i = 0; i < _floating.size(); ++i)
			{
				current += _floating[i];
				std::string tmp = _floating;
				_floating.erase(i, 1);
				guessHelper(guessList, current_index+1, spaceAmt-1, in, _floating, current, dict);
				_floating = tmp;
				current.pop_back();
			}
			if (spaceAmt-1 >= _floating.size())
			{
				current += 'a';
				for (int i = 0; i < 26; ++i)
				{
					guessHelper(guessList, current_index+1, spaceAmt-1, in, _floating, current, dict);
					current[current_index]++;
				}
				current.pop_back();
			}
			return;
		}
	}
}

