#include "../include/CalculatorApp.h"

CalculatorApp::CalculatorApp(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
	// ������������� ��������� ���������� �� ����������
	setTitle(Wt::WString::fromUTF8("Calculator"));

	// ������������� ����� ��� html � body, ����� ������ �������
	root()->addChild(std::make_unique<Wt::WText>(
		"<style>"
		"html, body { margin: 0; padding: 0; height: 100%; }"
		"</style>"
	));

	// ������������� ������ ����������� ��� ��� ��������� ��������
	root()->setAttributeValue("style",
		"background: linear-gradient(135deg, #4A2C2C, #3B1E1E, #2E1414); " // ������ �������
		"background-size: cover; "
		"height: 100vh; " // �������� ��� ������ ������
		"display: flex; " // ���������� flexbox ��� ������������� ��������
		"justify-content: center; " // ���������� �� �����������
		"align-items: center; " // ���������� �� ���������
	);

	// ������� ��������� ��� ���������� ���������
	auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
	container->setAttributeValue("style", "background: rgba(0, 0, 0, 0.5); padding: 20px; border-radius: 10px;");

	// ������� ������������ ��������� ��� ��������, ��������� ����� � ������
	auto vbox = container->setLayout(std::make_unique<Wt::WVBoxLayout>());

	// ������� �������������� ��������� ��� ��� "�������� + ��������� ����"
	auto hbox = vbox->addLayout(std::make_unique<Wt::WHBoxLayout>());

	// ������ ��� �������� ��������� �����
	std::vector<Wt::WLineEdit*> inputs;

	// ��������� 5 ���������� �������� � 5 ��������� �����
	for (int i = 0; i < 5; ++i) {
		// ������� ������������ ��������� ��� ������ ���� "�������� + ��������� ����"
		auto vboxPair = hbox->addLayout(std::make_unique<Wt::WVBoxLayout>());

		// ������� ���������� ��������
		auto image = vboxPair->addWidget(std::make_unique<Wt::WImage>(), 0, Wt::AlignmentFlag::Center);
		switch (i) {
		case 0:
			image->setImageLink("resources/c4.png"); // ������� ���� � ������ ��������
			break;
		case 1:
			image->setImageLink("resources/rocket.png"); // ������� ���� �� ������ ��������
			break;
		case 2:
			image->setImageLink("resources/explosive_ammo.png"); // ������� ���� � ������� ��������
			break;
		case 3:
			image->setImageLink("resources/satchel.png"); // ������� ���� � ��������� ��������
			break;
		case 4:
			image->setImageLink("resources/beancan_grenade.png"); // ������� ���� � ����� ��������
			break;
		}
		image->setAlternateText("Image " + std::to_string(i + 1));
		image->setWidth(128); // ������������� ������ ��������
		image->setHeight(128); // ������������� ������ ��������

		// ��������� ��������� ����
		auto input = vboxPair->addWidget(std::make_unique<Wt::WLineEdit>());
		input->setAttributeValue("style",
			"text-align: center; " // ����������� ����� �� ������
			"background: rgba(255, 255, 255, 0.2); " // �������������� ����� ���
			"border: 1px solid rgba(255, 255, 255, 0.3); " // �������������� �������
			"color: white; " // ����� �����
			"padding: 5px; " // ������� ������ ���������� ����
			"border-radius: 5px; " // ������������ ����
		);
		inputs.push_back(input);
	}

	// ������� ������ "Calculate" � ��������� ��
	auto calculateButton = vbox->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString::fromUTF8("Calculate")));
	calculateButton->setAttributeValue("style",
		"background-color: #A0522D; " // ���������� ����
		"border: 2px solid #8B4513; " // �����-���������� �������
		"color: white; " // ����� �����
		"padding: 10px 20px; " // ������� ������ ������
		"text-align: center; " // ������������ ������ �� ������
		"text-decoration: none; " // ������� �������������
		"display: inline-block; "
		"font-size: 16px; "
		"font-weight: bold; " // ������ �����
		"border-radius: 5px; " // ������������ ����
		"cursor: pointer; " // ������ � ���� ���������
		"box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.3); " // ���� ��� ������
	);

	// ������ ��� ��������� �� ������
	calculateButton->setAttributeValue("onmouseover", "this.style.backgroundColor='#8B4513'; this.style.boxShadow='0px 6px 8px rgba(0, 0, 0, 0.4)';");
	calculateButton->setAttributeValue("onmouseout", "this.style.backgroundColor='#A0522D'; this.style.boxShadow='0px 4px 6px rgba(0, 0, 0, 0.3)';");

	// ������� ��������� ������� ��� ������ ����������
	Wt::WText* resultText = vbox->addWidget(std::make_unique<Wt::WText>());
	resultText->setAttributeValue("style", "color: white; text-align: center;"); // ����� ����� � ������������ �� ������

	// ���������� ������� �� ������
	calculateButton->clicked().connect([=]() {
		try {
			double sum = 0;
			for (auto input : inputs) {
				sum += std::stod(input->text().toUTF8()); // ��������� �������� �� ��������� �����
			}

			// ������� ��������� �� ����������
			resultText->setText(Wt::WString::fromUTF8("Sum: {1}").arg(sum));
		}
		catch (const std::exception& e) {
			// � ������ ������ (��������, ���� ������� �� �����)
			resultText->setText(Wt::WString::fromUTF8("Error: Please enter valid numbers"));
			std::cerr << "Error: " << e.what() << std::endl; // ����� ������ � �������
		}
		});
}