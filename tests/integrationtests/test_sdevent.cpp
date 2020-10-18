/* SPDX-License-Identifier: LGPL-2.1+ */

#include <chrono>
#include <iostream>

#include "fixture_sdevent.hpp"

using namespace std;
using namespace sdevent;
using namespace sdevent::test;

static void defer_handler_1(Source& source)
{
    int* var1 = static_cast<int*>(source.getUserdata());
    *var1 = *var1 + 1;
}

TEST_F(FixtureSdEvent, DeferOneShot)
{
    int var1 = 17;
    auto defer = m_sdevent->addDeferOneShot(&defer_handler_1, &var1);
    runSdEvent(3);
    EXPECT_EQ(var1, 18);
    defer->setEnabled(SD_EVENT_ONESHOT);
    runSdEvent(3);
    EXPECT_EQ(var1, 19);
    defer->setEnabled(SD_EVENT_ON);
    runSdEvent(3);
    EXPECT_EQ(var1, 22);
    defer->setEnabled(SD_EVENT_OFF);
    runSdEvent(3);
    EXPECT_EQ(var1, 22);
}
