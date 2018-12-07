#include <fstream>

#include "parser.hpp"

namespace
{

gridtopia::Testcase parseTestcase(std::ifstream & fileStream)
{
    gridtopia::Testcase testcase;
    unsigned policeStationsCount;

    fileStream >> testcase.rows >> testcase.columns >> policeStationsCount;

    for (unsigned i = 0; i < policeStationsCount; ++i) {
        unsigned x, y;
        fileStream >> x >> y;
        testcase.policeStations.push_back(std::make_pair(x, y));
    }

    return testcase;
}

}

std::vector<gridtopia::Testcase> parseInputFile(std::string filename)
{
    std::vector<gridtopia::Testcase> result;
    std::ifstream fileStream(filename);

    if (!fileStream.is_open())
    {
        throw std::runtime_error("Cannot read from file");
    }

    unsigned testcasesCount;

    fileStream >> testcasesCount;

    if (testcasesCount < 1)
    {
        throw std::invalid_argument("Invalid test case number");
    }

    for (unsigned i = 0; i < testcasesCount; ++i)
    {
        result.push_back(parseTestcase(fileStream));
    }

    return result;
}
