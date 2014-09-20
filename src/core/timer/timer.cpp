/**
 * @file    core/timer/timer.cpp
 *
 * @brief   Qta::Core::Timer class implementation
 *
 * @author  ymoch
 */

#include <ctime>
#include "timer.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of local functions
 *============================================================================*/

/**
 * @brief Get the current time point
 *
 * @return current time point
 */
static inline Qta::Core::UnsignedSecondType FindCurrentTimePoint()
{
    return static_cast<Qta::Core::UnsignedSecondType>(std::time(NULL));
}

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

Timer::Timer()
{
    Clear();
}

void Timer::Start()
{
    if (IsStarted()) {
        return;
    }
    started_time_point_ = FindCurrentTimePoint();
    last_counted_time_ = 0;
}

void Timer::Stop()
{
    const UnsignedSecondType temp_time_point = FindCurrentTimePoint();
    const UnsignedSecondType elapsed_time = temp_time_point - started_time_point_;
    accumulated_time_ += elapsed_time;
    last_counted_time_ = elapsed_time;

    started_time_point_ = 0;
}

void Timer::Clear()
{
    accumulated_time_ = 0;
    started_time_point_ = 0;
    last_counted_time_ = 0;
}

bool Timer::IsStarted() const
{
    return started_time_point_ != 0;
}

void Timer::SetTimeSecond(const UnsignedSecondType time)
{
    Clear();
    accumulated_time_ = time;
}

UnsignedSecondType Timer::GetCurrentTime() const
{
    if (IsStarted()) {
        const UnsignedSecondType elapsed_time = FindCurrentTimePoint() - started_time_point_;
        return accumulated_time_ + elapsed_time;
    }
    return accumulated_time_;
}

UnsignedSecondType Timer::DecreaseLastCountedTime(const UnsignedSecondType max_time)
{
    if (max_time > last_counted_time_) {
        const UnsignedSecondType decreased_time = last_counted_time_;
        last_counted_time_ = 0;
        accumulated_time_ -= decreased_time;
        return decreased_time;
    }
    last_counted_time_ -= max_time;
    accumulated_time_ -= max_time;
    return max_time;
}

void Timer::AddCurrentTime(const UnsignedSecondType time)
{
    if (IsStarted()) {
        started_time_point_ -= time;
    } else {
        accumulated_time_ += time;
    }
}

/* End of namespace Qta::Core */
}

/* End of namespace Qta */
}

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <>
void Serialization::IArchive::Load(Qta::Core::Timer& timer)
{
    timer.Clear();
    *this >> timer.accumulated_time_
          >> timer.last_counted_time_;
}

template <>
void Serialization::OArchive::Save(const Qta::Core::Timer& timer)
{
    if (timer.IsStarted()) {
        const Qta::Core::UnsignedSecondType temp_time_point = Qta::Core::FindCurrentTimePoint();
        const Qta::Core::UnsignedSecondType elapsed_time = temp_time_point - timer.started_time_point_;
        const Qta::Core::UnsignedSecondType current_time = elapsed_time + timer.accumulated_time_;
        const Qta::Core::UnsignedSecondType last_counted_time = elapsed_time;
        *this << current_time << last_counted_time;
    } else {
        *this << timer.accumulated_time_ << timer.last_counted_time_;
    }
}
