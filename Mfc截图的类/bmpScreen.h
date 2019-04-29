
/*类名称：bmpScreen.h。
; 类功能：提供了一个MFC下截取窗口特定部分并保存为bmp图片的类。
; 类参数：Crect rect, int left, int top, int top, char* name。
; 类参数说明:
;            (1)Crect rect   定义截图框的大小。
;			 (2)int left     定义截图框距截图窗口左边的距离。
;			 (3)int top      定义截图框距截图窗口上边的距离。
;			 (4)char *name   定义所截图的bmp图像的名称，该图像默认保存在所建项目的目录下。
*/

#ifndef H_BMPSCREEN_H
#define H_BMPSCREEN_H

class bmpScreen
{

   public:

   void screenShot(CRect rect,int left,int top,char *name);

};
#endif