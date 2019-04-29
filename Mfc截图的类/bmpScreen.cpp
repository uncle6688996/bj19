
/*类名称：bmpScreen.h。
; 类功能：提供了一个MFC下截取窗口特定部分并保存为bmp图片的类。
; 类参数：Crect rect, int left, int top, int top, char* name。
; 类参数说明:
;            (1)Crect rect   定义截图框的大小。
;			 (2)int left     定义截图框距截图窗口左边的距离。
;			 (3)int top      定义截图框距截图窗口上边的距离。
;			 (4)char *name   定义所截图的bmp图像的名称，该图像默认保存在所建项目的目录下。
*/

#include "stdafx.h"

#include "bmpScreen.h"


void bmpScreen::screenShot(CRect rect,int left,int top,char *name)

{
    CBitmap*  m_pBitmap; 	                                                 // 加入类成员
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     // 获得截图窗口的指针，默认为主窗口，可以更改为其他的窗口。
   	CPaintDC   dc(pMainFrame); 
	
	m_pBitmap=new   CBitmap;   
	m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   

	CDC   memDC;  
	memDC.CreateCompatibleDC(&dc); 
	CBitmap memBitmap, *oldmemBitmap;                                        // 建立和屏幕兼容的bitmap
	
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
	
    oldmemBitmap = memDC.SelectObject(&memBitmap);//将memBitmap选入内存DC
    memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,left, top, SRCCOPY);  // 调解高度宽度
	BITMAP bmp;
    memBitmap.GetBitmap(&bmp);                                               // 获得位图信息 
    
    FILE *fp = fopen(name, "w+b");
	
    BITMAPINFOHEADER bih = {0};                                              // 位图信息头
    bih.biBitCount = bmp.bmBitsPixel;                                        // 每个像素字节大小
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;                                             // 高度
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                       // 图像数据大小
    bih.biWidth = bmp.bmWidth;                                               // 宽度
    
    BITMAPFILEHEADER bfh = {0};                                              // 位图文件头
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // 到位图数据的偏移量
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;            // 文件总的大小
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                           //写入位图文件头
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);                           //写入位图信息头
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];                    //申请内存保存位图数据
	
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);                                    //获取位图数据
	
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);                       //写入位图数据
    delete [] p;	
    fclose(fp);
	memDC.SelectObject(oldmemBitmap);
	memDC.DeleteDC();

}

