#pragma once
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <stdexcept>

namespace delta {

class Object; // forward declaration

class Value {
public:
    using List = std::vector<Value>;
    using ObjectPtr = std::shared_ptr<Object>;

    // Variant of all supported runtime types
    using Storage = std::variant<
        double,        // number
        std::string,   // string
        bool,          // boolean
        List,          // list
        ObjectPtr      // object
    >;

    Storage data;

    // Constructors
    Value() : data(0.0) {}
    Value(double n) : data(n) {}
    Value(const char* s) : data(std::string(s)) {}
    Value(const std::string& s) : data(s) {}
    Value(bool b) : data(b) {}
    Value(const List& l) : data(l) {}
    Value(const ObjectPtr& o) : data(o) {}

    // Type checks
    bool isNumber() const { return std::holds_alternative<double>(data); }
    bool isString() const { return std::holds_alternative<std::string>(data); }
    bool isBool()   const { return std::holds_alternative<bool>(data); }
    bool isList()   const { return std::holds_alternative<List>(data); }
    bool isObject() const { return std::holds_alternative<ObjectPtr>(data); }

    // Conversions
    double asNumber() const {
        if (!isNumber()) throw std::runtime_error("Value is not a number");
        return std::get<double>(data);
    }

    int asInt() const {
        return static_cast<int>(asNumber());
    }

    const std::string& asString() const {
        if (!isString()) throw std::runtime_error("Value is not a string");
        return std::get<std::string>(data);
    }

    const List& asList() const {
        if (!isList()) throw std::runtime_error("Value is not a list");
        return std::get<List>(data);
    }

    ObjectPtr asObject() const {
        if (!isObject()) throw std::runtime_error("Value is not an object");
        return std::get<ObjectPtr>(data);
    }
};

} // namespace delta