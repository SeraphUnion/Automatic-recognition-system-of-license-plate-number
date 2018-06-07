//
// Created by Administrator on 2018/5/6.
//


#include "MyFrame.h"
#include <LP.h>
#include <unordered_map>
#include <wx/wx.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <vector>
#include <algorithm>
#include <wx/textdlg.h>
#include <wx/dcbuffer.h>
#include "sstream"

const long MyFrame::ID_PANEL = wxNewId();
const long MyFrame::ID_MENUITEM_OPEN = wxNewId();
const long MyFrame::ID_MENUITEM_SAVE = wxNewId();
const long MyFrame::ID_EXIT = wxNewId();
const long MyFrame::ID_CUT = wxNewId();
const long MyFrame::ID_COLOR = wxNewId();
const long MyFrame::ID_CHINESE = wxNewId();
const long MyFrame::ID_OTHER = wxNewId();
const long MyFrame::ID_TRAIN_CHINESE = wxNewId();
const long MyFrame::ID_TRAIN_OTHER = wxNewId();
const long MyFrame::ID_HANDBOOK = wxNewId();
const long MyFrame::ID_AI = wxNewId();

MyFrame::~MyFrame() {
    exit(0);
}

MyFrame::MyFrame(wxWindow *parent, wxWindowID id) {
    Create(parent, id, wxString::FromUTF8("ZXY的车牌号码识别系统"), wxDefaultPosition, wxSize(688, 485));
    MenuOperate = new wxMenu();
    MenuItemOpen = new wxMenuItem(MenuOperate, ID_MENUITEM_OPEN, wxString::FromUTF8("识别静态车牌图片"), wxEmptyString,
                                  wxITEM_NORMAL);
    MenuItemSave = new wxMenuItem(MenuOperate, ID_MENUITEM_SAVE, wxString::FromUTF8("通过摄像头实时识别"), wxEmptyString,
                                  wxITEM_NORMAL);
    MenuItemExit = new wxMenuItem(MenuOperate, ID_EXIT, wxString::FromUTF8("退出系统"), wxEmptyString,
                                  wxITEM_NORMAL);
    MenuOperate1 = new wxMenu();
    MenuItemCut = new wxMenuItem(MenuOperate1, ID_CUT, wxString::FromUTF8("车牌定位之颜色定位模块"), wxEmptyString, wxITEM_NORMAL);
    MenuItemColor = new wxMenuItem(MenuOperate1, ID_COLOR, wxString::FromUTF8("车牌定位之Sobel算子定位"), wxEmptyString,
                                   wxITEM_NORMAL);
    MenuOperate3 = new wxMenu();
    MenuItemChinese = new wxMenuItem(MenuOperate3, ID_CHINESE, wxString::FromUTF8("中文字符识别"), wxEmptyString,
                                     wxITEM_NORMAL);
    MenuItemOther = new wxMenuItem(MenuOperate3, ID_OTHER, wxString::FromUTF8("其他字符识别"), wxEmptyString, wxITEM_NORMAL);
    MenuOperate5 = new wxMenu();
    MenuItemTrainChinese = new wxMenuItem(MenuOperate5, ID_TRAIN_CHINESE, wxString::FromUTF8("训练中文字符识别模型"),
                                          wxEmptyString, wxITEM_NORMAL);
    MenuItemTrainOther = new wxMenuItem(MenuOperate5, ID_TRAIN_OTHER, wxString::FromUTF8("训练数字和字母识别模型"), wxEmptyString,
                                        wxITEM_NORMAL);
    MenuOperate4 = new wxMenu();
    MenuItemAI = new wxMenuItem(MenuOperate4, ID_AI, wxString::FromUTF8("用户交互，修正错误"));
    MenuOperate6 = new wxMenu();
    MenuItemHandbook = new wxMenuItem(MenuOperate6, ID_HANDBOOK, wxString::FromUTF8("用户使用手册"), wxEmptyString,
                                      wxITEM_NORMAL);

    MenuBar = new wxMenuBar();
    MenuOperate = new wxMenu();
    MenuOperate->Append(MenuItemOpen);
    MenuOperate->Append(MenuItemSave);
    MenuOperate->Append(MenuItemExit);
    MenuOperate1->Append(MenuItemCut);
    MenuOperate1->Append(MenuItemColor);
    MenuOperate3->Append(MenuItemChinese);
    MenuOperate3->Append(MenuItemOther);
    MenuOperate5->Append(MenuItemTrainChinese);
    MenuOperate5->Append(MenuItemTrainOther);
    MenuOperate6->Append(MenuItemHandbook);
    MenuOperate4->Append(MenuItemAI);
    MenuBar->Append(MenuOperate, wxString::FromUTF8("选择系统识别模式"));
    MenuBar->Append(MenuOperate1, wxString::FromUTF8("车牌定位和字符切割模块"));
    MenuBar->Append(MenuOperate3, wxString::FromUTF8("车牌字符识别"));
    MenuBar->Append(MenuOperate5, wxString::FromUTF8("车牌字符识别模型训练"));
    MenuBar->Append(MenuOperate4, wxString::FromUTF8("识别错误修正"));
    MenuBar->Append(MenuOperate6, wxString::FromUTF8("用户使用手册"));
//    MenuBar->Append(MenuOperate6, wxString::FromUTF8("其他字符训练"));
    SetMenuBar(MenuBar);
    Connect(ID_MENUITEM_OPEN, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnClickStart);
    Connect(ID_MENUITEM_SAVE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnClickSave);
    Connect(ID_EXIT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnQuit);
    Connect(ID_CUT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnCut);
    Connect(ID_COLOR, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnColor);
    Connect(ID_CHINESE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnChinese);
    Connect(ID_OTHER, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnOther);
    Connect(ID_TRAIN_CHINESE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnTrainChinese);
    Connect(ID_TRAIN_OTHER, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnTrainOther);
    Connect(ID_HANDBOOK, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnHandBook);
    Connect(ID_AI, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnAI);
    Mat temp = cv::imread("data/background/bg.jpg");
    if (!temp.data) {
        exit(0);
    }
    wxImage img(temp.cols, temp.rows, temp.data, true);
    Panel = new wxStaticBitmap(this, ID_PANEL, wxBitmap(img));

}

