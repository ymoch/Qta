/**
 * @file    gui/gui_config.h
 *
 * @brief   Qta::Gui::GuiConfig class header
 *
 * @author  ymoch
 */

#ifndef QTA_GUI_GUI_CONFIG_H
#define QTA_GUI_GUI_CONFIG_H

#include "../externals/serialization/archive.h"

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief GUI config
 */
class GuiConfig
{
    SERIALIZE_ARCHIVE_FRIEND
public:
    /**
     * @brief Default constructor
     */
    GuiConfig();

    /**
     * @brief Clear
     */
    void Clear();

    unsigned GetUpdateTimeIntervalMillisec() const { return update_time_interval_millisec_; }
    unsigned GetAutoSaveIntervalMillisec() const { return auto_save_interval_millisec_; }
    bool GetConfirmBeforeResetTime() const { return confirm_before_reset_time_; }
    bool GetConfirmBeforeResetTimeAll() const { return confirm_before_reset_time_all_; }
    bool GetConfirmBeforeDeleteTimer() const { return confirm_before_delete_timer_; }

    void SetUpdateTimeIntervalMillisec(const unsigned value) { update_time_interval_millisec_ = value; }
    void SetAutoSaveIntervalMillisec(const unsigned value) { auto_save_interval_millisec_ = value; }
    void SetConfirmBeforeResetTime(const bool flag) { confirm_before_reset_time_ = flag; }
    void SetConfirmBeforeResetTimeAll(const bool flag) { confirm_before_reset_time_all_ = flag; }
    void SetConfirmBeforeDeleteTimer(const bool flag) { confirm_before_delete_timer_ = flag; }

private:
    static const unsigned kDefaultUpdateTimeIntervalMillisec;
    static const unsigned kDefaultAutoSaveIntervalMillisec;
    static const bool kDefaultConfirmBeforeResetTime;
    static const bool kDefaultConfirmBeforeResetTimeAll;
    static const bool kDefaultConfirmDeleteTimer;

    unsigned update_time_interval_millisec_;
    unsigned auto_save_interval_millisec_;
    bool confirm_before_reset_time_;
    bool confirm_before_reset_time_all_;
    bool confirm_before_delete_timer_;
};

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Declarations of serialization
 *============================================================================*/

namespace Serialization
{
template <> void IArchive::Load(Qta::Gui::GuiConfig& conf);
template <> void OArchive::Save(const Qta::Gui::GuiConfig& conf);
}

#endif // QTA_GUI_GUI_CONFIG_H
