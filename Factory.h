#ifndef FACTORY_MODULE_H
#define FACTORY_MODULE_H

#include <vuMap.h>
#include <CharPointer.h>
#include <DebugUtil.h>
///---------------------------------------------------------------------------
///    @brief This class is the Factory template class.
///     The Class will make a Factory of the abstract class tied to it. The 
///     Factory creates Concrete classes of the abstract one.
///---------------------------------------------------------------------------
template <class AbstractProductT> 
class Factory
{
public:

    virtual const char* GetConcreteClassName(void) const = 0;
	virtual AbstractProductT* Create(void) = 0;

};


///---------------------------------------------------------------------------
/// Concrete Factory Macro makes a concrete factory given an Abstract class
/// which is the derived class for the Given Concrete factory.
///---------------------------------------------------------------------------
#define ConcreteFactory(AbstractProductT, ConcreteProductT)\
    class ConcreteProductT##Factory : public Factory<AbstractProductT>\
    {\
        public:\
        ConcreteProductT##Factory() { };\
        ~ConcreteProductT##Factory() { };\
        virtual const char *GetConcreteClassName(void) const\
            { return #ConcreteProductT; }\
        virtual AbstractProductT* Create(void)\
        {\
            AbstractProductT* product = new ConcreteProductT();\
            assert(product != NULL);\
            return product;\
        }\
		private:\
			friend class ConcreteProductT;\
     };\

#endif