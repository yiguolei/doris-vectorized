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

#include "vec/data_types/data_type_date_time.h"

#include "runtime/datetime_value.h"
#include "vec/columns/columns_number.h"

namespace doris::vectorized {

DataTypeDateTime::DataTypeDateTime() {}

std::string DataTypeDateTime::doGetName() const {
    return "DateTime";
}

bool DataTypeDateTime::equals(const IDataType& rhs) const {
    return typeid(rhs) == typeid(*this);
}
std::string DataTypeDateTime::to_string(const IColumn& column, size_t row_num) const {
    Int128 int_val = assert_cast<const ColumnInt128&>(*column.convertToFullColumnIfConst().get())
                             .getData()[row_num];
    doris::DateTimeValue value = *reinterpret_cast<doris::DateTimeValue*>(&int_val);
    std::stringstream ss;
    // Year
    uint32_t temp = value.year() / 100;
    ss << (char)('0' + (temp / 10)) << (char)('0' + (temp % 10));
    temp = value.year() % 100;
    ss << (char)('0' + (temp / 10)) << (char)('0' + (temp % 10)) << '-';
    // Month
    ss << (char)('0' + (value.month() / 10)) << (char)('0' + (value.month() % 10)) << '-';
    // Day
    ss << (char)('0' + (value.day() / 10)) << (char)('0' + (value.day() % 10));
    if (value.neg()) {
        ss << '-';
    }
    ss << ' ';
    // Hour
    temp = value.hour();
    if (temp >= 100) {
        ss << (char)('0' + (temp / 100));
        temp %= 100;
    }
    ss << (char)('0' + (temp / 10)) << (char)('0' + (temp % 10)) << ':';
    // Minute
    ss << (char)('0' + (value.minute() / 10)) << (char)('0' + (value.minute() % 10)) << ':';
    /* Second */
    ss << (char)('0' + (value.second() / 10)) << (char)('0' + (value.second() % 10));
    if (value.microsecond() > 0) {
        ss << '.';
        uint32_t first = value.microsecond() / 10000;
        uint32_t second = (value.microsecond() % 10000) / 100;
        uint32_t third = value.microsecond() % 100;
        ss << (char)('0' + first / 10) << (char)('0' + first % 10) << (char)('0' + second / 10);
        ss << (char)('0' + second % 10) << (char)('0' + third / 10) << (char)('0' + third % 10);
    }
    return ss.str();
}

} // namespace doris::vectorized
