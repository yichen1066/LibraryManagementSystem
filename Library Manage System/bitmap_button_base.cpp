#include "bitmap_button_base.h"
#include "wx/dcbuffer.h"

IMPLEMENT_CLASS(BitmapButtonBase, wxControl);

BEGIN_EVENT_TABLE(BitmapButtonBase, wxControl)
EVT_PAINT               (BitmapButtonBase::OnPaint)
EVT_LEFT_DOWN           (BitmapButtonBase::OnMouseLeftDown)
EVT_LEFT_UP             (BitmapButtonBase::OnMouseLeftUp)
EVT_LEFT_DCLICK         (BitmapButtonBase::OnMouseLeftDClick)
EVT_ENTER_WINDOW        (BitmapButtonBase::OnMouseEnter)
EVT_LEAVE_WINDOW        (BitmapButtonBase::OnMouseLeave)
EVT_MOUSE_CAPTURE_LOST  (BitmapButtonBase::OnMouseCaptureLost)
EVT_SET_FOCUS           (BitmapButtonBase::OnSetFocus)
EVT_KILL_FOCUS          (BitmapButtonBase::OnKillFocus)
END_EVENT_TABLE()

BitmapButtonBase::BitmapButtonBase() {
  Init();
}

BitmapButtonBase::BitmapButtonBase(wxWindow* parent, wxWindowID id) {
  Init();
  Create(parent, id);
}

BitmapButtonBase::~BitmapButtonBase() {
}

bool BitmapButtonBase::Create(wxWindow* parent, wxWindowID id) {
  if (!wxControl::Create(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)) {
    return false;
  }

  SetExtraStyle(GetExtraStyle() | wxWS_EX_PROCESS_UI_UPDATES);

  SetBackgroundStyle(wxBG_STYLE_PAINT);
  SetBackgroundColour(parent->GetBackgroundColour());

  SetCursor(wxCURSOR_HAND);

  return true;
}

bool BitmapButtonBase::Enable(bool enable) {
  if (wxControl::Enable(enable)) {
    Refresh();
    return true;
  }
  return false;
}

void BitmapButtonBase::SetBitmaps(const wxBitmap& normal,
                                  const wxBitmap& hover,
                                  const wxBitmap& pressed,
                                  const wxBitmap& disabled) {
  bitmaps_[NORMAL] = normal;
  bitmaps_[HOVER] = hover;
  bitmaps_[PRESSED] = pressed;
  bitmaps_[DISABLED] = disabled;
}

void BitmapButtonBase::SetBitmaps(const wxBitmap& bitmap) {
  SetBitmaps(bitmap, bitmap, bitmap, bitmap);
}

void BitmapButtonBase::SetBitmapsNH(const wxBitmap& normal,
                                    const wxBitmap& hover) {
  SetBitmaps(normal, hover, hover, normal);
}

void BitmapButtonBase::SetBitmapsND(const wxBitmap& normal,
                                    const wxBitmap& disabled) {
  SetBitmaps(normal, normal, normal, disabled);
}

void BitmapButtonBase::SetBitmapsNHD(const wxBitmap& normal,
                                     const wxBitmap& hover,
                                     const wxBitmap& disabled) {
  SetBitmaps(normal, hover, hover, disabled);
}

void BitmapButtonBase::Init() {
  pressed_ = false;
  hover_ = false;
  accepts_focus_ = true;
  outline_focus_ = false;
}

wxSize BitmapButtonBase::DoGetBestSize() const {
  const wxBitmap& bitmap = bitmaps_[NORMAL];
  if (!bitmap.IsOk()) {
    return wxDefaultSize;
  }
  return wxSize(bitmap.GetWidth(), bitmap.GetHeight());
}

void BitmapButtonBase::OnPaint(wxPaintEvent& evt) {
  wxAutoBufferedPaintDC dc(this);
#if (!wxALWAYS_NATIVE_DOUBLE_BUFFER)
  dc.SetBackground(wxBrush(GetBackgroundColour()));
  dc.Clear();
#endif

  State state = GetState();

  const wxBitmap& bitmap = bitmaps_[state];
  if (bitmap.IsOk()) {
    dc.DrawBitmap(bitmap, 0, 0, true);
  }

  // Draw a dotted rectangle to indicate the focus state.
  if (outline_focus_ && HasFocus()) {
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(wxPen(*wxLIGHT_GREY, 1, wxPENSTYLE_DOT));
    dc.DrawRectangle(GetClientRect());
  }
}

void BitmapButtonBase::OnMouseLeftDown(wxMouseEvent& evt) {
  pressed_ = true;

  if (!HasCapture()) {
    CaptureMouse();
  }

  Refresh();
  evt.Skip();
}

void BitmapButtonBase::OnMouseLeftUp(wxMouseEvent& evt) {
  if (HasCapture()) {
    ReleaseMouse();
  }

  if (pressed_) {
    if (GetClientRect().Contains(evt.GetPosition())) {
      PostEvent();
    }
  }

  pressed_ = false;
  Refresh();

  evt.Skip();
}

// NOTE:
// If you double click this control, the mouse events would be:
//   - Left Down
//   - Left Up
//   - Left DClick
//   - Left Up
// There won't be two Left Down, instead the second Left Down is replaced
// by Left DClick.
void BitmapButtonBase::OnMouseLeftDClick(wxMouseEvent& evt) {
  pressed_ = true;

  Refresh();
  evt.Skip();
}

void BitmapButtonBase::OnMouseEnter(wxMouseEvent& evt) {
  hover_ = true;
  Refresh();
  evt.Skip();
}

void BitmapButtonBase::OnMouseLeave(wxMouseEvent& evt) {
  hover_ = false;
  Refresh();
  evt.Skip();
}

void BitmapButtonBase::OnMouseCaptureLost(wxMouseCaptureLostEvent& evt) {
  pressed_ = false;
  hover_ = false;
  Refresh();
}

void BitmapButtonBase::OnSetFocus(wxFocusEvent& evt) {
  Refresh();
  evt.Skip();
}

void BitmapButtonBase::OnKillFocus(wxFocusEvent& evt) {
  Refresh();
  evt.Skip();
}
