#include <iostream>
#include <cmath>
#include <climits>
#define _USE_MATH_DEFINES

using namespace std;

void Cin_Check(double &number)
{
    bool typeFail;

    do
    {
        cin >> number;
        typeFail = cin.fail();
        if (typeFail)
        {
            cout << "Error! Enter correct value\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    while (typeFail);

    return;
}

class ComplexTrigonometry
{
protected:
    double x, y,
           r, phi;

public:
//Сеттеры:
    void setX(double val)
    {
        x = val;
    }

    void setX()// для умножения и деления
    {
        x = r * cos(phi);
    }

    void setY(double val)
    {
        y = val;
    }

    void setY() // для умножения и деления
    {
        y = r * sin(phi);
    }

    void setModule(double x, double y)
    {
        r = sqrt(x*x + y*y);
    }

    void setModule(double r_val)//для умножения и деления
    {
        r = r_val;
    }

    void setPhi()
    {
        if ((x/r) == 0.0) //частные случаи
        {
            if ((y/r) == 1.0)
            {
                phi = 90.0;
            }
            if ((y/r) == -1.0)
            {
                phi = 270.0;
            }
        }
        else
        {
            if ((y/r) == 0.0)
            {
                if ((x/r) == 1.0)
                {
                    phi = 0.0;
                }
                if ((x/r) == -1.0)
                {
                    phi = 180.0;
                }
            }
            else //общий случай
            {
                phi = acos(x/r) * 180.0 / M_PI; //угол фи в градусах
            }
        }

        return;
    }

    void setPhi(double phi_val)//для умножения и деления
    {
        phi = phi_val;
    }
//Конструкторы и деструкторы:
    ComplexTrigonometry(double x, double y)
    {
        setX(x);
        setY(y);
        setModule(x, y);
        setPhi();
    }

    ComplexTrigonometry(double x) //конструктор для сложения с действительным числом
    {
        setX(x);
        setY(0.0);
        setModule(x, y);
        setPhi();
    }

    ComplexTrigonometry()
    {
        setX(0.0);
        setY(0.0);
    }

    ~ComplexTrigonometry()
    {
    }

//Перегрузки операций:
    ComplexTrigonometry operator+(const ComplexTrigonometry &res_plus)
    {
        return ComplexTrigonometry(x + res_plus.x, y + res_plus.y);
    }

    ComplexTrigonometry operator-(const ComplexTrigonometry &res_minus)
    {
        return ComplexTrigonometry(x - res_minus.x, y - res_minus.y);
    }

    ComplexTrigonometry operator*(const ComplexTrigonometry &res_mul)
    {
        ComplexTrigonometry temp;
        double phi_val = phi + res_mul.phi;
        double r_val = r * res_mul.r;

        temp.setPhi(phi_val);
        temp.setModule(r_val);
        temp.setX();
        temp.setY();
        return temp;
    }

    ComplexTrigonometry operator/(const ComplexTrigonometry &res_div)
    {
        ComplexTrigonometry temp;
        double phi_val = phi - res_div.phi;
        double r_val = r / res_div.r;

        temp.setPhi(phi_val);
        temp.setModule(r_val);
        temp.setX();
        temp.setY();
        return temp;
    }

    void print()
    {
        cout << r << "e^(i*"<< phi << ") = "
             << r << "(cos(" << phi << ") + isin(" << phi << "))\n";

        if (phi != phi)
        {
            cout << "phi = nan because module = 0 => x/r or y/r = nan => angle undefined\n";
        }

        return;
    }
};

class Real_And_Imaginary: private ComplexTrigonometry
{
public:

    Real_And_Imaginary(double phi_val, double r_val)
    {
        setPhi(phi_val);
        setModule(r_val);
    }

    Real_And_Imaginary()
    {
    }

    ~Real_And_Imaginary()
    {
    }

    void Calc_x_y()
    {
        double phi_rad = phi * M_PI / 180.0;
        x = r * cos(phi_rad);
        y = r * sin(phi_rad);
        cout << "\nx = " << x << "\n";
        cout << "y = " << y << "\n";
        return;
    }

    void Complex_Conjugate()
    {
        Real_And_Imaginary temp = Real_And_Imaginary();
        temp.x = x;
        temp.y = -y;

        if (temp.y > 0)
        {
            cout << "\nComplex conjugate = " << temp.x << " + " << temp.y << "i";
        }
        else
        {
            cout << "\nComplex conjugate = " << temp.x << temp.y << "i";
        }

        return;
    }
};

int main()
{
    double x1 = 0;
    cout << "Enter real part of your first complex number\n";
    Cin_Check(x1);

    double y1 = 0;
    cout << "Enter imaginary part of your first complex number\n";
    Cin_Check(y1);

    cout << "Your first complex number:\n";
    cout << x1 << " + " << y1 << "i\n";


    double x2 = 0;
    cout << "\nEnter real part of your second complex number\n";
    Cin_Check(x2);

    double y2 = 0;
    cout << "Enter imaginary part of your second complex number\n";
    Cin_Check(y2);

    cout << "Your second complex number:\n";
    cout << x2 << " + " << y2 << "i\n";


    ComplexTrigonometry obj_1 = ComplexTrigonometry(x1, y1);
    ComplexTrigonometry obj_2 = ComplexTrigonometry(x2, y2);

    cout << "\nYour the first complex number in trigonometric form:\n";
    obj_1.print();
    cout << "\nYour the second complex number in trigonometric form:\n";
    obj_2.print();


    ComplexTrigonometry res_plus = obj_1 + obj_2;
    cout << "\nThe result of adding your complex numbers:\n";
    res_plus.print();

    ComplexTrigonometry res_minus = obj_1 - obj_2;
    cout << "\nThe result of substraction your complex numbers(1-st - 2-nd):\n";
    res_minus.print();

    ComplexTrigonometry res_mul = obj_1 * obj_2;
    cout << "\nThe result of multiplication your the first complex number and the second complex number:\n";
    res_mul.print();

    ComplexTrigonometry res_div = obj_1 / obj_2;
    cout << "\nThe result of division your the first complex number and the second complex number:\n";
    res_div.print();

    double real = 0.0;
    cout << "\nEnter a real number for adding:\n";
    Cin_Check(real);
    ComplexTrigonometry res_plus_real = obj_1 + real;
    cout << "\nThe result of substraction your the first complex number and real number:\n";
    res_plus_real.print();


    cout << "\nEnter the third complex number with phi and r\n";
    cout << "Enter phi angle(in degrees):\n";
    double phi = 0.0;
    Cin_Check(phi);

    cout << "Enter r module:\n";
    double r = 0.0;
    Cin_Check(r);

    Real_And_Imaginary obj_3 = Real_And_Imaginary(phi, r);
    obj_3.Calc_x_y();
    obj_3.Complex_Conjugate();

    return 0;
}
