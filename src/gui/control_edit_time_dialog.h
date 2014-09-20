/**
 * @file    gui/control_edit_time_dialog.h
 *
 * @brief   Qta::Gui::ControlEditTimeDialog class header
 *
 * @author  ymoch
 */

#ifndef QTA_GUI_CONTROL_EDIT_TIME_DIALOG_H
#define QTA_GUI_CONTROL_EDIT_TIME_DIALOG_H

#include <QTime>
#include <QDialog>
#include "../core/api/typedef.h"

namespace Ui {
class ControlEditTimeDialog;
}

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

class ControlEditTimeDialog : public QDialog
{
    Q_OBJECT

public:
    ControlEditTimeDialog(
            const Core::UnsignedSecondType time, QWidget *parent);
    ~ControlEditTimeDialog();

    Core::UnsignedSecondType Time() const;

private:
    Ui::ControlEditTimeDialog *ui;
};

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}

#endif // QTA_GUI_CONTROL_EDIT_TIME_DIALOG_H
