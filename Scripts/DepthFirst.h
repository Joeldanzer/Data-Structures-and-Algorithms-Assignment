#pragma once

class DepthFirst
{
public:
	DepthFirst() : m_nodes({}) {}
	bool FindPath(const UINT start, const UINT end);

	std::vector<Node>& GetGraph() {
		return m_nodes;
	}

private:
	std::vector<Node> m_nodes;

};

