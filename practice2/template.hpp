#ifndef __TEMPLATE_MY_HPP__
#define __TEMPLATE_MY_HPP__
#include "DataType.hpp"
#include "detail.hpp"
using std::next;
using std::prev;

namespace Model
{
    namespace Core
    {
        template <typename T, typename InputIterator, typename DataType>
        InputIterator Calculate(InputIterator begin, InputIterator end, DataType &result, const DataType &target)
        {
            if (begin >= end || begin == prev(end) || begin == prev(end, 2))
                return end;
            return Core::detail::caclulate_imp<T>(begin, end, result, target);
        }

        template <typename T, typename DataType>
        RV Calculate(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target)
        {
            return Core::detail::caclulate_imp2<T>(p1, p2, p3, result, target);
        }
    }
}


class Calculator
{
public:
    Calculator() {}
    ~Calculator() {}

    RV CalculateNormal(const std::vector<Plane> &planes, const Plane &target_plane, Plane &result, const FindMode &mode)
    {
        switch (mode)
        {
        case FIND_WITH_TIME:
            return CalculateNormalWithTime(planes, target_plane, result);
        case FIND_WITH_POS_X:
            return CalculateNormalWithPosX(planes, target_plane, result);
        default:
            return FAILURE;
        }
        return SUCCESS;
    }

    RV CalculateNormalWithTime(const std::vector<Plane> &planes, const Plane &target_plane, Plane &result)
    {
        if (planes.size() < 3)
            return FAILURE;
        auto mid = find_if(next(planes.begin()), prev(planes.end()), [&target_plane](const Plane &plane)
                           { return plane.time > target_plane.time; });

        if (mid == prev(planes.end()))
            return FAILURE;

        return CalculateHelperWithTime(*prev(mid), *mid, *next(mid), target_plane, result);
    }

    RV CalculateNormalWithPosX(const std::vector<Plane> &planes, const Plane &target_plane, Plane &result)
    {
        if (planes.size() < 3)
            return FAILURE;
        auto mid = find_if(next(planes.begin()), prev(planes.end()), [&target_plane](const Plane &plane)
                           { return plane.pos.x() > target_plane.pos.x(); });

        if (mid == prev(planes.end()))
            return FAILURE;

        return CalculateHelperWithPosX(*prev(mid), *mid, *next(mid), target_plane, result);
    }

    RV CalculateHelperWithTime(const Plane &p1, const Plane &p2, const Plane &p3, const Plane &target, Plane &result)
    {
        result.time = target.time;
        result.pos.x() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.pos.x(), p2.pos.x(), p3.pos.x());
        result.pos.y() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.pos.y(), p2.pos.y(), p3.pos.y());
        result.pos.z() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.pos.z(), p2.pos.z(), p3.pos.z());
        result.vel.x() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.vel.x(), p2.vel.x(), p3.vel.x());
        result.vel.y() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.vel.y(), p2.vel.y(), p3.vel.y());
        result.vel.z() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.vel.z(), p2.vel.z(), p3.vel.z());
        result.pos_1.x() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.pos_1.x(), p2.pos_1.x(), p3.pos_1.x());
        result.pos_1.y() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.pos_1.y(), p2.pos_1.y(), p3.pos_1.y());
        result.pos_1.z() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.pos_1.z(), p2.pos_1.z(), p3.pos_1.z());
        result.vel_1.x() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.vel_1.x(), p2.vel_1.x(), p3.vel_1.x());
        result.vel_1.y() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.vel_1.y(), p2.vel_1.y(), p3.vel_1.y());
        result.vel_1.z() = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.vel_1.z(), p2.vel_1.z(), p3.vel_1.z());
        result.distance = CalculateHelper(target.time, p1.time, p2.time, p3.time, p1.distance, p2.distance, p3.distance);

        return SUCCESS;
    }

    RV CalculateHelperWithPosX(const Plane &p1, const Plane &p2, const Plane &p3, const Plane &target, Plane &result)
    {
        result.time = target.time;
        result.pos.x() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.pos_1.x(), p2.pos_1.x(), p3.pos_1.x());
        result.pos.y() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.pos_1.y(), p2.pos_1.y(), p3.pos_1.y());
        result.pos.z() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.pos_1.z(), p2.pos_1.z(), p3.pos_1.z());
        result.vel.x() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.vel.x(), p2.vel.x(), p3.vel.x());
        result.vel.y() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.vel.y(), p2.vel.y(), p3.vel.y());
        result.vel.z() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.vel.z(), p2.vel.z(), p3.vel.z());
        result.pos_1.x() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.pos_1.x(), p2.pos_1.x(), p3.pos_1.x());
        result.pos_1.y() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.pos_1.y(), p2.pos_1.y(), p3.pos_1.y());
        result.pos_1.z() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.pos_1.z(), p2.pos_1.z(), p3.pos_1.z());
        result.vel_1.x() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.vel_1.x(), p2.vel_1.x(), p3.vel_1.x());
        result.vel_1.y() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.vel_1.y(), p2.vel_1.y(), p3.vel_1.y());
        result.vel_1.z() = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.vel_1.z(), p2.vel_1.z(), p3.vel_1.z());
        result.distance = CalculateHelper(target.pos.x(), p1.pos.x(), p2.pos.x(), p3.pos.x(), p1.distance, p2.distance, p3.distance);

        return SUCCESS;
    }

    double CalculateHelper(
        const double &x, const double &x1, const double &x2, const double &x3,
        const double &y1, const double &y2, const double &y3)
    {
        double a = (x - x2) * (x - x3) / (x1 - x2) / (x1 - x3);
        double b = (x - x1) * (x - x3) / (x2 - x1) / (x2 - x3);
        double c = (x - x1) * (x - x2) / (x3 - x1) / (x3 - x2);
        return a * y1 + b * y2 + c * y3;
    }
};
#endif