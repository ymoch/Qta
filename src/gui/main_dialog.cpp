/**
 * @file    gui/main_dialog.cpp
 *
 * @brief   Qta::Gui::MainDialog class implementation
 *
 * @author  ymoch
 */

#include <memory>
#include <sstream>
#include <QMutexLocker>
#include "../app/application_config.h"
#include "common.h"
#include "ui_main_dialog.h"
#include "main_dialog.h"
#include "control_edit_time_dialog.h"
#include "control_inherit_time_dialog.h"
#include "timer_edit_dialog.h"

using std::string;
using std::unique_ptr;

namespace Qta
{
namespace Gui
{

/*==============================================================================
 * Defenitions of local enumerated types
 *============================================================================*/

/**
 * @brief Timer table index
 */
enum TimerTableIndex {
    TIMER_TABLE_INDEX_TIME = 0,
    TIMER_TABLE_INDEX_NAME,
    TIMER_TABLE_INDEX_NUM,
};

/*==============================================================================
 * Defenitions of local functions
 *============================================================================*/

/**
 * @brief Covert a index to a size type value
 *
 * @param idx index value
 * @return converted index value
 */
template <typename T>
static inline Core::TimerTable::TimersSizeType ConvertIndex(const T &idx)
{
    return static_cast<Core::TimerTable::TimersSizeType>(idx);
}

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

MainDialog::MainDialog(
        QWidget *parent,
        App::ApplicationConfig* conf,
        Core::TimerTable* timer_table)
    : QWidget(parent)
    , ui(new Ui::MainDialog)
    , config_(conf)
    , timer_table_(timer_table)
    , timer_for_update_(this)
    , timer_for_autosave_(this)
    , timer_table_modify_mutex_()
{
    ui->setupUi(this);

    InitializeTimerTable();
    connect(&timer_for_update_, SIGNAL(timeout()), this, SLOT(UpdateEverySecond()));
    connect(&timer_for_autosave_, SIGNAL(timeout()), this, SLOT(AutoSave()));
    timer_for_autosave_.start(config_->GuiConfig()->GetAutoSaveIntervalMillisec());
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::InitializeTimerTable()
{
    ui->timerTable->clear();

    const Core::TimerTable::TimersSizeType timer_table_size = timer_table_->GetSize();

    ui->timerTable->setColumnCount(TIMER_TABLE_INDEX_NUM);
    ui->timerTable->setColumnWidth(TIMER_TABLE_INDEX_TIME, 70);
    ui->timerTable->setColumnWidth(TIMER_TABLE_INDEX_NAME, 240);
    ui->timerTable->setRowCount(static_cast<int>(timer_table_size));

    for (Core::TimerTable::TimersSizeType idx = 0; idx < timer_table_size; ++idx) {
        const int row = static_cast<int>(idx);
        ui->timerTable->setItem(
                    row,
                    TIMER_TABLE_INDEX_TIME,
                    new QTableWidgetItem(Common::ToQTimeString(timer_table_->GetCurrentTime(idx))));
        ui->timerTable->setItem(
                    row,
                    TIMER_TABLE_INDEX_NAME,
                    new QTableWidgetItem(timer_table_->GetName(idx)));
    }
}

void MainDialog::RefreshTime(const int row)
{
    const Core::TimerTable::TimersSizeType idx = ConvertIndex(row);
    ui->timerTable->item(idx, TIMER_TABLE_INDEX_TIME)
            ->setText(Common::ToQTimeString(timer_table_->GetCurrentTime(idx)));
}

void MainDialog::RefreshTimeAll()
{
    const int size = ui->timerTable->rowCount();
    for (int idx = 0; idx < size; ++idx) {
        RefreshTime(idx);
    }
}

void MainDialog::UpdateTime()
{
    if (!timer_table_->IsWorkingItemExists()) {
        return;
    }
    RefreshTime(static_cast<int>(timer_table_->GetWorkingItemIndex()));
}

void MainDialog::SwitchTimer(const int idx)
{
    timer_for_update_.stop();

    timer_table_->SwitchTimer(ConvertIndex(idx));
    UpdateTime();
    ui->controlStartStopButton->setText("Stop");

    timer_for_update_.start(config_->GuiConfig()->GetUpdateTimeIntervalMillisec());
}

void MainDialog::StopTimer()
{
    timer_table_->StopTimer();
    ui->controlStartStopButton->setText("Start");
}

int MainDialog::FindSelectedTimeTableRowIndex() const
{
    const QList<QTableWidgetItem*>& items = ui->timerTable->selectedItems();
    const int num_selected_row = items.size() / TIMER_TABLE_INDEX_NUM;
    if (num_selected_row != 1) {
        /* assert == 0 */
        return -1;
    }
    return items[0]->row();
}

/*==============================================================================
 * Defenitions of member slots
 *============================================================================*/

void MainDialog::closeEvent(QCloseEvent* event)
{
    Core::ReturnCode rc = timer_table_->Save();
    if (rc != Core::kReturnCodeOK) {
        Common::Alert(this, "Failed to save");
    }
    QWidget::closeEvent(event);
}

void MainDialog::UpdateEverySecond()
{
    /* Lock for thread */
    QMutexLocker locker(&timer_table_modify_mutex_);
    UpdateTime();
}

void MainDialog::AutoSave()
{
    /* Lock for thread */
    QMutexLocker locker(&timer_table_modify_mutex_);
    timer_table_->Save();
}

void MainDialog::on_timerTable_doubleClicked(const QModelIndex &index)
{
    if (timer_table_->GetWorkingItemIndex() == ConvertIndex(index.row())) {
        StopTimer();
        return;
    }
    SwitchTimer(index.row());
}

void MainDialog::on_controlStartStopButton_clicked()
{
    /* Timer is working */
    if (timer_table_->IsWorkingItemExists()) {
        StopTimer();
        return;
    }

    /* Timer is not working */
    const int row = FindSelectedTimeTableRowIndex();
    if (row == -1) {
        Common::Alert(this, "No Timer Selected!");
        return;
    }
    SwitchTimer(row);
}


void MainDialog::on_controlResetButtomn_clicked()
{
    const int row = FindSelectedTimeTableRowIndex();
    if (row == -1) {
        Common::Alert(this, "No Timer Selected!");
        return;
    }
    const Core::TimerTable::TimersSizeType idx = ConvertIndex(row);

    if (config_->GuiConfig()->GetConfirmBeforeResetTime()) {
        std::ostringstream os;
        os << "Are you sure to reset the timer? : "
           << timer_table_->GetName(idx);
        const bool confirm = Common::Confirm(this, os.str());
        if (!confirm) {
            return;
        }
    }
    timer_table_->ResetTimer(ConvertIndex(idx));
    RefreshTime(row);
}

void MainDialog::on_controlResetAllButton_clicked()
{
    if (config_->GuiConfig()->GetConfirmBeforeResetTimeAll()) {
        const bool confirm = Common::Confirm(this, "Are you sure to reset all the timers?");
        if (!confirm) {
            return;
        }
    }
    StopTimer();
    timer_table_->ResetAllTimer();
    RefreshTimeAll();
}


void MainDialog::on_controlEditTimeButton_clicked()
{
    const int row = FindSelectedTimeTableRowIndex();
    if (row == -1) {
        Common::Alert(this, "No Timer Selected!");
        return;
    }

    const Core::TimerTable::TimersSizeType idx = ConvertIndex(row);
    if (timer_table_->IsLastWorkingItemExists() && idx == timer_table_->GetWorkingItemIndex()) {
        StopTimer();
    }

    ControlEditTimeDialog modal_dialog(timer_table_->GetCurrentTime(idx), this);
    if (modal_dialog.exec() != QDialog::Accepted) {
        return;
    }
    timer_table_->EditTime(idx, modal_dialog.Time());
    RefreshTime(row);
}

void MainDialog::on_controlMoveTimeButton_clicked()
{
    if (!timer_table_->IsLastWorkingItemExists()) {
        Common::Alert(this, "No timer worked last time!");
        return;
    }

    /* Decide the row index */
    const int row = FindSelectedTimeTableRowIndex();
    if (row == -1) {
        Common::Alert(this, "No timer selected!");
        return;
    }

    const Core::TimerTable::TimersSizeType last_timer_idx = timer_table_->GetLastWorkingItemIndex();
    if (static_cast<int>(last_timer_idx) == row) {
        Common::Alert(this, "The selected timer and the last timer is the same!");
        return;
    }

    const Core::UnsignedSecondType last_counted_time = timer_table_->GetLastCountedTime(last_timer_idx);
    if (last_counted_time == 0) {
        Common::Alert(this, "The last counted time is zero!");
        return;
    }
    ControlInheritTimeDialog modal_dialog(
                this,
                timer_table_->GetName(last_timer_idx),
                last_counted_time);
    if (modal_dialog.exec() != QDialog::Accepted) {
        return;
    }
    timer_table_->MoveTime(last_timer_idx, ConvertIndex(row), modal_dialog.GetMoveTimeSecond());
    RefreshTimeAll();
}


void MainDialog::on_timerExportReportButton_clicked()
{
    const Core::ReturnCode rc = timer_table_->ExportReport();
    if (rc != Core::kReturnCodeOK) {
        Common::Alert(this, "Failed to exporting the report!");
        return;
    }
    Common::Alert(this, "Report exported!");

}

void MainDialog::on_timerAddButton_clicked()
{
    TimerEditDialog modal_dialog(this);
    if (modal_dialog.exec() != QDialog::Accepted) {
        return;
    }

    QMutexLocker locker(&timer_table_modify_mutex_);
    timer_table_->AddTimer(modal_dialog.GetName().c_str());
    InitializeTimerTable();
}

void MainDialog::on_timerEditButton_clicked()
{
    /* Decide the row index */
    const int row = FindSelectedTimeTableRowIndex();
    if (row == -1) {
        Common::Alert(this, "No timer selected!");
        return;
    }
    const Core::TimerTable::TimersSizeType idx = ConvertIndex(row);

    /* Edit */
    TimerEditDialog modal_dialog(this, timer_table_->GetName(idx));
    if (modal_dialog.exec() != QDialog::Accepted) {
        return;
    }

    QMutexLocker locker(&timer_table_modify_mutex_);
    timer_table_->EditTimer(idx, modal_dialog.GetName().c_str());
    InitializeTimerTable();
}

void MainDialog::on_timerDeleteButton_clicked()
{
    const int row = FindSelectedTimeTableRowIndex();
    if (row == -1) {
        Common::Alert(this, "No timer selected!");
        return;
    }
    if (config_->GuiConfig()->GetConfirmBeforeDeleteTimer()) {
        const bool confirm = Common::Confirm(this, "Are you sure to delete the timer?");
        if (!confirm) {
            return;
        }
    }
    QMutexLocker locker(&timer_table_modify_mutex_);
    timer_table_->DeleteTimer(row);
    if (!timer_table_->IsWorkingItemExists()) {
        StopTimer();
    }
    InitializeTimerTable();
}

/* End of namespace Qta::Gui */
}
/* End of namespace Qta */
}
