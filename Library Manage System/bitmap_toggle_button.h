#ifndef CSUI_BITMAP_TOGGLE_BUTTON_H_
#define CSUI_BITMAP_TOGGLE_BUTTON_H_
#pragma once

// A replacement of wxBitmapToggleButton.

#include "bitmap_button_base.h"
#include "wx/tglbtn.h" // For wxEVT_TOGGLEBUTTON, etc.

// Note:
// BitmapToggleButton emits the same event as wxBitmapToggleButton:
//   Event type: wxEVT_TOGGLEBUTTON
//   Macro: EVT_TOGGLEBUTTON(id, func)

class BitmapToggleButton : public BitmapButtonBase {
  DECLARE_CLASS(BitmapToggleButton)
  DECLARE_NO_COPY_CLASS(BitmapToggleButton)

public:
  BitmapToggleButton(wxWindow* parent, wxWindowID id);
  virtual ~BitmapToggleButton();

  void set_auto_switch(bool auto_switch) {
    auto_switch_ = auto_switch;
  }

  // Switch toggle state.
  void Toggle() {
    toggle_ = !toggle_;
  }

  bool toggle() const {
    return toggle_;
  }
  void set_toggle(bool toggle) {
    toggle_ = toggle;
    Refresh();
  }

  void SetToggleBitmaps(const wxBitmap& normal, const wxBitmap& pressed) {
    SetBitmaps(normal, pressed, pressed, normal);
  }

protected:
// #ifdef __WXMSW__
//   // Auto test support.
//   virtual WXLRESULT MSWWindowProc(WXUINT msg, WXWPARAM wparam, WXLPARAM lparam) override;
// #endif  // __WXMSW__

  BitmapButtonBase::State GetState() override;

  void PostEvent() override;

private:
  bool toggle_;
  bool auto_switch_;
};

#endif  // CSUI_BITMAP_TOGGLE_BUTTON_H_
