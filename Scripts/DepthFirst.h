#pragma once

class DepthFirst : public Graph
{
public:
	DepthFirst(){}
	bool FindPath(const UINT start, const UINT end) override;
};

