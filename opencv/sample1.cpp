#include <iostream>
#include <string>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    std::string image_path = cv::samples::findFile("starry_night.jpg");

    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    cv::imshow("Display window", img);

    int k = cv::waitKey(0); // Wait for a keystroke in the window
                        //
    //if(k == 's')
    //{
    //    imwrite("starry_night.png", img);
    //}
    //
    return 0;
}

