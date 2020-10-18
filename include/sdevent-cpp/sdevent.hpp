/* SPDX-License-Identifier: LGPL-2.1+ */

#pragma once

#include <systemd/sd-event.h>

#include <chrono>
#include <memory>
#include <system_error>

#include "sdevent-cpp/defer.hpp"

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

    /**
     * @name Adds a new event source that will be dispatched
     *
     * The defer source is dispatched instantly, before the event loop goes to sleep again and waits for new events.
     * By default, the handler will be called once (SD_EVENT_ONESHOT).
     * Note that if the event source is set to SD_EVENT_ON the event loop will never go to sleep again,
     * but continuously call the handler, possibly interleaved with other event sources.
     *
     * @param handler  handler function
     * @param userdata The pointer gets forwarded to the handler function
     *
     * @return A unique_ptr to the new Defer object.
     */
    //@{
    /**
     * @brief Add a Defer in state SD_EVENT_OFF
     */
    std::unique_ptr<Defer> addDeferOff(Defer::HandlerFunc handler, void* userdata = nullptr);

    /**
     * @brief Add a Defer in state SD_EVENT_ON
     */
    std::unique_ptr<Defer> addDeferOn(Defer::HandlerFunc handler, void* userdata = nullptr);

    /**
     * @brief Add a Defer in state SD_EVENT_ONESHOT
     */
    std::unique_ptr<Defer> addDeferOneShot(Defer::HandlerFunc handler, void* userdata = nullptr);
    //@}

   protected:
    sd_event* m_event;
};

}  // namespace sdevent
