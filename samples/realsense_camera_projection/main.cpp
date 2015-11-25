#include <iostream>
#include <pxcprojection.h>
#include <pxcsensemanager.h>
#include <pxccapturemanager.h>
#include <common/util_render.h>


#define WIDTH 640
#define HEIGHT 480

void PlotXY(pxcBYTE *cpixels, int xx, int yy, int cwidth, int cheight, int dots, int color) {
    if (xx < 0 || xx >= cwidth || yy < 0 || yy >= cheight) return;

    int lyy = yy * cwidth;
    int xxm1 = (xx > 0 ? xx - 1 : xx), xxp1 = (xx < (int)cwidth - 1 ? xx + 1 : xx);
    int lyym1 = yy > 0 ? lyy - cwidth : lyy, lyyp1 = yy < (int)cheight - 1 ? lyy + cwidth : lyy;

    if (dots >= 9)  /* 9 dots */
    {
        cpixels[(lyym1 + xxm1) * 4 + color] = 0xFF;
        cpixels[(lyym1 + xxp1) * 4 + color] = 0xFF;
        cpixels[(lyyp1 + xxm1) * 4 + color] = 0xFF;
        cpixels[(lyyp1 + xxp1) * 4 + color] = 0xFF;
    }
    if (dots >= 5)  /* 5 dots */
    {
        cpixels[(lyym1 + xx) * 4 + color] = 0xFF;
        cpixels[(lyy + xxm1) * 4 + color] = 0xFF;
        cpixels[(lyy + xxp1) * 4 + color] = 0xFF;
        cpixels[(lyyp1 + xx) * 4 + color] = 0xFF;
    }
    cpixels[(lyy + xx) * 4 + color] = 0xFF; /* 1 dot */
}

void DepthToColorByUVMAP(PXCProjection *projection, PXCImage *color, PXCImage *depth, int dots, pxcU16 invalid_value)
{
    if ( !color || !depth ){
        return;
    }
    PXCImage::ImageInfo cinfo = color->QueryInfo();

    /* Retrieve the color pixels */
    PXCImage::ImageData cdata;
    pxcStatus sts = color->AcquireAccess( PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB32, &cdata);
    if( sts >= PXC_STATUS_NO_ERROR ){
        int cwidth = cdata.pitches[0]/sizeof(int); /* aligned width */
        pxcBYTE *cpixels = cdata.planes[0];

        PXCImage::ImageInfo dinfo = depth->QueryInfo();
        PXCPointF32 *uvmap = new PXCPointF32[dinfo.width*dinfo.height];

        /* Retrieve the depth pixels and uvmap */
        PXCImage::ImageData ddata;
        if( depth->AcquireAccess( PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_DEPTH, &ddata ) >= PXC_STATUS_NO_ERROR ) {
            pxcU16 *dpixels = (pxcU16*)ddata.planes[0];
            int dpitch = ddata.pitches[0]/sizeof(pxcU16); /* aligned width */

            sts = projection->QueryUVMap(depth, uvmap);
            if(sts>=PXC_STATUS_NO_ERROR) {
                int uvpitch = depth->QueryInfo().width;

                /* Draw dots onto the color pixels */
                for (int y = 0; y < (int)dinfo.height; y++) {
                    for (int x = 0; x < (int)dinfo.width; x++) {
                        pxcU16 d = dpixels[y*dpitch+x];
                        if (d == invalid_value) continue; // no mapping based on unreliable depth values

                        float uvx = uvmap[y*uvpitch+x].x;
                        float uvy = uvmap[y*uvpitch+x].y;
                        int xx = (int)(uvx * cwidth + 0.5f), yy = (int)(uvy * cinfo.height + 0.5f);
                        if (xx >= 0 && xx < cwidth && yy >= 0 && yy < cinfo.height)
                        {
                            PlotXY(cpixels, xx, yy, cwidth, cinfo.height, dots, color?1:0);
                        }
                    }
                }
            }
            depth->ReleaseAccess(&ddata);
        }
        delete[] uvmap;
        color->ReleaseAccess(&cdata);
    }
}

void main()
{
    UtilRender *renderColor = new UtilRender(L"COLOR_STREAM");
    UtilRender *renderDepth = new UtilRender(L"DEPTH_STREAM");

    PXCSenseManager *psm = NULL;
    psm = PXCSenseManager::CreateInstance();
    if ( psm == NULL ){
        std::cout<<"Unabel to create the PXCSenseManager"<<std::endl;
        return;
    }

    PXCSession::ImplVersion version = psm->QuerySession()->QueryVersion();
    std::cout<<"RealSense SDK Version:"<<version.major<<"."<<version.minor<<std::endl;

    psm->EnableStream( PXCCapture::STREAM_TYPE_COLOR, WIDTH, HEIGHT);
    psm->EnableStream( PXCCapture::STREAM_TYPE_DEPTH, WIDTH, HEIGHT);

    if( psm->Init() != PXC_STATUS_NO_ERROR ){
        std::cout<<"Unable to Init the PXCSenseManager"<<std::endl;
        return;
    }

    PXCCapture::Device *device = psm->QueryCaptureManager()->QueryDevice();
    PXCProjection *projection = NULL;
    projection = device->CreateProjection();
    pxcU16 invalid_value = device->QueryDepthLowConfidenceValue();

    PXCImage *colorIm, *depthIm;
//    projection->CreateDepthImageMappedToColor( depthIm, colorIm);

    while(true){
        if( psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR ){
            break;
        }
        PXCCapture::Sample *sample = psm->QuerySample();
        if( sample ){
            if( sample->color ){
                colorIm = sample->color;
            }
            if( sample->depth ){
                depthIm = sample->depth;
            }
        }

        DepthToColorByUVMAP(projection, colorIm, depthIm, 9, invalid_value);

        if (!renderColor->RenderFrame(colorIm)) break;
        if (!renderDepth->RenderFrame(depthIm)) break;

        psm->ReleaseFrame();
    }
    projection->Release();
    psm->Release();
}

