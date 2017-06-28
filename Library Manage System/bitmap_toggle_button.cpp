#include "bitmap_toggle_button.h"
#include "app.h"

IMPLEMENT_CLASS(BitmapToggleButton, BitmapButtonBase);

BitmapToggleButton::BitmapToggleButton(wxWindow* parent, wxWindowID id)
    : BitmapButtonBase(parent, id), toggle_(false), auto_switch_(true) {
}

BitmapToggleButton::~BitmapToggleButton() {
}

// #ifdef __WXMSW__
// WXLRESULT BitmapToggleButton::MSWWindowProc(WXUINT msg, WXWPARAM wparam, WXLPARAM lparam) {
//   if (msg == BM_GETCHECK) {
//     return toggle_ ? BST_CHECKED : BST_UNCHECKED;
//   }
//   return wxControl::MSWWindowProc(msg, wparam, lparam);
// }
// #endif  // __WXMSW__

BitmapButtonBase::State BitmapToggleButton::GetState() {
  if (!IsThisEnabled()) {  // NOTE: Don't use IsEnabled()!
    return DISABLED;
  }

  if (toggle_ || pressed_) {
    return PRESSED;
  } else if (hover_) {
    return HOVER;
  } else {
    return NORMAL;
  }
}

void BitmapToggleButton::PostEvent() {
//   if (auto_switch_) {
//     toggle_ = !toggle_;
//   }

  wxCommandEvent toggle_evt(wxEVT_TOGGLEBUTTON, GetId());
  toggle_evt.SetEventObject(this);
  toggle_evt.SetInt(toggle_ ? 1 : 0);  // Note: SetInt() affects IsChecked().

  GetParent()->GetEventHandler()->AddPendingEvent(toggle_evt);
}
