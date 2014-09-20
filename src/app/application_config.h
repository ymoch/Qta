/**
 * @file    app/application_config.h
 *
 * @brief   Qta::App::ApplicationConfig class header
 *
 * @author  ymoch
 */

#ifndef QTA_APP_APPLICATION_CONFIG_H
#define QTA_APP_APPLICATION_CONFIG_H

#include "../externals/serialization/archive.h"
#include "../gui/gui_config.h"

namespace Qta
{

namespace App
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Application config
 */
class ApplicationConfig
{
    SERIALIZE_ARCHIVE_FRIEND

public:
    /**
     * @brief Default constructor
     */
    ApplicationConfig();

    /**
     * @brief Clear
     */
    void Clear();

    /**
     * @brief Get the pointer to the GUI config
     *
     * @return pointer to the GUI config
     */
    Gui::GuiConfig* GuiConfig()
    {
        return const_cast<Gui::GuiConfig*>(static_cast<const ApplicationConfig&>(*this).GuiConfig());
    }
    const Gui::GuiConfig* GuiConfig() const { return &gui_config_; }

private:
    Gui::GuiConfig gui_config_;
};

/* End of namespace Qta::App */
}
/* End of namespace Qta */
}

/*==============================================================================
 * Declarations of serialization
 *============================================================================*/

template <> void Serialization::IArchive::Load(Qta::App::ApplicationConfig& conf);
template <> void Serialization::OArchive::Save(const Qta::App::ApplicationConfig& conf);

#endif // QTA_APP_APPLICATION_CONFIG_H
