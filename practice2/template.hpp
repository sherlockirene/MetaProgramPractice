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
        double CalculateHelper(
            const double &x, const double &x1, const double &x2, const double &x3,
            const double &y1, const double &y2, const double &y3);

        template <typename T, typename InputIterator, typename DataType>
        InputIterator Calculate(InputIterator begin, InputIterator end, DataType &result, const DataType &target)
        {
            if (begin >= end || begin == prev(end) || begin == prev(end, 2))
                return end;
            return Core::detail::caclulate_container_imp<T>(begin, end, result, target);
        }

        template <typename T, typename DataType>
        RV Calculate(const DataType &p1, const DataType &p2, const DataType &p3, DataType &result, const DataType &target)
        {
            return Core::detail::caclulate_imp_varible<T>(p1, p2, p3, result, target);
        }
    }
}
#endif // __TEMPLATE_MY_HPP__