#pragma once
#include <vector>
#include <string>
#include <Windows.h>

struct Node {
	UINT m_x = 0;
	UINT m_y = 0;

	std::vector<UINT> m_neighbours;
};

class BreadthFirst
{
public:
	BreadthFirst() : m_nodes({}), m_width(0), m_height(0) {}

	const std::array<UINT, 2> ConstrucGraph(std::string fileName);
	void FindPath(const UINT start, const UINT end);

private:
	std::vector<UINT> GetNodeNeighbours(const UINT x, const UINT y);

	UINT m_width, m_height;
	std::vector<Node> m_nodes;
};

