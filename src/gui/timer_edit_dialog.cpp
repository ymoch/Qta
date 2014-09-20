/**
 * @file    gui/timer_edit_dialog.cpp
 *
 * @brief   Qta::Gui::TimerEditDialog class implementation
 *
 * @author  ymoch
 */

#include "common.h"
#include "timer_edit_dialog.h"
#include "ui_timer_edit_dialog.h"

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

TimerEditDialog::TimerEditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TimerEditDialog)
{
    ui->setupUi(this);
}

TimerEditDialog::TimerEditDialog(QWidget* parent, const char* const name)
    : QDialog(parent)
    , ui(new Ui::TimerEditDialog)
{
    ui->setupUi(this);
    ui->nameEdit->setText(name);
}

TimerEditDialog::~TimerEditDialog()
{
    delete ui;
}

std::string TimerEditDialog::GetName() const
{
    return ui->nameEdit->text().toStdString();
}

void TimerEditDialog::accept()
{
    /* Validate input */
    if (ui->nameEdit->text().isEmpty()) {
        Common::Alert(this, "The name is empty!");
        return;
    }
    QDialog::accept();
}

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}
