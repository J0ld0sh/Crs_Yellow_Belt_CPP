#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date &newDate, const string &event) const {
    return true;
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
    if (cmp_ == Comparison::Less) { return (date_ > date); }
    if (cmp_ == Comparison::LessOrEqual) { return (date_ >= date); }
    if (cmp_ == Comparison::Greater) { return (date_ < date); }
    if (cmp_ == Comparison::GreaterOrEqual) { return (date_ <= date); }
    if (cmp_ == Comparison::Equal) { return (date_ == date); }
    if (cmp_ == Comparison::NotEqual) { return (date_ != date); }

    return false;
}

bool EventComparisonNode::Evaluate(const Date &newDate, const string &event) const {
    if (cmp_ == Comparison::Less) { return event_ > event; }
    if (cmp_ == Comparison::LessOrEqual) { return event_ >= event; }
    if (cmp_ == Comparison::Greater) { return event_ < event; }
    if (cmp_ == Comparison::GreaterOrEqual) { return event_ <= event; }
    if (cmp_ == Comparison::Equal) { return event_ == event; }
    if (cmp_ == Comparison::NotEqual) { return event_ != event; }

    return false;
}

bool LogicalOperationNode::Evaluate(const Date &newDate, const string &event) const {
    if (operation_ == LogicalOperation::And) {
        return (left_->Evaluate(newDate, event) && right_->Evaluate(newDate, event));
    }
    if (operation_ == LogicalOperation::Or) {
        return (left_->Evaluate(newDate, event) || right_->Evaluate(newDate, event));
    }

    return false;
}
