/**
 * @file    externals/time_util/formatted_time.cpp
 *
 * @brief   TimeUtil::FormattedTime class implementation
 *
 * @author  ymoch
 */

#include <sstream>
#include <iomanip>
#include "formatted_time.h"

using std::string;
using std::ostringstream;
using std::right;
using std::setw;
using std::setfill;

namespace TimeUtil
{

/*==============================================================================
 * Defenitions of member functions
 *============================================================================*/

FormattedTime::FormattedTime(
        const unsigned hour,
        const unsigned minute,
        const unsigned second)
    : hour_(hour)
    , minute_(minute)
    , second_(second)
{}

FormattedTime FormattedTime::FromHms(const unsigned hour, const unsigned minute, const unsigned second)
{
    return FormattedTime(hour, minute, second);
}

FormattedTime FormattedTime::FromSecond(UnsignedSecondType time)
{
    const UnsignedSecondType second = time;
    const UnsignedSecondType minute = second / 60;
    const UnsignedSecondType hour = minute / 60;
    return FormattedTime(
                static_cast<unsigned>(hour),
                static_cast<unsigned>(minute % 60),
                static_cast<unsigned>(second % 60));
}

const char* FormattedTime::ToString() const
{
    ostringstream os;
    os << hour_
       << ':' << setw(2) << right << setfill('0') << minute_
       << ':' << setw(2) << right << setfill('0') << second_;
    return os.str().c_str();
}

/* End of namespace TimeUtil */
}
