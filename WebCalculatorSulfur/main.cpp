#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WImage.h>
#include <iostream> // Для вывода ошибок в консоль

class CalculatorApp : public Wt::WApplication
{
public:
	CalculatorApp(const Wt::WEnvironment& env)
		: Wt::WApplication(env)
	{
		// Устанавливаем заголовок приложения на английском
		setTitle(Wt::WString::fromUTF8("Calculator"));

		// Создаем контейнер для размещения элементов
		auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());

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
			inputs.push_back(input);
		}

		// Создаем кнопку "Calculate" и размещаем ее по центру
		auto calculateButton = vbox->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString::fromUTF8("Calculate")), 0, Wt::AlignmentFlag::Center);

		// Создаем текстовый элемент для вывода результата
		Wt::WText* resultText = vbox->addWidget(std::make_unique<Wt::WText>(), 0, Wt::AlignmentFlag::Center);

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
};

int main(int argc, char** argv)
{
	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return std::make_unique<CalculatorApp>(env);
		});
}