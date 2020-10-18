/* SPDX-License-Identifier: LGPL-2.1+ */

#pragma once

#include <system_error>

#include "sdevent-cpp/source.hpp"

namespace sdevent
{

class Defer : public Source
{
   public:
    Defer(sd_event* event, HandlerFunc handler, void* userdata);

    Defer(Defer&& other);
    Defer& operator=(Defer&& other);

    Defer(const Defer& other) = delete;
    Defer& operator=(const Defer& other) = delete;

    ~Defer();

    void setEnabled(int enabled);
};

}  // namespace sdevent
