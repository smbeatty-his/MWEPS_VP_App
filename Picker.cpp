#include <DebugUtil.h>
#include <vuAllocTracer.h>
#include <vuMath.h>
#include <vrLight.h>
#include <vrMode.h>
#include <vrRenderStrategy.h>
#include <vrDrawContext.h>
#include <vsDOF.h>
#include <vsLOD.h>
#include <vpInputMouse.h>
#include <vpIsectorLOS.h>
#include <vpMotionUFO.h>
#include <vpObject.h>
#include <vpObserver.h>
#include <Picker.h>



Picker::Picker(vpScene *scene, uint mask)
{
	// set the parameters to their default values
    m_mode = MODE_OBJECT;
    m_isector = new vpIsectorLOS();
    m_isector->setTarget(scene);
    m_isector->setIsectMask(mask);
	m_isector->ref();
}

Picker::~Picker(void)
{
	m_isector->unref();
}

vsNode* Picker::Pick(vpChannel *pkChannel, const float mx, const float my)
{
	float n, f;
    double x, y, z, h, p, r = 0.0, range;
    const vuMatrix<double> &viewMat = pkChannel->getViewMatrix();
    pkChannel->getNearFar(&n, &f);

    // if we've got an orthographic projection, then things are easy.
    // In this case the mouse position gives us the xy location within
    // the orthographic frustum and our isector will run from the near
    // to the far clipping plane.
    if (pkChannel->getProjection() == vrChannel::PROJECTION_ORTHOGRAPHIC) 
	{
       float l, r, b, t;
       pkChannel->getFrustum(&l, &r, &b, &t);

       x = l + ((mx + 1.0f) * 0.5f) * (r - l);
       y = b + ((my + 1.0f) * 0.5f) * (t - b);
       z = viewMat[3][2] + n;
       h = 0.0;
       p = -90.0;
       range = f - n;

     }

     // if we've got a perspective projection, then things are a little
     // more difficult
     else 
	 {

		 // transform the mouse position, which is in normalized channel
		 // screen space, back into world space.  In order to accomplish
		 // this, we need to "undo" the projection and graphics library
		 // specific offset transformations by transforming the point
		 // through the inverse of their respective matrices.  This gives
		 // us the mouse position in the eye's coordinate system.  Then a
		 // final transformation through the view matrix will put us into
		 // world coordinates.  Note that in the initial transformation
		 // that the Z coordinate doesn't matter since the inverse of the
		 // projection transformation "ignores" it.
		 vuVec3<float> mouse(mx, my, -1);
		 vuVec3<double> vec;
		 vuMatrix<float> projInv;
		 projInv.invert(pkChannel->getVrChannel()->getProjectionMatrix());
		 projInv.transformPoint(&mouse);
		 pkChannel->getVrChannel()->getOffsetMatrixInverse().transformPoint(&mouse);
		 pkChannel->getVrChannel()->getViewMatrix().transformPoint(&mouse);

		 // create a vector from the eye point through the mouse position
		 x = viewMat[3][0];
         y = viewMat[3][1];
         z = viewMat[3][2];

         vec[0] = mouse[0] - x;
         vec[1] = mouse[1] - y;
         vec[2] = mouse[2] - z;

         // calculate the heading and pitch of this vector
         h = vuRad2Deg(vuArcTan(-vec[0], vec[1]));
         p = vuRad2Deg(vuArcTan(vec[2], vuSqrt(vuSq(vec[0]) + vuSq(vec[1]))));

         range = 2 * f;

	}

    // update the isector to align w/ the vector
    m_isector->setTranslate(x, y, z);
    m_isector->setRotate(h, p, 0.0);
	m_isector->setSegmentRange(range);

    // perform the intersection test and see if we hit anything
    vsNode *node = NULL;
	m_isector->update();

    if (m_isector->getHit()) 
	{
		switch(m_mode) 
		{

            case MODE_OBJECT: // pick the object
                node = m_isector->getHitObject();
                break;

            case MODE_GEOMETRY: // pick the geometry
                node = m_isector->getHitNode();
                break;

            case MODE_DOF: // pick the dof
                node = GetParent(m_isector->getHitNode(), vsDOF::getStaticClassType());
                if(node == NULL)
                    printf("Geometry is not parented by a DOF node\n");
                break;

            case MODE_LOD: // pick the lod
                // if we don't have a parent whose a lod, return the hit geometry
                node = GetParent(m_isector->getHitNode(), vsLOD::getStaticClassType());
                if(node == NULL)
                    printf("Geometry is not parented by a LOD node\n");
                break;

		}

	}

	return node;
}

vuVec3<double>* Picker::MouseCoordsToMouseRotationVector(vpChannel *pkChannel, const float fMX, const float fMY)
{
	vuMatrix<float> matfProjInv;
	vuVec3<float> vfMousePos = vuVec3<float>(fMX, fMY, -1);
	matfProjInv.invert(pkChannel->getVrChannel()->getProjectionMatrix());
	matfProjInv.transformPoint(&vfMousePos);
	pkChannel->getVrChannel()->getOffsetMatrixInverse().transformPoint(&vfMousePos);
	pkChannel->getVrChannel()->getViewMatrix().transformPoint(&vfMousePos);

	const vuMatrix<double> &viewMat = pkChannel->getViewMatrix();

	vuVec3<double> vec;

    vec[0] = vfMousePos[0] - viewMat[3][0];
    vec[1] = vfMousePos[1] - viewMat[3][1];
    vec[2] = vfMousePos[2] - viewMat[3][2];

	double dHeading = vuRad2Deg(vuArcTan(-vec[0], vec[1]));
	double dPitch = vuRad2Deg(vuArcTan(vec[2], vuSqrt(vuSq(vec[0]) + vuSq(vec[1]))));

	return new vuVec3<double>(dHeading , dPitch, 0.0);
}