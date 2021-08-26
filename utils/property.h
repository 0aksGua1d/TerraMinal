#pragma once

template<typename T> struct argument_type;
template<typename T, typename U> struct argument_type<T(U)> { typedef U type; };

#define PROPERTY(t, n)  private: \
                            typedef argument_type<void(t)>::type _property_tmp_type_##n; \
                        public: \
                            _property_tmp_type_##n _property_get_##n() const { return std::any_cast<_property_tmp_type_##n>(this->local_scope->variables[L###n]); } \
                            void _property_set_##n(const _property_tmp_type_##n& value) { this->local_scope->variables[L###n] = value; }

#define READONLY_PROPERTY(t, n) private: \
                                    typedef argument_type<void(t)>::type _property_tmp_type_##n; \
                                public: \
                                    const _property_tmp_type_##n _property_get_##n() const { return std::any_cast<_property_tmp_type_##n>(this->local_scope->variables[L###n]); }

#define WRITEONLY_PROPERTY(t, n)    private: \
                                        typedef argument_type<void(t)>::type _property_tmp_type_##n; \
                                    public: \
                                        void _property_set_##n(const _property_tmp_type_##n& value) { this->local_scope->variables[L###n] = value; }

#define GET(o, n) o._property_get_##n()
#define GET_PTR(o, n) o->_property_get_##n()

#define SET(o, n, v) o._property_set_##n(v)
#define SET_PTR(o, n, v) o->_property_set_##n(v)
