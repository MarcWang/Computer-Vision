#ifndef FACECOREMODULE_H
#define FACECOREMODULE_H
#include <pxcfacemodule.h>
#include <pxcsensemanager.h>
#include <opencv2\opencv.hpp>
#include <vector>

#define MAX_LANDMARK 78
#define LIB_DECL __declspec(dllexport)

struct MFaceInfo
{
    MFaceInfo();

    pxcUID id;
    PXCRectI32 rect;
    pxcF32 anglePitch;
    pxcF32 angleRoll;
    pxcF32 angleYaw;
    pxcF32 depth;
    pxcI32 expressSmile;
    pxcI32 expressKiss;
    pxcI32 expressMouthOpen;
    pxcF32 heartRate;
    PXCFaceData::LandmarkPoint points[MAX_LANDMARK];
};

struct MFaceResult
{
public:
    MFaceResult();
    ~MFaceResult();
    void addFaceInfo( MFaceInfo info );
    MFaceInfo getFaceInfo( int id );
    int getFaceCount();
    void setFaceCount( int count );

private:
    std::vector<MFaceInfo> faces;
    int _count;
};


class LIB_DECL MFaceCoreModule
{
public:
    MFaceCoreModule( PXCSenseManager *senseManager );
    ~MFaceCoreModule();
    void initialize();
    void detect( MFaceResult &result );

private:
    PXCSenseManager *_senseManager;
    PXCFaceModule *_faceModule;
    PXCFaceData *_faceData;
};

#endif // FACECOREMODULE_H
