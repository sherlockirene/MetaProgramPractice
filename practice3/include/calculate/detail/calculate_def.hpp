#ifndef __CALCULATE_DEF_HPP__
#define __CALCULATE_DEF_HPP__
#include <boost/preprocessor/variadic.hpp>

#define REGISTER_HELP(pivot, suffix) \
    result.suffix = CalculateHelper(target.pivot, p1.pivot, p2.pivot, p3.pivot, p1.suffix, p2.suffix, p3.suffix);

#define REGISTER_POINT_DO_BODY(r, pivot, elem) \
    REGISTER_HELP(pivot, elem.x())             \
    REGISTER_HELP(pivot, elem.y())             \
    REGISTER_HELP(pivot, elem.z())

#define REGISTER_POINT_TYPE(type, pivot, ...) \
    BOOST_PP_SEQ_FOR_EACH(REGISTER_POINT_DO_BODY, pivot, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define REGISTER_NORMAL_DO_BODY(r, pivot, elem) \
    REGISTER_HELP(pivot, elem)

#define REGISTER_NORMAL_TYPE(type, pivot, ...) \
    BOOST_PP_SEQ_FOR_EACH(REGISTER_NORMAL_DO_BODY, pivot, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#endif // __CALCULATE_DEF_HPP__