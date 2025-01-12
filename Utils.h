#pragma once

// RAII for backtracking
template<typename T>
class ScopedRevert {
public:
	ScopedRevert(T& val) : valPtr{&val} {
		originalVal = val;
	}
	
	~ScopedRevert() {
		*valPtr = originalVal;
	}
	
private:
	T* valPtr;
	T originalVal;
};

// Takes a pointer-to-member for type T
// Returns a comparator for type T which compares by the given field
template<typename M, typename T, typename Compare = std::less<M>>
auto makeMemberComparator(M T::* member, Compare cmp = {}) {
	return [=](const T& a, const T& b) {
		return cmp(a.*member, b.*member);
	};
}

// Hash function for pair types
struct PairHash {
	template <typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const {
		std::size_t hash1 = std::hash<T1>{}(pair.first);
		std::size_t hash2 = std::hash<T2>{}(pair.second);

		return hash1 ^ (hash2 << 1);
	}
};