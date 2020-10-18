/* SPDX-License-Identifier: LGPL-2.1+ */

#pragma once

#include <systemd/sd-event.h>

#include <chrono>
#include <system_error>

namespace sdevent
{
class SdEvent
{
   public:
    /** @defgroup SdEvent_throws
     *
     * @throws System error code exceptions
     */

    /**
     * @brief Constructor of a new sd-event loop.
     *
     * @param watchdog Enable sd-event watchdog feature
     * @param default_sigs Setup default signal handlers for SIGINT and SIGTERM
     *
     * @copydetails SdEvent_throws
     */
    SdEvent(bool watchdog = true, bool default_sigs = true);

    virtual ~SdEvent();

    /**
     * @brief Run a single iteration of the event loop
     *
     * The function waits until an event to process is available, and dispatches the registered handler for it.
     *
     * @param usec specifies the maximum time (in microseconds) to wait for an event.
     *              Use (uint64_t) -1 to specify an infinite timeout.
     * @copydetails SdEvent_throws
     */
    virtual void run(std::chrono::milliseconds usec);

    /**
     * @brief Run the event loop forever
     *
     * @copydetails SdEvent_throws
     */
    virtual void loop();

   protected:
    sd_event* m_event;
};

}  // namespace sdevent
