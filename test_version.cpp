#define BOOST_TEST_MODULE ip_filter_test_module

#include "filter.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

BOOST_AUTO_TEST_CASE(ip_filter_test_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_filter_any)
{
    ip_container container;
    std::vector<std::string> ip1 = {"1", "2", "3", "4"};
    std::vector<std::string> ip2 = {"2", "5", "3", "4"};
    std::vector<std::string> ip3 = {"2", "10", "3", "4"};
    container.push_back(ip1);
    container.push_back(ip2);
    container.push_back(ip3);

    ip_container result = filter_any(container, 1);

    for(const auto& vs: result)
    {
        for(size_t i = 0; i < vs.size(); ++i)
        {
            bool compResult = !((bool)(vs[i].compare(ip1[i])));
            BOOST_CHECK( compResult );
        }
    }
}

BOOST_AUTO_TEST_CASE(ip_filter_test_filter)
{
    ip_container container;
    std::vector<std::string> ip1 = {"1", "2", "3", "4"};
    std::vector<std::string> ip2 = {"2", "5", "3", "4"};
    std::vector<std::string> ip3 = {"2", "10", "3", "4"};
    container.push_back(ip1);
    container.push_back(ip2);
    container.push_back(ip3);

    ip_container result = filter(container, 1);

    for(const auto& vs: result)
    {
        for(size_t i = 0; i < vs.size(); ++i)
        {
            bool compResult = !((bool)(vs[i].compare(ip1[i])));
            BOOST_CHECK( compResult );
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()