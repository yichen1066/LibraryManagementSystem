#include "text_button.h"

#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"

#include "color.h"
#include "app.h"

BEGIN_EVENT_TABLE(TextButton, wxControl)
EVT_PAINT(TextButton::OnPaint)
EVT_LEFT_DOWN(TextButton::OnMouseLeftDown)
EVT_LEFT_UP(TextButton::OnMouseLeftUp)
EVT_ENTER_WINDOW(TextButton::OnMouseEnter)
EVT_LEAVE_WINDOW(TextButton::OnMouseLeave)
EVT_MOUSE_CAPTURE_LOST(TextButton::OnMouseCaptureLost)
EVT_KEY_DOWN(TextButton::OnKeyDown)
EVT_KEY_UP(TextButton::OnKeyUp)
EVT_SET_FOCUS(TextButton::OnSetFocus)
EVT_KILL_FOCUS(TextButton::OnKillFocus)
END_EVENT_TABLE()

TextButton::TextButton()
    : ratio_x_(2)
    , ratio_y_(2)
    , pressed_(false)
    , accepts_focus_(true)
    , outline_focus_(false) {
}

TextButton::TextButton(wxWindow* parent, wxWindowID id, const wxString& label)
    : ratio_x_(2)
    , ratio_y_(2)
    , pressed_(false)
    , accepts_focus_(true)
    , outline_focus_(false) {
  Create(parent, id, label);
}

TextButton::~TextButton() {
}

bool TextButton::Create(wxWindow* parent, wxWindowID id, const wxString& label) {
  if (!wxControl::Create(parent, id, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS | wxBORDER_NONE)) {
    return false;
  }

  SetLabel(label);

  SetExtraStyle(GetExtraStyle() | wxWS_EX_PROCESS_UI_UPDATES);

  SetLayoutDirection(wxLayout_LeftToRight);
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);

  int cw = GetCharWidth();
  padding_.Set(cw, cw / 2);

  // Default colors.
  bg_normal_.Set(75, 75, 75);
  bg_select_.Set(51, 153, 255);
  fg_ = *wxWHITE;

  return true;
}

void TextButton::SetPaddingRatio(int ratio_x, int ratio_y) {
  ratio_x_ = ratio_x;
  ratio_y_ = ratio_y;
}

wxSize TextButton::DoGetBestSize() const {
  wxSize best_size;
  GetTextExtent(GetLabel(), &best_size.x, &best_size.y);
  best_size.IncBy(padding_.x * ratio_x_, padding_.y * ratio_y_);

  return best_size;
}

void TextButton::PostEvent() {
//   wxCommandEvent evt(evt_type, GetId());
//   evt.SetEventObject(this);
//   evt.SetString(GetLabel());
// 
//   wxWindow* top_window = wxGetApp().GetTopWindow();
//   top_window->GetEventHandler()->AddPendingEvent(evt);
  wxCommandEvent evt(wxEVT_BUTTON, GetId());
  evt.SetEventObject(this);
  evt.SetString(GetLabel());
  GetParent()->GetEventHandler()->AddPendingEvent(evt);
}

bool TextButton::Enable(bool enable) {
  bool enabled = wxControl::Enable(enable);
  Refresh();
  return enabled;
}

void TextButton::SetColors(const wxColor& bg_normal,
                           const wxColor& bg_select,
                           const wxColor& fg) {
  bg_normal_ = bg_normal;
  bg_select_ = bg_select;
  fg_ = fg;
}
void TextButton::OnPaint(wxPaintEvent& evt) {
  wxAutoBufferedPaintDC dc(this);

#if (!wxALWAYS_NATIVE_DOUBLE_BUFFER)
  dc.SetBackground(wxBrush(GetBackgroundColour()));
  dc.Clear(); // Color the background!
#endif

#ifdef __WXMAC__
  wxGraphicsContext* gc = dc.GetGraphicsContext();
#else
  wxGCDC gcdc(dc);
  wxGraphicsContext* gc = gcdc.GetGraphicsContext();
#endif  // __WXMAC__

  wxColour bg;

  if (IsEnabled()) {
    if (pressed_) {
      bg = DecColor(bg_select_, 20);
    } else if (this->IsMouseInWindow()) {
      bg = bg_select_;
    } else if (outline_focus_ && HasFocus()) {
      bg = IncColor(bg_select_, 20);
    } else {
      bg = bg_normal_;
    }
  } else {
    bg.Set(155, 155, 155);
  }

  gc->SetPen(wxPen(bg));
  gc->SetBrush(wxBrush(bg));

  wxRect client_rect = GetClientRect();

  gc->DrawRoundedRectangle(client_rect.GetLeft(),
                           client_rect.GetTop(),
                           client_rect.GetWidth() - 1,
                           client_rect.GetHeight() - 1,
                           0);

  dc.SetFont(GetFont());
  dc.SetTextForeground(*wxWHITE);
  dc.DrawLabel(GetLabel(), client_rect, wxALIGN_CENTER);

}

void TextButton::OnMouseLeftDown(wxMouseEvent& evt) {
  pressed_ = true;

  if (!HasCapture()) {
    CaptureMouse();
  }

  Refresh();
  evt.Skip();
}

void TextButton::OnMouseLeftUp(wxMouseEvent& evt) {
  if (GetClientRect().Contains(evt.GetPosition())) {
    PostEvent();
  }

  if (HasCapture()) {
    ReleaseMouse();
  }

  pressed_ = false;
  Refresh();

  evt.Skip();
}

void TextButton::OnMouseEnter(wxMouseEvent& evt) {
  Refresh();
  SetCursor(wxCURSOR_HAND);
  evt.Skip();
}

void TextButton::OnMouseLeave(wxMouseEvent& evt) {
  Refresh();
  evt.Skip();
}

void TextButton::OnMouseCaptureLost(wxMouseCaptureLostEvent& evt) {
  pressed_ = false;
  Refresh();
}

void TextButton::OnKeyDown(wxKeyEvent& evt) {
  evt.Skip();

  if (evt.GetKeyCode() == WXK_TAB) {
    wxNavigationKeyEvent nk_evt;
    nk_evt.SetFromTab(true);
    nk_evt.SetDirection(!evt.ShiftDown());
    GetParent()->GetEventHandler()->AddPendingEvent(nk_evt);
  }
}

void TextButton::OnKeyUp(wxKeyEvent& evt) {
  if (evt.GetKeyCode() == WXK_SPACE || evt.GetKeyCode() == WXK_RETURN) {
//    PostEvent();
  }
  evt.Skip();
}

void TextButton::OnSetFocus(wxFocusEvent& evt) {
  Refresh();
  evt.Skip();
}

void TextButton::OnKillFocus(wxFocusEvent& evt) {
  Refresh();
  evt.Skip();
}
