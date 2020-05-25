#include<iostream>
#include <vector>
#include <cmath>
#include <fstream>
#define PI 3.14159265
//предполагается сисема координат с нулем в левом верхнем углу экрана
//ось Х  - горизонтальна, направлена в право
//ось Y - вертикальна, направлена вниз

class Point  {
//private: //модификатор доступа (https://www.youtube.com/watch?v=6udKffus77A&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=31)
public:
    double x;
    double y;
    double z;
    double m;
    double Vx;
    double Vy;
    double Vz;
    double rigidity_Top;
    double rigidity_Bottom;
    double rigidity_Left;
    double rigidity_Right;
    double Bond_length;

public:                                                     //модификатор доступа
    Point() {                                                //другой конструктор, по умолчанию
        x = 0;
        y = 0;
        z = 0;
        m = 1;
        Vx = 0;
        Vy = 0;
        Vz = 0;
        rigidity_Top = 0;
        rigidity_Bottom = 0;
        rigidity_Left = 0;
        rigidity_Right = 0;
        Bond_length = 5;
    }

//    Point(double x, double y, double z, double m,
//            double Vx, double Vy, double Vz){              // конструктор
//        this->x = x;
//        this->y = y;
//        this->z = z;
//        this->m = m;
//        this->Vx = Vx;
//        this->Vy = Vy;
//        this->Vz = Vz;
//    }

//    ~Point() {                                               //диструктор. Может быть только один.
//        // Вызывается, при выходе из зоны видимити {}
//        // полезен для очистки динамической памяти
//    }

//    double GetX() {
//        return x;
//    }
//    double GeY() {
//        return y;
//    }
//    double GetZ() {
//        return z;
//    }
//
//    // ключевое слово this (https://www.youtube.com/watch?v=2rv_s1j5pHE&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=10)
////    void light(double initial_length); //изменение начальной длинны пружины (связи)
    void SetR(double x, double y, double z); //изменение коорнинат точки
    void SerV(double Vx, double Vy, double Vz); //изменение компонент скорости точнки
    void SetRigidity(double rigidity_Top, double rigidity_Bottom, double rigidity_Left, double rigidity_Right); //изменение жесткостей пружин (связей)
    void SetM(double m);                      //реализация метода вне класса. Полезно если класс большой
    double distance(Point a, Point b); // метод расчитывает растояние между двумя тояками
    void move(Point object);

//    friend void ChangeM(Point& rel);     //Реализация дужественной функции
    //для коректного копирования объекта класса нужно написать конструктор копиравани


//void Point::SetM(double m)
//{                                         //реализация метода вне класса. Полезно если класс большой
//    this->m = m;я (https://www.youtube.com/watch?v=3x9nd6Tm7Pc&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=11)
};
//}
//

void Point::SetR(double x1, double y1, double z1) { //изменение коорнинат точки
    x = x1;                                        // ключевое слово this (https://www.youtube.com/watch?v=2rv_s1j5pHE&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=10)
    y = y1;
    z = z1;
}

void Point::SerV(double Vx, double Vy, double Vz){ //изменение компонент скорости точки
    this->Vx = Vx;
    this->Vy = Vy;
    this->Vz = Vz;
}

void Point::SetRigidity(double rigidity_Top, double rigidity_Bottom, double rigidity_Left, double rigidity_Right) { //изменение жесткости связи (пружины)
    this->rigidity_Top = rigidity_Top;
    this->rigidity_Bottom = rigidity_Bottom;
    this->rigidity_Right = rigidity_Right;
    this->rigidity_Left = rigidity_Left;
}

double Point::distance(Point a, Point b){ // метод расчитывает растояние между двумя тояками
    return sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2) + pow((a.z - b.z),2));
};

void Point::move(Point object){
    object.x += object.Vx;
    object.y += object.Vy;
    object.z += object.Vx;
};





