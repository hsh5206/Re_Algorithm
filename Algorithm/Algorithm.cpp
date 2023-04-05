#include <iostream>
using namespace std;

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>

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

#pragma region 그래프
void CreateGraph_1()
{
	// 정점이 연결 유무를 관리
	struct Vertex
	{
		vector<Vertex*> edges;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);
}
void CreateGraph_2()
{
	// 연결 목록을 따로 관리

	// 1
	vector<vector<int>> adjacent1(6);
	adjacent1[0] = { 1, 3 };
	adjacent1[1] = { 0, 2, 3 };
	adjacent1[3] = { 4 };
	adjacent1[5] = { 4 };

	// 2
	// [0][1][0][1][0][0]
	// [1][0][1][1][0][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][1][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][1][0]
	vector<vector<bool>> adjacent2(6, vector<bool>(6, false));
	adjacent2[0][1] = true;
	adjacent2[0][3] = true;
	adjacent2[1][0] = true;
	adjacent2[1][2] = true;
	adjacent2[1][3] = true;
	adjacent2[3][4] = true;
	adjacent2[5][4] = true;
	// 가중치 : bool값 => 가중치
}

vector<bool> visited(6, false);
vector<vector<int>> adjList;
vector<vector<int>> adjMatrix;
vector<vector<int>> adjMatrix_Dikjstra;

void ResetGraph()
{
	adjList = vector<vector<int>>(6);
	adjList[0].push_back(1);
	adjList[0].push_back(3);
	adjList[1].push_back(0);
	adjList[1].push_back(2);
	adjList[1].push_back(3);
	adjList[3].push_back(4);
	adjList[5].push_back(4);

	adjMatrix = vector<vector<int>>
	{
		{0, 1, 0, 1, 0, 0},
		{1, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0}
	};

	adjMatrix_Dikjstra = vector<vector<int>>(6, vector<int>(6, -1));
	adjMatrix_Dikjstra[0][1] = 15;
	adjMatrix_Dikjstra[0][3] = 35;
	adjMatrix_Dikjstra[1][0] = 15;
	adjMatrix_Dikjstra[1][2] = 5;
	adjMatrix_Dikjstra[1][3] = 10;
	adjMatrix_Dikjstra[3][4] = 5;
	adjMatrix_Dikjstra[5][4] = 5;

	visited = vector<bool>(6, false);
}

void DFS(int here)
{
	visited[here] = true;
	cout << "Visited : " << here << endl;

	// 인접리스트 버전
	/*for (int i = 0; i < adjList[here].size(); i++)
	{
		int there = adjList[here][i];
		if (!visited[there])
			DFS(there);
	}*/

	// 인접행렬  버전
	for (int there = 0; there < 6; there++)
	{
		if (adjMatrix[here][there] == 0)
			continue;

		if (visited[there] == false)
			DFS(there);
	}
}

void BFS(int here)
{
	queue<int> q;
	q.push(here);
	visited[here] = true;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "Visited : " << here << endl;
		for (int i = 0; i < adjList[here].size(); i++)
		{
			if (visited[adjList[here][i]])
				continue;
			q.push(adjList[here][i]);
			visited[adjList[here][i]] = true;
		}
	}
}

void Dijkstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};
	list<VertexCost> discovered;
	vector<int> best(6, INT32_MAX);
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	
	// 우선순위 큐로 실행해야 함
	while (discovered.empty() == false)
	{
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			const int cost = it->cost;
			if (cost < bestCost)
			{
				bestCost = cost;
				bestIt = it;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		if (best[here] < cost)
			continue;

		for (int there = 0; there < 6; there++)
		{
			if (adjMatrix_Dikjstra[here][there] == -1)
				continue;
			int nextCost = best[here] + adjMatrix_Dikjstra[here][there];
			if (nextCost >= best[there])
				continue;

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}
}
#pragma endregion

#pragma region 트리 & 힙 & 우선순위 큐
/** 트리 */
using NodeRef = shared_ptr<struct Node>;
struct Node
{
	Node() {}
	Node(const string& data) :data(data) {}
	string data;
	vector<NodeRef> children;
};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}

		node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서브");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}

		node = make_shared<Node>("아트팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->children.push_back(leaf);
		}
	}

	return root;
}
void PrintTree(NodeRef root, int depth = 0)
{
	for (int i = 0; i < depth; i++)
		cout << "-";
	cout << root->data << endl;
	for (NodeRef& child : root->children)
		PrintTree(child, depth+1);
}
int GetHeight(NodeRef root)
{
	int height = 1;
	for (NodeRef& child : root->children)
	{
		height = max(height, GetHeight(child) + 1);
	}
	return height;
}

