//
// Created by Administrator on 2018/5/6.
//

#ifndef ZXYBISHE_MYFRAME_H
#define ZXYBISHE_MYFRAME_H

#include "wx/frame.h"
#include "wx/panel.h"
#include "wx/menu.h"
#include "wx/filepicker.h"
#include <wx/statbmp.h>
class MyFrame : public wxFrame {
public:
    MyFrame(wxWindow *parent, wxWindowID id=-1);
    virtual ~MyFrame();

private:
    static const long ID_PANEL;
    static const long ID_MENUITEM_OPEN;
    static const long ID_MENUITEM_SAVE;
    static const long ID_EXIT;
    static const long ID_CUT;
    static const long ID_COLOR;
    static const long ID_CHINESE;
    static const long ID_OTHER;
    static const long ID_TRAIN_CHINESE;
    static const long ID_TRAIN_OTHER;
    static const long ID_HANDBOOK;
    static const long ID_AI;
    //wxPanel *Panel;
    wxStaticBitmap* Panel;
    wxMenu *MenuOperate;
    wxMenu *MenuOperate1; //字符切割(颜色定位)
    wxMenu *MenuOperate2; //自符切割(Sobel)
    wxMenu *MenuOperate3; //中文字符识别
    wxMenu *MenuOperate4; //用户交互
    wxMenu *MenuOperate5; //利用CNN对汉字训练
    wxMenu *MenuOperate6; //用户使用手册
    wxMenuBar *MenuBar;
    wxFileDialog *fileDialog;
    wxMenuItem *MenuItemOpen;
    wxMenuItem *MenuItemSave;
    wxMenuItem *MenuItemExit;
    wxMenuItem *MenuItemCut;
    wxMenuItem *MenuItemColor;
    wxMenuItem *MenuItemChinese;
    wxMenuItem *MenuItemOther;
    wxMenuItem *MenuItemTrainChinese;
    wxMenuItem *MenuItemTrainOther;
    wxMenuItem *MenuItemHandbook;
    wxMenuItem *MenuItemAI;
    wxBitmap bitmap;
    void OnClickStart(wxMenuEvent &event);
    void OnClickSave(wxMenuEvent &event);
    void OnQuit(wxCommandEvent &event);
    void OnCut(wxCommandEvent &event);
    void OnColor(wxCommandEvent &event);
    void OnChinese(wxCommandEvent &event);
    void OnOther(wxCommandEvent &event);
    void OnTrainChinese(wxCommandEvent &event);
    void OnTrainOther(wxCommandEvent &event);
    void OnHandBook(wxCommandEvent &event);
    void OnAI(wxCommandEvent &event);
};

#endif //ZXYBISHE_MYFRAME_H
