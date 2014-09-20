/**
 * @file    core/api/timer_table.cpp
 *
 * @brief   Qta core API Qta::Core::TimerTable class implementation
 *
 * @author  ymoch
 */

#include <fstream>
#include "../../externals/time_util/formatted_time.h"
#include "../manager/timer_table_manager.h"
#include "../manager/category_manager.h"
#include "version.h"
#include "timer_table.h"
#include "timer_table_config.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of local functions
 *============================================================================*/

/**
 * @brief Create the erial version
 *
 * @return Serial version
 */
static Serialization::SerialVersionType SerialVersion()
{
    static const Serialization::SerialVersionType version =
                (kMajorVersion << 22) | (kMinorVersion << 12) | kSourceVersion;
    return version;
}

/*==============================================================================
 * Defenitions of implementation classes
 *============================================================================*/

class TimerTable::Impl
{
public:
    Impl();
    Impl(const Impl&);
    ~Impl();

    friend class TimerTable;
private:
    Core::TimerTableManager timer_table_manager_;
    Core::CategoryManager category_manager_;
    TimerTableConfig config_;
};

/*==============================================================================
 * Defenitions of member functions of implementation classes
 *============================================================================*/

TimerTable::Impl::Impl()
    : timer_table_manager_()
    , category_manager_()
    , config_()
{}

TimerTable::Impl::Impl(const Impl& obj)
    : timer_table_manager_(obj.timer_table_manager_)
    , category_manager_(obj.category_manager_)
    , config_(obj.config_)
{}

TimerTable::Impl::~Impl()
{}

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

TimerTable::TimerTable()
    : impl_(new Impl())
{}

TimerTable::TimerTable(const TimerTable& obj)
    : impl_(new Impl(*obj.impl_))
{}

TimerTable::~TimerTable()
{
    delete impl_;
}

void TimerTable::ClearTimers()
{
    impl_->timer_table_manager_.Clear();
}

void TimerTable::ClearCategories()
{
    impl_->category_manager_.Clear();
}

TimerTableConfig* TimerTable::Config()
{
    return const_cast<TimerTableConfig*>(static_cast<const TimerTable&>(*this).Config());
}

const TimerTableConfig* TimerTable::Config() const
{
    return &impl_->config_;
}

TimerTable::TimersSizeType TimerTable::GetSize() const
{
    return static_cast<TimersSizeType>(impl_->timer_table_manager_.GetSize());
}

bool TimerTable::IsWorkingItemExists() const
{
    return impl_->timer_table_manager_.IsWorkingItemExists();
}

TimerTable::TimersSizeType TimerTable::GetWorkingItemIndex() const
{
    return static_cast<TimersSizeType>(impl_->timer_table_manager_.GetWorkingItemIndex());
}

bool TimerTable::IsLastWorkingItemExists() const
{
    return impl_->timer_table_manager_.IsLastWorkingItemExists();
}

TimerTable::TimersSizeType TimerTable::GetLastWorkingItemIndex() const
{
   return static_cast<TimersSizeType>(impl_->timer_table_manager_.GetLastWorkingItemIndex());
}

const char* TimerTable::GetName(const TimersSizeType idx) const
{
    return impl_->timer_table_manager_.GetNameConstRef(idx).c_str();
}

UnsignedSecondType TimerTable::GetCurrentTime(const TimersSizeType idx) const
{
    return impl_->timer_table_manager_.GetCurrentTime(idx);
}

UnsignedSecondType TimerTable::GetLastCountedTime(const TimersSizeType idx) const
{
    return impl_->timer_table_manager_.GetLastCountedTime(idx);
}

void TimerTable::SetCategoryToTimer(
        const CategoriesSizeType category_idx,
        const TimersSizeType timer_idx)
{
    const IdType category_id = impl_->category_manager_.GetId(category_idx);
    impl_->timer_table_manager_.SetCategoryId(timer_idx, category_id);
}

