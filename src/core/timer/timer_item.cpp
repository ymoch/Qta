/**
 * @file    core/timer/timer_item.cpp
 *
 * @brief   Qta::Core::TimerItem class implementation
 *
 * @author  ymoch
 */

#include "timer_item.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

TimerItem::TimerItem()
    : id_(0)
    , name_()
    , timer_()
{}

TimerItem::TimerItem(const IdType id, const std::string& name)
    : id_(id)
    , name_(name)
    , timer_()
{}

void TimerItem::Start()
{
    timer_.Start();
}

void TimerItem::Stop()
{
    timer_.Stop();
}

void TimerItem::Reset()
{
    timer_.Clear();
}

UnsignedSecondType TimerItem::GetCurrentTime() const
{
    return timer_.GetCurrentTime();
}

UnsignedSecondType TimerItem::GetLastCountedTime() const
{
    return timer_.GetLastCountedTime();
}

/* End of namespace Qta::Core */
}

/* End of namespace Qta */
}

/*==============================================================================
 * Defenitions of serialization
 *============================================================================*/

template <>
void Serialization::IArchive::Load(Qta::Core::TimerItem& item)
{
    *this >> item.id_
          >> item.category_id_
          >> item.name_
          >> item.timer_;
}

template <>
void Serialization::OArchive::Save(const Qta::Core::TimerItem& item)
{
    *this << item.id_
          << item.category_id_
          << item.name_
          << item.timer_;
}

