#include <string>

#include <gtest/gtest.h>

#include "package.h"

using cyclus::Package;

TEST(PackageTests, Create) {

    std::string exp_name = "foo";
    double exp_min = 0.1;
    double exp_max = 0.9;
    std::string exp_strat = "first";

    Package::Ptr p = Package::Create(exp_name, exp_min, exp_max, exp_strat);

    EXPECT_EQ(exp_name, p->name());
    EXPECT_DOUBLE_EQ(exp_min, p->fill_min());
    EXPECT_DOUBLE_EQ(exp_max, p->fill_max());
    EXPECT_EQ(exp_strat, p->strategy());

}

TEST(PackageTests, UnpackagedID) {
    EXPECT_EQ(1, Package::unpackaged_id());
}
