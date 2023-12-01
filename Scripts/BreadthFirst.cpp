#include "stdafx.h"
#include "BreadthFirst.h"

#include <queue>

bool BreadthFirst::FindPath(const UINT start, const UINT end)
{
	bool goalFound = false;
	
	Node& goal = m_nodes[end];
	
	std::queue<UINT> nodeQ; // Using UINT instead of a node& or pointer
	nodeQ.emplace(start);
	m_nodes[nodeQ.front()].m_checked = true;

	while (!nodeQ.empty() && !goalFound) {
		Node& node = m_nodes[nodeQ.front()];	

		if (PositionToArray(node.m_x, node.m_y) != end) {
			for (UINT i = 0; i < node.m_neighbours.size(); i++) {
				const UINT nodeIndex = node.m_neighbours[i];
				if (!m_nodes[nodeIndex].m_checked) {
					m_nodes[nodeIndex].m_parent = nodeQ.front();
					m_nodes[nodeIndex].m_checked = true;
					nodeQ.emplace(node.m_neighbours[i]);
				}
			}
		}
		else {
			goalFound = true;		
			std::cout << "Goal found att position x: " << node.m_x << " y: " << node.m_y << "\n";
 		}
		nodeQ.pop();
	}

	if (!goalFound)
		std::cout << "Goal not found! \n";

	return goalFound;
}
