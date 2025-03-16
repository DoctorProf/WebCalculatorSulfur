#pragma once
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace calculator_explosive
{
	json calculateC4(int count);
	json calculateRocket(int count);
	json calculateExplosiveAmmo(int count);
	json calculateSatchel(int count);
	json calculateBeancanGrenade(int count);
}
