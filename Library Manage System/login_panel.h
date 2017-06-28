#ifndef LOGIN_PANEL_H_
#define LOGIN_PANEL_H_

#include "wx/panel.h"
#include "text_button.h"

class wxTextCtrl;

class LoginPanel : public wxPanel {
  DECLARE_EVENT_TABLE()

public:
  LoginPanel(wxWindow* parent,
             wxWindowID id,
             const wxPoint& position,
             const wxSize& size);
  virtual ~LoginPanel();

  const wxString& GetUsername();
  const wxString& GetPassword();

protected:
  void OnPaint(wxPaintEvent& evt);
  void OnEraseBackGround(wxEraseEvent& evt);
  void OnEnterKeyDown(wxKeyEvent& evt);

  void CreateControls();
  void PostEvent();

private:
  TextButton* login_button_;
  TextButton* register_button_;

  wxTextCtrl* user_name_ctrl_;
  wxTextCtrl* password_ctrl_;

  wxString user_name_;
  wxString password_;
};

#endif  // LOGIN_PANEL_H_
