#ifndef STATIC_TEXT_H_ 
#define STATIC_TEXT_H_  

#include "static_text_base.h"  
#include "wx/msw/private.h"  

class StaticText :public StaticTextBase {
  DECLARE_EVENT_TABLE()
public:
  StaticText();
  virtual ~StaticText();

protected:
  void OnEraseBackground(wxEraseEvent& event);
  virtual WXHBRUSH DoMSWControlColor(WXHDC pDC, wxColour colBg, WXHWND hWnd);

private:
  wxBrush *brush_;

  wxRect last_rect_;
  wxBitmap bg_cache_;
};

#endif  // STATIC_TEXT_H_
