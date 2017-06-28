#ifndef APP_H_
#define APP_H_

#include "wx/app.h"

class MainFrame;

class App : public wxApp {
public:
  virtual bool OnInit() override;

protected:
  void LoadIcon();

private:
  MainFrame* main_frame_;
};

DECLARE_APP(App)

#endif  // APP_H_
