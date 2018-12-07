
#include <map>
#include <exception>
#include <algorithm>

#include "gridtopia.hpp"

namespace gridtopia
{
namespace
{

using Coord = std::pair<unsigned, unsigned>;
using GridMap = std::multimap<Coord, PoliceStation>;
using PoliceStationFields = std::multimap<PoliceStation, Coord>;

inline unsigned boundIfMore(unsigned number, unsigned bound)
{
    return number > bound ? bound : number;
}

inline unsigned oneIfLess(int number)
{
    return number < 1 ? 1 : number;
}

GridMap createGridMap(const Testcase & testcase)
{
    GridMap gridMap;

    const auto & policeStations = testcase.policeStations;
    for (auto it = policeStations.begin(); it != policeStations.end(); it++)
    {
	const auto xBegin = oneIfLess(it->position.first - it->range);
	const auto xEnd = boundIfMore(it->position.first + it->range, testcase.columns);
	const auto yBegin = oneIfLess(it->position.second - it->range);
	const auto yEnd = boundIfMore(it->position.second + it->range, testcase.rows);

	for (auto x = xBegin; x <= xEnd; ++x)
	{
	    for (auto y = yBegin; y <= yEnd; ++y)
	    {
		const auto coord = std::make_pair(x, y);
		gridMap.emplace(coord, *it);
	    }
	}
    }

    return gridMap;
}

void addExclusiveFields(PoliceStationFields & psFields, const GridMap & gridMap)
{
    // NOTE: iterate over unique keys of gridMap
    for (auto it = gridMap.begin(); it != gridMap.end(); it = gridMap.upper_bound(it->first))
    {
	const auto coord = it->first;
	if (gridMap.count(coord) == 1)
	{
	    const auto ps = gridMap.find(coord)->second;
	    psFields.emplace(std::make_pair(ps, coord));
	}

    }
}

void balanceSharedFields(PoliceStationFields & psFields, const GridMap & gridMap)
{
    for (auto it = gridMap.begin(); it != gridMap.end(); it = gridMap.upper_bound(it->first))
    {
	const auto coord = it->first;
	if (gridMap.count(coord) < 2)
	{
	    continue;
	}

	const auto valuesRange = gridMap.equal_range(coord);

	const PoliceStation * min = &valuesRange.first->second;
	for (auto psIt = valuesRange.first; psIt != valuesRange.second; psIt++)
	{
	    if (psFields.count(*min) > psFields.count(psIt->second))
	    {
		min = &psIt->second;
	    }
	}
	psFields.emplace(*min, coord);
    }
}

std::vector<unsigned> countPoliceStationAssignedFields(const PoliceStationFields & psFields)
{
    std::vector<unsigned> result;

    for (auto it = psFields.begin(); it != psFields.end(); it = psFields.upper_bound(it->first))
    {
	result.emplace_back(psFields.count(it->first));
    }

    return result;

}

unsigned computeSmallestDifference(const Testcase & testcase)
{
    const auto gridMap = createGridMap(testcase);

    PoliceStationFields psFields;
    addExclusiveFields(psFields, gridMap);
    balanceSharedFields(psFields, gridMap);

    const auto countVector = countPoliceStationAssignedFields(psFields);
    const auto minCount = std::min_element(countVector.begin(), countVector.end());
    const auto maxCount = std::max_element(countVector.begin(), countVector.end());

    return maxCount - minCount;
}
}

std::vector<unsigned> computeSmallestDifference(const std::vector<Testcase> & testcases)
{
    std::vector<unsigned> differences;

    for (auto it = testcases.begin(); it != testcases.end(); it++)
    {
	if (!it->isCorrect())
	{
	    throw std::invalid_argument("Incorrect testcase data");
	}

	differences.emplace_back(computeSmallestDifference(*it));
    }

    return differences;
}

}
