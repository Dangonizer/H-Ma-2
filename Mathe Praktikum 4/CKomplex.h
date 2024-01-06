#pragma once
#include <cmath>
#include <vector>
#include <string>

class CKomplex
{
private:
    double real;
    double img;

public:
    CKomplex() : real{0}, img{0} {};
    CKomplex(double a, double b) : real{a}, img{b} {};
    CKomplex(double phi) : real{cos(phi)}, img{sin(phi)} {};

    double re() { return real; }
    double im() { return img; }

    CKomplex operator+(CKomplex a)
    {
        CKomplex result(0, 0);
        result.real = this->real + a.real;
        result.img = this->img + a.img;
        return result;
    }

    CKomplex operator-(CKomplex a)
    {
        CKomplex result(0, 0);
        result.real = this->real - a.real;
        result.img = this->img - a.img;
        return result;
    }

    CKomplex operator*(CKomplex a)
    {
        CKomplex result(0, 0);
        result.real = this->real * a.real - this->img * a.img;
        result.img = this->real * a.img + this->img * a.real;
        return result;
    }

    double abs() { return sqrt(img * img + real * real); }
};

CKomplex operator*(CKomplex a, double b);
CKomplex operator*(double b, CKomplex a);

std::vector<CKomplex> werte_einlesen(const std::string dateiname);
void werte_ausgeben(const std::string dateiname, std::vector<CKomplex> werte, double epsilon = -1.0);

std::vector<CKomplex> fourier(std::vector<CKomplex> data, bool hin = true);

void test_transformation(std::string filename, int index);
void save_files(std::vector<CKomplex> data, int index);
void open_files(int index, std::vector<CKomplex> data_read[5]);
void berechne_abweichung(std::vector<CKomplex> data, std::vector<CKomplex> data_retrans[5]);
void bildverarbeitung(std::string path);