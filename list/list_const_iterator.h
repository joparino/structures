
#ifndef JP_LIST_CONST_ITERATOR
#define JP_LIST_CONST_ITERATOR

#include "list_item.h"

namespace jp
{
	template <typename T>
	class ListConstIterator
	{
	public:
		ListConstIterator(ListItem<T>* listItem) :
			m_listItem(listItem)
		{ }

		bool operator==(const ListConstIterator<T>& other)
		{
			return this->m_listItem == other.m_listItem;
		}

		bool operator!=(const ListConstIterator<T>& other)
		{
			return !(*this == other);
		}

		ListConstIterator<T>& operator++()
		{
			m_listItem = m_listItem->next;
			return *this;
		}

		ListConstIterator<T> operator++(int)
		{
			ListConstIterator<T> old = *this;
			operator++();
			return old;
		}

		ListConstIterator<T>& operator+=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->next;
			}
			return *this;
		}


		friend ListConstIterator<T> operator+(ListConstIterator<T> lhs, size_t count)
		{
			lhs += count;
			return lhs;
		}


		ListConstIterator<T>& operator--()
		{
			m_listItem = m_listItem->prev;
			return *this;
		}

		ListConstIterator<T> operator--(int)
		{
			ListConstIterator<T> old = *this;
			operator--();
			return old;
		}

		ListConstIterator<T>& operator-=(size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				m_listItem = m_listItem->prev;
			}
			return *this;
		}


		friend ListConstIterator<T> operator-(ListConstIterator<T> lhs, size_t count)
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
