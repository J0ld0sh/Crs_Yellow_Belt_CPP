#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Personage {
public:
    explicit Personage(const string &name, const string &classId) : name_(name), classId_(classId) {};

    virtual void Walk(const string &destination) const {
        cout << getClassId() << ": " << getName() << " walks to: " << destination << endl;
    };

    virtual void Learn() const {
        cout << getClassId() << ": " << getName() << " learns" << endl;
    };

    string getName() const { return name_; }

    string getClassId() const { return classId_; }

private:
    const string name_;
    const string classId_;
};

class Student : public Personage {
public:
    explicit Student(const string &name, const string &favouriteSong) : Personage(name, "Student"),
                                                                        favouriteSong_(favouriteSong) {}

    void Walk(const string &destination) const override {
        cout << getClassId() << ": " << getName() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << getClassId() << ": " << getName() << " sings a song: " << favouriteSong_ << endl;
    }

private:
    const string favouriteSong_;
};

class Teacher : public Personage {
public:
    explicit Teacher(const string &name, const string &subject) : Personage(name, "Teacher"), subject_(subject) {}

    void Teach() const {
        cout << getClassId() << ": " << getName() << " teaches: " << subject_ << endl;
    }

private:
    const string subject_;

    void Learn() const override {};
};

class Policeman : public Personage {
public:
    explicit Policeman(const string &name) : Personage(name, "Policeman") {}

    void Check(const Personage &person) const {
        cout << getClassId() << ": " << getName() << " checks " <<
             person.getClassId() << ". " << person.getClassId() << "'s name is: " << person.getName() << endl;
    }

private:
    void Walk(const string &destination) const override {};

    void Learn() const override {};
};

void VisitPlaces(const Personage &person, const vector<string> &places) {
    for (auto &p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});

    return 0;
}
