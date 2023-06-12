#include "graph.hpp"

#include <stdexcept>
int sir::control_proportions(int a){
  if((a >= 0) && ( a < 20)){
    return 1;
  } else if((a >= 20) && ( a < 70)){
    return 5;
  } else if((a >= 70) && ( a < 150)){
    return 10;
  } else if((a >= 150) && ( a < 500)){
    return 25;
  } else if((a >= 500) && ( a <= 1000)){
    return 100;
  } else {
    return 10;
  }
}
void sir::create_chart(sf::RenderWindow& window, const int width,
                       const int height, const int delta, int T, int N) {
  sf::Font font;
  if (!font.loadFromFile("arial.ttf")) {
    throw std::runtime_error("font non caricato");
  }
  sf::RectangleShape asse_X(sf::Vector2f(width - delta * 2, 4.f));
  sf::RectangleShape asse_Y(sf::Vector2f(height - delta * 2, 3.f));
  asse_Y.rotate(90.f);
  asse_X.setFillColor(sf::Color::Black);
  asse_Y.setFillColor(sf::Color::Black);
  asse_X.setPosition(delta, width - delta);
  asse_Y.setPosition(delta, delta);

  sf::Text label_x;
  label_x.setFont(font);
  label_x.setString("T");
  label_x.setCharacterSize(15);
  label_x.setFillColor(sf::Color::Black);
  label_x.setStyle(sf::Text::Bold);
  label_x.setPosition(width - delta - 10, height - delta - 20);

  window.draw(asse_X);
  window.draw(asse_Y);
  window.draw(label_x);

  int scale_T{sir::control_proportions(T)};
  int scale_N{sir::control_proportions(N)};
  sf::RectangleShape rect_X[T / scale_T];
  sf::RectangleShape rect_Y[N / scale_N];
  sf::Text index_x[T / scale_T];
  sf::Text index_y[N / scale_N];

  int i{delta};
  int l{0};
  int index{0};

  while (l < T / scale_T) {
    i += scale_T * (width - delta * 2) / T;
    index += scale_T;
    rect_X[l].setSize(sf::Vector2f(1, 10));

    rect_X[l].setPosition(i, height - delta);

    rect_X[l].setFillColor(sf::Color::Black);

    window.draw(rect_X[l]);

    index_x[l].setFont(font);
    index_x[l].setString(std::to_string(index));
    index_x[l].setCharacterSize(12);
    index_x[l].setFillColor(sf::Color::Black);
    index_x[l].setStyle(sf::Text::Bold);
    index_x[l].setPosition(i - 7, height - delta + 10);
    window.draw(index_x[l]);
    l++;
  }

  l = 0;
  i = height - delta;
  index = 0;

  while (l < (N / scale_N)) {
    i -= scale_N * (height - delta * 2) / N;
    index += scale_N;
    rect_Y[l].setSize(sf::Vector2f(5, 1));

    rect_Y[l].setPosition(delta, i);

    rect_Y[l].setFillColor(sf::Color::Black);

    window.draw(rect_Y[l]);

    index_y[l].setFont(font);
    index_y[l].setString(std::string(std::to_string(index)));
    index_y[l].setCharacterSize(12);
    index_y[l].setFillColor(sf::Color::Black);
    index_y[l].setStyle(sf::Text::Bold);
    index_y[l].setPosition(delta + 5, i - 7);
    window.draw(index_y[l]);
    l++;
  }
}

