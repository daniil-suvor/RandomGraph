#include "Iterator.h"

NodeIterator::NodeIterator(pointer ptr, int step) : m_ptr(ptr) {
	this->step = step;
	this->node = 0;
}

NodeIterator& NodeIterator::operator++() {
	m_ptr += step;
	step--; node++;
	return *this;
}

AdjacentIterator::AdjacentIterator(pointer ptr) : m_ptr(ptr) {
	this->adjNode = 0;
	this->node = 0;
	this->step = 0;
	this->stopStep = 0;
}

AdjacentIterator::AdjacentIterator(pointer ptr, int graphSize, int node) : m_ptr(ptr) {
	this->adjNode = 0;
	this->node = node;
	this->step = graphSize - 1;
	this->stopStep = graphSize - node - 1;
	if (node == 0) {
		m_ptr++;
		this->adjNode += 1;
	}
}

AdjacentIterator& AdjacentIterator::operator++() {
	if (step == stopStep)
		m_ptr++;
	else {
		m_ptr += step;
		step--;
	}
	adjNode++;
	if (adjNode == node) {
		m_ptr++;
		adjNode++;
	}
	return *this;
}
