#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


class Personage {
public:
    explicit Personage(const string &name) : name_(name) {};

    virtual void Walk(const string &destination) const = 0;

    virtual void SingSong() const = 0;

    virtual void Teach() const = 0;

    virtual void Learn() const = 0;

    virtual string getClassId() const = 0;

    string getName() const { return name_; }

private:
    const string name_;
};

class Student : public Personage {
public:
    Student(const string &name, const string &favouriteSong)
            : Personage(name), favouriteSong_(favouriteSong) {}

    void Learn() const override {
        cout << getClassId() << ": " << getName() << " learns" << endl;
    }

    void Walk(const string &destination) const override {
        cout << getClassId() << ": " << getName() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const override {
        cout << getClassId() << ": " << getName() << " sings a song: " << favouriteSong_ << endl;
    }

protected:
    string getClassId() const override { return "Student"; }

    void Teach() const override {}; // Пусть полежит здесь, т.к. вдруг студент захочет
    // поучить кого  нибудь.

private:
    const string favouriteSong_;
};

class Teacher : public Personage {
public:
    Teacher(const string &name, const string &subject)
            : Personage(name), subject_(subject) {}

    void Teach() const override {
        cout << getClassId() << ": " << getName() << " teaches: " << subject_ << endl;
    }

    void Walk(const string &destination) const override {
        cout << getClassId() << ": " << getName() << " walks to: " << destination << endl;
    }

protected:
    string getClassId() const override { return "Teacher"; }

    void SingSong() const override {}; // Пока не поет, но вдруг?

    void Learn() const override {};    // Всем нужно учиться постоянно, учителя не исключения.

private:
    const string subject_;
};

class Policeman : public Personage {
public:
    explicit Policeman(const string &name) : Personage(name) {}

    void Check(const Personage &person) const {
        cout << getClassId() << ": " << getName() << " checks " <<
             person.getClassId() << ". " << person.getClassId() << "'s name is: " << person.getName() << endl;
    }

protected:
    string getClassId() const override { return "Policeman"; }

    void Walk(const string &destination) const override {}; // Копы могут тупо гулять,
    // делая вид что на службе.

    void SingSong() const override {}; // Приняв на грудь, начать орать песни,

    void Teach() const override {};    // учить уму разуму первого попавшегося гражданина,

    void Learn() const override {};    // и огрести, если гражданин не простой,
                                       // и извлечь из этого урок.

};

void VisitPlaces(Personage &person, vector<string> places) {
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

    // p.Walk("Moscow");
    // p.SingSong();
    // p.Teach();

    return 0;
}