void MyFrame::OnAI(wxCommandEvent &event) {
    wxTextEntryDialog dialog(this, wxT("错误字符编号，从左到右填入1-7"), wxT("请输入"), wxT(""), wxOK | wxCANCEL);
    wxString x, y;
    if (dialog.ShowModal() == wxID_OK) {
        x = dialog.GetValue();
    }
    Mat now = cv::imread("C:/Users/Administrator/zxybishe/python/zxytest_images/8.png");
    cv::imshow("now", now);
    cv::waitKey(0);
    wxTextEntryDialog dialog2(this, wxT("该字符的正确值为，从左到右填入正确字符对应的数字序号"), wxT("请输入"), wxT(""), wxOK | wxCANCEL);
    if (dialog2.ShowModal() == wxID_OK) {
        y = dialog2.GetValue();
    }
    unordered_map<string, int> mp;
    unordered_map<string, int> mp2;
    mp["川"] = 0;
    mp["鄂"] = 1;
    mp["赣"] = 2;
    mp["甘"] = 3;
    mp["贵"] = 4;
    mp["桂"] = 5;
    mp["黑"] = 6;
    mp["沪"] = 7;
    mp["冀"] = 8;
    mp["津"] = 9;
    mp["京"] = 10;
    mp["吉"] = 11;
    mp["辽"] = 12;
    mp["鲁"] = 13;
    mp["蒙"] = 14;
    mp["闽"] = 15;
    mp["宁"] = 16;
    mp["青"] = 17;
    mp["琼"] = 18;
    mp["陕"] = 19;
    mp["苏"] = 20;
    mp["晋"] = 21;
    mp["皖"] = 22;
    mp["湘"] = 23;
    mp["新"] = 24;
    mp["豫"] = 25;
    mp["渝"] = 26;
    mp["粤"] = 27;
    mp["云"] = 28;
    mp["藏"] = 29;
    mp["浙"] = 30;
    mp2["0"] = 0;
    mp2["1"] = 1;
    mp2["2"] = 2;
    mp2["3"] = 3;
    mp2["4"] = 4;
    mp2["5"] = 5;
    mp2["6"] = 6;
    mp2["7"] = 7;
    mp2["8"] = 8;
    mp2["9"] = 9;
    mp2["A"] = 10;
    mp2["B"] = 11;
    mp2["C"] = 12;
    mp2["D"] = 13;
    mp2["E"] = 14;
    mp2["F"] = 15;
    mp2["G"] = 16;
    mp2["H"] = 17;
    mp2["J"] = 18;
    mp2["K"] = 19;
    mp2["L"] = 20;
    mp2["M"] = 21;
    mp2["N"] = 22;
    mp2["P"] = 23;
    mp2["Q"] = 24;
    mp2["R"] = 25;
    mp2["S"] = 26;
    mp2["T"] = 27;
    mp2["U"] = 28;
    mp2["V"] = 29;
    mp2["W"] = 30;
    mp2["X"] = 31;
    mp2["Y"] = 32;
    mp2["Z"] = 33;
    if (x == "1") {
        int cnt = wxAtoi(y);
        string path =
                "python/train_images/training-set/chinese-characters/" + to_string(cnt);
        int num = getFileNum(path);
        string now = "python/train_images/training-set/chinese-characters/" +
                     to_string(cnt) + "/" + to_string(num + 1) + ".jpg";
        Mat src = cv::imread("python/zxytest_images/1.jpg");
        cv::imwrite(now, src);
    } else {
        int cnt = wxAtoi(y);
        string path = "python/train_images/training-set/" + to_string(cnt);
        int num = getFileNum(path);
        string now = "python/train_images/training-set/" + to_string(cnt) + "/" +
                     to_string(num + 1) + ".jpg";
        string dir = "python/zxytest_images/" + to_string(num + 1) + ".jpg";
        Mat src = cv::imread(dir);
        cv::imwrite(now, src);
    }
    destroyAllWindows();
}

