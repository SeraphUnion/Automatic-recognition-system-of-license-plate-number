#include <LP.h>
#include <Python.h>
#include <LP.cpp>
#include <string>
#include <opencv/cvaux.h>
#include <cstdio>
using namespace cv;
using namespace std;
extern "C"{
#include <Python.h>
}
int main(){
    char filename[200];
    sprintf(filename, "C:/Users/Administrator/zxybishe/saveImage/1.jpg");
    Mat input_img = imread(filename, 1);
    Mat input_img2;
    input_img2 = input_img.clone();
    if (input_img.empty()) {

    }
    vector<RotatedRect> rects;
    sobelOper(input_img, input_img, 3, 17, 3);
    //寻找车牌区域的轮廓
    vector<vector<Point> > contours;
    findContours(input_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //只检测外面的轮廓
    //对候选的轮廓进行进一步的筛选
    vector<vector<Point> >::iterator it = contours.begin();
    while (it != contours.end()) {
        RotatedRect temp = minAreaRect(Mat(*it)); //返回每个轮廓的最小有界矩形区域
        if (!check_closeImage(temp)) {
            it = contours.erase(it);
        } else {
            rects.push_back(temp);
            ++it;
        }
    }
    Mat result;
    input_img2.copyTo(result);
    drawContours(result, contours, -1, Scalar(0, 0, 255), 1);
    vector<Mat> output_area;
    GetStandardPlate(input_img2, rects, output_area); //获得144×33的候选车牌区域
    for(int i=0; i<output_area.size(); i++){
        cv::imshow("result", output_area[i]);
        waitKey(0);
    }
    CvSVM svmClassifyModel;
    svm_train(svmClassifyModel);
    vector<Mat> plates_svm;
    for (int i = 0; i < output_area.size(); i++) {
        Mat img = output_area[i];
        Mat now = img.reshape(1, 1);
        now.convertTo(now, CV_32FC1);
        int res = (int) svmClassifyModel.predict(now);
        if (res == 1)
            plates_svm.push_back(output_area[i]);
    }
    if(plates_svm.size()==0){
        return 0;
    }
    vector<Mat> char_seg;
    char_segment(plates_svm[0], char_seg);
    cv::imshow("char0", char_seg[0]);
    waitKey(0);
    cv::imshow("char1", char_seg[1]);
    waitKey(0);
    cv::imshow("char2", char_seg[2]);
    waitKey(0);
    cv::imshow("char3", char_seg[3]);
    waitKey(0);
    cv::imshow("char4", char_seg[4]);
    waitKey(0);
    cv::imshow("char5", char_seg[5]);
    waitKey(0);
    cv::imshow("char6", char_seg[6]);
    waitKey(0);
    cv::imwrite("C:/Users/Administrator/zxybishe/python/zxytest_images/1.jpg", char_seg[0]);
    cv::imwrite("C:/Users/Administrator/zxybishe/python/zxytest_images/2.jpg", char_seg[1]);
    cv::imwrite("C:/Users/Administrator/zxybishe/python/zxytest_images/3.jpg", char_seg[2]);
    cv::imwrite("C:/Users/Administrator/zxybishe/python/zxytest_images/4.jpg", char_seg[3]);
    cv::imwrite("C:/Users/Administrator/zxybishe/python/zxytest_images/5.jpg", char_seg[4]);
    cv::imwrite("C:/Users/Administrator/zxybishe/python/zxytest_images/6.jpg", char_seg[5]);
    cv::imwrite("C:/Users/Administrator/zxybishe/python/zxytest_images/7.jpg", char_seg[6]);
    cv::destroyAllWindows();
    return 0;
}