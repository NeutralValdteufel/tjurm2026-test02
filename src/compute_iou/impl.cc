#include "impls.h"
#include <algorithm>

float compute_iou(const cv::Rect& a, const cv::Rect& b) 
{
    /**
     * 要求：
     *      有一个重要的指标叫做“交并比”，简称“IOU”，可以用于衡量
     * 两个矩形的重合程度，本练习要求自行学习交并比的计算方式，计算输入
     * 的两个矩形的交并比。
     * 
     * 提示：
     * (1) 注意OpenCV中规定的xy坐标系方向跟平常的xy坐标系不一样。
     * (2) 注意矩形的x, y, width, height四个属性在坐标系内的含义。
     * (3) 注意分母不要除以0（不过我们不会测试这一点）
     * 
     * 通过条件：
     * 运行测试点，显示通过就行，不通过会告诉你哪一组矩形错了。
    */
    // IMPLEMENT YOUR CODE HERE

// 1. 计算交集矩形的坐标
    int inter_left   = std::max(a.x, b.x);
    int inter_top    = std::max(a.y, b.y);
    int inter_right  = std::min(a.x + a.width,  b.x + b.width);
    int inter_bottom = std::min(a.y + a.height, b.y + b.height);

    // 2. 没有交集的情况
    if (inter_right <= inter_left || inter_bottom <= inter_top) 
    {
        return 0.0f;
    }

    // 3. 计算交集与并集面积
    float inter_area = static_cast<float>((inter_right - inter_left) * (inter_bottom - inter_top));
    float union_area = static_cast<float>(a.area() + b.area() - inter_area);

    // 4. 计算 IoU
    return inter_area / union_area;
}