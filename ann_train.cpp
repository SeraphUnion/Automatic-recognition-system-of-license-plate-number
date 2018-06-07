#include <LP.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;


int main(){
    FileStorage fs("/home/just_sort/CLionProjects/zxybisepredeal/XML/ann_xml.xml", FileStorage::WRITE);
    Mat trainData;
    Mat classes = Mat::zeros(1,1700,CV_8UC1);
    char path[90];
    Mat img_read;
    for(int i=0;i<34;i++){
        for(int j=1;j<51;j++){
            sprintf(path,"/home/just_sort/CLionProjects/zxybisepredeal/data/charSamples/%d/%d.jpg", i,j);
            img_read = cv::imread(path, -1);
//            cv::imshow("233", img_read);
//            cv::waitKey(0);
            Mat img_threshold;
            threshold(img_read,img_threshold,180,255,CV_THRESH_BINARY);
            Mat dst_mat;
            Mat train_mat(2,3,CV_32FC1);
            int length;
            Point2f srcTri[3], dstTri[3];
            srcTri[0] = Point2f(0.0,0.0);
            srcTri[1] = Point2f(img_threshold.cols-1,0.0);
            srcTri[2] = Point2f(0.0,img_threshold.rows-1);
            length = img_threshold.rows>img_threshold.cols?img_threshold.rows:img_threshold.cols;
            dstTri[0] = Point2f(0.0,0.0);
            dstTri[1] = Point2f(length, 0.0);
            dstTri[2] = Point2f(0.0, length);
            train_mat = getAffineTransform(srcTri,dstTri);
            dst_mat = Mat::zeros(length,length,img_threshold.type());
            warpAffine(img_threshold,dst_mat,train_mat,dst_mat.size(),INTER_LINEAR,BORDER_CONSTANT,Scalar(0));
            resize(dst_mat,dst_mat,Size(20,20));
            Mat dst_feature;
            features(dst_mat,dst_feature,15); //1*440
            cout << dst_feature.rows << " " << dst_feature.cols << endl;
            trainData.push_back(dst_feature);
            classes.at<uchar>(i*50+j-1) = i;
        }
    }
    fs<<"TrainingData"<<trainData;
    fs<<"classes"<<classes;
    fs.release();
    return 0;
}
