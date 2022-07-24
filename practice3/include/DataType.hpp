#ifndef __DATA_TYPE_HPP__
#define __DATA_TYPE_HPP__
#include <iostream>
#include <Eigen/Dense>
#include <boost/type_traits.hpp>

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

#define REGISTER_ELEMENT_POINT pos, vel, pos_1, vel_1
#define REGISTER_ELEMENT_NORMAL distance

#define GENERATE_CALC_CODE(type, pivot)                      \
    REGISTER_POINT_TYPE(type, pivot, REGISTER_ELEMENT_POINT) \
    REGISTER_NORMAL_TYPE(type, pivot, REGISTER_ELEMENT_NORMAL)

#endif // __DATA_TYPE_HPP__