/** 우선순위 큐 */
template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data)
	{
		_heap.push_back(data);

		int now = static_cast<int>(_heap.size()) - 1;
		while (now > 0)
		{
			// 부모와 비교
			int parent = (now - 1) / 2;
			/*if (_heap[now] < _heap[parent])
				break;*/
			if (_predicate(_heap[now], _heap[parent]))
				break;

			// 교체
			::swap(_heap[now], _heap[parent]);
			now = parent;
		}
	}

	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();
		
		int now = 0;
		while (true)
		{
			int left = now * 2 + 1;
			int right = now * 2 + 2;
			
			if (left >= _heap.size())
				break;

			int next = now;
			
			if (_predicate(_heap[next], _heap[left]))
				next = left;

			if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
				next = right;

			if (next == now)
				break;
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}

private:
	Container _heap = {};
	Predicate _predicate = {};
};
#pragma endregion

#pragma region 이진탐색 트리 & 레드블랙 트리
/** 이진탐색 */
vector<int> numbers(10);
void BinarySearch(int N)
{
	int left = 0;
	int right = numbers.size() - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;

		if (N < numbers[mid])
		{
			right = mid - 1;
		}

		else if (N < numbers[mid])
		{
			left = mid + 1;
		}

		else
		{
			cout << "Find!" << endl;
			break;
		}
	}
}

/** 이진탐색 트리 */
struct NodeBST
{
	NodeBST* parent = nullptr;
	NodeBST* left = nullptr;
	NodeBST* right = nullptr;
	int key = {};
};

class BinarySearchTree
{
public:
	void Print_InOrder() { Print_InOrder(_root); }
	void Print_InOrder(NodeBST* node)
	{
		if (node == nullptr)
			return;

		// 전위 순회 (preorder)
		// cout << node->key << endl;
		// Print_InOrder(node->left);
		// Print_InOrder(node->right);

		// 중위 순회 (inorder)
		// Print_InOrder(node->left);
		// cout << node->key << endl;
		// Print_InOrder(node->right);

		// 후위 순회 (postorder)
		// Print_InOrder(node->left);
		// Print_InOrder(node->right);
		// cout << node->key << endl;

		cout << node->key << endl;
		Print_InOrder(node->left);
		Print_InOrder(node->right);
	}

	void Insert(int key)
	{
		NodeBST* newNode = new NodeBST();
		newNode->key = key;

		if (!_root)
		{
			_root = newNode;
			return;
		}

		NodeBST* node = _root;
		NodeBST* parent = nullptr;

		while (node)
		{
			parent = node;
			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}

		newNode->parent = parent;
		if (key < parent->key)
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	void Delete(int key)
	{
		NodeBST* deleteNode = Search(_root, key);
		Delete(deleteNode);
	}
	void Delete(NodeBST* node)
	{
		if (node == nullptr)
			return;

		if (node->left == nullptr)
			Replace(node, node->right);
		else if (node->right == nullptr)
			Replace(node, node->left);
		else
		{
			NodeBST* next = Next(node);
			node->key = next->key;
			Delete(next);
		}
	}

	void Replace(NodeBST* u, NodeBST* v)
	{
		if (u->parent == nullptr)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;

		if (v)
			v->parent = u->parent;

		delete u;
	}

	NodeBST* Search(NodeBST* node, int key)
	{
		if (node == nullptr || key == node->key)
			return node;

		if (key < node->key)
			return Search(node->left, key);
		else
			return Search(node->right, key);
	}
	NodeBST* Search2(NodeBST* node, int key)
	{
		while (node && key != node->key)
		{
			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}
		return node;
	}

	NodeBST* Min(NodeBST* node)
	{
		while (node->left)
			node = node->left;

		return node;
	}
	NodeBST* Max(NodeBST* node)
	{
		while (node->right)
			node = node->right;

		return node;
	}
	NodeBST* Next(NodeBST* node)
	{
		if (node->right)
			return Min(node->right);
		
		NodeBST* parent = node->parent;
		while (parent && node == parent->right)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
private:
	NodeBST* _root = nullptr;
};
#pragma endregion

#pragma region 정렬
/** 버블 정렬 : O(N^2) */
void BubbleSort(vector<int>& v)
{
	const int n = v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (v[j] > v[j + 1])
			{
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}

/** 선택 정렬 : O(N^2) */
void SelectionSort(vector<int>& v)
{
	const int n = v.size();
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[min])
				min = j;
		}

		int temp = v[i];
		v[i] = v[min];
		v[min] = temp;
	}
}

