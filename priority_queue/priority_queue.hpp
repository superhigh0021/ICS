#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <vector>
#include <functional>

#include "heap_algorithm.hpp"

INTERFACE_BEGIN

struct value_initialize_first_tag_t { };
constexpr value_initialize_first_tag_t value_initialize_first_tag;
struct one_value_initialize_first_tag_t { };
constexpr one_value_initialize_first_tag_t one_value_initialize_first_tag;

template<class T1, class T2, bool opt = std::is_empty<T1>::value && !std::is_final<T1>::value>
class compressed_pair : private T1 {
public:
	constexpr compressed_pair() = default;
	template<class... Args>
	constexpr compressed_pair(value_initialize_first_tag_t, Args&&... args)
		: T1(), _t2(std::forward<Args>(args)...) { }
	template<class Arg1, class... Args>
	constexpr compressed_pair(one_value_initialize_first_tag_t, Arg1&& arg1, Args&&... args)
		: T1(std::forward<Arg1>(arg1)), _t2(std::forward<Args>(args)...) { }

	constexpr T1& first_value() {
		return *this;
	}
	constexpr const T1& first_value() const {
		return *this;
	}

	constexpr T2& second_value() {
		return _t2;
	}
	constexpr const T2& second_value() const {
		return _t2;
	}
private:
	T2 _t2;
};

template<class T1, class T2>
class compressed_pair<T1, T2, false> {
public:
	constexpr compressed_pair() = default;
	template<class... Args>
	constexpr compressed_pair(value_initialize_first_tag_t, Args&&... args)
		: _t1(), _t2(std::forward<Args>(args)...) { }
	template<class Arg1, class... Args>
	constexpr compressed_pair(one_value_initialize_first_tag_t, Arg1 && arg1, Args&&... args)
		: _t1(std::forward<Arg1>(arg1)), _t2(std::forward<Args>(args)...) { }

	constexpr T1& first_value() {
		return _t1;
	}
	constexpr const T1& first_value() const {
		return _t1;
	}

	constexpr T2& second_value() {
		return _t2;
	}
	constexpr const T2& second_value() const {
		return _t2;
	}
private:
	T1 _t1;
	T2 _t2;
};

template<class Ty, class Container = std::vector<Ty>, class Comp = std::less<typename Container::value_type>>
class priority_queue {
	static_assert(std::is_same_v<Ty, typename Container::value_type>, "invalid container type");
public:
	using container_type	= Container;
	using value_compare		= Comp;
	using value_type			= typename Container::value_type;
	using size_type				= typename Container::size_type;
	using reference				= typename Container::reference;
	using const_reference = typename Container::const_reference;
	using iterator				= typename Container::iterator;
	using const_iterator	= typename Container::const_iterator;

	priority_queue() : priority_queue(Comp(), Container()) { }

	explicit priority_queue(const Comp& comp) : priority_queue(comp, Container()) { }

	priority_queue(const Comp& comp, const Container& cont)
		: _c(cont), _comp(comp) {
		INTERFACE make_heap(_c.begin(), _c.end(), _comp);
	}

	priority_queue(const Comp& comp, Container&& cont)
		: _c(std::move(cont)), _comp(comp) {
		INTERFACE make_heap(_c.begin(), _c.end(), _comp);
	}
	
	const_reference top() const {
		return _c.front();
	}

	bool empty() const {
		return _c.empty();
	}

	size_type size() const {
		return _c.size();
	}

	void push(const value_type& value) {
		_c.push_back(value);
		INTERFACE push_heap(_c.begin(), _c.end(), _comp);
	}

	void push(value_type&& value) {
		_c.push_back(std::move(value));
		INTERFACE push_heap(_c.begin(), _c.end(), _comp);
	}

	template<class... Args>
	void emplace(Args&&... args) {
		_c.emplace_back(std::forward<Args>(args)...);
		INTERFACE push_heap(_c.begin(), _c.end(), _comp);
	}

	void pop() {
		INTERFACE pop_heap(_c.begin(), _c.end(), _comp);
		_c.pop_back();
	}

	iterator begin() {
		return _c.begin();
	}
	const_iterator begin() const {
		return _c.begin();
	}
	const_iterator cbegin() const {
		return _c.cbegin();
	}

	iterator end() {
		return _c.end();
	}
	const_iterator end() const {
		return _c.end();
	}
	const_iterator cend() const {
		return _c.cend();
	}

	void increase_key(iterator pos, const value_type& value) {
		_increase_key_impl(pos, value);
	}

	void increase_key(iterator pos, value_type&& value) {
		_increase_key_impl(pos, std::move(value));
	}
protected:
	Container _c;
	Comp _comp;

	template<class Arg>
	void _increase_key_impl(iterator pos, Arg&& arg) {
		std::size_t _idx = static_cast<std::size_t>(pos - _c.begin());
		value_type _new_value = std::forward<Arg>(arg);
		bool _less = _comp(*pos, _new_value);
		*pos = std::forward<Arg>(arg);
		if (_less) {
			IMPL _adjust_heap(_c.begin(), _idx, _c.size(), _comp);
		}
		else {
			INTERFACE push_heap(_c.begin(), ++pos, _comp);
		}
	}
};

INTERFACE_END

#endif // !PRIORITY_QUEUE_HPP
