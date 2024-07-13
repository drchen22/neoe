#include <catch2/catch_test_macros.hpp>
#include <runtime/core/meta/var_traits.hpp>
#include <type_traits>

using namespace Neoe;

struct Person { 
    bool isFemale(Person other) { return other.sex; }
    bool isFemaleConst() const { return sex; }
    bool sex;
};
int var = 1;

TEST_CASE("type erase", "[type_erase]") {
    auto ptr = &Person::isFemale;
    using func_info1 = func_traits<decltype(ptr)>;
    REQUIRE(std::is_same_v<func_info1::param_type, int>);
    REQUIRE(std::is_same_v<func_info1::return_type, void>);

    auto ptr2 = &Person::isFemaleConst;
    using func_info2 = func_traits<decltype(ptr2)>;
    REQUIRE(std::is_same_v<func_info2::param_type, int>);
    REQUIRE(std::is_same_v<func_info2::return_type, void>);
}