/** 삽입 정렬 : O(N^2) */
void InsertionSort(vector<int>& v)
{
	const int n = v.size();
	for (int i = 1; i < n; i++)
	{
		int data = v[i];
		int j;
		for (j = i-1; j >= 0; j--)
		{
			if (v[j] > data)
				v[j + 1] = v[j];
			else
				break;
		}
		v[j + 1] = data;
	}
}

/** 힙 정렬 : O(NlogN)*/
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int num : v)
		pq.push(num);

	v.clear();

	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}

/** 병합 정렬 : O(NlogN) */
void MergeResult(vector<int>& v, int left, int mid, int right)
{
	vector<int> temp;
	int leftIndex = left;
	int rightIndex = mid + 1;

	while (leftIndex <= mid && rightIndex <= right)
	{
		if (v[leftIndex] <= v[rightIndex])
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
		else
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}
	else
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
		v[left + i] = temp[i];
}
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

/** 퀵 정렬 : O(NlogN)~O(N^2) */
int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;
		while (high >= left + 1 && pivot <= v[high])
			high--;

		if (low < high)
			::swap(v[low], v[high]);
	}

	::swap(v[left], v[high]);

	return high;
}
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}
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
		/** 그래프 
		* 정점(Vertex), 간선(Edge)
		* 기본 그래프
		* 가중치 그래프
		* 방향 그래프
		*/

		/** 표현
		* 인접리스트
		* 인접행렬
		*/
		

		/** 그래프 탐색
		* 깊이우선탐색(DFS)
		* 너비우선탐색(BFS)
		*/

		/** DFS */
		ResetGraph();
		DFS(0);
		cout << endl;

		/** BFS */
		ResetGraph();
		BFS(0);
		cout << endl;

		/** 다익스트라 
		* 한점에서 모든점으로의 최단거리
		* 비용이 가장 낮은 애들 부터 방문
		* 우선순위 큐 사용
		*/
		ResetGraph();
		Dijkstra(0);

		cout << "---------" << endl;
	}
#pragma endregion

#pragma region 트리 & 힙 & 우선순위 큐
	{
		/** 트리
		* 노드와 간선으로 이루어진 계층구조
		*/
		{
			NodeRef root = CreateTree();
			PrintTree(root);
			cout << "높이 : " << GetHeight(root) << endl;
			cout << "---------" << endl;
		}

		/** 힙
		* 부모노드는 항상 자식노드보다 큼
		* 트리는 위, 왼쪽부터 채워나감
		* < 배열로 표현가능 >
		* i의 왼쪽자식 : [2*i +1]
		* i의 오른쪽자식 : [2*i + 2]
		* i의 부모 : [(i-1) / 2]
		*/

		/** 우선순위 큐
		* 기본적으로 큰값
		*/
		{
			// priority_queue<int> pq1;
			priority_queue<int, vector<int>, greater<int>> pq1; // 작은 순서
			pq1.push(100);
			pq1.push(200);
			pq1.push(300);
			pq1.push(400);
			pq1.push(500);
			while (!pq1.empty())
			{
				int value = pq1.top();
				pq1.pop();

				cout << value << endl;
			}
			cout << endl;

			PriorityQueue<int, vector<int>, greater<int>> pq2;
			pq2.push(100);
			pq2.push(200);
			pq2.push(300);
			pq2.push(400);
			pq2.push(500);
			while (!pq2.empty())
			{
				int value = pq2.top();
				pq2.pop();

				cout << value << endl;
			}

			cout << "---------" << endl;

		}

		/** A*알고리즘
		* 길찾기 알고리즘
		*/
	}
