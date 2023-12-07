#pragma once
#include <cfloat>
#include <cstring>

class Astar : public Graph
{
public:
	Astar(){}

	bool FindPath(const UINT start, const UINT end) override;

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

	int Distance(const UINT& n1, const UINT& n2);
};


