#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <string>
#include "template.hpp"
#include "DataType.hpp"

using std::vector;
using std::shared_ptr;

#define TEST_DB_EQUAL 0.0000001
Plane init_plane(){
    static int i = 0;
    Plane plane;
    plane.time = i;
    plane.distance = i+10;
    plane.pos = Point(i+50,i+100,i+200);
    plane.vel = Point(i+10,i+20,i+30);
    plane.pos_1 = Point(i+50,i+100,i+200);
    plane.vel_1 = Point(i+10,i+20,i+30);
    i+=10;
    return plane;
}

BOOST_AUTO_TEST_SUITE( test_suite1 )

    static int MIN_SIZE = 3;
    static int MAX_SIZE = 10;
    static Plane target_plane;
    static Plane result_plane;

    vector<Plane> planes_min(MIN_SIZE);
    vector<Plane> planes_max(MAX_SIZE);
    BOOST_AUTO_TEST_CASE( init_test_case )
    {
        target_plane.time = 10;
        target_plane.pos.x() = 10;
        std::generate(planes_max.begin(), planes_max.end(), init_plane);
        std::copy_n(planes_min.begin(), MIN_SIZE, planes_max.begin());
    }

    BOOST_AUTO_TEST_CASE( calculate_help_test_case)
    {
        shared_ptr<Calculator> calculator = std::make_shared<Calculator>();
        auto res = calculator->CalculateHelper(1.5, 1, 2, 3, 10, 20, 30);
        BOOST_CHECK_LT(fabs(res-17.5) , TEST_DB_EQUAL);
    }

    BOOST_AUTO_TEST_CASE( calculate_with_time)
    {
        shared_ptr<Calculator> calculator = std::make_shared<Calculator>();
        FindMode mode = FIND_WITH_TIME;
        RV rv = calculator->CalculateNormal(planes_max, target_plane, result_plane, mode);
        BOOST_CHECK_EQUAL(rv, SUCCESS);
        BOOST_CHECK_LT(fabs(result_plane.time-10) , TEST_DB_EQUAL);
        BOOST_CHECK_LT(fabs(result_plane.distance-42.5) , TEST_DB_EQUAL);
        BOOST_CHECK_LT(fabs(result_plane.pos.x()-92.5) , TEST_DB_EQUAL);
    }

    BOOST_AUTO_TEST_CASE( calculate_with_pos_x)
    {
        shared_ptr<Calculator> calculator = std::make_shared<Calculator>();
        FindMode mode = FIND_WITH_POS_X;
        RV rv = calculator->CalculateNormal(planes_max, target_plane, result_plane, mode);
        BOOST_CHECK_EQUAL(rv, SUCCESS);
    }

BOOST_AUTO_TEST_SUITE_END()

