#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student{
public:
    void set_name(string n){
        name_ = n;
    }

    void set_surname(string n){
        surname_ = n;
    }

    void set_album_number(int an){
        if(an >= 10000 && an <= 999999){
            album_number_ = an;
        }
        else{
            cout << "Error! - wrong album number!" << endl;
        }
    }

    void set_grades(float new_grade){
        if(new_grade >= 2.0 && new_grade <= 5.0){
            grades_.emplace_back(new_grade);
        }
        else{
            cout << "Error! - Wrong grade!" << endl;
        }
    }

    void display_student(){
        cout << "Name and Surname: " << name_ << " " << surname_ << endl;
        cout << "Album number: " << album_number_ << endl;
        cout << "Grades: ";
        for(auto value : grades_){
            cout << value << " ";
        }
    }

    float mean_grade(){
        float sum = 0.0;
        for(auto value : grades_){
            sum += value;
        }

        float mean = (sum / grades_.size());
        return mean;
    }

    void if_passed(){
        int a = 0;
        for(auto value : grades_){
            if (value == 2.0){
                a += 1;
            }
        }

        if(a > 1){
            cout << "Student didn't pass the semester. Student has " << a << " 2.0 grades." << endl;
        }
        else{
            cout << "Student passed the semester" << endl;
        }
    }
private:
    string name_;
    string surname_;
    int album_number_;
    vector<float> grades_;
};

class Complex{
public:
    Complex(float real_part, float imaginary_part){
        real_part_ = real_part;
        imaginary_part_ = imaginary_part;
    }

    Complex(float real_part){
        real_part_ = real_part;
        imaginary_part_ = 0;
    }

    void print(){
        if(imaginary_part_ == 0){
            cout << real_part_ << endl;
        }
        else{
            cout << real_part_ << " " << imaginary_part_ << "i" << endl;
        }
    }

    void set_im(float a){
        imaginary_part_ = a;
    }

    void set_real(float a){
        real_part_ = a;
    }

    Complex add(Complex nr){
        nr.imaginary_part_ += imaginary_part_;
        nr.real_part_ += real_part_;

        return nr;
    }

private:
    float real_part_;
    float imaginary_part_;
};

int main()
{
    char option;
    cin >> option;

    switch(option){
    case '1':{
        Student s1;

        s1.set_name("Jakub");
        s1.set_surname("Kazmierczak");
        s1.set_album_number(111222);
        s1.set_grades(4.0);
        s1.set_grades(4.5);
        s1.set_grades(5.0);

        s1.display_student();

        cout << endl << "Mean grade: " << s1.mean_grade() << endl;
        break;
    }

    case '2':{
        Complex a(1.0, -2.0);
        Complex b(3.14);

        b.set_im(-5);

        Complex c = a.add(b);
        c.print();

    }
    };
    return 0;
}
