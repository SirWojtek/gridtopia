#pragma once
#include <utility>

namespace gridtopia
{

struct PoliceStation
{
    std::pair<unsigned, unsigned> position;
    unsigned range;

    inline bool operator<(const PoliceStation & other) const
    {
	return position.first < other.position.first &&
	    position.second < other.position.second;
    }
};

}
