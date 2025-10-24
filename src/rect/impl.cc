#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) 
{
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray, binary;
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat hierarchy;

    // 1. 转灰度
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // 2. 二值化（阈值可根据图像调整）
    cv::threshold(gray, binary, 50, 255, cv::THRESH_BINARY);

    // 3. 找轮廓
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 4. 找最大轮廓（通常目标矩形是最大的轮廓）
    int max_idx = -1;
    double max_area = 0;
    for (int i = 0; i < contours.size(); i++) 
    {
        double area = cv::contourArea(contours[i]);
        if (area > max_area) {
            max_area = area;
            max_idx = i;
        }
    }

    // 5. 计算矩形
    if (max_idx != -1) 
    {
        cv::Rect bound_rect = cv::boundingRect(contours[max_idx]);       // 外接矩形
        cv::RotatedRect min_rect = cv::minAreaRect(contours[max_idx]);   // 最小面积旋转矩形
        return std::make_pair(bound_rect, min_rect);
    }

    // 6. 如果没有轮廓，返回默认值
    return std::make_pair(cv::Rect(), cv::RotatedRect());
}