#pragma once

#include <tuple>

namespace Neoe {
namespace Refelction {

namespace detail {}
template <typename T>
struct func_traits;

template <typename Ret, typename... Args>
struct func_traits<Ret (*)(Args...)> {
    using return_type = Ret;
    using param_type = std::tuple<Args...>;
    static constexpr bool is_member = false;
};

template <typename Ret, typename Class, typename... Args>
struct func_traits<Ret (Class::*)(Args...)> {
    using return_type = Ret;
    using class_type = Class;
    using param_type = std::tuple<Args...>;
    static constexpr bool is_member = true;
};

// const 特化
template <typename Ret, typename Class, typename... Args>
struct func_traits<Ret (Class::*)(Args...) const> {
    using return_type = Ret;
    using class_type = Class;
    using param_type = std::tuple<Args...>;
    static constexpr bool is_member = true;
};
} // namespace Refelction
} // namespace Neoe
