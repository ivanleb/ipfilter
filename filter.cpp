
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "version.h"

using ip_container = std::vector<std::vector<int>>;

template<typename T>
ip_container filter_any(ip_container& container, T t)
{
    ip_container result;    
    for(const auto & ip : container)
    {
        if(std::any_of(ip.begin(), ip.end(), 
            [t](int ip_part){return t == ip_part;}))
        {
            // if(!std::any_of(result.begin(), result.end(), 
            //     [ip](std::vector<int> v){return v == ip;}))
            result.push_back(ip);
        }
    }
    return result;
}

template <typename T, typename ... P>
ip_container filter_any(ip_container container, T t, P ... p)
{
    auto intermediateResult = filter_any(container, t);
    auto result = filter_any(intermediateResult, p...);
    return result;
}

template<int N,typename T>
ip_container filter(ip_container& ip_pool, T t)
{
    ip_container result;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(result),
    [t, &result](std::vector<int> v)
    {
        if(v.at(N) == t) 
        {
            return true;
            // !std::any_of(result.begin(), result.end(),
            //             [&v](std::vector<int> ip){return v == ip;});
        }
        else return false;
    });
    return result;
}

template<int N, typename T, typename ... P>
ip_container filter(ip_container& ip_pool, T t, P ...p)
{
    auto intermediateResult = filter<N>(ip_pool,t);
    auto result = filter<N+1>(intermediateResult,p...);
    return result;
}

template<typename ... P>
ip_container filter(ip_container& ip_pool, P ...p)
{
    auto result = filter<0>(ip_pool, p...);
    return result;
}

int version()
{
    return PROJECT_VERSION_PATCH;
}