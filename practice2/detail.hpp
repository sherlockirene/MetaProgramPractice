#ifndef __TEMPLATE_DETAIL_HPP__
#define __TEMPLATE_DETAIL_HPP__
#include "DataType.hpp"
namespace Model
{
    namespace Core
    {
        double CalculateHelper(
            const double &x, const double &x1, const double &x2, const double &x3,
            const double &y1, const double &y2, const double &y3)
        {
            double a = (x - x2) * (x - x3) / (x1 - x2) / (x1 - x3);
            double b = (x - x1) * (x - x3) / (x2 - x1) / (x2 - x3);
            double c = (x - x1) * (x - x2) / (x3 - x1) / (x3 - x2);
            return a * y1 + b * y2 + c * y3;
        }
        namespace detail
        {

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

            template <typename DataType>
            RV caclulate_imp2_is_time_type(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target, const boost::true_type &)
            {
                return CalculateHelperWithTime(p1, p2, p3, target, result);
            }

            template <typename DataType>
            RV caclulate_imp2_is_time_type(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target, const boost::false_type &)
            {
                return CalculateHelperWithPosX(p1, p2, p3, target, result);
            }

            template <typename T, typename DataType>
            RV caclulate_imp_varible(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target)
            {
                return caclulate_imp2_is_time_type(p1, p2, p3, result, target, typename boost::integral_constant<bool, is_calc_by_time<T>::value>());
            }

            template <typename T, typename InputIterator, typename DataType, typename Predicate>
            InputIterator caclulate_imp_serch(InputIterator begin, InputIterator end, DataType &result, const DataType &target, Predicate p)
            {
                auto mid = find_if(next(begin), prev(end), p);
                if (mid == prev(end))
                    return end;

                auto &p1 = *prev(mid);
                auto &p2 = *mid;
                auto &p3 = *next(mid);
                auto rv = caclulate_imp_varible<T>(p1, p2, p3, result, target);
                return rv == SUCCESS ? mid : end;
            }
            template <typename T, typename InputIterator, typename DataType>
            InputIterator caclulate_imp_predicate(InputIterator begin, InputIterator end, DataType &result, const DataType &target, const boost::true_type &)
            {
                auto p = [&target](const Plane &plane)
                { return plane.time > target.time; };
                return caclulate_imp_serch<T>(begin, end, result, target, p);
            }

            template <typename T, typename InputIterator, typename DataType>
            InputIterator caclulate_imp_predicate(InputIterator begin, InputIterator end, DataType &result, const DataType &target, const boost::false_type &)
            {
                auto p = [&target](const Plane &plane)
                { return plane.pos.x() > target.pos.x(); };
                return caclulate_imp_serch<T>(begin, end, result, target, p);
            }

            template <typename T, typename InputIterator, typename DataType>
            InputIterator caclulate_container_imp(InputIterator begin, InputIterator end, DataType &result, const DataType &target)
            {
                typedef typename boost::integral_constant<bool, is_calc_by_time<T>::value> truth_type;
                return caclulate_imp_predicate<T>(begin, end, result, target, truth_type());
            }

        }
    }
}
#endif // __TEMPLATE_DETAIL_HPP__