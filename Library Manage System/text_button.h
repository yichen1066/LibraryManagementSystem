#ifndef TEXT_BUTTON_H_
#define TEXT_BUTTON_H_

#include "wx/control.h"

class TextButton : public wxControl {
  DECLARE_NO_COPY_CLASS(TextButton)
  DECLARE_EVENT_TABLE()

public:
  TextButton();
  TextButton(wxWindow* parent, wxWindowID id, const wxString& label);
  virtual ~TextButton();

  bool Create(wxWindow* parent, wxWindowID id, const wxString& label);

  void SetPaddingRatio(int ratio_x, int ratio_y);

  virtual bool AcceptsFocus() const override {
    return accepts_focus_;
  }
  virtual bool AcceptsFocusFromKeyboard() const override {
    return accepts_focus_;
  }

  void set_accepts_focus(bool accepts_focus) {
    accepts_focus_ = accepts_focus;
  }

  void SetColors(const wxColor& bg_normal,
                 const wxColor& bg_select,
                 const wxColor& fg);

  virtual bool Enable(bool enable = true) override;

  // Highlight in some way to indicate that it's in focus.
  void OutlineFocus(bool outline_focus) {
    outline_focus_ = outline_focus;
  }

protected:
  virtual wxSize DoGetBestSize() const override;
  void PostEvent();

  void OnPaint(wxPaintEvent& evt);
  void OnMouseLeftDown(wxMouseEvent& evt);
  void OnMouseLeftUp(wxMouseEvent& evt);
  void OnMouseEnter(wxMouseEvent& evt);
  void OnMouseLeave(wxMouseEvent& evt);
  void OnMouseCaptureLost(wxMouseCaptureLostEvent& evt);
  void OnSetFocus(wxFocusEvent& evt);
  void OnKillFocus(wxFocusEvent& evt);
  void OnKeyDown(wxKeyEvent& evt);
  void OnKeyUp(wxKeyEvent& evt);

private:
//  wxSize min_size_;
  wxSize padding_;

  bool pressed_;
  bool accepts_focus_;
  bool outline_focus_;

  wxColor bg_normal_;
  wxColor bg_select_;
  wxColor fg_;

  int ratio_x_;
  int ratio_y_;
};

#endif // CSUI_TEXT_BUTTON_H_
