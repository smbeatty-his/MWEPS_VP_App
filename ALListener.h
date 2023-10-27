#ifndef AL_LISTENER_MODULE_H
#define AL_LISTENER_MODULE_H

class ALListener
{

public:

	ALListener();
	virtual ~ALListener();
	void SetGain(const float fGain);
	const float GetGain(void) const;
	void SetPosition(const float fX, const float fY, const float fZ);
	const float GetPositionX(void) const;
	const float GetPositionY(void) const;
	const float GetPositionZ(void) const;
	void GetPosition(float* fX, float* fY, float* fZ) const;
	void SetVelocity(const float fX, const float fY, const float fZ);
	const float GetVelocityX(void) const;
	const float GetVelocityY(void) const;
	const float GetVelocityZ(void) const;
	void GetVelocity(float* fX, float* fY, float* fZ) const;
	void SetOrientation(float* fOrient);
	void GetOrientation(float* fOrient);

private:

};

#endif