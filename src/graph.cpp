#include "graph.hpp"

#include <stdexcept>

int sir::controlProportions(int a) {
  if ((a >= 0) && (a < 20)) {
    return 1;
  } else if ((a >= 20) && (a < 70)) {
    return 5;
  } else if ((a >= 70) && (a < 150)) {
    return 10;
  } else if ((a >= 150) && (a < 500)) {
    return 25;
  } else if ((a >= 500) && (a <= 1000)) {
    return 100;
  } else {
    return 10;
  }
}

void sir::createChart(sf::RenderWindow& window, const int width,
                      const int height, const int margin, int T, int N,
                      sf::Font font) {
  sf::RectangleShape axisX(sf::Vector2f(width - margin * 2, 4.f));
  sf::RectangleShape axisY(sf::Vector2f(height - margin * 2, 3.f));
  axisY.rotate(90.f);
  axisX.setFillColor(sf::Color::Black);
  axisY.setFillColor(sf::Color::Black);
  axisX.setPosition(margin, width - margin);
  axisY.setPosition(margin, margin);

  sf::Text labelX;
  sf::Text labelY;
  labelX.setFont(font);
  labelX.setString("T");
  labelX.setCharacterSize(15);
  labelX.setFillColor(sf::Color::Black);
  labelX.setStyle(sf::Text::Bold);
  labelX.setPosition(width - margin - 10, height - margin - 20);

  
  labelY.setFont(font);
  labelY.setString("Individui");
  labelY.setCharacterSize(15);
  labelY.setFillColor(sf::Color::Black);
  labelY.setStyle(sf::Text::Bold);
  labelY.setPosition(margin + 5, margin);

  window.draw(axisX);
  window.draw(axisY);
  window.draw(labelX);
  window.draw(labelY);

  int scaleT{sir::controlProportions(T)};
  int scaleN{sir::controlProportions(N)};
  sf::RectangleShape rectX[T / scaleT];
  sf::RectangleShape rectY[N / scaleN];
  sf::Text indexX[T / scaleT];
  sf::Text indexY[N / scaleN];

  int i{margin};
  int l{0};
  int index{0};

  while (l < T / scaleT) {
    i += scaleT * (width - margin * 2) / T;
    index += scaleT;
    rectX[l].setSize(sf::Vector2f(1, 10));

    rectX[l].setPosition(i, height - margin);

    rectX[l].setFillColor(sf::Color::Black);

    window.draw(rectX[l]);

    indexX[l].setFont(font);
    indexX[l].setString(std::to_string(index));
    indexX[l].setCharacterSize(12);
    indexX[l].setFillColor(sf::Color::Black);
    indexX[l].setStyle(sf::Text::Bold);
    indexX[l].setPosition(i - 7, height - margin + 10);
    window.draw(indexX[l]);
    l++;
  }

  l = 0;
  i = height - margin;
  index = 0;

  while (l < (N / scaleN)) {
    i -= scaleN * (height - margin * 2) / N;
    index += scaleN;
    rectY[l].setSize(sf::Vector2f(5, 1));

    rectY[l].setPosition(margin, i);

    rectY[l].setFillColor(sf::Color::Black);

    window.draw(rectY[l]);

    indexY[l].setFont(font);
    indexY[l].setString(std::string(std::to_string(index)));
    indexY[l].setCharacterSize(12);
    indexY[l].setFillColor(sf::Color::Black);
    indexY[l].setStyle(sf::Text::Bold);
    indexY[l].setPosition(margin + 5, i - 7);
    window.draw(indexY[l]);
    l++;
  }
}

void sir::createGraph(sf::RenderWindow& window, const int width,
                      const int height, const int margin,
                      std::vector<sir::SIR> state, int T, int N,
                      sf::Font font) {
  sf::Text labelS;
  sf::Text labelI;
  sf::Text labelR;
  sf::RectangleShape containerLabels(sf::Vector2f(100.f, 30.f));
  containerLabels.setPosition(width - 160, 100);
  containerLabels.setOutlineColor(sf::Color::Black);
  containerLabels.setOutlineThickness(3.);

  labelS.setFont(font);
  labelS.setString("S");
  labelS.setCharacterSize(25);
  labelS.setFillColor(sf::Color::Red);
  labelS.setStyle(sf::Text::Bold);
  labelS.setPosition(width - 140, 100);

  labelI.setFont(font);
  labelI.setString("I");
  labelI.setCharacterSize(25);
  labelI.setFillColor(sf::Color::Blue);
  labelI.setStyle(sf::Text::Bold);
  labelI.setPosition(width - 120, 100);

  labelR.setFont(font);
  labelR.setString("R");
  labelR.setCharacterSize(25);
  labelR.setFillColor(sf::Color::Green);
  labelR.setStyle(sf::Text::Bold);
  labelR.setPosition(width - 100, 100);

  window.draw(containerLabels);
  window.draw(labelS);
  window.draw(labelI);
  window.draw(labelR);

  sf::VertexArray graphS(sf::PrimitiveType::LineStrip, T);
  sf::VertexArray graphI(sf::PrimitiveType::LineStrip, T);
  sf::VertexArray graphR(sf::PrimitiveType::LineStrip, T);

  graphS.append(sf::Vertex(sf::Vector2f(
      margin - 0.5, height - margin - state[0].S * (height - margin * 2) / N)));
  graphI.append(sf::Vertex(sf::Vector2f(
      margin - 0.5, height - margin - state[0].I * (height - margin * 2) / N)));
  graphR.append(sf::Vertex(sf::Vector2f(
      margin - 0.5, height - margin - state[0].R * (height - margin * 2) / N)));

  for (int i = 1; i <= T; i++) {
    graphS.append(sf::Vertex(
        sf::Vector2f(margin + i * (width - margin * 2) / T,
                     height - margin - state[i].S * (height - margin * 2) / N),
        sf::Color::Red));

    graphI.append(sf::Vertex(
        sf::Vector2f(margin + i * (width - margin * 2) / T,
                     height - margin - state[i].I * (height - margin * 2) / N),
        sf::Color::Blue));

    graphR.append(sf::Vertex(
        sf::Vector2f(margin + i * (width - margin * 2) / T,
                     height - margin - state[i].R * (height - margin * 2) / N),
        sf::Color::Green));
  }
  window.draw(graphS);
  window.draw(graphI);
  window.draw(graphR);
}

