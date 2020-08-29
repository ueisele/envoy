#pragma once

#include <memory>
#include <string>
#include <vector>

#include <sstream>
#include <iterator>

#include "absl/types/optional.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {

/**
 * Nullable string used by Kafka.
 */
using NullableString = absl::optional<std::string>;

/**
 * Bytes array used by Kafka.
 */
using Bytes = std::vector<unsigned char>;

/**
 * Nullable bytes array used by Kafka.
 */
using NullableBytes = absl::optional<Bytes>;

/**
 * Kafka array of elements of type T.
 */
template <typename T> using NullableArray = absl::optional<std::vector<T>>;

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T> & v) {
    os << "[";
    if(!v.empty()) {
        std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(os, ","));
        os << v.back();
    }
    os << "]";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const std::vector<unsigned char> & b) {
    os << "{\"bytes\":" << b.size() << "}";
    return os;
}

} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
