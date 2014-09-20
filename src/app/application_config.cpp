/**
 * @file    app/application_config.cpp
 *
 * @brief   Qta::App::ApplicationConfig class implementation
 *
 * @author  ymoch
 */

#include "application_config.h"

namespace Qta
{
namespace App
{

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

ApplicationConfig::ApplicationConfig()
    : gui_config_()
{}

void ApplicationConfig::Clear()
{
    gui_config_.Clear();
}

/* End of namespace Qta::App */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <> void Serialization::IArchive::Load(Qta::App::ApplicationConfig& conf)
{
    *this >> conf.gui_config_;
}

template <> void Serialization::OArchive::Save(const Qta::App::ApplicationConfig& conf)
{
    *this << conf.gui_config_;
}

