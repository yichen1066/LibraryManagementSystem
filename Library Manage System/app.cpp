#include "app.h"

#include "wx/font.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"
#include "wx/icon.h"
#include "wx/busyinfo.h"

#include "mysql_interface.h"
#include "static_text.h"
#include "text_button.h"
#include "main_frame.h"

IMPLEMENT_APP(App)

bool App::OnInit() {
  wxInitAllImageHandlers();

  wxWindowDisabler disableAll;
  wxBusyInfo info("Loading...", NULL);

  main_frame_ = new MainFrame(NULL,
                              wxID_ANY,
                              _T("图书管理系统1.0.1"),
                              wxDefaultPosition,
                              wxDefaultSize);

  main_frame_->SetSize(wxSize(960, 720));
  main_frame_->CenterOnScreen();
  main_frame_->SetBackgroundColour(*wxWHITE);

//   main_frame_->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~
//                              (wxSYSTEM_MENU |
//                               wxRESIZE_BORDER |
//                               wxMAXIMIZE_BOX |
//                               wxCLIP_CHILDREN |
//                               wxCLOSE_BOX |
//                               wxCAPTION));
  main_frame_->SetWindowStyle(wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION);
  LoadIcon();
//  main_frame_->Maximize(true);
  main_frame_->Show(true);
  return true;
}

void App::LoadIcon() {
  wxInitAllImageHandlers();
  wxIcon icon(_T("bitmap\\Library.ico"), wxBITMAP_TYPE_ANY, 16, 16);
  main_frame_->SetIcon(icon);
}
