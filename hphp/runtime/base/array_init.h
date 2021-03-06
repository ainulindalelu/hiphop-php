/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/
#ifndef incl_HPHP_ARRAY_INIT_H_
#define incl_HPHP_ARRAY_INIT_H_

#include "hphp/runtime/base/array_data.h"
#include "hphp/runtime/base/complex-types.h"
#include "hphp/runtime/base/hphp_array.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////
// macros for creating vectors or maps

#define CREATE_VECTOR1(e)                                               \
  VectorInit(1).add(e).toArray()
#define CREATE_VECTOR2(e1, e2)                                          \
  VectorInit(2).add(e1).add(e2).toArray()
#define CREATE_VECTOR3(e1, e2, e3)                                      \
  VectorInit(3).add(e1).add(e2).add(e3).toArray()
#define CREATE_VECTOR4(e1, e2, e3, e4)                                  \
  VectorInit(4).add(e1).add(e2).add(e3).add(e4).toArray()
#define CREATE_VECTOR5(e1, e2, e3, e4, e5)                              \
  VectorInit(5).add(e1).add(e2).add(e3).add(e4).add(e5).toArray()
#define CREATE_VECTOR6(e1, e2, e3, e4, e5, e6)                          \
  VectorInit(6).add(e1).add(e2).add(e3).add(e4).add(e5).add(e6).toArray()

inline String initkey(const char* s) { return String(s); }
inline int64_t initkey(int k) { return k; }
inline int64_t initkey(int64_t k) { return k; }
inline CStrRef initkey(CStrRef k) { return k; }

#define CREATE_MAP1(n, e) Array(ArrayInit(1).set(initkey(n), e).create())
#define CREATE_MAP2(n1, e1, n2, e2)\
  Array(ArrayInit(2).set(initkey(n1), e1)\
                    .set(initkey(n2), e2).create())
#define CREATE_MAP3(n1, e1, n2, e2, n3, e3)\
  Array(ArrayInit(3).set(initkey(n1), e1)\
                    .set(initkey(n2), e2)\
                    .set(initkey(n3), e3).create())
#define CREATE_MAP4(n1, e1, n2, e2, n3, e3, n4, e4)\
  Array(ArrayInit(4).set(initkey(n1), e1)\
                    .set(initkey(n2), e2)\
                    .set(initkey(n3), e3)\
                    .set(initkey(n4), e4).create())
#define CREATE_MAP5(n1, e1, n2, e2, n3, e3, n4, e4, n5, e5)\
  Array(ArrayInit(5).set(initkey(n1), e1)\
                    .set(initkey(n2), e2)\
                    .set(initkey(n3), e3)\
                    .set(initkey(n4), e4)\
                    .set(initkey(n5), e5).create())
#define CREATE_MAP6(n1, e1, n2, e2, n3, e3, n4, e4, n5, e5, n6, e6)\
  Array(ArrayInit(6).set(initkey(n1), e1)\
                    .set(initkey(n2), e2)\
                    .set(initkey(n3), e3)\
                    .set(initkey(n4), e4)\
                    .set(initkey(n5), e5)\
                    .set(initkey(n6), e6).create())

///////////////////////////////////////////////////////////////////////////////
// ArrayInit

/**
 * When an Array is created, ArrayInit completely skips the use of
 * ArrayElement, (the set methods mimic the constructors of ArrayElement).
 * The setRef method handles the case where the value needs to be a reference.
 *
 * For arrays that need to have C++ references/pointers to their elements for
 * an extended period of time, set keepRef to true, so that there will not
 * be reference-breaking escalation.
 */
class ArrayInit {
public:
  enum MapInit { mapInit };

  explicit ArrayInit(ssize_t n);

  ArrayInit(ssize_t n, MapInit);

  ArrayInit(ArrayInit&& other) : m_data(other.m_data) {
    other.m_data = nullptr;
  }

  ArrayInit(const ArrayInit&) = delete;
  ArrayInit& operator=(const ArrayInit&) = delete;

  ~ArrayInit() {
    // In case an exception interrupts the initialization.
    if (m_data) m_data->release();
  }

  ArrayInit &set(CVarRef v) {
    m_data->append(v, false);
    return *this;
  }

  ArrayInit &set(RefResult v) {
    setRef(variant(v));
    return *this;
  }

  ArrayInit &set(CVarWithRefBind v) {
    m_data->appendWithRef(variant(v), false);
    return *this;
  }

  ArrayInit &setRef(CVarRef v) {
    m_data->appendRef(v, false);
    return *this;
  }

  ArrayInit &set(int64_t name, CVarRef v, bool keyConverted = false) {
    m_data->set(name, v, false);
    return *this;
  }

  // set(const char*) deprecated.  Use set(CStrRef) with a StaticString,
  // if you have a literal, or String otherwise.
  ArrayInit &set(const char*, CVarRef v, bool keyConverted = false) = delete;

