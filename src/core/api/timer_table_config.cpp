/**
 * @file    core/api/timer_table_config.cpp
 *
 * @brief   Qta core API Qta::Core::TimerTableConfig class implementation
 *
 * @author  ymoch
 */

#include <string>
#include "timer_table_config.h"

namespace Qta
{
namespace Core
{

/*==============================================================================
 * Defenitions of implementation classes
 *============================================================================*/

/**
 * @brief Implementation of the TimerTableConfig Class
 */
class TimerTableConfig::Impl
{
public:
    Impl();
    Impl(const Impl&);
    ~Impl();

    void Clear();
    friend class TimerTableConfig;
private:
    std::string save_file_name_;
    std::string report_file_name_;
};

/*==============================================================================
 * Defenitions of member functions of implementation classes
 *============================================================================*/

TimerTableConfig::Impl::Impl()
    : save_file_name_()
    , report_file_name_()
{}

TimerTableConfig::Impl::Impl(const Impl& obj)
    : save_file_name_(obj.save_file_name_)
    , report_file_name_(obj.report_file_name_)
{}

TimerTableConfig::Impl::~Impl()
{}

void TimerTableConfig::Impl::Clear()
{
    save_file_name_.clear();
    report_file_name_.clear();
}

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

TimerTableConfig::TimerTableConfig()
    : impl_(new Impl)
{}

TimerTableConfig::TimerTableConfig(const TimerTableConfig& obj)
    : impl_(new Impl(*obj.impl_))
{}

TimerTableConfig::~TimerTableConfig()
{
    delete impl_;
}

void TimerTableConfig::Clear()
{
    impl_->Clear();
}

void TimerTableConfig::SetSaveFileName(const char* const name)
{
    impl_->save_file_name_ = name;
}

const char* TimerTableConfig::GetSaveFileName() const
{
    return impl_->save_file_name_.c_str();
}

void TimerTableConfig::SetReportFileName(const char* const name)
{
    impl_->report_file_name_ = name;
}

const char* TimerTableConfig::GetReportFileName() const
{
    return impl_->report_file_name_.c_str();
}

/* End of namespace Qta::Core */
}
/* End of namespace Qta */
}
