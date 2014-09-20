/**
 * @file    gui/timer_edit_dialog.h
 *
 * @brief   Qta::Gui::TimerEditDialog class header
 *
 * @author  ymoch
 */

#ifndef QTA_GUI_TIMER_EDIT_DIALOG_H
#define QTA_GUI_TIMER_EDIT_DIALOG_H

#include <QDialog>

namespace Ui {
class TimerEditDialog;
}

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief Dialog to edit timer
 */
class TimerEditDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor
     * @param pointer to the parent widget
     */
    explicit TimerEditDialog(QWidget *parent);

    /**
     * @brief Constructor
     * @param pointer to the parent widget
     */
    TimerEditDialog(QWidget *parent, const char* const name);

    /**
     * @brief Destructor
     */
    ~TimerEditDialog();

    /**
     * @brief Get the timer name
     *
     * @return timer name
     */
    std::string GetName() const;

    /**
     * @see QDialog::accept()
     */
    virtual void accept();

private:
    Ui::TimerEditDialog *ui;    /**< UI */
};

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}

#endif // QTA_GUI_TIMER_EDIT_DIALOG_H
