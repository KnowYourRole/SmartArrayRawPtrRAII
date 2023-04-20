#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>

using namespace std;

/*
1. Implement a SmartArray<T> class that uses dynamic memory
2. Must be RAII, but STL containers/smart pointers are NOT allowed
3. Has size, has index access (with operator[])
4. Can be resized
5. No support for copying/moving or assignment/move assignment
6. Bonus: even more RAII
7. Don’t use (directly) new methods
8. Bonus: enable iteration (e.g. with range-based for loop)
*/

template <typename T>
class SmartArray
{
public:
	class Iterator
	{
	public:
		Iterator(T * data, size_t size, size_t idx)
			: _data(data), _size(size), _idx(idx)
		{}

		Iterator& operator++() { ++_idx; return *this; }

		bool operator !=(const Iterator & other) const
		{
			return _data != other._data || _idx != other._idx;
		}

		T& operator*()
		{
			return _data[_idx];
		}


	private:
		T * _data;
		const size_t _size;
		size_t _idx;
	};

	SmartArray(size_t size)	//RAII part (1) Initialise
		: _data(new T[size] {}),
		_size(size) {}

	//can't copy and assign this class
	SmartArray(const SmartArray & other) = delete;	//No copy constructor
	SmartArray& operator=(const SmartArray & other) = delete;	//No assignement operator

	SmartArray(SmartArray && other) = delete;	//No move constructor
	SmartArray& operator=(SmartArray && other) = delete;	//No move assign operator

	~SmartArray() //RAII part (2) Delete
	{
		delete[] _data;
		_data = nullptr;

	}

	T& operator[](size_t index)	//access elements operator
	{
		if (index >= _size)
			throw("SIZE GUARD ACTIVATED!");
		return _data[index];
	}

	void print() const
	{
		for (size_t i = 0; i < _size; ++i)
			cout << _data[i] << " ";
		cout << endl;
	}

	void resize(size_t newSize)
	{
		T * newData = new T[newSize]{};
		for (size_t i = 0; i < _size && i < newSize; i++)
		{
			newData[i] = _data[i];
		}


		delete[] _data;
		_data = newData;
		_size = newSize;
	}

	Iterator begin()
	{
		return Iterator(_data, _size, 0);
	}

	Iterator end()
	{
		return Iterator(_data, _size, _size);
	}

private:
	T * _data;
	size_t _size;


};

int main()
{

	SmartArray<int> arr(5);
	arr[2] = 45;
	arr.print();

	arr.resize(10);
	arr.print();

	arr.resize(2);
	arr.print();

	cout << "Custom range based for loop: " << endl;
	for (const auto elem : arr)	//we need predefined iterator in SmartARray
	{
		cout << elem << ' ';
	}
	cout << endl;


	return 0;
}
