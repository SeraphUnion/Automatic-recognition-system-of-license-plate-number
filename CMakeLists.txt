cmake_minimum_required(VERSION 3.9)
project(zxybishe)

INCLUDE_DIRECTORIES(src)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -DMS_WIN64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DMS_WIN64 -DwxDEBUG_LEVEL=0")
include_directories(Commons/include)
link_directories(Commons/lib)
include_directories(include)
add_library(lpr src/LP.cpp)
add_executable(zxybishe main.cpp)
add_executable(svm_train svm_train.cpp)
add_executable(ann_train ann_train.cpp)
add_executable(window src/MyApp.cpp src/MyFrame.cpp)

target_link_libraries(ann_train lpr
        opencv_imgproc2413 opencv_highgui2413 opencv_core2413 opencv_ml2413
        libtiff libjpeg libpng  libjasper IlmImf zlib Vfw32)
target_link_libraries(svm_train lpr
        opencv_imgproc2413 opencv_highgui2413 opencv_core2413 opencv_ml2413
        libtiff libjpeg libpng  libjasper IlmImf zlib Vfw32)
target_link_libraries(zxybishe lpr
        opencv_imgproc2413 opencv_highgui2413 opencv_core2413 opencv_ml2413
        libtiff libjpeg libpng  libjasper IlmImf zlib
        wx_mswu_core-3.0 wx_baseu-3.0 wxjpeg-3.0 wxpng-3.0 wxtiff-3.0 wxzlib-3.0
        ws2_32 comctl32 Vfw32)
target_link_libraries(window lpr
        opencv_imgproc2413 opencv_highgui2413 IlmImf opencv_core2413 opencv_ml2413
        libtiff libjpeg libpng libjasper
        wx_mswu_core-3.0 wx_baseu-3.0 wxpng-3.0 wxtiff-3.0 wxjpeg-3.0 zlib
        ws2_32 comctl32 Vfw32 -mwindows -static)
