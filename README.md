# **Computer-Vision**


### **Dir Tree**
```
Computer-Vision
├── samples
│   └── face_detection
│   └── 		....
│   └── realsense_open_camera
│
├── demo
├── 3rdparty
│   └── dlib
│   └── opencv
│       └── data
│           └── haarcascades
│           └── lbpcascades
│   └── intel
```


### **Sample Projecrt**
name                             | description          
---------------------------------|----------------------------
face_detection                   | compare opencv and dlib                   
dlib_object_tracking             | implement object tracker using dlib                  
opencv_facial_recognition        | implement facial recognition using opencv
opencv_human_detection           | implement human detection using HOG and Haar feature using opencv
opencv_mat_control               | compare methods for mat of control on opencv
opencv_license_plate_recognition | 
opencv_machine_learning          | 
opencv_open_camera               | 
opencv_using_gpu                 | 
opencv_text_recognition          | 
realsense_camera_projection      | implement camera projection using realsense on F200
realsense_face_detection         | implement face detection using realsense SDK
realsense_open_camera            | open camera on F200


### **IDE**
* QT 5.4.2

### **Compiler**
* MSVC2012

### **Dependence Library**
* OpenCV 3.0
* Dlib 18.18
* Intel RealSense SDK R4

### **Tools**
* CMake

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

### **Build OpenCV**
```bat
cmake -G "Visual Studio 11 2012" .. -DOPENCV_EXTRA_MODULES_PATH=...\opencv\sources\modules\contrib\modules ...\opencv\sources
cmake --build . --config Release
```
