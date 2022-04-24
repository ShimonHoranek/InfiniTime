#include "displayapp/screens/settings/Settings.h"
#include <lvgl/lvgl.h>
#include <array>
#include "displayapp/screens/List.h"
#include "displayapp/Apps.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"

using namespace Pinetime::Applications::Screens;

Settings::Settings(Pinetime::Applications::DisplayApp* app, Pinetime::Controllers::Settings& settingsController)
  : Screen(app),
    settingsController {settingsController},
    screens {app,
             settingsController.GetSettingsMenu(),
             {[this]() -> std::unique_ptr<Screen> {
                return CreateScreen1();
              },
              [this]() -> std::unique_ptr<Screen> {
                return CreateScreen2();
              },
              [this]() -> std::unique_ptr<Screen> {
                return CreateScreen3();
              },
              [this]() -> std::unique_ptr<Screen> {
               return CreateScreen4();
              },
             },
             Screens::ScreenListModes::UpDown} {
}

Settings::~Settings() {
  lv_obj_clean(lv_scr_act());
}

bool Settings::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return screens.OnTouchEvent(event);
}

std::unique_ptr<Screen> Settings::CreateScreen1() {
  std::array<Screens::List::Applications, 4> applications {{
    {Symbols::sun, "Obrazovka", Apps::SettingDisplay},
    {Symbols::eye, "Probuzeni", Apps::SettingWakeUp},
    {Symbols::clock, "Format casu", Apps::SettingTimeFormat},
    {Symbols::home, "Cifernik", Apps::SettingWatchFace},
  }};

  return std::make_unique<Screens::List>(0, 4, app, settingsController, applications);
}

std::unique_ptr<Screen> Settings::CreateScreen2() {
  std::array<Screens::List::Applications, 4> applications {{
    {Symbols::shoe, "Kroky", Apps::SettingSteps},
    {Symbols::clock, "Nastaveni datumu", Apps::SettingSetDate},
    {Symbols::clock, "Nastaveni casu", Apps::SettingSetTime},
    {Symbols::batteryHalf, "Baterie", Apps::BatteryInfo}}};

  return std::make_unique<Screens::List>(1, 4, app, settingsController, applications);
}

std::unique_ptr<Screen> Settings::CreateScreen3() {

  std::array<Screens::List::Applications, 4> applications {{
    {Symbols::clock, "Upominky", Apps::SettingChimes},
    {Symbols::tachometer, "Kalibrace otr.", Apps::SettingShakeThreshold},
    {Symbols::check, "Firmware", Apps::FirmwareValidation},
    {Symbols::bluetooth, "Bluetooth", Apps::SettingBluetooth}
  }};

  return std::make_unique<Screens::List>(2, 4, app, settingsController, applications);
}

std::unique_ptr<Screen> Settings::CreateScreen4() {

  std::array<Screens::List::Applications, 4> applications {{
    {Symbols::list, "O systemu", Apps::SysInfo},
    {Symbols::none, "None", Apps::None},
    {Symbols::none, "None", Apps::None},
    {Symbols::none, "None", Apps::None}
  }};

  return std::make_unique<Screens::List>(3, 4, app, settingsController, applications);
}