void MyFrame::OnClickStart(wxMenuEvent &event) {
    fileDialog = new wxFileDialog(this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString,
                                  "*.jpg",
                                  wxFD_FILE_MUST_EXIST | wxFD_OPEN);
    if (wxID_CANCEL == fileDialog->ShowModal())
        return;

    Mat src = cv::imread(String(fileDialog->GetPath()));
    cv::imwrite("saveImage/1.jpg", src);
    bool x = solve1();
    if (x == false) {
        wxString msg;
        msg.Printf(wxT("未检测到车牌号码"));
        wxMessageBox(msg, wxT("按下此键以继续"));
    }
    string cmd = "Python36/python.exe -W ignore python/estimate_chinese1.py";
    WinExec(cmd.c_str(), SW_HIDE);
    cmd = "Python36/python.exe -W ignore python/estimate1.py";
    WinExec(cmd.c_str(), SW_HIDE);
}

void MyFrame::OnCut(wxCommandEvent &event) {
    bool x = solve2();
    if (x == false) {
        wxString msg;
        msg.Printf(wxT("未检测到车牌号码"));
        wxMessageBox(msg, wxT("按下此键以继续"));
    }
}

void MyFrame::OnColor(wxCommandEvent &event) {
    bool y = solve3();
    if (y == false) {
        wxString msg;
        msg.Printf(wxT("未检测到车牌号码"));
        wxMessageBox(msg, wxT("按下此键以继续"));
    }
}

void MyFrame::OnChinese(wxCommandEvent &event) {
//    system("");
    string cmd = "Python36/python.exe -W ignore python/estimate_chinese.py";
    WinExec(cmd.c_str(), SW_HIDE);
}

void MyFrame::OnOther(wxCommandEvent &event) {
    string cmd = "Python36/python.exe -W ignore python/estimate.py";
    WinExec(cmd.c_str(), SW_HIDE);
}

void MyFrame::OnTrainChinese(wxCommandEvent &event) {
    system("Python36\\python.exe python\\train-license-province.py");
}

void MyFrame::OnTrainOther(wxCommandEvent &event) {
    system("Python36\\python.exe python\\train-license-digits.py");
}

void MyFrame::OnHandBook(wxCommandEvent &event) {
    wxString msg1, msg2, msg3, msg4;
    msg1.Printf(wxT("1: 通过选择车牌识别模式确定自己需要识别的图片或者摄像头实时识别"));
    msg2.Printf(wxT("2: 通过车牌定位模块选择车牌定位的方式即利用颜色或者边缘信息"));
    msg3.Printf(wxT("3: 通过车牌字符识别模块对车牌号码进行识别"));
    msg4.Printf(wxT("4: 通过车牌字符训练模块对车牌识别模型进行训练"));
    wxMessageBox(msg1, wxT("用户使用手册"));
    wxMessageBox(msg2, wxT("用户使用手册"));
    wxMessageBox(msg3, wxT("用户使用手册"));
    wxMessageBox(msg4, wxT("用户使用手册"));
}

void MyFrame::OnQuit(wxCommandEvent &event) {
    wxString msg;
    msg.Printf(wxT("你已成功退出车牌号码自动识别系统！"));
    wxMessageBox(msg, wxT("退出系统"));
    Close();
}

bool flag;

void on_mouse(int event, int x, int y, int flags, void *ustc) {
    if (event == CV_EVENT_LBUTTONDBLCLK)    //左键双击
    {
        flag = 0;
    }
}

void MyFrame::OnClickSave(wxMenuEvent &event) {
    VideoCapture cap(0);
    Mat frame;
    flag = 1;
    int cnt = 1;namedWindow("result");
    cvSetMouseCallback("result", on_mouse, 0);
    while (flag) {
        cap >> frame;
        string now = "saveImage/" + to_string(cnt) + ".jpg";
        cv::imwrite(now, frame);
        if (cnt == 20) cnt = 1;
        imshow("result", frame);
        waitKey(20);
        ++cnt;
    }
    for (int i = 2; i <= cnt; i++) {
        string now = "saveImage/" + to_string(i) + ".jpg";
        Mat img = cv::imread(now);
        bool flag = solve1();
        if (flag == false) continue;
        else {
            string cmd = "Python36/python.exe -W ignore python/estimate_chinese1.py";
            WinExec(cmd.c_str(), SW_HIDE);
            cmd = "Python36/python.exe -W ignore python/estimate1.py";
            WinExec(cmd.c_str(), SW_HIDE);
        }
    }
    destroyAllWindows();
}