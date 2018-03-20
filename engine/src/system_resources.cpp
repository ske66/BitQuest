#include "system_resources.h"

namespace Resources {

	template<>
	std::shared_ptr<sf::Font> load(const std::string &name) {
		auto f = std::make_shared<sf::Font>();
		if (!f->loadFromFile("res/fonts/" + name)) {
			throw("not found: " + name);
		};
		return f;
	};

	template <> // explicit specialisation for T = Texture
	std::shared_ptr<sf::Texture> load(const std::string& name) {
		auto tex = std::make_shared<sf::Texture>();
		if (!tex->loadFromFile("res/textures/" + name)) {
			throw("not found: " + name);
		};
		return tex;
	};
#ifdef SOUND
	template <> // explicit specialisation for T = SoundBuffer
	std::shared_ptr<sf::SoundBuffer> load(const std::string& name) {
		auto buf = std::make_shared<sf::SoundBuffer>();
		if (!buf->loadFromLevel("res/sound/" + name)) {
			throw("not found: " + name);
		};
		return buf;
	};

	template <> // explicit specialisation for T = Music
	std::shared_ptr<sf::Music> load(const std::string& name) {
		auto music = std::make_shared<sf::Music>();
		if (!music->openFromFile("res/sound/music/" + name)) {
			throw("not found: " + name);
		};
		return music;
	};
#endif // SOUND
}