#pragma once

#include <vector>
#include <utility>

#include "police_station.hpp"

namespace gridtopia
{
struct Testcase {
    unsigned columns;
    unsigned rows;
    std::vector<PoliceStation> policeStations;

    inline bool isCorrect() const
    {
	if (columns < 1 || rows < 1)
	{
	    return false;
	}

	for (auto it = policeStations.begin(); it != policeStations.end(); it++)
	{
	    if (it->range < 1)
	    {
		return false;
	    }
	    if (it->position.first < 1 || it->position.first > columns)
	    {
		return false;
	    }
	    if (it->position.second < 1 || it->position.second > rows)
	    {
		return false;
	    }
	}

	return true;
    }
};

}
