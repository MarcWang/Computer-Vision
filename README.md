# **Computer-Vision**


### **Dir Tree**
```
Computer-Vision
├── samples
│   └── face_detection
│	└── 		....
│	└── realsense_open_camera
│
├── 3rdparty
│	└── dlib
│	└── opencv
│	└── intel
```


### **Sample Projecrt**
* Face Detection with OpenCV and Dlib
* Open Camera on RealSense F200
* Facial Recognition using OpenCV
* Face Detection using RealSense SDK
* Compare access mat on OpenCV

### **IDE**
* QT 5.4.2

### **Compiler**
* MSVC2012

### **Dependence Library**
* OpenCV 3.0
* Dlib 18.18
* Intel RealSense SDK R4


### **Download**
* [opencv](https://github.com/Itseez/opencv)
* [dlib](http://dlib.net/)
* [realsense](https://software.intel.com/en-us/intel-realsense-sdk/download)


### **Build Dlib**
```bat
cd examples
mkdir build
cd build
cmake -G "Visual Studio 11 2012" ..
cmake --build . --config Release
```