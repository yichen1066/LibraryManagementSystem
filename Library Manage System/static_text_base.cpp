#include "static_text_base.h"  

StaticTextBase::StaticTextBase() {
}

StaticTextBase::~StaticTextBase() {
}

bool StaticTextBase::HasTransparentBackground() {
  return true;
}

void StaticTextBase::SetBackground(wxBitmap bitmap) {
  bitmap_ = bitmap;
}
