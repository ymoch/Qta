/**
 * @file    gui/common.cpp
 *
 * @brief   Qta GUI common functions implementation
 *
 * @author  ymoch
 */

#include <QMessageBox>
#include "../externals/time_util/formatted_time.h"
#include "common.h"

namespace Qta
{
namespace Gui
{
namespace Common
{

/*==============================================================================
 * Defenitions of global functions
 *============================================================================*/

void Alert(QWidget* parent, const char* const message)
{
    QMessageBox message_box(parent);
    message_box.setText(message);
    message_box.exec();
}

void Alert(QWidget* parent, const std::string& message)
{
    Alert(parent, message.c_str());
}

bool Confirm(QWidget* parent, const char* const message)
{
    const QMessageBox::StandardButton reply = QMessageBox::question(
                parent,
                "Confirm",
                message,
                QMessageBox::Ok|QMessageBox::Cancel);
    switch (reply)
    {
    case QMessageBox::Ok:
        return true;
    case QMessageBox::Cancel:
        return false;
    default:
        Alert(parent, "Invalid reply!");
    }
    return false;
}

bool Confirm(QWidget* parent, const std::string& message)
{
    return Confirm(parent, message.c_str());
}

Core::UnsignedSecondType ToSecond(const QTime& time)
{
    return TimeUtil::FormattedTime::FromHms(time.hour(), time.minute(), time.second())
            .ToSecond();
}

QTime ToQTime(const Core::UnsignedSecondType time)
{
    const TimeUtil::FormattedTime formatted_time = TimeUtil::FormattedTime::FromSecond(time);
    return QTime(static_cast<int>(formatted_time.GetHour()),
                 static_cast<int>(formatted_time.GetMinute()),
                 static_cast<int>(formatted_time.GetSecond()));
}

QString ToQTimeString(const Core::UnsignedSecondType time)
{
    return ToQTime(time).toString(Qt::TextDate);
}


/* End of namespace Qta::Gui::Common */
}
/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}
