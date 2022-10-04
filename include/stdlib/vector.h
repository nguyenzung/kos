#ifndef VECTOR
#define VECTOR
#include <kernel/printer.h>
#include <kernel/type.h>
#include <stdlib/string.h>

using namespace kernel;
template <typename T> class iterator {
public:
  iterator(T *ptr) : ptr(ptr) {}
  void operator++() { ++ptr; }
  bool operator!=(const iterator &other) const { return ptr != other.ptr; }
  const T &operator*() const { return *ptr; }

private:
  T *ptr;
};
template <typename T>
class Vector
{
  const int ratioAllocate = 2;

private:
  size_t m_size = 0;
  T *m_data = nullptr;
  T *m_data_tail = nullptr;
  bool is_full() { return capacity() == size(); }

  bool expand()
  {
      auto tmp_m_data = m_data;
      size_t new_capacity = capacity() * ratioAllocate + 1;
      reserve(new_capacity);
      if (tmp_m_data != m_data) {
        for (size_t i = 0; i < m_size; i++)
          m_data[i] = tmp_m_data[i];
        delete[] tmp_m_data;
      }
      m_data_tail = m_data + new_capacity;

  }
public:
  iterator<T> begin() { return iterator<T>(m_data); }

  iterator<T> end() { return iterator<T>(m_data + size()); }

  void reserve(size_t s) {
    if (!s)
      return;
    // lock here
    m_data = new T[s];
    m_data_tail = m_data + s;
    // unlock here
  }

  Vector(size_t s = 0) : m_size(s) { reserve(m_size); }

  ~Vector() {
    delete[] m_data;
    m_data = nullptr;
  }

  size_t capacity() const { return (m_data_tail - m_data); }

  size_t size() const { return m_size; }

  void push_back(T &v) {
    if (is_full()) {
	    expand();
    }
    *(m_data + m_size) = v;
    m_size++;
  }

  void push_back(T &&v) {
    if (is_full()) {
	    expand();
      }
    *(m_data + m_size) = (T&&)v;
    m_size++;
  }

  void clear() {
    m_size = 0;
    delete m_data;
    m_data_tail = m_data = nullptr;
  }

  T &operator[](int idx) {
    if (idx < m_size)
      return *(m_data + idx);
    // need fix when exception is enabled
    return *(m_data + m_size - 1);
  }
};

#endif
