#ifndef HASH_MAP
#define HASH_MAP
#include <functional>
#include "fwdList.hpp"
#include "hashMapIterator.hpp"

namespace shapkov
{
	template <class Key, class T, class Hash = std::hash< Key >, class KeyEqual = std::equal_to< Key >>
	class HashMap
	{
		friend class HashMapIterator< Key, T, Hash, KeyEqual, false >;
		friend class HashMapIterator< Key, T, Hash, KeyEqual, true >;
	public:
		using iterator = HashMapIterator< Key, T, Hash, KeyEqual, false >;
		using const_iterator = HashMapIterator< Key, T, Hash, KeyEqual, true >;

		explicit HashMap(size_t size = 101);
		HashMap(const HashMap& src);
		HashMap(HashMap&& src) noexcept;
		void swap(HashMap& src) noexcept;
		HashMap& operator=(const HashMap& src);
		HashMap& operator=(HashMap&& src) noexcept;
		~HashMap();
		std::pair< bool, iterator > insert(const Key& key, const T& value);
		bool erase(const Key& key);
		iterator find(const Key& key);
		const_iterator find(const Key& key) const;
		T& at(const Key& key);
		const T& at(const Key& key) const;
		T& operator[](const Key& key);
		void clear();
		void rehash(size_t newSize);
		size_t size() const;
		bool empty() const;
		bool operator==(const HashMap& src) const;
		bool operator!=(const HashMap& src) const;
		double load_factor() const;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;


	private:
		ForwardList< Key, T >* buckets_;
		size_t number_;
		size_t size_;
		Hash hash;
		KeyEqual key_equal;
		static constexpr double MAX_LOAD = 0.7;
	};

	template < class Key, class T, class Hash, class KeyEqual >
	HashMap< Key, T, Hash, KeyEqual >::HashMap(size_t size) :
		buckets_(new ForwardList< Key, T >[size]),
		number_(0),
		size_(size),
		hash(Hash{}),
		key_equal(KeyEqual{})
	{}

	template < class Key, class T, class Hash, class KeyEqual >
	HashMap< Key, T, Hash, KeyEqual >::HashMap(const HashMap& src) :
		buckets_(new ForwardList< Key, T >[src.size_]),
    	number_(src.number_),
    	size_(src.size_),
    	hash(src.hash),
    	key_equal(src.key_equal)
	{
		try
		{
			for (size_t i = 0; i < src.size_; i++)
			{
				buckets_[i] = src.buckets_[i];
			}
		}
		catch (...)
		{
			delete[] buckets_;
			throw;
		}
	}

