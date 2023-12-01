#include "stdafx.h"

#include "Astar.h"

#include <queue>

bool Astar::FindPath(const UINT start, const UINT end)
{
    bool finished = false;
    
    // Compares Nodes f value and places the Nodes with the lowest fScore on top of the queue
    std::priority_queue<NodeCompare, std::vector<NodeCompare>, FCompare> openList;
    
    // Set f & gScore on startNode to 0
    m_nodes[start].m_f = 0.0f;
    m_nodes[start].m_g = 0.0f;

    openList.push({0.0f, start});
    
    //float fNew = 0.0f;
    //float gNew = 0.0f;
    //float hNew = 0.0f;
    
    while (!finished && !openList.empty()) {
        Node& current = m_nodes[openList.top().m_index];
        current.m_checked = true;
        openList.pop();

        for (UINT i = 0; i < current.m_neighbours.size(); i++)
        {
            const UINT neighbourIndex = current.m_neighbours[i];
            if (neighbourIndex == end) {
                Node& neighbour = m_nodes[neighbourIndex];
                neighbour.m_parent = PositionToArray(current.m_x, current.m_y);

                std::cout << "Goal found att position x: " << neighbour.m_x << " y: " << neighbour.m_y << "\n";

                finished = true;
            }
            else {
                Node& neighbour = m_nodes[neighbourIndex];

                const float gNew = current.m_g + 1.0f;
                const float hNew = Distance(neighbourIndex, end);
                const float fNew = gNew + hNew;

                if (fNew < neighbour.m_f) {
                    neighbour.m_f = fNew;
                    neighbour.m_g = gNew;

                    neighbour.m_parent = PositionToArray(current.m_x, current.m_y);
                    openList.push({ neighbour.m_f, neighbourIndex });
                }
            }
        }            
    }
    
    if (!finished)
        std::cout << "No Path Found! \n";

    return finished;
}


void Astar::ReconstructPath(int startIndex, std::vector<std::pair<int, int>> closedList, std::vector<int>& outPath)
{
    std::pair<int, int> current = closedList[closedList.size() - 1];
    outPath.emplace_back(current.first);

    // Loop through the closedList list and add the coordinate index to outPath
    while (current.second != 0) {
        current = closedList[current.second];
        outPath.insert(outPath.begin(), current.first);
    }
}
float Astar::Distance(const UINT& n1, const UINT& n2)
{
    float x = fabs(static_cast<float>(m_nodes[n1].m_x) - static_cast<float>(m_nodes[n2].m_x));
    float y = fabs(static_cast<float>(m_nodes[n1].m_y) - static_cast<float>(m_nodes[n2].m_y));
    return x + y;
}

