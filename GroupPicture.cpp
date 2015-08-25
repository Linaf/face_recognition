#include "GroupPicture.h"
#include "utils/utils.h"
#include </home/lina/setup/ffmpeg-2.7.2/compat/aix/math.h>
#include <boost/filesystem.hpp>
#include "tracker/FaceTracker.hpp"

using namespace FACETRACKER;
GroupPicture::GroupPicture()
{
tracker = FACETRACKER::LoadFaceTracker();
tracker_params= FACETRACKER::LoadFaceTrackerParams();
 Utils::Init();
}
GroupPicture::~GroupPicture()
{
delete tracker;
tracker=0;
delete tracker_params;
tracker_params=0;
}
void GroupPicture::setImage(const std::string &imgLoc)
{
image= cv::imread(imgLoc,CV_LOAD_IMAGE_GRAYSCALE);
}
void GroupPicture::processVideo()
{
cap >> image;
if( !vidLoc.empty())
{
faces = Utils::detectFaces(image);
//for (int i = 0; i < faces.size(); i++){
 cv::Mat imageadd1= image(faces[0]).clone();
writer.open(vidLoc,CV_FOURCC('M','J','P','G'), 30, (image(faces[0])).size());
writer.write(imageadd1);
//}
}
//if(faces.size()>0){

//for(int i=0; i < faces.size();i++){
cv::Point_<double> initialRun48;
initialRun48.x=-1;
cv::Point_<double> initialRun54;
initialRun54.x=-1;
cv::Point_<double> runningMax48;
runningMax48.x=0;
cv::Point_<double> runningMax54;
runningMax54.x=0;
cv::Point_<double> point6;
cv::Point_<double> point10;
cv::Point_<double> point14;
cv::Point_<double> point17;//For the left eye;
cv::Point_<double> point22;//For the right eye;
cv::Point_<double> point28;
cv::Point_<double> point51;
cv::Point_<double> point48;//For the mouth;
char key;
int j=0;
while(image.size().width>0 && image.size().height>0)
{
cv::Mat imageadd= image(faces[0]).clone();

result= tracker->NewFrame(imageadd, tracker_params);
if(result!=tracker->TRACKER_FAILED && result!=tracker->TRACKER_FACE_OUT_OF_FRAME)
{
//Return the value;
std::vector<cv::Point_<double> > shapeAdditional;
Pose pose;
std::vector<cv::Point3_<double> > shape3DAdditional;
shapeAdditional= tracker->getShape();
shape3DAdditional= tracker->get3DShape();
pose= tracker->getPose();
shape.insert(shape.end(),shapeAdditional.begin(), shapeAdditional.end());
shape3D.insert(shape3D.end(), shape3DAdditional.begin(), shape3DAdditional.end());
poseVec.insert(poseVec.end(), pose);
for(int i1=0; i1<66; i1++)
{
cv::Point_<double> m= shape.at(i1+j);
if(i1==48)
{
point48= m;
if(initialRun48.x==-1)
{
initialRun48= m;
}
if(runningMax48.x<m.x)
{
runningMax48= m;
}
}
if(i1==54)
{
if(initialRun54.x==-1)
{
initialRun48= m;
}
if(runningMax54.x<m.x)
{
runningMax54= m;
}
}
if(i1==6)
{
point6= m;
}
if(i1==10)
{
point10= m;
}
if(i1==14)
{
point14=m;
}
if(i1==17)
{
point17=m;
}
if(i1==22)
{
point22=m;
}
if(i1==30)
{
point28=m;
}
if(i1==33)
{
point51=m;
}
paintOnPicture(imageadd, m,1);
cv::Point point;
point.x= ((image(faces[0])).size().width/2);
point.y= ((image(faces[0])).size().height/2);
//Here call the generateSmiles using the queries for the fucntion;
if(i1==60)

std::cout<<"generate smile"<<std::endl;
}}
else if(result==tracker->TRACKER_FACE_OUT_OF_FRAME)
{
tracker->Reset();
//Call the FaceTracker out of Frame
}
else
{
tracker->Reset();
//Call the FaceTracker Failed to come;
}
//viewImage();
//viewImage();
cap >> imageadd;
viewImage(imageadd);
if(!vidLoc.empty())
writer.write(imageadd);
key = (char) cv::waitKey(20);
if(key==27)
break;
else if(key==82 || key== 114)//press R or r to reset the tracking;
{
j=0;
shape.clear();
shape3D.clear();
poseVec.clear();
if(!vidLoc.empty())
writer.open(vidLoc,CV_FOURCC('M','J','P','G'), 30, (image(faces[0])).size());
tracker->Reset();
}
}
delete tracker;
tracker=0;
delete tracker_params;
tracker_params=0;
//}

//
//}

}
void GroupPicture::setVideoSource()
{
cap= cv::VideoCapture(0);
if(!cap.isOpened())
throw(12346);
//std::cout<<"IT also reached here"<<std::endl;
}
void GroupPicture::setVideoSource(const std::string &videoLoc)
{
cap= cv::VideoCapture(videoLoc);
if(!cap.isOpened())
throw(12345);
}

