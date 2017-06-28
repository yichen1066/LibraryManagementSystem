#ifndef STATIC_TEXT_BASE_H_ 
#define STATIC_TEXT_BASE_H_  

#include "wx/wx.h"  

class StaticTextBase :public wxStaticText {
public:
  StaticTextBase();
  virtual ~StaticTextBase();

  virtual bool HasTransparentBackground();
  void SetBackground(wxBitmap bitmap);

protected:
  wxBitmap bitmap_;
};

#endif  //STATIC_TEXT_BASE_H_
