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