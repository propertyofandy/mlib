#include <gtest/gtest.h>

#include "../../type/Record.hpp"

using namespace mxxlib;
// Test default constructor
TEST(RecordTest, DefaultConstructor) {
    Record<int, double, std::string> record;
    // No specific runtime check, just ensuring it compiles.
}

// Test parameterized constructor
TEST(RecordTest, ParameterizedConstructor) {
    Record<int, double, std::string> record(42, 3.14, "Hello");
    EXPECT_EQ(record.get<int>(), 42);
    EXPECT_DOUBLE_EQ(record.get<double>(), 3.14);
    EXPECT_EQ(record.get<std::string>(), "Hello");
}

// Test non-const get()
TEST(RecordTest, NonConstGet) {
    Record<int, double, std::string> record(42, 3.14, "Hello");
    record.get<int>() = 100; // Modify the value
    EXPECT_EQ(record.get<int>(), 100);
}

// Test const get()
TEST(RecordTest, ConstGet) {
    const Record<int, double, std::string> record(42, 3.14, "Hello");
    EXPECT_EQ(record.get<int>(), 42);
    EXPECT_DOUBLE_EQ(record.get<double>(), 3.14);
    EXPECT_EQ(record.get<std::string>(), "Hello");
}
