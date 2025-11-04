#ifndef NODE_H
#define NODE_H
#include <utility>

namespace shapkov
{
	template <class Key, class Value>
	struct Node
	{
		std::pair<Key, Value> data_;
		Node* next_;
		Node(const Key& k, const Value& val, Node* ptr = nullptr) : data_({ k, val }), next_(ptr) {}
	};
}
#endif