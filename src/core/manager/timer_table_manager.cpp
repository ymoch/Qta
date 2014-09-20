/**
 * @file    core/manager/timer_table_manager.cpp
 *
 * @brief   Qta::Core::TimerTableManager class implementation
 *
 * @author  ymoch
 */

#include <fstream>
#include "../timer/timer_item.h"
#include "timer_table_manager.h"

using std::string;

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

TimerTableManager::TimerTableManager()
{
    Clear();
}

void TimerTableManager::Clear()
{
    items_.clear();
    working_item_index_ = kInvalidSize;
    last_working_item_index_ = kInvalidSize;
    item_id_maker_.Clear();
}

const std::string& TimerTableManager::GetNameConstRef(const ItemsSizeType idx) const
{
    return items_[idx].GetNameConstRef();
}

UnsignedSecondType TimerTableManager::GetCurrentTime(const ItemsSizeType idx) const
{
    return items_[idx].GetCurrentTime();
}

UnsignedSecondType TimerTableManager::GetLastCountedTime(const ItemsSizeType idx) const
{
    return items_[idx].GetLastCountedTime();
}

IdType TimerTableManager::GetCategoryId(const ItemsSizeType idx) const
{
    return items_[idx].GetCategoryId();
}

void TimerTableManager::SetCategoryId(const ItemsSizeType idx, IdType id)
{
    items_[idx].SetCategoryId(id);
}

void TimerTableManager::SwitchTimer(ItemsSizeType index)
{
    StopTimer();
    working_item_index_ = index;
    items_[working_item_index_].Start();
}

void TimerTableManager::StopTimer()
{
    if (IsWorkingItemExists()) {
        last_working_item_index_ = working_item_index_;
        TimerItem& working_item = items_[working_item_index_];
        working_item.Stop();
    }
    working_item_index_ = kInvalidSize;
}

void TimerTableManager::ResetTimer(const ItemsSizeType idx)
{
    if (idx == working_item_index_) {
        working_item_index_ = kInvalidSize;
    }
    items_[idx].Reset();
}

void TimerTableManager::ResetAllTimer()
{
    working_item_index_ = kInvalidSize;
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        it->Reset();
    }
}

void TimerTableManager::EditTime(const ItemsSizeType idx,
                               const UnsignedSecondType time)
{
    TimerItem& item = items_[idx];
    item.timer_.SetTimeSecond(time);
}

void TimerTableManager::MoveTime(const ItemsSizeType from, const ItemsSizeType to,
                               const UnsignedSecondType time)
{
    TimerItem& item_from = items_[from];
    TimerItem& item_to = items_[to];

    const UnsignedSecondType moved_time = item_from.timer_.DecreaseLastCountedTime(time);
    item_to.timer_.AddCurrentTime(moved_time);
}

void TimerTableManager::AddTimer(const std::string& name)
{
    items_.emplace_back(static_cast<IdType>(item_id_maker_.Create()), name);
}

void TimerTableManager::EditTimer(const ItemsSizeType idx, const std::string& name)
{
    TimerItem& item = items_[idx];
    item.SetName(name);
}

void TimerTableManager::DeleteTimer(const ItemsSizeType idx)
{
    items_.erase(items_.begin() + idx);

    working_item_index_ = kInvalidSize;
    for (ItemsSizeType idx = 0; idx < items_.size(); ++idx) {
        if (items_[idx].IsWorking()) {
            working_item_index_ = idx;
            break;
        }
    }
}

/* End of namespace Qta::Core */
}

/* End of namespace Qta */
}

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <>
void Serialization::IArchive::Load(Qta::Core::TimerTableManager& model)
{
    *this >> model.items_
          >> model.last_working_item_index_
          >> model.item_id_maker_;
}

template <>
void Serialization::OArchive::Save(const Qta::Core::TimerTableManager& model)
{
    *this << model.items_;

    if (model.IsWorkingItemExists()) {
        *this << model.working_item_index_;
    } else {
        *this << model.last_working_item_index_;
    }

    *this << model.item_id_maker_;
}

