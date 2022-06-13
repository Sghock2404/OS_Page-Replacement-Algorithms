/*
*LRU.cpp
*Scott Hockaday
*Course: Operating Systems CS4328
*project 3: Page Replacement Algorithms
* due: 12/02/21
*/

//Least Recently Used (LRU)
//declared libraries
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>

const int TOTAL_PAGES = 100;
int LRU(std::deque<std::string>, int);
bool isExists(std::vector<std::string>, std::string);
bool isAppearedOnce(std::vector<std::string>&, std::string, int, int);

int main()
{
    int pageFrame = 30;
    std::deque<std::string>myList; //stores the randomly generated pages
    std::string generatedPage;
    int pageFaultNumber_LRU;

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
    pageFaultNumber_LRU = LRU(myList, pageFrame);
    std::cout << "\n\nNumber of page faults in LRU: " << pageFaultNumber_LRU << std::endl;
    return 0;
}
//function to determine page faults
int LRU(std::deque<std::string> myList, int pageFrame)
{
    int pageFaultCounter = 0;
    std::vector<std::string> pageFrameList;
    std::vector<std::string> popped_MyList;
    std::vector<std::string>::iterator iter;
    int tempNum;

    while (myList.size() != 0)
    {
        if (pageFrameList.size() < pageFrame)
        {
            if (isExists(pageFrameList, myList.front()) == false)
            {
                pageFrameList.push_back(myList.front());
                popped_MyList.push_back(myList.front());
                myList.pop_front();
                pageFaultCounter++;
            }
            else
            {
                popped_MyList.push_back(myList.front());
                myList.pop_front();
            }
        }
        else if (pageFrameList.size() == pageFrame)
        {
            if (isExists(pageFrameList, myList.front()))
            {
                popped_MyList.push_back(myList.front());
                myList.pop_front();
            }
            else
            {
                int i = (TOTAL_PAGES - myList.size() - 1);
                std::string changePage;
                tempNum = pageFrame;
                while (tempNum > 0 && i >= 0)
                {
                    for (i = TOTAL_PAGES - myList.size() - 1; i >= 0; i--)
                    {
                        if (isExists(pageFrameList, popped_MyList[i]))
                        {
                            int value = TOTAL_PAGES - myList.size() - 1;
                            if (isAppearedOnce(popped_MyList, popped_MyList[i], value, i))
                            {
                                tempNum--;
                                changePage = popped_MyList[i];
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                popped_MyList.push_back(myList.front());
                myList.pop_front();
                pageFaultCounter++;
            }
        }
    }
    pageFrameList.clear();
    popped_MyList.clear();
    return pageFaultCounter;
}
//function to determine if page exists or not
bool isExists(std::vector<std::string> tempList, std::string iterator_One)
{
    std::vector<std::string>::iterator iter;
    for (int i = 0; i < tempList.size(); i++)
    {
        if (tempList.at(i) == iterator_One)
        {
            return true;
        }
    }
    return false;
}
//function to determine if page appears already
bool isAppearedOnce(std::vector <std::string>& tempList, std::string iterator_One, int num, int currentNum)
{
    for (int i = num; i <= currentNum; i++)
    {
        if (tempList[i] == iterator_One)
        {
            return false;
        }
    }
    return true;
}