#pragma once

class State
{
public:
	 State() {}
	~State() {}

	virtual bool Update(float frame_time) = 0;
	virtual void Render() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual const char* getName() = 0;

private:
	
};

