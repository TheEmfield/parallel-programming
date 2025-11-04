#ifndef HASH_MAP_ITERATOR
#define HASH_MAP_ITERATOR

#include "node.hpp"
#include <type_traits>
#include <iterator>

namespace shapkov
{
	template < class Key, class T, class Hash, class KeyEqual >
	class HashMap;

	template < class Key, class T, class Hash, class KeyEqual, bool isConst >
	class HashMapIterator
	{
		friend class HashMap< Key, T, Hash, KeyEqual >;
	public:
		using this_t = HashMapIterator< Key, T, Hash, KeyEqual, isConst >;
		using Val = typename std::conditional< isConst, const std::pair< Key, T >, std::pair< Key, T > >::type;
		using Ref = typename std::conditional< isConst, const std::pair< Key, T >&, std::pair< Key, T >& >::type;
		using Ptr = typename std::conditional< isConst, const std::pair< Key, T >*, std::pair< Key, T >* >::type;
		using Map = typename std::conditional< isConst, const HashMap< Key, T, Hash, KeyEqual >, HashMap< Key, T, Hash, KeyEqual > >::type;

		HashMapIterator() :
			hMap_(nullptr),
			bucket_(0),
			node_(nullptr)
		{}

		template< bool OtherConst, typename = std::enable_if_t< isConst || !OtherConst > >
		HashMapIterator(const HashMapIterator< Key, T, Hash, KeyEqual, OtherConst >& other) :
			hMap_(other.hMap_),
			bucket_(other.bucket_),
			node_(other.node_)
		{}

		HashMapIterator(Map* map, size_t b, Node< Key, T >* n) :
			hMap_(map),
			bucket_(b),
			node_(n)
		{}

		~HashMapIterator() = default;
		HashMapIterator(const this_t&) = default;
		this_t& operator=(const this_t&) = default;

		this_t& operator++()
		{
			if (node_)
			{
				node_ = node_->next_;
			}
			while (!node_ && (bucket_ + 1) < hMap_->size_)
			{
				++bucket_;
				node_ = hMap_->buckets_[bucket_].head_;
			}
			if (!node_)
			{
				bucket_ = hMap_->size_;
			}
			return *this;
		}

		this_t operator++(int)
		{
			this_t result(*this);
			++(*this);
			return result;
		}

		Ref operator*() const
		{
			return node_->data_;
		}

		Ptr operator->() const
		{
			return &(node_->data_);
		}

		bool operator==(const this_t& other) const
		{
			return node_ == other.node_ && bucket_ == other.bucket_ && hMap_ == other.hMap_;
		}
		bool operator!=(const this_t& other) const
		{
			return !(*this == other);
		}

	private:
		Map* hMap_;
		size_t bucket_;
		Node< Key, T >* node_;
	};
}

#endif
