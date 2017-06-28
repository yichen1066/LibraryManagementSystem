#ifndef CSUI_TEXT_PANEL_H_
#define CSUI_TEXT_PANEL_H_
#pragma once

// A panel enclosing a text control.

#include "wx/panel.h"
#include "wx/textctrl.h"

////////////////////////////////////////////////////////////////////////////////

class TextCtrl : public wxTextCtrl {
  DECLARE_DYNAMIC_CLASS(TextCtrl)
  DECLARE_NO_COPY_CLASS(TextCtrl)
  DECLARE_EVENT_TABLE()

public:
  TextCtrl();

  TextCtrl(wxWindow* parent,
           wxWindowID id,
           const wxString& value = wxEmptyString,
           long style = 0,
           const wxValidator& validator = wxDefaultValidator);

protected:
  void OnSetFocus(wxFocusEvent& evt);
  void OnKillFocus(wxFocusEvent& evt);
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(kEvtTextCtrlFocus, 0)
DECLARE_EVENT_TYPE(kEvtTextCtrlKillFocus, 0)
END_DECLARE_EVENT_TYPES()
////////////////////////////////////////////////////////////////////////////////

class TextPanel : public wxPanel {
  DECLARE_DYNAMIC_CLASS(TextPanel)
  DECLARE_NO_COPY_CLASS(TextPanel)
  DECLARE_EVENT_TABLE()

public:
  TextPanel();

  // NOTE: id, value, style, validator and name are all of the internal
  // text ctrl instead of the panel itself.
  void Create(wxWindow* parent,
              wxWindowID id,
              const wxString& value = wxEmptyString,
              long style = 0,
              const wxValidator& validator = wxDefaultValidator);

  void SetBorderColor(const wxColour& border_color);

  virtual void SetFocus() override;

  // Mediators of text ctrl.

  wxString GetValue() const;
  void SetValue(const wxString& value) const;

  wxTextCtrl* text_ctrl() {
    return text_ctrl_;
  }

protected:
  // Override this to create a wxTextCtrl sub-class instance.
  virtual wxTextCtrl* CreateTextCtrl(wxWindowID id,
                                     const wxString& value,
                                     long style,
                                     const wxValidator& validator);
  void OnTextCtrlFocus(wxCommandEvent& evt);
  void OnTextCtrlKillFocus(wxCommandEvent& evt);
private:
  wxTextCtrl* text_ctrl_;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(kEvtTextPanelFocus, 0)
DECLARE_EVENT_TYPE(kEvtTextPanelKillFocus, 0)
END_DECLARE_EVENT_TYPES()

#endif // CSUI_TEXT_PANEL_H_
