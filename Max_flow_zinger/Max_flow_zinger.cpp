
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
#include "Header.h"
/** 
* \brief main-функция
* \details Здесь вызываются функции чтения, записи в файл, а также главная функция для нахождения максимального потока
*/
int main()
{
    load();

    int source, sink;

    cout << "Maximum flow: " << maximum_flow(source, sink);

    download();

    return 0;
}