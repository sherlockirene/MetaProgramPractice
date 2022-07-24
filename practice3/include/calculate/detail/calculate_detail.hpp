#ifndef __TEMPLATE_DETAIL_HPP__
#define __TEMPLATE_DETAIL_HPP__
#include <iostream>
#include "calculate_def.hpp"
#include "../../DataType.hpp"
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
            void caclulate_imp2_is_time_type(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target, const boost::true_type &)
            {
                GENERATE_CALC_CODE(Plane, time)
            }

            template <typename DataType>
            void caclulate_imp2_is_time_type(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target, const boost::false_type &)
            {
                GENERATE_CALC_CODE(Plane, pos.x())
            }

            template <typename T, typename DataType>
            void caclulate_imp_varible(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target)
            {
                result.time = target.time;
                caclulate_imp2_is_time_type(p1, p2, p3, result, target, typename boost::integral_constant<bool, is_calc_by_time<T>::value>());
            }

            template <typename T, typename InputIterator, typename DataType, typename Predicate>
            InputIterator caclulate_imp_serch(InputIterator begin, InputIterator end, DataType &result, const DataType &target, Predicate p)
            {
                begin = find_if(next(begin), prev(end), p);
                if (begin == prev(end)) return end;

                caclulate_imp_varible<T>(*prev(begin), *begin, *next(begin), result, target);
                return begin;
            }

            template <typename T, typename InputIterator, typename DataType>
            InputIterator caclulate_imp_predicate(InputIterator begin, InputIterator end, DataType &result, const DataType &target, const boost::true_type &)
            {
                auto p = [&target](const DataType &plane)
                { return plane.time > target.time; };
                return caclulate_imp_serch<T>(begin, end, result, target, p);
            }

            template <typename T, typename InputIterator, typename DataType>
            InputIterator caclulate_imp_predicate(InputIterator begin, InputIterator end, DataType &result, const DataType &target, const boost::false_type &)
            {
                auto p = [&target](const DataType &plane)
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