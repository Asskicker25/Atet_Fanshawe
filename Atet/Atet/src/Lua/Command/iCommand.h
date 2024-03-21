#pragma once

class iCommand
{
public:
	iCommand() {};
	virtual ~iCommand() {};

	virtual void Start() = 0;
	virtual void Update(float deltatime) = 0;
	virtual bool IsComplete() = 0;
private:

};

