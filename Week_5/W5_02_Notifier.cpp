
#include <iostream>
#include <string>

using namespace std;

void SendSms(const string &number, const string &message) {
    cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string &email, const string &message) {
    cout << "Send '" << message << "' to e-mail " << email << endl;
}

/*
 Реализуйте здесь классы INotifier, SmsNotifier, EmailNotifier
 */

class INotifier {
public:
    virtual void Notify(const string &message) const = 0;
};

class SmsNotifier : public INotifier {
public:
    SmsNotifier(const string &num) : number(num) {};

    virtual void Notify(const string &message) const override {
        SendSms(number, message);
    }

private:
    const string number;
};

class EmailNotifier : public INotifier {
public:
    EmailNotifier(const string &eml) : email(eml) {};

    virtual void Notify(const string &message) const override {
        SendEmail(email, message);
    }

private:
    const string email;
};

void Notify(INotifier &notifier, const string &message) {
    notifier.Notify(message);
}