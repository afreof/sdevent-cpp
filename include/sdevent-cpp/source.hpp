/* SPDX-License-Identifier: LGPL-2.1+ */

#pragma once

#include <systemd/sd-event.h>

#include <functional>
#include <system_error>

namespace sdevent
{

class Source
{
   public:
    using HandlerFunc = std::function<void(Source& source)>;

    Source(HandlerFunc handler, void* userdata = nullptr);

    Source(Source&& other);
    Source& operator=(Source&& other);

    Source(const Source& other);
    Source& operator=(const Source& other);

    virtual ~Source();

    sd_event_source* getSource()
    {
        return m_event_source;
    };

    void* getUserdata()
    {
        return m_userdata;
    };

   protected:
    static int handlerC(sd_event_source* source_c, void* p_this);
    sd_event_source* m_event_source;
    HandlerFunc m_handler;
    void* m_userdata;
};

}  // namespace sdevent
