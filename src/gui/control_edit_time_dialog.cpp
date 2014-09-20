/**
 * @file    gui/control_edit_time_dialog.cpp
 *
 * @brief   Qta::Gui::ControlEditTimeDialog class implementation
 *
 * @author  ymoch
 */

#include "common.h"
#include "control_edit_time_dialog.h"
#include "ui_control_edit_time_dialog.h"

namespace Qta
{

namespace Gui
{

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

ControlEditTimeDialog::ControlEditTimeDialog(
        const Core::UnsignedSecondType time, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ControlEditTimeDialog)
{
    ui->setupUi(this);
    ui->timeEdit->setTime(Common::ToQTime(time));
    ui->timeEdit->update();
}

ControlEditTimeDialog::~ControlEditTimeDialog()
{
    delete ui;
}

Core::UnsignedSecondType ControlEditTimeDialog::Time() const
{
    const QTime time = ui->timeEdit->time();
    return Common::ToSecond(time);
}

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}
