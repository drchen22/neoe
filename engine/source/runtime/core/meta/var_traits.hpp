#pragma once

#include <cstdlib>
#include <type_traits>

namespace Neoe {
namespace Refelction {

namespace detail {

template <typename T>
struct var_type {
    using type = T;
};

template <typename T, typename Class>
struct var_type<T Class::*> {
    using type = T;
};

} // namespace detail

template <typename T>
using var_type_t = typename detail::var_type<T>::type;

namespace internal {

template <typename T>
struct basic_var_tarits {
    using type = var_type_t<T>;
    static constexpr bool is_member = std::is_member_pointer_v<T>;
};
} // namespace internal


template <typename T> struct var_traits;

template <typename T>
struct var_traits<T *> : internal::basic_var_tarits<T> {
    using pointer_type = T *;
};

template <typename T, typename Class>
struct var_traits<T Class::*> : internal::basic_var_tarits<T> {
    using pointer_type = T Class::*;
    using clazz = Class;
};





template <typename T>
struct TypeInfo;

#define BEGIN_CLASS(T) \
    template <> \
    struct TypeInfo<T> { \
        using type = T;

#define FUNCS(...) using funcs = std::tuple<__VA_ARGS__>;

#define END_CLASS() \
    } \
    ;

} // namespace Refelction

} // namespace Neoe
