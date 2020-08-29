#pragma once

#include <algorithm>
#include <endian.h>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {

#if __BYTE_ORDER == __LITTLE_ENDIAN
#  define hostToNet(x) reverseByteOrder(x)
#  define netToHost(x) reverseByteOrder(x)
#else
#  define hostToNet(x) x
#  define netToHost(x) x
#endif

template <typename T> inline T reverseByteOrder(T const &val, typename std::enable_if<std::is_arithmetic<T>::value, std::nullptr_t>::type = nullptr) {
  union U {
    T val;
    std::array<std::uint8_t, sizeof(T)> raw;
  } src, dst;
  src.val = val;
  std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
  return dst.val;
}

}}}}