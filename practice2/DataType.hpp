#ifndef __DATA_TYPE_HPP__
#define __DATA_TYPE_HPP__
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <boost/type_traits.hpp>
using std::vector;

typedef Eigen::Vector3d Point;

struct Plane{
    double time;
    double distance;
    Point pos;
    Point vel;
    Point pos_1;
    Point vel_1;
};

enum ReturnValue{
    SUCCESS = 0,
    FAILURE = 1
};
typedef ReturnValue RV;

enum FindMode{
    FIND_WITH_TIME,
    FIND_WITH_POS_X
};

struct CalcByTime;
struct CalcByPosX;

template <typename T>
struct is_calc_by_time : boost::false_type {};

template <>
struct is_calc_by_time<CalcByTime> : boost::true_type {};


#endif // __DATA_TYPE_HPP__