#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <fmt/core.h>
#include <iostream>
#include <stdexcept>


namespace Screen {
  const unsigned int WIDTH = 700;
  const unsigned int HEIGHT = 600;
}

/* Palette: https://lospec.com/palette-list/basic-bit
  Name: Basic Bit
  Creator: RABBITKING
*/
namespace Color {
  sf::Color red(215, 108, 108);
  sf::Color orange(244, 148, 97);
  sf::Color yellow(255, 221, 126);
  sf::Color green(135, 191, 114);
  sf::Color blue(106, 148, 177);
  sf::Color purple(115, 87, 126);
  sf::Color white(255, 252, 241);
  sf::Color gray(190, 190, 180);
  sf::Color black(62, 62, 62);
}

namespace Helper {
  sf::Image load_icon(const sf::String& file_path) {
    sf::Image icon;

    if (!icon.loadFromFile(file_path)) {
      throw std::runtime_error("The icon could not be loaded.");
    }

    return icon;
  }

  sf::Vector2f round(const sf::Vector2f vector) {
    return sf::Vector2f(std::round(vector.x), std::round(vector.y));
  }

  sf::Font load_font(const sf::String& filename) {
    sf::Font font;

    if (!font.loadFromFile(filename)) {
      throw std::runtime_error("The font could not be loaded.");
    }

    return font;
  }

  // Awesome article: https://learnsfml.com/how-to-center-text
  sf::Text create_text(
    const sf::String& text,
    sf::Vector2f position,
    sf::Font& font,
    sf::Color& color,
    sf::Uint32 style = sf::Text::Regular,
    unsigned int character_size = 30
  ) {
    sf::Text t(text, font, character_size);

    sf::Vector2f center(
      t.getGlobalBounds().width / 2.0f,
      t.getGlobalBounds().height / 2.0f
    );
    sf::Vector2f local_bounds(
      center.x + t.getLocalBounds().left,
      center.y + t.getLocalBounds().top
    );
    sf::Vector2f rounded = Helper::round(local_bounds);

    t.setOrigin(rounded);
    t.setPosition(position);
    t.setFillColor(color);
    t.setStyle(style);

    return t;
  }

  class Sprite {
  public:
    sf::Texture* texture;
    sf::Sprite* sprite;

    Sprite(const sf::String& filename) {
      texture = new sf::Texture;
      sprite = new sf::Sprite;

      if (!texture->loadFromFile(filename)) {
        throw std::runtime_error("The texture could not be loaded from " + filename);
      }

      sprite->setTexture(*texture);
    }

    sf::Sprite get_sprite() {
      return *sprite;
    }

    void unload() {
      delete texture;
      delete sprite;
    }
  };
}

class Menu {
public:
  sf::RectangleShape background;

  Menu(
    sf::Vector2u window_size,
    sf::Vector2f size,
    sf::Color background_color
  ) {
    background = sf::RectangleShape(size);
    background.setPosition({
      (window_size.x / 2) - (size.x / 2),
      (window_size.y / 2) - (size.y / 2)
      });
    background.setFillColor(background_color);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(background);
  }
};

// Declares the size of each rendered squared.
const sf::Vector2f square_size(140.0f, 120.0f);

// Declares the initial position of the first square.
const sf::Vector2f initial_position(140.0f, 120.0f);

/*
  0 = Empty
  1 = O
  2 = X
*/
class Game {
public:
  //int choice;
  int row = 0;
  int column = 0;
  bool turn;
  bool tie = false;
  int grid[3][3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
  };

  /// @brief Initializes the game's business logic
  /// @param turn - Defines who starts. 1 = X and 2 = O.
  Game(bool& turn) {
    this->turn = turn;
  }

  Game() = default;
};

class Grid {
public:
  Game game;
  sf::Sprite X;
  sf::Sprite O;
  sf::RectangleShape board[9];

  Grid(bool turn, sf::Color color) {
    this->game = Game(turn);

    Helper::Sprite x("resources/x.png");
    Helper::Sprite o("resources/o.png");

    X = x.get_sprite();
    O = o.get_sprite();

    for (int i = 0; i < 9; i++) {
      board[i].setSize(square_size);
      board[i].setFillColor(Color::white);
      board[i].setOutlineColor(color);
      board[i].setOutlineThickness(3);
    }
  }

  void draw(sf::RenderWindow& window) {
    sf::Vector2u window_size = window.getSize();
    board[0].setPosition({ initial_position.x, initial_position.y });
    board[1].setPosition({ initial_position.x + square_size.x, initial_position.y });
    board[2].setPosition({ initial_position.x + square_size.x * 2, initial_position.y });

    board[3].setPosition({ initial_position.x, initial_position.y + square_size.y });
    board[4].setPosition({ initial_position.x + square_size.x, initial_position.y + square_size.y });
    board[5].setPosition({ initial_position.x + square_size.x * 2, initial_position.y + square_size.y });

    board[6].setPosition({ initial_position.x, initial_position.y + square_size.y * 2 });
    board[7].setPosition({ initial_position.x + square_size.x, initial_position.y + square_size.y * 2 });
    board[8].setPosition({ initial_position.x + square_size.x * 2, initial_position.y + square_size.y * 2 });

    for (int i = 0; i < 9; i++) {
      window.draw(board[i]);
    }
  }

  void draw_x(
    sf::RenderWindow& window,
    sf::Vector2i& mouse_position,
    bool& turn
  ) {
    if (!turn) {
      X.setPosition((sf::Vector2f) mouse_position);
      window.draw(X);
    }
  }

  void draw_o(
    sf::RenderWindow& window,
    sf::Vector2i& mouse_position,
    bool& turn
  ) {
    if (turn) {
      O.setPosition((sf::Vector2f) mouse_position);
      window.draw(O);
    }
  }
};
