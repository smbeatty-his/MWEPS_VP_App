#ifndef TRACER_MODULE_H
#define TRACER_MODULE_H

#include <vuVec4.h>

class vrGeometry;
class vsRenderStrategyFrameGeometry;
class DisaltApp;

class Tracer
{
public:
	Tracer();
	~Tracer();

	vsRenderStrategyFrameGeometry* GetRenderStrategy(void) const { return m_pkRenderStrategy; };
	vrGeometry* GetGeometry(void) const { return m_pkGeometry; };
	void SetVelocity(const float fX, const float fY, const float fZ) { m_pvfVelocity->set(fX, fY, fZ); };
	const vuVec3<float>* GetVelocity(void) const { return m_pvfVelocity; };
	void Initialize(void);
	void EnterScene(vuVec3<float>* vfEntryPoint);
	static void InitializeColor(void) 
	{ 
		s_pvfColor = new vuVec4<float>();
		s_pvfColor->set(1.0f, 1.0f, 1.0f, 1.0f); 
	}
	void Update(const float fTime);

private:

	vrGeometry* m_pkGeometry;
	vsRenderStrategyFrameGeometry* m_pkRenderStrategy;
	vsGeometry* m_pkGeometryNode;
	vuVec3<float>* m_pvfVelocity;
	static vuVec4<float>* s_pvfColor; 
};

#endif