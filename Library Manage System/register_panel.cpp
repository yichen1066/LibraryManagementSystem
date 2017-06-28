#include "register_panel.h"

#include "wx/sizer.h"
#include "wx/button.h"
#include "wx/dcbuffer.h"
#include "wx/radiobut.h"
#include "wx/choice.h"
#include "wx/stattext.h"
#include "wx/textctrl.h"
#include "wx/msgdlg.h"

#include "text_panel.h"
#include "resource_id.h"
#include "text_button.h"
#include "bitmap_toggle_button.h"
#include "defs.h"
#include "mysql_interface.h"

#define kLabelUserName                 _T("姓名：")
#define kLabelUserGender               _T("性别：")
#define kLabelUserBirthday             _T("出生日期：")
#define kLabelUserType                 _T("读者类型：")
#define kLabelUserAccount              _T("用户名：")
#define kLabelUserPassword             _T("密码：")
#define kLabelUserConfirmPassword      _T("确认密码：")
#define kLabelUserEmail                _T("Email：")
#define kLabelUserComments             _T("备注：")
#define kWarningLabel                  _T("此项为必填项")

#define kGap                           20

BEGIN_EVENT_TABLE(RegisterPanel, wxPanel)
EVT_BUTTON(ID_REGISTER_PANEL_CANCEL_BUTTON, RegisterPanel::OnCancelButtonClicked)
EVT_BUTTON(ID_REGISTER_PANEL_OK_BUTTON, RegisterPanel::OnOkButtonClicked)
END_EVENT_TABLE()

