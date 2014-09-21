/**
 * @file    app/application.cpp
 *
 * @brief   Qta::App::Application class implementation
 *
 * @author  ymoch
 */

#include <fstream>
#include <sstream>
#include "../core/api/timer_table_config.h"
#include "../gui/common.h"
#include "version.h"
#include "application.h"

namespace Qta
{

namespace App
{

/*==============================================================================
 * Defenitions of local constant values
 *============================================================================*/

static const char* const kWindowTitle = "Qta";
static const char* const kConfigFileName = "qta_settings.dat";
static const char* const kTimerTableFileName = "qta_timer_table.dat";
static const char* const kReportFileName = "qta_report.txt";

/*==============================================================================
 * Defenitions of local functions
 *============================================================================*/

static const char* CreateWindowTitle()
{
    std::ostringstream os;
    os << kWindowTitle << " ver."
       << kMajorVersion << '.'
       << kMinorVersion << '.'
       << kSourceVersion;
    return os.str().c_str();
}

/**
 * @brief Create the erial version
 *
 * @return Serial version
 */
static Serialization::SerialVersionType SerialVersion()
{
    static const Serialization::SerialVersionType version =
                (kMajorVersion << 22) | (kMinorVersion << 12) | kSourceVersion;
    return version;
}

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

Application::Application(int argc, char** argv)
    : app_(argc, argv)
    , timer_table_()
    , config_()
{
    timer_table_.Config()->SetSaveFileName(kTimerTableFileName);
    timer_table_.Config()->SetReportFileName(kReportFileName);
}

int Application::exec()
{
    Initialize();

    Gui::MainDialog dialog(0, Config(), &timer_table_);
    dialog.setWindowTitle(CreateWindowTitle());
    dialog.show();
    const int rc = app_.exec();

    Finalize();
    return rc;
}

Application::ReturnCode Application::Initialize()
{
    LoadConfig();
    LoadTimerTable();
    return kReturnCodeOK;
}

Application::ReturnCode Application::Finalize()
{
    SaveConfig();
    return kReturnCodeOK;
}

Application::ReturnCode Application::LoadConfig()
{
    std::ifstream ifs(kConfigFileName, std::ios::binary);
    if (!ifs) {
        Gui::Common::Alert(0, "Unable to load the setting data! Applying the default setting.");
        config_.Clear();
        return kReturnCodeNotice;
    }
    Serialization::IArchive iarchive(ifs);
    if (iarchive.GetVersion() != SerialVersion()) {
        Gui::Common::Alert(0, "Failed to load the setting data! Applying the default setting.");
        config_.Clear();
        return kReturnCodeNotice;
    }

    iarchive >> config_;
    if (ifs.fail()) {
        Gui::Common::Alert(0, "Failed to load the setting data! Applying the default setting.");
        config_.Clear();
        return kReturnCodeNotice;
    }
    return kReturnCodeOK;
}

Application::ReturnCode Application::SaveConfig()
{
    std::ofstream ofs(kConfigFileName, std::ios::binary);
    if (!ofs) {
        Gui::Common::Alert(0, "Unable to save the setting data!");
        return kReturnCodeNotice;
    }
    Serialization::OArchive archive(ofs, SerialVersion());
    archive << config_;
    if (ofs.fail()) {
        Gui::Common::Alert(0, "Failed to save the setting data!");
        return kReturnCodeNotice;
    }
    return kReturnCodeOK;
}

Application::ReturnCode Application::LoadTimerTable()
{
    Core::ReturnCode rc = timer_table_.Load();
    switch (rc) {
    case Core::kReturnCodeOK:
        return kReturnCodeOK;

    case Core::kReturnCodeFileOpenFailed:
    case Core::kReturnCodeFileReadFailed:
        Gui::Common::Alert(0, "Unable to load the saved data! Applying the default setting.");

        timer_table_.ClearTimers();
        timer_table_.ClearCategories();
        timer_table_.AddTimer("Doubleclick to Start!");
        timer_table_.AddTimer("Control timers at the \"Control\" Tab");
        timer_table_.AddTimer("Edit timers at the \"Timer\" Tab");
        return kReturnCodeNotice;

    default:
        return kReturnCodeFatalError;
    }
}

/* End of namespace Qta::App */
}
/* End of namespace Qta */
}
