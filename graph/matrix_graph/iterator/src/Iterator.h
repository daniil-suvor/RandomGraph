#pragma once
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <iterator>
class NodeIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = double;
	using pointer = double*;
	using reference = double&;
	int node;

	NodeIterator(pointer ptr, int step);

	reference operator*() const { return *m_ptr; }
	pointer operator->() { return m_ptr; }
	NodeIterator& operator++();
	NodeIterator operator++(int) { NodeIterator tmp = *this; ++(*this); return tmp; }
	friend bool operator== (const NodeIterator& a, const NodeIterator& b) { return a.m_ptr == b.m_ptr; };
	friend bool operator!= (const NodeIterator& a, const NodeIterator& b) { return a.m_ptr != b.m_ptr; };

private:
	pointer m_ptr;
	int step;
};

class  AdjacentIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = double;
	using pointer = double*;
	using reference = double&;
	int adjNode;
	AdjacentIterator(pointer ptr);
	AdjacentIterator(pointer ptr, int graphSize, int node);

	reference operator*() const { return *m_ptr; }
	pointer operator->() { return m_ptr; }
	AdjacentIterator& operator++();
	AdjacentIterator operator++(int) { AdjacentIterator tmp = *this; ++(*this); return tmp; }
	friend bool operator== (const AdjacentIterator& a, const AdjacentIterator& b) { return a.m_ptr == b.m_ptr; };
	friend bool operator!= (const AdjacentIterator& a, const AdjacentIterator& b) { return a.m_ptr != b.m_ptr; };

private:
	pointer m_ptr;
	int step;
	int stopStep;
	int node;
};

#endif // !_ITERATOR_H_
