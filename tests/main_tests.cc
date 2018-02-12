#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define TEMPUS_IMPL 1
#include <tempus.h>

TEST_CASE("TEMPUS", "") {
    auto tmp = tempus::tmpFilename();
    auto a = tempus::getAppDirectory();
    auto b =  tempus::getAppDirectory();
    REQUIRE(a == b);
    WARN(tmp);

   // REQUIRE(tmp.length() > 0);
   // WARN(tmp);

    //tempus::tmpDir();
}
