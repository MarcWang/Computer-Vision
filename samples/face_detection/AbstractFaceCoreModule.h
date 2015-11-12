#ifndef ABSTRACTFACECOREMODULE_H
#define ABSTRACTFACECOREMODULE_H
#include "IFaceCoreModule.h"

class AbstractFaceCoreModule : public IFaceCoreModule
{
public:
    AbstractFaceCoreModule();
    virtual ~AbstractFaceCoreModule();
    virtual MResult initialize() = 0;
};

#endif // ABSTRACTFACECOREMODULE_H
