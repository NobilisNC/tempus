#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define TEMPUS_IMPL 1
#include <tempus.h>

#include <fstream>

TEST_CASE("TEMPUS", "") {
    auto a = tempus::tmpDir();
    auto b =  tempus::tmpDir();
    REQUIRE(a != b);

    auto c = tempus::tmpDir("hello");
    auto d = tempus::tmpDir("abc");
    REQUIRE(c != d);

    auto x = tempus::uniqueName("abc");
    REQUIRE(d != x);
    REQUIRE(x != tempus::uniqueName("abc"));


    std::fstream file;
    file.open(tempus::tmpFile(), std::ios::out);
    REQUIRE(file.is_open());
}