	template < class Key, class T, class Hash, class KeyEqual >
	HashMap< Key, T, Hash, KeyEqual >::HashMap(HashMap&& src) noexcept:
		buckets_(src.buckets_),
    	number_(src.number_),
    	size_(src.size_),
    	hash(src.hash),
    	key_equal(src.key_equal)
	{
		src.buckets_ = nullptr;
    	src.number_ = 0;
    	src.size_ = 0;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	void HashMap< Key, T, Hash, KeyEqual >::swap(HashMap& src) noexcept
	{
		std::swap(buckets_, src.buckets_);
		std::swap(number_, src.number_);
		std::swap(size_, src.size_);
		std::swap(hash, src.hash);
		std::swap(key_equal, src.key_equal);
	}

	template < class Key, class T, class Hash, class KeyEqual >
	HashMap< Key, T, Hash, KeyEqual>& HashMap<Key, T, Hash, KeyEqual >::operator=(const HashMap& src)
	{
		if (this != &src)
		{
			HashMap temp(src);
			swap(temp);
		}
		return *this;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	HashMap< Key, T, Hash, KeyEqual >& HashMap< Key, T, Hash, KeyEqual >::operator=(HashMap&& src) noexcept
	{
		if (this != &src)
		{
			HashMap temp(std::move(src));
			swap(temp);
		}
		return *this;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	HashMap< Key, T, Hash, KeyEqual >::~HashMap()
	{
		delete[] buckets_;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	double HashMap< Key, T, Hash, KeyEqual >::load_factor() const
	{
		return static_cast< double >(number_) / size_;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	std::pair< bool, typename HashMap< Key, T, Hash, KeyEqual >::iterator > HashMap< Key, T, Hash, KeyEqual >::insert(const Key& key, const T& value)
	{
		if (load_factor() >= MAX_LOAD)
		{
			rehash(size_ * 2);
		}
		size_t index = hash(key) % size_;
		if (buckets_[index].insert(key, value))
		{
			number_++;
			return { true, iterator(this, index, buckets_[index].find(key)) };
		}
		return { false, iterator(this, index, buckets_[index].find(key)) };
	}

	template < class Key, class T, class Hash, class KeyEqual >
	void HashMap< Key, T, Hash, KeyEqual >::rehash(size_t newSize)
	{
		auto* newBuckets = new ForwardList< Key, T >[newSize];
		try
		{
			for (size_t i = 0; i < size_; ++i)
			{
				auto* node = buckets_[i].head_;
				while (node)
				{
					size_t newIndex = hash(node->data_.first) % newSize;
					newBuckets[newIndex].insert(node->data_.first, node->data_.second);
					node = node->next_;
				}
			}
		}
		catch (...)
		{
			delete[] newBuckets;
			throw;
		}
		delete[] buckets_;
		buckets_ = newBuckets;
		size_ = newSize;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	bool HashMap< Key, T, Hash, KeyEqual >::erase(const Key& key)
	{
		size_t index = hash(key) % size_;
		if (buckets_[index].remove(key))
		{
			number_--;
			return true;
		}
		return false;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	T& HashMap< Key, T, Hash, KeyEqual >::at(const Key& key)
	{
		size_t index = hash(key) % size_;
		auto value = buckets_[index].find(key);
		if (value != nullptr)
		{
			return value->data_.second;
		}
		else
		{
			throw std::out_of_range("Out of range");
		}
	}

	template < class Key, class T, class Hash, class KeyEqual >
	const T& HashMap< Key, T, Hash, KeyEqual >::at(const Key& key) const
	{
		size_t index = hash(key) % size_;
		auto value = buckets_[index].find(key);
		if (value != nullptr)
		{
			return value->data_.second;
		}
		else
		{
			throw std::out_of_range("Out of range");
		}
	}

	template < class Key, class T, class Hash, class KeyEqual >
	T& HashMap< Key, T, Hash, KeyEqual >::operator[](const Key& key)
	{
		auto val = insert(key, T{});
		return val.second->second;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	void HashMap< Key, T, Hash, KeyEqual >::clear()
	{
		for (size_t i = 0; i < size_; ++i)
		{
			buckets_[i].clear();
		}
		number_ = 0;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	size_t HashMap< Key, T, Hash, KeyEqual >::size() const
	{
		return number_;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	bool HashMap< Key, T, Hash, KeyEqual >::empty() const
	{
		return number_ == 0;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	bool HashMap< Key, T, Hash, KeyEqual >::operator==(const HashMap& other) const
	{
		if (number_ != other.number_)
		{
			return false;
		}
		for (size_t i = 0; i < size_; ++i)
		{
			auto current = buckets_[i].head_;
			while (current)
			{
				auto word = other.find(current->data_.first);
				if (word == other.end() || word->second != current->data_.second) {
					return false;
				}
				current = current->next_;
			}
		}
		return true;
	}

	template < class Key, class T, class Hash, class KeyEqual >
	bool HashMap< Key, T, Hash, KeyEqual >::operator!=(const HashMap& other) const
	{
		return !(*this == other);
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::iterator HashMap< Key, T, Hash, KeyEqual >::begin()
	{
		for (size_t i = 0; i < size_; ++i)
		{
			if (buckets_[i].head_)
			{
				return iterator(this, i, buckets_[i].head_);
			}
		}
		return end();
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::iterator HashMap< Key, T, Hash, KeyEqual >::end()
	{
		return iterator(this, size_, nullptr);
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::const_iterator HashMap< Key, T, Hash, KeyEqual >::begin() const
	{
		return cbegin();
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::const_iterator HashMap< Key, T, Hash, KeyEqual >::end() const
	{
		return cend();
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::const_iterator HashMap< Key, T, Hash, KeyEqual >::cbegin() const
	{
		for (size_t i = 0; i < size_; ++i)
		{
			if (buckets_[i].head_)
			{
				return const_iterator(this, i, buckets_[i].head_);
			}
		}
		return cend();
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::const_iterator HashMap< Key, T, Hash, KeyEqual >::cend() const
	{
		return const_iterator(this, size_, nullptr);
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::iterator HashMap< Key, T, Hash, KeyEqual >::find(const Key& key)
	{
		size_t index = hash(key) % size_;
		auto node = buckets_[index].find(key);
		return (node != nullptr) ? iterator(this, index, buckets_[index].find(key)) : end();
	}

	template< typename Key, typename T, typename Hash, typename KeyEqual >
	typename HashMap< Key, T, Hash, KeyEqual >::const_iterator HashMap< Key, T, Hash, KeyEqual >::find(const Key& key) const
	{
		size_t index = hash(key) % size_;
		auto node = buckets_[index].find(key);
		return (node != nullptr) ? const_iterator(this, index, buckets_[index].find(key)) : cend();
	}
}

#endif