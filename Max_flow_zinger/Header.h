#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
/**
*  \brief  ������� ������ ���������������� ����.
*       \details ������� ����� ������ ���� �� ������ � ����, �� �������� ��� ����� ������� �����, ������ ���������� ����������� �����.
* \param source ����� - ��������� �������
* \param sink ���� - �������� �������
* \return �������� ������, ������� �������� ������� �� �����
*/
int find_path(int source, int sink) // source - �����, sink - ����
{
    int array_begin = 0, array_count = 1, number_of_vertices;
    const int max_vertices = 32;
    int iteration_flow[max_vertices];
    int link[max_vertices], flow[max_vertices][max_vertices]; // ������ ����� ���������� ������� ��� i-��
    int Array[max_vertices], capacity[max_vertices][max_vertices];
    int current_vertex, maximum = INT_MAX;

    Array[0] = source;

    link[sink] = -1;


    memset(iteration_flow, 0, sizeof(int) * number_of_vertices);//������� �������� ������, �� �� ������ �������� ����� �������

    iteration_flow[source] = maximum; // �� ������ ����� ������ ������� ������

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
*  \brief ������� ������ ������������� ������.
*       \details ������� ��� ������ ������������� ������ � ������� ��������� �����-����������.
*  \param source ����� - ��������� �������
* \param sink ���� - �������� �������
* \return �������� ������������� ������
*/
int maximum_flow(int source, int sink) // source - �����, target - ����
{
    int max_flow = 0,delta;
    const int max_vertices = 32;
    int flow[max_vertices][max_vertices];//��������, �� ������� ����� ������������� ������������ ����� ����� ��������� ��������
    memset(flow, 0, sizeof(int) * max_vertices * max_vertices);

    do
    {
        delta = find_path(source, sink);

        max_flow += delta;

    } while (delta > 0);

    return max_flow;
}
/**
* \brief ������� ������ � ����.
* \details ������� ���������� ������ � ���� � ������� .dot ��� ������������� � graphviz.
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
* \brief ������� ������ �� �����
* \details ������� ������ �� ����� ������(���������� ������, ��������� � �������� ������� � ������� ���������)
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
