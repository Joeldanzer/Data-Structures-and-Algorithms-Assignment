#include "stdafx.h"

#include "DepthFirst.h"
#include <stack>

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
			parent = PositionToArray(node.m_x, node.m_y);

			if (PositionToArray(node.m_x, node.m_y) != end) {
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
