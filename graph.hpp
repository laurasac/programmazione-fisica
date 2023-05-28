#ifndef graph_HPP
#define graph_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "epidemic.hpp"

namespace sir{
void render_window(const int width, const int height, const int delta,
                        sir::Epidemic& epidemic);
void create_graph(sf::RenderWindow& window, const int width, const int height,const int delta, std::vector<sir::SIR> state,  int T, int N);
void create_chart(sf::RenderWindow& window, const int width, const int height,
                  const int delta, int T, int N);
int control_proportions(int a);
}

#endif