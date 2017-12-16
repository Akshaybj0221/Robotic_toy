#include <ros/ros.h>
#include <gtest/gtest.h>

/**
 * @brief main function for running all google tests
 *
 * @param  argc is the argument count
 * @param  argv is the argument vector
 *
 * @return 0 if all tests pass else 1
 */

int main(int argc, char **argv) {
  ros::init(argc, argv, "test_node");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
