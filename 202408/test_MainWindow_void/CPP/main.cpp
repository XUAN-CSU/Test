#include <iostream>
#include <string>

class Person {
    private:
        int age;
        std::string name;

    public:
        Person(std::string name, int age);
        Person(std::string name);
        ~Person();
        friend std::ostream& operator<<(std::ostream& os, const Person& person);
        Person& operator++();
        Person& operator++(int);
};

Person::Person(std::string name, int age)
{
    this->name = name;
    this->age = age;
}

Person::Person(std::string name)
{
    this->name = name;
    this->age = 18;
}

Person& Person::operator++()
{
    ++age;
    return *this;
}

Person& Person::operator++(int)
{
    age++;
    return *this;
}

Person::~Person()
{

}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
    os << "Name : "<< person.name << " , Age : " << person.age;
    return os;
}

    
       
int main()
{
    Person p1("wlc", 28);
    std::cout << p1 << std::endl;

    ++p1;
    std::cout << p1 << std::endl;

    p1++;
    std::cout << p1 << std::endl;


    return 0;
}

