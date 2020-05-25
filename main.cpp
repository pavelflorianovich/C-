#include<iostream>
#include <vector>
#include <cmath>
#include <fstream>

#define PI 3.14159265
//предполагается сисема координат с нулем в левом верхнем углу экрана
//ось Х  - горизонтальна, направлена в право
//ось Y - вертикальна, направлена вниз

class Point;
class Membrane;
void rotation(std::vector<std::vector <Point>>* v, int N, int M, float a, float b, float g);

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
    float initial_lengthX;
    float initial_lengthY;
    //float initial_lengthZ;
    // единица жестккости связи жесткость связи
    float rigidity;
    //двумерный вектор размера N+2 на M+2. крайние слои мембраны созданы для того, чтобы взимидействие граничных точек мембраны расчитывалось проще
    std::vector<std::vector <Point>> M_Point;

    //конструктор по умолчанию
    Membrane(){
        M = 3;
        N = 3;
        //длинны и размеры по умолнчалию
        initial_lengthY = 100;
        initial_lengthX = 100;
        //initial_lengthZ = 100;
        rigidity = 1;
    }
    //конструктос с задаваемыми размерами мембраны
    Membrane(int N, int M){
        this->N = N;
        this->M = M;
        //длинны и размеры по умолнчалию
        initial_lengthY = 100;
        initial_lengthX = 100;
        //initial_lengthZ = 100;
        rigidity = 1;
    }

    // cоздание мембраны с размера N+2 на M+2 крайние слои пустыщки(жесткость связей их навна 0)
    void membrane_creation();
    //метод взаимодействия точки со своим окружением
    void Dynamics(int i, int j);
    // изменение скарастей и координат мембраны
    void Move_membrane();
    //вывод данных
    void Data_output (int T, Membrane* pWork, float a, float b, float g);
    //КОНЕЦ ТЕЛА КЛАССА
};


