
#ifndef JP_LIST_CONST_REVERSE_ITERATOR
#define JP_LIST_CONST_REVERSE_ITERATOR

#include "list_item.h"

namespace jp
{
	template <typename T>
	class ListConstReverseIterator
	{
	public:
		ListConstReverseIterator(ListItem<T>* listItem) :
			m_listItem(listItem)
		{ }

		bool operator==(const ListConstReverseIterator<T>& other)
		{
			return this->m_listItem == other.m_listItem;
		}

		bool operator!=(const ListConstReverseIterator<T>& other)
		{
			return !(*this == other);
		}

		ListConstReverseIterator<T>& operator++()
		{
			m_listItem = m_listItem->prev;
			return *this;
		}

		ListConstReverseIterator<T> operator++(int)
		{
			ListConstReverseIterator<T> old = *this;
			operator++();
			return old;
		}

		ListConstReverseIterator<T>& operator+=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->prev;
			}
			return *this;
		}


		friend ListConstReverseIterator<T> operator+(ListConstReverseIterator<T> lhs, size_t count)
		{
			lhs += count;
			return lhs;
		}


		ListConstReverseIterator<T>& operator--()
		{
			m_listItem = m_listItem->next;
			return *this;
		}

		ListConstReverseIterator<T> operator--(int)
		{
			ListConstReverseIterator<T> old = *this;
			operator--();
			return old;
		}

		ListConstReverseIterator<T>& operator-=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->next;
			}
			return *this;
		}


		friend ListConstReverseIterator<T> operator-(ListConstReverseIterator<T> lhs, size_t count)
		{
			lhs -= count;
			return lhs;
		}


		const T& operator*()
		{
			return m_listItem->value;
		}

	private:
		ListItem<T>* m_listItem;
	};
}

#endif
