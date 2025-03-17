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
	if (current_panels) {
		main_box->removeWidget(current_panels);
		current_panels = nullptr;
	}
	current_panels = main_box->addWidget(std::make_unique<Wt::WContainerWidget>());
	current_panels->setStyleClass("panel-container");
	auto hbox = current_panels->setLayout(std::make_unique<Wt::WHBoxLayout>());
	hbox->addWidget(std::move(generatePanelC4(count_c4)));
	hbox->addWidget(std::move(generatePanelRocket(count_rocket)));
	hbox->addWidget(std::move(generatePanelExplosiveAmmo(count_explosive_ammo)));
	hbox->addWidget(std::move(generatePanelSatchel(count_satchel)));
	hbox->addWidget(std::move(generatePanelBeancanGrenade(count_beancan_grenade)));
}
std::unique_ptr<Wt::WContainerWidget> CalculatorApp::generateRow(int value, std::string resource, std::string target)
{
	auto row_container = std::make_unique<Wt::WContainerWidget>();
	row_container->setStyleClass("row-container");
	auto hbox = row_container->setLayout(std::make_unique<Wt::WHBoxLayout>());

	auto value_text = std::make_unique<Wt::WText>(std::to_string(value));
	value_text->setStyleClass("text");
	hbox->addWidget(std::move(value_text), 0, Wt::AlignmentFlag::Center);

	auto resource_image = std::make_unique<Wt::WImage>(resource);
	resource_image->setStyleClass("resource-image");
	hbox->addWidget(std::move(resource_image), 0, Wt::AlignmentFlag::Center);

	auto to_text = std::make_unique<Wt::WText>(" to ");
	to_text->setStyleClass("text");
	hbox->addWidget(std::move(to_text), 0, Wt::AlignmentFlag::Center);

	auto target_image = std::make_unique<Wt::WImage>(target);
	target_image->setStyleClass("target-image");
	hbox->addWidget(std::move(target_image), 0, Wt::AlignmentFlag::Center);

	return row_container;
}
std::unique_ptr<Wt::WContainerWidget> CalculatorApp::generatePanelC4(int count_c4)
{
	auto c4_container = std::make_unique<Wt::WContainerWidget>();
	c4_container->addStyleClass("item-container");
	auto vbox = c4_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	json materials = calculator_explosive::calculateC4(count_c4);
	vbox->addWidget(generateRow(materials["sulfur"], "resources/sulfur.png", "resources/c4.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_powder"], "resources/sulfur.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["charcoal_to_powder"], "resources/charcoal.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["powder_to_exp"], "resources/powder.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["lgf_to_exp"], "resources/low_grade_fuel.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_exp"], "resources/sulfur.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["metal_to_exp"], "resources/metal.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["microcircuits"], "resources/microcircuits.png", "resources/c4.png"));
	vbox->addWidget(generateRow(materials["cloth"], "resources/cloth.png", "resources/c4.png"));
	return c4_container;
}
std::unique_ptr<Wt::WContainerWidget> CalculatorApp::generatePanelRocket(int count_rocket)
{
	auto rocket_container = std::make_unique<Wt::WContainerWidget>();
	rocket_container->addStyleClass("item-container");
	auto vbox = rocket_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	json materials = calculator_explosive::calculateRocket(count_rocket);
	vbox->addWidget(generateRow(materials["sulfur"], "resources/sulfur.png", "resources/rocket.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_powder"], "resources/sulfur.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["charcoal_to_powder"], "resources/charcoal.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["powder_to_exp"], "resources/powder.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["lgf_to_exp"], "resources/low_grade_fuel.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_exp"], "resources/sulfur.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["metal_to_exp"], "resources/metal.png", "resources/explosives.png"));
	vbox->addWidget(generateRow(materials["powder_to_rocket"], "resources/powder.png", "resources/rocket.png"));
	vbox->addWidget(generateRow(materials["pipe"], "resources/pipe.png", "resources/rocket.png"));
	return rocket_container;
}
std::unique_ptr<Wt::WContainerWidget> CalculatorApp::generatePanelExplosiveAmmo(int count_explosive_ammo)
{
	auto explosive_ammo_container = std::make_unique<Wt::WContainerWidget>();
	explosive_ammo_container->addStyleClass("item-container");
	auto vbox = explosive_ammo_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	json materials = calculator_explosive::calculateExplosiveAmmo(count_explosive_ammo);
	vbox->addWidget(generateRow(materials["sulfur"], "resources/sulfur.png", "resources/explosive_ammo.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_powder"], "resources/sulfur.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["charcoal_to_powder"], "resources/charcoal.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_ammo"], "resources/sulfur.png", "resources/explosive_ammo.png"));
	vbox->addWidget(generateRow(materials["metal_to_ammo"], "resources/metal.png", "resources/explosive_ammo.png"));
	return explosive_ammo_container;
}
std::unique_ptr<Wt::WContainerWidget> CalculatorApp::generatePanelSatchel(int count_satchel)
{
	auto satchel_container = std::make_unique<Wt::WContainerWidget>();
	satchel_container->addStyleClass("item-container");
	auto vbox = satchel_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	json materials = calculator_explosive::calculateSatchel(count_satchel);
	vbox->addWidget(generateRow(materials["sulfur"], "resources/sulfur.png", "resources/satchel.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_powder"], "resources/sulfur.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["charcoal_to_powder"], "resources/charcoal.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["powder_to_grenade"], "resources/powder.png", "resources/beancan_grenade.png"));
	vbox->addWidget(generateRow(materials["metal_to_grenade"], "resources/metal.png", "resources/beancan_grenade.png"));
	vbox->addWidget(generateRow(materials["cloth_to_stash"], "resources/cloth.png", "resources/small_stash.png"));
	vbox->addWidget(generateRow(materials["rope"], "resources/rope.png", "resources/satchel.png"));
	return satchel_container;
}
std::unique_ptr<Wt::WContainerWidget> CalculatorApp::generatePanelBeancanGrenade(int count_beancan_grenade)
{
	auto beancan_grenade_container = std::make_unique<Wt::WContainerWidget>();
	beancan_grenade_container->addStyleClass("item-container");
	auto vbox = beancan_grenade_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	json materials = calculator_explosive::calculateBeancanGrenade(count_beancan_grenade);
	vbox->addWidget(generateRow(materials["sulfur"], "resources/sulfur.png", "resources/beancan_grenade.png"));
	vbox->addWidget(generateRow(materials["sulfur_to_powder"], "resources/sulfur.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["charcoal_to_powder"], "resources/charcoal.png", "resources/powder.png"));
	vbox->addWidget(generateRow(materials["metal_to_grenade"], "resources/metal.png", "resources/beancan_grenade.png"));
	return beancan_grenade_container;
}