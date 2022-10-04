#include "pair.h"
#include "vector.h"

void VectorTest01();
void VectorTest02();

void VectorTest() {
  VectorTest01();
  VectorTest02();
}

void VectorTest01() {
  Vector<int> vi;

  Printer::println();
  Printer::println();
  for (int i = 0; i < 6; i++)
    vi.push_back(i);

  CHECK(vi[4] == 4);
  for (auto i : vi) {
    printf("\n[%d] ", i);
  }

  vi.clear();
  CHECK(vi.size() == 0);
  CHECK(vi.capacity() == 0);
}

void VectorTest02() {
  Vector<std::Pair<int, int> *> vi;

  for (int i = 0; i < 7; i++)
    vi.push_back(std::makePair<int, int>(i, 10 - i));

  CHECK(vi[3]->first == 3 && vi[3]->second == 7);
  CHECK(vi.size() == 7);
  for (auto i : vi) {
    printf("\n[%d:%d] ", i->first, i->second);
  }

  vi.clear();
  CHECK(vi.size() == 0);
  CHECK(vi.capacity() == 0);
}
