#pragma once

template<typename OnDeleteFunc>
class Context {
public:
    explicit Context(const OnDeleteFunc& on_delete) : on_delete(on_delete) {}
    ~Context() { this->on_delete(); }
private:
    OnDeleteFunc on_delete;
};
