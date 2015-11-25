#include "FaceCoreModule.h"
#include <iostream>
#include <pxcstatus.h>

MFaceInfo::MFaceInfo(){
    id = -1;
    rect = PXCRectI32();
    anglePitch = 0;
    angleRoll = 0;
    angleYaw = 0;
    depth = 0;
    expressSmile = 0;
    expressKiss = 0;
    expressMouthOpen = 0;
    heartRate = -1;
}

MFaceResult::MFaceResult(){
    _count = 0;
}

MFaceResult::~MFaceResult(){
}

void MFaceResult::addFaceInfo(MFaceInfo info)
{
    faces.push_back( info );
}

MFaceInfo MFaceResult::getFaceInfo(int id)
{
    if( id < (int)faces.size() ){
        return faces[id];
    }
    else{
        return MFaceInfo();
    }
}

int MFaceResult::getFaceCount()
{
    return _count;
}

void MFaceResult::setFaceCount(int count)
{
    _count = count;
}


MFaceCoreModule::MFaceCoreModule(PXCSenseManager *senseManager)
{
    if ( senseManager == NULL ){
//        std::cout<<"Load PXCSenseManager Error"<<std::endl;
        return;
    }

    _faceModule = NULL;
    senseManager->EnableFace();
    _faceModule = senseManager->QueryFace();
    if( _faceModule == NULL ){
//        std::cout<<"Query Face Module Error"<<std::endl;
        return;
    }

    _faceData = NULL;
    _faceData = _faceModule->CreateOutput();
    if( _faceData == NULL ){
//        std::cout<<"Create Face Data Error"<<std::endl;
        _faceModule->Release();
        return;
    }
}

MFaceCoreModule::~MFaceCoreModule()
{
    if( _faceModule == NULL ){
        _faceModule->Release();
    }

    if( _faceData == NULL ){
        _faceData->Release();
    }
}

void MFaceCoreModule::initialize()
{
    if( _faceModule == NULL ){
        return;
    }
    PXCFaceConfiguration *cfg = _faceModule->CreateActiveConfiguration();
    cfg->detection.isEnabled = true;
    cfg->detection.maxTrackedFaces = 10;

    PXCFaceConfiguration::ExpressionsConfiguration *expc = cfg->QueryExpressions();
    expc->EnableAllExpressions();
    expc->Enable();

    cfg->QueryPulse()->Enable();

    cfg->ApplyChanges();
    cfg->Release();
}

void MFaceCoreModule::detect( MFaceResult &result )
{
    if( _faceModule == NULL ){
        return;
    }
    if( _faceData == NULL ){
        return;
    }
    if( _faceData->Update() != PXC_STATUS_NO_ERROR ){
        return;
    }

    pxcI32 nfaces = _faceData->QueryNumberOfDetectedFaces();
    result.setFaceCount( (int)nfaces );

    for( pxcI32 i = 0; i < nfaces; i++ ){
        MFaceInfo info;
        PXCFaceData::Face *face = _faceData->QueryFaceByIndex(i);

        //Get Face ID
        info.id = face->QueryUserID();

        //Get Face Depth
        PXCFaceData::DetectionData *ddata = face->QueryDetection();
        pxcF32 faceDepth = -1;
        if( !ddata->QueryFaceAverageDepth( &faceDepth ) ){
//            std::cout<<"Get Face Depth Error"<<std::endl;
            break;
        }
        info.depth = faceDepth;

        //Get Face Rectangle
        PXCRectI32 rect;
        if( !ddata->QueryBoundingRect(&rect) ){
//            std::cout<<"Extract Face Rectangle Error"<<std::endl;
            break;
        }
        info.rect = rect;

        if( i == 0 ){
            //Get Face Landmark Points
            PXCFaceData::LandmarksData *ldata = face->QueryLandmarks();
            if( !ldata->QueryPoints( info.points ) ){
//                std::cout<<"Get Face Landmark Points Error"<<std::endl;
                break;
            }

            //Get Face Angle
            PXCFaceData::PoseData *pdata = face->QueryPose();
            PXCFaceData::PoseEulerAngles angles;
            if( !pdata->QueryPoseAngles(&angles) ){
//                std::cout<<"Get Face Angle Error"<<std::endl;
                break;
            }
            info.anglePitch = angles.pitch;
            info.angleRoll = angles.roll;
            info.angleYaw = angles.yaw;

            //Get Expression Result
            PXCFaceData::ExpressionsData *edata = face->QueryExpressions();
            PXCFaceData::ExpressionsData::FaceExpressionResult scoreSmile, scoreKiss, scoreMouth;
            edata->QueryExpression(PXCFaceData::ExpressionsData::EXPRESSION_SMILE, &scoreSmile);
            edata->QueryExpression(PXCFaceData::ExpressionsData::EXPRESSION_KISS, &scoreKiss);
            edata->QueryExpression(PXCFaceData::ExpressionsData::EXPRESSION_MOUTH_OPEN, &scoreMouth);
            info.expressSmile = scoreSmile.intensity;
            info.expressKiss = scoreKiss.intensity;
            info.expressMouthOpen = scoreMouth.intensity;

            //Get Heart Rate
            PXCFaceData::PulseData *pulesdata = face->QueryPulse();
            info.heartRate = pulesdata->QueryHeartRate();
        }
        result.addFaceInfo( info );
    }
}
