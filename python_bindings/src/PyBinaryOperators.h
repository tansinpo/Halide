#ifndef HALIDE_PYTHON_BINDINGS_add_binary_operators_H
#define HALIDE_PYTHON_BINDINGS_add_binary_operators_H

#include <boost/python/operators.hpp>
#include <boost/python/self.hpp>

template <typename A, typename B, typename WrappedType>
auto floordiv(A a, B b) -> decltype(a / b) {
    // Halide does floordiv by default over Expr and similar.
    // see https://lists.csail.mit.edu/pipermail/halide-dev/2015-June/001679.html
    return a / b;
}

template <typename PythonClass, typename T>
void add_binary_operators_with(PythonClass &class_instance) {
    using namespace boost::python;

    typedef typename PythonClass::wrapped_type wrapped_t;

    // <boost/python/operators.hpp> lists all operators
    class_instance
        .def(self + other<T>())
        .def(other<T>() + self)

        .def(self - other<T>())
        .def(other<T>() - self)

        .def(self * other<T>())
        .def(other<T>() * self)

        .def(self / other<T>())
        .def(other<T>() / self)

        .def(self % other<T>())
        .def(other<T>() % self)

        .def(pow(self, other<T>()))
        .def(pow(other<T>(), self))

        .def(self & other<T>())  // and
        .def(other<T>() & self)

        .def(self | other<T>())  // or
        .def(other<T>() | self)

        .def(self < other<T>())
        .def(other<T>() < self)

        .def(self <= other<T>())
        .def(other<T>() <= self)

        .def(self == other<T>())
        .def(other<T>() == self)

        .def(self != other<T>())
        .def(other<T>() != self)

        .def(self > other<T>())
        .def(other<T>() > self)

        .def(self >= other<T>())
        .def(other<T>() >= self)

        .def(self >> other<T>())
        .def(other<T>() >> self)

        .def(self << other<T>())
        .def(other<T>() << self)

        .def("__floordiv__", &floordiv<wrapped_t, T, wrapped_t>)
        .def("__floordiv__", &floordiv<T, wrapped_t, wrapped_t>)

        ;
}

template <typename PythonClass>
void add_binary_operators(PythonClass &class_instance) {
    using namespace boost::python;

    typedef typename PythonClass::wrapped_type wrapped_t;

    // The order of definitions matters.
    // Python first will try input value as int, then float, then wrapped_t
    add_binary_operators_with<PythonClass, wrapped_t>(class_instance);
    add_binary_operators_with<PythonClass, float>(class_instance);
    add_binary_operators_with<PythonClass, int>(class_instance);

    // Define unary operators
    // <boost/python/operators.hpp> lists all operators
    class_instance
        .def(-self)  // neg
        //.def(+self) // pos
        .def(~self)  // invert
        //.def(abs(self))
        //.def(!!self) // nonzero
        ;
}

#endif  // HALIDE_PYTHON_BINDINGS_add_binary_operators_H
