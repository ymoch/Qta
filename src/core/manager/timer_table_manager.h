/**
 * @file    core/manager/category_manager.h
 *
 * @brief   Qta::Core::TimerTableManager class header
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_MANAGER_TIMER_TABLE_MANAGER_H
#define QTA_CORE_MANAGER_TIMER_TABLE_MANAGER_H

#include <vector>
#include "../../externals/id_maker/id_maker.h"
#include "../api/return_code.h"
#include "../timer/timer_item.h"
#include "category_manager.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Model of a timer table
 */
class TimerTableManager
{
    SERIALIZE_ARCHIVE_FRIEND

public:
    /**
     * @brief Type of the items
     */
    typedef std::vector<TimerItem> ItemsType;

    /**
     * @brief Type of the size of the items
     */
    typedef ItemsType::size_type ItemsSizeType;

    /**
     * @brief Default constructor
     */
    TimerTableManager();

    /**
     * @brief Clear
     */
    void Clear();

    /**
     * @brief Get the number of items
     *
     * @return the number of items
     */
    ItemsSizeType GetSize() const { return items_.size(); }

    /**
     * @brief Judge whether a working item exists
     *
     * @return true if a working item exists else false
     */
    bool IsWorkingItemExists() const { return working_item_index_ != kInvalidSize; }

    /**
     * @brief Get the index of the working item
     *
     * @return index of the working item if a working item exists else the invalid value
     */
    ItemsSizeType GetWorkingItemIndex() const { return working_item_index_; }

    /**
     * @brief Judge whether a last working item exists
     *
     * @return true if the last working item exists else false
     */
    bool IsLastWorkingItemExists() const { return last_working_item_index_ != kInvalidSize; }

    /**
     * @brief Get the index of the working last item
     *
     * @return index of the last working item if that exists else the invalid value
     */
    ItemsSizeType GetLastWorkingItemIndex() const { return last_working_item_index_; }

    /**
     * @brief Get the reference to the name of the timer
     *
     * @param idx index of the item
     * @return reference to the name
     */
    const std::string& GetNameConstRef(const ItemsSizeType idx) const;

    /**
     * @brief Get the current time
     *
     * @param idx index of the item
     * @return current time
     */
    UnsignedSecondType GetCurrentTime(const ItemsSizeType idx) const;

    /**
     * @brief Get the last-counted time
     *
     * @param idx index of the item
     * @return last-counted time
     */
    UnsignedSecondType GetLastCountedTime(const ItemsSizeType idx) const;

    /**
     * @brief Get the category ID
     *
     * @param idx index of the item
     * @return category ID
     */
    IdType GetCategoryId(const ItemsSizeType idx) const;

    /**
     * @brief Set the category ID
     *
     * @param idx index of the item
     * @param id  category ID
     */
    void SetCategoryId(const ItemsSizeType idx, IdType id);

    /**
     * @brief Switch the working timer to the specified one
     *
     * @param idx index of the item
     */
    void SwitchTimer(const ItemsSizeType idx);

    /**
     * @brief Stop the working timer
     */
    void StopTimer();

    /**
     * @brief Reset a timer
     *
     * @param idx index of the timer
     */
    void ResetTimer(const ItemsSizeType idx);

    /**
     * @brief Reset all timer
     */
    void ResetAllTimer();

    /**
     * @brief Edit a time
     * @param idx  index of timer
     * @param time new time
     */
    void EditTime(const ItemsSizeType idx,
                  const UnsignedSecondType time);

    /**
     * @brief Move time
     *
     * @param from index of timer taken time
     * @param to   index of timer added time into
     * @param time moved time
     */
    void MoveTime(const ItemsSizeType from,
                  const ItemsSizeType to,
                  const UnsignedSecondType time);

    /**
     * @brief Add a new timer
     *
     * @param name name of the new timer
     */
    void AddTimer(const std::string& name);

    /**
     * @brief Add a new timer
     *
     * @param name name of the new timer
     */
    void EditTimer(const ItemsSizeType idx, const std::string& name);

    /**
     * @brief Delete the specified timer
     *
     * @param idx index of the item
     */
    void DeleteTimer(const ItemsSizeType idx);

private:
    static const ItemsSizeType kInvalidSize = 0xffffffff; /**< Invalid size value */

    ItemsType items_;                       /**< Timer items */
    ItemsSizeType working_item_index_;      /**< index of the working timer item */
    ItemsSizeType last_working_item_index_; /**< index of the last working timer item */

    IdMaker::IdMaker item_id_maker_;        /**< Item ID maker */
};

/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Declarations of types
 *============================================================================*/

template <> void Serialization::IArchive::Load(Qta::Core::TimerTableManager& model);
template <> void Serialization::OArchive::Save(const Qta::Core::TimerTableManager& model);

#endif // QTA_CORE_MANAGER_TABLE_MANAGER_H