// cоздание мембраны с размера N+2 на M+2 крайние слои пустыщки
void Membrane::membrane_creation() {

    //создание двумерного вектора
    for (int i = 0; i < N+2; i++){
        std::vector<Point> temp;
        for(int j = 0; j < M+2; j++){
            temp.push_back(Point());
        }
        M_Point.push_back(temp);
    }

    //заполнение мембраны (двумерного вектора) точками расположеными в форме прямоугольной сетки.
    //сетка дежит в
    //В принцыме начальное расположене очек можно задавать произвольным
    for (int i = 0; i < N+2; i++){
        for(int j = 0; j < M+2; j++){
            // приведение мембраны в начальное состояние с начальным координатами
            M_Point[i][j].SetR(i*initial_lengthX, j*initial_lengthY, 0);
            //Membrane_Point[i][j].SetM( 5); // присваимвание каждой точке macсу
            M_Point[i][j].SerV(0,0,0); //начальное распределение скоростей
        }
    }

    for (int i = 1; i < N+1; i++){ // задание жесткостей свяжей для каждой точки
        for(int j = 1; j < M+1; j++){
            if(i == 1 && j == 1){ //крайние случаи углы
                M_Point[i][j].SetRigidity(0, rigidity, 0, rigidity);
            } else if(i == 1 && j == M){
                M_Point[i][j].SetRigidity(0, rigidity, rigidity, 0);
            } else if ( i == N && j == 1){
                M_Point[i][j].SetRigidity(rigidity, 0, 0, rigidity);
            }else if ( i == N && j == M){
                M_Point[i][j].SetRigidity(rigidity, 0, rigidity, 0);
            }else if ( i == 1 ){ //крайние случаи края
                M_Point[i][j].SetRigidity(rigidity, rigidity, 0, rigidity);
            }else if ( i == N){
                M_Point[i][j].SetRigidity(rigidity, rigidity, rigidity, 0);
            }else if ( j == 1){
                M_Point[i][j].SetRigidity(0, rigidity, rigidity, rigidity);
            }else if ( j == M){
                M_Point[i][j].SetRigidity(rigidity, 0, rigidity, rigidity);
            } else{
                M_Point[i][j].SetRigidity(rigidity, rigidity, rigidity, rigidity); //внутренние точки мембраны
            }
        }
    }
};
void Membrane::Dynamics(int i, int j){
    float length_top, length_bottom, length_left, length_right; //растояние между обектом действия точка Membrane_Point[i][j] и соседями
    float gamma_top, gamma_bottom, gamma_left, gamma_right; //параметр для упрощения формулы

    length_top = distance(M_Point[i][j], M_Point[i][j-1]);
    length_bottom = distance(M_Point[i][j], M_Point[i][j+1]);
    length_left = distance(M_Point[i][j], M_Point[i-1][j]);
    length_right = distance(M_Point[i][j], M_Point[i+1][j]);

    gamma_top = M_Point[i][j].rigidity_Top/M_Point[i][j].m *(1 - M_Point[i][j].Bond_length/ length_top);
    gamma_bottom = M_Point[i][j].rigidity_Bottom/M_Point[i][j].m *(1 - M_Point[i][j].Bond_length/ length_bottom);
    gamma_left = M_Point[i][j].rigidity_Left/M_Point[i][j].m *(1 - M_Point[i][j].Bond_length/ length_left);
    gamma_right = M_Point[i][j].rigidity_Right/M_Point[i][j].m *(1 - M_Point[i][j].Bond_length/ length_right);

    //расчет новых скоростей течки
    M_Point[i][j].Vx += gamma_top * (M_Point[i][j-1].x - M_Point[i][j].x) +
                               gamma_bottom * (M_Point[i][j+1].x - M_Point[i][j].x) +
                               gamma_left * (M_Point[i-1][j].x - M_Point[i][j].x) +
                               gamma_right * (M_Point[i+1][j].x - M_Point[i][j].x);

    M_Point[i][j].Vy += gamma_top * (M_Point[i][j-1].y  - M_Point[i][j].y) +
                               gamma_bottom * (M_Point[i][j+1].y - M_Point[i][j].y) +
                               gamma_left * (M_Point[i-1][j].y - M_Point[i][j].y) +
                               gamma_right * (M_Point[i+1][j].y - M_Point[i][j].y);

    M_Point[i][j].Vz += gamma_top * (M_Point[i][j-1].z  - M_Point[i][j].z) +
                               gamma_bottom * (M_Point[i][j+1].z - M_Point[i][j].z) +
                               gamma_left * (M_Point[i-1][j].z - M_Point[i][j].z) +
                               gamma_right * (M_Point[i+1][j].z - M_Point[i][j].z);
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
            M_Point[i][j].move(M_Point[i][j].Vx, M_Point[i][j].Vy, M_Point[i][j].Vz);
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
void Membrane::Data_output (int T, Membrane* pWork, float a, float b, float g){
    std::ofstream Data("H:\\NewProject\\Data.txt", std::ios_base::trunc);

    //Записываем количество итераций
    Data << T << '\n';
    //Записываем размеры мембраны
    Data << M << '\n';
    Data << N << '\n';

    //поворачиваем
    rotation(&M_Point, N, M, a, b, g);

    for(int t =0; t<T; t++){
        for(int i = 1; i< N+1; i++){
            for(int j = 1; j < M+1; j++){
                Data <<M_Point[i][j].x << '\n';         //Записываем координаты Х точек поле поворота
                Data <<M_Point[i][j].y << '\n';         //Записываем координаты У точек после поворота
                Data <<M_Point[i][j].z << '\n';       //Записываем координаты Z точек после поворота
            }
        }
        (*pWork).Move_membrane();
    }

    Data.close(); //Закрываем файл

};

















int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    //размеры мембраны
    int N, M;
    std::cout<< "N =";;
    std::cin >> N;
    std::cout<< "M =";;
    std::cin >> M;

    Membrane Work(N, M);
    Work.membrane_creation();
    Membrane* pWork = &Work;

    //количество итераций
    int T;
    std::cout<< "T =";;
    std::cin >> T;

    //углы поворота
    float a, b, g;
    std::cout<< "angle a =";
    std::cin>>a;
    std::cout<< "angle b =";
    std::cin>>b;
    std::cout<< "angle g =";
    std::cin>>g;

    //динамика, поворот и запись файла
    Work.Data_output (T, pWork, a, b, g);

    return 0;
}



//матрица повората. Поврацивает координаты двумерного вектора
void rotation(std::vector<std::vector <Point>>* v, int N, int M, float a, float b, float g) {
    // a, b, g --- angles
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int x = (*v)[i][j].x;
            int y = (*v)[i][j].y;
            int z = (*v)[i][j].z;
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