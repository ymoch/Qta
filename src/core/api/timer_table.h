/**
 * @file    core/api/timer_table.h
 *
 * @brief   Qta core API Qta::Core::TimerTable class header
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_API_TIMER_TABLE_H
#define QTA_CORE_API_TIMER_TABLE_H

#include "typedef.h"
#include "return_code.h"

namespace Qta
{
namespace Core
{

class TimerTableConfig;

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Timer table
 */
class TimerTable
{
public:
    /**
     * @brief Items size type
     */
    typedef unsigned long TimersSizeType;

    /**
     * @brief Categories size type
     */
    typedef unsigned long CategoriesSizeType;

    /**
     * @brief Default constructor
     */
    TimerTable();

    /**
     * @brief Copy constructor
     */
    TimerTable(const TimerTable&);

    /**
     * @brief Destructor
     */
    ~TimerTable();

    /**
     * @brief Clear timers
     */
    void ClearTimers();

    /**
     * @brief Clear categories
     */
    void ClearCategories();

    /**
     * @brief Get the config
     *
     * @return config
     */
    TimerTableConfig* Config();
    const TimerTableConfig* Config() const;

    /**
     * @brief Get the number of items
     *
     * @return the number of items
     */
    TimersSizeType GetSize() const;

    /**
     * @brief Judge whether a working item exists
     *
     * @return true if a working item exists else false
     */
    bool IsWorkingItemExists() const;

    /**
     * @brief Get the index of the working item
     *
     * @return index of the working item if a working item exists else the invalid value
     */
    TimersSizeType GetWorkingItemIndex() const;

    /**
     * @brief Judge whether a last working item exists
     *
     * @return true if the last working item exists else false
     */
    bool IsLastWorkingItemExists() const;

    /**
     * @brief Get the index of the working last item
     *
     * @return index of the last working item if that exists else the invalid value
     */
    TimersSizeType GetLastWorkingItemIndex() const;

    /**
     * @brief Get the reference to the name of the timer
     *
     * @param idx index of the item
     * @return reference to the name
     */
    const char* GetName(const TimersSizeType idx) const;

    /**
     * @brief Get the current time
     *
     * @param idx index of the item
     * @return current time
     */
    UnsignedSecondType GetCurrentTime(const TimersSizeType idx) const;

    /**
     * @brief Get the last-counted time
     *
     * @param idx index of the item
     * @return last-counted time
     */
    UnsignedSecondType GetLastCountedTime(const TimersSizeType idx) const;

    /**
     * @brief Set the category ID of the specified timer
     *
     * @param idx   index of the item
     * @param id    category ID
     */
    void SetCategoryToTimer(
            const CategoriesSizeType category_idx,
            const TimersSizeType timer_idx);

    /**
     * @brief Switch the working timer to the specified one
     *
     * @param idx index of the item
     */
    void SwitchTimer(const TimersSizeType idx);

    /**
     * @brief Stop the working timer
     */
    void StopTimer();

    /**
     * @brief Reset a timer
     *
     * @param idx index of the timer
     */
    void ResetTimer(const TimersSizeType idx);

    /**
     * @brief Reset all timer
     */
    void ResetAllTimer();

    /**
     * @brief Edit a time
     *
     * @param idx  index of timer
     * @param time new time
     */
    void EditTime(const TimersSizeType idx,
                  const UnsignedSecondType time);

    /**
     * @brief Move time
     *
     * @param from index of timer taken time
     * @param to   index of timer added time into
     * @param time moved time
     */
    void MoveTime(const TimersSizeType from,
                  const TimersSizeType to,
                  const UnsignedSecondType time);

    /**
     * @brief Add a new timer
     *
     * @param name name of the new timer
     */
    void AddTimer(const char* const name);

    /**
     * @brief Add a new timer
     *
     * @param name name of the new timer
     */
    void EditTimer(const TimersSizeType idx, const char* const name);

    /**
     * @brief Delete the specified timer
     *
     * @param idx index of the item
     */
    void DeleteTimer(const TimersSizeType idx);

    /**
     * @brief   Get the size of categories
     *
     * @return  size of categories
     */
    CategoriesSizeType GetCategorySize() const;

    /**
     * @brief Get the category label
     *
     * @param idx index of the item
     * @return category label
     */
    const char* GetCategoryLabel(const CategoriesSizeType idx) const;

    /**
     * @brief Get the category name
     *
     * @param idx index of the item
     * @return category name
     */
    const char* GetCategoryName(const CategoriesSizeType idx) const;

    /**
     * @brief   Add a Category
     *
     * @param   label   label
     * @param   name    name
     */
    void AddCategory(const char* const label, const char* const name);

    /**
     * @brief   Edit the category specified by its id
     *
     * @param   id        ID
     * @param   label     label
     * @param   name      name
     * @return  return code
     */
    void EditCategory(const CategoriesSizeType idx, const char* const label, const char* const name);

    /**
     * @brief Load from the file
     *
     * @return return code
     */
    ReturnCode Load();

    /**
     * @brief Save into the file
     *
     * @return return code
     */
    ReturnCode Save() const;

    /**
     * @brief Export the time report
     *
     * @return return code
     */
    ReturnCode ExportReport() const;

private:
    class Impl;
    Impl* impl_;
};


/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

#endif // QTA_CORE_API_TIMER_TABLE_H
