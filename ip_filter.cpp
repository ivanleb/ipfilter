#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "filter.cpp"

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

void Print(const ip_container& container)
{
        for(const auto& i: container)
        {
            for(const auto& str : i)
            {
                std::cout << str;
                if(str != *(i.cend()-1)){std::cout<< ".";}
            }
            std::cout << std::endl;
        }
}

int main(int argc, char const *argv[])
{
   
    if(argc <= 1)
    {
        std::cout << "Empty file path" << std::endl;
        return 0;
    }
    std::cout << argv[1] << std::endl;
    if(argv[1] == "--version")
    {
        std::cout << "version = " << version() << std::endl;
        return 0;
    }
    std::ifstream instream(argv[1]); 

    try
    {
        ip_container ip_pool;

        for(std::string line; std::getline(instream, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        Print(ip_pool);

        auto result = filter(ip_pool, 1);

        std::sort(result.begin(), result.end(),predicate);

        Print(result);

        auto result_1 = filter(ip_pool, 46, 70);

        std::sort(result_1.begin(), result_1.end(),predicate);

        Print(result_1);

        auto any_result = filter_any(ip_pool, 46);

        std::sort(any_result.begin(), any_result.end(),predicate);

        Print(any_result);        

    }    
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