static wxFont normal_label_font(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
static wxFont warning_label_font(10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
static const wxColour grey_color(135, 135, 135);

RegisterPanel::RegisterPanel(wxWindow* parent,
                             wxWindowID id,
                             const wxPoint& position,
                             const wxSize& size,
                             MySQLInterface* mysql_interface)
    : wxPanel(parent, id, position, size)
    , mysql_interface_(mysql_interface) {
  CreateControls();
  SetBackgroundColour(wxColour(237,237,237));

  Connect(user_account_text_panel_->GetId(),
          kEvtTextPanelFocus,
          wxCommandEventHandler(RegisterPanel::OnUserAccountTextPanelFocus));
  Connect(user_account_text_panel_->GetId(),
          kEvtTextPanelKillFocus,
          wxCommandEventHandler(RegisterPanel::OnUserAccountTextPanelKillFocus));
  Connect(user_name_text_panel_->GetId(),
          kEvtTextPanelFocus,
          wxCommandEventHandler(RegisterPanel::OnUserNameTextPanelFocus));
  Connect(user_name_text_panel_->GetId(),
          kEvtTextPanelKillFocus,
          wxCommandEventHandler(RegisterPanel::OnUserNameTextPanelKillFocus));
  Connect(user_password_text_panel_->GetId(),
          kEvtTextPanelFocus,
          wxCommandEventHandler(RegisterPanel::OnUserPasswordTextPanelFocus));
  Connect(user_password_text_panel_->GetId(),
          kEvtTextPanelKillFocus,
          wxCommandEventHandler(RegisterPanel::OnuserPasswordTextPanelKillFocus));
  Connect(user_confirm_password_text_panel_->GetId(),
          kEvtTextPanelFocus,
          wxCommandEventHandler(RegisterPanel::OnUserConfirmPasswordTextPanelFocus));
  Connect(user_confirm_password_text_panel_->GetId(),
          kEvtTextPanelKillFocus,
          wxCommandEventHandler(RegisterPanel::OnuserConfirmPasswordTextPanelKillFocus));
}

RegisterPanel::~RegisterPanel() {
}

void RegisterPanel::ClearAllInfo() {
  user_account_text_panel_->SetValue(wxEmptyString);
  user_password_text_panel_->SetValue(wxEmptyString);
  user_confirm_password_text_panel_->SetValue(wxEmptyString);
  user_name_text_panel_->SetValue(wxEmptyString);
  radio_button_male_->SetValue(false);
  radio_button_female_->SetValue(false);
  user_birthday_text_panel_->SetValue(wxEmptyString);
  choice_->SetLabel(wxEmptyString);
  user_emali_text_ctrl_->Clear();
  user_comments_text_ctrl_->Clear();

  user_name_warning_label_->SetLabel(wxEmptyString);
  user_name_text_panel_->SetBorderColor(GetBackgroundColour());

  user_account_warning_label_->SetLabel(wxEmptyString);
  user_account_text_panel_->SetBorderColor(GetBackgroundColour());

  user_password_warning_label_->SetLabel(wxEmptyString);
  user_password_text_panel_->SetBorderColor(GetBackgroundColour());

  user_confirm_password_warning_label_->SetLabel(wxEmptyString);
  user_confirm_password_text_panel_->SetBorderColor(GetBackgroundColour());
}

void RegisterPanel::CreateControls() {
  wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_account = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserAccount(user_account, 30);
  top_sizer->Add(user_account, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_name = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserName(user_name, 30);
  top_sizer->Add(user_name, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_gender = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserGender(user_gender, 30);
  top_sizer->Add(user_gender, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_birthday = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserBirthday(user_birthday, 30);
  top_sizer->Add(user_birthday, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_type = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserType(user_type, 30);
  top_sizer->Add(user_type, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_password = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserPassword(user_password, 30);
  top_sizer->Add(user_password, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_confirm_password = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserConfirmPassword(user_confirm_password, 30);
  top_sizer->Add(user_confirm_password, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_email = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserEmali(user_email, 30);
  top_sizer->Add(user_email, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(kGap);

  wxBoxSizer* user_comments = new wxBoxSizer(wxHORIZONTAL);
  LayoutUserComments(user_comments, 30);
  top_sizer->Add(user_comments, 0, wxALIGN_LEFT);
  top_sizer->AddSpacer(3 * kGap);

  wxBoxSizer* button = new wxBoxSizer(wxHORIZONTAL);
  LayoutButton(button, 80);
  top_sizer->Add(button, 0, wxALIGN_CENTER);

  SetSizer(top_sizer);
  Layout();
}

TextPanel* RegisterPanel::CreateTextPanel(wxWindowID id, long style) {
  TextPanel* text_panel = new TextPanel();
  text_panel->Create(this,
                     id,
                     wxEmptyString,
                     style);

  text_panel->text_ctrl()->SetFont(normal_label_font);
  return text_panel;
}

wxStaticText* RegisterPanel::CreateWarningLabel(const wxString& label_str) {
  wxStaticText* label = new wxStaticText(this, wxID_ANY, label_str);
  label->SetForegroundColour(*wxRED);
  label->SetFont(warning_label_font);
  return label;
}

void RegisterPanel::LayoutUserAccount(wxBoxSizer* sizer, int space_x) {
  user_account_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_account_->SetFont(normal_label_font);
  user_account_->SetLabel(kLabelUserAccount);

  bitmap_button_ = new BitmapToggleButton(this, ID_REGISTER_PANEL_BITMAP_BUTTON);
  wxBitmap normal(NORMAL_PATH, wxBITMAP_TYPE_PNG);
  wxBitmap hover(HOVER_PATH, wxBITMAP_TYPE_PNG);
  wxBitmap disabled(DISABLED_PATH, wxBITMAP_TYPE_PNG);
  wxBitmap pressed(PRESSED_PATH, wxBITMAP_TYPE_PNG);

  bitmap_button_->SetBitmaps(normal, hover, pressed, disabled);
  bitmap_button_->SetToolTip(_T("返回"));

  sizer->AddSpacer(20);
  sizer->Add(bitmap_button_, 0, wxALIGN_CENTER);

  sizer->AddSpacer(247);
  sizer->Add(user_account_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  user_account_text_panel_ = CreateTextPanel(ID_TEXT_PANEL_ACCOUNT, 0);
  sizer->Add(user_account_text_panel_, 0, wxALIGN_CENTER);

  wxStaticText* text = new wxStaticText(this, wxID_ANY, _T("*"));
  text->SetFont(normal_label_font);
  sizer->AddSpacer(5);
  sizer->Add(text, 0, wxALIGN_CENTER);

  sizer->AddSpacer(5);
  user_account_warning_label_ = CreateWarningLabel(wxEmptyString);
  sizer->Add(user_account_warning_label_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutUserName(wxBoxSizer* sizer, int space_x) {
  user_name_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_name_->SetFont(normal_label_font);
  user_name_->SetLabel(kLabelUserName);

  sizer->AddSpacer(320);
  sizer->Add(user_name_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  user_name_text_panel_ = CreateTextPanel(ID_TEXT_PANEL_NAME, 0);
  sizer->Add(user_name_text_panel_, 0, wxALIGN_CENTER);

  wxStaticText* text = new wxStaticText(this, wxID_ANY, _T("*"));
  text->SetFont(normal_label_font);
  sizer->AddSpacer(5);
  sizer->Add(text, 0, wxALIGN_CENTER);

  sizer->AddSpacer(5);
  user_name_warning_label_ = CreateWarningLabel(wxEmptyString);
  sizer->Add(user_name_warning_label_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutUserGender(wxBoxSizer* sizer, int space_x) {
  user_gender_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_gender_->SetFont(normal_label_font);
  user_gender_->SetLabel(kLabelUserGender);

  sizer->AddSpacer(320);
  sizer->Add(user_gender_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  radio_button_male_ = new wxRadioButton(this,
                                         ID_REGISTER_PANEL_RADIO_BUTTON_MALE,
                                         _T("男"),
                                         wxDefaultPosition,
                                         wxDefaultSize,
                                         wxRB_GROUP);
  radio_button_male_->SetFont(normal_label_font);
  radio_button_male_->SetValue(false);

  radio_button_female_ = new wxRadioButton(this,
                                                         ID_REGISTRE_PANEL_RADIO_BUTTON_FEMALE,
                                                         _T("女"));
  radio_button_female_->SetFont(normal_label_font);

  sizer->Add(radio_button_male_, 0, wxALIGN_CENTER | wxALL, 5);
  sizer->Add(radio_button_female_, 0, wxALIGN_CENTER | wxALL, 5);
}

void RegisterPanel::LayoutUserBirthday(wxBoxSizer* sizer, int space_x) {
  user_birthday_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_birthday_->SetFont(normal_label_font);
  user_birthday_->SetLabel(kLabelUserBirthday);

  sizer->AddSpacer(280);
  sizer->Add(user_birthday_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  user_birthday_text_panel_ = CreateTextPanel(ID_TEXT_PANEL_BIRTHDAY, 0);
  sizer->Add(user_birthday_text_panel_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutUserType(wxBoxSizer* sizer, int space_x) {
  user_type_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_type_->SetFont(normal_label_font);
  user_type_->SetLabel(kLabelUserType);

  sizer->AddSpacer(280);
  sizer->Add(user_type_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  wxArrayString strings;
  strings.Add(_T("学生"));
  strings.Add(_T("教师"));
  strings.Add(_T("上班族"));
  strings.Add(_T("自由职业者"));
  strings.Add(_T("其他"));

  choice_ = new wxChoice(this,
                                  ID_REGISTER_PANEL_COMBOBOX,
                                  wxDefaultPosition,
                                  wxDefaultSize,
                                  strings);

  choice_->SetFont(normal_label_font);

  sizer->Add(choice_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutUserPassword(wxBoxSizer* sizer, int space_x) {
  user_password_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_password_->SetFont(normal_label_font);
  user_password_->SetLabel(kLabelUserPassword);

  sizer->AddSpacer(320);
  sizer->Add(user_password_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  user_password_text_panel_ = CreateTextPanel(ID_TEXT_PANEL_PASSWORD, wxTE_PASSWORD);
  sizer->Add(user_password_text_panel_, 0, wxALIGN_CENTER);

  wxStaticText* text = new wxStaticText(this, wxID_ANY, _T("*"));
  text->SetFont(normal_label_font);
  sizer->AddSpacer(5);
  sizer->Add(text, 0, wxALIGN_CENTER);

  sizer->AddSpacer(5);
  user_password_warning_label_ = CreateWarningLabel(wxEmptyString);
  sizer->Add(user_password_warning_label_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutUserConfirmPassword(wxBoxSizer* sizer, int space_x) {
  user_confirm_password_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_confirm_password_->SetFont(normal_label_font);
  user_confirm_password_->SetLabel(kLabelUserConfirmPassword);

  sizer->AddSpacer(280);
  sizer->Add(user_confirm_password_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  user_confirm_password_text_panel_ = CreateTextPanel(ID_TEXT_PANEL_CONFIRM_PASSWORD, wxTE_PASSWORD);
  sizer->Add(user_confirm_password_text_panel_, 0, wxALIGN_CENTER);

  wxStaticText* text = new wxStaticText(this, wxID_ANY, _T("*"));
  text->SetFont(normal_label_font);
  sizer->AddSpacer(5);
  sizer->Add(text, 0, wxALIGN_CENTER);

  sizer->AddSpacer(5);
  user_confirm_password_warning_label_ = CreateWarningLabel(wxEmptyString);
  sizer->Add(user_confirm_password_warning_label_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutUserEmali(wxBoxSizer* sizer, int space_x) {
  user_email_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_email_->SetFont(normal_label_font);
  user_email_->SetLabel(kLabelUserEmail);

  sizer->AddSpacer(313);
  sizer->Add(user_email_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  user_emali_text_ctrl_ = new wxTextCtrl(this,
                                         ID_TEXT_CTRL_EMAIL,
                                         wxEmptyString,
                                         wxDefaultPosition,
                                         wxSize(300, 30));
  sizer->Add(user_emali_text_ctrl_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutUserComments(wxBoxSizer* sizer, int space_x) {
  user_comments_ = new wxStaticText(this, wxID_ANY, wxEmptyString);
  user_comments_->SetFont(normal_label_font);
  user_comments_->SetLabel(kLabelUserComments);

  sizer->AddSpacer(320);
  sizer->Add(user_comments_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  user_comments_text_ctrl_= new wxTextCtrl(this,
                                         ID_TEXT_CTRL_EMAIL,
                                         wxEmptyString,
                                         wxDefaultPosition,
                                         wxSize(300, 90),
                                         wxTE_MULTILINE);
  sizer->Add(user_comments_text_ctrl_, 0, wxALIGN_CENTER);
}

void RegisterPanel::LayoutButton(wxBoxSizer* sizer, int space_x) {
  cancel_button_ = new TextButton(this, ID_REGISTER_PANEL_CANCEL_BUTTON, _T("取消"));
  cancel_button_->SetPaddingRatio(20, 3);

  sizer->Add(cancel_button_, 0, wxALIGN_CENTER);
  sizer->AddSpacer(space_x);

  ok_button_ = new TextButton(this, ID_REGISTER_PANEL_OK_BUTTON, _T("注册"));
  const wxColour kBtnHighlightColor(51, 153, 255);
  ok_button_->SetColors(kBtnHighlightColor, kBtnHighlightColor, *wxWHITE);

  ok_button_->SetPaddingRatio(20, 3);

  sizer->Add(ok_button_, 0, wxALIGN_CENTER);
}

void RegisterPanel::OnUserAccountTextPanelFocus(wxCommandEvent& evt) {
  user_account_warning_label_->SetForegroundColour(grey_color);
  user_account_warning_label_->SetLabel(_T("中英文均可，最长14个英文或7个汉字"));
}

void RegisterPanel::OnUserAccountTextPanelKillFocus(wxCommandEvent& evt) {
  user_account_warning_label_->SetLabel(wxEmptyString);
}

void RegisterPanel::OnUserNameTextPanelFocus(wxCommandEvent& evt) {
  user_name_warning_label_->SetForegroundColour(grey_color);
  user_name_warning_label_->SetLabel(_T("填写您的真实姓名"));
}

void RegisterPanel::OnUserNameTextPanelKillFocus(wxCommandEvent& evt) {
  user_name_warning_label_->SetLabel(wxEmptyString);
}

void RegisterPanel::OnUserPasswordTextPanelFocus(wxCommandEvent& evt) {
  user_password_warning_label_->SetForegroundColour(grey_color);
  user_password_warning_label_->SetLabel(_T("长度为6~14个字符，支持数字和大小写字母\n不允许有空格"));
}

void RegisterPanel::OnuserPasswordTextPanelKillFocus(wxCommandEvent& evt) {
  user_password_warning_label_->SetLabel(wxEmptyString);
}

void RegisterPanel::OnUserConfirmPasswordTextPanelFocus(wxCommandEvent& evt) {
  user_confirm_password_warning_label_->SetForegroundColour(grey_color);
  user_confirm_password_warning_label_->SetLabel(_T("再次确认你的密码"));
}

void RegisterPanel::OnuserConfirmPasswordTextPanelKillFocus(wxCommandEvent& evt) {
  user_confirm_password_warning_label_->SetLabel(wxEmptyString);
}

void RegisterPanel::OnCancelButtonClicked(wxCommandEvent& evt) {
  PostEvent(ID_REGISTER_PANEL_CANCEL_BUTTON);
}

void RegisterPanel::OnOkButtonClicked(wxCommandEvent& evt) {
  int bit = 0;
  if (!IsEssentailControlEmpty()) {
    if (IsUserAccountMeetRequirements()) {
      bit |= 1 << 0;
    }
    if (IsPasswordMeetRequirements()) {
      bit |= 1 << 1;
    }
    if (IsConfirmPasswordMeetRequirements()) {
      bit |= 1 << 2;
    }
  }

  if (bit == 7) {
    if (IsAccountExist()) {
      user_account_warning_label_->SetForegroundColour(*wxRED);
      user_account_warning_label_->SetLabel(_T("用户名已存在"));
      return;
    }
    if (HandleWriteRegisterInfo()) {
      wxMessageDialog* msg_dlg = new wxMessageDialog(this, _T("注册成功！"), _T("消息提醒"), wxOK);
      msg_dlg->ShowModal();
      PostEvent(ID_REGISTER_PANEL_OK_BUTTON);
    }
  }
}

void RegisterPanel::PostEvent(int id) {
  wxCommandEvent evt(wxEVT_BUTTON, id);
  evt.SetEventObject(this);
  GetParent()->GetEventHandler()->AddPendingEvent(evt);
}

bool RegisterPanel::IsEssentailControlEmpty() {
  bool is_user_account_empty = (user_account_text_panel_->GetValue() == wxEmptyString) ? true : false;
  bool is_user_name_empty = (user_name_text_panel_->GetValue() == wxEmptyString) ? true : false;
  bool is_user_password_empty = (user_password_text_panel_->GetValue() == wxEmptyString) ? true : false;
  bool is_user_confirm_password_empty = (user_confirm_password_text_panel_->GetValue() == wxEmptyString) ? true : false;

  if (is_user_account_empty) {
    user_account_warning_label_->SetForegroundColour(*wxRED);
    user_account_warning_label_->SetLabel(kWarningLabel);
    user_account_text_panel_->SetBorderColor(*wxRED);
  }
  if (is_user_name_empty) {
    user_name_warning_label_->SetForegroundColour(*wxRED);
    user_name_warning_label_->SetLabel(kWarningLabel);
    user_name_text_panel_->SetBorderColor(*wxRED);
  }
  if (is_user_password_empty) {
    user_password_warning_label_->SetForegroundColour(*wxRED);
    user_password_warning_label_->SetLabel(kWarningLabel);
    user_password_text_panel_->SetBorderColor(*wxRED);
  }
  if (is_user_confirm_password_empty) {
    user_confirm_password_warning_label_->SetForegroundColour(*wxRED);
    user_confirm_password_warning_label_->SetLabel(kWarningLabel);
    user_confirm_password_text_panel_->SetBorderColor(*wxRED);
  }

  if (is_user_account_empty | is_user_name_empty | is_user_password_empty | is_user_confirm_password_empty) {
    return true;
  } else {
    return false;
  }
}

bool RegisterPanel::IsUserAccountMeetRequirements() {
  wxString user_account = user_account_text_panel_->GetValue();
  const char* str = user_account.c_str();
  bool is_true = true;

  if (IsChineseString(str)) {
    if (user_account.length() > 7) {
      user_account_warning_label_->SetForegroundColour(*wxRED);
      user_account_warning_label_->SetLabel(_T("中文不能超过7个汉字"));
      is_true = false;
    }
  } else {
    if (user_account.length() > 14) {
      user_account_warning_label_->SetForegroundColour(*wxRED);
      user_account_warning_label_->SetLabel(_T("英文不能超过14个字符"));
      is_true = false;
    }
  }
  return is_true;
}

bool RegisterPanel::IsChineseString(const char* str) {
  bool is_chinese = false;
  char c;
  while (c = *str++) {
    if ((c & 0x80) && (*str & 0x80)) {
      is_chinese = true;
      break;
    }
  }
  return is_chinese;
}

bool RegisterPanel::IsPasswordMeetRequirements() {
  wxString password = user_password_text_panel_->GetValue();
  bool is_true = true;

  if (password.length() < 6) {
    user_password_warning_label_->SetForegroundColour(*wxRED);
    user_password_warning_label_->SetLabel(_T("密码长度不能低于6位"));
    is_true = false;
  } else if (password.length() > 14) {
    user_password_warning_label_->SetForegroundColour(*wxRED);
    user_password_warning_label_->SetLabel(_T("密码长度不能高于14位"));
    is_true = false;
  } else {
    if (IsStringHasBlank(password)) {
      user_password_warning_label_->SetForegroundColour(*wxRED);
      user_password_warning_label_->SetLabel(_T("密码中不允许有空格"));
      is_true = false;
    }
  }
  return is_true;
}

bool RegisterPanel::IsStringHasBlank(const wxString& str) {
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (*it == ' ') {
      return true;
    }
  }
  return false;
}

bool RegisterPanel::IsConfirmPasswordMeetRequirements() {
  if (IsPasswordMeetRequirements()) {
    if (user_password_text_panel_->GetValue() != user_confirm_password_text_panel_->GetValue()) {
      user_confirm_password_warning_label_->SetForegroundColour(*wxRED);
      user_confirm_password_warning_label_->SetLabel(_T("密码填写不一致"));
      return false;
    }
  }
  return true;
}

bool RegisterPanel::HandleWriteRegisterInfo() {
  mysql_interface_->CreateDBTable("Create table user_info(account varchar(15), name varchar(15), sex varchar(4), birthday varchar(20), type varchar(15), password varchar(15), email varchar(20), note varchar(100))");
  std::string account = user_account_text_panel_->GetValue().c_str();
  std::string name = user_name_text_panel_->GetValue().c_str();

  std::string sex;
  if (radio_button_male_->GetValue()) {
    sex = "男";
  }
  if (radio_button_female_->GetValue()) {
    sex = "女";
  }

  std::string birthday = user_birthday_text_panel_->GetValue().c_str();

  std::string type;
  int index = choice_->GetSelection();
  if (index != wxNOT_FOUND) {
    type = choice_->GetString(index);
  }

  std::string password = user_password_text_panel_->GetValue();
  std::string email = user_emali_text_ctrl_->GetValue();
  std::string note = user_comments_text_ctrl_->GetValue();

  std::string mysql_query = "insert into user_info values('" + account + "'" + "," + "'" + name + "'" + "," + "'" +
    sex + "'" + "," + "'" + birthday + "'" + "," + "'" + type + "'" + "," + "'" + password + "'" + "," + "'" +
    email + "'" + "," + "'" + note + "'" + ");";

  if (!mysql_interface_->WriteDataToDB(mysql_query)) {
    return false;
    // TODO(Yi Chen) : error handle
  }
  return true;
}

bool RegisterPanel::IsAccountExist() {
  std::vector<std::vector<std::string>> data;

  if (mysql_interface_->GetDataFromDB("SELECT* FROM user_info;", data)) {
    int i = data.size();
    for (size_t i = 0; i < data.size(); ++i) {
      wxString user_account = data[i][0];
      if (user_account_text_panel_->GetValue() == user_account) {
        return true;
      }
    }
    return false;
  }
  return false;
}
