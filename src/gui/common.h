/**
 * @file    gui/common.h
 *
 * @brief   Qta GUI common functions header
 *
 * @author  ymoch
 */

#ifndef QTA_GUI_COMMON_H
#define QTA_GUI_COMMON_H

#include <string>
#include <QWidget>
#include <QTime>
#include "../core/api/typedef.h"

namespace Qta
{
namespace Gui
{
namespace Common
{

/*==============================================================================
 * Declarations of global functions
 *============================================================================*/

void Alert(QWidget* parent, const char* const message);
void Alert(QWidget* parent, const std::string& message);

bool Confirm(QWidget* parent, const char* const message);
bool Confirm(QWidget* parent, const std::string& message);

Core::UnsignedSecondType ToSecond(const QTime& time);
QTime ToQTime(const Core::UnsignedSecondType);
QString ToQTimeString(const Core::UnsignedSecondType);


/* End of namespace Qta::Gui::Common */
}
/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}

#endif // QTA_GUI_COMMON_H
