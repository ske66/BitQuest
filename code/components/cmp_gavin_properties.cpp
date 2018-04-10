#include "cmp_gavin_properties.h"
#include <iostream>

void GavinPropertiesComponent::takeDamage(double h)
{
	_health = _health - h;
	std::cout << "gavin hit" << std::endl;
}