#include "stdafx.h"
#include "DepthFirst.h"

#include <stack>

const std::array<UINT, 2> DepthFirst::ConstructGraph(const char* charNodes, const UINT size)
{
	std::array<UINT, 2> returnNodes = { 0, 0 };

	for (UINT y = 0; y < m_height; y++)
	{
		for (UINT x = 0; x < m_width; x++)
		{
			Node node = { x, y, {} };
			const char c = charNodes[y * m_width + x];
			if (c == 'o' || c == 'S' || c == 'G') { // Will return start and goal node 
				node.m_valid = 1;
				node.m_neighbours = GetNodeNeighbours(x, y, &charNodes[0]);
				m_nodes.emplace_back(node);

				if (c == 'S')
					returnNodes[0] = y * m_width + x;
				if (c == 'G')
					returnNodes[1] = y * m_width + x;
			}
			else {
				m_nodes.emplace_back(node);
			}
		}
	}


	return returnNodes;
}

bool DepthFirst::FindPath(const UINT start, const UINT end)
{
	bool goalFound = false;

	Node& goal = m_nodes[end];

	std::stack<UINT> nodeStack; // Using UINT instead of a node& or pointer
	nodeStack.push(start);

	int parent = -1;

	while (!nodeStack.empty() && !goalFound) {
		Node& node = m_nodes[nodeStack.top()];
		nodeStack.pop();
	
		if (!node.m_checked) {
			node.m_checked = true;
			parent = node.m_y * m_width + node.m_x;

			if (node != goal) {
				for (UINT i = 0; i < node.m_neighbours.size(); i++) {
					const UINT nodeIndex = node.m_neighbours[i];
					if (m_nodes[nodeIndex].m_parent == -1)
						m_nodes[nodeIndex].m_parent = parent;
					nodeStack.push(nodeIndex);
				}
			}
			else {
				goalFound = true;
				std::cout << "Goal found att position x: " << node.m_x << " y: " << node.m_y << "\n";
			}

		}
				
	}

	if (!goalFound)
		std::cout << "Goal not found! \n";

	return goalFound;
}

void DepthFirst::PrintPath(const UINT start, const UINT end)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	Node currentNode = m_nodes[end];

	std::vector<UINT> backTrack;

	//m_nodes[start].m_parent = -1;

	while (currentNode.m_parent != start) {
		backTrack.emplace_back(currentNode.m_parent);
		currentNode = m_nodes[currentNode.m_parent];
	}

	UINT x = 0;
	for (UINT i = 0; i < m_nodes.size(); i++)
	{
		if (i == start) {
			SetConsoleTextAttribute(console, 10);
			std::cout << " S ";
		}
		else if (i == end) {
			SetConsoleTextAttribute(console, 10);
			std::cout << " G ";
		}
		else {
			bool isBackTracked = false;
			for (UINT j = 0; j < backTrack.size(); j++)
				if (i == backTrack[j])
					isBackTracked = true;

			if (isBackTracked)
				SetConsoleTextAttribute(console, 11);
			else if (m_nodes[i].m_checked)
				SetConsoleTextAttribute(console, 12);
			else
				SetConsoleTextAttribute(console, 15);

			if (m_nodes[i].m_valid == -1)
				std::cout << " X ";
			else
				std::cout << " o ";

		}

		x++;
		if (x > m_width - 1) {
			x = 0;
			std::cout << "\n";
		}

	}


}

std::vector<UINT> DepthFirst::GetNodeNeighbours(const UINT x, const UINT y, const char* charNodes)
{
	std::vector<UINT> neighbours;
	const UINT index = y * m_width + x;

	if (x > 0)
		if (charNodes[index - 1] != 'X')
			neighbours.emplace_back(index - 1);

	if (x < m_width - 1)
		if (charNodes[index + 1] != 'X')
			neighbours.emplace_back(index + 1);

	if (y > 0)
		if (charNodes[index - (m_width)] != 'X')
			neighbours.emplace_back(index - (m_width));

	if (y < m_height - 1)
		if (charNodes[index + (m_width)] != 'X')
			neighbours.emplace_back(index + (m_width));

	return neighbours;
}