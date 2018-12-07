#include <string>
#include <exception>
#include <iostream>

#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include "parser.hpp"
#include "gridtopia/gridtopia.hpp"

std::string parseCommandLine(int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("input-file,i", po::value<std::string>(), "input file with testcases");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (!vm.count("input-file"))
    {
        throw std::invalid_argument("There is no input file argument (--input-file or -i)");
    }

    return vm["input-file"].as<std::string>();
}


int main(int argc, char** argv)
{
    try
    {
        const auto inputFilename = parseCommandLine(argc, argv);
        const auto testcases = parseInputFile(inputFilename);
        const auto differences = gridtopia::computeSmallestDifference(testcases);

        for (unsigned i = 0; i < differences.size(); ++i) {
            std::cout << "Case #" <<  i + 1 << ": " << differences[i] << std::endl;
        }

        return 0;
    }
    catch (std::exception & e)
    {
        std::cout << "std::exception: " << e.what() << std::endl;
        return -1;
    }
}