  ArrayInit &set(CStrRef name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->set(name, v, false);
    } else if (!name.isNull()) {
      m_data->set(name.toKey(), v, false);
    }
    return *this;
  }

  ArrayInit &set(CVarRef name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->set(name, v, false);
    } else {
      VarNR k(name.toKey());
      if (!k.isNull()) {
        m_data->set(k, v, false);
      }
    }
    return *this;
  }

  template<typename T>
  ArrayInit &set(const T &name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->set(name, v, false);
    } else {
      VarNR k(Variant(name).toKey());
      if (!k.isNull()) {
        m_data->set(k, v, false);
      }
    }
    return *this;
  }

  ArrayInit &set(CStrRef name, RefResult v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->setRef(name, variant(v), false);
    } else if (!name.isNull()) {
      m_data->setRef(name.toKey(), variant(v), false);
    }
    return *this;
  }

  ArrayInit &set(CVarRef name, RefResult v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->setRef(name, variant(v), false);
    } else {
      VarNR k(name.toKey());
      if (!k.isNull()) {
        m_data->setRef(k, variant(v), false);
      }
    }
    return *this;
  }

  template<typename T>
  ArrayInit &set(const T &name, RefResult v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->setRef(name, variant(v), false);
    } else {
      VarNR k(Variant(name).toKey());
      if (!k.isNull()) {
        m_data->setRef(k, variant(v), false);
      }
    }
    return *this;
  }

  ArrayInit &add(int64_t name, CVarRef v, bool keyConverted = false) {
    m_data->add(name, v, false);
    return *this;
  }

  ArrayInit &add(CStrRef name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->add(name, v, false);
    } else if (!name.isNull()) {
      m_data->add(name.toKey(), v, false);
    }
    return *this;
  }

  ArrayInit &add(CVarRef name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->add(name, v, false);
    } else {
      VarNR k(name.toKey());
      if (!k.isNull()) {
        m_data->add(k, v, false);
      }
    }
    return *this;
  }

  template<typename T>
  ArrayInit &add(const T &name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->add(name, v, false);
    } else {
      VarNR k(Variant(name).toKey());
      if (!k.isNull()) {
        m_data->add(k, v, false);
      }
    }
    return *this;
  }

  ArrayInit &setRef(int64_t name, CVarRef v, bool keyConverted = false) {
    m_data->setRef(name, v, false);
    return *this;
  }

  ArrayInit &setRef(CStrRef name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->setRef(name, v, false);
    } else {
      m_data->setRef(name.toKey(), v, false);
    }
    return *this;
  }

  ArrayInit &setRef(CVarRef name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->setRef(name, v, false);
    } else {
      Variant key(name.toKey());
      if (!key.isNull()) {
        m_data->setRef(key, v, false);
      }
    }
    return *this;
  }

  template<typename T>
  ArrayInit &setRef(const T &name, CVarRef v, bool keyConverted = false) {
    if (keyConverted) {
      m_data->setRef(name, v, false);
    } else {
      VarNR key(Variant(name).toKey());
      if (!key.isNull()) {
        m_data->setRef(key, v, false);
      }
    }
    return *this;
  }

  // Prefer toArray() in new code---it can save a null check when the
  // compiler can't prove m_data hasn't changed.
  ArrayData *create() {
    ArrayData *ret = m_data;
    m_data = nullptr;
    return ret;
  }

  Array toArray() {
    auto ptr = m_data;
    m_data = nullptr;
    return Array(ptr, Array::ArrayInitCtor::Tag);
  }

  Variant toVariant() {
    auto ptr = m_data;
    m_data = nullptr;
    return Variant(ptr, Variant::ArrayInitCtor::Tag);
  }

private:
  ArrayData* m_data;
};

/*
 * Initializer for a vector-shaped array.
 */
class VectorInit {
public:
  explicit VectorInit(size_t n) : m_vec(ArrayData::Make(n)) {}

  VectorInit(VectorInit&& other) : m_vec(other.m_vec) {
    other.m_vec = nullptr;
  }

  VectorInit(const VectorInit&) = delete;
  VectorInit& operator=(const VectorInit&) = delete;

  ~VectorInit() {
    // In case an exception interrupts the initialization.
    if (m_vec) m_vec->release();
  }

  VectorInit& add(CVarRef v) {
    m_vec->nvAppend(v.asTypedValue());
    return *this;
  }

  VectorInit& add(CVarWithRefBind v) {
    HphpArray::AppendWithRefVec(m_vec, variant(v), false);
    return *this;
  }

  VectorInit& add(RefResult v) {
    HphpArray::AppendRefVec(m_vec, variant(v), false);
    return *this;
  }

  Variant toVariant() {
    auto ptr = m_vec;
    m_vec = nullptr;
    return Variant(ptr, Variant::ArrayInitCtor::Tag);
  }

  Array toArray() {
    ArrayData* ptr = m_vec;
    m_vec = nullptr;
    return Array(ptr, Array::ArrayInitCtor::Tag);
  }

  ArrayData *create() {
    auto ptr = m_vec;
    m_vec = nullptr;
    return ptr;
  }

private:
  HphpArray* m_vec;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif /* incl_HPHP_ARRAY_INIT_H_ */
