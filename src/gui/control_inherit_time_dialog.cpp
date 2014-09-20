/**
 * @file    gui/control_inherit_time_dialog.cpp
 *
 * @brief   Qta::Gui::ControlInheritTimeDialog class implementation
 *
 * @author  ymoch
 */

#include "common.h"
#include "control_inherit_time_dialog.h"
#include "ui_control_inherit_time_dialog.h"

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

ControlInheritTimeDialog::ControlInheritTimeDialog(
        QWidget *parent,
        const std::string& name,
        const Core::UnsignedSecondType time)
    : QDialog(parent)
    , ui(new Ui::ControlInheritTimeDialog)
    , last_count_time_(Common::ToQTime(time))
{
    ui->setupUi(this);
    ui->lastTimerNameValue->setText(name.c_str());
    ui->lastTimerTimeValue->setText(Common::ToQTimeString(time));
}

ControlInheritTimeDialog::~ControlInheritTimeDialog()
{
    delete ui;
}

Core::UnsignedSecondType ControlInheritTimeDialog::GetMoveTimeSecond() const
{
    const QTime time = ui->moveTimeEdit->time();
    return Common::ToSecond(time);
}

void ControlInheritTimeDialog::accept()
{
    if (ui->moveTimeEdit->time() > last_count_time_) {
        Common::Alert(this, "Time to move is larget than the last counted time!");
        return;
    }
    QDialog::accept();
}

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}
