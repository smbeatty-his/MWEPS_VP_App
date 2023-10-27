#ifndef SOUND_NODE_MODULE_H
#define SOUND_NODE_MODULE_H

#include <vsTransform.h>
#include <ISound.h> 
#include <vuVec3.h>
#include <Factory.h>
#include <VuMap.h>
#include <CharPointer.h>

class SoundNode : public vsTransform, public ISound
{
public:
	
	virtual ~SoundNode();
	virtual void ConfigureSource(void);
	virtual void ProcessData(const vuMap<CharPointer, const char*>& msTagMap);
	virtual void PopulateAttachedSound(SoundAttachedNode* pkSound);

	const inline float GetRollOffFactor(void) const { return m_fRollOffFactor; }
	const inline void SetRollOffFactor(const float fRollOffFactor) { m_fRollOffFactor = fRollOffFactor; }
	const inline float GetConeOuterGain(void) const { return m_fConeOuterGain; }
	const inline void SetConeOuterGain(const float fOuterGain) { m_fConeOuterGain = fOuterGain; }
	const inline float GetConeInnerAngle(void) const { return m_fConeInnerAngle; }
	const inline void SetConeInnerAngle(const float fInnerAngle) { m_fConeInnerAngle = fInnerAngle; }
	const inline float GetConeOuterAngle(void) const { return m_fConeOuterAngle; }
	const inline void SetConeOuterAngle(const float fOuterAngle) { m_fConeOuterAngle = fOuterAngle; }
	const inline vuVec3<float>& GetVelocity(void) const {return m_vfVelocity; }
	const inline void SetVelocity(const vuVec3<float>& vfVel) { m_vfVelocity = vfVel; }
	
	ConcreteFactory(ISound, SoundNode);

protected:

	SoundNode(bool bReleases = true);

private:

	float m_fRollOffFactor;
	float m_fConeOuterGain;
	float m_fConeInnerAngle;
	float m_fConeOuterAngle;
	vuVec3<float> m_vfVelocity;
};

typedef SoundNode::SoundNodeFactory SoundNodeFactory;

namespace vsgu 
{

    template<>
        inline int copy<SoundNode>(SoundNode* dst, 
        const SoundNode* src, 
        const vsgu::Options& options)
    {
        int ret = vsgu::SUCCESS;

        if(dst == src) return vsgu::SUCCESS;
        if(dst == NULL || src == NULL) return vsgu::FAILURE;

        if (!(options[vuBase::getOptionIndex()] & vuBase::OPTION_IGNORE_BASE_CLASS))
        {
            ret = vsgu::copy<vsTransform>( dst, src, options );
            if(ret != vsgu::SUCCESS) return vsgu::FAILURE;
			
			dst->SetLooping(src->GetLooping());
			dst->SetGain(src->GetGain());
			dst->SetPitch(src->GetPitch());
			dst->SetMaxGain(src->GetMaxGain());
			dst->SetMinGain(src->GetMinGain());
			dst->SetBuffer(src->GetBuffer());
			dst->SetSource(src->GetSource());
			dst->SetRollOffFactor(src->GetRollOffFactor());
			dst->SetConeOuterGain(src->GetConeOuterGain());
			dst->SetConeInnerAngle(src->GetConeInnerAngle());
			dst->SetConeOuterAngle(src->GetConeOuterAngle());
			dst->SetVelocity(src->GetVelocity());
        }

        return (vsgu::SUCCESS);
    }

    template<>
        inline bool compare<SoundNode>(
        const SoundNode* s1, 
        const SoundNode* s2, 
        const Options& options)
    {
        
		if(s1 == NULL || s2 == NULL) 
		{
			return false;
		}

        if (!(options[vuBase::getOptionIndex()] & vuBase::OPTION_IGNORE_BASE_CLASS))
        {
            if(! vsgu::compare<vsTransform>( s1, s2, options )) 
			{
				return false;
			}
        }

        return (s1 == s2);
    }

} //namespace vsgu

#endif