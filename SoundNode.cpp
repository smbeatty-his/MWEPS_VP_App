#include <al.h>
#include <ALSource.h>
#include <SoundNode.h>
#include <tinyxml2.h>
#include <XMLParser.h>
#include <SoundAttachedNode.h>


SoundNode::SoundNode(bool bReleases) : ISound(bReleases), m_fRollOffFactor(1.0f), m_fConeOuterGain(0.8f),
										m_fConeInnerAngle(0.0f), m_fConeOuterAngle(90.0f),
										m_vfVelocity(0.0f, 0.0f, 0.0f)
										
{
	
}

SoundNode::~SoundNode(void)
{
	
}

void SoundNode::ConfigureSource(void)
{
	double dX, dY, dZ;
	getTranslate(&dX, &dY, &dZ);
	GetSource()->SetPosition((float) dX, (float) dY, (float) dZ);
	getRotate(&dX, &dY, &dZ);
	GetSource()->SetDirection((float) dX, (float) dY, (float) dZ);
	GetSource()->SetVelocity(m_vfVelocity[0], m_vfVelocity[1], m_vfVelocity[2]);
	ALSound::ConfigureSource();
}

void SoundNode::ProcessData(const vuMap<CharPointer, const char*>& msTagMap)
{
	if (msTagMap.count("Position"))
	{
		vuVec3<double> vdPos;
		XMLParser::ParseVec3(&vdPos, msTagMap.find("Position")->second);
		setTranslate(vdPos[0], vdPos[1], vdPos[2]);
	}

	if (msTagMap.count("Rotation"))
	{
		vuVec3<double> vdRotate;
		XMLParser::ParseVec3(&vdRotate, msTagMap.find("Position")->second);
		setRotate(vdRotate[0], vdRotate[1], vdRotate[2]);
	}

	if (msTagMap.count("Velocity"))
	{
		vuVec3<float> vfVelocity;
		XMLParser::ParseVec3(&vfVelocity, msTagMap.find("Velocity")->second);
		SetVelocity(vfVelocity);
	}

	if (msTagMap.count("RollOffFactor"))
	{
		SetRollOffFactor((float) atof(msTagMap.find("RollOffFactor")->second));
	}
	
	if (msTagMap.count("ConeOuterGain"))
	{
		SetConeOuterGain((float) atof(msTagMap.find("ConeOuterGain")->second));
	}

	if (msTagMap.count("ConeOuterAngle"))
	{
		SetConeOuterAngle((float) atof(msTagMap.find("ConeOuterAngle")->second));
	}
	
	if (msTagMap.count("ConeInnerAngle"))
	{
		SetConeInnerAngle((float) atof(msTagMap.find("ConeInnerAngle")->second));
	}

	ISound::ProcessData(msTagMap);
}

void SoundNode::PopulateAttachedSound(SoundAttachedNode* pkSound)
{
	vsgu::copy<SoundNode>(pkSound, this);
}