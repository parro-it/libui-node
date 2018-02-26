#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
/* TODO: this has to be removed */
struct Ui {
  static void main() { uiMain(); }

  static void mainSteps() { uiMainSteps(); }

  static int mainStep(int wait) { return uiMainStep(wait); }

  static void quit() { uiQuit(); }

  static void init() {}
};

NBIND_CLASS(Ui) {
  method(init);
  method(main);
  method(quit);
  method(mainStep);
  method(mainSteps);
}
