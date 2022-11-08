
#ifndef JP_LIST_ITERATOR
#define JP_LIST_ITERATOR

#include "list_item.h"

namespace jp
{
	template <typename T>
	class ListIterator
	{
	public:
		ListIterator(ListItem<T>* listItem) :
			m_listItem(listItem)
		{ }

		bool operator==(const ListIterator<T>& other)
		{
			return this->m_listItem == other.m_listItem;
		}

		bool operator!=(const ListIterator<T>& other)
		{
			return !(*this == other);
		}

		ListIterator<T>& operator++()
		{
			m_listItem = m_listItem->next;
			return *this;
		}

		ListIterator<T> operator++(int)
		{
			ListIterator<T> old = *this;
			operator++();
			return old;
		}

		ListIterator<T>& operator+=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->next;
			}
			return *this;
		}


		friend ListIterator<T> operator+(ListIterator<T> lhs, size_t count)
		{
			lhs += count;
			return lhs;
		}


		ListIterator<T>& operator--()
		{
			m_listItem = m_listItem->prev;
			return *this;
		}

		ListIterator<T> operator--(int)
		{
			ListIterator<T> old = *this;
			operator--();
			return old;
		}

		ListIterator<T>& operator-=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->prev;
			}
			return *this;
		}


		friend ListIterator<T> operator-(ListIterator<T> lhs, size_t count)
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
