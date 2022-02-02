#ifndef SIMPLE_LIST
#define SIMPLE_LIST

#include <cstdio>
#include <cstddef>
#include <cstdlib>

const size_t LIST_SIZE = 10;

template <typename list_type> class List
{
private:
	
	list_type *array;

	size_t capacity;
	size_t length;

public:

	List()
	{
		// array = (list_type*)calloc(LIST_SIZE, sizeof(list_type));
		array = new list_type[LIST_SIZE];

		if (array)
		{
			capacity = LIST_SIZE;
			length = 0;
		}
	}

	List(size_t par_capacity)
	{
		array = new list_type[par_capacity];

		if (array)
		{
			capacity = par_capacity;
			length = 0;
		}
	}

	~List()
	{
		delete [] array;
	}

	list_type *get_array() { return array; }
	size_t     get_length() { return length; }

	void resize()
	{
		size_t new_capacity = capacity * 2;
		
		list_type *other_array = new list_type[new_capacity];
		for (size_t i = 0; i < length; ++i)
			other_array[i] = array[i];
		delete [] array;

		array = other_array;
		capacity = new_capacity;
	}

	void add_to_end(const list_type value)
	{
		if (length >= capacity - 1)
			resize();

		array[length++] = value;
	}

	void delete_from_end()
	{
		if (length <= 0)
			return;

		delete array[length - 1];
		length--;
	}

	void extract_from_end()
	{
		if (length <= 0)
			return;

		length--;
	}

	void slow_delete(size_t index)
	{
		if (index >= length)
			return;

		delete array[index];
		for (size_t i = index + 1; i < length; ++i)
		{
			array[i - 1] = array[i];
		}

		length--;
	}

	void extract(size_t index)
	{
		if (index >= length)
			return;

		for (size_t i = index + 1; i < length; ++i)
		{
			array[i - 1] = array[i];
		}

		length--;
	}
};

#endif // SIMPLE_LIST
