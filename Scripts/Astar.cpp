#include "stdafx.h"

#include "Astar.h"

#include <queue>

bool Astar::FindPath(const UINT start, const UINT end)
{
    bool finished = false;
    
    // Compares Nodes f value and places the Nodes with the lowest fScore on top of the queue
    std::priority_queue<NodeCompare, std::vector<NodeCompare>, FCompare> openList;

    // Set f & gScore on startNode to 0
    m_nodes[start].m_f = 0;
    m_nodes[start].m_g = 0;

    openList.push({ 0, start });
     
    while (!finished && !openList.empty()) {
        Node& current = m_nodes[openList.top().m_index];
   
        if (!current.m_checked) {
            current.m_checked = true;
            std::cout << "FValue: " << current.m_f << " Index: " << openList.top().m_index << "\n";
            openList.pop();

            if (PositionToArray(current.m_x, current.m_y) == end) {

                std::cout << "Goal found att position x: " << current.m_x << " y: " << current.m_y << "\n";
                finished = true;
                break;
            }

            for (UINT i = 0; i < current.m_neighbours.size(); i++)
            {
                const UINT neighbourIndex = current.m_neighbours[i];
                Node& neighbour           = m_nodes[neighbourIndex];

                const int gNew = current.m_g + 1;
                const int hNew = Distance(neighbourIndex, end);
                const int fNew = gNew + hNew;
            
                // Checks if this neighbour is in the openlist && it's fNew is lower than current f or hasnt been checked before
                if (!neighbour.m_inOpenList && (fNew < neighbour.m_f || !neighbour.m_checked)) {            
                    neighbour.m_inOpenList = true;
                    neighbour.m_f = fNew;
                    neighbour.m_g = gNew;

                    neighbour.m_parent = PositionToArray(current.m_x, current.m_y);
                    openList.push({ neighbour.m_f, neighbourIndex });
                }
            }
        }
        else
            openList.pop();
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
int Astar::Distance(const UINT& n1, const UINT& n2)
{
    int x = fabs(static_cast<float>(m_nodes[n1].m_x) - static_cast<float>(m_nodes[n2].m_x));
    int y = fabs(static_cast<float>(m_nodes[n1].m_y) - static_cast<float>(m_nodes[n2].m_y));
    return x + y;
}

