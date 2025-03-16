#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WImage.h>
#include "calculator_explosive.h"
#include "utils.h"

class CalculatorApp : public Wt::WApplication
{
public:
	CalculatorApp(const Wt::WEnvironment& env);
private:

	Wt::WContainerWidget* container;
	Wt::WVBoxLayout* main_box;
	std::vector<Wt::WLineEdit*> inputs;
	void setRoot();
	void createContainer();
	void fillMainBox();
	void createButton();

	void generatePanels(int count_c4, int count_rocket, int count_explosive_ammo, int count_satchel, int count_beancan_grenade);
	void generatePanelC4(int count_c4, Wt::WHBoxLayout* hbox);
	void generatePanelRocket(int count_rocket);
	void generatePanelExplosiveAmmo(int count_explosive_ammo);
	void generatePanelSatchel(int count_satchel);
	void generatePanelBeancanGrenade(int count_beancan_grenade);
};
