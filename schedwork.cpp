

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
bool isValid(
    unsigned int row, 
    unsigned int col,
    unsigned int ID,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);

bool scheduleHelper(
    unsigned int row,
    unsigned int col,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);



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
    unsigned int row, col = 0;
    unsigned int len = avail.size();
    for (unsigned int i = 0; i < len; ++i)
    {
        vector<Worker_T> temp;
        for (unsigned int j = 0; j < dailyNeed; ++j)
        {
            temp.push_back(INVALID_ID);
        }
        sched.push_back(temp);
    }
    return scheduleHelper(row, col, avail, dailyNeed, maxShifts, sched);
}

bool isValid(
    unsigned int row, 
    unsigned int col,
    unsigned int ID,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    bool ret = true; //default 
    if (avail[row][ID] == 0) return false;
    else if (avail[row][ID] == 1)
    {
        unsigned int num = 0;
        unsigned int len = sched.size();
        for (unsigned int i = 0; i < len; ++i)
        {
            for (unsigned int j = 0; j < dailyNeed; ++j)
            {
                if (sched[i][j] == ID) num++;
            }
        }
        if (maxShifts < num)
        {
            ret = false;
        }
        if (ret == true)
        {
            for (unsigned int i = 0; i < dailyNeed; ++i)
            {
                if (sched[row][i] == ID) ret = false;
            }
        }
    }
    return ret;
}

bool scheduleHelper(
    unsigned int row,
    unsigned int col,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    unsigned int len = sched.size();
    if (len == row)
    {
        for (unsigned int i = 0; i < len; ++i)
        {
            for (unsigned int j = 0; j < sched[0].size(); ++j)
            {
                if (sched[i][j] == INVALID_ID) return false;
            }
        }
        return true;
    }
    unsigned int size = avail[0].size();
    for (unsigned int i = 0; i < size; ++i)
    {
        //segementation fault 
       /*if (isValid(row, col, i, avail, dailyNeed, maxShifts, sched))
        {
            sched[row][col] = i;
            if (dailyNeed-1 != col)
            {
                if (scheduleHelper(row, col+1, avail, dailyNeed, maxShifts, sched)) return true;
                else sched[row][col] = INVALID_ID;
            }
        }*/
    } 
    return false;
}