void sir::printMap(sf::RenderWindow& window, std::vector<char> map,
                   sir::SIR state, int size, int width, int height, int margin,
                   sf::Font font) {
  sf::RectangleShape cells[map.size()];
  sf::Text people[map.size()];
  int countX{0};
  int countY{0};

  for (unsigned long i = 0; i < map.size(); i++) {
    cells[i].setSize(sf::Vector2f((width - 2 * margin) / size,
                                  (height - 2 * margin) / size));
    cells[i].setOutlineColor(sf::Color::Black);
    cells[i].setOutlineThickness(2.);

    people[i].setFont(font);
    people[i].setString(map[i]);
    people[i].setCharacterSize(((height - 2 * margin) / size) - 10);
    people[i].setFillColor(sf::Color::Black);

    if ((i % size == 0) && (i != 0)) {
      countY += 1;
      countX = 0;
      cells[i].setPosition(margin + countX * (width - 2 * margin) / size,
                           margin + countY * (height - 2 * margin) / size);
      people[i].setPosition(margin + 10 + countX * (width - 2 * margin) / size,
                            margin + countY * (height - 2 * margin) / size);

      countX += 1;
    } else {
      cells[i].setPosition(margin + countX * (width - 2 * margin) / size,
                           margin + countY * (height - 2 * margin) / size);
      people[i].setPosition(margin + 10 + countX * (width - 2 * margin) / size,
                            margin + countY * (height - 2 * margin) / size);
      countX += 1;
    }
    window.draw(cells[i]);
    window.draw(people[i]);
  }
  sf::RectangleShape containerState(
      sf::Vector2f(width / 2, width - height - 50));
  containerState.setOutlineColor(sf::Color::Red);
  containerState.setOutlineThickness(3.);
  containerState.setPosition((width - 2 * margin) / 4, height);

  sf::Text labelState;
  labelState.setFont(font);
  labelState.setString("S: " + std::to_string(state.S) +
                       ", I: " + std::to_string(state.I) +
                       ", R: " + std::to_string(state.R));
  labelState.setCharacterSize((width - height - 50) / 4);
  labelState.setStyle(sf::Text::Bold);
  labelState.setFillColor(sf::Color::Black);
  labelState.setPosition(((width - 2 * margin) / 4) + (width - 2 * margin) / 8,
                         height + (width - height - 50) / 3);
  window.draw(containerState);
  window.draw(labelState);
}

void sir::renderWindow(const int width, const int height, const int margin,
                       sir::Epidemic& epidemic) {
  sf::RenderWindow window(sf::VideoMode(width, height), "Grafico S, R, I",
                          sf::Style::Default);
  sf::Font font;
  if (!font.loadFromFile("arial.ttf")) {
    throw std::runtime_error("font non caricato");
  }
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    try {
      createGraph(window, width, height, margin, epidemic.getState(),
                  epidemic.getT(), epidemic.getN(), font);
      createChart(window, width, height, margin, epidemic.getT(),
                  epidemic.getN(), font);
      window.display();
    } catch (const std::runtime_error& e) {
      throw e;
    }
  }
}

void sir::renderWindow(const int width, const int height, const int margin,
                       sir::Automaton& automaton) {
  sf::RenderWindow window(sf::VideoMode(width, height), "automa cellulare",
                          sf::Style::Default);

  sf::Font font;
  if (!font.loadFromFile("arial.ttf")) {
    throw std::runtime_error("font non caricato");
  }

  sf::Text label;
  label.setFont(font);
  label.setString(
      "Premere 'Enter' per far partire la simulazione\n e per andare avanti "
      "nei giorni");
  label.setCharacterSize(36);
  label.setFillColor(sf::Color::Black);
  label.setStyle(sf::Text::Bold);
  label.setPosition(25, 50);

  window.clear(sf::Color::White);
  window.draw(label);
  window.display();

  int count{0};
  int t{automaton.getT()};

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Key::Enter) {
        if (count <= t) {
          window.clear(sf::Color::White);
          printMap(window, automaton.getMap(), automaton.getState(),
                   automaton.getSize(), width, height - 200, margin, font);
          window.display();
          count += 1;
          automaton.evolve();
        } else {
          label.setString("Simulazione terminata, e' possibile chiudere la finestra");
          window.clear(sf::Color::White);
          window.draw(label);
          window.display();
        }
      }
    }
  }
}