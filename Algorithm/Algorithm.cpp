#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <stack>
#include <queue>

#pragma region 선형 자료구조
/** 동적 배열 */
template <typename T>
class Vector
{
public:
	~Vector()
	{
		if (_data)
			delete[] _data;
	}

	T& operator[](const int index) { return _data[index]; }

	void push_back(const T& value)
	{
		if (_size == _capacity)
		{
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (_capacity == newCapacity)
				newCapacity++;

			reserve(newCapacity);
		}

		_data[_size] = value;
		_size++;
	}

	void reserve(T capacity)
	{
		if (_size >= capacity) return;

		_capacity = capacity;

		T* tempData = new T[_capacity];

		for (int i = 0; i < _size; ++i)
			tempData[i] = _data[i];

		if (_data)
			delete[] _data;

		_data = tempData;
	}

	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}

		_size = 0;
	}

	int size() { return _size; }
	int capacity() { return _capacity; }

private:
	T* _data = nullptr;
	int _size = 0;
	int _capacity = 0;
};

/** 스택 */
template<typename T>
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		_container.pop_back();
	}

	T& top()
	{
		return _container.back();
	}

	bool empty() { return _container.empty(); }
	int size() { return _container.back(); }

private:
	vector<T> _container;
};

/** 큐 */
template<typename T>
class Queue
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		_container.pop_front();
	}

	T& front()
	{
		return _container.front();
	}

	bool empty() { return _container.empty(); }
	int size() { return _container.size(); }

private:
	list<T> _container;
};

template<typename T>
class ArrQueue
{
public:
	void push(const T& value)
	{
		if (_size == _container.size())
		{
			int newSize = max(1, _size * 2);
			vector<T> newData;
			newData.resize(newSize);
			
			for (int i = 0; i < _size; i++)
			{
				int index = (_front + 1) % _container.size();
				newData[index] = _container[index];
			}

			_container.swap(newData);
			_front = 0;
			_back = _size;
		}

		_container[_back] = value;
		_back = (_back + 1) % _container.size();
		_size++;
	}

	void pop()
	{
		_front = (_front + 1) % _container.size();
		_size--;
	}

	T& front()
	{
		return _container[_front];
	}

	bool empty() { return _size == 0; }
	int size() { return _size; }

private:
	vector<T> _container;
	int _front = 0;
	int _back = 0;
	int _size = 0;
};

#pragma endregion

int main()
{
#pragma region 선형 자료구조
	{
		/** 배열 & 동적 배열 & 연결 리스트 */
		vector<int> v1;
		for (int i = 0; i < 10; i++)
		{
			v1.push_back(i);
			cout << v1[i] << " " << v1.size() << " " << v1.capacity() << endl;
		}
		cout << endl;
		
		Vector<int> v2;
		for (int i = 0; i < 10; i++)
		{
			v2.push_back(i);
			cout << v2[i] << " " << v2.size() << " " << v2.capacity() << endl;
		}

		cout << "---------" << endl;

		/** 스택 */
		// 후입선출 (push pop)
		stack<int> s1;
		s1.push(1);
		s1.push(2);
		s1.push(3);
		if (!s1.empty())
		{
			cout << s1.top() << endl;
			s1.pop();
		}

		stack<int> s2;
		s2.push(1);
		s2.push(2);
		s2.push(3);
		if (!s2.empty())
		{
			cout << s2.top() << endl;
			s2.pop();
		}

		cout << endl << "---------" << endl;

		/** 큐 */
		// 선입선출
		// 원형큐(선형큐)
		queue<int> q1;
		for (int i = 0; i < 10; i++)
			q1.push(i);
		while (!q1.empty())
		{
			int value = q1.front();
			q1.pop();
			cout << value << " ";
		}
		cout << endl;

		Queue<int> q2;
		for (int i = 0; i < 10; i++)
			q2.push(i);
		while (!q2.empty())
		{
			int value = q2.front();
			q2.pop();
			cout << value << " ";
		}

		ArrQueue<int> q3;
		for (int i = 0; i < 10; i++)
			q3.push(i);
		while (!q3.empty())
		{
			int value = q3.front();
			q3.pop();
			cout << value << " ";
		}

		cout << endl << "---------" << endl;
	}
#pragma endregion

#pragma region 그래프
	{

	}
#pragma endregion

#pragma region 힙 & 우선순위 큐
	{

	}
#pragma endregion

#pragma region 이진탐색 트리 & 레드 블랙 트리
	{

	}
#pragma endregion

#pragma region 정렬
	{

	}
#pragma endregion

#pragma region 해시 테이블
	{

	}
#pragma endregion

#pragma region 최소 스패닝 트리 (MST)
	{

	}
#pragma endregion

#pragma region 동적 계획법 (DP)
	{

	}
#pragma endregion
}