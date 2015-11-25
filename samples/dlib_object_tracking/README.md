### **Description**
Implement object tracker using dlib library, and capture frame from webcam using OpenCV.

### **Dir Tree**
```
Computer-Vision
├── samples
│   └── dlib_object_tracking
│
├── 3rdparty
│	└── dlib
│	└── opencv
```

### **3rdParty Library**
* OpenCV 3.0
* Dlib 18.18

### **Download**
* [opencv](https://github.com/Itseez/opencv)
* [dlib](http://dlib.net/)

### **Build Dlib**
```bat
cd examples
mkdir build
cd build
cmake ..
cmake --build . --config Release
```