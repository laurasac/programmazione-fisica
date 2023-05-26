#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "sir.hpp"

using namespace std;

int main() {
  // x ha 0 in basso a sinistra, la y ha 0 in altro a sinistra
  int width = 1000;
  int height = 1000;
  sf::RenderWindow window(sf::VideoMode(width, height), "Grafico",
                          sf::Style::Default);

  int T = 100;
  int N = 150;
  sir::SIR state{87, 32, 31};
  sf::VertexArray chart1(sf::PrimitiveType::LineStrip, T);
  sf::VertexArray chart2(sf::PrimitiveType::LineStrip, T);
  float gamma{0.3};
  float beta{0.4};

  chart1.append(
          sf::Vertex(sf::Vector2f(29.5,
                                  height - 30 - state.S * (height - 60) / N)));
  chart2.append(sf::Vertex(
          sf::Vector2f(29.5,
                       height - 30 - state.S * (height - 60) / N + 0.5)));

  std::ofstream out_file{"./result.txt"};
  if (out_file.is_open()) {
    for (int i = 1; i <= T; i++) {
      int S = sir::update_s(state, beta, N);
      int I = sir::update_i(state, beta, gamma, N);
      int R = sir::update_r(state, gamma);
      state.S = S;
      state.I = I;
      state.R = R;
      out_file << i * (width - 60) / T << "  "
               << height - 30 - state.S * (height - 60) / N << "\n";
      chart1.append(
          sf::Vertex(sf::Vector2f(30 + i * (width - 60) / T,
                                  height - 30 - state.S * (height - 60) / N),
                     sf::Color::Black));
      chart2.append(sf::Vertex(
          sf::Vector2f(30 + i * (width - 60) / T,
                       height - 30 - state.S * (height - 60) / N + 0.5),
          sf::Color::Black));

      // chart.append(sf::Vertex(sf::Vector2f(i*8+30, height - 30 -
      // std::sin(i)*(height-60)/N),sf::Color::Black));
    }
  }

  out_file.close();

  sf::RectangleShape rect_X[T / 10];
  sf::RectangleShape rect_Y[N / 10];

  sf::RectangleShape asse_X(sf::Vector2f(940, 3.f));
  sf::RectangleShape asse_Y(sf::Vector2f(940, 3.f));
  asse_Y.rotate(90.f);
  asse_X.setFillColor(sf::Color::Black);
  asse_Y.setFillColor(sf::Color::Black);
  asse_X.setPosition(30, width - 30);
  asse_Y.setPosition(30, 30);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed) window.close();

    window.clear(sf::Color::White);
    window.draw(chart1);
    window.draw(chart2);
    window.draw(asse_X);
    window.draw(asse_Y);
    int i = 30, j = 0, l = 0;

    while (l < sizeof(rect_X) / sizeof(rect_X[0])) {
      i += 10 * (width - 60) / T;
      rect_X[l].setSize(sf::Vector2f(1, 10));

      rect_X[l].setPosition(i, height - 30);

      rect_X[l].setFillColor(sf::Color::Black);

      window.draw(rect_X[l]);

      l++;
    }

    l = 0;
    i = height - 30;

    while (l < sizeof(rect_Y) / sizeof(rect_Y[0])) {
      i -= 10 * (height - 60) / N;

      rect_Y[l].setSize(sf::Vector2f(5, 1));

      rect_Y[l].setPosition(30, i);

      rect_Y[l].setFillColor(sf::Color::Black);

      window.draw(rect_Y[l]);

      l++;
    }

    window.display();
  }
  return 0;
}