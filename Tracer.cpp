#include <vsGeometry.h>
#include <vsRenderStrategy.h>
#include <vrState.h>
#include <vrMode.h>
#include <vpScene.h>
#include <Tracer.h>
#include <vpObserver.h>

#define GRAVITY -9.8f
#define INITIAL_TRACER_VELOCITY vuVec3<float>(0.0f, 1000.0f, 0.0f);

vuVec4<float>* Tracer::s_pvfColor = 0;

Tracer::Tracer()
{
	Initialize();
}

Tracer::~Tracer()
{
	
}

void Tracer::Initialize()
{
	m_pkGeometry = new vrGeometry();
	m_pkGeometry->setPrimitive(vrGeometry::PRIMITIVE_POINT);
	m_pkGeometry->setColors(s_pvfColor, vrGeometry::BINDING_OVERALL);
	m_pkGeometry->setVertices(vuAllocArray<vuVec3<float> >::malloc(1));

	m_pkRenderStrategy = new vsRenderStrategyFrameGeometry(m_pkGeometry, 
								vsRenderStrategyFrameGeometry::ATTRIBUTE_VERTICES);

	m_pvfVelocity = new vuVec3<float>();

    vrState *pkState = new vrState(true);
    vrPoint::Element kPointElement;
    kPointElement.m_enableAntiAlias = true;
    kPointElement.m_size = 2.0f;
    pkState->setElement(vrPoint::Element::Id, &kPointElement);
	
	m_pkGeometryNode = new vsGeometry();
	m_pkGeometryNode->setGeometry(m_pkGeometry);
	m_pkGeometryNode->setState(pkState);
}

void Tracer::Update(const float fTime)
{
	(*m_pvfVelocity)[2] += fTime * GRAVITY;

	vuVec3<float>* pvfVerts = m_pkGeometry->getVertices();

	pvfVerts[0] += *m_pvfVelocity * fTime;

	printf("Tracers Position %f, %f, %f\n", (pvfVerts[0])[0], (pvfVerts[0])[1], (pvfVerts[0])[2]);
}

void Tracer::EnterScene(vuVec3<float>* vfEntryPoint)
{
	(*m_pvfVelocity) = *vfEntryPoint;
	
	printf("Velocity Heading and Pitch %f, %f %f", (*vfEntryPoint)[0], (*vfEntryPoint)[1], (*vfEntryPoint)[2]);

	m_pvfVelocity->normalize();
	*m_pvfVelocity *= 500.0;

	printf("Initial Velocity %f, %f, %f", (*m_pvfVelocity)[0], (*m_pvfVelocity)[1], (*m_pvfVelocity)[2]);

	vuVec3<float>* pvfVerts = m_pkGeometry->getVertices();
	
	double dX, dY, dZ;

	(*vpObserver::begin())->getTranslate(&dX, &dY, &dZ);

	pvfVerts[0] = vuVec3<float>((float) dX, (float) dY, (float) dZ);
	
	vpScene *scene = *vpScene::begin();
	scene->push_back_child(m_pkGeometryNode);
}