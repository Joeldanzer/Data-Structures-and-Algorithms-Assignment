#pragma once
#include <cfloat>
#include <cstring>

class Astar
{
public:
	Astar() : m_nodes({}) {}

	bool FindPath(const UINT start, const UINT end);

	std::vector<Node>& GetGraph(){
		return m_nodes;
	}


private:
	struct NodeCompare {	
		int   m_f;
		UINT  m_index;
	};

	struct FCompare {
		bool operator()(const NodeCompare& a, const NodeCompare& b) {
			return a.m_f > b.m_f;
		}
	};

	void ReconstructPath(int startIndex, std::vector<std::pair<int, int>> cameFrom, std::vector<int>& outPath);

	int Distance(const UINT& n1, const UINT& n2);
	
	std::vector<Node> m_nodes;
};


