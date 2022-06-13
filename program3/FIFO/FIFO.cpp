/*
*FIFO.cpp
*Scott Hockaday
*Course: Operating Systems CS4328
*project 3: Page Replacement Algorithms
* due: 12/02/21
*/

//First-in, First-Out (FIFO)
//declared libraries
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>

const int TOTAL_PAGES = 100;
int FIFO(std::deque<std::string>, int);
bool isExists(std::list<std::string>, std::string);

int main()
{
    int pageFrame = 30;
    std::deque<std::string>myList; //stores the randomly generated pages
    std::string generatedPage;
    int pageFaultNumber_FIFO;

    //generated random page numbers
    srand((int)time(0));
    for (int i = 0; i < TOTAL_PAGES; i++)
    {
        int u;
        u = rand() % 49;
        generatedPage = std::to_string(u);
        myList.push_back(generatedPage);
        std::cout << generatedPage << " ";
    }
    //display the number of page faults
    pageFaultNumber_FIFO = FIFO(myList, pageFrame);
    std::cout << "\n\nNumber of page faults in FIFO: " << pageFaultNumber_FIFO << std::endl;
    return 0;
}
//function to determine page faults
int FIFO(std::deque<std::string> myList, int pageFrame)
{
    int pageFaultCounter = 0;
    std::list<std::string> pageFrameList;
    std::list<std::string>::iterator iter;

    while (myList.size() != 0)
    {
        if (pageFrameList.size() < pageFrame)
        {
            if (isExists(pageFrameList, myList.front()) == false)
            {
                pageFrameList.push_back(myList.front());
                myList.pop_front();
                pageFaultCounter++;
            }
            else
            {
                myList.pop_front();
            }
        }
        else if (pageFrameList.size() == pageFrame)
        {
            bool inPageFrame = false;
            for (iter = pageFrameList.begin(); iter != pageFrameList.end(); iter++)
            {
                if (myList.front() == *iter)
                    inPageFrame = true;
            }

            if (inPageFrame == true)
            {
                myList.pop_front();
            }
            else
            {
                pageFrameList.pop_front();
                pageFrameList.push_back(myList.front());
                myList.pop_front();
                pageFaultCounter++;
            }
        }
    }
    pageFrameList.clear();
    return pageFaultCounter;
}
//function to determine if page exists or not
bool isExists(std::list <std::string> tempList, std::string iterator_One)
{
    std::list<std::string>::iterator iter;
    for (iter = tempList.begin(); iter != tempList.end(); iter++)
    {
        if (*iter == iterator_One)
            return true;
    }
    return false;
}