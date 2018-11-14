#include <mitsuba/core/object.h>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <vector>

NAMESPACE_BEGIN(mitsuba)

void Object::dec_ref(bool dealloc) const noexcept {
    --m_ref_count;
    if (m_ref_count == 0 && dealloc) {
        delete this;
    } else if (m_ref_count < 0) {
        fprintf(stderr, "Internal error: Object reference count < 0!\n");
        abort();
    }
}

std::string Object::id() const {
    std::ostringstream oss;
    oss << class_()->name() << "[" << (void *) this << "]";
    return oss.str();
}

std::string Object::to_string() const {
    return id();
}

std::vector<ref<Object>> Object::expand() const {
    return { };
}

std::vector<ref<Object>> Object::children() {
    return { };
}

Object::~Object() { }

std::ostream& operator<<(std::ostream &os, const Object *object) {
    os << ((object != nullptr) ? object->to_string() : "nullptr");
    return os;
}

MTS_IMPLEMENT_CLASS(Object,)
NAMESPACE_END(mitsuba)
