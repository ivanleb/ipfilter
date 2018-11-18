#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

#include "filter.cpp"

std::vector<std::string> split2(const std::string &str, char d)
{
    std::vector<std::string> r;
    std::stringstream strStream(str);
    std::string word;

    while (std::getline(strStream, word, d)) 
    {
        r.push_back(word);
    }
   
    return r;
}

void Print(const ip_container& container)
{
    for(const auto& ip: container)
    {
        for(size_t i = 0; i < ip.size(); ++i )
        {            
            std::cout << ip[i];
            if(i != ip.size()-1){std::cout<< ".";}
        }
        std::cout << std::endl;
    }
}

int main()
{
    try
    {
        ip_container ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split2(line, '\t');
            std::vector<std::string> vv = split2(v.at(0), '.');
            std::vector<int> intV; 
            for(const auto& s: vv)
            {
                intV.emplace_back(std::stoi(s));
            }
            ip_pool.push_back(intV);
        }
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());
        //std::sort(ip_pool.begin(), ip_pool.end(), [](std::vector<int> v1, std::vector<int> v2){return v1 > v2;});
        Print(ip_pool);

        auto result = filter(ip_pool, 1);
        Print(result);

        auto result_1 = filter(ip_pool, 46, 70);
        Print(result_1);

        auto any_result = filter_any(ip_pool, 46);
        Print(any_result);        

    }    
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
