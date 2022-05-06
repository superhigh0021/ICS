#ifndef HEAP_ALGORITHM_HPP
#define HEAP_ALGORITHM_HPP

#include <cstddef>
#include <iterator>

#include "def.hpp"

#define LEFT_CHILD(IDX)  ((IDX) * 2 + 1)
#define RIGHT_CHILD(IDX) ((IDX) * 2 + 2)
#define PARENT(IDX)      (((IDX) - 1) / 2)

INTERFACE_BEGIN

IMPL_BEGIN
template<class RandIt, class Comp>
void _adjust_heap(RandIt begin, std::size_t root_idx, std::size_t length, Comp comp) {
	using value_type = typename std::iterator_traits<RandIt>::value_type;
	value_type root_value = std::move(*(begin + root_idx));
	for (std::size_t _largest = RIGHT_CHILD(root_idx);
		root_idx < (length - 1) / 2; root_idx = _largest, _largest = RIGHT_CHILD(root_idx)) {
		if (comp(*(begin + _largest), *(begin + LEFT_CHILD(root_idx))))
			--_largest;
		if (comp(root_value, *(begin + _largest))) {
			*(begin + root_idx) = std::move(*(begin + _largest));
		}
		else {
			*(begin + root_idx) = std::move(root_value);
			return;
		}
	}
	if (!(length & 1) && root_idx == (length - 1) / 2) {
		std::size_t left_idx = LEFT_CHILD(root_idx);
		if (comp(root_value, *(begin + left_idx))) {
			*(begin + root_idx) = std::move(*(begin + left_idx));
			root_idx = left_idx;
		}
	}
	*(begin + root_idx) = std::move(root_value);
}

template<class RandIt, class Comp>
void _pop_heap_unchecked(RandIt begin, RandIt end, Comp comp) {
	--end;
	std::iter_swap(begin, end);
	IMPL _adjust_heap(begin, 0, end - begin, comp);
}
IMPL_END

template<class RandIt, class Comp>
void make_heap(RandIt begin, RandIt end, Comp comp) {
	std::size_t _length = static_cast<std::size_t>(end - begin);
	for (std::size_t idx = _length / 2; idx > 0; ) {
		--idx;
		IMPL _adjust_heap(begin, idx, _length, comp);
	}
}

template<class RandIt>
void make_heap(RandIt begin, RandIt end) {
	INTERFACE make_heap(begin, end, std::less<>());
}

template<class RandIt, class Comp>
void push_heap(RandIt begin, RandIt end, Comp comp) {
	using value_type = typename std::iterator_traits<RandIt>::value_type;
	value_type value = std::move(*--end);
	std::size_t idx = static_cast<std::size_t>(end - begin);
	for (; idx != 0; idx = PARENT(idx)) {
		if (comp(*(begin + PARENT(idx)), value)) {
			*(begin + idx) = std::move(*(begin + PARENT(idx)));
		}
		else
			break;
	}
	*(begin + idx) = std::move(value);
}

template<class RandIt>
void push_heap(RandIt begin, RandIt end) {
	INTERFACE push_heap(begin, end, std::less<>());
}

template<class RandIt, class Comp>
void pop_heap(RandIt begin, RandIt end, Comp comp) {
	if (end - begin > 1) {
		IMPL _pop_heap_unchecked(begin, end, comp);
	}
}

template<class RandIt>
void pop_heap(RandIt begin, RandIt end) {
	INTERFACE pop_heap(begin, end, std::less<>());
}

template<class RandIt, class Comp>
void sort_heap(RandIt begin, RandIt end, Comp comp) {
	for (auto temp_begin = begin++; begin != end; --end)
		IMPL _pop_heap_unchecked(temp_begin, end, comp);
}

template<class RandIt>
void sort_heap(RandIt begin, RandIt end) {
	INTERFACE sort_heap(begin, end, std::less<>());
}

INTERFACE_END

#undef LEFT_CHILD
#undef RIGHT_CHILD
#undef PARENT

#endif // !HEAP_ALGORITHM_HPP

