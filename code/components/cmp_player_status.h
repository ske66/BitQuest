#include <ecm.h>

class PlayerStatusComponent : public Component
{
protected:
	double _health = 10;

public:

	explicit PlayerStatusComponent(Entity* p);
	PlayerStatusComponent() = delete; 
	double getHealth();
	void setHealth(double b);
	void takeDamage(double);

	void update(double dt); 
	void render() override; 

};
