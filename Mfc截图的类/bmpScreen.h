
/*�����ƣ�bmpScreen.h��
; �๦�ܣ��ṩ��һ��MFC�½�ȡ�����ض����ֲ�����ΪbmpͼƬ���ࡣ
; �������Crect rect, int left, int top, int top, char* name��
; �����˵��:
;            (1)Crect rect   �����ͼ��Ĵ�С��
;			 (2)int left     �����ͼ����ͼ������ߵľ��롣
;			 (3)int top      �����ͼ����ͼ�����ϱߵľ��롣
;			 (4)char *name   ��������ͼ��bmpͼ������ƣ���ͼ��Ĭ�ϱ�����������Ŀ��Ŀ¼�¡�
*/

#ifndef H_BMPSCREEN_H
#define H_BMPSCREEN_H

class bmpScreen
{

   public:

   void screenShot(CRect rect,int left,int top,char *name);

};
#endif