#ifndef MAIN_FRAME_H_
#define MAIN_FRAME_H_

#include "wx/frame.h"

class LoginPanel;
class MySQLInterface;
class RegisterPanel;

class MainFrame : public wxFrame {
  DECLARE_EVENT_TABLE()
  DECLARE_NO_COPY_CLASS(MainFrame)

public:
  MainFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& position,
            const wxSize& size);

  virtual ~MainFrame();

protected:
  void OnLoginButtonClicked(wxCommandEvent& evt);
  void OnRegisterButtonClicked(wxCommandEvent& evt);
  void OnBitmapButtonClicked(wxCommandEvent& evt);
  void OnEnterKeyDown(wxCommandEvent& evt);

  void OnRegisterPanelCancelButtonClicked(wxCommandEvent& evt);
  void OnRegisterPanelRegitserButtonClicked(wxCommandEvent& evt);

private:
  LoginPanel* login_panel_;
  RegisterPanel* register_panel_;

  MySQLInterface* mysql_interface_;

  bool is_user_name_accordance_;
  bool is_password_accordance_;
};

#endif  // MAIN_FRMAE_H_
