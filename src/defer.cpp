/* SPDX-License-Identifier: LGPL-2.1+ */

#include "sdevent-cpp/defer.hpp"

using namespace std;

namespace sdevent
{

Defer::Defer(sd_event* event, HandlerFunc handler, void* userdata) : Source(handler, userdata)
{
    int r = sd_event_add_defer(event, &m_event_source, &handlerC, this);
    if (r < 0)
    {
        throw system_error(-r, generic_category());
    }
}

Defer::Defer(Defer&& other) : Source(move(other))
{
}

Defer& Defer::operator=(Defer&& other)
{
    Source::operator=(move(other));
    return *this;
}

Defer::~Defer()
{
}

void Defer::setEnabled(int enabled)
{
    int r = sd_event_source_set_enabled(m_event_source, enabled);
    if (r < 0)
    {
        throw system_error(-r, generic_category());
    }
}

}  // namespace sdevent
