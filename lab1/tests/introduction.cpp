#include <regex>

#include <catch2/catch_all.hpp>

#include <introduction.hpp>

TEST_CASE("introduction")
{
    introduction intr;
    static_assert(sizeof(intr) > 1);

    CHECK(std::regex_match(intr.name().data(), std::regex{R"([A-Z]\w+)"}));
    CHECK(std::regex_match(intr.surename().data(), std::regex{R"([A-Z]\w+)"}));
    CHECK(std::regex_match(intr.fullname(), std::regex{R"(\w+ \w+)"}));
}
