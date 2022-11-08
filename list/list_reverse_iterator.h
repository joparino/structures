
#ifndef JP_LIST_REVERSE_ITERATOR
#define JP_LIST_REVERSE_ITERATOR

#include "list_item.h"

namespace jp
{
	template <typename T>
	class ListReverseIterator
	{
	public:
		ListReverseIterator(ListItem<T>* listItem) :
			m_listItem(listItem)
		{ }

		bool operator==(const ListReverseIterator<T>& other)
		{
			return this->m_listItem == other.m_listItem;
		}

		bool operator!=(const ListReverseIterator<T>& other)
		{
			return !(*this == other);
		}

		ListReverseIterator<T>& operator++()
		{
			m_listItem = m_listItem->prev;
			return *this;
		}

		ListReverseIterator<T> operator++(int)
		{
			ListReverseIterator<T> old = *this;
			operator++();
			return old;
		}

		ListReverseIterator<T>& operator+=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->prev;
			}
			return *this;
		}


		friend ListReverseIterator<T> operator+(ListReverseIterator<T> lhs, size_t count)
		{
			lhs += count;
			return lhs;
		}


		ListReverseIterator<T>& operator--()
		{
			m_listItem = m_listItem->next;
			return *this;
		}

		ListReverseIterator<T> operator--(int)
		{
			ListReverseIterator<T> old = *this;
			operator--();
			return old;
		}

		ListReverseIterator<T>& operator-=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->next;
			}
			return *this;
		}


		friend ListReverseIterator<T> operator-(ListReverseIterator<T> lhs, size_t count)
		{
			lhs -= count;
			return lhs;
		}


		T& operator*()
		{
			return m_listItem->value;
		}

	private:
		ListItem<T>* m_listItem;
	};
}

#endif
