
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
        for (const auto& ip_part : ip)
        {
            if(ip_part == t)
            {
                if(!std::any_of(result.cbegin(), result.cend(), 
                    [ip](std::vector<int> v)
                    {
                        return v == ip;
                    }))
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
    ip_container result;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(result), [t](std::vector<int> v){return v.at(N) == t;});
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