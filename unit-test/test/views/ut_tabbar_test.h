
#ifndef UT_TABBAR_TEST_H
#define UT_TABBAR_TEST_H

#include <gtest/gtest.h>

class UT_Tabbar_Test : public ::testing::Test
{
public:
    UT_Tabbar_Test();

public:
    //这里的几个函数都会自动调用

    //用于做一些初始化操作
    virtual void SetUp();

    //用于做一些清理操作
    virtual void TearDown();
};

#endif // UT_TABBAR_TEST_H

