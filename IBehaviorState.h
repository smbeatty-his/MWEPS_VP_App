#ifndef IBEHAVIOR_STATE_MODULE_H
#define IBEHAVIOR_STATE_MODULE_H

#include <DebugUtil.h>
#include <ITarget.h>

class IBehaviorState
{
public:

	~IBehaviorState(void) { };
	virtual void Update(const double dTime, ITarget* pkTarget) = 0;
	virtual void OnStateEntry(ITarget* pkTarget) = 0;
	virtual void OnStateExit(ITarget* pkTarget) = 0;

protected:
	IBehaviorState(void) { };

private:
	
};

#endif