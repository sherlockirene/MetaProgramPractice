#ifndef __DATA_TYPE_HPP__
#define __DATA_TYPE_HPP__
#include <iostream>
#include <Eigen/Dense>
#include <vector>

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
    FIND_WITH_TIME = 0,
    FIND_WITH_POS_X,
    FIND_MODE_LAST 
};

#endif // __DATA_TYPE_HPP__