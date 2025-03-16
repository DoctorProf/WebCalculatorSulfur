#include "../include/CalculatorApp.h"

CalculatorApp::CalculatorApp(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
	setRoot();
	createContainer();
	fillMainBox();
	createButton();
}

void CalculatorApp::setRoot()
{
	setTitle(Wt::WString::fromUTF8("Calculator"));
	useStyleSheet("resources/style.css?v=" + std::to_string(time(nullptr)));
	root()->addStyleClass("root");
	root()->setHeight("100vh");
}

void CalculatorApp::createContainer()
{
	container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
	container->addStyleClass("container");
}

void CalculatorApp::fillMainBox()
{
	main_box = container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	auto pairs_image_lineedit = main_box->addLayout(std::make_unique<Wt::WHBoxLayout>());
	pairs_image_lineedit->setSpacing(12);

	for (int i = 0; i < 5; ++i) {
		auto pair_box = pairs_image_lineedit->addLayout(std::make_unique<Wt::WVBoxLayout>());
		pair_box->setSpacing(12);
		auto image = pair_box->addWidget(std::make_unique<Wt::WImage>(), 0, Wt::AlignmentFlag::Center);
		switch (i) {
		case 0:
			image->setImageLink("resources/c4.png");
			break;
		case 1:
			image->setImageLink("resources/rocket.png");
			break;
		case 2:
			image->setImageLink("resources/explosive_ammo.png");
			break;
		case 3:
			image->setImageLink("resources/satchel.png");
			break;
		case 4:
			image->setImageLink("resources/beancan_grenade.png");
			break;
		}
		image->setWidth(128);
		image->setHeight(128);

		auto input = pair_box->addWidget(std::make_unique<Wt::WLineEdit>(), 0, Wt::AlignmentFlag::Center);
		input->setStyleClass("input");
		inputs.push_back(input);
	}
}

void CalculatorApp::createButton()
{
	auto calculateButton = main_box->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString::fromUTF8("Calculate")));
	calculateButton->addStyleClass("button");

	calculateButton->clicked().connect([=]() {
		int c4 = converter::string_to_int(inputs[0]->text().toUTF8());
		int rocket = converter::string_to_int(inputs[1]->text().toUTF8());
		int explosive_ammo = converter::string_to_int(inputs[2]->text().toUTF8());
		int satchel = converter::string_to_int(inputs[3]->text().toUTF8());
		int beancan_grenade = converter::string_to_int(inputs[4]->text().toUTF8());
		generatePanels(c4, rocket, explosive_ammo, satchel, beancan_grenade);
		});
}

void CalculatorApp::generatePanels(int count_c4, int count_rocket, int count_explosive_ammo, int count_satchel, int count_beancan_grenade)
{
	//auto panels = std::make_unique<Wt::WContainerWidget>();
	//auto hbox = panels->setLayout(std::make_unique<Wt::WHBoxLayout>());

	//generatePanelC4(count_c4, hbox);
	//main_box->addWidget(std::move(panels));
}
void CalculatorApp::generatePanelC4(int count_c4, Wt::WHBoxLayout* hbox)
{
	//auto vbox = hbox->addLayout(std::make_unique<Wt::WVBoxLayout>());
	//vbox->addWidget(std::make_unique<Wt::WImage>("resources/c4.png"));
}
void CalculatorApp::generatePanelRocket(int count_rocket)
{
}
void CalculatorApp::generatePanelExplosiveAmmo(int count_explosive_ammo)
{
}
void CalculatorApp::generatePanelSatchel(int count_satchel)
{
}
void CalculatorApp::generatePanelBeancanGrenade(int count_beancan_grenade)
{
}