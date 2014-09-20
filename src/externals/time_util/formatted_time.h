/**
 * @file    externals/time_util/formatted_time.h
 *
 * @brief   TimeUtil::FormattedTime class header
 *
 * @author  ymoch
 */

#ifndef TIME_UTIL_FORMATTED_TIME_H
#define TIME_UTIL_FORMATTED_TIME_H

namespace TimeUtil
{

/*==============================================================================
 * Defenitions of classes
 *============================================================================*/

/**
 * @brief The formatted time
 */
class FormattedTime
{
public:
    /**
     * @brief Type for unsigned time to the second
     */
    typedef unsigned long UnsignedSecondType;

    /**
     * @brief Create formatted value
     *
     * @param hour hour value
     * @param minute minute value
     * @param second second value
     */
    static FormattedTime FromHms(const unsigned hour, const unsigned minute, const unsigned second);

    /**
     * @brief Create formatted value from a time expressed in seconds
     *
     * @param time millisecond time
     * @return formatted time
     */
    static FormattedTime FromSecond(const UnsignedSecondType time);

    /**
     * @brief Judge this time is zero
     *
     * @return true if this time is zero else false
     */
    bool IsZero() const { return hour_ == 0 && minute_ == 0 && second_ == 0; }

    /**
     * @brief Get the hour
     */
    unsigned GetHour() const { return hour_; }

    /**
     * @brief Get the minute
     */
    unsigned GetMinute() const { return minute_; }

    /**
     * @brief Get the second
     */
    unsigned GetSecond() const { return second_; }

    /**
     * @brief Create the time expressed in seconds
     *
     * @return time expressed in seconds
     */
    UnsignedSecondType ToSecond() const
    {
        return ((hour_ * 60) + minute_) * 60 + second_;
    }

    /**
     * @brief Create the time expressed in a string
     *
     * @return time expressed in a string
     */
    const char* ToString() const;

private:
    /**
     * @brief Private constructor
     *
     * @param hour hour value
     * @param minute minute value
     * @param second second value
     */
    FormattedTime(
            const unsigned hour,
            const unsigned minute,
            const unsigned second);

    unsigned hour_;     /**< hour */
    unsigned minute_;   /**< minute */
    unsigned second_;   /**< second */
};

/* End of namespace TimeUtil */
}

#endif // TIME_UTIL_FORMATTED_TIME_H
