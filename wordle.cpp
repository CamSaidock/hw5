// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void floatingWords (std::string in, std::set<std::string>& words, const std::string& floating, int floatingSize, const std::set<std::string>& dict);
void generateWords (std::string in, std::set<std::string>& words, int location, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{

		std::string newWord = in;
		std::set<std::string> wordSet;
		floatingWords(newWord, wordSet, floating, floating.length()-1, dict);
		return wordSet;
}

// Define any helper functions here
void floatingWords ( std::string in, std::set<std::string>& wordSet, const std::string& floating, int floatingSize, const std::set<std::string>& dict )
{		

		if(floatingSize < 0) {
			generateWords(in, wordSet, 0, dict);
			return;
		}

		for(int i = 0; i < signed(in.length()); i++) {
			if(in[i] == '-') {
				std::string newWord = in;
				newWord[i] = floating[floatingSize];
				floatingWords(newWord, wordSet, floating, floatingSize-1, dict);
			}
		}
		
}

void generateWords (std::string in, std::set<std::string>& wordSet, int location, const std::set<std::string>& dict)
{		
	while(in[location] != '-' && location != signed(in.length())) {
		location++;
	}

	if(location == signed(in.length())) {
		if(dict.find(in) != dict.end()) {
			wordSet.insert(in);
		}
		return;
	}

	for(char z = 'a'; z <= 'z'; z++) {
		std::string newWord = in;
		if(newWord[location] == '-') {
			newWord[location] = z;
		}

		generateWords (newWord, wordSet, location+1, dict);
	}

	return;
}