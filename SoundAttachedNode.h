#ifndef SOUND_ATTACHED_NODE_MODULE_H
#define SOUND_ATTACHED_NODE_MODULE_H

#include <SoundNode.h>

class vpObject;

class SoundAttachedNode : public SoundNode
{
public:
	virtual ~SoundAttachedNode(void);
	virtual void ConfigureSource(void);
	virtual void ProcessData(const vuMap<CharPointer, const char*>& msTagMap);
	virtual const char* GetClassType(void) { return "SoundAttachedNode"; }
	virtual void CloneSound(SoundAttachedNode* pkSound);
	virtual void Update(vpObject* pkObject);
	virtual void Activate(vpObject* pkObject);

	const inline int GetStartState(void) const { return m_iStartState; }
	const inline void SetStartState(const int iState) { m_iStartState = iState; }
	const inline int GetEndState(void) const { return m_iEndState; }
	const inline void SetEndState(const int iState) { m_iEndState = iState; }

	ConcreteFactory(ISound, SoundAttachedNode);

private:
	
	SoundAttachedNode(bool bReleases = true);

	int m_iStartState;
	int m_iEndState;

};

typedef SoundAttachedNode::SoundAttachedNodeFactory SoundAttachedNodeFactory;

namespace vsgu 
{

    template<>
        inline int copy<SoundAttachedNode>(SoundAttachedNode* dst, 
        const SoundAttachedNode* src, 
        const vsgu::Options& options)
    {
        int ret = vsgu::SUCCESS;

        if(dst == src) return vsgu::SUCCESS;
        if(dst == NULL || src == NULL) return vsgu::FAILURE;

        if (!(options[vuBase::getOptionIndex()] & vuBase::OPTION_IGNORE_BASE_CLASS))
        {
			ret = vsgu::copy<SoundNode>( dst, src, options );
            if(ret != vsgu::SUCCESS) return vsgu::FAILURE;
			
        }

		dst->SetStartState(src->GetStartState());
		dst->SetEndState(src->GetEndState());

        return (vsgu::SUCCESS);
    }

    template<>
        inline bool compare<SoundAttachedNode>(
        const SoundAttachedNode* s1, 
        const SoundAttachedNode* s2, 
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