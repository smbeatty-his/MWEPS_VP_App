#ifndef DEFAULT_BEHAVIOR_STATE_H
#define DEFAULT_BEHAVIOR_STATE_H

#include <IBehaviorState.h>

class DefaultBehaviorState : public IBehaviorState
{
public:

	~DefaultBehaviorState(void);

	static inline void Initialize(void)
	{
		ASSERT(! s_pkInstance)
		s_pkInstance = new DefaultBehaviorState();
	}

	static inline DefaultBehaviorState* GetInstance(void)
	{
		ASSERT(s_pkInstance)
		return s_pkInstance;
	}

	static inline void Shutdown(void)
	{
		ASSERT(s_pkInstance)
		delete s_pkInstance;
	}

	virtual void Update(const double dTime, ITarget* pkTarget);
	virtual void OnStateEntry(ITarget* pkTarget);
	virtual void OnStateExit(ITarget* pkTarget);

private:

	DefaultBehaviorState(void);

	static DefaultBehaviorState* s_pkInstance;
};

#endif