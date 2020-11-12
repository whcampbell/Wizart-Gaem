#pragma once
#include <bitset>

namespace INTERNAL_ONLY_COMPONENT {
    using CID = std::size_t;

inline CID getCID() {
	static CID last = 0;
	return last++;
}

template <typename T> inline CID getCID() noexcept {
	static CID typeID = getCID();
	return typeID;
}
};