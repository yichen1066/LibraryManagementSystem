#include "main_frame.h"

#include "wx/log.h"
#include "wx/sizer.h"
#include "wx/tglbtn.h"

#include "login_panel.h"
#include "resource_id.h"
#include "mysql_interface.h"
#include "register_panel.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ID_LOGIN_TEXT_BUTTON, MainFrame::OnLoginButtonClicked)
EVT_BUTTON(ID_REGISTER_TEXT_BUTTON, MainFrame::OnRegisterButtonClicked)
EVT_TOGGLEBUTTON(ID_REGISTER_PANEL_BITMAP_BUTTON, MainFrame::OnBitmapButtonClicked)
EVT_BUTTON(ID_REGISTER_PANEL_CANCEL_BUTTON, MainFrame::OnRegisterPanelCancelButtonClicked)
EVT_BUTTON(ID_REGISTER_PANEL_OK_BUTTON, MainFrame::OnRegisterPanelRegitserButtonClicked)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent,
                     wxWindowID id,
                     const wxString& title,
                     const wxPoint& position,
                     const wxSize& size)
    : wxFrame(parent, id, title, position, size)
    , login_panel_(nullptr)
    , register_panel_(nullptr)
    , is_user_name_accordance_(false)
    , is_password_accordance_(false) {
  login_panel_ = new LoginPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

  Connect(login_panel_->GetId(),
          wxEVT_KEY_DOWN,
          wxCommandEventHandler(MainFrame::OnEnterKeyDown));

  mysql_interface_ = new MySQLInterface();
  wxString error_msg;

  if (!mysql_interface_->ConnectMysql(_T("localhost"), _T("root"), _T("root"), _T("library"), 3306)) {
    error_msg = _T("连接数据库错误！");
  }
}

MainFrame::~MainFrame() {
}

void MainFrame::OnLoginButtonClicked(wxCommandEvent& evt) {
  std::vector<std::vector<std::string>> data;

  if (mysql_interface_->GetDataFromDB("SELECT* FROM user_info;", data)) {
    for (size_t i = 0; i < data.size(); ++i) {
      wxString user_name = data[i][0];
      wxString password = data[i][5];

      if (user_name == login_panel_->GetUsername()) {
        is_user_name_accordance_ = true;
      }
      if (password == login_panel_->GetPassword()) {
        is_password_accordance_ = true;
      }
    }

    if (is_user_name_accordance_ && is_password_accordance_) {
      login_panel_->Show(false);
    } else {
      wxLogMessage(_T("用户名或密码有错误，请重新输入！"));
    }
    return;
  }

  wxLogMessage(_T("查询表有误！"));
}

void MainFrame::OnRegisterButtonClicked(wxCommandEvent& evt) {
  login_panel_->Show(false);

  if (register_panel_ == nullptr) {
    register_panel_ = new RegisterPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mysql_interface_);
    register_panel_->SetClientSize(GetClientSize());
  } else {
    register_panel_->ClearAllInfo();
    register_panel_->Show(true);
  }
  register_panel_->SetFocus();
  SetTitle(_T("注册个人信息"));
}

void MainFrame::OnBitmapButtonClicked(wxCommandEvent& evt) {
  register_panel_->Show(false);
  login_panel_->Show(true);
  SetTitle(_T("图书管理系统1.0.1"));
}

void MainFrame::OnEnterKeyDown(wxCommandEvent& evt) {
  OnLoginButtonClicked(evt);
}

void MainFrame::OnRegisterPanelCancelButtonClicked(wxCommandEvent& evt) {
  register_panel_->Show(false);
  login_panel_->Show(true);
  SetTitle(_T("图书管理系统1.0.1"));
}

void MainFrame::OnRegisterPanelRegitserButtonClicked(wxCommandEvent& evt) {
  register_panel_->Show(false);
  login_panel_->Show(true);
  SetTitle(_T("图书管理系统1.0.1"));
}
