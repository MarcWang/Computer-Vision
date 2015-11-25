![dlib](http://dlib.net/dlib-logo.png)


## **Description**

Dlib is a modern C++ toolkit containing machine learning algorithms and tools for creating complex software in C++ to solve real world problems. It is open source software and licensed under the Boost Software License. The introduction contains everything you need to know to get started using the library. However, if after consulting the documentation, you have any questions, comments, or complaints feel free to post in the forums.

### **Download**
* [Dlib](http://dlib.net/) 
* [Cmake](https://cmake.org/)
* [Visual Studio Express 2012](https://www.microsoft.com/zh-tw/download/details.aspx?id=34673)


### **Build Dlib**
```bat
cd examples
mkdir build
cd build
cmake -G "Visual Studio 11 2012" ..
cmake --build . --config Release
```


### **Dir Tree**
```
Computer-Vision
├── 3rdparty
│	└── dlib
│		└── data
│		└── include
│		└── lib
│			└── vc11
```
