#ifndef CSUI_BITMAP_BUTTON_BASE_H_
#define CSUI_BITMAP_BUTTON_BASE_H_
#pragma once

#include "wx/bitmap.h"
#include "wx/control.h"

class BitmapButtonBase : public wxControl {
  DECLARE_CLASS(BitmapButtonBase)
  DECLARE_NO_COPY_CLASS(BitmapButtonBase)
  DECLARE_EVENT_TABLE()

public:
  enum State {
    NORMAL = 0,
    HOVER,
    PRESSED,
    DISABLED,
    STATES,
  };

public:
  BitmapButtonBase();
  BitmapButtonBase(wxWindow* parent, wxWindowID id);
  virtual ~BitmapButtonBase();

  bool Create(wxWindow* parent, wxWindowID id);

  virtual bool Enable(bool enable) override;

  virtual bool AcceptsFocus() const override {
    return accepts_focus_;
  }
  virtual bool AcceptsFocusFromKeyboard() const override {
    return accepts_focus_;
  }

  void set_accepts_focus(bool accepts_focus) {
    accepts_focus_ = accepts_focus;
  }

  void SetBitmap(State state, const wxBitmap& bitmap) {
    bitmaps_[state] = bitmap;
  }

  void SetBitmaps(const wxBitmap& normal,
                  const wxBitmap& hover,
                  const wxBitmap& pressed,
                  const wxBitmap& disabled);

  void SetBitmaps(const wxBitmap& bitmap);

  void SetBitmapsNH(const wxBitmap& normal,
                    const wxBitmap& hover);

  void SetBitmapsND(const wxBitmap& normal,
                    const wxBitmap& disabled);

  void SetBitmapsNHD(const wxBitmap& normal,
                     const wxBitmap& hover,
                     const wxBitmap& disabled);

  // Highlight in some way to indicate that it's in focus.
  void OutlineFocus(bool outline_focus) {
    outline_focus_ = outline_focus;
  }

protected:
  void Init();

  wxSize DoGetBestSize() const override;

  virtual State GetState() = 0;

  virtual void PostEvent() = 0;

  void OnPaint(wxPaintEvent& evt);
  void OnMouseLeftDown(wxMouseEvent& evt);
  void OnMouseLeftUp(wxMouseEvent& evt);
  void OnMouseLeftDClick(wxMouseEvent& evt);
  void OnMouseEnter(wxMouseEvent& evt);
  void OnMouseLeave(wxMouseEvent& evt);
  void OnMouseCaptureLost(wxMouseCaptureLostEvent& evt);
  void OnSetFocus(wxFocusEvent& evt);
  void OnKillFocus(wxFocusEvent& evt);

protected:
  wxBitmap bitmaps_[STATES];

  bool pressed_;
  bool hover_;
  bool accepts_focus_;
  bool outline_focus_;
};

#endif  // CSUI_BITMAP_BUTTON_BASE_H_
