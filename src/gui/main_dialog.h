/**
 * @file    gui/main_dialog.h
 *
 * @brief   Qta::Gui::MainDialog class header
 *
 * @author  ymoch
 */

#ifndef QTA_GUI_MAIN_DIALOG_H
#define QTA_GUI_MAIN_DIALOG_H

#include <QWidget>
#include <QTimer>
#include <QMutex>
#include <QAbstractTableModel>
#include "../core/api/timer_table.h"

/* UI Class */
namespace Ui
{
class MainDialog;
}

namespace Qta {

namespace App
{
class ApplicationConfig;
}

namespace Gui
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief The main dialog class
 */
class MainDialog : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param model pointer to a timer table model
     * @param parent pointer to the parent widget
     */
    MainDialog(
            QWidget *parent,
            App::ApplicationConfig* conf,
            Core::TimerTable* timer_table);

    /**
     * @brief Destructor
     */
    ~MainDialog();

private slots:
    void on_timerTable_doubleClicked(const QModelIndex &index);

private:
    Ui::MainDialog *ui;                 /**< Main dialog UI */
    App::ApplicationConfig* config_;    /**< Application config */
    Core::TimerTable* timer_table_;     /**< Timer table model */

    QTimer timer_for_update_;           /**< Timer for updating UI */
    QTimer timer_for_autosave_;         /**< Timer for autosave */
    QMutex timer_table_modify_mutex_;   /**< Mutex */

    /**
     * @brief Initialize the timer table
     */
    void InitializeTimerTable();

    /**
     * @brief Refresh the specified time
     *
     * @param idx index of the timer
     */
    void RefreshTime(const int idx);

    /**
     * @brief Refresh all the times
     */
    void RefreshTimeAll();

    /**
     * @brief Update the timer table
     */
    void UpdateTime();

    /**
     * @brief Switch the working timer
     *
     * @param idx index of the timer
     */
    void SwitchTimer(const int idx);

    /**
     * @brief Stop the working timer
     */
    void StopTimer();

    int FindSelectedTimeTableRowIndex() const;

protected slots:
    virtual void closeEvent(QCloseEvent* event);

private slots:
    /**
     * @brief Update thread on every second
     */
    void UpdateEverySecond();

    /**
     * @brief Automatic saving thread
     */
    void AutoSave();

    /* Events */
    void on_controlStartStopButton_clicked();
    void on_controlResetButtomn_clicked();
    void on_controlResetAllButton_clicked();
    void on_controlMoveTimeButton_clicked();
    void on_controlEditTimeButton_clicked();
    void on_timerAddButton_clicked();
    void on_timerEditButton_clicked();
    void on_timerDeleteButton_clicked();
    void on_timerExportReportButton_clicked();
};

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}

#endif // QTA_GUI_MAIN_DIALOG_H
