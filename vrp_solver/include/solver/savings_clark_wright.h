//
// Created by petkovic on 04.04.25.
//

#ifndef SAVINGS_CLARK_WRIGHT_H
#define SAVINGS_CLARK_WRIGHT_H

#include <solver/solver.h>

struct Saving {
  uint16_t from_node_id;
  uint16_t to_node_id;
  double value;

  bool operator<(const Saving &other) const {
    return value > other.value;
  }
};

class SavingsClarkWright : public Solver {
public:
  SavingsClarkWright(Graph &g, Vehicle &v) : Solver(g, v) {
  }

  void solve() override;

private:
  std::vector<Saving> savings_vector;
  void initRoutes();

  void calculateSavings();

  void combineRoutes(uint16_t from, uint16_t to);
};


#endif //SAVINGS_CLARK_WRIGHT_H
