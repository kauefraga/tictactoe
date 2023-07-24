#include "gui.h"
#include "event_handler.h"

using namespace Screen;
using namespace Helper;

int main() {
  /* WINDOW */
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tic Tac Toe");

  sf::Image icon = load_icon("resources/icon.png");

  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  window.setFramerateLimit(60);

  sf::Vector2i mouse_position = sf::Mouse::getPosition();

  /* MENU */
  bool is_in_menu = true;
  Menu menu(window.getSize(), { 450, 400 }, Color::black);

  /* GAME */
  bool turn = false;
  int x_score = 0;
  int o_score = 0;

  Grid grid(turn, Color::purple);

  /* TEXT */
  sf::Font font = load_font("resources/fonts/roboto.ttf");

  sf::Text scoreboard_label = create_text(
    "X   O",
    { WIDTH / 2, 30 },
    font,
    Color::orange,
    sf::Text::Bold
  );

  while (window.isOpen()) {
    /* --- EVENT HANDLING --- */
    sf::Event event;

    event_handler(window, event, mouse_position, is_in_menu, turn);

    /* UPDATE STATES */
    sf::Text scoreboard = create_text(
      fmt::format("{} x {}", x_score, o_score),
      { WIDTH / 2, 60 },
      font,
      Color::black
    );

    sf::Text whose_turn = create_text(
      turn ? "It's X turn" : "It's O turn" ,
      { WIDTH / 2,  540 },
      font,
      Color::black
    );

    /* --- DRAW --- */
    window.clear(Color::white);

    if (is_in_menu) {
      menu.draw(window);
    }
    else {
      // Draw scoreboard
      window.draw(scoreboard_label);
      window.draw(scoreboard);

      // Draw the game
      grid.draw(window);
      grid.draw_o(window, mouse_position, turn);
      grid.draw_x(window, mouse_position, turn);

      // Draw whose turn
      window.draw(whose_turn);
    }

    window.display();
  }

  return 0;
}
