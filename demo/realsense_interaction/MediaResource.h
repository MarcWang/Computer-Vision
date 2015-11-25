#ifndef MEDIARESOURCE_H
#define MEDIARESOURCE_H
#include <pxcsensemanager.h>
#include <ImageFormatConverter.h>
#include <QObject>
#include <QThread>

#define LIB_DECL __declspec(dllexport)

class LIB_DECL MediaResource : public QThread
{
    Q_OBJECT
public:
    MediaResource();
    ~MediaResource();

    void initialize( PXCSenseManager *senseManager, int width, int height );
    void stop();

signals:

public slots:

protected:
    void run();

private:
    PXCSenseManager *_senseManager;
    ImageFormatConverter *_converter;
    bool _captureState;
    PXCImage *colorIm;
};

#endif // MEDIARESOURCE_H
