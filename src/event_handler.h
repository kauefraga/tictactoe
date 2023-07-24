#pragma once


/// @brief Handle all kind of events.
/// @param window - A reference to the main window.
/// @param event - A reference to the event listener.
/// @param is_active - A reference to check or assign if the menu pop up is activated
void event_handler(
  sf::Window& window,
  sf::Event& event,
  sf::Vector2i& mouse_position,
  bool& is_in_menu,
  bool& turn
) {
  while (window.pollEvent(event)) {
    if (is_in_menu) {
      // MENUUUUUUUUUU
    }

    if (event.type == sf::Event::Closed) {
      window.close();
    }

    if (event.type == sf::Event::KeyReleased) {
      if (event.key.code == sf::Keyboard::Q) {
        is_in_menu = !is_in_menu;
      }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        // std::cout << event.mouseButton.x << ", " << event.mouseButton.y << '\n';
        mouse_position = { event.mouseButton.x, event.mouseButton.y };

        turn = !turn;
      }
    }
  }
}
