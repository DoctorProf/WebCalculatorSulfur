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
#include <iostream>

class CalculatorApp : public Wt::WApplication
{
public:
	CalculatorApp(const Wt::WEnvironment& env);
private:
	void generateImage();
	void generateTextBoxes();
	void generateButton();

	void calculateC4(int count);
	void calculateRocket(int count);
	void calculateExplosiveAmmo(int count);
	void calculateSatchel(int count);
	void calculateBeancanGrenade(int count);
};
