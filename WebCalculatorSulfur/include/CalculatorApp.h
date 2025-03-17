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
	Wt::WContainerWidget* current_panels = nullptr;
	void setRoot();
	void createContainer();
	void fillMainBox();
	void createButton();

	void generatePanels(int count_c4, int count_rocket, int count_explosive_ammo, int count_satchel, int count_beancan_grenade);
	std::unique_ptr<Wt::WContainerWidget> generateRow(int value, std::string resource, std::string target);
	std::unique_ptr<Wt::WContainerWidget> generatePanelC4(int count_c4);
	std::unique_ptr<Wt::WContainerWidget> generatePanelRocket(int count_rocket);
	std::unique_ptr<Wt::WContainerWidget> generatePanelExplosiveAmmo(int count_explosive_ammo);
	std::unique_ptr<Wt::WContainerWidget> generatePanelSatchel(int count_satchel);
	std::unique_ptr<Wt::WContainerWidget> generatePanelBeancanGrenade(int count_beancan_grenade);
};
