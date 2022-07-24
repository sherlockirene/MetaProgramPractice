#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <vector>
#include <calculate/calculate.hpp>
#include "DataType.hpp"

static const double TEST_DB_EQUAL = 0.0000001;

using std::shared_ptr;
using std::vector;
using namespace Model::Core;
static int i = 0;
Plane init_plane()
{
    Plane plane;
    plane.time = i;
    plane.distance = i * 10;
    plane.pos = Point(i * 10, i * 20, i * 30);
    plane.vel = plane.pos;
    plane.pos_1 = plane.pos;
    plane.vel_1 = plane.pos;
    i += 1;
    return plane;
}

static int MIN_SIZE = 3;
static int MAX_SIZE = 10;
static Plane target_plane;
vector<Plane> planes_min(MIN_SIZE);
vector<Plane> planes_max(MAX_SIZE);

struct GlobalFixture
{
    GlobalFixture()
    {
        std::cout << "GlobalFixture" << std::endl;
        target_plane.time = 5;
        target_plane.pos.x() = 60;
        std::generate(planes_max.begin(), planes_max.end(), init_plane);
        std::copy_n(planes_max.begin(), MIN_SIZE, planes_min.begin());
    }
    ~GlobalFixture()
    {
        std::cout << "~GlobalFixture" << std::endl;
    }
};

BOOST_GLOBAL_FIXTURE(GlobalFixture);
BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(calculate_help_test_case)
{
    auto res = CalculateHelper(1.5, 1, 2, 3, 10, 20, 30);
    BOOST_CHECK_LT(fabs(res - 15), TEST_DB_EQUAL);
    res = CalculateHelper(1.5, 1, 2, 3, 100, 200, 300);
    BOOST_CHECK_LT(fabs(res - 150), TEST_DB_EQUAL);
}

BOOST_AUTO_TEST_CASE(calculate_varible_with_time)
{
    Plane result_plane;
    Calculate<CalcByTime>(planes_max[0], planes_max[1], planes_max[2], result_plane, target_plane);
    BOOST_CHECK_LT(fabs(result_plane.time - 5), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.distance - 50), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.pos.x() - 50), TEST_DB_EQUAL);
}

BOOST_AUTO_TEST_CASE(calculate_varible_with_pos_x)
{
    Plane result_plane;
    Calculate<CalcByPosX>(planes_max[0], planes_max[1], planes_max[2], result_plane, target_plane);
    BOOST_CHECK_LT(fabs(result_plane.time - 5), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.distance - 60), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.pos.x() - 60), TEST_DB_EQUAL);
}

BOOST_AUTO_TEST_CASE(calculate_container_with_time)
{
    Plane result_plane;
    auto it = Calculate<CalcByTime>(planes_max.begin(), planes_max.end(), result_plane, target_plane);
    bool is_calc_success = it != planes_max.end();
    BOOST_CHECK(is_calc_success);
    BOOST_CHECK_LT(fabs(result_plane.time - 5), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.distance - 50), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.pos.x() - 50), TEST_DB_EQUAL);
}

BOOST_AUTO_TEST_CASE(calculate_container_with_pos_x)
{
    Plane result_plane;
    auto it = Calculate<CalcByPosX>(planes_max.begin(), planes_max.end(), result_plane, target_plane);
    bool is_calc_success = it != planes_max.end();
    BOOST_CHECK(is_calc_success);
    BOOST_CHECK_LT(fabs(result_plane.time - 5), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.distance - 60), TEST_DB_EQUAL);
    BOOST_CHECK_LT(fabs(result_plane.pos.x() - 60), TEST_DB_EQUAL);
}

BOOST_AUTO_TEST_SUITE_END()
