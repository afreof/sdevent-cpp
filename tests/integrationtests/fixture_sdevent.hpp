/* SPDX-License-Identifier: LGPL-2.1+ */

#pragma once

#include <gtest/gtest.h>

#include <memory>

#include "sdevent-cpp/sdevent.hpp"

namespace sdevent
{
namespace test
{

class FixtureSdEvent : public ::testing::Test
{
   public:
    static void SetUpTestCase()
    {
    }

    static void TearDownTestCase()
    {
    }

   private:
    void SetUp() override
    {
        m_sdevent = std::make_unique<sdevent::SdEvent>();
    }

    void TearDown() override
    {
    }

   public:
    std::unique_ptr<sdevent::SdEvent> m_sdevent;
};

}  // namespace test
}  // namespace sdevent
