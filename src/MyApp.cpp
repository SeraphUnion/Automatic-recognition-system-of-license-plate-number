//
// Created by Administrator on 2018/5/6.
//
#include "MyApp.h"
#include "MyFrame.h"


IMPLEMENT_APP(MyApp)



bool MyApp::OnInit() {
    wxInitAllImageHandlers();
    auto *Frame = new MyFrame(0);

    Frame->Show();
    SetTopWindow(Frame);
    return true;
};