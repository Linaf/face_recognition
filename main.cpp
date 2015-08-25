#include "GroupPicture.h"
#include <time.h>
int main(int argc, char* argv[])
{
time_t rawtime;
GroupPicture gp;
try
{
if(argc==1)
{
std::cout<<"Using Camera"<<std::endl;
time(&rawtime);
gp.setVideoWriteLocation(ctime(&rawtime));
gp.setVideoSource();
}
else if(argc==2)
{
std::cout<<"Using File"<<argv[1];
gp.setVideoSource(argv[1]);
}
gp.processVideo();
time(&rawtime);
}
catch(int n)
{
if (n==12345)
{
std::cout<<"File Not Found"<<std::endl;
}
else
std::cout<<"Camera Not Found"<<std::endl;
}
catch(cv::Exception e)
{
std::cout<<"opencv"<<std::endl;
}
}