//void ChangeM(Point& rel) {             //Реализация дужественной функции (https://www.youtube.com/watch?v=Ic19I0kcBnU&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=19)
//    rel.m += 1;                          //Одна функция может быть дужественной к нескольким классам
//    //дружестенная функция имеет доступ ко всем объектам класса (не зависимо от расположения)
//}







class Membrane : public Point
    // класс мембраны
{
public:
    //разметры мембраны
    int N; //размер по Х
    int M; //размер по Y
    double initial_lengthX; //начальное растояние между точками по X
    double initial_lengthY; //начальное растояние между точками по Y
    //double initial_lengthZ; //начальное растояние между точками по Z
    double rigidity; // жесткость связи

    std::vector<std::vector <Point>> Membrane_Point;

    Membrane(){ //конструктор по умолчанию
        M = 3;
        N = 3;
        initial_lengthY = 5;
        initial_lengthX = 5;
        rigidity = 10000000;
    }

    Membrane(int N, int M){ //конструктос с задаваемыми размерами мембраны
        this->N = N;
        this->M = M;
    }

    void membrane_creation(); // cоздание мембраны с размера N+2 на M+2 крайние слои пустыщки(жесткость связей их навна 0)
    void Dynamics(int i, int j); //метод взаимодействия точки со своим окружением
    void Move_membrane(); // изменение скарастей и координат мембраны
    void Data_output (); //вывод данных
    Point Rotation (Point a, double ux, double uy, double uz);
};

