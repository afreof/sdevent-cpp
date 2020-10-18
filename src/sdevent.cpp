/* SPDX-License-Identifier: LGPL-2.1+ */

#include "sdevent-cpp/sdevent.hpp"

using namespace std;

namespace sdevent
{

SdEvent::SdEvent(bool watchdog, bool default_sigs) : m_event(NULL)
{
    int r;

    r = sd_event_default(&m_event);
    if (r < 0)
    {
        throw system_error(-r, generic_category());
    }

    if (default_sigs)
    {
        sigset_t ss;
        if (sigemptyset(&ss) < 0 || sigaddset(&ss, SIGTERM) < 0 || sigaddset(&ss, SIGINT) < 0)
        {
            throw system_error(errno, generic_category());
        }

        /* Block SIGTERM first, so that the event loop can handle it */
        if (sigprocmask(SIG_BLOCK, &ss, NULL) < 0)
        {
            throw system_error(errno, generic_category());
        }

        /* Let's make use of the default handler and "floating" reference
         * features of sd_event_add_signal() */
        r = sd_event_add_signal(m_event, NULL, SIGTERM, NULL, NULL);
        if (r < 0)
        {
            throw system_error(-r, generic_category());
        }

        r = sd_event_add_signal(m_event, NULL, SIGINT, NULL, NULL);
        if (r < 0)
        {
            throw system_error(-r, generic_category());
        }
    }

    if (watchdog)
    {
        /* Enable automatic service watchdog support */
        r = sd_event_set_watchdog(m_event, true);
        if (r < 0)
        {
            throw system_error(-r, generic_category());
        }
    }
}

SdEvent::~SdEvent()
{
    m_event = sd_event_unref(m_event);
}

void SdEvent::run(chrono::milliseconds usec)
{
    uint64_t usec_i = usec.count();
    int r = sd_event_run(m_event, usec_i);
    if (r < 0)
    {
        throw system_error(-r, generic_category());
    }
}

void SdEvent::loop()
{
    int r = sd_event_loop(m_event);
    if (r < 0)
    {
        throw system_error(-r, generic_category());
    }
}

}  // namespace sdevent