void sir::create_graph(sf::RenderWindow& window, const int width,
                       const int height, const int delta,
                       std::vector<sir::SIR> state, int T, int N) {
  sf::Font font;
  if (!font.loadFromFile("arial.ttf")) {
     throw std::runtime_error("font non caricato");
  }
  sf::Text label_s;
  sf::Text label_i;
  sf::Text label_r;
  sf::RectangleShape container_labels(sf::Vector2f(100.f, 30.f));
  container_labels.setPosition(width - 160, 100);
  container_labels.setOutlineColor(sf::Color::Black);
  container_labels.setOutlineThickness(3.);

  label_s.setFont(font);
  label_s.setString("S");
  label_s.setCharacterSize(25);
  label_s.setFillColor(sf::Color::Red);
  label_s.setStyle(sf::Text::Bold);
  label_s.setPosition(width - 140, 100);

  label_i.setFont(font);
  label_i.setString("I");
  label_i.setCharacterSize(25);
  label_i.setFillColor(sf::Color::Blue);
  label_i.setStyle(sf::Text::Bold);
  label_i.setPosition(width - 120, 100);

  label_r.setFont(font);
  label_r.setString("R");
  label_r.setCharacterSize(25);
  label_r.setFillColor(sf::Color::Green);
  label_r.setStyle(sf::Text::Bold);
  label_r.setPosition(width - 100, 100);

  window.draw(container_labels);
  window.draw(label_s);
  window.draw(label_i);
  window.draw(label_r);

  sf::VertexArray chart_S_1(sf::PrimitiveType::LineStrip, T); 
  sf::VertexArray chart_S_2(sf::PrimitiveType::LineStrip, T);
  sf::VertexArray chart_I_1(sf::PrimitiveType::LineStrip, T);
  sf::VertexArray chart_I_2(sf::PrimitiveType::LineStrip, T);
  sf::VertexArray chart_R_1(sf::PrimitiveType::LineStrip, T);
  sf::VertexArray chart_R_2(sf::PrimitiveType::LineStrip, T);

  chart_S_1.append(sf::Vertex(sf::Vector2f(
      delta - 0.5, height - delta - state[0].S * (height - delta * 2) / N)));
  chart_S_2.append(sf::Vertex(sf::Vector2f(
      delta - 0.5,
      height - delta - state[0].S * (height - delta * 2) / N + 0.5)));
  chart_I_1.append(sf::Vertex(sf::Vector2f(
      delta - 0.5, height - delta - state[0].I * (height - delta * 2) / N)));
  chart_I_2.append(sf::Vertex(sf::Vector2f(
      delta - 0.5,
      height - delta - state[0].I * (height - delta * 2) / N + 0.5)));
  chart_R_1.append(sf::Vertex(sf::Vector2f(
      delta - 0.5, height - delta - state[0].R * (height - delta * 2) / N)));
  chart_R_2.append(sf::Vertex(sf::Vector2f(
      delta - 0.5,
      height - delta - state[0].R * (height - delta * 2) / N + 0.5)));

  for (int i = 1; i <= T; i++) {
    chart_S_1.append(sf::Vertex(
        sf::Vector2f(delta + i * (width - delta * 2) / T,
                     height - delta - state[i].S * (height - delta * 2) / N),
        sf::Color::Red));
    chart_S_2.append(sf::Vertex(
        sf::Vector2f(
            delta + i * (width - delta * 2) / T,
            height - delta - state[i].S * (height - delta * 2) / N + 0.5),
        sf::Color::Red));

    chart_I_1.append(sf::Vertex(
        sf::Vector2f(delta + i * (width - delta * 2) / T,
                     height - delta - state[i].I * (height - delta * 2) / N),
        sf::Color::Blue));
    chart_I_2.append(sf::Vertex(
        sf::Vector2f(
            delta + i * (width - delta * 2) / T,
            height - delta - state[i].I * (height - delta * 2) / N + 0.5),
        sf::Color::Blue));
    chart_R_1.append(sf::Vertex(
        sf::Vector2f(delta + i * (width - delta * 2) / T,
                     height - delta - state[i].R * (height - delta * 2) / N),
        sf::Color::Green));
    chart_R_2.append(sf::Vertex(
        sf::Vector2f(
            delta + i * (width - delta * 2) / T,
            height - delta - state[i].R * (height - delta * 2) / N + 0.5),
        sf::Color::Green));
  }
  window.draw(chart_S_1);
  window.draw(chart_S_2);
  window.draw(chart_I_1);
  window.draw(chart_I_2);
  window.draw(chart_R_1);
  window.draw(chart_R_2);
}

void sir::render_window(const int width, const int height, const int delta,
                        sir::Epidemic& epidemic) {
  sf::RenderWindow window(sf::VideoMode(width, height), "Grafico S, R, I",
                          sf::Style::Default);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    try {
      create_graph(window, width, height, delta, epidemic.getState(),
                   epidemic.getT(), epidemic.getN());
      create_chart(window, width, height, delta, epidemic.getT(),
                   epidemic.getN());
      window.display();
    } catch (const std::runtime_error& e) {
        throw e;
    }
  }
}