void GroupPicture::viewImage()
{
    cv::namedWindow("Facial Expression Tracker");
    cv::imshow("Facial Expression Tracker", image);
}
void GroupPicture::viewImage(cv::Mat image1)
{
    cv::namedWindow("Facial Expression Tracker1");
    cv::imshow("Facial Expression Tracker1", image1);
}
std::string GroupPicture::intToString(int x)
{
    std::stringstream ss;
    ss.str(std::string());
    ss<<x;
    std::string xLoc= ss.str();
    return xLoc;
}
std::string GroupPicture::doubleToString(double x)
{
    std::stringstream ss;
    ss.str(std::string());
    ss<<x;
    std::string xLoc= ss.str();
    return xLoc;
}
void GroupPicture::paintOnPicture(cv::Mat &image, cv::Point_<double> point)
{
    int x=(int)point.y;
    int y=(int)point.x;
    image.at<cv::Vec3b>(x,y)[0]=0;
    image.at<cv::Vec3b>(x,y)[1]=255;
    image.at<cv::Vec3b>(x,y)[2]=0;

    image.at<cv::Vec3b>(x+1,y+1)[0]=0;      image.at<cv::Vec3b>(x-1,y-1)[0]=0;
    image.at<cv::Vec3b>(x+1,y+1)[1]=255;    image.at<cv::Vec3b>(x-1,y-1)[1]=255;
    image.at<cv::Vec3b>(x+1,y+1)[2]=0;      image.at<cv::Vec3b>(x-1,y-1)[2]=0;

    image.at<cv::Vec3b>(x+1,y-1)[0]=0;      image.at<cv::Vec3b>(x-1,y+1)[0]=0;
    image.at<cv::Vec3b>(x+1,y-1)[1]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
    image.at<cv::Vec3b>(x+1,y-1)[2]=0;      image.at<cv::Vec3b>(x-1,y+1)[0]=0;
}
void GroupPicture::paintOnPicture(cv::Mat &image, cv::Point_<double> point, int)
{
    int x=(int)point.y;
    int y=(int)point.x;
    image.at<cv::Vec3b>(x,y)[0]=255;
    image.at<cv::Vec3b>(x,y)[1]=255;
    image.at<cv::Vec3b>(x,y)[2]=255;

    image.at<cv::Vec3b>(x+1,y+1)[0]=255;    image.at<cv::Vec3b>(x-1,y-1)[0]=255;
    image.at<cv::Vec3b>(x+1,y+1)[1]=255;    image.at<cv::Vec3b>(x-1,y-1)[1]=255;
    image.at<cv::Vec3b>(x+1,y+1)[2]=255;    image.at<cv::Vec3b>(x-1,y-1)[2]=255;

    image.at<cv::Vec3b>(x+1,y-1)[0]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
    image.at<cv::Vec3b>(x+1,y-1)[1]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
    image.at<cv::Vec3b>(x+1,y-1)[2]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
}
void GroupPicture::setVideoWriteLocation(const std::string &vidLoc)
{
    this->vidLoc= vidLoc;
    /*
    this->vidLoc= vidLoc;
    writer= cv::VideoWriter(vidLoc,CV_FOURCC('M','J','P','G'), 30, image.size());
    if(!writer.isOpened())
        throw(12347);*/

}
