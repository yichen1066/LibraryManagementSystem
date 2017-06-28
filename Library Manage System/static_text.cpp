#include "static_text.h"

BEGIN_EVENT_TABLE(StaticText, StaticTextBase)
EVT_ERASE_BACKGROUND(StaticText::OnEraseBackground)
END_EVENT_TABLE()

StaticText::StaticText() {
  SetBackgroundStyle(wxBG_STYLE_ERASE);
  SetForegroundColour(*wxWHITE);
  brush_ = new wxBrush(wxNullColour, wxBRUSHSTYLE_TRANSPARENT);
}

StaticText::~StaticText() {
}

void StaticText::OnEraseBackground(wxEraseEvent& event) {
  wxRect rect = GetRect();

  if (last_rect_ != rect) {
    last_rect_ = rect;

    int height = bitmap_.GetHeight();
    int width = bitmap_.GetWidth();

    rect.height = (height < (rect.y + rect.height)) ? (height - rect.y) : rect.height;
    rect.width = (width < (rect.x + rect.width)) ? (width - rect.x) : rect.width;

    assert(bitmap_.GetHeight() >= (rect.y + rect.height));
    assert(bitmap_.GetWidth() >= (rect.x + rect.width));

    bg_cache_ = bitmap_.GetSubBitmap(
      wxRect(rect.x, rect.y, rect.width, rect.height));
  }
  event.GetDC()->DrawBitmap(bg_cache_, 0, 0);
}

WXHBRUSH StaticText::DoMSWControlColor(WXHDC pDC, wxColour colBg, WXHWND hWnd) {
  HDC hdc = (HDC)pDC;
  ::SetTextColor(hdc, wxColourToRGB(GetForegroundColour()));
  return (WXHBRUSH)brush_->GetResourceHandle();
}
