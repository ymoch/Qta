/**
 * @file    gui/gui_config.cpp
 *
 * @brief   Qta::Gui::GuiConfig class implementation
 *
 * @author  ymoch
 */

#include "gui_config.h"

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of static member variables
 *============================================================================*/

const unsigned GuiConfig::kDefaultUpdateTimeIntervalMillisec = 1000;
const unsigned GuiConfig::kDefaultAutoSaveIntervalMillisec = 1000 * 60 * 5;
const bool GuiConfig::kDefaultConfirmBeforeResetTime = true;
const bool GuiConfig::kDefaultConfirmBeforeResetTimeAll = true;
const bool GuiConfig::kDefaultConfirmDeleteTimer = true;

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

GuiConfig::GuiConfig()
{
    Clear();
}

void GuiConfig::Clear()
{
    update_time_interval_millisec_ = kDefaultUpdateTimeIntervalMillisec;
    auto_save_interval_millisec_ = kDefaultAutoSaveIntervalMillisec;
    confirm_before_reset_time_ = kDefaultConfirmBeforeResetTime;
    confirm_before_reset_time_all_ = kDefaultConfirmBeforeResetTimeAll;
    confirm_before_delete_timer_ = kDefaultConfirmDeleteTimer;
}

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <>
void Serialization::IArchive::Load(Qta::Gui::GuiConfig& conf)
{
    *this >> conf.update_time_interval_millisec_
          >> conf.auto_save_interval_millisec_
          >> conf.confirm_before_reset_time_
          >> conf.confirm_before_reset_time_all_
          >> conf.confirm_before_delete_timer_;
}

template <>
void Serialization::OArchive::Save(const Qta::Gui::GuiConfig& conf)
{
    *this << conf.update_time_interval_millisec_
          << conf.auto_save_interval_millisec_
          << conf.confirm_before_reset_time_
          << conf.confirm_before_reset_time_all_
          << conf.confirm_before_delete_timer_;
}

