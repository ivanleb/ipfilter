#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    std::ifstream instream("ip_filter.tsv");
    
    try
    {
        ip_container ip_pool;

        for(std::string line; std::getline(instream, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        auto result = filter(ip_pool, 81, 198);

        std::sort(result.begin(), result.end(),predicate);

        for(const auto& i: result)
        {
            for(const auto& str : i)
            {
                std::cout << str;
                if(str != *(i.cend()-1)){std::cout<< ".";}
            }
            std::cout << std::endl;
        }

        // TODO reverse lexicographically sort

    }    
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
