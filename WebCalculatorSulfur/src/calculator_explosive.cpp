#include "../include/calculator_explosive.h"

json calculator_explosive::calculateC4(int count)
{
	json materials;
	materials["sulfur"] = count * 2200;
	materials["sulfur_to_powder"] = count * 2000;
	materials["powder_to_exp"] = count * 1000;
	materials["sulfur_to_exp"] = count * 200;
	materials["metal_to_exp"] = count * 200;
	materials["lgf_to_exp"] = count * 60;
	materials["charcoal_to_powder"] = count * 2000;
	materials["microcircuits"] = count * 2;
	materials["cloth"] = count * 5;
	return materials;
}
json calculator_explosive::calculateRocket(int count)
{
	json materials;
	materials["sulfur"] = count * 1400;
	materials["sulfur_to_powder"] = count * 1300;
	materials["powder_to_rocket"] = count * 150;
	materials["powder_to_exp"] = count * 500;
	materials["sulfur_to_exp"] = count * 100;
	materials["metal_to_exp"] = count * 100;
	materials["lgf_to_exp"] = count * 30;
	materials["charcoal_to_powder"] = count * 1400;
	materials["pipe"] = count * 2;
	return materials;
}
json calculator_explosive::calculateExplosiveAmmo(int count)
{
	json materials;
	count = std::ceil(count / 2);
	materials["sulfur"] = count * 50;
	materials["sulfur_to_powder"] = count * 40;
	materials["sulfur_to_ammo"] = count * 10;
	materials["metal_to_ammo"] = count * 10;
	materials["charcoal_to_powder"] = count * 40;
	return materials;
}
json calculator_explosive::calculateSatchel(int count)
{
	json materials;
	materials["sulfur"] = count * 480;
	materials["sulfur_to_powder"] = count * 480;
	materials["powder_to_grenade"] = count * 480;
	materials["metal_to_grenade"] = count * 80;
	materials["cloth_to_stash"] = count * 10;
	materials["rope"] = count;
	materials["charcoal_to_powder"] = count * 480;
	return materials;
}
json calculator_explosive::calculateBeancanGrenade(int count)
{
	json materials;
	materials["sulfur"] = count * 120;
	materials["sulfur_to_powder"] = count * 120;
	materials["metal_to_grenade"] = count * 20;
	materials["charcoal_to_powder"] = count * 120;
	return materials;
}