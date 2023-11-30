#pragma once
#include <vector>
#include <string>
#include <Windows.h>

struct Node {
	UINT m_x = 0;
	UINT m_y = 0;

	std::vector<UINT> m_neighbours;

	int  m_parent  = -1;
	int  m_valid   = -1;
	bool m_checked = false;

	bool operator!=(const Node& node) { // Checks if it is the same node
		UINT x = m_x != node.m_x ? 1 : 0;
		UINT y = m_y != node.m_y ? 1 : 0;

		return x + y != 0;
	}
};

class BreadthFirst
{
public:
	BreadthFirst() : m_nodes({}), m_width(20), m_height(20) {}

	const std::array<UINT, 2> ConstrucGraph(const char* arr, const UINT size);
	bool FindPath(const UINT start, const UINT end);

	void PrintPath(const UINT start, const UINT end);

private:
	std::vector<UINT> GetNodeNeighbours(const UINT x, const UINT y, const char* charNodes);

	const UINT m_width;
	const UINT m_height;
	std::vector<Node> m_nodes;
};

