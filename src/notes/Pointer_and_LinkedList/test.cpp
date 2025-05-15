#include "fff.h"
#include <gtest/gtest.h>

#include "main.cpp"

DEFINE_FFF_GLOBALS; 



class LinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        FFF_RESET_HISTORY();
    }

    void TearDown() override {}
};


TEST_F(LinkedListTest, NominalCheck) {
    
}