void TimerTable::SwitchTimer(const TimersSizeType idx)
{
    impl_->timer_table_manager_.SwitchTimer(idx);
}

void TimerTable::StopTimer()
{
    impl_->timer_table_manager_.StopTimer();
}

void TimerTable::ResetTimer(const TimersSizeType idx)
{
    impl_->timer_table_manager_.ResetTimer(idx);
}

void TimerTable::ResetAllTimer()
{
    impl_->timer_table_manager_.ResetAllTimer();
}

void TimerTable::EditTime(const TimersSizeType idx, const UnsignedSecondType time)
{
    impl_->timer_table_manager_.EditTime(idx, time);
}

void TimerTable::MoveTime(const TimersSizeType from,
              const TimersSizeType to,
              const UnsignedSecondType time)
{
    impl_->timer_table_manager_.MoveTime(from, to, time);
}

void TimerTable::AddTimer(const char* const name)
{
    impl_->timer_table_manager_.AddTimer(name);
}

void TimerTable::EditTimer(const TimersSizeType idx, const char* const name)
{
    impl_->timer_table_manager_.EditTimer(idx, name);
}

void TimerTable::DeleteTimer(const TimersSizeType idx)
{
    impl_->timer_table_manager_.DeleteTimer(idx);
}

TimerTable::CategoriesSizeType TimerTable::GetCategorySize() const
{
    return impl_->category_manager_.GetSize();
}

const char* TimerTable::GetCategoryLabel(const CategoriesSizeType idx) const
{
    return impl_->category_manager_.GetLabelConstRefByIndex(idx).c_str();
}

const char* TimerTable::GetCategoryName(const CategoriesSizeType idx) const
{
    return impl_->category_manager_.GetNameConstRefByIndex(idx).c_str();
}

void TimerTable::AddCategory(const char* const label, const char* const name)
{
    impl_->category_manager_.AddCategory(label, name);
}

void TimerTable::EditCategory(const CategoriesSizeType idx, const char* const label, const char* const name)
{
    return impl_->category_manager_.EditCategoryByIndex(idx, label, name);
}

ReturnCode TimerTable::Load()
{
    std::ifstream ifs(impl_->config_.GetSaveFileName(), std::ios::binary);
    if (!ifs) {
        return kReturnCodeFileOpenFailed;
    }

    Serialization::IArchive iarchive(ifs);
    if (iarchive.GetVersion() != SerialVersion()) {
        return kReturnCodeFileReadFailed;
    }

    iarchive >> impl_->timer_table_manager_
             >> impl_->category_manager_;
    if (ifs.fail()) {
        return kReturnCodeFileReadFailed;
    }
    return kReturnCodeOK;
}

ReturnCode TimerTable::Save() const
{
    std::ofstream ofs(Config()->GetSaveFileName(), std::ios::binary);
    if (!ofs) {
        return kReturnCodeFileOpenFailed;
    }

    Serialization::OArchive oarchive(ofs, SerialVersion());
    oarchive << impl_->timer_table_manager_
             << impl_->category_manager_;
    if (ofs.fail()) {
        return kReturnCodeFileWriteFailed;
    }
    return kReturnCodeOK;
}

ReturnCode TimerTable::ExportReport() const
{
    std::ofstream ofs(Config()->GetReportFileName(), std::ios::app);
    if (!ofs) {
        return kReturnCodeFileOpenFailed;
    }

    TimerTableManager::ItemsSizeType size = impl_->timer_table_manager_.GetSize();
    for (TimerTableManager::ItemsSizeType idx = 0; idx < size; ++idx) {
        ofs << TimeUtil::FormattedTime::FromSecond(
                   impl_->timer_table_manager_.GetCurrentTime(idx)).ToString()
            << '\t'
            << impl_->timer_table_manager_.GetNameConstRef(idx)
            << '\n';
    }
    ofs << "\n-----\n\n";

    if (ofs.fail()) {
        return kReturnCodeFileWriteFailed;
    }
    return kReturnCodeOK;
}


/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}
