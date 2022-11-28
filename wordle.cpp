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

void generateWords (std::string in, std::set<std::string>& words, int location);
std::set<std::string> updateDict(const std::string& in, const std::set<std::string>& dict);
void floatingWords ( std::string in, std::set<std::string>& words, const std::string& floating, int floatingSize );

std::set<std::string> updateDict(
    const std::string& in,
    const std::set<std::string>& dict)
{   
    std::set<std::string>::iterator itr;
    std::set<std::string> updatedDict;

    for(itr = dict.begin(); itr != dict.end(); itr++) {
        if((*itr).length() == in.size()) {
          updatedDict.insert(*itr);
        }
    }

    return updatedDict;
}

void floatingWords (
    std::string in,
		std::set<std::string>& words,
		const std::string& floating,
		int floatingSize )
{		

		if(floatingSize < 0) {
			generateWords(in, words, 0);
			return;
		}

		for(int i = 0; i < signed(in.length()); i++) {
			if(in[i] == '-') {
				std::string newWord = in;
				newWord[i] = floating[floatingSize];
				floatingWords(newWord, words, floating, floatingSize-1);
			}
		}
		
}

void generateWords (std::string in, std::set<std::string>& words, int location)
{		
	while(in[location] != '-' && location != signed(in.length())) {
		location++;
	}

	if(location == signed(in.length())) {
		words.insert(in);
		return;
	}

	for(char z = 'a'; z <= 'z'; z++) {
		std::string newWord = in;
		if(newWord[location] == '-') {
			newWord[location] = z;
		}

		generateWords (newWord, words, location+1);
	}

	return;
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{

    std::set<std::string> updatedDict = updateDict(in, dict); //Updated dictionary to only words same length as input
		std::string newWord = in;
		std::set<std::string> words;
		std::set<std::string> finalSet;
		floatingWords(newWord, words, floating, floating.length()-1);
		
		std::set<std::string>::iterator itr;
		
		for(itr = words.begin(); itr != words.end(); itr++) {
			if(updatedDict.find(*itr) != updatedDict.end()) {
				finalSet.insert(*itr);
			}
		}

		return finalSet;
}

// Define any helper functions here