#pragma endregion

#pragma region 이진탐색 트리 & 레드블랙 트리
	{
		/** 이진 탐색
		* 배열에 데이터가 정렬되어 있음
		* log N의 시간 복잡도
		*/
		srand(static_cast<unsigned>(time(nullptr)));
		for (int i = 0; i < 10; i++)
		{
			numbers[i] = rand() % 100;
		}
		int WantToFind = 34;
		numbers[7] = WantToFind;
		::sort(numbers.begin(), numbers.end());
		for (int i = 0; i < 10; i++)
			cout << numbers[i] << " ";

		cout << endl << WantToFind << " : ";
		BinarySearch(WantToFind);

		cout << "---------" << endl;
	}

	{
		/** 이진탐색 트리
		* 이진탐색에서 데이터의 삽입삭제가 빈번할 경우 사용
		*/
		BinarySearchTree bst;
		bst.Insert(10);
		bst.Insert(20);
		bst.Insert(30);
		bst.Print_InOrder();
	}

	{
		/** 레드블랙 트리
		* 이진탐색 트리에서 left와 right의 균형을 유지하기 위함
		* (1) 모든 노드들은 Red or Black
		* (2) 루트는 Black
		* (3) 리프(NIL)는 Black
		* (4) Red 노드의 자식은 Black (Red의 연속X)
		* (5) 각 노드로부터 - 리프까지 가는 경로들은 모두 같은 수의 Black
		*/

		cout << "---------" << endl;
	}
#pragma endregion

#pragma region 정렬
	// O(N^2)
	{
		/** 버블 정렬 */
		vector<int> v(10);
		srand(static_cast<unsigned>(time(nullptr)));
		for (int i = 0; i < 10; i++)
		{
			v[i] = rand() % 100;
		}
		cout << "정렬 전  : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		BubbleSort(v);

		cout << endl << "버블정렬 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		cout << endl << "---------" << endl;

		/** 선택 정렬 */
		v = vector<int>(10);
		srand(static_cast<unsigned>(time(nullptr)));
		for (int i = 0; i < 10; i++)
		{
			v[i] = rand() % 100;
		}
		cout << "정렬 전  : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		SelectionSort(v);

		cout << endl << "선택정렬 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		cout << endl << "---------" << endl;

		/** 삽입 정렬 */
		v = vector<int>(10);
		srand(static_cast<unsigned>(time(nullptr)));
		for (int i = 0; i < 10; i++)
		{
			v[i] = rand() % 100;
		}
		cout << "정렬 전  : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		InsertionSort(v);

		cout << endl << "삽입정렬 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		cout << endl << "---------" << endl;
	}

	// O(NlogN)
	{
		/** 힙 정렬 */
		vector<int> v(10);
		srand(static_cast<unsigned>(time(nullptr)));
		for (int i = 0; i < 10; i++)
		{
			v[i] = rand() % 100;
		}
		cout << "정렬 전 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		HeapSort(v);

		cout << endl << "힙 정렬 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		cout << endl << "---------" << endl;

		/** 병합 정렬 */
		// 분할 정복
		// - 분할	문제를 더 단순하게 분할
		// - 정복	분할된 문제를 해결
		// - 결합	결과를 취합하여 마무리
		v = vector<int>(10);
		srand(static_cast<unsigned>(time(nullptr)));
		for (int i = 0; i < 10; i++)
		{
			v[i] = rand() % 100;
		}
		cout << "정렬 전  : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		MergeSort(v, 0, v.size() - 1);

		cout << endl << "병합정렬 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		cout << endl << "---------" << endl;
	}

	// O(NlogN) ~ O(N^2)
	{
		/** 퀵 정렬 */
		// pivot을 기준점으로 분할정복
		vector<int> v(10);
		srand(static_cast<unsigned>(time(nullptr)));
		for (int i = 0; i < 10; i++)
		{
			v[i] = rand() % 100;
		}
		cout << "정렬 전 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		QuickSort(v, 0, v.size() - 1);

		cout << endl << "퀵 정렬 : ";
		for (int i = 0; i < 10; i++)
			cout << v[i] << " ";

		cout << endl << "---------" << endl;
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