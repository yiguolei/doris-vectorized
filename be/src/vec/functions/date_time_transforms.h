// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "runtime/datetime_value.h"
#include "vec/columns/column_string.h"
#include "vec/columns/column_vector.h"
#include "vec/common/exception.h"
#include "vec/core/types.h"
#include "vec/functions/function_helpers.h"
//#include "vec/functions/extract_time_zone_from_function_arguments.h>

namespace doris::vectorized {

namespace ErrorCodes {
extern const int ILLEGAL_TYPE_OF_ARGUMENT;
extern const int ILLEGAL_COLUMN;
} // namespace ErrorCodes

/** Transformations.
  * Represents two functions - from datetime (UInt32) and from date (UInt16).
  *
  * Also, the "factor transformation" F is defined for the T transformation.
  * This is a transformation of F such that its value identifies the region of monotonicity for T
  *  (for a fixed value of F, the transformation T is monotonic).
  *
  * Or, figuratively, if T is similar to taking the remainder of division, then F is similar to division.
  *
  * Example: for transformation T "get the day number in the month" (2015-02-03 -> 3),
  *  factor-transformation F is "round to the nearest month" (2015-02-03 -> 2015-02-01).
  */

static inline UInt32 dateIsNotSupported(const char* name) {
    throw Exception("Illegal type Date of argument for function " + std::string(name),
                    ErrorCodes::ILLEGAL_TYPE_OF_ARGUMENT);
}

///// This factor transformation will say that the function is monotone everywhere.
//struct ZeroTransform
//{
//    static inline UInt16 execute(UInt32, const DateLUTImpl &) { return 0; }
//    static inline UInt16 execute(UInt16, const DateLUTImpl &) { return 0; }
//};

//struct ToDateImpl
//{
//    static constexpr auto name = "toDate";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return UInt16(time_zone.toDayNum(t));
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl &)
//    {
//        return d;
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfDayImpl
//{
//    static constexpr auto name = "toStartOfDay";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toDate(t);
//    }
//    static inline UInt32 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toDate(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToMondayImpl
//{
//    static constexpr auto name = "toMonday";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfWeek(time_zone.toDayNum(t));
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfWeek(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfMonthImpl
//{
//    static constexpr auto name = "toStartOfMonth";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfMonth(time_zone.toDayNum(t));
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfMonth(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfQuarterImpl
//{
//    static constexpr auto name = "toStartOfQuarter";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfQuarter(time_zone.toDayNum(t));
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfQuarter(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfYearImpl
//{
//    static constexpr auto name = "toStartOfYear";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfYear(time_zone.toDayNum(t));
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toFirstDayNumOfYear(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//
//struct ToTimeImpl
//{
//    static constexpr auto name = "toTime";
//
//    /// When transforming to time, the date will be equated to 1970-01-02.
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toTime(t) + 86400;
//    }
//
//    static inline UInt32 execute(UInt16, const DateLUTImpl &)
//    {
//        return dateIsNotSupported(name);
//    }
//
//    using FactorTransform = ToDateImpl;
//};
//
//struct ToStartOfMinuteImpl
//{
//    static constexpr auto name = "toStartOfMinute";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toStartOfMinute(t);
//    }
//    static inline UInt32 execute(UInt16, const DateLUTImpl &)
//    {
//        return dateIsNotSupported(name);
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfFiveMinuteImpl
//{
//    static constexpr auto name = "toStartOfFiveMinute";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toStartOfFiveMinute(t);
//    }
//    static inline UInt32 execute(UInt16, const DateLUTImpl &)
//    {
//        return dateIsNotSupported(name);
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfTenMinutesImpl
//{
//    static constexpr auto name = "toStartOfTenMinutes";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toStartOfTenMinutes(t);
//    }
//    static inline UInt32 execute(UInt16, const DateLUTImpl &)
//    {
//        return dateIsNotSupported(name);
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfFifteenMinutesImpl
//{
//    static constexpr auto name = "toStartOfFifteenMinutes";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toStartOfFifteenMinutes(t);
//    }
//    static inline UInt32 execute(UInt16, const DateLUTImpl &)
//    {
//        return dateIsNotSupported(name);
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
///// Round to start of half-an-hour length interval with unspecified offset. This transform is specific for Yandex.Metrica.
//struct TimeSlotImpl
//{
//    static constexpr auto name = "timeSlot";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl &)
//    {
//        return t / 1800 * 1800;
//    }
//
//    static inline UInt32 execute(UInt16, const DateLUTImpl &)
//    {
//        return dateIsNotSupported(name);
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToStartOfHourImpl
//{
//    static constexpr auto name = "toStartOfHour";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toStartOfHour(t);
//    }
//
//    static inline UInt32 execute(UInt16, const DateLUTImpl &)
//    {
//        return dateIsNotSupported(name);
//    }
//
//    using FactorTransform = ZeroTransform;
//};

#define TIME_FUNCTION_IMPL(CLASS, UNIT, FUNCTION)                     \
    struct CLASS {                                                    \
        static constexpr auto name = #UNIT;                           \
        static inline auto execute(const Int128& t) {                 \
            const auto& date_time_value = (doris::DateTimeValue&)(t); \
            return date_time_value.FUNCTION;                          \
        }                                                             \
    }

#define TO_TIME_FUNCTION(CLASS, UNIT) TIME_FUNCTION_IMPL(CLASS, UNIT, UNIT())

TO_TIME_FUNCTION(ToYearImpl, year);
TO_TIME_FUNCTION(ToQuarterImpl, quarter);
TO_TIME_FUNCTION(ToMonthImpl, month);
TO_TIME_FUNCTION(ToDayImpl, day);
TO_TIME_FUNCTION(ToHourImpl, hour);
TO_TIME_FUNCTION(ToMinuteImpl, minute);
TO_TIME_FUNCTION(ToSecondImpl, second);

TIME_FUNCTION_IMPL(WeekOfYearImpl, weekofyear, week(mysql_week_mode(3)));
TIME_FUNCTION_IMPL(DayOfYearImpl, dayofyear, day_of_year());
TIME_FUNCTION_IMPL(DayOfMonthImpl, dayofmonth, day());
TIME_FUNCTION_IMPL(DayOfWeekImpl, dayofweek, day_of_week());
TIME_FUNCTION_IMPL(ToDaysImpl, to_days, daynr());

struct ToDateImpl {
    static constexpr auto name = "to_date";

    static inline auto execute(const Int128& t) {
        auto res = t;
        auto& dt = (doris::DateTimeValue&)(res);
        dt.cast_to_date();
        return res;
    }
};
struct DateImpl : public ToDateImpl {
    static constexpr auto name = "date";
};

// TODO: This function look like no need do indeed copy here, we should optimize
// this function
struct TimeStampImpl {
    static constexpr auto name = "timestamp";
    static inline auto execute(const Int128& t) { return t; }
};

struct UnixTimeStampImpl {
    static constexpr auto name = "unix_timestamp";
    static inline int execute(const Int128& t) {
        // TODO: use default time zone, slowly and incorrect, just for test use
        static cctz::time_zone time_zone = cctz::fixed_time_zone(cctz::seconds(8 * 60 * 60));

        const auto& dt = (doris::DateTimeValue&)(t);
        int64_t timestamp = 0;
        dt.unix_timestamp(&timestamp, time_zone);

        return (timestamp < 0 || timestamp > INT_MAX) ? 0 : timestamp;
    }
};

struct DayNameImpl {
    static constexpr auto name = "dayname";
    static constexpr auto max_size = MAX_DAY_NAME_LEN;

    static inline auto execute(const DateTimeValue& dt, ColumnString::Chars& res_data,
                               size_t& offset) {
        const auto* day_name = dt.day_name();
        if (day_name == nullptr) {
            offset += 1;
            res_data[offset - 1] = 0;
        } else {
            auto len = strlen(day_name);
            memcpySmallAllowReadWriteOverflow15(&res_data[offset], day_name, len);
            offset += len + 1;
            res_data[offset - 1] = 0;
        }
        return offset;
    }
};

struct MonthNameImpl {
    static constexpr auto name = "monthname";
    static constexpr auto max_size = MAX_MONTH_NAME_LEN;

    static inline auto execute(const DateTimeValue& dt, ColumnString::Chars& res_data,
                               size_t& offset) {
        const auto* month_name = dt.month_name();
        if (month_name == nullptr) {
            offset += 1;
            res_data[offset - 1] = 0;
        } else {
            auto len = strlen(month_name);
            memcpySmallAllowReadWriteOverflow15(&res_data[offset], month_name, len);
            offset += len + 1;
            res_data[offset - 1] = 0;
        }
        return offset;
    }
};

struct DateFormatImpl {
    using FromType = Int128;

    static constexpr auto name = "date_format";

    static inline auto execute(const Int128& t, StringRef format, ColumnString::Chars& res_data,
                               size_t& offset) {
        const auto& dt = (DateTimeValue&)t;
        if (format.size > 128) {
            offset += 1;
            res_data.emplace_back(0);
            return std::pair{offset, true};
        }
        char buf[128];
        if (!dt.to_format_string(format.data, format.size, buf)) {
            offset += 1;
            res_data.emplace_back(0);
            return std::pair{offset, true};
        }

        auto len = strlen(buf) + 1;
        res_data.insert(buf, buf + len);
        offset += len;
        return std::pair{offset, false};
    }
};

struct FromUnixTimeImpl {
    using FromType = Int32;

    static constexpr auto name = "from_unixtime";

    static inline auto execute(FromType val, StringRef format, ColumnString::Chars& res_data,
                               size_t& offset) {
        // TODO: use default time zone, slowly and incorrect, just for test use
        static cctz::time_zone time_zone = cctz::fixed_time_zone(cctz::seconds(8 * 60 * 60));

        DateTimeValue dt;
        if (format.size > 128 || val < 0 || val > INT_MAX || !dt.from_unixtime(val, time_zone)) {
            offset += 1;
            res_data.emplace_back(0);
            return std::pair{offset, true};
        }

        char buf[128];
        if (!dt.to_format_string(format.data, format.size, buf)) {
            offset += 1;
            res_data.emplace_back(0);
            return std::pair{offset, true};
        }

        auto len = strlen(buf) + 1;
        res_data.insert(buf, buf + len);
        offset += len;
        return std::pair{offset, false};
    }
};

//struct ToRelativeYearNumImpl
//{
//    static constexpr auto name = "toRelativeYearNum";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toYear(t);
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toYear(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToRelativeQuarterNumImpl
//{
//    static constexpr auto name = "toRelativeQuarterNum";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeQuarterNum(t);
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeQuarterNum(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToRelativeMonthNumImpl
//{
//    static constexpr auto name = "toRelativeMonthNum";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeMonthNum(t);
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeMonthNum(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToRelativeWeekNumImpl
//{
//    static constexpr auto name = "toRelativeWeekNum";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeWeekNum(t);
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeWeekNum(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToRelativeDayNumImpl
//{
//    static constexpr auto name = "toRelativeDayNum";
//
//    static inline UInt16 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toDayNum(t);
//    }
//    static inline UInt16 execute(UInt16 d, const DateLUTImpl &)
//    {
//        return static_cast<DayNum>(d);
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//
//struct ToRelativeHourNumImpl
//{
//    static constexpr auto name = "toRelativeHourNum";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeHourNum(t);
//    }
//    static inline UInt32 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeHourNum(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToRelativeMinuteNumImpl
//{
//    static constexpr auto name = "toRelativeMinuteNum";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeMinuteNum(t);
//    }
//    static inline UInt32 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toRelativeMinuteNum(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToRelativeSecondNumImpl
//{
//    static constexpr auto name = "toRelativeSecondNum";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl &)
//    {
//        return t;
//    }
//    static inline UInt32 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.fromDayNum(DayNum(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToYYYYMMImpl
//{
//    static constexpr auto name = "toYYYYMM";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toNumYYYYMM(t);
//    }
//    static inline UInt32 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toNumYYYYMM(static_cast<DayNum>(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToYYYYMMDDImpl
//{
//    static constexpr auto name = "toYYYYMMDD";
//
//    static inline UInt32 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toNumYYYYMMDD(t);
//    }
//    static inline UInt32 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toNumYYYYMMDD(static_cast<DayNum>(d));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//struct ToYYYYMMDDhhmmssImpl
//{
//    static constexpr auto name = "toYYYYMMDDhhmmss";
//
//    static inline UInt64 execute(UInt32 t, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toNumYYYYMMDDhhmmss(t);
//    }
//    static inline UInt64 execute(UInt16 d, const DateLUTImpl & time_zone)
//    {
//        return time_zone.toNumYYYYMMDDhhmmss(time_zone.toDate(static_cast<DayNum>(d)));
//    }
//
//    using FactorTransform = ZeroTransform;
//};
//
//

template <typename Transform>
struct TransformerToStringOneArgument {
    static void vector(const PaddedPODArray<Int128>& ts, ColumnString::Chars& res_data,
                       ColumnString::Offsets& res_offsets) {
        auto len = ts.size();
        res_data.resize(len * Transform::max_size);
        res_offsets.resize(len);

        size_t offset = 0;
        for (int i = 0; i < len; ++i) {
            const auto& t = ts[i];
            const auto& date_time_value = reinterpret_cast<const DateTimeValue&>(t);
            res_offsets[i] = Transform::execute(date_time_value, res_data, offset);
        }
    }
};

template <typename Transform>
struct TransformerToStringTwoArgument {
    static void vector_constant(const PaddedPODArray<typename Transform::FromType>& ts,
                                const std::string& format, ColumnString::Chars& res_data,
                                ColumnString::Offsets& res_offsets,
                                PaddedPODArray<UInt8>& null_map) {
        auto len = ts.size();
        res_offsets.resize(len);

        size_t offset = 0;
        for (int i = 0; i < len; ++i) {
            const auto& t = ts[i];
            const auto [new_offset, is_null] = Transform::execute(
                    t, StringRef(format.c_str(), format.size()), res_data, offset);

            res_offsets[i] = new_offset;
            null_map[i] = is_null;
        }
    }
};

template <typename FromType, typename ToType, typename Transform>
struct Transformer {
    //    static void vector(const PaddedPODArray<FromType> & vec_from, PaddedPODArray<ToType> & vec_to, const DateLUTImpl & time_zone)
    static void vector(const PaddedPODArray<FromType>& vec_from, PaddedPODArray<ToType>& vec_to) {
        size_t size = vec_from.size();
        vec_to.resize(size);

        for (size_t i = 0; i < size; ++i) vec_to[i] = Transform::execute(vec_from[i]);
    }
};

template <typename FromType, typename ToType, typename Transform>
struct DateTimeTransformImpl {
    static void execute(Block& block, const ColumnNumbers& arguments, size_t result,
                        size_t /*input_rows_count*/) {
        using Op = Transformer<FromType, ToType, Transform>;

        //        const DateLUTImpl & time_zone = extractTimeZoneFromFunctionArguments(block, arguments, 1, 0);

        const ColumnPtr source_col = block.getByPosition(arguments[0]).column;
        if (const auto* sources = checkAndGetColumn<ColumnVector<FromType>>(source_col.get())) {
            auto col_to = ColumnVector<ToType>::create();
            //            Op::vector(sources->getData(), col_to->getData(), time_zone);
            Op::vector(sources->getData(), col_to->getData());
            block.getByPosition(result).column = std::move(col_to);
        } else {
            throw Exception("Illegal column " +
                                    block.getByPosition(arguments[0]).column->getName() +
                                    " of first argument of function " + Transform::name,
                            ErrorCodes::ILLEGAL_COLUMN);
        }
    }
};

} // namespace doris::vectorized