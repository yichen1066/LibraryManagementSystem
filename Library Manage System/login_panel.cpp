#include "login_panel.h"

#include "wx/bitmap.h"
#include "wx/dcbuffer.h"
#include "wx/stattext.h"
#include "wx/sizer.h"
#include "wx/font.h"

#include "static_text.h"
#include "text_button.h"
#include "resource_id.h"

BEGIN_EVENT_TABLE(LoginPanel, wxPanel)
EVT_ERASE_BACKGROUND(LoginPanel::OnEraseBackGround)
EVT_PAINT(LoginPanel::OnPaint)
EVT_CHAR_HOOK(LoginPanel::OnEnterKeyDown)
END_EVENT_TABLE()

LoginPanel::LoginPanel(wxWindow* parent,
                       wxWindowID id,
                       const wxPoint& point,
                       const wxSize& size)
    : wxPanel(parent, id, point, size) {
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
  CreateControls();
}

LoginPanel::~LoginPanel() {
}

const wxString& LoginPanel::GetUsername() {
  user_name_ = user_name_ctrl_->GetValue();
  return user_name_;
}

const wxString& LoginPanel::GetPassword() {
  password_ = password_ctrl_->GetValue();
  return password_;
}

void LoginPanel::OnPaint(wxPaintEvent& evt) {
  wxBufferedPaintDC dc(this);
  dc.Clear();

  wxBitmap bitmap = wxImage(_T("D:\\c++\\Library Manage System\\1.bmp"), wxBITMAP_TYPE_BMP);
  dc.DrawBitmap(bitmap, wxDefaultPosition);
}

void LoginPanel::OnEraseBackGround(wxEraseEvent& evt) {
}

void LoginPanel::OnEnterKeyDown(wxKeyEvent& evt) {
  if (evt.GetUnicodeKey() == WXK_RETURN) {
    PostEvent();
  }
  evt.Skip();
}

void LoginPanel::CreateControls() {
  wxBoxSizer* top_sizer_ = new wxBoxSizer(wxVERTICAL);
  top_sizer_->AddSpacer(180);

  StaticText* description_text = new StaticText();
  description_text->Create(this, wxID_ANY, _T("图书管理系统"));
  description_text->SetFont(wxFont(35, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  wxBitmap bitmap = wxImage(_T("D:\\c++\\Library Manage System\\1.bmp"), wxBITMAP_TYPE_BMP);
  description_text->SetBackground(bitmap);

  top_sizer_->Add(description_text, 0, wxALIGN_CENTRE);
  top_sizer_->AddSpacer(70);

  wxFont font(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

  StaticText* user_name = new StaticText();
  user_name->Create(this, wxID_ANY, _T("用户名："));
  user_name->SetFont(font);
  user_name->SetBackground(bitmap);

  wxBoxSizer* user_name_sizer = new wxBoxSizer(wxHORIZONTAL);
  user_name_sizer->Add(user_name, 0, wxALIGN_LEFT);

  user_name_ctrl_ = new wxTextCtrl(this,
                                   wxID_ANY,
                                   wxEmptyString,
                                   wxDefaultPosition,
                                   wxDefaultSize);
  user_name_sizer->Add(user_name_ctrl_, 0, wxALIGN_LEFT);
  top_sizer_->Add(user_name_sizer, 0, wxALIGN_CENTRE);
  top_sizer_->AddSpacer(5);

  StaticText* password_ = new StaticText();
  password_->Create(this, wxID_ANY, _T("密    码："));
  password_->SetFont(font);
  password_->SetBackground(bitmap);

  wxBoxSizer* password_sizer = new wxBoxSizer(wxHORIZONTAL);
  password_sizer->Add(password_, 0, wxALIGN_LEFT);

  password_ctrl_ = new wxTextCtrl(this,
                                  wxID_ANY,
                                  wxEmptyString,
                                  wxDefaultPosition,
                                  wxDefaultSize,
                                  wxTE_PASSWORD);
  password_sizer->Add(password_ctrl_, 0, wxALIGN_LEFT);
  top_sizer_->Add(password_sizer, 0, wxALIGN_CENTRE);
  top_sizer_->AddSpacer(5);

  wxBoxSizer* bitmap_button_sizer = new wxBoxSizer(wxHORIZONTAL);
  login_button_ = new TextButton(this, ID_LOGIN_TEXT_BUTTON, _T("登录"));
  bitmap_button_sizer->AddSpacer(454);
  bitmap_button_sizer->Add(login_button_, 0, wxALIGN_LEFT);
  bitmap_button_sizer->AddSpacer(5);

  register_button_ = new TextButton(this, ID_REGISTER_TEXT_BUTTON, _T("注册"));
  bitmap_button_sizer->Add(register_button_, 0, wxALIGN_LEFT);

  top_sizer_->Add(bitmap_button_sizer, 0, wxALIGN_LEFT);
  SetSizer(top_sizer_);
  Layout();
}

void LoginPanel::PostEvent() {
  wxCommandEvent evt(wxEVT_KEY_DOWN, GetId());
  evt.SetEventObject(this);
  GetParent()->GetEventHandler()->AddPendingEvent(evt);
}
