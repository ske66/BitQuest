#include "ecm.h"

class Component {
protected:
	Entity *const _parent;
	bool _fordeletion; //should be removed
	explicit Component(Entity *const p);

public:
	Component() = delete;
	bool is_fordeletion() const;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual ~Component();
};