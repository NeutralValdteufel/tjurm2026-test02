#include "impls.h"


std::vector<std::vector<cv::Point>> find_contours(const cv::Mat& input) 
{
    /**
     * 要求：
     * 使用cv::findContours函数，从输入图像（3个通道）中找出所有的最内层轮廓。
     * 将它们保存起来作为函数返回值就行。contours的中文意思就是轮廓。
     * 
     * 提示：
     * 1. 使用cv::imshow来查看输入图像。
     * 2. 使用cv::drawContours来在一张图上绘制轮廓。
     * 3. 直接使用原图一般而言不利于轮廓的寻找，可以做一些简单的处理。
     * 4. findContours函数可以返回轮廓的层次结构，理解层次结构的保存方式并使用它（重点）。
     * 
     * 通过条件：
     * 运行测试点，你找到的轮廓与答案的轮廓一样就行。
     */
    
    // IMPLEMENT YOUR CODE HERE
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> res;  // 最终返回的最内层轮廓
    cv::Mat gray, binary;

    // 1. 转灰度
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // 2. 二值化，尝试自适应阈值，避免固定阈值不准
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // 3. 找轮廓，获取完整层次结构
    cv::Mat hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // 4. 遍历轮廓，选择最内层轮廓（没有子轮廓）
    if (!hierarchy.empty()) {
        for (size_t i = 0; i < contours.size(); i++) 
        {
            int first_child = hierarchy.at<cv::Vec4i>(0, i)[2];
            if (first_child == -1) {  // 没有子轮廓
                // 过滤噪声小轮廓，可以调整面积阈值
                if (cv::contourArea(contours[i]) > 50) 
                {
                    res.push_back(contours[i]);
                }
            }
        }
    }

    return res;
}