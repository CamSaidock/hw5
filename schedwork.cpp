#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(size_t row, size_t col, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched, std::map<Worker_T, int> workerMap);
bool isValid(std::map<Worker_T, int> workerMap, unsigned int id);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	if(avail.size() == 0U){
			return false;
	}
	sched.clear();
	// Add your code below 

	std::vector<Worker_T> dailyWorkers(dailyNeed, INVALID_ID);

	std::map<Worker_T, int> workerMap; //Store Worker ID's

	for(size_t i = 0; i < avail.size(); i++) {
		sched.push_back(dailyWorkers); //Initalize schedule
	}

	for(unsigned int y = 0; y < avail[0].size(); y++) {
		workerMap.insert(std::make_pair(y, maxShifts)); //Populate entire map with worker ID and the max number of shifts they can work
	}

	return scheduleHelper(0, 0, avail, dailyNeed, sched, workerMap);
}

bool scheduleHelper(size_t row, size_t col, const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched, std::map<Worker_T, int> workerMap) {
	size_t d = sched[row].size();
	size_t n = sched.size();
	size_t k = avail[row].size();

	if(row == n) { //If function reaches last available row return true || Base Case
		return true;
	}

	for(unsigned int id = 0; id < k; id++) { //Iterate through entire availability matrix for current day/row
		if(find(sched[row].begin(), sched[row].begin() + col, id) != (sched[row].begin() + col)) {
			continue;
		}

		if(avail[row][id] == true && isValid(workerMap, id)) { //First make sure they're available and use isValid to determine if the worker is overworked or not
			sched[row][col] = id; //Assign current id to schedule
			workerMap[id] += -1; //Decrement the amount of shifts they're working from MaxShifts

			if(col == d-1) { //If last column, set column equal to zero and row equal to next row in recursive call
				if(scheduleHelper(row + 1, 0, avail, dailyNeed, sched, workerMap)) {
					return true;
				}
				else { //If it returns false, set schedule id to INVALID_ID and decrease number of shits working by -1
					workerMap[id] -= -1;
					sched[row][col] = INVALID_ID;
				}
			} 

			else { //If not last column, make a recursive call to next column
				if(scheduleHelper(row, col + 1, avail, dailyNeed, sched, workerMap)) {
					return true;
				}
				else { //If it returns false, set schedule id to INVALID_ID and decrease number of shits working by -1
					workerMap[id] -= -1;
					sched[row][col] = INVALID_ID;
				}
			}
		}
	}

	return false;
}

bool isValid(std::map<Worker_T, int> workerMap, unsigned int id) {
	std::map<Worker_T, int>::iterator itr;
	for(itr = workerMap.begin(); itr != workerMap.end(); itr++) {
		if((*itr).first == id) {
			if((*itr).second > 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false;
}