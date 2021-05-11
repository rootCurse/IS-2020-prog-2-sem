#ifndef PREDICATE_HPP
#define PREDICATE_HPP
#include <functional>
template<class iterator, class predicate>
bool allOf(const iterator begin, const iterator end, const predicate pred)
{
	for (auto it = begin; it != end; it++)
		if (!pred(*it))
			return false;
	return true;
}

template<class iterator, class predicate>
bool anyOf(const iterator begin, const iterator end, const predicate pred)
{
	for (auto it = begin; it != end; it++)
		if (pred(*it))
			return true;
	return false;
}

template<class iterator, class predicate>
bool noneOf(const iterator begin, const iterator end, const predicate pred)
{
	return !anyOf(begin, end, pred);
}

template<class iterator, class predicate>
bool oneOf(const iterator begin, const iterator end, const predicate pred)
{
	bool flag = 0;
	for (auto it = begin; it != end; it++)
	{
		if (pred(*it))
			if (flag)
				return false;
			else
				flag = true;
	}
	return flag;
}

template<class iterator, class predicate = std::less<>>
bool isSorted(const iterator begin, const iterator end, const predicate pred = predicate())
{
	iterator previous = begin;
	for (auto it = next(begin); it != end; it++)
	{
		if (!pred(*previous, *it))
			return false;
		previous = it;
	}
	return true;
}

template<class iterator, class predicate>
bool isPartitioned(const iterator begin, const iterator end, const predicate pred)
{
	bool flag = 0;
	iterator prev = begin;
	for (auto it = begin; it != end; it++)
	{
		if (pred(*prev) != pred(*it))
		{
			if (!flag)
				flag = true;
			else
				return false;
		}
	}
	return flag;

}

template<class iterator, class predicate>
iterator findNot(const iterator begin, const iterator end, const predicate key)
{
	for (auto it = begin; it != end; it++)
		if (*it != key)
			return it;
	return end;
}

template<class iterator, class predicate>
iterator findBackward(const iterator begin, const iterator end, const predicate key)
{
	iterator ans = end;
	for (auto it = begin; it != end; it++)
		if (*it == key)
			ans = it;
	return ans;
}

template<class iterator, class predicate>
bool isPalindrome(const iterator begin, const iterator end, const predicate pred)
{
	for (auto itl = begin, itr = prev(end); (itl != end && itr != begin); itl++, itr--)
		if (!pred(*itl, *itr))
			return false;
	return true;
}

#endif