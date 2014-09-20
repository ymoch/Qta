/**
 * @file    gui/control_inherit_time_dialog.h
 *
 * @brief   Qta::Gui::ControlInheritTimeDialog class header
 *
 * @author  ymoch
 */

#ifndef QTA_GUI_CONTROL_MOVE_DIALOG_H
#define QTA_GUI_CONTROL_MOVE_DIALOG_H

#include <string>
#include <QDialog>
#include <QTime>
#include "../core/api/typedef.h"

namespace Ui {
class ControlInheritTimeDialog;
}

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

class ControlInheritTimeDialog : public QDialog
{
    Q_OBJECT

public:
    ControlInheritTimeDialog(
            QWidget *parent,
            const std::string& name,
            const Core::UnsignedSecondType time);

    ~ControlInheritTimeDialog();

    virtual void accept();

    Core::UnsignedSecondType GetMoveTimeSecond() const;

private:
    Ui::ControlInheritTimeDialog *ui;
    QTime last_count_time_;
};

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}

#endif // QTA_GUI_CONTROL_MOVE_DIALOG_H
