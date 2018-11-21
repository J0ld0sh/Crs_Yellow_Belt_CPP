#pragma once

#include "date.h"
#include "database.h"

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};


class Node {
public:
    virtual bool Evaluate(const Date &newDate, const string &event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date &newDate, const string &event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &cmp, const Date &date) : cmp_(cmp), date_(date) {}

    bool Evaluate(const Date &date, const string &event) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &cmp, const string &event) : cmp_(cmp), event_(event) {};

    bool Evaluate(const Date &newDate, const string &event) const override;

private:
    const Comparison cmp_;
    const string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation logical_operation,
            shared_ptr<Node> left, shared_ptr<Node> right)
            : operation_(logical_operation), left_(left), right_(right) {};

    bool Evaluate(const Date &newDate, const string &event) const override;

private:
    const LogicalOperation operation_;
    shared_ptr<const Node> left_;
    shared_ptr<const Node> right_;
};
