  #include "text_panel.h"
#include "wx/sizer.h"
#include "resource_id.h"

////////////////////////////////////////////////////////////////////////////////

DEFINE_EVENT_TYPE(kEvtTextCtrlFocus)
DEFINE_EVENT_TYPE(kEvtTextCtrlKillFocus)

IMPLEMENT_DYNAMIC_CLASS(TextCtrl, wxTextCtrl)

BEGIN_EVENT_TABLE(TextCtrl, wxTextCtrl)
EVT_SET_FOCUS(TextCtrl::OnSetFocus)
EVT_KILL_FOCUS(TextCtrl::OnKillFocus)
END_EVENT_TABLE();

TextCtrl::TextCtrl() {
}

TextCtrl::TextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, long style, const wxValidator& validator)
   : wxTextCtrl(parent, id, value, wxDefaultPosition, wxDefaultSize, style, validator) {
}

void TextCtrl::OnSetFocus(wxFocusEvent& evt) {
  wxCommandEvent cmd_evt(kEvtTextCtrlFocus, GetId());
  cmd_evt.SetEventObject(this);
  GetParent()->GetEventHandler()->AddPendingEvent(cmd_evt);
  evt.Skip();
}

void TextCtrl::OnKillFocus(wxFocusEvent& evt) {
  wxCommandEvent cmd_evt(kEvtTextCtrlKillFocus, GetId());
  cmd_evt.SetEventObject(this);
  GetParent()->GetEventHandler()->AddPendingEvent(cmd_evt);
  evt.Skip();
}

////////////////////////////////////////////////////////////////////////////////

DEFINE_EVENT_TYPE(kEvtTextPanelFocus)
DEFINE_EVENT_TYPE(kEvtTextPanelKillFocus)

IMPLEMENT_DYNAMIC_CLASS(TextPanel, wxPanel)

BEGIN_EVENT_TABLE(TextPanel, wxPanel)
END_EVENT_TABLE();

TextPanel::TextPanel() {
  Connect(GetId(),
          kEvtTextCtrlFocus,
          wxCommandEventHandler(TextPanel::OnTextCtrlFocus));
  Connect(GetId(),
          kEvtTextCtrlKillFocus,
          wxCommandEventHandler(TextPanel::OnTextCtrlKillFocus));
}

void TextPanel::Create(wxWindow* parent,
                       wxWindowID id,
                       const wxString& value,
                       long style,
                       const wxValidator& validator) {
  wxPanel::Create(parent, wxID_ANY);

  text_ctrl_ = CreateTextCtrl(id, value, style, validator);
  text_ctrl_->SetLayoutDirection(wxLayout_LeftToRight);

  wxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
  vsizer->Add(text_ctrl_, 1, wxEXPAND | wxALL, 1);
  SetSizer(vsizer);
}

void TextPanel::SetBorderColor(const wxColour& border_color) {
  if (border_color.IsOk()) {
    SetBackgroundColour(border_color);
  } else {
    SetBackgroundColour(GetParent()->GetBackgroundColour());
  }
  Refresh();
}

void TextPanel::SetFocus() {
  text_ctrl_->SetFocus();
}

wxString TextPanel::GetValue() const {
  return text_ctrl_->GetValue();
}

void TextPanel::SetValue(const wxString& value) const {
  text_ctrl_->SetValue(value);
}

wxTextCtrl* TextPanel::CreateTextCtrl(wxWindowID id,
                                      const wxString& value,
                                      long style,
                                      const wxValidator& validator) {
  return new TextCtrl(this, id, value, style, validator);
}

void TextPanel::OnTextCtrlFocus(wxCommandEvent& evt) {
  SetBorderColor(GetParent()->GetBackgroundColour());
  wxCommandEvent evt_focus(kEvtTextPanelFocus, GetId());
  evt_focus.SetEventObject(this);
  GetParent()->GetEventHandler()->AddPendingEvent(evt_focus);
}

void TextPanel::OnTextCtrlKillFocus(wxCommandEvent& evt) {
  wxCommandEvent evt_kill_focus(kEvtTextPanelKillFocus, GetId());
  evt_kill_focus.SetEventObject(this);
  GetParent()->GetEventHandler()->AddPendingEvent(evt_kill_focus);
}
