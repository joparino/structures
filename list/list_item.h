
#ifndef JP_LIST_ITEM
#define JP_LIST_ITEM

namespace jp
{
	template <typename T>
	struct ListItem
	{
		T value;
		ListItem<T>* prev;
		ListItem<T>* next;
	};
}

#endif
