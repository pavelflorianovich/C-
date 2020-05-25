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
    float x;
    float y;
    float z;
    float m;
    float Vx;
    float Vy;
    float Vz;
    float rigidity_Top;
    float rigidity_Bottom;
    float rigidity_Left;
    float rigidity_Right;
    float Bond_length;

public:                                                     //модификатор доступа
    Point() {                                                //другой конструктор, по умолчанию
        x = 0;
        y = 0;
        z = 0;
        m = 10;
        Vx = 0;
        Vy = 0;
        Vz = 0;
        rigidity_Top = 5;
        rigidity_Bottom = 5;
        rigidity_Left = 5;
        rigidity_Right = 5;
        Bond_length = 95;
    }

//    Point(float x, float y, float z, float m,
//            float Vx, float Vy, float Vz){              // конструктор
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

//    float GetX() {
//        return x;
//    }
//    float GeY() {
//        return y;
//    }
//    float GetZ() {
//        return z;
//    }
//
//    // ключевое слово this (https://www.youtube.com/watch?v=2rv_s1j5pHE&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=10)
////    void light(float initial_length); //изменение начальной длинны пружины (связи)
    void SetR(float x, float y, float z); //изменение коорнинат точки
    void SerV(float Vx, float Vy, float Vz); //изменение компонент скорости точнки
    void SetRigidity(float rigidity_Top, float rigidity_Bottom, float rigidity_Left, float rigidity_Right); //изменение жесткостей пружин (связей)
    void SetM(float m);                      //реализация метода вне класса. Полезно если класс большой
    float distance(Point a, Point b); // метод расчитывает растояние между двумя тояками
    void move(float VX, float Vy, float Vz);

//    friend void ChangeM(Point& rel);     //Реализация дужественной функции
    //для коректного копирования объекта класса нужно написать конструктор копиравани


//void Point::SetM(float m)
//{                                         //реализация метода вне класса. Полезно если класс большой
//    this->m = m;я (https://www.youtube.com/watch?v=3x9nd6Tm7Pc&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=11)
};
//}
//

void Point::SetR(float x1, float y1, float z1) { //изменение коорнинат точки
    x = x1;                                        // ключевое слово this (https://www.youtube.com/watch?v=2rv_s1j5pHE&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=10)
    y = y1;
    z = z1;
}

void Point::SerV(float Vx, float Vy, float Vz){ //изменение компонент скорости точки
    this->Vx = Vx;
    this->Vy = Vy;
    this->Vz = Vz;
}

void Point::SetRigidity(float rigidity_Top, float rigidity_Bottom, float rigidity_Left, float rigidity_Right) { //изменение жесткости связи (пружины)
    this->rigidity_Top = rigidity_Top;
    this->rigidity_Bottom = rigidity_Bottom;
    this->rigidity_Right = rigidity_Right;
    this->rigidity_Left = rigidity_Left;
}

float Point::distance(Point a, Point b){ // метод расчитывает растояние между двумя тояками
    return sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2) + pow((a.z - b.z),2));
};

void Point::move(float VX, float Vy, float Vz){
    x += Vx;
    y += Vy;
    z += Vz;
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
    float initial_lengthX = 100; //начальное растояние между точками по X
    float initial_lengthY = 100; //начальное растояние между точками по Y
    //float initial_lengthZ; //начальное растояние между точками по Z
    float rigidity =5; // жесткость связи

    std::vector<std::vector <Point>> Membrane_Point;

    Membrane(){ //конструктор по умолчанию
        M = 3;
        N = 3;
        initial_lengthY = 5;
        initial_lengthX = 5;
        rigidity = 20;
    }

    Membrane(int N, int M){ //конструктос с задаваемыми размерами мембраны
        this->N = N;
        this->M = M;
    }

    void membrane_creation(); // cоздание мембраны с размера N+2 на M+2 крайние слои пустыщки(жесткость связей их навна 0)
    void Dynamics(int i, int j); //метод взаимодействия точки со своим окружением
    void Move_membrane(); // изменение скарастей и координат мембраны
    void Data_output (); //вывод данных
    Point Rotation (Point a, float ux, float uy, float uz);
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
            //Membrane_Point[i][j].SetM( 5); // присваимвание каждой точке macсу
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
    float length_top, length_bottom, length_left, length_right; //растояние между обектом действия точка Membrane_Point[i][j] и соседями
    float gamma_top, gamma_bottom, gamma_left, gamma_right; //параметр для упрощения формулы

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

//    for(int i = 1; i < N+1; i++){
//        for(int j = 1; j < M+1; j++){
//            std::cout<< Membrane_Point[i][j].Vx << std::endl;
//            std::cout<< Membrane_Point[i][j].Vy << std::endl;
//            std::cout<< Membrane_Point[i][j].Vz << std::endl;
//            std::cout<< Membrane_Point[i][j].z << std::endl;
//        }
//    }

    for(int i = 1; i < N+1; i++){
        for(int j = 1; j < M+1; j++){
            Membrane_Point[i][j].move(Membrane_Point[i][j].Vx, Membrane_Point[i][j].Vy, Membrane_Point[i][j].Vz);
        }
    }

//    int k = N/2;
//    int c = M/2;
//    int p = 1; //размер "квадрата" центальных точек
//    float V_central = 5; //скорость специального точек
//    for(int i = k-p; i < k+p; i++){
//        for(int j = c-p; j < c+p; j++){
//            Membrane_Point[i][j].Vz += V_central;
//        }
//    }

};
void Membrane::Data_output (){
    std::vector<std::vector <Point>> Membrane_coordinates_Point;
    std::ofstream Data("H:\\NewProject\\Data.txt", std::ios_base::app);

    for(int i = 1; i< N+1; i++){
        for(int j = 1; j < M+1; j++){
            Point data = Rotation(Membrane_Point[i][j], 0, 0, PI/2);
            Data <<data.x << '\n';         //Записываем координаты Х точек поле поворота
            Data <<data.y << '\n';         //Записываем координаты У точек после поворота
            Data <<data.z << '\n';       //Записываем координаты Z точек после поворота
        }
    }
    Data.close(); //Закрываем файл

};
Point Membrane::Rotation(Point a, float ux, float uy, float uz){ //alpha - ux, beta - uy, gamma - uz
    Point res;
//    std::cout<< res.x<< res.y << res.z << std::endl;
//    std::cout<<a.x<< ' '<< a.y << ' '<<a.z<< std::endl;
//    res.x = a.x*(cos(ux)*cos(uz)-sin(ux)*cos(uy)*sin(uz)) + a.y*(-cos(ux)*sin(uz)-sin(ux)*cos(uy)*cos(uz)) + a.z*sin(ux)*sin(uy);
//    res.y = a.x*(sin(ux)*cos(uz)+cos(ux)*cos(uy)*sin(uz)) + a.y*(-sin(uz)*sin(uz) + cos(ux)*cos(uy)*cos(uz)) - a.z*cos(ux)*cos(uy);
//    res.z = a.x*sin(uy)*sin(uz) + sin(uy)*cos(uz)*a.y  + cos(uy)*a.z;
    res.x = a.x;
    res.y = a.y;
    res.z = a.z;
    std::cout<< res.x<< ' '<<res.y <<' '<< res.z << std::endl;
    return res;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M; //размеры мембраны
    std::cout<< "N =";;
    std::cin >> N;
    std::cout<< "M =";;
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
