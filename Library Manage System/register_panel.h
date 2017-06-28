#ifndef REGISTER_PANEL_H_
#define REGISTRE_PANEL_H_

#include "wx/panel.h"
#include "wx/stattext.h"

class TextPanel;
class wxBoxSizer;
class wxTextCtrl;
class BitmapToggleButton;
class TextButton;
class wxRadioButton;
class wxChoice;
class MySQLInterface;

class RegisterPanel : public wxPanel {
  DECLARE_EVENT_TABLE()

public:
  RegisterPanel(wxWindow* parent,
                wxWindowID id,
                const wxPoint& position,
                const wxSize& size,
                MySQLInterface* mysql_interface);
  virtual ~RegisterPanel();

  void ClearAllInfo();

protected:
  void CreateControls();

  TextPanel* CreateTextPanel(wxWindowID id, long style);
  wxStaticText* CreateWarningLabel(const wxString& label_str);

  void LayoutUserAccount(wxBoxSizer* sizer, int space_x);
  void LayoutUserName(wxBoxSizer* sizer, int space_x);
  void LayoutUserGender(wxBoxSizer* sizer, int space_x);
  void LayoutUserBirthday(wxBoxSizer* sizer, int space_x);
  void LayoutUserType(wxBoxSizer* sizer, int space_x);
  void LayoutUserPassword(wxBoxSizer* sizer, int space_x);
  void LayoutUserConfirmPassword(wxBoxSizer* sizer, int space_x);
  void LayoutUserEmali(wxBoxSizer* sizer, int space_x);
  void LayoutUserComments(wxBoxSizer* sizer, int space_x);
  void LayoutButton(wxBoxSizer* sizer, int space_x);

  void OnUserAccountTextPanelFocus(wxCommandEvent& evt);
  void OnUserAccountTextPanelKillFocus(wxCommandEvent& evt);
  void OnUserNameTextPanelFocus(wxCommandEvent& evt);
  void OnUserNameTextPanelKillFocus(wxCommandEvent& evt);
  void OnUserPasswordTextPanelFocus(wxCommandEvent& evt);
  void OnuserPasswordTextPanelKillFocus(wxCommandEvent& evt);
  void OnUserConfirmPasswordTextPanelFocus(wxCommandEvent& evt);
  void OnuserConfirmPasswordTextPanelKillFocus(wxCommandEvent& evt);

  void OnCancelButtonClicked(wxCommandEvent& evt);
  void OnOkButtonClicked(wxCommandEvent& evt);

  void PostEvent(int id);

  bool IsEssentailControlEmpty();
  bool IsUserAccountMeetRequirements();
  bool IsChineseString(const char* str);

  bool IsPasswordMeetRequirements();
  bool IsStringHasBlank(const wxString& str);
  bool IsConfirmPasswordMeetRequirements();

  bool HandleWriteRegisterInfo();
  bool IsAccountExist();

private:
  wxStaticText* user_account_;
  TextPanel* user_account_text_panel_;
  wxStaticText* user_account_warning_label_;

  wxStaticText* user_password_;
  TextPanel* user_password_text_panel_;
  wxStaticText* user_password_warning_label_;

  wxStaticText* user_confirm_password_;
  TextPanel* user_confirm_password_text_panel_;
  wxStaticText* user_confirm_password_warning_label_;

  wxStaticText* user_name_;
  TextPanel* user_name_text_panel_;
  wxStaticText* user_name_warning_label_;

  wxStaticText* user_gender_;
  wxRadioButton* radio_button_male_;
  wxRadioButton* radio_button_female_;

  wxStaticText* user_birthday_;
  TextPanel* user_birthday_text_panel_;

  wxStaticText* user_type_;
  wxChoice* choice_;

  wxStaticText* user_email_;
  wxTextCtrl* user_emali_text_ctrl_;

  wxStaticText* user_comments_;
  wxTextCtrl* user_comments_text_ctrl_;

  TextButton* cancel_button_;
  TextButton* ok_button_;

  BitmapToggleButton* bitmap_button_;
  MySQLInterface* mysql_interface_;
};

#endif  // REGISTRE_PANEL_H_
