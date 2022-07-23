#ifndef __DATA_TYPE_HPP__
#define __DATA_TYPE_HPP__
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <boost/type_traits.hpp>
#include <boost/preprocessor/variadic.hpp>

using std::vector;

typedef Eigen::Vector3d Point;

struct Plane
{
    double time;
    double distance;
    Point pos;
    Point vel;
    Point pos_1;
    Point vel_1;
};

enum ReturnValue
{
    SUCCESS = 0,
    FAILURE = 1
};
typedef ReturnValue RV;

struct CalcByTime;
struct CalcByPosX;

template <typename T>
struct is_calc_by_time : boost::false_type{};

template <>
struct is_calc_by_time<CalcByTime> : boost::true_type{};

#define REGISTER_HELP(pivot, suffix) \
    result.suffix  = CalculateHelper(target.pivot, p1.pivot, p2.pivot, p3.pivot, p1.suffix, p2.suffix, p3.suffix);

#define REGISTER_POINT_DO_BODY(r, data, elem) \
    REGISTER_HELP(data, elem.x())            \
    REGISTER_HELP(data, elem.y())            \
    REGISTER_HELP(data, elem.z())

#define REGISTER_POINT_TYPE(type, pivot, ...)                                                   \
    BOOST_PP_SEQ_FOR_EACH(REGISTER_POINT_DO_BODY, pivot, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
    while (0)

#define REGISTER_NORMAL_DO_BODY(r, data, elem) \
    REGISTER_HELP(data, elem) 

#define REGISTER_NORMAL_TYPE(type, pivot, ...)                                                   \
    BOOST_PP_SEQ_FOR_EACH(REGISTER_NORMAL_DO_BODY, pivot, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
    while (0)

#endif // __DATA_TYPE_HPP__