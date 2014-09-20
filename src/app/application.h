/**
 * @file    app/application.h
 *
 * @brief   Qta::App::Application class header
 *
 * @author  ymoch
 */

#ifndef QTA_APP_APPLICATION_H
#define QTA_APP_APPLICATION_H

#include <vector>
#include <QApplication>
#include "../core/api/timer_table.h"
#include "../gui/main_dialog.h"
#include "application_config.h"

namespace Qta
{

namespace App
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Application
 */
class Application
{
public:
    /**
     * @brief Return code
     */
    enum ReturnCode {
        kReturnCodeOK,
        kReturnCodeNotice,
        kReturnCodeFatalError,
        kReturnCodeOther,
    };

    /**
     * @brief Application
     *
     * @param argc
     * @param argv
     */
    Application(int argc, char** argv);

    /**
     * @brief execute this application
     *
     * @return return code
     */
    int exec();

    /**
     * @brief Get the pointer to the config
     *
     * @return pointer to the config
     */
    ApplicationConfig* Config() {
        return const_cast<ApplicationConfig*>(static_cast<const Application&>(*this).Config());
    }
    const ApplicationConfig* Config() const { return &config_; }

private:
    QApplication app_;              /**< Qt Application */
    Core::TimerTable timer_table_;  /**< timer table */
    ApplicationConfig config_;      /**< config */

    ReturnCode Initialize();
    ReturnCode Finalize();

    ReturnCode LoadConfig();
    ReturnCode LoadTimerTable();
    ReturnCode SaveConfig();
};

/* End of namespace Qta::App */
}
/* End of namespace Qta */
}

#endif // QTA_APP_APPLICATION_H
