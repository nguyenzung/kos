#ifndef VECTOR
#define VECTOR
#include <kernel/printer.h>
#include <kernel/type.h>
#include <stdlib/string.h>

using namespace kernel;

namespace std
{


template <typename T>
class Vector
{
public:
    class Iterator 
    {
    public:
      Iterator(T *ptr) : ptr(ptr) {}
      void operator++() { ++ptr; }
      bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
      const T &operator*() const { return *ptr; }
    
    private:
      T *ptr;
    };
    
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
      auto ret = reserve(new_capacity);
      if (ret) {
        if (tmp_m_data != m_data) {
          for (size_t i = 0; i < m_size; i++)
            m_data[i] = tmp_m_data[i];
          delete[] tmp_m_data;
        }
        m_data_tail = m_data + new_capacity;
      } else {
        // may throw an exception here;
      }

      return ret;
  }
public:
  Iterator begin() { return Iterator(m_data); }

  Iterator end() { return Iterator(m_data + size()); }

  bool reserve(size_t s) {
    if (!s)
      return true;
    // lock here
    m_data = new T[s];
    if (m_data) {
      m_data_tail = m_data + s;
    } else {
      return false;
    }
    // unlock here
    return true;
  }

  Vector(size_t s = 0) : m_size(s) {
    bool ret = reserve(m_size);
    if (!ret) {
      // FIX-ME (should thow a exception)
      printf("coundn't reserve memory with %d \n", m_size);
    }
  }

  ~Vector() {
    delete[] m_data;
    m_data = nullptr;
  }

  size_t capacity() const { return (m_data_tail - m_data); }

  size_t size() const { return m_size; }

  void push_back(T &v) {
    if (is_full()) {
      if (!expand())
        return;
    }
    *(m_data + m_size) = v;
    m_size++;
  }

  void push_back(T &&v) {
    if (is_full()) {
      if (!expand())
        return;
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
    // FIX-ME need fix when exception is enabled
    return *(m_data + m_size - 1);
  }
};
}
#endif
