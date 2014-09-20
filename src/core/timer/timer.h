/**
 * @file    core/timer/timer.h
 *
 * @brief   Qta::Core::Timer class header
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_TIMER_TIMER_H
#define QTA_CORE_TIMER_TIMER_H

#include "../../externals/serialization/archive.h"
#include "../api/typedef.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Timer
 */
class Timer
{
    SERIALIZE_ARCHIVE_FRIEND

public:
    /**
     * @brief Default Constructor
     */
    Timer();

    /**
     * @brief Start this timer
     */
    void Start();

    /**
     * @brief Stop this timer
     */
    void Stop();

    /**
     * @brief Clear the time
     */
    void Clear();

    /**
     * @brief judge whether this timer is started
     *
     * @return true if this timer is started else false
     */
    bool IsStarted() const;

    /**
     * @brief Set a time expressed in seconds
     *
     * @param time time to set expressed in seconds
     */
    void SetTimeSecond(const UnsignedSecondType time);

    /**
     * @brief Get the current time of this timer
     */
    UnsignedSecondType GetCurrentTime() const;

    /**
     * @brief Decrease the last counted time
     *
     * @param max_time max time to decrease
     * @return really decreased time
     */
   UnsignedSecondType DecreaseLastCountedTime(
            const UnsignedSecondType max_time);

    /**
     * @brief Add time into the current time
     *
     * @param time time to add
     */
    void AddCurrentTime(const UnsignedSecondType time);

    /**
     * @brief Get the time that this timer counted last time
     *
     * @return time that this timer counted last time
     */
    UnsignedSecondType GetLastCountedTime() const { return last_counted_time_; }

private:
    UnsignedSecondType accumulated_time_;
    UnsignedSecondType started_time_point_;
    UnsignedSecondType last_counted_time_;

};

/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Declarations of serialization
 *============================================================================*/

template <> void Serialization::IArchive::Load(Qta::Core::Timer& timer);
template <> void Serialization::OArchive::Save(const Qta::Core::Timer& timer);


#endif // QTA_CORE_TIMER_TIMER_H
