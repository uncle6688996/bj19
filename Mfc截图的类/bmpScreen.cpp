
/*�����ƣ�bmpScreen.h��
; �๦�ܣ��ṩ��һ��MFC�½�ȡ�����ض����ֲ�����ΪbmpͼƬ���ࡣ
; �������Crect rect, int left, int top, int top, char* name��
; �����˵��:
;            (1)Crect rect   �����ͼ��Ĵ�С��
;			 (2)int left     �����ͼ����ͼ������ߵľ��롣
;			 (3)int top      �����ͼ����ͼ�����ϱߵľ��롣
;			 (4)char *name   ��������ͼ��bmpͼ������ƣ���ͼ��Ĭ�ϱ�����������Ŀ��Ŀ¼�¡�
*/

#include "stdafx.h"

#include "bmpScreen.h"


void bmpScreen::screenShot(CRect rect,int left,int top,char *name)

{
    CBitmap*  m_pBitmap; 	                                                 // �������Ա
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     // ��ý�ͼ���ڵ�ָ�룬Ĭ��Ϊ�����ڣ����Ը���Ϊ�����Ĵ��ڡ�
   	CPaintDC   dc(pMainFrame); 
	
	m_pBitmap=new   CBitmap;   
	m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   

	CDC   memDC;  
	memDC.CreateCompatibleDC(&dc); 
	CBitmap memBitmap, *oldmemBitmap;                                        // ��������Ļ���ݵ�bitmap
	
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
	
    oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC
    memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,left, top, SRCCOPY);  // ����߶ȿ��
	BITMAP bmp;
    memBitmap.GetBitmap(&bmp);                                               // ���λͼ��Ϣ 
    
    FILE *fp = fopen(name, "w+b");
	
    BITMAPINFOHEADER bih = {0};                                              // λͼ��Ϣͷ
    bih.biBitCount = bmp.bmBitsPixel;                                        // ÿ�������ֽڴ�С
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;                                             // �߶�
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                       // ͼ�����ݴ�С
    bih.biWidth = bmp.bmWidth;                                               // ���
    
    BITMAPFILEHEADER bfh = {0};                                              // λͼ�ļ�ͷ
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // ��λͼ���ݵ�ƫ����
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;            // �ļ��ܵĴ�С
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                           //д��λͼ�ļ�ͷ
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);                           //д��λͼ��Ϣͷ
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];                    //�����ڴ汣��λͼ����
	
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);                                    //��ȡλͼ����
	
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);                       //д��λͼ����
    delete [] p;	
    fclose(fp);
	memDC.SelectObject(oldmemBitmap);
	memDC.DeleteDC();

}

