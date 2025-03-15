#include "../include/CalculatorApp.h"

CalculatorApp::CalculatorApp(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
	// Устанавливаем заголовок приложения на английском
	setTitle(Wt::WString::fromUTF8("Calculator"));

	// Устанавливаем стили для html и body, чтобы убрать отступы
	root()->addChild(std::make_unique<Wt::WText>(
		"<style>"
		"html, body { margin: 0; padding: 0; height: 100%; }"
		"</style>"
	));

	// Устанавливаем темный градиентный фон для корневого элемента
	root()->setAttributeValue("style",
		"background: linear-gradient(135deg, #4A2C2C, #3B1E1E, #2E1414); " // Темные оттенки
		"background-size: cover; "
		"height: 100vh; " // Занимает всю высоту экрана
		"display: flex; " // Используем flexbox для центрирования контента
		"justify-content: center; " // Центрируем по горизонтали
		"align-items: center; " // Центрируем по вертикали
	);

	// Создаем контейнер для размещения элементов
	auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
	container->setAttributeValue("style", "background: rgba(0, 0, 0, 0.5); padding: 20px; border-radius: 10px;");

	// Создаем вертикальный контейнер для картинок, текстовых полей и кнопки
	auto vbox = container->setLayout(std::make_unique<Wt::WVBoxLayout>());

	// Создаем горизонтальный контейнер для пар "картинка + текстовое поле"
	auto hbox = vbox->addLayout(std::make_unique<Wt::WHBoxLayout>());

	// Массив для хранения текстовых полей
	std::vector<Wt::WLineEdit*> inputs;

	// Добавляем 5 уникальных картинок и 5 текстовых полей
	for (int i = 0; i < 5; ++i) {
		// Создаем вертикальный контейнер для каждой пары "картинка + текстовое поле"
		auto vboxPair = hbox->addLayout(std::make_unique<Wt::WVBoxLayout>());

		// Создаем уникальную картинку
		auto image = vboxPair->addWidget(std::make_unique<Wt::WImage>(), 0, Wt::AlignmentFlag::Center);
		switch (i) {
		case 0:
			image->setImageLink("resources/c4.png"); // Укажите путь к первой картинке
			break;
		case 1:
			image->setImageLink("resources/rocket.png"); // Укажите путь ко второй картинке
			break;
		case 2:
			image->setImageLink("resources/explosive_ammo.png"); // Укажите путь к третьей картинке
			break;
		case 3:
			image->setImageLink("resources/satchel.png"); // Укажите путь к четвертой картинке
			break;
		case 4:
			image->setImageLink("resources/beancan_grenade.png"); // Укажите путь к пятой картинке
			break;
		}
		image->setAlternateText("Image " + std::to_string(i + 1));
		image->setWidth(128); // Устанавливаем ширину картинки
		image->setHeight(128); // Устанавливаем высоту картинки

		// Добавляем текстовое поле
		auto input = vboxPair->addWidget(std::make_unique<Wt::WLineEdit>());
		input->setAttributeValue("style",
			"text-align: center; " // Выравниваем текст по центру
			"background: rgba(255, 255, 255, 0.2); " // Полупрозрачный белый фон
			"border: 1px solid rgba(255, 255, 255, 0.3); " // Полупрозрачная граница
			"color: white; " // Белый текст
			"padding: 5px; " // Отступы внутри текстового поля
			"border-radius: 5px; " // Закругленные углы
		);
		inputs.push_back(input);
	}

	// Создаем кнопку "Calculate" и стилизуем ее
	auto calculateButton = vbox->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString::fromUTF8("Calculate")));
	calculateButton->setAttributeValue("style",
		"background-color: #A0522D; " // Коричневый цвет
		"border: 2px solid #8B4513; " // Темно-коричневая граница
		"color: white; " // Белый текст
		"padding: 10px 20px; " // Отступы внутри кнопки
		"text-align: center; " // Выравнивание текста по центру
		"text-decoration: none; " // Убираем подчеркивание
		"display: inline-block; "
		"font-size: 16px; "
		"font-weight: bold; " // Жирный шрифт
		"border-radius: 5px; " // Закругленные углы
		"cursor: pointer; " // Курсор в виде указателя
		"box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.3); " // Тень для объема
	);

	// Эффект при наведении на кнопку
	calculateButton->setAttributeValue("onmouseover", "this.style.backgroundColor='#8B4513'; this.style.boxShadow='0px 6px 8px rgba(0, 0, 0, 0.4)';");
	calculateButton->setAttributeValue("onmouseout", "this.style.backgroundColor='#A0522D'; this.style.boxShadow='0px 4px 6px rgba(0, 0, 0, 0.3)';");

	// Создаем текстовый элемент для вывода результата
	Wt::WText* resultText = vbox->addWidget(std::make_unique<Wt::WText>());
	resultText->setAttributeValue("style", "color: white; text-align: center;"); // Белый текст и выравнивание по центру

	// Обработчик нажатия на кнопку
	calculateButton->clicked().connect([=]() {
		try {
			double sum = 0;
			for (auto input : inputs) {
				sum += std::stod(input->text().toUTF8()); // Суммируем значения из текстовых полей
			}

			// Выводим результат на английском
			resultText->setText(Wt::WString::fromUTF8("Sum: {1}").arg(sum));
		}
		catch (const std::exception& e) {
			// В случае ошибки (например, если введено не число)
			resultText->setText(Wt::WString::fromUTF8("Error: Please enter valid numbers"));
			std::cerr << "Error: " << e.what() << std::endl; // Вывод ошибки в консоль
		}
		});
}