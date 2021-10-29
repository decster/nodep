#include <glog/logging.h>
#include "absl/random/random.h"
#include "absl/time/clock.h"
#include "absl/strings/str_format.h"
#include <gtest/gtest.h>

TEST(nodep, nodep) {
    EXPECT_TRUE(true);
}


int main(int argc, char** argv) {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
}
