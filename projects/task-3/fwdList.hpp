#ifndef FORWARD_LIST
#define FORWARD_LIST
#include <iostream>
#include <utility>
#include "node.hpp"
namespace shapkov
{
	template < class Key, class Value >
	struct ForwardList
	{
		Node< Key, Value >* head_;

		ForwardList() :
			head_(nullptr)
		{}
		ForwardList(const ForwardList& other)
		{
			if (!other.head_)
			{
				head_ = nullptr;
				return;
			}
			try
			{
				head_ = new Node< Key, Value >(other.head_->data_.first, other.head_->data_.second);
				Node< Key, Value >* ptr = head_;
				Node< Key, Value >* ptr1 = other.head_;
				while (ptr1->next_)
				{
					ptr1 = ptr1->next_;
					ptr->next_ = new Node< Key, Value >(ptr1->data_.first, ptr1->data_.second);
					ptr = ptr->next_;
				}
			}
			catch (...)
			{
				while (head_)
				{
					Node< Key, Value >* temp = head_;
					head_ = head_->next_;
					delete temp;
				}
				throw;
			}
		}
		ForwardList(ForwardList&& other) noexcept:
			head_(other.head_)
		{
			other.head_ = nullptr;
		}
		void swap(ForwardList& other) noexcept
		{
			std::swap(this->head_, other.head_);
		}
		ForwardList& operator=(const ForwardList& other)
		{
			if (this == &other) {
				return *this;
			}
			ForwardList temp(other);
			swap(temp);
			return *this;
		}
		ForwardList& operator=(ForwardList&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}
			swap(other);
			return *this;
		}
		~ForwardList()
		{
			clear();
		}
		bool insert(const Key& key, const Value& value)
		{
			if (search(key))
			{
				return false;
			}
			head_ = new Node< Key, Value >(key, value, head_);
			return true;
		}
		bool remove(const Key& k)
		{
			if (head_ == nullptr)
			{
				return false;
			}
			if (head_->data_.first == k)
			{
				Node< Key, Value >* temp = head_;
				head_ = head_->next_;
				delete temp;
				return true;
			}
			Node< Key, Value >* ptr = head_;
			while (ptr->next_)
			{
				if (ptr->next_->data_.first == k)
				{
					Node< Key, Value >* temp = ptr->next_->next_;
					delete ptr->next_;
					ptr->next_ = temp;
					return true;
				}
				ptr = ptr->next_;
			}
			return false;
		}
		bool search(const Key& k) const
		{
			Node< Key, Value >* ptr = head_;
			while (ptr)
			{
				if (ptr->data_.first == k)
				{
					return true;
				}
				ptr = ptr->next_;
			}
			return false;
		}
		Node< Key, Value >* find(const Key& k)
		{
			Node< Key, Value >* ptr = head_;
			while (ptr)
			{
				if (ptr->data_.first == k)
				{
					return ptr;
				}
				ptr = ptr->next_;
			}
			return nullptr;
		}
		friend std::ostream& operator<<(std::ostream& out, const ForwardList& list)
		{
			Node* node = list.head_;
			while (node)
			{
				out << node->data_ << " ";
				node = node->next_;
			}
			return out;
		}
		void clear()
		{
			while (head_)
			{
				Node< Key, Value >* temp = head_;
				head_ = head_->next_;
				delete temp;
			}
		}
	};
}

#endif