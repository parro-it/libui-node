#include "../libui/ui.h"
#include "ui-node.h"
#include "nbind/nbind.h"


struct uiDrawStrokeParams {
	int Cap;
	int Join;
	// TODO what if this is 0? on windows there will be a crash with dashing
	double Thickness;
	double MiterLimit;
	double *Dashes;
	// TOOD what if this is 1 on Direct2D?
	// TODO what if a dash is 0 on Cairo or Quartz?
	int NumDashes;
	double DashPhase;
};

class DrawStrokeParams {
	private:
		int Cap;
		int Join;
		double Thickness;
		double MiterLimit;
		std::vector<double> Dashes;
		int NumDashes;
		double DashPhase;
	public:
		DrawStrokeParams(int cap, int join, double thickness, double miterLimit,std::vector<double> dashes,int numDashes,double DashPhase);
		int getCap();
		int getJoin();
		double getThickness();
		double getMiterLimit();
		std::vector<double> getDashes();
		int getNumDashes();
		double getDashPhase();

		void setCap(int value);
		void setJoin(int value);
		void setThickness(double value);
		void setMiterLimit(double value);
		void setDashes(std::vector<double> value);
		void setNumDashes(int value);
		void setDashPhase(double value);

		uiDrawStrokeParams *toStruct();

		void toJS(nbind::cbOutput output);
}


NBIND_CLASS(DrawStrokeParams) {
  construct<double, Color>();
  method(getColor);
  method(setColor);
  method(getPos);
  method(setPos);
  method(toJS);
  getset(getColor, setColor);
  getset(getPos, setPos);
}
