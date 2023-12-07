#pragma once

class BreadthFirst : public Graph
{
public:
	BreadthFirst(){}

	bool FindPath(const UINT start, const UINT end) override;
};

