#include <opencv2/opencv.hpp>
#include <iostream>

const std::string keys =
        "{help h usage ? |      | print this message   }"
        "{@image1        |      | image1 for compare   }"
        "{@image2        |<none>| image2 for compare   }"
        "{@repeat        |1     | number               }"
        "{path           |.     | path to file         }"
        "{fps            | -1.0 | fps for output video }"
        "{N count        |100   | count of objects     }"
        ;

int main( int argc, char *argv[] )
{

    cv::CommandLineParser parser(argc, argv, keys);

    //程式的簡易說明都可以寫在這裡
    std::string description = "Application name v1.0.0";
    parser.about(description);

    //當cmd後面參數有 --help or --usage 時，顯示程式相關參數設定說明
    // ./app --help
    if (parser.has("help") || parser.has("usage")){
        parser.printMessage();
        return 0;
    }


    //取得設定參數(N or count)的int型態的值，在cmd參數下 N=50 or count=50可以設定parser中的(N and count)數值，初始值是 100
    //  ./app N=50
    int N = parser.get<int>("N");
    std::cout << "N : " << N << std::endl;

    //取得設定參數(fps)的double型態的值，在cmd參數下 fps=30.0可以設定parser中的fps數值，初始值是 -1.0
    //  ./app fps=30.0
    double fps = parser.get<double>("fps");
    std::cout << "fps : " << fps << std::endl;

    //取得設定參數(path)的string型態的值，在cmd參數下 path=./exeFolder可以設定parser中的path數值，初始值是.
    //  ./app path=./exeFolder
    std::string path = parser.get<std::string>("path");
    std::cout << "path : " << path << std::endl;

    //取得設定參數第一與第二個參數值，並轉成string型態，在cmd參數下 ./images/img1.jpg ./images/img2.jpg 可以設定parser中的img1 and img2數值，初始值是
    //  ./app ./images/img1.jpg ./images/img2.jpg
    std::string img1 = parser.get<std::string>(0);
    std::string img2 = parser.get<std::string>(1);
    std::cout << "img1 : " << img1 << std::endl;
    std::cout << "img2 : " << img2 << std::endl;

    //取得設定參數第三個參數值，並分別轉成int and string型態，在cmd參數下 params1 params2 55 可以設定parser中的repeat數值，初始值是 1
    //  ./app ./images/img1.jpg ./images/img2.jpg 55
    int repeat = parser.get<int>(2);
    std::cout << "repeat (int): " << repeat << std::endl;
    std::string repeatStr = parser.get<std::string>(2);
    std::cout << "repeat (str): " << repeatStr << std::endl;

    //檢查parsere過程中有沒有形態轉換錯誤或設定值錯誤
    if (!parser.check()){
        parser.printErrors();
        return 0;
    }

    return 0;
}
