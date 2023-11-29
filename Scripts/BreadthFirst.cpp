#include "stdafx.h"
#include "BreadthFirst.h"

#include <fstream>
#include <sstream>

const std::array<UINT, 2> BreadthFirst::ConstrucGraph(std::string fileName)
{
	std::array<UINT, 2> returnNodes = {0, 0};

	std::ifstream file(fileName);
	if (file.is_open()) {
		std::string line;

		UINT y = 0;
		UINT x = 0;

		while (std::getline(file, line)) {
			if (line.find_first_of("L") != std::string::npos)
				break;
			
			m_width = m_width == 0 ? m_width = line.size() : 0;

			for (UINT i = 0; i < line.size(); i++)
			{
				char c = line[i];
				if (c == 'o' || c == 'S' || c == 'G') { // Will return start and goal node 
					Node node		  = { x, y, {} };
					node.m_neighbours = GetNodeNeighbours(x, y);
					m_nodes.emplace_back(node);

					if (c == 'S')
						returnNodes[0] = y * m_width + x;
					if (c == 'G')
						returnNodes[1] = y * m_width + x;
				}
				x++;
			}

			y++;
			x = 0;
		}
	}
	else {
		std::cout << "Could not open: " << fileName;
		return std::array<UINT, 2>();
	}

	return returnNodes;
}

void BreadthFirst::FindPath(const UINT start, const UINT end)
{
	bool pathFound = false;

	while (!pathFound) {
		
	}
}

std::vector<UINT> BreadthFirst::GetNodeNeighbours(const UINT x, const UINT y)
{
	std::vector<UINT> neighbours;

	const UINT index = y * m_width + x;

	if (x > 0)
		neighbours.emplace_back(index - 1);

	if (x < m_width - 1)
		neighbours.emplace_back(index + 1);

	if (y > 0)
		neighbours.emplace_back(index - m_width);

	if (y < m_height - 1)
		neighbours.emplace_back(index + m_width);

	return neighbours;
}
