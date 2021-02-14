//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include <initializer_list>
#include <map>
#include <string>
#include <utility>

class Json
{
  public:
    enum class Type
    {
        NULL_TYPE,
        STRING,
        BOOL,
        NUMBER,
        OBJECT,
        ARRAY,
    };

  private:
    Type m_type{};
    std::string m_strVal{};
    int64_t m_intVal{};

    // TODO: Switch to some ordered map (preserving insertion order)
    std::map<std::string, Json> m_children{};

  private:
    typedef decltype(m_children.begin()) iterator;
    typedef decltype(const_cast<const std::map<std::string, Json> &>(m_children).begin()) const_iterator;

  public:
    Json();
    /* no-explicit */ Json(nullptr_t v);
    /* no-explicit */ Json(std::string str);
    /* no-explicit */ Json(const char *str);
    /* no-explicit */ Json(bool v);
    /* no-explicit */ Json(uint8_t v);
    /* no-explicit */ Json(int8_t v);
    /* no-explicit */ Json(uint16_t v);
    /* no-explicit */ Json(int16_t v);
    /* no-explicit */ Json(uint32_t v);
    /* no-explicit */ Json(int32_t v);
    /* no-explicit */ Json(int64_t v);
    /* no-explicit */ Json(uint64_t v) = delete;

  public:
    static Json Arr(std::initializer_list<Json> &&elements);
    static Json Obj(std::initializer_list<std::pair<std::string, Json>> &&elements);

  public:
    [[nodiscard]] Type type() const;
    [[nodiscard]] bool isNull() const;
    [[nodiscard]] bool isString() const;
    [[nodiscard]] bool isBool() const;
    [[nodiscard]] bool isNumber() const;
    [[nodiscard]] bool isObject() const;
    [[nodiscard]] bool isArray() const;
    [[nodiscard]] bool isPrimitive() const;
    [[nodiscard]] int itemCount() const;

  public:
    [[nodiscard]] std::string str() const;
    [[nodiscard]] int int32() const;
    [[nodiscard]] int64_t int64() const;
    [[nodiscard]] bool boolean() const;

  public:
    [[nodiscard]] iterator begin();
    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] iterator end();
    [[nodiscard]] const_iterator end() const;

  public:
    [[nodiscard]] std::string dumpJson() const;
    [[nodiscard]] std::string dumpYaml() const;
};