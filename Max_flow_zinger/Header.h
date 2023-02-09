#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
/**
*  \brief  Функция поиска увеличивающегося пути.
*       \details Функция будет искать путь из истока в сток, по которому еще можно пустить поток, считая пропускную способность ребер.
* \param source Исток - начальная вершина
* \param sink Сток - конечная вершина
* \return Значение потока, которое возможно пустить по графу
*/
int find_path(int source, int sink) // source - исток, sink - сток
{
    int array_begin = 0, array_count = 1, number_of_vertices;
    const int max_vertices = 32;
    int iteration_flow[max_vertices];
    int link[max_vertices], flow[max_vertices][max_vertices]; // хранит номер предыдущей вершины для i-ой
    int Array[max_vertices], capacity[max_vertices][max_vertices];
    int current_vertex, maximum = INT_MAX;

    Array[0] = source;

    link[sink] = -1;


    memset(iteration_flow, 0, sizeof(int) * number_of_vertices);//очищаем значение потока, тк на каждой итерации новая вершина

    iteration_flow[source] = maximum; // из истока может вытечь сколько угодно

    while (link[sink] == -1 && array_begin < array_count)
    {
        current_vertex = Array[array_begin];

        for (int i = 0; i < number_of_vertices; i++)

            if ((capacity[current_vertex][i] - flow[current_vertex][i]) > 0 && iteration_flow[i] == 0)
            {
                Array[array_count] = i;

                array_count++;

                link[i] = current_vertex;

                if (capacity[current_vertex][i] - flow[current_vertex][i] < iteration_flow[current_vertex])
                {
                    iteration_flow[i] = capacity[current_vertex][i];
                }
                else
                {
                    iteration_flow[i] = iteration_flow[current_vertex];
                }
            }

        array_begin++;

    }

    if (link[sink] == -1)
    {
        return 0;
    }


    current_vertex = sink;

    while (current_vertex != source)
    {
        flow[link[current_vertex]][current_vertex] += iteration_flow[sink];

        current_vertex = link[current_vertex];
    }
    return iteration_flow[sink];
}
/**
*  \brief Функция поиска максимального потока.
*       \details Функция для поиска максимального потока с помощью алгоритма Форда-Фалкерсона.
*  \param source Исток - начальная вершина
* \param sink Сток - конечная вершина
* \return Значение максимального потока
*/
int maximum_flow(int source, int sink) // source - исток, target - сток
{
    int max_flow = 0,delta;
    const int max_vertices = 32;
    int flow[max_vertices][max_vertices];//значение, на которое будет увеличиваться максимальный поток после очередной итерации
    memset(flow, 0, sizeof(int) * max_vertices * max_vertices);

    do
    {
        delta = find_path(source, sink);

        max_flow += delta;

    } while (delta > 0);

    return max_flow;
}
/**
* \brief Функция записи в файл.
* \details Функция записывает массив в файл в формате .dot для совместимости с graphviz.
* 
*/
void download()
{

    ofstream file;
    file.open("Result.dot", std::ios::out);
    file << "digraph A{\n";
    const int max_vertices = 32;
    int number_of_vertices;
    int flow[max_vertices][max_vertices];
    for (int i = 0; i < number_of_vertices; i++)
    {
        for (int j = 0; j < number_of_vertices; j++)
        {
            if (flow[i][j] != 0)
                file << i << " -> " << j << "[label = " << flow[i][j] << "];\n";
        }

    }
    file << "}";

    system("C://Users//User//source//graphviz//bin//dot.exe -Tpng Result.dot > picture.png");

}

/**
* \brief Функция чтения из файла
* \details Функция читает из файла данные(количество вершин, начальную и конечную вершину и матрицу смежности)
*/
void load()
{
    ifstream file;
    file.open("graf.txt", std::ios::in);
    int number_of_vertices, source, sink;
    const int max_vertices = 32;
    int capacity[max_vertices][max_vertices];
    file >> number_of_vertices;
    file >> source;
    file >> sink;

    for (int i = 0; i < number_of_vertices; i++)
    {
        for (int j = 0; j < number_of_vertices; j++)
        {
            file >> capacity[i][j];
        }
    }
}
