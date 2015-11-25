### **Description**
Implement face detection using OpenCV and Dlib library.

### **Dir Tree**
```
Computer-Vision
├── samples
│   └── face_detection
│		└── Release
│			└── haarcascade_frontalface_alt.xml
├── 3rdparty
│	└── dlib
│	└── opencv
```

### **3rdParty Library**
* OpenCV 3.0
* Dlib 18.18

### **OpenCV Face Detection File** 
* haarcascade_frontalface_alt.xml

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