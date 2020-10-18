/* SPDX-License-Identifier: LGPL-2.1+ */

#include "fixture_sdevent.hpp"

using namespace std;

namespace sdevent
{
namespace test
{

void FixtureSdEvent::runSdEvent(int n, chrono::milliseconds timeout)
{
    for (int i = 0; i < n; i++)
    {
        m_sdevent->run(chrono::milliseconds(timeout));
    }
}

}  // namespace test
}  // namespace sdevent
