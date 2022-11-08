
#ifndef JP_LIST
#define JP_LIST

#include <stdexcept>
#include "list_iterator.h"
#include "list_reverse_iterator.h"
#include "list_const_iterator.h"
#include "list_const_reverse_iterator.h"

namespace jp
{
	template <typename T, typename Allocator = std::allocator<T>>
	class List
	{
	public:

		typedef T& reference;
		typedef const T& const_reference;

		typedef ListIterator<T> iterator;
		typedef ListReverseIterator<T> reverse_iterator;
		typedef ListConstIterator<T> const_iterator;
		typedef ListConstReverseIterator<T> const_reverse_iterator;

		List() noexcept;
		List(const List<T, Allocator>& other) noexcept(false);
		List& operator=(const List<T, Allocator>& other) noexcept(false);
		List(List<T, Allocator>&& other) noexcept; // rvalue reference.
		List& operator=(List<T, Allocator>&& other) noexcept;
		~List();

		bool isEmpty() const noexcept;
		void pushFront(const T& value) noexcept(false);
		void pushBack(const T& value) noexcept(false);
		void popFront() noexcept(false);
		void popBack() noexcept(false);

		reference front() noexcept(false);
		const_reference front() const noexcept(false);
		reference back() noexcept(false);
		const_reference back() const noexcept(false);

		iterator begin() noexcept;
		iterator end() noexcept;

		reverse_iterator rbegin() noexcept;
		reverse_iterator rend() noexcept;

		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;

		const_reverse_iterator crbegin() const noexcept;
		const_reverse_iterator crend() const noexcept;

	private:
		ListItem<T>* m_first;
		ListItem<T>* m_last;

		using allocator_type_internal = typename std::allocator_traits<Allocator>::template rebind_alloc<ListItem<T>>;
		allocator_type_internal m_allocator;
	};
}


template <typename T, typename Allocator>
jp::List<T, Allocator>::List() noexcept :
	m_first(nullptr),
	m_last(nullptr)
{
}


template <typename T, typename Allocator>
jp::List<T, Allocator>::List(const jp::List<T, Allocator>& other) noexcept(false)
{
	*this = other;
}


template <typename T, typename Allocator>
jp::List<T, Allocator>& jp::List<T, Allocator>::operator=(const jp::List<T, Allocator>& other) noexcept(false)
{
	ListItem<T>* current = other.m_first;
	ListItem<T>* previous = nullptr;
	while (current)
	{
		ListItem<T>* copy = m_allocator.allocate(1);
		copy->value = current->value;
		copy->next = nullptr;

		if (!previous)
		{
			copy->prev = nullptr;
			m_first = copy;
		}
		else
		{
			copy->prev = previous;
			previous->next = copy;
		}
		m_last = copy;
		previous = copy;
		current = current->next;
	}
	return *this;
}


template <typename T, typename Allocator>
jp::List<T, Allocator>::List(List<T, Allocator>&& other) noexcept :
	m_first(other.m_first),
	m_last(other.m_last)
{
	other.m_first = nullptr;
	other.m_last = nullptr;
}


template <typename T, typename Allocator>
jp::List<T, Allocator>& jp::List<T, Allocator>::operator=(List<T, Allocator>&& other) noexcept
{
	m_first = other.m_first;
	m_last = other.m_last;
	other.m_first = nullptr;
	other.m_last = nullptr;
}


template <typename T, typename Allocator>
jp::List<T, Allocator>::~List()
{
	while (!isEmpty())
	{
		popFront();
	}
}


template <typename T, typename Allocator>
inline bool jp::List<T, Allocator>::isEmpty() const noexcept
{
	return !m_first;
}


template <typename T, typename Allocator>
void jp::List<T, Allocator>::pushFront(const T& value) noexcept(false)
{
	ListItem<T>* item = m_allocator.allocate(1);
	item->value = value;
	item->prev = nullptr;
	if (m_first)
	{
		item->next = m_first;
		m_first->prev = item;
	}
	else
	{
		item->next = nullptr;
		m_last = item;
	}
	m_first = item;
}


template <typename T, typename Allocator>
void jp::List<T, Allocator>::pushBack(const T& value) noexcept(false)
{
	ListItem<T>* item = m_allocator.allocate(1);
	item->value = value;
	item->next = nullptr;
	if (m_last)
	{
		item->prev = m_last;
		m_last->next = item;
	}
	else
	{
		item->prev = nullptr;
		m_first = item;
	}
	m_last = item;
}


template <typename T, typename Allocator>
void jp::List<T, Allocator>::popFront() noexcept(false)
{
	if (isEmpty())
	{
		throw std::runtime_error("Stack underflow");
	}

	ListItem<T>* item = m_first;
	if (m_first->next)
	{
		m_first->next->prev = nullptr;
	}
	else
	{
		m_last = nullptr;
	}
	m_first = m_first->next;
	delete item;
}


template <typename T, typename Allocator>
void jp::List<T, Allocator>::popBack() noexcept(false)
{
	if (isEmpty())
	{
		throw std::runtime_error("Stack underflow");
	}

	ListItem<T, Allocator>* item = m_last;
	if (m_last->prev)
	{
		m_last->prev->next = nullptr;
	}
	else
	{
		m_first = nullptr;
	}
	m_last = m_last->prev;
	delete item;
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::reference jp::List<T, Allocator>::front() noexcept(false)
{
	return const_cast<reference>(const_cast<const List<T, Allocator>*>(this)->front());
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::const_reference jp::List<T, Allocator>::front() const noexcept(false)
{
	if (isEmpty())
	{
		throw std::runtime_error("This container is empty");
	}
	return m_first->value;
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::reference jp::List<T, Allocator>::back() noexcept(false)
{
	return const_cast<reference>(const_cast<const List<T, Allocator>*>(this)->back());
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::const_reference jp::List<T, Allocator>::back() const noexcept(false)
{
	if (isEmpty())
	{
		throw std::runtime_error("This container is empty");
	}
	return m_last->value;
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::iterator jp::List<T, Allocator>::begin() noexcept
{
	return iterator(m_first);
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::iterator jp::List<T, Allocator>::end() noexcept
{
	return iterator(nullptr);
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::reverse_iterator jp::List<T, Allocator>::rbegin() noexcept
{
	return reverse_iterator(m_last);
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::reverse_iterator jp::List<T, Allocator>::rend() noexcept
{
	return reverse_iterator(nullptr);
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::const_iterator jp::List<T, Allocator>::cbegin() const noexcept
{
	return const_iterator(m_first);
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::const_iterator jp::List<T, Allocator>::cend() const noexcept
{
	return const_iterator(nullptr);
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::const_reverse_iterator jp::List<T, Allocator>::crbegin() const noexcept
{
	return const_reverse_iterator(m_last);
}


template <typename T, typename Allocator>
typename jp::List<T, Allocator>::const_reverse_iterator jp::List<T, Allocator>::crend() const noexcept
{
	return const_reverse_iterator(nullptr);
}

#endif
