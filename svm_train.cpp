//
// Created by just_sort on 18-3-1.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
using namespace cv;
using namespace std;

int main(){
    FileStorage fs("C:/Users/Administrator/zxybishe/XML/SVM2.xml", FileStorage::WRITE);
    char way[90];
    Mat trainingmat, input, now;
    for(int i=1; i<=100; i++){
        sprintf(way, "C:/Users/Administrator/zxybishe/data/Database_SVM/posdata/0000 (%d).bmp", i);
        input = imread(way, -1);
        now = input.reshape(1, 1);
        now.convertTo(now, CV_32FC1);
        trainingmat.push_back(now);
    }
    for(int i=1; i<=70; i++){
        sprintf(way, "C:/Users/Administrator/zxybishe/data/Database_SVM/negdata/0000 (%d).bmp", i);
        input = imread(way, -1);
        now = input.reshape(1, 1);
        now.convertTo(now, CV_32FC1);
        trainingmat.push_back(now);
    }
    Mat Labels(170, 1, CV_32FC1);
    for(int i=0; i<Labels.rows; i++){
        if(i<100) Labels.at<float>(i,0)=1.0;
        else Labels.at<float>(i,0)=-1.0;
    }
    CvSVM model;
    CvSVMParams model_params;
    model_params.kernel_type = CvSVM::LINEAR;
    model.train(trainingmat, Labels, Mat(), Mat(), model_params);
    fs<<"TraingingData"<<trainingmat;
    fs<<"classes"<<Labels;
    return 0;
}