#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include "automaton.hpp"
#include "epidemic.hpp"

namespace sir {
int controlProportions(int a);
void createGraph(sf::RenderWindow& window, const int width, const int height,
                  const int margin, std::vector<sir::SIR> state, int T, int N, sf::Font font);
void createChart(sf::RenderWindow& window, const int width, const int height,
                  const int margin, int T, int N, sf::Font font);
void printMap(sf::RenderWindow& window, std::vector<char> map, sir::SIR state, int size,
              int width, int height, int margin, sf::Font font);
void renderWindow(const int width, const int height, const int margin,
                   sir::Epidemic& epidemic);
void renderWindow(const int width, const int height,const int margin, sir::Automaton& automaton);
}  // namespace sir

#endif