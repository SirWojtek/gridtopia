#include <vector>
#include <utility>

namespace gridtopia
{
    struct Testcase {
	int columns;
	int rows;
	std::vector<std::pair<int, int>> policeStations;
    };
}
