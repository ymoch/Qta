/**
 * @file    core/timer/timer_item.h
 *
 * @brief   Qta::Core::TimerItem class header
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_TIMER_TIMER_ITEM_H
#define QTA_CORE_TIMER_TIMER_ITEM_H

#include <string>
#include <vector>
#include "timer.h"
#include "category.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Each item on the timer list
 */
class TimerItem
{
    SERIALIZE_ARCHIVE_FRIEND
    friend class TimerTableManager;

public:
    /**
     * @brief Default constructor
     */
    TimerItem();

    /**
     * @brief constructor
     *
     * @param id ID
     * @param name name
     */
    TimerItem(const IdType id, const std::string& name);

    /**
     * @brief Start the timer
     */
    void Start();

    /**
     * @brief Stop the timer
     */
    void Stop();

    /**
     * @brief Reset and stop the timer
     */
    void Reset();

    /**
     * @brief judge whether this timer is working
     *
     * @return true if this timer is working else false
     */
    bool IsWorking() const { return timer_.IsStarted(); }

    /**
     * @brief Set the name of this timer
     *
     * @param name the new name of this timer
     */
    void SetName(const std::string& name) { name_ = name; }

    /**
     * @brief Get the ID
     *
     * @return ID
     */
    IdType GetId() const { return id_; }

    /**
     * @brief Get the category ID
     *
     * @return Category ID
     */
    IdType GetCategoryId() const { return category_id_; }

    /**
     * @brief Set the category ID
     *
     * @param id ID
     */
    void SetCategoryId(const IdType id) { category_id_ = id; }

    /**
     * @brief Get the reference to the name of this timer
     *
     * @return the reference to the name of this timer
     */
    const std::string& GetNameConstRef() const { return name_; }

    /**
     * @brief Create the formatted current time
     *
     * @return formatted current time
     */
    UnsignedSecondType GetCurrentTime() const;

    /**
     * @brief Create the formatted time that this timer counted last time
     *
     * @return formatted time that the timer counted last time
     */
    UnsignedSecondType GetLastCountedTime() const;

private:
    IdType id_;             /**< ID */
    IdType category_id_;    /**< Category ID */
    std::string name_;      /**< Name */
    Timer timer_;           /**< Timer */
};

/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Declarations of types
 *============================================================================*/

namespace Serialization
{
template <> void IArchive::Load(Qta::Core::TimerItem&);
template <> void OArchive::Save(const Qta::Core::TimerItem&);
}

#endif // QTA_CORE_TIMER_TIMER_ITEM_H
