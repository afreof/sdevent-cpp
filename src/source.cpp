/* SPDX-License-Identifier: LGPL-2.1+ */

#include "sdevent-cpp/source.hpp"

#include <errno.h>

#include <cassert>
#include <utility>

using namespace std;

namespace sdevent
{

Source::Source(HandlerFunc handler, void* userdata) : m_event_source(nullptr), m_handler(handler), m_userdata(userdata)
{
}

Source::Source(Source&& other)
    : m_event_source(move(other.m_event_source)),
      m_handler(exchange(other.m_handler, nullptr)),
      m_userdata(exchange(other.m_userdata, nullptr))
{
    other.m_event_source = nullptr;
}

Source& Source::operator=(Source&& other)
{
    if (this != &other)
    {
        m_event_source = move(other.m_event_source);
        other.m_event_source = nullptr;
        m_handler = exchange(other.m_handler, nullptr);
        m_userdata = exchange(other.m_userdata, nullptr);
    }
    return *this;
}

Source::Source(const Source& other) : m_event_source(sd_event_source_ref(other.m_event_source))
{
}

Source& Source::operator=(const Source& other)
{
    if (this != &other)
    {
        m_event_source = sd_event_source_ref(other.m_event_source);
    }
    return *this;
}

Source::~Source()
{
    if (m_event_source)
    {
        m_event_source = sd_event_source_disable_unref(m_event_source);
    }
}

int Source::handlerC(sd_event_source* source_c, void* p_this)
{
    if (!p_this)
    {
        return -EINVAL;
    };

    auto instance = static_cast<Source*>(p_this);

    assert(source_c == instance->m_event_source);

    instance->m_handler(*instance);

    return 0;
}

}  // namespace sdevent
