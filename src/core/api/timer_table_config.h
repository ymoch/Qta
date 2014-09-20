/**
 * @file    core/api/timer_table_config.h
 *
 * @brief   Qta core API Qta::Core::TimerTableConfig class header
 *
 * @author  ymoch
 */

#ifndef QTA_CORE_API_TIMER_TABLE_CONFIG_H
#define QTA_CORE_API_TIMER_TABLE_CONFIG_H

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Configs for timer tables
 */
class TimerTableConfig
{
public:
    /**
     * @brief Default constructor
     */
    TimerTableConfig();

    /**
     * @brief Copy constructor
     */
    TimerTableConfig(const TimerTableConfig&);

    /**
     * @brief Destructor
     */
    ~TimerTableConfig();

    /**
     * @brief Clear
     */
    void Clear();

    /**
     * @brief Set the name of the save file
     *
     * @param name name of the save file
     */
    void SetSaveFileName(const char* const name);

    /**
     * @brief Get the name of the save file
     *
     * @return name of the save file
     */
    const char* GetSaveFileName() const;

    /**
     * @brief Set the name of the save file
     *
     * @param name name of the save file
     */
    void SetReportFileName(const char* const name);

    /**
     * @brief Get the name of the save file
     *
     * @return name of the save file
     */
    const char* GetReportFileName() const;

private:
    class Impl;
    Impl* impl_;
};


/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}

#endif // QTA_CORE_API_TIMER_TABLE_CONFIG_H