void Membrane::membrane_creation() { // cоздание мембраны с размера N+2 на M+2 крайние слои пустыщки
    for (int i = 0; i < N+2; i++){
        std::vector<Point> temp;
        for(int j = 0; j < M+2; j++){
            temp.push_back(Point());
        }
        Membrane_Point.push_back(temp);
    }

    for (int i = 1; i < N+1; i++){
        for(int j = 1; j < M+1; j++){
            Membrane_Point[i][j].SetR(i*initial_lengthX, j*initial_lengthY, 0); // приведение мембраны в начальное состояние с начальным координатами
//            Membrane_Point[i][j].SetM( 5); // присваимвание каждой точке macсу
            Membrane_Point[i][j].SerV(0,0,100); //начальное распределение скоростей
        }
    }

    for (int i = 1; i < N+1; i++){ // задание жесткостей свяжей для каждой точки
        for(int j = 1; j < M+1; j++){
            if(i == 1 && j == 1){ //крайние случаи углы
                Membrane_Point[i][j].SetRigidity(0, rigidity, 0, rigidity);
            } else if(i == 1 && j == M){
                Membrane_Point[i][j].SetRigidity(0, rigidity, rigidity, 0);
            } else if ( i == N && j == 1){
                Membrane_Point[i][j].SetRigidity(rigidity, 0, 0, rigidity);
            }else if ( i == N && j == M){
                Membrane_Point[i][j].SetRigidity(rigidity, 0, rigidity, 0);
            }else if ( i == 1 ){ //крайние случаи края
                Membrane_Point[i][j].SetRigidity(rigidity, rigidity, 0, rigidity);
            }else if ( i == N){
                Membrane_Point[i][j].SetRigidity(rigidity, rigidity, rigidity, 0);
            }else if ( j == 1){
                Membrane_Point[i][j].SetRigidity(0, rigidity, rigidity, rigidity);
            }else if ( j == M){
                Membrane_Point[i][j].SetRigidity(rigidity, 0, rigidity, rigidity);
            } else{
                Membrane_Point[i][j].SetRigidity(rigidity, rigidity, rigidity, rigidity); //внутренние точки мембраны
            }

        }
    }


};
void Membrane::Dynamics(int i, int j){
    double length_top, length_bottom, length_left, length_right; //растояние между обектом действия точка Membrane_Point[i][j] и соседями
    double gamma_top, gamma_bottom, gamma_left, gamma_right; //параметр для упрощения формулы

    length_top = distance(Membrane_Point[i][j], Membrane_Point[i][j-1]);
    length_bottom = distance(Membrane_Point[i][j], Membrane_Point[i][j+1]);
    length_left = distance(Membrane_Point[i][j], Membrane_Point[i-1][j]);
    length_right = distance(Membrane_Point[i][j], Membrane_Point[i+1][j]);

    gamma_top = Membrane_Point[i][j].rigidity_Top/Membrane_Point[i][j].m *(1 - Membrane_Point[i][j].Bond_length/ length_top);
    gamma_bottom = Membrane_Point[i][j].rigidity_Bottom/Membrane_Point[i][j].m *(1 - Membrane_Point[i][j].Bond_length/ length_bottom);
    gamma_left = Membrane_Point[i][j].rigidity_Left/Membrane_Point[i][j].m *(1 - Membrane_Point[i][j].Bond_length/ length_left);
    gamma_right = Membrane_Point[i][j].rigidity_Right/Membrane_Point[i][j].m *(1 - Membrane_Point[i][j].Bond_length/ length_right);

    //расчет новых скоростей течки
    Membrane_Point[i][j].Vx += gamma_top * (Membrane_Point[i][j-1].x  - Membrane_Point[i][j].x) +
                               gamma_bottom * (Membrane_Point[i][j+1].x - Membrane_Point[i][j].x) +
                               gamma_left * (Membrane_Point[i-1][j].x - Membrane_Point[i][j].x) +
                               gamma_right * (Membrane_Point[i+1][j].x - Membrane_Point[i][j].x);

    Membrane_Point[i][j].Vy += gamma_top * (Membrane_Point[i][j-1].y  - Membrane_Point[i][j].y) +
                               gamma_bottom * (Membrane_Point[i][j+1].y - Membrane_Point[i][j].y) +
                               gamma_left * (Membrane_Point[i-1][j].y - Membrane_Point[i][j].y) +
                               gamma_right * (Membrane_Point[i+1][j].y - Membrane_Point[i][j].y);

    Membrane_Point[i][j].Vz += gamma_top * (Membrane_Point[i][j-1].z  - Membrane_Point[i][j].z) +
                               gamma_bottom * (Membrane_Point[i][j+1].z - Membrane_Point[i][j].z) +
                               gamma_left * (Membrane_Point[i-1][j].z - Membrane_Point[i][j].z) +
                               gamma_right * (Membrane_Point[i+1][j].z - Membrane_Point[i][j].z);
}
void Membrane::Move_membrane() {
    for(int i = 1; i < N+1; i++){
        for(int j = 1; j < M+1; j++){
            Dynamics(i, j);
        }
    }

    for(int i = 1; i < N+1; i++){
        for(int j = 1; j < M+1; j++){
            Membrane_Point[i][j].move(Membrane_Point[i][j]);
        }
    }
//    int k = N/2;
//    int c = M/2;
//    int p = 1; //размер "квадрата" центальных точек
//    double V_central = 5; //скорость специального точек
//    for(int i = k-p; i < k+p; i++){
//        for(int j = c-p; j < c+p; j++){
//            Membrane_Point[i][j].Vz += V_central;
//        }
//    }

};
void Membrane::Data_output (){
    std::vector<std::vector <Point>> Membrane_coordinates_Point;
    std::ofstream Data("H:\\NewProject\\Data.txt");

    for(int i = 1; i< N+1; i++){
        for(int j = 1; j < M+1; j++){

            Data <<Membrane_Point.x << '\n';         //Записываем координаты Х точек поле поворота
            Data <<Membrane_Point.y << '\n';         //Записываем координаты У точек после поворота
            Data <<Membrane_Point.z << '\n';       //Записываем координаты Z точек после поворота
        }
    }
    Data.close(); //Закрываем файл

};




int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M; //размеры мембраны
    std::cout<< "N =";
    std::cin >> N;
    std::cout<< "M =";
    std::cin >> M;

    Membrane Work(N, M);
    Work.membrane_creation();

    int T;
    std::cout<< "T =";;
    std::cin >> T;

    for(int i =0; i<T; i++){
        Work.Data_output();
        Work.Move_membrane();
    }


    return 0;
}
