## Description

Implement facial recognition using OpenCV 3.0 from webcam

3rdParty Library
* OpenCV 3.0
* CMake



## Build contrib on opencv 3.0

opencv
├── sources
│   └── modules
│		└── contrib
├── build

```bat
cmake -G "Visual Studio 11 2012" .. -DOPENCV_EXTRA_MODULES_PATH=E:\temp\opencv\sources\modules\contrib\modules E:\temp\opencv\sources
cmake --build . --config Release
```

### Download
[opencv](https://github.com/Itseez/opencv)
[opencv_contrib](https://github.com/Itseez/opencv_contrib)