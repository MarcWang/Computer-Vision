## Description

Implement character & text recognition

3rdParty Library
* OpenCV 3.0
* CMake


## Build contrib on opencv 3.0

```
opencv
├── sources
│   └── modules
│       └── contrib
├── build
```

```bat
cmake -G "Visual Studio 11 2012" .. -DOPENCV_EXTRA_MODULES_PATH=E:\temp\opencv\sources\modules\contrib\modules E:\temp\opencv\sources
cmake --build . --config Release
```

### Download
* [opencv](https://github.com/Itseez/opencv)
* [opencv_contrib](https://github.com/Itseez/opencv_contrib)


### Files
* OCRBeamSearch_CNN_model_data.xml.gz
* OCRHMM_knn_model_data.xml.gz
* OCRHMM_transitions_table.xml
* scenetext_char01.jpg
* scenetext_char02.jpg
* scenetext_char03.jpg
* scenetext_word01.jpg
* scenetext_word02.jpg
* scenetext_word03.jpg

Google Tesseract OCR
https://github.com/tesseract-ocr/tesseract


