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
            template <typename DataType>
            RV caclulate_imp2_is_time_type(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target, const boost::true_type &)
            {
                REGISTER_NORMAL_TYPE(Plane, time, distance);
                REGISTER_POINT_TYPE(Plane, time, pos, vel, pos_1, vel_1);
                return SUCCESS;
            }

            template <typename DataType>
            RV caclulate_imp2_is_time_type(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target, const boost::false_type &)
            {
                REGISTER_NORMAL_TYPE(Plane, pos.x(), distance);
                REGISTER_POINT_TYPE(Plane, pos.x(), pos, vel, pos_1, vel_1);
                return SUCCESS;
            }

            template <typename T, typename DataType>
            RV caclulate_imp_varible(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target)
            {
                result.time = target.time;
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