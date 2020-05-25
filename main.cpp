#include<iostream>
#include <vector>
#include <cmath>
#include <fstream>

#define PI 3.14159265
//предполагается сисема координат с нулем в левом верхнем углу экрана
//ось Х  - горизонтальна, направлена в право
//ось Y - вертикальна, направлена вниз

class Point {
//private: //модификатор доступа (https://www.youtube.com/watch?v=6udKffus77A&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=31)
//делаем модификоторы доступа все изначально публичными. Если нужно, то можно изменить, но пока в этом не вижу смысла
public:
    //координаты точки
    float x;
    float y;
    float z;
    // масса точки
    float m;
    //компоненты скорости точки
    float Vx;
    float Vy;
    float Vz;
    // жесткости связей в разных направлениях
    float rigidity_Top;
    float rigidity_Bottom;
    float rigidity_Left;
    float rigidity_Right;
    //длинна связи в свободном ненатянутом состоянии
    float Bond_length;

    //конструктор , по умолчанию
    Point() {
        //координаты и компоненты скорости нулевые
        x = 0;
        y = 0;
        z = 0;
        Vx = 0;
        Vy = 0;
        Vz = 0;
        //масска и жесткости связей единичные
        m = 1;
        rigidity_Top = 1;
        rigidity_Bottom = 1;
        rigidity_Left = 1;
        rigidity_Right = 1;
        //длинна связи в нерастянутом состоянии по умолчанию единица
        Bond_length = 100;
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
// ключевое слово this (https://www.youtube.com/watch?v=2rv_s1j5pHE&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=10)

    //изменение коорнинат точки
    void SetR(float x, float y, float z);
    //изменение компонент скорости точнки
    void SerV(float Vx, float Vy, float Vz);
    //изменение жесткостей пружин (связей)
    void SetRigidity(float rigidity_Top, float rigidity_Bottom, float rigidity_Left, float rigidity_Right);
    // метод расчитывает растояние между двумя тояками a и b
    float distance(Point a, Point b);
    //метод расчитывает новые координаты точки: x += Vx...
    void move(float Vx, float Vy, float Vz);
    //КОНЕЦ ТЕЛА КЛАССА
};

//изменение коорнинат точки
void Point::SetR(float x, float y, float z) { //изменение коорнинат точки
    this->x = x;                                        // ключевое слово this (https://www.youtube.com/watch?v=2rv_s1j5pHE&list=PLQOaTSbfxUtBm7DxblJZShqBQnBAVzlXX&index=10)
    this->y = y;
    this->z = z;
}
//изменение компонент скорости точки
void Point::SerV(float Vx, float Vy, float Vz){
    this->Vx = Vx;
    this->Vy = Vy;
    this->Vz = Vz;
}
//изменение жесткости связи (пружины)
void Point::SetRigidity(float rigidity_Top, float rigidity_Bottom, float rigidity_Left, float rigidity_Right) {
    this->rigidity_Top = rigidity_Top;
    this->rigidity_Bottom = rigidity_Bottom;
    this->rigidity_Right = rigidity_Right;
    this->rigidity_Left = rigidity_Left;
}
// метод расчитывает растояние между двумя тояками a и b
float Point::distance(Point a, Point b){ // метод расчитывает растояние между двумя тояками
    return sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2) + pow((a.z - b.z),2));
};
//метод расчитывает новые координаты точки: x += Vx...
void Point::move(float Vx, float Vy, float Vz){
    x += Vx;
    y += Vy;
    z += Vz;
};










// класс мембрана наследуется от класса Point (хотя наверное это нигде не используется, поэтому его можно убрать)
class Membrane : public Point
{
public:
    //разметры мембраны
    int N; //размер по Х
    int M; //размер по Y
    //начальное растояние между точками по X, Y, Z
    float initial_lengthX =100;
    float initial_lengthY = 100;
    //float initial_lengthZ;
    // единица жестккости связи жесткость связи
    float rigidity =1;

    std::vector<std::vector <Point>> Membrane_Point;

    Membrane(){ //конструктор по умолчанию
        M = 3;
        N = 3;
        //длинны и размеры по умолнчалию
        initial_lengthY = 100;
        initial_lengthX = 100;
        //initial_lengthZ = 100;
        rigidity = 1;
    }

    Membrane(int N, int M){ //конструктос с задаваемыми размерами мембраны
        this->N = N;
        this->M = M;
    }

    void membrane_creation(); // cоздание мембраны с размера N+2 на M+2 крайние слои пустыщки(жесткость связей их навна 0)
    void Dynamics(int i, int j); //метод взаимодействия точки со своим окружением
    void Move_membrane(); // изменение скарастей и координат мембраны
    void Data_output (int T, Membrane* pWork); //вывод данных
    Point Rotation (Point a, float ux, float uy, float uz);
};

// cоздание мембраны с размера N+2 на M+2 крайние слои пустыщки
void Membrane::membrane_creation() {
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
void Membrane::Data_output (int T, Membrane* pWork){
    std::ofstream Data("H:\\NewProject\\Data.txt", std::ios_base::trunc);

    Data << T << '\n';         //Записываем количество итераций
    Data << M << '\n';         //Записываем размеры
    Data << N << '\n';

    for(int t =0; t<T; t++){
        for(int i = 1; i< N+1; i++){
            for(int j = 1; j < M+1; j++){
                Data <<Membrane_Point[i][j].x << '\n';         //Записываем координаты Х точек поле поворота
                Data <<Membrane_Point[i][j].y << '\n';         //Записываем координаты У точек после поворота
                Data <<Membrane_Point[i][j].z << '\n';       //Записываем координаты Z точек после поворота
            }
        }
        (*pWork).Move_membrane();
    }

    Data.close(); //Закрываем файл

};








void rotation(std::vector<std::vector <Point>>* v, int M, int N, float a, float b, float g) {
    // a, b, g --- angles
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int x = (*v)[i][j].x, y = (*v)[i][j].y, z = (*v)[i][j].z;
            (*v)[i][j].x = (cos(a) * cos(g) - sin(a) * cos(b) * sin(g)) * x +
                           (-cos(a) * sin(g) - sin(a) * cos(b) * cos(g)) * y +
                           (sin(a) * sin(b)) * z;
            (*v)[i][j].y = (sin(a) * cos(g) + cos(a) * cos(b) * sin(g)) * x +
                           (-sin(a) * sin(g) + cos(a) * cos(b) * cos(g)) * y +
                           (-cos(a) * sin(b)) * z;
            (*v)[i][j].z = (sin(b) * sin(g)) * x +
                           (sin(b) * cos(g)) * y +
                           cos(b) * z;
        }
    }
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

    Membrane* pWork = &Work;

    Work.Data_output (T, pWork);

    return 0;
}
