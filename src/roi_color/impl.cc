#include "impls.h"
#include <unordered_map>


std::unordered_map<int, cv::Rect> roi_color(const cv::Mat& input) 
{
    /**
     * INPUT: 一张彩色图片, 路径: opencv/assets/roi_color/input.png
     * OUTPUT: 一个 unordered_map, key 为颜色(Blue: 0, Green: 1, Red: 2), value 为对应颜色的矩形区域(cv::Rect)
     * TODO:
     *  1. 找到图片中三个颜色的轮廓
     *  2. 计算出三处矩形的颜色
     *  3. 返回一个 unordered_map, key 为颜色, value 为cv::Rect (表示矩形的位置)
     * HINT:
     *  1. 预处理
     *    1. 在学习 findContours 时，我们提供的输入图片已经是一个二值图像了，
     *       但是在这里，input 是一个彩色图形。
     *       而 findContours 的 input 最好是一个二值图像。
     *    2. findContours 处理时，一般是在一个黑色背景上，找白色的轮廓
     *       (因此在二值化时，你可能需要考虑一下 cv::THRESH_BINARY_INV 选项
     *       同时，建议了解一下 cv::THRESH_OTSU 选项以及他们如何配合使用)
     *    3. 因此，预处理流程如下:
     *      1. 将 input 转换成灰度图像
     *      2. 对灰度图像进行二值化，得到黑底的二值化图
     *   2. 找到三个矩形 (findContours)
     *   3. 对找到的三个矩形，分别进行如下计算:
     *      1. 使用 cv::boundingRect 将轮廓转换成矩形 cv::Rect
     *      2. 使用该 cv::Rect 得到 input 中的 ROI区域 (写法: roi = input(rect))
     *      3. 使用统计的方法，得到该 ROI 区域的颜色
     *      4. 将颜色 和 矩形位置 存入 map 中
     */
    std::unordered_map<int, cv::Rect> res;
    // IMPLEMENT YOUR CODE HERE

    // 1. 转为灰度图
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // 2. 二值化（使用 OTSU 自适应阈值 + 反色）
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    // 3. 找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 4. 按轮廓面积降序排列，避免小噪点干扰
    std::sort(contours.begin(), contours.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b){
        return cv::contourArea(a) > cv::contourArea(b);
    });

    // 5. 处理前三个大轮廓
    int max_count = std::min(3, (int)contours.size());
    for (int i = 0; i < max_count; ++i) 
    {
        cv::Rect rect = cv::boundingRect(contours[i]);
        cv::Mat roi = input(rect);

        // 计算 ROI 平均颜色
        cv::Scalar mean_color = cv::mean(roi);

        // 找到最大通道对应颜色
        double max_val = std::max({mean_color[0], mean_color[1], mean_color[2]});
        int color_type = -1;
        if (max_val == mean_color[0]) color_type = 0; // 蓝
        else if (max_val == mean_color[1]) color_type = 1; // 绿
        else if (max_val == mean_color[2]) color_type = 2; // 红

        if (color_type != -1) 
        {
            res[color_type] = rect;
        }
    }

    return res;
}