#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) 
{
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    // IMPLEMENT YOUR CODE HERE

    int new_rows = static_cast<int>(input.rows * scale);
    int new_cols = static_cast<int>(input.cols * scale);

    // 创建一个新图像，大小为目标尺寸
    cv::Mat output(new_rows, new_cols, input.type());

    // 遍历新图像的每个像素
    for (int i = 0; i < new_rows; i++) 
    {
        for (int j = 0; j < new_cols; j++) 
        {
            // 找到原图对应的像素坐标
            int src_y = std::min(static_cast<int>(i / scale), input.rows - 1);
            int src_x = std::min(static_cast<int>(j / scale), input.cols - 1);

            // 复制像素（考虑通道数）
            if (input.channels() == 1) 
            {
                output.at<uchar>(i, j) = input.at<uchar>(src_y, src_x);
            } 
            else if (input.channels() == 3) 
            {
                output.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(src_y, src_x);
            }
        }
    }

    return output;
}