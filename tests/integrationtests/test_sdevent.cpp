/* SPDX-License-Identifier: LGPL-2.1+ */

#include <chrono>

#include "fixture_sdevent.hpp"

using namespace std;
using namespace sdevent;
using namespace sdevent::test;

TEST_F(FixtureSdEvent, RunOnce)
{
    m_sdevent->run(chrono::milliseconds(10));
}
