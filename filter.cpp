
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <tuple>
#include <functional>

#include "version.h"

using ip_container = std::vector<std::vector<std::string>>;

bool predicate(std::vector<std::string> s1, std::vector<std::string> s2)
{
    size_t size = s1.size() < s2.size() ? s1.size() : s2.size();
    for (size_t i = 0; i < size; ++i)
    {
        if(s1.at(i).size() > s2.at(i).size()) return true;
        else if(s1.at(i).size() < s2.at(i).size()) return false;
        for (size_t j = 0; j < s1.at(i).size(); ++j)
        {
            if(s1.at(i).compare(s2.at(i)) > 0) return true;
            else if(s1.at(i).compare(s2.at(i)) < 0) return false;
        }
    }
    return true;
}

template<typename T>
ip_container filter_any(ip_container& container, T t)
{
    ip_container result;
    for(const auto & ip : container)
    {
        for (const auto& ip_part : ip)
        {
            if(ip_part == std::to_string(t))
            {
                result.push_back(ip);
            }
        }
    }
    return result;
}

template <typename T, typename ... P>
ip_container filter_any(ip_container container, T t, P ... p)
{
    ip_container intermediateResult;
    intermediateResult = filter_any(container, t);
    auto result = filter_any(intermediateResult, p...);
    return result;
}

template<int N,typename T>
ip_container filter(ip_container& ip_pool, T t)
{
    auto filter_predicate = [t](std::vector<std::string> v)
    {
        if(v.at(N) == std::to_string(t)) return true;
        return false;
    };
    ip_container result;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(result), filter_predicate);
    return result;
}

template<int N, typename T, typename ... P>
ip_container filter(ip_container& ip_pool, T t, P ...p)
{
    auto intermediateResult = filter<N>(ip_pool,t);
    auto result = filter<N+1>(intermediateResult,p...);
    return result;
}

template< typename ... P>
ip_container filter(ip_container& ip_pool, P ...p)
{
    auto result = filter<0>(ip_pool, p...);
    return result;
}

int version()
{
    return PROJECT_VERSION_PATCH;
}