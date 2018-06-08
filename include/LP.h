//
// Created by just_sort on 18-2-26.
//

#ifndef ZXYBISEPREDEAL_LP_H
#define ZXYBISEPREDEAL_LP_H

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/ml.hpp>
#include <opencv/cvaux.h>
using namespace cv;
using namespace std;

void RgbConvToGray(const Mat& inputImage, Mat &outputImage); //rgb转为二值图
bool needsize(const RotatedRect &candidates); //车牌区域需要满足什么条件
void posDetect_closeImage(Mat &inputImage, vector<RotatedRect>&rects); //考虑到车牌距离非常近的时候的情况
bool needsize_closeImage(const RotatedRect &candidates); //距离近时的车牌区域需要满足的条件
float calOverlap(const Rect& box1, const Rect& box2);//计算两个矩形的重叠比例
void GetStandardPlate(Mat &inputImg,vector<RotatedRect>& rects_optimal,vector<Mat>& output_area);
bool check_closeImage(const RotatedRect &candidate);
void clearLiuDing(Mat &img);
void sobelOper(const Mat &in, Mat &out, int blurSize, int morphW,int morphH);
void char_segment(const Mat &inputImg, vector<Mat>&); //对车牌区域中的字符进行分割
bool char_check(const RotatedRect &); //字符区域需要满足的条件
void char_sort(vector<RotatedRect>& in_char); //对字符区域进行排序
void features(const Mat &in, Mat &out, int sizeData); //获得一个字符矩阵对应的特征向量
void svm_train(CvSVM &);//取出SVM.xml中的特征矩阵和标签矩阵进行训练
bool solve1();//对静态图进行处理
bool solve2(); //颜色定位(蓝色)
bool solve3(); //颜色定位(黄色)
int getFileNum(string x);
void hsvImageBlue(Mat &hsvImage);
void hsvImageYello(Mat &hsvImage);
#endif //ZXYBISEPREDEAL_LP_H






